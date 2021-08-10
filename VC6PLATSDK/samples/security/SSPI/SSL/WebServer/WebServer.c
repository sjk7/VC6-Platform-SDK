/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999 - 2002  Microsoft Corporation.  All rights reserved.

Module Name:

    webserver.c

Abstract:

    Schannel web server sample application.

--*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock.h>
#include <wincrypt.h>
#include <wintrust.h>
#include <schannel.h>

#define SECURITY_WIN32
#include <security.h>
#include <sspi.h>

#define IO_BUFFER_SIZE  0x10000
#define DLL_NAME TEXT("Secur32.dll")
#define NT4_DLL_NAME TEXT("Security.dll")

// User options.
INT     iPortNumber     = 443;
BOOL    fVerbose        = FALSE;
LPSTR   pszUserName     = NULL;
BOOL    fClientAuth     = FALSE;
BOOL    fMachineStore   = FALSE;
DWORD   dwProtocol      = 0;

HCERTSTORE  hMyCertStore = NULL;

CHAR IoBuffer[IO_BUFFER_SIZE];
DWORD cbIoBuffer = 0;

HMODULE g_hSecurity = NULL;

PSecurityFunctionTable g_pSSPI;


static
DWORD
CreateCredentials(
    LPSTR pszUserName,
    PCredHandle phCreds);

static void
WebServer(CredHandle *phServerCreds);

static
BOOL
ParseRequest (
    IN PCHAR InputBuffer,
    IN INT InputBufferLength,
    OUT PCHAR ObjectName,
    OUT DWORD *pcbContentLength);

static
BOOL
SSPINegotiateLoop(
    SOCKET          Socket,
    PCtxtHandle     phContext,
    PCredHandle     phCred,
    BOOL            fClientAuth,
    BOOL            fDoInitialRead,
    BOOL            NewContext);

static
LONG
DisconnectFromClient(
    SOCKET          Socket, 
    PCredHandle     phCreds,
    CtxtHandle *    phContext);

static void PrintHexDump(DWORD length, PBYTE buffer);


/*****************************************************************************/
void Usage(void)
{
    printf("\n");
    printf("USAGE: webserver -u<user> [ <options> ]\n");
    printf("\n");
    printf("    -u<user>        Name of user (in existing certificate)\n");
    printf("    -U<user>        Name of user (machine store)\n");
    printf("    -p<port>        Port to listen on (default 443).\n");
    printf("    -a              Ask for client authentication.\n");
    printf("    -v              Verbose Mode.\n");
    printf("    -P<protocol>    Protocol to use\n");
    printf("                        2 = SSL 2.0\n");
    printf("                        3 = SSL 3.0\n");
    printf("                        4 = TLS 1.0\n");

    exit(1);
}

/*****************************************************************************/
BOOL
LoadSecurityLibrary(void)
{
    INIT_SECURITY_INTERFACE         pInitSecurityInterface;
    QUERY_CREDENTIALS_ATTRIBUTES_FN pQueryCredentialsAttributes;
    OSVERSIONINFO VerInfo;
    UCHAR lpszDLL[MAX_PATH];

    //
    //  Find out which security DLL to use, depending on
    //  whether we are on Win2k, NT or Win9x
    //

    VerInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    if (!GetVersionEx (&VerInfo))   
    {
        return FALSE;
    }

    if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT 
        && VerInfo.dwMajorVersion == 4)
    {
        strcpy (lpszDLL, NT4_DLL_NAME );
    }
    else if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ||
          VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT )
    {
        strcpy (lpszDLL, DLL_NAME );
    }
    else
    {
        return FALSE;
    }

    //
    //  Load Security DLL
    //

    g_hSecurity = LoadLibrary(lpszDLL);
    if(g_hSecurity == NULL)
    {
        printf("Error 0x%x loading %s.\n", GetLastError(), lpszDLL);
        return FALSE;
    }

    pInitSecurityInterface = (INIT_SECURITY_INTERFACE)GetProcAddress(
                                    g_hSecurity,
                                    "InitSecurityInterfaceA");
    
    if(pInitSecurityInterface == NULL)
    {
        printf("Error 0x%x reading InitSecurityInterface entry point.\n", 
               GetLastError());
        return FALSE;
    }

    g_pSSPI = pInitSecurityInterface();

    if(g_pSSPI == NULL)
    {
        printf("Error 0x%x reading security interface.\n",
               GetLastError());
        return FALSE;
    }

    return TRUE;
}

/*****************************************************************************/
void
UnloadSecurityLibrary(void)
{
    FreeLibrary(g_hSecurity);
    g_hSecurity = NULL;
}


/*****************************************************************************/
void _cdecl main(int argc, char *argv[])
{
    WSADATA WsaData;
    CredHandle hServerCreds;

    INT i;
    INT iOption;
    PCHAR pszOption;

    //
    // Parse the command line.
    //

    if(argc <= 1)
    {
        Usage();
    }

    for(i = 1; i < argc; i++) 
    {
        if(argv[i][0] == '/') argv[i][0] = '-';

        if(argv[i][0] != '-') 
        {
            printf("**** Invalid argument \"%s\"\n", argv[i]);
            Usage();
        }

        iOption = argv[i][1];
        pszOption = &argv[i][2];

        switch(iOption) 
        {
        case 'p':
            iPortNumber = atoi(pszOption);
            break;

        case 'v':
            fVerbose = TRUE;
            break;

        case 'u':
            pszUserName = pszOption;
            fMachineStore = FALSE;
            break;

        case 'U':
            pszUserName = pszOption;
            fMachineStore = TRUE;
            break;

        case 'a':
            fClientAuth = TRUE;
            break;

        case 'P':
            switch(atoi(pszOption))
            {
                case 2:
                    dwProtocol = SP_PROT_SSL2;
                    break;
                case 3:
                    dwProtocol = SP_PROT_SSL3;
                    break;
                case 4:
                    dwProtocol = SP_PROT_TLS1;
                    break;
                default:
                    dwProtocol = 0;
                    break;
            }
            break;

        default:
            printf("**** Invalid option \"%s\"\n", argv[i]);
            Usage();
        }
    }

    if(!LoadSecurityLibrary())
    {
        printf("Error initializing the security library\n");
        return;
    }

    //
    // Initialize the WinSock subsystem.
    //

    if(WSAStartup(0x0101, &WsaData) == SOCKET_ERROR)
    {
        printf("Error %d returned by WSAStartup\n", GetLastError());
        exit(1);
    }

    //
    // NOTE: In theory, an application could enumerate the security packages 
    // until it finds one with attributes it likes. Some applications 
    // (such as IIS) enumerate the packages and call AcquireCredentialsHandle 
    // on each until it finds one that accepts the SCHANNEL_CRED structure. 
    // If an application has its heart set on using SSL, like this sample does, 
    // then just hardcoding the UNISP_NAME package name when calling 
    // AcquireCredentialsHandle is not a bad thing.
    //

    //
    // Create credentials.
    //

    if(CreateCredentials(pszUserName, &hServerCreds))
    {
        printf("Error creating credentials\n");
        exit(1);
    }


    WebServer(&hServerCreds);

    // Free SSPI credentials handle.
    g_pSSPI->FreeCredentialsHandle(&hServerCreds);

    // Shutdown WinSock subsystem.
    WSACleanup();

    // Close "MY" certificate store.
    if(hMyCertStore)
    {
        CertCloseStore(hMyCertStore, 0);
    }


    exit(0);
}

/*****************************************************************************/
static 
void
DisplayCertChain(
    PCCERT_CONTEXT pServerCert)
{
    CHAR szName[1000];
    PCCERT_CONTEXT pCurrentCert;
    PCCERT_CONTEXT pIssuerCert;
    DWORD dwVerificationFlags;

    printf("\n");

    // display leaf name
    if(!CertNameToStr(pServerCert->dwCertEncodingType,
                      &pServerCert->pCertInfo->Subject,
                      CERT_X500_NAME_STR | CERT_NAME_STR_NO_PLUS_FLAG,
                      szName, sizeof(szName)))
    {
        printf("**** Error 0x%x building subject name\n", GetLastError());
    }
    printf("Client subject: %s\n", szName);
    if(!CertNameToStr(pServerCert->dwCertEncodingType,
                      &pServerCert->pCertInfo->Issuer,
                      CERT_X500_NAME_STR | CERT_NAME_STR_NO_PLUS_FLAG,
                      szName, sizeof(szName)))
    {
        printf("**** Error 0x%x building issuer name\n", GetLastError());
    }
    printf("Client issuer: %s\n\n", szName);

    // display certificate chain
    pCurrentCert = pServerCert;
    while(pCurrentCert != NULL)
    {
        dwVerificationFlags = 0;
        pIssuerCert = CertGetIssuerCertificateFromStore(pServerCert->hCertStore,
                                                        pCurrentCert,
                                                        NULL,
                                                        &dwVerificationFlags);
        if(pIssuerCert == NULL)
        {
            if(pCurrentCert != pServerCert)
            {
                CertFreeCertificateContext(pCurrentCert);
            }
            break;
        }

        if(!CertNameToStr(pIssuerCert->dwCertEncodingType,
                          &pIssuerCert->pCertInfo->Subject,
                          CERT_X500_NAME_STR | CERT_NAME_STR_NO_PLUS_FLAG,
                          szName, sizeof(szName)))
        {
            printf("**** Error 0x%x building subject name\n", GetLastError());
        }
        printf("CA subject: %s\n", szName);
        if(!CertNameToStr(pIssuerCert->dwCertEncodingType,
                          &pIssuerCert->pCertInfo->Issuer,
                          CERT_X500_NAME_STR | CERT_NAME_STR_NO_PLUS_FLAG,
                          szName, sizeof(szName)))
        {
            printf("**** Error 0x%x building issuer name\n", GetLastError());
        }
        printf("CA issuer: %s\n\n", szName);

        if(pCurrentCert != pServerCert)
        {
            CertFreeCertificateContext(pCurrentCert);
        }
        pCurrentCert = pIssuerCert;
        pIssuerCert = NULL;
    }
}


/*****************************************************************************/
static
void
DisplayWinVerifyTrustError(DWORD Status)
{
    LPSTR pszName = NULL;

    switch(Status)
    {
    case CERT_E_EXPIRED:                pszName = "CERT_E_EXPIRED";                 break;
    case CERT_E_VALIDITYPERIODNESTING:  pszName = "CERT_E_VALIDITYPERIODNESTING";   break;
    case CERT_E_ROLE:                   pszName = "CERT_E_ROLE";                    break;
    case CERT_E_PATHLENCONST:           pszName = "CERT_E_PATHLENCONST";            break;
    case CERT_E_CRITICAL:               pszName = "CERT_E_CRITICAL";                break;
    case CERT_E_PURPOSE:                pszName = "CERT_E_PURPOSE";                 break;
    case CERT_E_ISSUERCHAINING:         pszName = "CERT_E_ISSUERCHAINING";          break;
    case CERT_E_MALFORMED:              pszName = "CERT_E_MALFORMED";               break;
    case CERT_E_UNTRUSTEDROOT:          pszName = "CERT_E_UNTRUSTEDROOT";           break;
    case CERT_E_CHAINING:               pszName = "CERT_E_CHAINING";                break;
    case TRUST_E_FAIL:                  pszName = "TRUST_E_FAIL";                   break;
    case CERT_E_REVOKED:                pszName = "CERT_E_REVOKED";                 break;
    case CERT_E_UNTRUSTEDTESTROOT:      pszName = "CERT_E_UNTRUSTEDTESTROOT";       break;
    case CERT_E_REVOCATION_FAILURE:     pszName = "CERT_E_REVOCATION_FAILURE";      break;
    case CERT_E_CN_NO_MATCH:            pszName = "CERT_E_CN_NO_MATCH";             break;
    case CERT_E_WRONG_USAGE:            pszName = "CERT_E_WRONG_USAGE";             break;
    default:                            pszName = "(unknown)";                      break;
    }

    printf("Error 0x%x (%s) returned by CertVerifyCertificateChainPolicy!\n", 
        Status, pszName);
}

/*****************************************************************************/
static 
DWORD
VerifyClientCertificate(
    PCCERT_CONTEXT  pServerCert,
    DWORD           dwCertFlags)
{
    HTTPSPolicyCallbackData  polHttps;
    CERT_CHAIN_POLICY_PARA   PolicyPara;
    CERT_CHAIN_POLICY_STATUS PolicyStatus;
    CERT_CHAIN_PARA          ChainPara;
    PCCERT_CHAIN_CONTEXT     pChainContext = NULL;
    LPSTR                    pszUsage;

    DWORD   Status;

    if(pServerCert == NULL)
    {
        return SEC_E_WRONG_PRINCIPAL;
    }


    //
    // Build certificate chain.
    //

    pszUsage = szOID_PKIX_KP_CLIENT_AUTH;

    ZeroMemory(&ChainPara, sizeof(ChainPara));
    ChainPara.cbSize = sizeof(ChainPara);
    ChainPara.RequestedUsage.dwType = USAGE_MATCH_TYPE_OR;
    ChainPara.RequestedUsage.Usage.cUsageIdentifier     = 1;
    ChainPara.RequestedUsage.Usage.rgpszUsageIdentifier = &pszUsage;

    if(!CertGetCertificateChain(
                            NULL,
                            pServerCert,
                            NULL,
                            pServerCert->hCertStore,
                            &ChainPara,
                            0,
                            NULL,
                            &pChainContext))
    {
        Status = GetLastError();
        printf("Error 0x%x returned by CertGetCertificateChain!\n", Status);
        goto cleanup;
    }


    //
    // Validate certificate chain.
    // 

    ZeroMemory(&polHttps, sizeof(HTTPSPolicyCallbackData));
    polHttps.cbStruct           = sizeof(HTTPSPolicyCallbackData);
    polHttps.dwAuthType         = AUTHTYPE_CLIENT;
    polHttps.fdwChecks          = dwCertFlags;
    polHttps.pwszServerName     = NULL;

    memset(&PolicyPara, 0, sizeof(PolicyPara));
    PolicyPara.cbSize            = sizeof(PolicyPara);
    PolicyPara.pvExtraPolicyPara = &polHttps;

    memset(&PolicyStatus, 0, sizeof(PolicyStatus));
    PolicyStatus.cbSize = sizeof(PolicyStatus);

    if(!CertVerifyCertificateChainPolicy(
                            CERT_CHAIN_POLICY_SSL,
                            pChainContext,
                            &PolicyPara,
                            &PolicyStatus))
    {
        Status = GetLastError();
        printf("Error 0x%x returned by CertVerifyCertificateChainPolicy!\n", Status);
        goto cleanup;
    }

    if(PolicyStatus.dwError)
    {
        Status = PolicyStatus.dwError;
        DisplayWinVerifyTrustError(Status); 
        goto cleanup;
    }


    Status = SEC_E_OK;

cleanup:

    if(pChainContext)
    {
        CertFreeCertificateChain(pChainContext);
    }

    return Status;
}

/*****************************************************************************/
static void
WebServer(CredHandle *phServerCreds)
{
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET Socket = INVALID_SOCKET;
    SOCKADDR_IN address;
    SOCKADDR_IN remoteAddress;
    INT remoteSockaddrLength;
    DWORD cConnections = 0;
    INT err;
    INT i;

    CHAR objectName[256];
    DWORD currentDirectoryLength;
    HANDLE objectHandle = INVALID_HANDLE_VALUE;
    BY_HANDLE_FILE_INFORMATION fileInfo;
    INT bytesSent;
    DWORD bytesRead;
    DWORD cbContentLength;

    CtxtHandle      hContext;
    BOOL            fContextInitialized = FALSE;
    SecBufferDesc   Message;
    SecBuffer       Buffers[4];
    SecBufferDesc   MessageOut;
    SecBuffer       OutBuffers[4];
    SecPkgContext_StreamSizes Sizes;
    SECURITY_STATUS scRet;
    PCCERT_CONTEXT pRemoteCertContext = NULL;

    HANDLE hUserToken = NULL;
    BOOL fImpersonating = FALSE;

    //
    // Initialize security buffer structs
    //

    Message.ulVersion = SECBUFFER_VERSION;
    Message.cBuffers = 4;
    Message.pBuffers = Buffers;

    Buffers[0].BufferType = SECBUFFER_EMPTY;
    Buffers[1].BufferType = SECBUFFER_EMPTY;
    Buffers[2].BufferType = SECBUFFER_EMPTY;
    Buffers[3].BufferType = SECBUFFER_EMPTY;

    MessageOut.ulVersion = SECBUFFER_VERSION;
    MessageOut.cBuffers = 4;
    MessageOut.pBuffers = OutBuffers;

    OutBuffers[0].BufferType = SECBUFFER_EMPTY;
    OutBuffers[1].BufferType = SECBUFFER_EMPTY;
    OutBuffers[2].BufferType = SECBUFFER_EMPTY;
    OutBuffers[3].BufferType = SECBUFFER_EMPTY;



    //
    // Figure out our current directory so that we can open files
    // relative to it.
    //

    currentDirectoryLength = GetCurrentDirectory( 256, objectName );
    if ( currentDirectoryLength == 0 )
    {
        printf( "GetCurrentDirectory failed: %ld\n", GetLastError( ) );
        exit(1);
    }


    //
    // Set up a socket listening on the HTTPS port.
    //

    ListenSocket = socket( AF_INET, SOCK_STREAM, 0 );
    if ( ListenSocket == INVALID_SOCKET )
    {
        printf( "socket() failed for ListenSocket: %ld\n", GetLastError( ) );
        exit(1);
    }

    RtlZeroMemory( &address, sizeof(address) );
    address.sin_family = AF_INET;
    address.sin_port = htons( (short)iPortNumber );    // https port
    address.sin_addr.s_addr = 0;

    err = bind(ListenSocket, (PSOCKADDR) &address, sizeof(address));
    if (err == SOCKET_ERROR)
    {
        printf("bind failed: %ld\n", GetLastError());
        exit(1);
    }

    err = listen(ListenSocket, 1);
    if (err == SOCKET_ERROR)
    {
        printf("listen failed: %ld\n", GetLastError());
        exit(1);
    }


    //
    // Loop processing connections.
    //

    while (TRUE)
    {
        PSecBuffer pDataBuffer;

        fContextInitialized = FALSE;

        objectHandle = INVALID_HANDLE_VALUE;

        //
        // First accept an incoming connection.
        //

        printf("\nWaiting for connection %d\n", ++cConnections);

        remoteSockaddrLength = sizeof(remoteAddress);

        Socket = accept(ListenSocket,
                        (LPSOCKADDR)&remoteAddress,
                        &remoteSockaddrLength);
        if(Socket == INVALID_SOCKET)
        {
            printf( "accept() failed: %ld\n", GetLastError( ) );
            goto cleanup;
        }

        printf("Socket connection established\n");


        // 
        // Perform handshake
        //

        cbIoBuffer = 0;

        if(!SSPINegotiateLoop(Socket,
                          &hContext,
                          phServerCreds,
                          fClientAuth,
                          TRUE,
                          TRUE))
        {
            printf("Couldn't connect\n");
            goto cleanup;
        }

        fContextInitialized = TRUE;

        if(fClientAuth)
        {
            //
            // We requested client authentication. There are two ways
            // to go here. 
            //
            
            // 
            // Some server applications will want to validate
            // the client certificate themselves, in which case they
            // should read the client certificate using QueryContextAttributes
            // and validate it, etc.
            //

            // Read the client certificate.
            scRet = g_pSSPI->QueryContextAttributes(&hContext,
                                            SECPKG_ATTR_REMOTE_CERT_CONTEXT,
                                            (PVOID)&pRemoteCertContext);
            if(scRet != SEC_E_OK)
            {
                printf("Error 0x%lx querying client certificate\n", scRet);
            }
            else
            {
                // Display client certificate chain.
                DisplayCertChain(pRemoteCertContext);

                // Attempt to validate client certificate.
                scRet = VerifyClientCertificate(pRemoteCertContext, 0);
                if(scRet)
                {
                    printf("Error 0x%lx authenticating client credentials\n", scRet);
                    goto cleanup;
                }
                else
                    printf("\nAuth succeeded, ready for command\n");

            }

            //
            // Many server applications want to validate the client user,
            // but they don't want to get involved with validating the client
            // certificate themselves. This is really easy to do, since schannel's
            // certificate mapper code will automatically map the client 
            // certificate to a user account whenever possible. If this 
            // technique is used, then the code above can be removed, since
            // if a valid user token is obtained, then the server application
            // is guaranteed that the client certificate validated correctly.
            // This approach allows the server application to access ACL'ed
            // files on the behalf of the client user, which is really cool.
            // Note that this only works on Win2K, WinXP, and later versions
            // of Windows. 
            //

            fImpersonating = FALSE;

            scRet = g_pSSPI->QuerySecurityContextToken(&hContext, 
                                                       &hUserToken);
            if(SUCCEEDED(scRet))
            {
                if(ImpersonateLoggedOnUser(hUserToken))
                {
                    // We're impersonating the client user. Too cool.
                    printf("Impersonating client\n");
                    fImpersonating = TRUE;
                }
            }
        }


        //
        // Find out how big the header will be:
        //

        scRet = g_pSSPI->QueryContextAttributes(&hContext, SECPKG_ATTR_STREAM_SIZES, &Sizes);


        if(scRet != SEC_E_OK)
        {
            printf("Couldn't get Sizes\n");
            goto cleanup;
        }


        //
        // Receive the HTTP request from the client.  Note the
        // assumption that the client will send the request all in one
        // chunk.
        //

        do
        {
            Buffers[0].pvBuffer = IoBuffer;
            Buffers[0].cbBuffer = cbIoBuffer;
            Buffers[0].BufferType = SECBUFFER_DATA;

            Buffers[1].BufferType = SECBUFFER_EMPTY;
            Buffers[2].BufferType = SECBUFFER_EMPTY;
            Buffers[3].BufferType = SECBUFFER_EMPTY;

            scRet = g_pSSPI->DecryptMessage(&hContext, &Message, 0, NULL);

            if(scRet == SEC_E_INCOMPLETE_MESSAGE)
            {
                err = recv(Socket, IoBuffer + cbIoBuffer, IO_BUFFER_SIZE - cbIoBuffer, 0);
                if ((err == SOCKET_ERROR) || (err == 0))
                {
                    printf("recv failed: %ld\n", GetLastError());
                    goto cleanup;
                }

                printf("\nReceived %d (request) bytes from client\n", err);
                if(fVerbose)
                {
                    PrintHexDump(err, IoBuffer+cbIoBuffer);
                }
                else
                {
                    PrintHexDump(16, IoBuffer+cbIoBuffer);
                }

                cbIoBuffer += err;
            }
        }
        while(scRet == SEC_E_INCOMPLETE_MESSAGE);

        if(scRet == SEC_I_CONTEXT_EXPIRED)
        {
            // Client signalled end of session
            goto cleanup;
        }
        
        if(scRet != SEC_E_OK)
        {
            printf("Couldn't decrypt, error %lx\n", scRet);
            goto cleanup;
        }
        cbIoBuffer = 0;

        // Locate data buffer.
        pDataBuffer  = NULL;
        for(i = 1; i < 4; i++)
        {
            if(Buffers[i].BufferType == SECBUFFER_DATA)
            {
                pDataBuffer = &Buffers[i];
                break;
            }
        }
        if(pDataBuffer == NULL)
        {
            goto cleanup;
        }

        // Make sure the data in the output buffer is zero-terminated
        // and print it out.
        ((CHAR *) pDataBuffer->pvBuffer)[pDataBuffer->cbBuffer] = '\0';
        printf("\nMessage is: '%s'\n", pDataBuffer->pvBuffer);


        // Parse the request in order to determine the requested object.
        // Note that we only handle the GET verb in this server.

        if(!ParseRequest(
                        pDataBuffer->pvBuffer,
                        pDataBuffer->cbBuffer,
                        objectName+currentDirectoryLength,
                        &cbContentLength))
        {
            printf("Unable to parse message\n");
            goto cleanup;
        }



        objectHandle = CreateFileA(
                           objectName,
                           GENERIC_READ,
                           FILE_SHARE_READ,
                           NULL,
                           OPEN_EXISTING,
                           0,
                           NULL);
        if (objectHandle == INVALID_HANDLE_VALUE)
        {
            printf("CreateFile(%s) failed: %ld\n", objectName, GetLastError());
            goto cleanup;
        }

        // Determine the length of the file.

        if(!GetFileInformationByHandle(objectHandle, &fileInfo))
        {
            printf("GetFileInformationByHandle failed: %ld\n", GetLastError());
            goto cleanup;
        }

        //
        // Build and the HTTP response header.
        //

        ZeroMemory(IoBuffer, Sizes.cbHeader);

        i = sprintf(
            IoBuffer + Sizes.cbHeader,
            "HTTP/1.0 200 OK\r\nContent-Length: %d\r\n\r\n",
            fileInfo.nFileSizeLow);

        //
        // Line up the buffers so that the header and content will be
        // all set to go.
        //

        Buffers[0].pvBuffer = IoBuffer;
        Buffers[0].cbBuffer = Sizes.cbHeader;
        Buffers[0].BufferType = SECBUFFER_STREAM_HEADER;

        Buffers[1].pvBuffer = IoBuffer + Sizes.cbHeader;
        Buffers[1].cbBuffer = i;
        Buffers[1].BufferType = SECBUFFER_DATA;

        Buffers[2].pvBuffer = IoBuffer + Sizes.cbHeader + i;
        Buffers[2].cbBuffer = Sizes.cbTrailer;
        Buffers[2].BufferType = SECBUFFER_STREAM_TRAILER;

        Buffers[3].BufferType = SECBUFFER_EMPTY;

        scRet = g_pSSPI->EncryptMessage(&hContext, 0, &Message, 0);

        if ( FAILED( scRet ) )
        {
            printf(" EncryptMessage failed with %#x\n", scRet );
            goto cleanup;
        }


        err = send( Socket,
                    IoBuffer,
                    Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer,
                    0 );

        printf("\nSend %d header bytes to client\n", Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer);
        if(fVerbose > 1)
        {
            PrintHexDump(Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer, IoBuffer);
        }
        else
        {
            PrintHexDump(16, IoBuffer);
        }
        if ( err == SOCKET_ERROR )
        {
            printf( "send failed: %ld\n", GetLastError( ) );
            goto cleanup;
        }

        //
        // Now read and send the file data.
        //

        for(bytesSent = 0;
            bytesSent < (INT) fileInfo.nFileSizeLow;
            bytesSent += err)
        {

            if(!ReadFile(objectHandle,
                          IoBuffer + Sizes.cbHeader,
                          IO_BUFFER_SIZE - (Sizes.cbHeader + Sizes.cbTrailer),
                          &bytesRead,
                          NULL))
            {
                printf( "ReadFile failed: %ld\n", GetLastError( ) );
                break;
            }

            if(bytesRead == 0)
            {
                printf( "zero bytes read\n");
                break;
            }


            Buffers[0].pvBuffer = IoBuffer;
            Buffers[0].cbBuffer = Sizes.cbHeader;
            Buffers[0].BufferType = SECBUFFER_STREAM_HEADER;

            Buffers[1].pvBuffer = IoBuffer + Sizes.cbHeader;
            Buffers[1].cbBuffer = bytesRead;
            Buffers[1].BufferType = SECBUFFER_DATA;

            Buffers[2].pvBuffer = IoBuffer + Sizes.cbHeader + bytesRead;
            Buffers[2].cbBuffer = Sizes.cbTrailer;
            Buffers[2].BufferType = SECBUFFER_STREAM_TRAILER;

            Buffers[3].BufferType = SECBUFFER_EMPTY;

            scRet = g_pSSPI->EncryptMessage(&hContext,
                                0,
                                &Message,
                                0);

            if ( FAILED( scRet ) )
            {
                printf(" EncryptMessage failed with %#x\n", scRet );
                goto cleanup;
            }

            err = send( Socket,
                        IoBuffer,
                        Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer,
                        0 );

            printf("\nSend %d data bytes to client\n", Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer);
            if(fVerbose > 1)
            {
                PrintHexDump(Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer, IoBuffer);
            }
            else
            {
                PrintHexDump(16, IoBuffer);
            }

            if ( err == SOCKET_ERROR )
            {
                printf( "send failed: %ld\n", GetLastError( ) );
                break;
            }
        }

cleanup:

        if(fImpersonating)
        {
            RevertToSelf();
            fImpersonating = FALSE;
        }

        if(hUserToken)
        {
            CloseHandle(hUserToken);
            hUserToken = NULL;
        }

        if(fContextInitialized)
        {
            scRet = DisconnectFromClient(Socket, phServerCreds, &hContext);

            if(scRet == SEC_E_OK)
            {
                fContextInitialized = FALSE;
                Socket = INVALID_SOCKET;
            }
            else
            {
                printf("Error disconnecting from server\n");
            }
        }

        if(objectHandle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(objectHandle);
        }

        // Free SSPI context handle.
        if(fContextInitialized)
        {
            g_pSSPI->DeleteSecurityContext(&hContext);
            fContextInitialized = FALSE;
        }

        // Close socket.
        if(Socket != INVALID_SOCKET)
        {
            closesocket(Socket);
            Socket = INVALID_SOCKET;
        }
    }

} // WebServer


static
BOOL
SSPINegotiateLoop(
    SOCKET          Socket,
    PCtxtHandle     phContext,
    PCredHandle     phCred,
    BOOL            fClientAuth,
    BOOL            fDoInitialRead,
    BOOL            NewContext)
{
    TimeStamp            tsExpiry;
    SECURITY_STATUS      scRet;
    SecBufferDesc        InBuffer;
    SecBufferDesc        OutBuffer;
    SecBuffer            InBuffers[2];
    SecBuffer            OutBuffers[1];
    DWORD                err = 0;

    BOOL                 fDoRead;
    BOOL                 fInitContext = NewContext;

    DWORD                dwSSPIFlags, dwSSPIOutFlags;

    fDoRead = fDoInitialRead;

    dwSSPIFlags =   ASC_REQ_SEQUENCE_DETECT        |
                    ASC_REQ_REPLAY_DETECT      |
                    ASC_REQ_CONFIDENTIALITY  |
                    ASC_REQ_EXTENDED_ERROR    |
                    ASC_REQ_ALLOCATE_MEMORY  |
                    ASC_REQ_STREAM;

    if(fClientAuth)
    {
        dwSSPIFlags |= ASC_REQ_MUTUAL_AUTH;
    }


    //
    //  set OutBuffer for InitializeSecurityContext call
    //

    OutBuffer.cBuffers = 1;
    OutBuffer.pBuffers = OutBuffers;
    OutBuffer.ulVersion = SECBUFFER_VERSION;


    scRet = SEC_I_CONTINUE_NEEDED;

    while( scRet == SEC_I_CONTINUE_NEEDED ||
            scRet == SEC_E_INCOMPLETE_MESSAGE ||
            scRet == SEC_I_INCOMPLETE_CREDENTIALS) 
    {

        if(0 == cbIoBuffer || scRet == SEC_E_INCOMPLETE_MESSAGE)
        {
            if(fDoRead)
            {
                err = recv(Socket, IoBuffer+cbIoBuffer, IO_BUFFER_SIZE, 0);

                if (err == SOCKET_ERROR || err == 0)
                {
                    printf(" recv failed: %d\n", GetLastError() );
                    return FALSE;
                }
                else
                {
                    printf("\nReceived %d (handshake) bytes from client\n", err);
                    if(fVerbose)
                    {
                        PrintHexDump(err, IoBuffer+cbIoBuffer);
                    }
                    else
                    {
                        PrintHexDump(min(16, err), IoBuffer+cbIoBuffer);
                    }

                    cbIoBuffer += err;
                }
            }
            else
            {
                fDoRead = TRUE;
            }
        }





        //
        // InBuffers[1] is for getting extra data that
        //  SSPI/SCHANNEL doesn't proccess on this
        //  run around the loop.
        //

        InBuffers[0].pvBuffer = IoBuffer;
        InBuffers[0].cbBuffer = cbIoBuffer;
        InBuffers[0].BufferType = SECBUFFER_TOKEN;

        InBuffers[1].pvBuffer   = NULL;
        InBuffers[1].cbBuffer   = 0;
        InBuffers[1].BufferType = SECBUFFER_EMPTY;

        InBuffer.cBuffers        = 2;
        InBuffer.pBuffers        = InBuffers;
        InBuffer.ulVersion       = SECBUFFER_VERSION;


        //
        // Initialize these so if we fail, pvBuffer contains NULL,
        // so we don't try to free random garbage at the quit
        //

        OutBuffers[0].pvBuffer   = NULL;
        OutBuffers[0].BufferType = SECBUFFER_TOKEN;
        OutBuffers[0].cbBuffer   = 0;


        scRet = g_pSSPI->AcceptSecurityContext(
                        phCred,
                        (fInitContext?NULL:phContext),
                        &InBuffer,
                        dwSSPIFlags,
                        SECURITY_NATIVE_DREP,
                        (fInitContext?phContext:NULL),
                        &OutBuffer,
                        &dwSSPIOutFlags,
                        &tsExpiry);



        fInitContext = FALSE;


        if ( scRet == SEC_E_OK ||
             scRet == SEC_I_CONTINUE_NEEDED ||
             (FAILED(scRet) && (0 != (dwSSPIOutFlags & ISC_RET_EXTENDED_ERROR))))
        {
            if  (OutBuffers[0].cbBuffer != 0    &&
                 OutBuffers[0].pvBuffer != NULL )
            {
                //
                // Send response to server if there is one
                //
                err = send( Socket,
                            OutBuffers[0].pvBuffer,
                            OutBuffers[0].cbBuffer,
                            0 );

                printf("\nSend %d handshake bytes to client\n", OutBuffers[0].cbBuffer);
                if(fVerbose)
                {
                    PrintHexDump(OutBuffers[0].cbBuffer, OutBuffers[0].pvBuffer);
                }
                else
                {
                    PrintHexDump(16, OutBuffers[0].pvBuffer);
                }

                g_pSSPI->FreeContextBuffer( OutBuffers[0].pvBuffer );
                OutBuffers[0].pvBuffer = NULL;
            }
        }


        if ( scRet == SEC_E_OK )
        {


            if ( InBuffers[1].BufferType == SECBUFFER_EXTRA )
            {

                    memcpy(IoBuffer,
                           (LPBYTE) (IoBuffer + (cbIoBuffer - InBuffers[1].cbBuffer)),
                            InBuffers[1].cbBuffer);
                    cbIoBuffer = InBuffers[1].cbBuffer;
            }
            else
            {
                cbIoBuffer = 0;
            }

            if(fClientAuth)
            {
                // Display info about cert...


            }

            return TRUE;
        }
        else if (FAILED(scRet) && (scRet != SEC_E_INCOMPLETE_MESSAGE))
        {

            printf("Accept Security Context Failed with error code %lx\n", scRet);
            return FALSE;

        }



        if ( scRet != SEC_E_INCOMPLETE_MESSAGE &&
             scRet != SEC_I_INCOMPLETE_CREDENTIALS)
        {


            if ( InBuffers[1].BufferType == SECBUFFER_EXTRA )
            {



                memcpy(IoBuffer,
                       (LPBYTE) (IoBuffer + (cbIoBuffer - InBuffers[1].cbBuffer)),
                        InBuffers[1].cbBuffer);
                cbIoBuffer = InBuffers[1].cbBuffer;
            }
            else
            {
                //
                // prepare for next receive
                //

                cbIoBuffer = 0;
            }
        }
    }

    return FALSE;
}



static
BOOL
ParseRequest (
    IN PCHAR InputBuffer,
    IN INT InputBufferLength,
    OUT PCHAR ObjectName,
    OUT DWORD *pcbContentLength)
{
    PCHAR s = InputBuffer;
    DWORD i;

    *pcbContentLength = 0;

    while ( (INT)(s - InputBuffer) < InputBufferLength )
    {

        // Parse off verb

        //
        // First determine whether this line starts with the GET
        // verb.
        //

        while(*s != '\0' && *s != ' ' && *s != '\t')
        {
            *s = (CHAR)toupper(*s);
            s++;
        }

        if(*s == '\0' || *s == ' ' || *s == '\0')
        {
            *s = '\0';
//            printf("Verb is :%s\n", InputBuffer);

            //
            // It is a GET.  Skip over white space.
            //
            for ( s++; *s == ' ' || *s == '\t'; s++ );

            //
            // Now grab the object name.
            //

            for ( i = 0; *s != 0xA && *s != 0xD && *s != ' ' && *s != '\0'; s++, i++ ) {
                ObjectName[i] = *s;
                if ( ObjectName[i] == '/' ) {
                    ObjectName[i] = '\\';
                }
            }

            ObjectName[i] = '\0';

            //
            // We're done parsing.
            //

            if(strcmp(ObjectName, "\\") == 0)
            {
                strcpy(ObjectName, "\\default.html");
            }
            if(strcmp(InputBuffer, "POST") == 0)
            {
                char * content_length;
                DWORD cbContent = 0;
                // look for content length;
                content_length = strstr(s, "Content-Length: ");
                if(content_length)
                {
                    cbContent = atoi(content_length+16);
                    printf("Content Length is %d\n", cbContent);
                    *pcbContentLength = cbContent;
                }
            }
            return TRUE;
        }

        //
        // Skip to the end of the line and continue parsing.
        //

        while ( *s != 0xA && *s != 0xD )
        {
            s++;
        }

        s++;

        if ( *s == 0xD || *s == 0xA )
        {
            s++;
        }
    }

    return FALSE;

} // ParseRequest



/*****************************************************************************/
static
DWORD
CreateCredentials(
    LPSTR pszUserName,              // in
    PCredHandle phCreds)            // out
{
    SCHANNEL_CRED   SchannelCred;
    TimeStamp       tsExpiry;
    SECURITY_STATUS Status;
    PCCERT_CONTEXT  pCertContext = NULL;

    if(pszUserName == NULL || strlen(pszUserName) == 0)
    {
        printf("**** No user name specified!\n");
        return SEC_E_NO_CREDENTIALS;
    }

    // Open the "MY" certificate store.
    if(hMyCertStore == NULL)
    {
        if(fMachineStore)
        {
            hMyCertStore = CertOpenStore(CERT_STORE_PROV_SYSTEM,
                                         X509_ASN_ENCODING,
                                         0,
                                         CERT_SYSTEM_STORE_LOCAL_MACHINE,
                                         L"MY");
        }
        else
        {
            hMyCertStore = CertOpenSystemStore(0, "MY");
        }

        if(!hMyCertStore)
        {
            printf("**** Error 0x%x returned by CertOpenSystemStore\n", 
                GetLastError());
            return SEC_E_NO_CREDENTIALS;
        }
    }

    // Find certificate. Note that this sample just searchs for a 
    // certificate that contains the user name somewhere in the subject name.
    // A real application should be a bit less casual.
    pCertContext = CertFindCertificateInStore(hMyCertStore, 
                                              X509_ASN_ENCODING, 
                                              0,
                                              CERT_FIND_SUBJECT_STR_A,
                                              pszUserName,
                                              NULL);
    if(pCertContext == NULL)
    {
        printf("**** Error 0x%x returned by CertFindCertificateInStore\n",
            GetLastError());
        return SEC_E_NO_CREDENTIALS;
    }


    //
    // Build Schannel credential structure. Currently, this sample only
    // specifies the protocol to be used (and optionally the certificate, 
    // of course). Real applications may wish to specify other parameters 
    // as well.
    //

    ZeroMemory(&SchannelCred, sizeof(SchannelCred));

    SchannelCred.dwVersion = SCHANNEL_CRED_VERSION;

    SchannelCred.cCreds = 1;
    SchannelCred.paCred = &pCertContext;

    SchannelCred.grbitEnabledProtocols = dwProtocol;


    //
    // Create an SSPI credential.
    //

    Status = g_pSSPI->AcquireCredentialsHandle(
                        NULL,                   // Name of principal
                        UNISP_NAME_A,           // Name of package
                        SECPKG_CRED_INBOUND,    // Flags indicating use
                        NULL,                   // Pointer to logon ID
                        &SchannelCred,          // Package specific data
                        NULL,                   // Pointer to GetKey() func
                        NULL,                   // Value to pass to GetKey()
                        phCreds,                // (out) Cred Handle
                        &tsExpiry);             // (out) Lifetime (optional)
    if(Status != SEC_E_OK)
    {
        printf("**** Error 0x%x returned by AcquireCredentialsHandle\n", Status);
        return Status;
    }


    //
    // Free the certificate context. Schannel has already made its own copy.
    //

    if(pCertContext)
    {
        CertFreeCertificateContext(pCertContext);
    }


    return SEC_E_OK;
}

/*****************************************************************************/
static
LONG
DisconnectFromClient(
    SOCKET          Socket, 
    PCredHandle     phCreds,
    CtxtHandle *    phContext)
{
    DWORD           dwType;
    PBYTE           pbMessage;
    DWORD           cbMessage;
    DWORD           cbData;

    SecBufferDesc   OutBuffer;
    SecBuffer       OutBuffers[1];
    DWORD           dwSSPIFlags;
    DWORD           dwSSPIOutFlags;
    TimeStamp       tsExpiry;
    DWORD           Status;

    //
    // Notify schannel that we are about to close the connection.
    //

    dwType = SCHANNEL_SHUTDOWN;

    OutBuffers[0].pvBuffer   = &dwType;
    OutBuffers[0].BufferType = SECBUFFER_TOKEN;
    OutBuffers[0].cbBuffer   = sizeof(dwType);

    OutBuffer.cBuffers  = 1;
    OutBuffer.pBuffers  = OutBuffers;
    OutBuffer.ulVersion = SECBUFFER_VERSION;

    Status = g_pSSPI->ApplyControlToken(phContext, &OutBuffer);

    if(FAILED(Status)) 
    {
        printf("**** Error 0x%x returned by ApplyControlToken\n", Status);
        goto cleanup;
    }

    //
    // Build an SSL close notify message.
    //

    dwSSPIFlags =   ASC_REQ_SEQUENCE_DETECT     |
                    ASC_REQ_REPLAY_DETECT       |
                    ASC_REQ_CONFIDENTIALITY     |
                    ASC_REQ_EXTENDED_ERROR      |
                    ASC_REQ_ALLOCATE_MEMORY     |
                    ASC_REQ_STREAM;

    OutBuffers[0].pvBuffer   = NULL;
    OutBuffers[0].BufferType = SECBUFFER_TOKEN;
    OutBuffers[0].cbBuffer   = 0;

    OutBuffer.cBuffers  = 1;
    OutBuffer.pBuffers  = OutBuffers;
    OutBuffer.ulVersion = SECBUFFER_VERSION;

    Status = g_pSSPI->AcceptSecurityContext(
                    phCreds,
                    phContext,
                    NULL,
                    dwSSPIFlags,
                    SECURITY_NATIVE_DREP,
                    NULL,
                    &OutBuffer,
                    &dwSSPIOutFlags,
                    &tsExpiry);

    if(FAILED(Status)) 
    {
        printf("**** Error 0x%x returned by AcceptSecurityContext\n", Status);
        goto cleanup;
    }

    pbMessage = OutBuffers[0].pvBuffer;
    cbMessage = OutBuffers[0].cbBuffer;


    //
    // Send the close notify message to the client.
    //

    if(pbMessage != NULL && cbMessage != 0)
    {
        cbData = send(Socket, pbMessage, cbMessage, 0);
        if(cbData == SOCKET_ERROR || cbData == 0)
        {
            Status = WSAGetLastError();
            printf("**** Error %d sending close notify\n", Status);
            goto cleanup;
        }

        printf("\n%d bytes of handshake data sent\n", cbData);

        if(fVerbose)
        {
            PrintHexDump(cbData, pbMessage);
        }
        else
        {
            PrintHexDump(min(16, cbData), pbMessage);
        }

        // Free output buffer.
        g_pSSPI->FreeContextBuffer(pbMessage);
    }
    

cleanup:

    // Free the security context.
    g_pSSPI->DeleteSecurityContext(phContext);

    // Close the socket.
    closesocket(Socket);

    return Status;
}

/*****************************************************************************/
static void 
PrintHexDump(DWORD length, PBYTE buffer)
{
    DWORD i,count,index;
    CHAR rgbDigits[]="0123456789abcdef";
    CHAR rgbLine[100];
    char cbLine;

    for(index = 0; length; length -= count, buffer += count, index += count) 
    {
        count = (length > 16) ? 16:length;

        sprintf(rgbLine, "%4.4x  ",index);
        cbLine = 6;

        for(i=0;i<count;i++) 
        {
            rgbLine[cbLine++] = rgbDigits[buffer[i] >> 4];
            rgbLine[cbLine++] = rgbDigits[buffer[i] & 0x0f];
            if(i == 7) 
            {
                rgbLine[cbLine++] = ':';
            } 
            else 
            {
                rgbLine[cbLine++] = ' ';
            }
        }
        for(; i < 16; i++) 
        {
            rgbLine[cbLine++] = ' ';
            rgbLine[cbLine++] = ' ';
            rgbLine[cbLine++] = ' ';
        }

        rgbLine[cbLine++] = ' ';

        for(i = 0; i < count; i++) 
        {
            if(buffer[i] < 32 || buffer[i] > 126 || buffer[i] == '%') 
            {
                rgbLine[cbLine++] = '.';
            } 
            else 
            {
                rgbLine[cbLine++] = buffer[i];
            }
        }

        rgbLine[cbLine++] = 0;
        printf("%s\n", rgbLine);
    }
}

