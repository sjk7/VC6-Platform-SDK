// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998 - 2000  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      chkqos.cpp
//
// Abstract:    
//      This file contains the functionality needed to determine whether or
//      not data transfers can start on a QOS socket prior to receipt of
//      an RSVP RESV message.
//
// Entry Points: 
//      ChkQosSend - This function fills in a QOS structure
//
// Author:
//      Barry R. Butterklee

#include "qosevent.h"

// Abstract:
//      Determine when to start sending data.  If not using QOS then start
//      we should start sending data right away.  If we are requesting QOS then
//      we should first see if traffic control is sufficent to handle the data
//      transmission until we get a RESV.  
//
//      Also note that the socket must be a QOS socket before we can use this 
//      ioctl, otherwise we would get WSAEINVAL. 
//
//      Also note that on Win98, where this ioctl is not supported, WSAIoctl 
//      also returns WSAENINVAL.  
//
BOOL ChkQosSend(
    SOCKET  sd
    )
{
    int     nRet;
    DWORD   dwBytes;
    DWORD   inbuf = ALLOWED_TO_SEND_DATA;
    DWORD   outbuf;
   	OSVERSIONINFO   verInfo = {0};

    // first check for windows 98, and silently fail if it is.
    verInfo.dwOSVersionInfoSize = sizeof(verInfo);
	GetVersionEx(&verInfo);
	if (VER_PLATFORM_WIN32_NT != verInfo.dwPlatformId)
	    return(TRUE);

    nRet = WSAIoctl(sd, SIO_CHK_QOS, 
                        (LPVOID)&inbuf, sizeof(inbuf),
                        (LPVOID)&outbuf, sizeof(outbuf),
                        &dwBytes, NULL, NULL);

    if (SOCKET_ERROR == nRet)
    {
        printf("WSAIoctl:SIO_CHK_QOS %d\n", WSAGetLastError());
        return(FALSE);
    } 

    return((BOOL)outbuf);
}

