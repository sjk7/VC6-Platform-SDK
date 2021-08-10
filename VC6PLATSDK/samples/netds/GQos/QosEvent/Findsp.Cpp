// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998 - 2000  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      findsp.cpp
//
// Abstract:
//      Implement functionality to find/select a Winsock Service Provider based
//      on selected options.
//
// Entry Points:
//      FindServiceProvider - find a service provider
//
// Author:
//      barry r. butterklee

#include "qosevent.h"

// Abstract:
//      Look for a service provider.  If QoS has been requested, then look for  
//      a QoS-enabled IP service provider.  Return TRUE only if a service 
//      provider is found that matches all the criteria. Also, if QoS was not 
//      requested do not pick a QoS-enabled service provider (even though that
//      should NOT matter).
//
//      Notice that actual service provider names are different on NT and Win9x 
//      when searching for a service provider, you should not use the service 
//      provider name, but instead use the various flags in the protocol 
//      structure.
//
BOOL FindServiceProvider(
    int                 iProtocol,
    BOOL                bQos,
    BOOL                bMulticast,
    WSAPROTOCOL_INFO    *pProtocolInfo
    )
{
    int nRet;
    WSAPROTOCOL_INFO *lpProtocolBuf = NULL;
    DWORD dwBufLen = 0;
    DWORD dwErr;
    BOOL bProtocolFound = FALSE;
    BOOL bSPQos = FALSE, bSPMulticast=FALSE;
    BOOL bQosMatch = FALSE, bMulticastMatch = FALSE;

    // first have WSAEnumProtocols tell us how big a buffer is needed
    nRet = WSAEnumProtocols(NULL, NULL, &dwBufLen);
    if (SOCKET_ERROR != nRet)
    {
        printf("WSAEnumProtocols: should not have suceeded\n");
        goto end;
    }

    if (WSAENOBUFS != (dwErr = WSAGetLastError()))
    {
        // WSAEnumProtocols failed for some reason not relating to buffer size 
        printf("WSAEnumProtocols(1): %d\n", dwErr);
        goto end;
    }

    // WSAEnumProtocols failed for the "expected" reason, allocate a buffer
    // of the needed size
    lpProtocolBuf = (WSAPROTOCOL_INFO *)malloc(dwBufLen);
    if (!lpProtocolBuf)
    {
        printf("malloc failed in FindServiceProvider\n");
        goto end;
    }

    // now we can call WSAEnumProtocols again with the expectation it will
    // succeed because we have allocated a big enough buffer.
    nRet = WSAEnumProtocols(NULL, lpProtocolBuf, &dwBufLen);
    if (SOCKET_ERROR == nRet)
    {
        printf("WSAEnumProtocols(3): %d\n", WSAGetLastError());
        goto end;
    }

    // loop thru protocols, looking for a matching service provider 
    {
    for (int i=0; i<nRet; i++)
    {
        printf("  sp <%s>\n", lpProtocolBuf[i].szProtocol);
        
        // do we have the correct protocol?
        if (AF_INET != lpProtocolBuf[i].iAddressFamily 
                || iProtocol != lpProtocolBuf[i].iProtocol)
            continue; // nope, move on
                
        // Check for Qos and Multicast
        bSPQos = 
            ((XP1_QOS_SUPPORTED & lpProtocolBuf[i].dwServiceFlags1) != 0);
        bSPMulticast =
            ((XP1_SUPPORT_MULTIPOINT & lpProtocolBuf[i].dwServiceFlags1) != 0);

        // Look to see if we got exactly what we wanted
        if ((bQos == bSPQos) && (bMulticast == bSPMulticast))
        {
            
            memcpy(pProtocolInfo, (void *) &lpProtocolBuf[i], 
                    sizeof(WSAPROTOCOL_INFO));
            bProtocolFound = TRUE;
            break;
        } 
    } // for    
    } // scope resolution for int i on stricter compilers
    

end:
    if (lpProtocolBuf)
        free(lpProtocolBuf);
    
    if (bProtocolFound)
        printf("  Using service provider <%s>\n\n", pProtocolInfo->szProtocol);

    return(bProtocolFound);
}

