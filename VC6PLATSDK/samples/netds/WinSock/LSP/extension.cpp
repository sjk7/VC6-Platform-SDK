// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998  Microsoft Corporation.  All Rights Reserved.
//
// Module Name: extension.cpp
//
// Description:
//
//    This sample illustrates how to develop a layered service provider that is
//    capable of counting all bytes transmitted through a TCP/IP socket.
//
//    This file contains all of the Winsock extension functions that can
//    be monitored by a service provider. This is done by intercepting any
//    WSAIoctl calls with the SIO_GET_EXTENSION_FUNCTION_POINTER (see spi.cpp
//    and WSPIoctl for more info). We substitute our own function pointer so
//    that an application calls into us. Currently we intercept only TransmitFile
//    and AcceptEx.
//

#include "provider.h"

//
// Used to output debug messages
//
static TCHAR        Msg[512];
static ULONG_PTR    EventMask=1;

//
// Function: LoadExtensionFunction
//
// Description:
//    This function dynamically loads the given extension function from the
//    underlying provider. Each extension function checks to see if the 
//    corresponding extension function for the lower provider is loaded
//    before calling. If not, it will load it as needed. This is necessary
//    if the app loads the extension function for say TCP and then calls
//    that extension function on a UDP socket. Normally this isn't the case
//    but we're being defensive here.
//
BOOL
LoadExtensionFunction(
    FARPROC **func,
    GUID ExtensionGuid,
    LPWSPIOCTL fnIoctl,
    SOCKET  s
    )
{
    DWORD   dwBytes;
    int     rc, 
            error;

    // Use the lower provider's WSPIoctl to load the extension function
    rc = fnIoctl(
            s,
            SIO_GET_EXTENSION_FUNCTION_POINTER,
           &ExtensionGuid,
            sizeof(GUID),
            func,
            sizeof(FARPROC),
           &dwBytes,
            NULL,
            NULL,
            NULL,
           &error
            );
    if (rc == SOCKET_ERROR)
    {
        dbgprint("LoadExtensionFunction: WSAIoctl (SIO_GET_EXTENSION_FUNCTION) failed: %d",
            error);
            
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

//
// Function: ExtTransmitFile
//
// Description:
//    This is our provider's TransmitFile function. When an app calls WSAIoctl
//    to request the function pointer to TransmitFile, we intercept the call
//    and return a pointer to our extension function instead.
//
BOOL PASCAL FAR ExtTransmitFile (
    IN SOCKET hSocket,
    IN HANDLE hFile,
    IN DWORD nNumberOfBytesToWrite,
    IN DWORD nNumberOfBytesPerSend,
    IN LPOVERLAPPED lpOverlapped,
    IN LPTRANSMIT_FILE_BUFFERS lpTransmitBuffers,
    IN DWORD dwFlags)
{
	SOCK_INFO          *SocketContext;
	LPWSAOVERLAPPEDPLUS ProviderOverlapped;
	int                 Errno,
                        ret;

    // Get the context
    SocketContext = FindAndLockSocketContext(hSocket, &Errno);
    if (SocketContext == NULL)
    {
        dbgprint("ExtTransmitFile: WPUQuerySocketHandleContext() failed: %d", Errno);
        WSASetLastError(Errno);
		return FALSE;
    }

    // Make sure we already have the extension function
    if (!SocketContext->Provider->NextProcTableExt.lpfnTransmitFile)
    {
        GUID    guidTransmitFile = WSAID_TRANSMITFILE;

        if (LoadExtensionFunction(
                (FARPROC **)&SocketContext->Provider->NextProcTableExt.lpfnTransmitFile,
                guidTransmitFile,
                SocketContext->Provider->NextProcTable.lpWSPIoctl,
                SocketContext->ProviderSocket
                ) == FALSE)
        {
            UnlockSocketContext(SocketContext, &Errno);
            dbgprint("Next proc table TransmitFile == NULL!");
            WSASetLastError(WSAEFAULT);
            return FALSE;
        }   
    }

	// Check for overlapped I/O
	
	if (lpOverlapped)
	{
		ProviderOverlapped = GetOverlappedStructure(SocketContext);
        if (!ProviderOverlapped)
        {
            UnlockSocketContext(SocketContext, &Errno);
            dbgprint("ExtTransmitFile: GetOverlappedStructure() returned NULL!");
            WSASetLastError(WSAENOBUFS);
            return FALSE;
        }
        // Verify the event is valid
        __try {
            if ( lpOverlapped->hEvent != NULL )
            {
                ret = ResetEvent((HANDLE)((ULONG_PTR)lpOverlapped->hEvent & ~EventMask));
                if (ret == 0)
                {
                    // Return to original state and indicate error
                    (SocketContext->dwOutstandingAsync)--;
                    UnlockSocketContext(SocketContext, &Errno);
                    PutbackOverlappedStructure(ProviderOverlapped);
                    WSASetLastError(ERROR_INVALID_HANDLE);
                    return FALSE;
                }
            }
            CopyOffset(&ProviderOverlapped->ProviderOverlapped, lpOverlapped);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            // Return to original state and indicate error
            (SocketContext->dwOutstandingAsync)--;
            UnlockSocketContext(SocketContext, &Errno);
            PutbackOverlappedStructure(ProviderOverlapped);
            WSASetLastError(WSAEFAULT);
            return FALSE;
        }
        //
        // Save off the arguments and setup the overlapped structure
        //
        ProviderOverlapped->lpCallerOverlapped = lpOverlapped;
        ProviderOverlapped->SockInfo           = SocketContext;
        ProviderOverlapped->CallerSocket       = hSocket;
        ProviderOverlapped->ProviderSocket     = SocketContext->ProviderSocket;
        ProviderOverlapped->Error              = NO_ERROR;
        ProviderOverlapped->Operation          = LSP_OP_TRANSMITFILE;
        ProviderOverlapped->lpCallerCompletionRoutine              = NULL;
        ProviderOverlapped->TransmitFileArgs.hFile                 = hFile;
        ProviderOverlapped->TransmitFileArgs.nNumberOfBytesToWrite = nNumberOfBytesToWrite;
        ProviderOverlapped->TransmitFileArgs.nNumberOfBytesPerSend = nNumberOfBytesPerSend;
        ProviderOverlapped->TransmitFileArgs.lpTransmitBuffers     = lpTransmitBuffers;
        ProviderOverlapped->TransmitFileArgs.dwFlags               = dwFlags;
        ProviderOverlapped->Provider = SocketContext->Provider;

        ret = QueueOverlappedOperation(ProviderOverlapped, SocketContext);

        if (ret != NO_ERROR)
        {
            WSASetLastError(ret);
            ret = FALSE;
        }
        else
        {
            ret = TRUE;
        }
	}
	else
	{
		ret = SocketContext->Provider->NextProcTableExt.lpfnTransmitFile(
			SocketContext->ProviderSocket,
			hFile,
			nNumberOfBytesToWrite,
			nNumberOfBytesPerSend,
			NULL,
			lpTransmitBuffers,
			dwFlags);
	}

    UnlockSocketContext(SocketContext, &Errno);

    return ret;
}

//
// Function: ExtAcceptEx
//
// Description:
//    This is our provider's AcceptEx function. When an app calls WSAIoctl
//    to request the function pointer to AcceptEx, we intercept the call
//    and return a pointer to our extension function instead.
//
BOOL PASCAL FAR ExtAcceptEx(
	IN SOCKET sListenSocket,
	IN SOCKET sAcceptSocket,
	IN PVOID lpOutputBuffer,
	IN DWORD dwReceiveDataLength,
	IN DWORD dwLocalAddressLength,
	IN DWORD dwRemoteAddressLength,
	OUT LPDWORD lpdwBytesReceived,
	IN LPOVERLAPPED lpOverlapped)
{
	LPWSAOVERLAPPEDPLUS ProviderOverlapped;
	SOCK_INFO          *ListenSocketContext=NULL,
	                   *AcceptSocketContext=NULL;
	int                 Errno,
                        ret;


    //
    // Query the socket context for the listening socket
    //
    ListenSocketContext = FindAndLockSocketContext(sListenSocket, &Errno);
    if (ListenSocketContext == NULL)
    {
        dbgprint("AcceptExExt: WPUQuerySocketHandleContext "
                  "on listen socket failed: %d", Errno);
        Errno = WSAENOTSOCK;
        WSASetLastError(Errno);
		return FALSE;
    }
    //
    // Also need to query the socket context for the accept socket
    //
    AcceptSocketContext = FindAndLockSocketContext(sAcceptSocket, &Errno);
    if (AcceptSocketContext == NULL)
    {
        UnlockSocketContext(ListenSocketContext, &Errno);

        dbgprint("AcceptExExt: WPUQuerySocketHandleContext "
                  "on accept socket failed: %d", Errno);
        Errno = WSAENOTSOCK;
        WSASetLastError(Errno);
		return FALSE;
    }

    if (!ListenSocketContext->Provider->NextProcTableExt.lpfnAcceptEx)
    {
        GUID    guidAcceptEx = WSAID_ACCEPTEX;

        if (LoadExtensionFunction(
                (FARPROC **)&ListenSocketContext->Provider->NextProcTableExt.lpfnAcceptEx,
                guidAcceptEx,
                ListenSocketContext->Provider->NextProcTable.lpWSPIoctl,
                ListenSocketContext->ProviderSocket
                ) == FALSE)
        {
            UnlockSocketContext(ListenSocketContext, &Errno);
            UnlockSocketContext(AcceptSocketContext, &Errno);

            dbgprint("Lower provider AcceptEx == NULL!");
            WSASetLastError(WSAEFAULT);
            return FALSE;
        }
    }

	// Check for overlapped I/O

	if (lpOverlapped)
	{
		ProviderOverlapped = GetOverlappedStructure(ListenSocketContext);
        if (!ProviderOverlapped)
        {
            UnlockSocketContext(ListenSocketContext, &Errno);
            UnlockSocketContext(AcceptSocketContext, &Errno);

            dbgprint("ExtAcceptEx: GetOverlappedStructre() returne NULL!");
            WSASetLastError(WSAENOBUFS);
            return FALSE;
        }

        // Verify the event is valid
        __try {
            if ( lpOverlapped->hEvent != NULL )
            {
                ret = ResetEvent((HANDLE)((ULONG_PTR)lpOverlapped->hEvent & ~EventMask));
                if (ret == 0)
                {
                    // Return to original state and indicate error
                    (ListenSocketContext->dwOutstandingAsync)--;

                    UnlockSocketContext(ListenSocketContext, &Errno);
                    UnlockSocketContext(AcceptSocketContext, &Errno);

                    PutbackOverlappedStructure(ProviderOverlapped);
                    WSASetLastError(ERROR_INVALID_HANDLE);
                    return FALSE;
                }
            }
            CopyOffset(&ProviderOverlapped->ProviderOverlapped, lpOverlapped);
            ProviderOverlapped->AcceptExArgs.dwBytesReceived = (lpdwBytesReceived ? *lpdwBytesReceived : 0);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            // Return to original state and indicate error
            (ListenSocketContext->dwOutstandingAsync)--;

            UnlockSocketContext(ListenSocketContext, &Errno);
            UnlockSocketContext(AcceptSocketContext, &Errno);

            PutbackOverlappedStructure(ProviderOverlapped);
            WSASetLastError(WSAEFAULT);
            return FALSE;
        }
        //
        // Save off the paramters and initalize the overlapped structure
        //
        ProviderOverlapped->lpCallerOverlapped = lpOverlapped;
        ProviderOverlapped->SockInfo           = ListenSocketContext;
        ProviderOverlapped->CallerSocket       = sListenSocket;
        ProviderOverlapped->ProviderSocket     = ListenSocketContext->ProviderSocket;
        ProviderOverlapped->Error              = NO_ERROR;
        ProviderOverlapped->Operation          = LSP_OP_ACCEPTEX;
        ProviderOverlapped->lpCallerCompletionRoutine          = NULL;
        ProviderOverlapped->AcceptExArgs.sAcceptSocket         = sAcceptSocket;
        ProviderOverlapped->AcceptExArgs.sProviderAcceptSocket = AcceptSocketContext->ProviderSocket;
        ProviderOverlapped->AcceptExArgs.lpOutputBuffer        = lpOutputBuffer;
        ProviderOverlapped->AcceptExArgs.dwReceiveDataLength   = dwReceiveDataLength;
        ProviderOverlapped->AcceptExArgs.dwLocalAddressLength  = dwLocalAddressLength;
        ProviderOverlapped->AcceptExArgs.dwRemoteAddressLength = dwRemoteAddressLength;
        ProviderOverlapped->Provider = AcceptSocketContext->Provider;

        ret = QueueOverlappedOperation(ProviderOverlapped, ListenSocketContext);

        if (ret != NO_ERROR)
        {
            WSASetLastError(ret);
            ret = FALSE;
        }
        else
        {
            ret = TRUE;
        }
	}
	else
	{
		ret = ListenSocketContext->Provider->NextProcTableExt.lpfnAcceptEx(
			ListenSocketContext->ProviderSocket,
			AcceptSocketContext->ProviderSocket,
			lpOutputBuffer,
			dwReceiveDataLength,
			dwLocalAddressLength,
			dwRemoteAddressLength,
			lpdwBytesReceived,
			NULL);
	}

    UnlockSocketContext(ListenSocketContext, &Errno);
    UnlockSocketContext(AcceptSocketContext, &Errno);

    return ret;
}

//
// Function: ExtConnectEx
//
// Description:
//    This is our provider's ConnectEx function. When an app calls WSAIoctl
//    to request the function pointer to ConnectEx, we intercept the call
//    and return a pointer to our extension function instead.
//
BOOL PASCAL FAR ExtConnectEx(
    IN SOCKET s,
    IN const struct sockaddr FAR *name,
    IN int namelen,
    IN PVOID lpSendBuffer OPTIONAL,
    IN DWORD dwSendDataLength,
    OUT LPDWORD lpdwBytesSent,
    IN LPOVERLAPPED lpOverlapped)
{
    SOCK_INFO           *SocketContext=NULL;
    LPWSAOVERLAPPEDPLUS  ProviderOverlapped=NULL;
    int                  Errno,
                         ret;

    // Get the context
    SocketContext = FindAndLockSocketContext(s, &Errno);
    if (SocketContext == NULL)
    {
        dbgprint("ExtConnectEx: WPUQuerySocketHandleContext() failed: %d", Errno);
        return FALSE;
    }

    // Verify the function pointer is correct
    if (!SocketContext->Provider->NextProcTableExt.lpfnConnectEx)
    {
        GUID    guidConnectEx = WSAID_CONNECTEX;

        if (LoadExtensionFunction(
                (FARPROC **)&SocketContext->Provider->NextProcTableExt.lpfnConnectEx,
                guidConnectEx,
                SocketContext->Provider->NextProcTable.lpWSPIoctl,
                SocketContext->ProviderSocket
                ) == FALSE)
        {
            UnlockSocketContext(SocketContext, &Errno);

            dbgprint("Next proc table ConnectEx == NULL!");
            WSASetLastError(WSAEFAULT);
            return FALSE;
        }
    }

    // Check for overlapped I/O

    if (lpOverlapped)
    {
        ProviderOverlapped = GetOverlappedStructure(SocketContext);
        if (!ProviderOverlapped)
        {
            UnlockSocketContext(SocketContext, &Errno);

            dbgprint("ExtConnectEx: GetOverlappedStructure() returned NULL");
            WSASetLastError(WSAENOBUFS);
            return FALSE;
        }
        //
        // Save off the arguments and setup the overlapped structure
        //
        // Also reset the event handle if present
        //
        __try {
            if ( lpOverlapped->hEvent != NULL )
            {
                ret = ResetEvent((HANDLE)((ULONG_PTR)lpOverlapped->hEvent & ~EventMask));
                if (ret == 0)
                {
                    // Return to original state and indicate error
                    (SocketContext->dwOutstandingAsync)--;
                    UnlockSocketContext(SocketContext, &Errno);
                    PutbackOverlappedStructure(ProviderOverlapped);
                    WSASetLastError(ERROR_INVALID_HANDLE);
                    return FALSE;
                }
            }
            CopyOffset(&ProviderOverlapped->ProviderOverlapped, lpOverlapped);
            if (namelen <= sizeof(ProviderOverlapped->ConnectExArgs.name))
                CopyMemory(&ProviderOverlapped->ConnectExArgs.name, name, namelen);
            ProviderOverlapped->ConnectExArgs.dwBytesSent = (lpdwBytesSent ? *lpdwBytesSent : 0);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            (SocketContext->dwOutstandingAsync)--;
            UnlockSocketContext(SocketContext, &Errno);
            PutbackOverlappedStructure(ProviderOverlapped);
            WSASetLastError(WSAEFAULT);
            return FALSE;
        }

        ProviderOverlapped->lpCallerOverlapped = lpOverlapped;
        ProviderOverlapped->SockInfo           = SocketContext;
        ProviderOverlapped->CallerSocket       = s;
        ProviderOverlapped->ProviderSocket     = SocketContext->ProviderSocket;
        ProviderOverlapped->Error              = NO_ERROR;
        ProviderOverlapped->Operation          = LSP_OP_CONNECTEX;
        ProviderOverlapped->lpCallerCompletionRoutine      = NULL;
        ProviderOverlapped->ConnectExArgs.s                = s;
        ProviderOverlapped->ConnectExArgs.namelen          = namelen;
        ProviderOverlapped->ConnectExArgs.lpSendBuffer     = lpSendBuffer;
        ProviderOverlapped->ConnectExArgs.dwSendDataLength = dwSendDataLength;
        ProviderOverlapped->Provider           = SocketContext->Provider;

        ret = QueueOverlappedOperation(ProviderOverlapped, SocketContext);

        if (ret != NO_ERROR)
        {
            WSASetLastError(ret);
            ret = FALSE;
        }
        else
        {
            ret = TRUE;
        }
    }
    else
    {
        ret = SocketContext->Provider->NextProcTableExt.lpfnConnectEx(
            SocketContext->ProviderSocket,
            name,
            namelen,
            lpSendBuffer,
            dwSendDataLength,
            lpdwBytesSent,
            NULL);
    }
    UnlockSocketContext(SocketContext, &Errno);

    return ret;
}

//
// Function: ExtTransmitPackets
//
// Description:
//    This is our provider's TransmitPackets function. When an app calls WSAIoctl
//    to request the function pointer to TransmitPackets, we intercept the call
//    and return a pointer to our extension function instead.
//
BOOL PASCAL FAR ExtTransmitPackets(
    SOCKET hSocket,
    LPTRANSMIT_PACKETS_ELEMENT lpPacketArray,
    DWORD nElementCount,
    DWORD nSendSize,
    LPOVERLAPPED lpOverlapped,
    DWORD dwFlags)
{
    SOCK_INFO           *SocketContext=NULL;
    LPWSAOVERLAPPEDPLUS  ProviderOverlapped=NULL;
    int                  Errno,
                         ret;

    // Get the context
    SocketContext = FindAndLockSocketContext(hSocket, &Errno);
    if (SocketContext == NULL)
    {
        dbgprint("ExtTransmitPackets: WPUQuerySocketHandleContext() failed: %d", Errno);
        WSASetLastError(Errno);
        return FALSE;
    }

    // Make sure we already have the extension function
    if (!SocketContext->Provider->NextProcTableExt.lpfnTransmitPackets)
    {
        GUID    guidTransmitPackets = WSAID_TRANSMITPACKETS;

        if (LoadExtensionFunction(
                (FARPROC **)&SocketContext->Provider->NextProcTableExt.lpfnTransmitPackets,
                guidTransmitPackets,
                SocketContext->Provider->NextProcTable.lpWSPIoctl,
                SocketContext->ProviderSocket
                ) == FALSE)
        {
            UnlockSocketContext(SocketContext, &Errno);
            dbgprint("Next proc table TransmitPackets == NULL!");
            WSASetLastError(WSAEFAULT);
            return FALSE;
        }
    }
    //
    // Check for overlapped I/O
    //
    if (lpOverlapped)
    {
        ProviderOverlapped = GetOverlappedStructure(SocketContext);
        if (!ProviderOverlapped)
        {
            UnlockSocketContext(SocketContext, &Errno);
            dbgprint("ExtTransmitPackets: GetOverlappedStructure() returned NULL");
            WSASetLastError(WSAENOBUFS);
            return FALSE;
        }
        //
        // Save off the arguments and setup the overlapped structure
        //
        // Verify the event is valid
        //
        __try {
            if ( lpOverlapped->hEvent != NULL )
            {
                ret = ResetEvent((HANDLE)((ULONG_PTR)lpOverlapped->hEvent & ~EventMask));
                if (ret == 0)
                {
                    // Return to original state and indicate error
                    (SocketContext->dwOutstandingAsync)--;
                    UnlockSocketContext(SocketContext, &Errno);
                    PutbackOverlappedStructure(ProviderOverlapped);
                    WSASetLastError(ERROR_INVALID_HANDLE);
                    return FALSE;
                }
            }
            CopyOffset(&ProviderOverlapped->ProviderOverlapped, lpOverlapped);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            // Return to original state and indicate error
            (SocketContext->dwOutstandingAsync)--;
            UnlockSocketContext(SocketContext, &Errno);
            PutbackOverlappedStructure(ProviderOverlapped);
            WSASetLastError(WSAEFAULT);
            return FALSE;
        }
        ProviderOverlapped->lpCallerOverlapped = lpOverlapped;
        ProviderOverlapped->SockInfo           = SocketContext;
        ProviderOverlapped->CallerSocket       = hSocket;
        ProviderOverlapped->ProviderSocket     = SocketContext->ProviderSocket;
        ProviderOverlapped->Error              = NO_ERROR;
        ProviderOverlapped->Operation          = LSP_OP_TRANSMITPACKETS;
        ProviderOverlapped->lpCallerCompletionRoutine           = NULL;
        ProviderOverlapped->TransmitPacketsArgs.s               = hSocket;
        ProviderOverlapped->TransmitPacketsArgs.lpPacketArray   = lpPacketArray;
        ProviderOverlapped->TransmitPacketsArgs.nElementCount   = nElementCount;
        ProviderOverlapped->TransmitPacketsArgs.nSendSize       = nSendSize;
        ProviderOverlapped->TransmitPacketsArgs.dwFlags         = dwFlags;
        ProviderOverlapped->Provider           = SocketContext->Provider;

        ret = QueueOverlappedOperation(ProviderOverlapped, SocketContext);

        if (ret != NO_ERROR)
        {
            WSASetLastError(ret);
            ret = FALSE;
        }
        else
        {
            ret = TRUE;
        }

    }
    else
    {
        ret = SocketContext->Provider->NextProcTableExt.lpfnTransmitPackets(
            SocketContext->ProviderSocket,
            lpPacketArray,
            nElementCount,
            nSendSize,
            NULL,
            dwFlags);
    }
    UnlockSocketContext(SocketContext, &Errno);

    return ret;
}

//
// Function: ExtDisconnectEx
//
// Description:
//    This is our provider's DisconnectEx function. When an app calls WSAIoctl
//    to request the function pointer to DisconnectEx, we intercept the call
//    and return a pointer to our extension function instead.
//
BOOL PASCAL FAR ExtDisconnectEx(
    IN SOCKET s,
    IN LPOVERLAPPED lpOverlapped,
    IN DWORD  dwFlags,
    IN DWORD  dwReserved)
{
    SOCK_INFO           *SocketContext=NULL;
    LPWSAOVERLAPPEDPLUS  ProviderOverlapped=NULL;
    int                  Errno,
                         ret;

    // Get the context
    SocketContext = FindAndLockSocketContext(s, &Errno);
    if (SocketContext == NULL)
    {
        dbgprint("ExtDisconnectEx: WPUQuerySocketHandleContext() failed: %d", Errno);
        WSASetLastError(Errno);
        return FALSE;
    }

    // Make sure we already have the extension function
    if (!SocketContext->Provider->NextProcTableExt.lpfnDisconnectEx)
    {
        GUID    guidDisconnectEx = WSAID_DISCONNECTEX;

        if (LoadExtensionFunction(
                 (FARPROC **)&SocketContext->Provider->NextProcTableExt.lpfnDisconnectEx,
                 guidDisconnectEx,
                 SocketContext->Provider->NextProcTable.lpWSPIoctl,
                 SocketContext->ProviderSocket
                 ) == NULL)
        {
            UnlockSocketContext(SocketContext, &Errno);
            dbgprint("Next proc table DisconnectEx == NULL!");
            WSASetLastError(WSAEFAULT);
            return FALSE;
        }
    }


    // Check for overlapped I/O

    if (lpOverlapped)
    {
        ProviderOverlapped = GetOverlappedStructure(SocketContext);
        if (!ProviderOverlapped)
        {
            UnlockSocketContext(SocketContext, &Errno);
            dbgprint("ExtDisconnectEx: GetOverlappedStructure() returned NULL");
            WSASetLastError(WSAENOBUFS);
            return FALSE;
        }
        //
        // Save off the arguments and setup the overlapped structure
        //
        // Verify the event is valid
        //
        __try {
            if ( lpOverlapped->hEvent != NULL )
            {
                ret = ResetEvent((HANDLE)((ULONG_PTR)lpOverlapped->hEvent & ~EventMask));
                if (ret == 0)
                {
                    (SocketContext->dwOutstandingAsync)--;
                    PutbackOverlappedStructure(ProviderOverlapped);
                    UnlockSocketContext(SocketContext, &Errno);
                    WSASetLastError(ERROR_INVALID_HANDLE);
                    return FALSE;
                }
            }
            CopyOffset(&ProviderOverlapped->ProviderOverlapped, lpOverlapped);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            (SocketContext->dwOutstandingAsync)--;
            PutbackOverlappedStructure(ProviderOverlapped);
            UnlockSocketContext(SocketContext, &Errno);
            WSASetLastError(WSAEFAULT);
            return FALSE;
        }

        ProviderOverlapped->lpCallerOverlapped = lpOverlapped;
        ProviderOverlapped->SockInfo           = SocketContext;
        ProviderOverlapped->CallerSocket       = s;
        ProviderOverlapped->ProviderSocket     = SocketContext->ProviderSocket;
        ProviderOverlapped->Error              = NO_ERROR;
        ProviderOverlapped->Operation          = LSP_OP_DISCONNECTEX;
        ProviderOverlapped->lpCallerCompletionRoutine           = NULL;
        ProviderOverlapped->DisconnectExArgs.s                  = s;
        ProviderOverlapped->DisconnectExArgs.dwFlags            = dwFlags;
        ProviderOverlapped->DisconnectExArgs.dwReserved         = dwReserved;
        ProviderOverlapped->Provider           = SocketContext->Provider;
 
        ret = QueueOverlappedOperation(ProviderOverlapped, SocketContext);

        if (ret != NO_ERROR)
        {
            WSASetLastError(ret);
            ret = FALSE;
        }
        else
        {
            ret = TRUE;
        }
    }
    else
    {
        ret = SocketContext->Provider->NextProcTableExt.lpfnDisconnectEx(
            SocketContext->ProviderSocket,
            lpOverlapped,
            dwFlags,
            dwReserved);
    }
    UnlockSocketContext(SocketContext, &Errno);

    return ret;
}

//
// Function: ExtWSARecvMsg
//
// Description:
//    This is our provider's WSARecvMsg function. When an app calls WSAIoctl
//    to request the function pointer to WSARecvMsg, we intercept the call
//    and return a pointer to our extension function instead.
//
INT PASCAL FAR ExtWSARecvMsg(
    IN SOCKET s,
    IN OUT LPWSAMSG lpMsg,
    OUT LPDWORD lpdwNumberOfBytesRecvd,
    IN LPWSAOVERLAPPED lpOverlapped,
    IN LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    SOCK_INFO           *SocketContext=NULL;
    LPWSAOVERLAPPEDPLUS  ProviderOverlapped=NULL;
    int                  Errno,
                         ret = NO_ERROR;

    // Get the context
    SocketContext = FindAndLockSocketContext(s, &Errno);
    if (SocketContext == NULL)
    {
        dbgprint("ExtWSARecvmsg: WPUQuerySocketHandleContext() failed: %d", Errno);
        WSASetLastError(Errno);
        return SOCKET_ERROR;
    }

    // Make sure we already have the extension function
    if (!SocketContext->Provider->NextProcTableExt.lpfnWSARecvMsg)
    {
        GUID    guidWSARecvMsg = WSAID_WSARECVMSG;

        if (LoadExtensionFunction(
                (FARPROC **)&SocketContext->Provider->NextProcTableExt.lpfnWSARecvMsg,
                guidWSARecvMsg,
                SocketContext->Provider->NextProcTable.lpWSPIoctl,
                SocketContext->ProviderSocket
                ) == FALSE)
        {
            UnlockSocketContext(SocketContext, &Errno);
            dbgprint("Next proc table WSARecvMsg == NULL!");
            WSASetLastError(WSAEFAULT);
            return SOCKET_ERROR;
        }
    }
    //
    // Check for overlapped I/O
    //
    if (lpOverlapped)
    {
        ProviderOverlapped = GetOverlappedStructure(SocketContext);
        if (!ProviderOverlapped)
        {
            UnlockSocketContext(SocketContext, &Errno);
            dbgprint("ExtWSARecvMsg: GetOverlappedStructure() returned NULL");
            WSASetLastError(WSAENOBUFS);
            return SOCKET_ERROR;
        }
        //
        // Save off the arguments and setup the overlapped structure
        //
        __try {
            if (( lpCompletionRoutine == NULL ) && ( lpOverlapped->hEvent != NULL ))
            {
                // Verify the event is valid
                ret = ResetEvent((HANDLE)((ULONG_PTR)lpOverlapped->hEvent & ~EventMask));
                if (ret == 0)
                {
                    // Return to original state and indicate error
                    (SocketContext->dwOutstandingAsync)--;
                    UnlockSocketContext(SocketContext, &Errno);
                    PutbackOverlappedStructure(ProviderOverlapped);
                    WSASetLastError(ERROR_INVALID_HANDLE);
                    return SOCKET_ERROR;
                }
            }
            CopyOffset(&ProviderOverlapped->ProviderOverlapped, lpOverlapped);
            ProviderOverlapped->WSARecvMsgArgs.dwNumberOfBytesRecvd = (lpdwNumberOfBytesRecvd ? *lpdwNumberOfBytesRecvd : 0);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            // Return to original state and indicate error
            (SocketContext->dwOutstandingAsync)--;
            UnlockSocketContext(SocketContext, &Errno);
            PutbackOverlappedStructure(ProviderOverlapped);
            WSASetLastError(WSAEFAULT);
            return SOCKET_ERROR;
        }
        ProviderOverlapped->lpCallerOverlapped = lpOverlapped;
        ProviderOverlapped->SockInfo           = SocketContext;
        ProviderOverlapped->CallerSocket       = s;
        ProviderOverlapped->ProviderSocket     = SocketContext->ProviderSocket;
        ProviderOverlapped->Error              = NO_ERROR;
        ProviderOverlapped->Operation          = LSP_OP_WSARECVMSG;
        ProviderOverlapped->lpCallerCompletionRoutine           = lpCompletionRoutine;
        ProviderOverlapped->WSARecvMsgArgs.s                    = s;
        ProviderOverlapped->WSARecvMsgArgs.lpMsg                = lpMsg;
        ProviderOverlapped->Provider           = SocketContext->Provider;

        ret = QueueOverlappedOperation(ProviderOverlapped, SocketContext);

        if (ret != NO_ERROR)
        {
            WSASetLastError(ret);
            ret = SOCKET_ERROR;
        }
        else
        {
            ret = NO_ERROR;
        }
    }
    else
    {
        ret = SocketContext->Provider->NextProcTableExt.lpfnWSARecvMsg(
            SocketContext->ProviderSocket,
            lpMsg,
            lpdwNumberOfBytesRecvd,
            NULL,
            NULL);
    }

    UnlockSocketContext(SocketContext, &Errno);

    return ret;
}
