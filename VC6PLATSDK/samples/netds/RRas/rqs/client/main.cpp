//+--------------------------------------------------------------------------
//
//      File:       main.cpp
//
//      Synopsis:   Main file for ras quarantine removal utility (client)
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#define MBCS
#include "rasutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ras.h>
#include <raserror.h>

//
//  Define the Ras Version 4.01 RASCONN struct
//
#ifdef _WIN64
#include <pshpack4.h>
#endif

#define RASCONN_V401_A struct tagRASCONN_V401_A
RASCONN_V401_A
{
    DWORD    dwSize;
    HRASCONN hrasconn;
    CHAR     szEntryName[ RAS_MaxEntryName + 1 ];
    CHAR     szDeviceType[ RAS_MaxDeviceType + 1 ];
    CHAR     szDeviceName[ RAS_MaxDeviceName + 1 ];
    CHAR     szPhonebook [ MAX_PATH ];
    DWORD    dwSubEntry;
};

#ifdef _WIN64
#include <poppack.h>
#endif

//+--------------------------------------------------------------------------
//
// Synopsis: Common tracing api. 
//
//+--------------------------------------------------------------------------
VOID 
RqcTrace(
    IN LPSTR pszTrace, 
    IN ...) 
{
    va_list arglist;
    CHAR szTemp[256];

    szTemp[0] = 0;

    va_start(arglist, pszTrace);
    _vsnprintf(szTemp, sizeof(szTemp)/sizeof(szTemp[0]) - 1, pszTrace, arglist);
    va_end(arglist);

    szTemp[255] = '\0'; // make sure to NULL terminate as _vsnprintf doesn't guarantee that

    OutputDebugString(szTemp);
    OutputDebugString(TEXT("\n"));
}

//+--------------------------------------------------------------------------
//
// Synopsis: Get the Client IP Address and the Server IP Address for the
//           specified connection. 
//
//+--------------------------------------------------------------------------
BOOL IsNT4OrBetter()
{
    OSVERSIONINFO oviVersion;
    BOOL bReturn = FALSE;

    ZeroMemory(&oviVersion,sizeof(oviVersion));
    oviVersion.dwOSVersionInfoSize = sizeof(oviVersion);

    if (GetVersionEx(&oviVersion))
    {
        if ((oviVersion.dwPlatformId == VER_PLATFORM_WIN32_NT) && 
            (oviVersion.dwMajorVersion >= 4))
        {
            bReturn = TRUE;
        }
    }

    return bReturn;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Find the given connection name in the list of RASCONN structs
//
//+--------------------------------------------------------------------------
HRASCONN FindConnectionByName (LPRASCONNA pRasConn, DWORD dwCount, LPTSTR pszConnection)
{
    HRASCONN hConnection = NULL;

    if (pRasConn && pszConnection)
    {
        for (DWORD dwIndex = 0; dwIndex < dwCount; dwIndex++)
        {
            //
            //  Increment the array index manually since we could have a v4.0 RASCONNA
            //  struct or a v4.1 RASCONNA struct.
            //
            LPRASCONNA pTmpRasConn = (LPRASCONNA)((BYTE*)pRasConn + (pRasConn->dwSize)*dwIndex);

            if (0 == lstrcmpi(pszConnection, pTmpRasConn->szEntryName))
            {
                //
                //  We have one complication though...  On certain platforms both
                //  parts of a double dial CM connection (dialup part and tunnel part)
                //  have the same name.  We can tell the difference by looking at the
                //  phonebook parameter.  If it has _CMPhone as the phonebook file name
                //  then we know it is actually the dialup part of the double dial connection.
                //
                if (IsNT4OrBetter())
                {
                    TCHAR szFileName[_MAX_FNAME];

                    _splitpath(((RASCONN_V401_A*)pTmpRasConn)->szPhonebook, NULL, NULL, szFileName, NULL);

                    if (0 != lstrcmpi(TEXT("_cmphone"), szFileName))
                    {
                        //
                        //  Okay, we have a match
                        //
                        hConnection = pTmpRasConn->hrasconn;
                        break;                    
                    }
                }
                else
                {
                    //
                    //  Okay, we have a match
                    //
                    hConnection = pTmpRasConn->hrasconn;
                    break;                
                }
            }
        }
    }

    return hConnection;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Get the Client IP Address and the Server IP Address for the
//           specified connection. 
//
//+--------------------------------------------------------------------------
DWORD GetClientAndServerAddresses(LPTSTR pszConnectionName, LPTSTR pszTunnelConnectionName, OUT LPTSTR pszClientIpAddress, UINT cchClientIpAddress, OUT LPTSTR pszServerIpAddress, UINT cchServerIpAddress) 
{
    //
    //  Check inputs
    //
    if ((NULL == pszConnectionName) || (NULL == pszTunnelConnectionName) || (NULL == pszClientIpAddress) || (NULL == pszServerIpAddress) || (0 == cchClientIpAddress) || (0 == cchServerIpAddress))
    {
        return ERROR_INVALID_PARAMETER;
    }

    pszClientIpAddress[0] = TEXT('\0');
    pszServerIpAddress[0] = TEXT('\0');

    //
    //  First we need to call loadlibrary on RasApi32.dll and then get the function addresses for
    //  RasEnumConnections and RasGetProjectionInfo
    //
    DWORD dwRet = ERROR_SUCCESS;
    HMODULE hRasApi32 = NULL;
    LPRASCONNA pRasConn = NULL;
    typedef DWORD (WINAPI *pfnRasEnumConnectionsSpec)(LPRASCONNA, LPDWORD, LPDWORD);
    typedef DWORD (WINAPI *pfnRasGetProjectionInfoSpec)(HRASCONN, RASPROJECTION, LPVOID, LPDWORD);

    pfnRasEnumConnectionsSpec pfnRasEnumConnections = NULL;
    pfnRasGetProjectionInfoSpec pfnRasGetProjectionInfo = NULL;

    __try
    {
        hRasApi32 = LoadLibrary("rasapi32.dll");

        if (hRasApi32)
        {
            pfnRasEnumConnections = (pfnRasEnumConnectionsSpec)GetProcAddress(hRasApi32, "RasEnumConnectionsA");
            pfnRasGetProjectionInfo = (pfnRasGetProjectionInfoSpec)GetProcAddress(hRasApi32, "RasGetProjectionInfoA");

            if ((NULL == pfnRasEnumConnections) || (NULL == pfnRasGetProjectionInfo))
            {
                dwRet = ERROR_PROC_NOT_FOUND;
                __leave;
            }
        }
        else
        {
            dwRet = GetLastError();
            __leave;
        }

        //
        //  Okay, now call EnumRasConnections to get a list of active connections
        //
        DWORD dwCount = 0;
        DWORD dwSizeOfRasConn = IsNT4OrBetter() ? sizeof(RASCONN_V401_A) : sizeof(RASCONNA);
        DWORD dwSize = dwSizeOfRasConn;

        do
        {
            LocalFree(pRasConn);

            pRasConn = (RASCONNA*)LocalAlloc(LMEM_ZEROINIT, dwSize);
    
            if (pRasConn)
            {
                pRasConn->dwSize = dwSizeOfRasConn;

                dwRet = pfnRasEnumConnections(pRasConn, &dwSize, &dwCount);

                if ((ERROR_BUFFER_TOO_SMALL != dwRet) && (ERROR_SUCCESS != dwRet))
                {
                    //
                    //  RAS error, bail.
                    //
                    __leave;
                }
            }
            else
            {
                dwRet = ERROR_NOT_ENOUGH_MEMORY;
                __leave;
            }
    
        } while (ERROR_BUFFER_TOO_SMALL == dwRet);

        //
        //  Okay, so now we have a buffer of connections.  Let's look
        //  through them for a match to the passed in connection name.
        //  Figure out if we are looking for the tunnel connection name
        //  or the dialup connection name
        //
        LPTSTR pszConnection = pszTunnelConnectionName;
        HRASCONN hConnection = NULL;

        if (0 == lstrcmpi(pszTunnelConnectionName, TEXT("NULL")))
        {
            pszConnection = pszConnectionName;
        }
        //else use pszTunnelConnectionName as saved above

        hConnection = FindConnectionByName (pRasConn, dwCount, pszConnection);

        //
        //  Okay, now we have the right connection so we can call RasGetProjectionInfo to actually get the data we want
        //
        if (hConnection)
        {
            RASPROJECTION RasProj = RASP_PppIp;
            RASPPPIP RasPPPIP;
            DWORD dwBufSize = sizeof(RASPPPIP);

            ZeroMemory(&RasPPPIP, dwBufSize);
            RasPPPIP.dwSize = dwBufSize;

            dwRet = pfnRasGetProjectionInfo(hConnection, RASP_PppIp, (PVOID)&RasPPPIP, &dwBufSize);

            if (ERROR_SUCCESS == dwRet)
            {
                lstrcpyn(pszClientIpAddress, RasPPPIP.szIpAddress, cchClientIpAddress);
                lstrcpyn(pszServerIpAddress, RasPPPIP.szServerIpAddress, cchClientIpAddress);
            }
        }
        else
        {
            dwRet = ERROR_NO_CONNECTION;
            __leave;
        }

    }

    __finally
    {
        if (hRasApi32)
        {
            FreeLibrary(hRasApi32);
        }

        LocalFree(pRasConn);
    }

    if (ERROR_SUCCESS != dwRet)
    {
        RqcTrace("GetClientAndServerAddresses failed with error = %d", dwRet);
    }

    return dwRet;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Returns a properly formatted username and domain pair.  This
//           with be one of the following:
//
//           "domain\username"
//           "username"
//
//           It is the caller's responsibility to free the returned buffer.
//           Note that we also append the colon separator (:).
//
//+--------------------------------------------------------------------------
PCHAR GenerateUserName(PCHAR pszUsername, PCHAR pszDomain)
{
    BOOL bHaveUserName = pszUsername && (0 != lstrcmpi(pszUsername, "NULL"));
    BOOL bHaveDomain = pszDomain && (0 != lstrcmpi(pszDomain, "NULL"));

    //  Allocate the maximum amount of memory we will need.  Note that
    //  we add 3 extra, one for the \, one for the :, and one for the null
    //  terminator.
    //
    PCHAR pszReturn = (PCHAR)RuAlloc(3 + (bHaveDomain ? (UINT)strlen(pszDomain) : 0) + (bHaveUserName ? (UINT)strlen(pszUsername) : 0), TRUE);
    if (pszReturn)
    {
        if (bHaveUserName)
        {
            if (bHaveDomain)
            {
                // return domain + \ + username
                sprintf(pszReturn, "%s\\%s:", pszDomain, pszUsername);
            }
            else
            {
               // return dup of username
                sprintf(pszReturn, "%s:", pszUsername);
            }
        }
    }

    return pszReturn;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Prints a usage message for the command line of rqc.exe.
//                                                         
//+--------------------------------------------------------------------------
void PrintUsage(char *argv[ ])
{
    printf("\nRemote Access Quarantine Client\n");

    printf("\nUsage:\n\n");
    printf("%s <ConnName> <TunnelConnName> <Port> <Domain> <Username> <String>\n\n", argv[0]);
    printf("  ConnName:\t\tthe name of the RAS connection on this host\n");
    printf("  TunnelConnName:\tthe name of the RAS tunnel connection on this host\n");
    printf("  Port:\t\t\tthe port to send the quarantine string to\n");
    printf("  Domain:\t\tthe domain of the connecting user\n");
    printf("  Username:\t\tthe username of the connecting user\n");
    printf("  String:\t\tthe string to send\n");
    printf("\n");

    printf("%s /?\t\t\n\n  Display this help\n", argv[0]);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Main routine
//
//  Usage:  rqc <ConnectionName> <TunnelConnectionName> <port> <domain> <username> <string>          
//                                                         
//    ConnectionName:     	the name of the RAS connection on this host 
//    TunnelConnectionName:    	the name of the RAS tunnel connection on this host
//    port:      		the port to send the quarantine string
//    domain:      		the domain of the user
//    username:                 the username of the connecting user
//    string:    		the string to send
//
//  Note:  For the ConnectionName and TunnelConnectionName parameters, you will
//         only have both if doing a double dial connection (dialup connection
//         to the internet and a tunnel connection over it).  If you do not have
//         both, then the text "NULL" should be passed for the unused parameter.
//         See the GetClientAndServerAddresses function for more information
//         on how these parameters are used.
//                                                         
//+--------------------------------------------------------------------------
int 
__cdecl 
main(
    int argc, 
    char *argv[ ], 
    char *envp[ ])
{
    HRESULT hr;
    RuSocket Socket;
    ULONG ulPort;
    UINT uiStringSize, uiBufSize, uiSizeOrig;
    CHAR pszResponse[4], pszPrefix[64];
    INT iRet;

    PCHAR pszConnectionName, pszTunnelConnectionName, pszPort;
    PCHAR pszDomain, pszUsername, pszString;
    PCHAR pszUsernameAndDomain = NULL;
    CHAR szMyIp[RAS_MaxIpAddress + 1];
    CHAR szDstIp[RAS_MaxIpAddress + 1];

    //
    //  Check to see if they asked for a usage message
    //
    if ((argc == 2) && (strcmp(argv[1], "/?") == 0))
    {
        PrintUsage(argv);
        return -1;
    }

    //
    //  Make sure we got the required number of arguments
    //
    if (argc < 7)
    {
        return -1;
    }

    // Save the input params
    //
    pszConnectionName = argv[1];
    pszTunnelConnectionName = argv[2];
    pszPort = argv[3];
    pszDomain = argv[4];
    pszUsername = argv[5];
    pszString = argv[6];


    iRet = -1;

    // Get the client and server IP's
    //
    if (ERROR_SUCCESS != GetClientAndServerAddresses(pszConnectionName,
                                                     pszTunnelConnectionName,
                                                     szMyIp, 
                                                     sizeof(szMyIp)/sizeof(szMyIp[0]), 
                                                     szDstIp, 
                                                     sizeof(szDstIp)/sizeof(szDstIp[0])))
    {
        RqcTrace("GetClientAndServerAddresses failed!");
        iRet = -1;
        goto exit;        
    }

    //  Generate the username and domain string
    //
    pszUsernameAndDomain = GenerateUserName(pszUsername, pszDomain);

    if (NULL == pszUsernameAndDomain)
    {
        RqcTrace("GenerateUserName failed!");
        iRet = -1;
        goto exit;
    }

    // Calculate the sizes
    //
    uiStringSize = (UINT)strlen(pszString) + (UINT)(strlen(pszUsernameAndDomain)) + 1;

    if ((uiStringSize == 0) || (uiStringSize > 1024))
    {
        RqcTrace("Invalid string length. %d", uiStringSize);
        iRet = -1;
        goto exit;
    }
    uiBufSize = uiStringSize + 3;       // 3 = len(":1:")

    // Initialize the socket library
    //
    RqcTrace("Initializing sockets api");
    hr = RuSocket::Initialize();
    if (S_OK != hr)
    {
        RqcTrace("Unable to use sockets. %1!d!", hr);
        iRet = -1;
        goto exit;
    }

    // Covert the port over
    //
    ulPort = (UINT) atoi(pszPort);
    if ((ulPort == 0) || (ulPort == ULONG_MAX) || (ulPort > 65 * 1024))
    {
        RqcTrace("Invalid port.  %d", ulPort);
        goto exit;
    }

    // Open the socket
    //
    RqcTrace("Opening socket...");
    hr = Socket.Open(ulPort, szDstIp, szMyIp);
    if (S_OK != hr)
    {
        RqcTrace("Unable to open socket 0x%x", hr);
        iRet = 1;
        goto exit;
    }

    // Send the prefix.  Size:1:
    //
    RqcTrace("Writing prefix...");
    sprintf(pszPrefix, "%04d:1:", uiBufSize);
    uiSizeOrig = uiBufSize = (UINT)strlen(pszPrefix);
    hr = Socket.Write((BYTE*)pszPrefix, &uiBufSize);
    if ((S_OK != hr) || (uiSizeOrig != uiBufSize))
    {
        RqcTrace(
            "Can't write prefix 0x%x, %d %d", 
            hr, 
            uiBufSize, 
            uiSizeOrig);
        iRet = 1;
        goto exit;
    }

    //
    // Send the Username and Domain
    RqcTrace("Writing username...");
    uiSizeOrig = uiBufSize = (UINT)strlen(pszUsernameAndDomain);
    hr = Socket.Write((BYTE*)pszUsernameAndDomain, &uiBufSize);
    if ((S_OK != hr) || (uiSizeOrig != uiBufSize))
    {
        RqcTrace(
            "Can't write the username 0x%x, %d %d", 
            hr, 
            uiBufSize, 
            uiSizeOrig);
            
        iRet = 1;
        goto exit;
    }

    // Send the string
    //
    RqcTrace("Writing version string...");
    uiSizeOrig = uiBufSize = (UINT)strlen(pszString) + 1;
    hr = Socket.Write((BYTE*)pszString, &uiBufSize);
    if ((S_OK != hr) || (uiSizeOrig != uiBufSize))
    {
        RqcTrace(
            "Can't write string 0x%x, %d %d", 
            hr, 
            uiBufSize, 
            uiSizeOrig);
            
        iRet = 1;
        goto exit;
    }

    // Receive the response
    //
    RqcTrace("Reading response...");
    ZeroMemory(pszResponse, sizeof(pszResponse));
    uiSizeOrig = uiBufSize = sizeof(pszResponse) - 1;
    hr = Socket.Read((BYTE*)pszResponse, &uiBufSize);
    if ((S_OK != hr) || (uiSizeOrig != uiBufSize))
    {
        RqcTrace(
            "Can't read, 0x%x, %d %d", 
            hr, 
            uiBufSize, 
            uiSizeOrig);
            
        goto exit;
    }

    RqcTrace("Response: %s", pszResponse);

    if (strcmp(pszResponse, "Ok") == 0)
    {
        iRet = 0;
    }
    else if (strcmp(pszResponse, "No") == 0)
    {
        iRet = 2;
    }

exit:
    RuFree(pszUsernameAndDomain);
    RqcTrace("Closing socket...");
    Socket.Close();
    RqcTrace("Cleanup socket api...");
    RuSocket::Cleanup();

    return iRet;
}
