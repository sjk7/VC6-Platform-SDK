// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998 - 2000  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      getqos.cpp
//
// Abstract:    
//      This file contains the functionality needed to retrieve a 
//      QOS structure. 
//
// Entry Points:
//      GetQos
//
// Author:
//      Barry R. Butterklee

#include "qosevent.h"



// Abstract
//      Use WSAIoctl(SIO_GET_QOS) to retrieve a QOS structure queued up in the 
//      QOSSP.  We potentially call WSAIoctl twice, the first time to retrieve 
//      the size of the entire QOS buffer we need to allocate in order to
//      hold all the supplied QOS, RSVP, and POLICY objects.  Only Win2k and above 
//      currently supports querying the QOSSP for the needed buffer size, on Win98 
//      we  must supply a "large" buffer or risk not being able to retrieve all the
//      objects.
//
BOOL GetQos(
    SOCKET  sd,
    BOOL    bQueryBufferSize,
    QOS     **pQos
    )
{
    DWORD   dwBytesReturned=0;
    DWORD   status;
    DWORD   dwBufferLen;
    CHAR    *pBuf;
    QOS     *pTempQos;

    // Figure out what size buffer we need.
    if (!bQueryBufferSize)
        dwBufferLen = 2048; //win98 platform
    else
    {
        // Try to get it dynamically.
        dwBufferLen = 0;
        status = WSAIoctl(sd, SIO_GET_QOS, NULL, 0,
                			&dwBufferLen, sizeof(dwBufferLen), 
                			&dwBytesReturned, NULL, NULL);

        // we have an error, anything except
        if (SOCKET_ERROR == status)
        {
            DWORD dwErr = WSAGetLastError();

            if (WSAEWOULDBLOCK == dwErr)
                return(FALSE); 	// nothing to do

            if (WSAENOBUFS != dwErr)
            {
                // some sort of error not related to passing a large enough buffer
                printf("GetQos: WSAIoctl(SIO_GET_QOS) - query: %d\n", dwErr);
                return(FALSE);
            }
        }
    }

    // for Windows 98 dwBufferLen has been set statically, for Windows 2000 we queried the OS 
    // for the proper buffer size
    printf("GetQos: dwBufferlen for pQos = %d\n", dwBufferLen);
    pBuf = (CHAR *)malloc(dwBufferLen);
    if (!pBuf)
    {
        printf("GetQos: malloc: %d\n", GetLastError());
        return(FALSE);
    }

    // Windows 98 workaround - not needed for Win2000, but doesn't hurt.  Windows 98
    // needs the provider specific buffer to point to valid memory, whereas Windows 2000
    // simply needs a contiguous block of memory.  Therefore we allocate a contiguous
    // block of memory cast it to a QOS structure and then set the provider specific
    // buffer pointer to just beyond the QOS structure proper.  Windows 98 needs this
    // whereas Windows 2000 ignores this.  Windows 98 should not care, because this
    // is strictly an output buffer, Windows 2000 corrects this problem.
    pTempQos = (QOS *)pBuf;
    pTempQos->ProviderSpecific.buf = pBuf + sizeof(QOS);
    pTempQos->ProviderSpecific.len = dwBufferLen - sizeof(QOS);
    // end Windows 98 workaround

    // Make the real call
    status = WSAIoctl(sd, SIO_GET_QOS, NULL, 0,
                            pBuf, dwBufferLen, &dwBytesReturned,
                            NULL, NULL);

    if (SOCKET_ERROR == status)
    {
        DWORD dwErr = WSAGetLastError();
        if (WSAEWOULDBLOCK != dwErr)
            printf("GetQos(2): WSAIoctl(SIO_GET_QOS) %d\n", dwErr);

        free(pBuf);
        return(FALSE);
    }

    // True means we need to free this memory later.
    *pQos = pTempQos;
    return(TRUE);
}




