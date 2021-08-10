// --------------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation.  All rights reserved
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --------------------------------------------------------------------
//
// file:  drctencp.cpp
//
//




#include <windows.h>
#include <wincrypt.h>
#include <STDIO.H>
#include <mq.h>


//
// Globals.
//

BOOL   fEnhEncrypted = FALSE ;
QMPROPID propidPK = PROPID_QM_ENCRYPTION_PK;
WCHAR  wszMachineName[ 128 ] = {0} ;




void Usage(char * pszProgramName)
{
    fprintf(stderr, "...Usage:  %s\n", pszProgramName);
    fprintf(stderr, "\t-2 send encrypted, RC2\n") ;
    fprintf(stderr, "\t-4 send encrypted, RC4\n") ;
    fprintf(stderr, "\t-b <Message Body>\n") ;
    fprintf(stderr, "\t-e Enhanced Encryption\n") ;
    fprintf(stderr, "\t-l <Message Label>\n") ;
    fprintf(stderr, "\t-m <Name of destination machine>\n") ;
    fprintf(stderr, "\t-q <Queue name>\n") ;
    exit(1);
}

BOOL getPublicKeyBlob( PBYTE* pbPbKeyxKey, DWORD* pdwPbKeyxKeyLen)
/*++
  
Routine Description:    
    
    This routine retrieves the public key of the remote computer.
    The key is retrieved using the MQGetMachineProperties() API, which connects to the
    directory service (DS) to retrieve the specified properties.
    Usually when using workgroup (direct) mode, no DS connection is available.
    This routine comes only as a substitute to other means of obtaining the
    remote computer public key. (SSL protocol, via disk or file, etc.) .

Arguments:

    pbPbKeyxKey     - (OUT) pointer to the key.
    pdwPbKeyxKeyLen - (OUT) pointer to the key length 

Return Value:

    TRUE  - if the key was retreived .
    FALSE - if the key couldn't be reteived.

--*/
{
    if (fEnhEncrypted)
    {
        propidPK = PROPID_QM_ENCRYPTION_PK_ENHANCED ;
    }

    QMPROPID aQmPropId[1] ;
    aQmPropId[0] = propidPK ;
    #define QMPROPS (sizeof(aQmPropId) / sizeof(*aQmPropId))

    MQPROPVARIANT aQmPropVar[QMPROPS];
    HRESULT       aQmStatus[QMPROPS];

    MQQMPROPS QmProps = {QMPROPS, aQmPropId, aQmPropVar, aQmStatus};

    aQmPropVar[0].vt = VT_NULL;

    HRESULT hr = MQGetMachineProperties(wszMachineName, NULL, &QmProps);
    if (FAILED(hr))
    {
        printf(
           "The public key of %S could not be retrieved. Error code: %lxh\n",
                                                  wszMachineName, hr);

        return FALSE;
    }

    if (aQmPropVar[0].vt != (VT_UI1|VT_VECTOR))
    {
        printf(
        "A type indicator in the structure passed to MQGetMachineProperties() is incorrect. Type idicator: %lxh, QMPROPS: %lut, Error code: %lxh\n",
                                                 aQmPropVar[0].vt, QMPROPS, hr) ;
        return FALSE ;
    }

    *pbPbKeyxKey = aQmPropVar[0].caub.pElems;
    *pdwPbKeyxKeyLen = aQmPropVar[0].caub.cElems;

    return TRUE;
}


int main(int argc, char *argv[])
{
       
    DWORD  dwEncryptAlg = CALG_RC2 ;
    WCHAR  wszQueueName[ 128 ] = {0} ;
    WCHAR  wszMsgLabel[ 128 ] = {TEXT("MessageLabel")} ;
    WCHAR  wszMsgBody[ 128 ] = {TEXT("MessageBody")} ;
    LPSTR  lpszArg = NULL ;
    DWORD  dwMsgSize = sizeof(WCHAR) * (1 + wcslen(wszMsgBody)) ;
    DWORD  dwBufferSize = sizeof(wszMsgBody) ;
    LPWSTR pMsgBody = wszMsgBody ;
	BOOL bQueueName = FALSE, bMachineName = FALSE;

	if (argc < 2)
	{
		Usage(argv[0]);
	}
    //
    // Allow the user to override settings with command line switches.
    //
    for ( int i = 1; i < argc; i++)
    {
        if ((*argv[i] == '-') || (*argv[i] == '/'))
        {
			if(strlen(argv[i]) <2)
			{
				Usage(argv[0]);
			}
            switch (*(argv[i]+1))
            {
            case '2':
                dwEncryptAlg = CALG_RC2 ;
                break ;

            case '4':
                dwEncryptAlg = CALG_RC4 ;
                break ;

            case 'e':
                fEnhEncrypted = TRUE ;
                break ;

            case 'b':
				if(i+1 == argc)
				{
					Usage(argv[0]);
				}

                lpszArg = argv[++i];
                mbstowcs(wszMsgBody, lpszArg, 127) ;
                break;

            case 'l':
				if(i+1 == argc)
				{
					Usage(argv[0]);
				}
                lpszArg = argv[++i];
                mbstowcs(wszMsgLabel, lpszArg, 127) ;
                break;

            case 'm':
 				if(i+1 == argc)
				{
					Usage(argv[0]);
				}
				lpszArg = argv[++i];
                mbstowcs(wszMachineName, lpszArg, 127) ;
                bMachineName = TRUE;
				break;

            case 'q':
 				if(i+1 == argc)
				{
					Usage(argv[0]);
				}
				lpszArg = argv[++i];
                mbstowcs(wszQueueName, lpszArg, 127) ;
				bQueueName = TRUE;
                break;

            case 'h':
            case '?':
            default:
                Usage(argv[0]);
            }
        }
        else
        {
            Usage(argv[0]);
        }
    }

	if(!bMachineName || !bQueueName)
	{
		Usage(argv[0]);
	}

    dwMsgSize = sizeof(WCHAR) * (1 + wcslen(wszMsgBody)) ;

    //
    // Get the public key blob of the destination computer.
    //

    PBYTE pbPbKeyxKey = NULL;
    DWORD dwPbKeyxKeyLen = 0;

    if (getPublicKeyBlob( &pbPbKeyxKey, &dwPbKeyxKeyLen))
    {
        printf("The public key of %S was retrieved successfully. Length: %lut\n",
                                     wszMachineName, dwPbKeyxKeyLen) ;

    }
    else
    {
        return -1 ;
    }

    //
    // Get a handle to the default cryptographic service provider (CSP).
    //
    LPWSTR lpwszProviderName = MS_DEF_PROV ;
    if (fEnhEncrypted)
    {
        lpwszProviderName = MS_ENHANCED_PROV ;
    }
    HCRYPTPROV hProv = NULL;

    BOOL bRet = CryptAcquireContext( &hProv,
                                       NULL,
                                       lpwszProviderName,
                                       PROV_RSA_FULL,
                                       0 ) ;
    if (!bRet)
    {
        if (GetLastError() == NTE_BAD_KEYSET)
        {
            //
            // The default key container does not exist yet, so create it.
            //
            if (!CryptAcquireContext( &hProv,
                                        NULL,
                                        lpwszProviderName,
                                        PROV_RSA_FULL,
                                        CRYPT_NEWKEYSET ))
            {
                printf(
                "CryptAcquireContext(%S, CRYPT_NEWKEYSET) failed. Error code: %lxh\n",
                                     lpwszProviderName, GetLastError());
                return -1;
            }
            printf("CryptAcquireContext(%S, CRYPT_NEWKEYSET) succeeded.\n",
                                                       lpwszProviderName) ;
        }
        else
        {
            printf(
              "CryptAcquireContext(%S) failed. Error code: %lxh\n",
                                     lpwszProviderName, GetLastError());
            return -1;
        }
    }
    else
    {
        printf("CryptAcquireContext(%S) succeeded.\n", lpwszProviderName) ;
    }

    //
    // Import the public key blob of the destination computer into the CSP.
    //
    HCRYPTKEY hPbKey = NULL;

    if (!CryptImportKey( hProv,
                         pbPbKeyxKey,
                         dwPbKeyxKeyLen,
                         NULL,
                         0,
                        &hPbKey ))
    {
        printf("CryptImportKey() failed. Error code: %lxh\n", GetLastError());
        return -1;
    }
    printf("CryptImportKey() succeeded.\n") ;

    //
    // Free the public key blob of the destination computer.
    //
    MQFreeMemory(pbPbKeyxKey);

    //
    // Create a symmetric key.
    //                   
    HCRYPTKEY hSymmKey = NULL;

    if (!CryptGenKey(hProv, dwEncryptAlg, CRYPT_EXPORTABLE, &hSymmKey))
    {
        printf("CryptGenKey() failed. Error code: %lxh\n", GetLastError());
        return -1;
    }
    printf("CryptGenKey(alg- %lut) successfully created a symmetric key.\n",
                                                           dwEncryptAlg) ;
    //
    // Get the encrypted symmetric key blob. This blob should
    // be passed to MQSendMessage in PROPID_M_DEST_SYMM_KEY.
    //
    BYTE  abSymmKey[ 512 ];
    DWORD dwSymmKeyLen = sizeof(abSymmKey);

    if (!CryptExportKey( hSymmKey,
                         hPbKey,
                         SIMPLEBLOB,
                         0,
                         abSymmKey,
                         &dwSymmKeyLen ))
    {
        printf("CryptExportKey() failed. Error code: %lxh\n", GetLastError());
        return -1;
    }
    printf("CryptExportKey() succeeded.\n") ;

    //
    // Get a handle to the destination queue.
    //
    WCHAR wszQueueFormat[128] = {0};

	if (_snwprintf(wszQueueFormat, (sizeof(wszQueueFormat)/sizeof(wszQueueFormat[0])) - 1, TEXT("DIRECT=OS:%s\\%s"),
                                        wszMachineName, wszQueueName) <0)
	{
		printf("The format name is too long for the buffer specified. Exiting...\n");
		exit(1);
	}
	else
	{
		wszQueueFormat[(sizeof(wszQueueFormat)/sizeof(wszQueueFormat[0]))-1] = '\0';
	}




    QUEUEHANDLE hQueue = NULL;

    HRESULT hr = MQOpenQueue(wszQueueFormat, MQ_SEND_ACCESS, 0, &hQueue);
    if (FAILED(hr))
    {
        printf("MQOpenQueue(%S) failed. Error code: %lxh\n", wszQueueFormat, hr) ;
        return -1;
    }
    printf("MQOpenQueue(%S) succeeded.\n", wszQueueFormat) ;

    //
    // Prepare the message properties.
    //
	GUID guid ;

    MSGPROPID aMsgPropId[] = {PROPID_M_BODY,
                              PROPID_M_DEST_SYMM_KEY,
                              PROPID_M_ENCRYPTION_ALG,
                              PROPID_M_CONNECTOR_TYPE,
                              PROPID_M_LABEL,
                              PROPID_M_PRIV_LEVEL};
    #define MSGPROPS (sizeof(aMsgPropId) / sizeof(*aMsgPropId))

    MQPROPVARIANT aMsgPropVar[MSGPROPS];
    HRESULT       aMsgStatus[MSGPROPS];

    MQMSGPROPS MsgProps = {MSGPROPS, aMsgPropId, aMsgPropVar, aMsgStatus};

    aMsgPropVar[0].vt = VT_VECTOR | VT_UI1;
    aMsgPropVar[0].caub.pElems = (BYTE*) pMsgBody ;

    aMsgPropVar[1].vt = VT_VECTOR | VT_UI1;
    aMsgPropVar[1].caub.cElems = dwSymmKeyLen;
    aMsgPropVar[1].caub.pElems = abSymmKey;

    aMsgPropVar[2].vt = VT_UI4;
    aMsgPropVar[2].ulVal = dwEncryptAlg ;

    aMsgPropVar[3].vt = VT_CLSID;
	aMsgPropVar[3].puuid = &guid;

    aMsgPropVar[4].vt = VT_LPWSTR;
    aMsgPropVar[4].pwszVal = wszMsgLabel;

    //
    // The connector type (PROPID_M_CONNECTOR_TYPE) is not initialized
    // because it is assumed that nobody will bother about it on the
    // receiving side; otherwise, it should be initialized.
    //

    //
    // Encrypt the line.
    //

    if (!CryptEncrypt( hSymmKey,
                       NULL,
                       TRUE,
                       0,
                       (BYTE*) pMsgBody,
                      &dwMsgSize,
                       dwBufferSize ))
    {
        printf("CryptEncrypt() failed. Error code: %lxh\n", GetLastError());
        return -1;
    }
    printf("CryptEncrypt() succeeded.\n") ;

    //
    // Update the length of the message according to the result of the
    // encryption algorithm. RC4 may enlarge the message size. At the
    // destination, the message will be received as clear text with the
    // correct (original) message body size.
    //
    aMsgPropVar[0].caub.cElems = dwMsgSize ;
   
    aMsgPropVar[5].vt = VT_UI4;
    if(!fEnhEncrypted)
    {
        aMsgPropVar[5].ulVal= MQMSG_PRIV_LEVEL_NONE ;
    }
    else
    {
        aMsgPropVar[5].ulVal = MQMSG_PRIV_LEVEL_BODY_ENHANCED ;
    }
    MsgProps.cProp = MSGPROPS ;


    //
    // Send the mesasge.
    //
    hr = MQSendMessage(hQueue, &MsgProps, NULL);
    if (FAILED(hr))
    {
        printf("MQSendMessage() failed. Error code: %lxh\n", hr) ;
		return -1;
    }	
    printf("MQSendMessage() succeeded.\n") ;

    //
    // Free resources. This is actually not required here. The code is included
    // to show how it is done, if neccessary.
    //
    MQCloseQueue(hQueue);
    CryptDestroyKey(hSymmKey);
    CryptDestroyKey(hPbKey);
    CryptReleaseContext(hProv, 0);

    return 0;
}
