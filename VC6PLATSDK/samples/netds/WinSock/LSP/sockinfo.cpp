// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1999  Microsoft Corporation.  All Rights Reserved.
//
// Module Name: provider.cpp
//
// Description:
//
//    This sample illustrates how to develop a layered service provider that is
//    capable of counting all bytes transmitted through a TCP/IP socket.
//
//    This file contains support functions that are common to the lsp and
//    the instlsp sample for enumerating the Winsock catalog of service
//    providers.
//    

#include "provider.h"

//
// External variable definitions
//
extern CRITICAL_SECTION gCriticalSection;
extern INT              gLayerCount;
extern PROVIDER        *gBaseInfo;
extern HANDLE           hLspHeap;
extern HANDLE           gAddContextEvent;

static char Msg[512];

//
// Function: FindAndLockSocketContext
//
// Description:
//    This routine grabs the LSP critical seciton to lookup the socket context
//    and increase its ref count. Any operation on the socket context holds
//    the critical section so that it cannot be freed while its state changes.
//
SOCK_INFO *FindAndLockSocketContext(SOCKET s, int *lpErrno)
{
    SOCK_INFO *SocketContext=NULL;
    int        ret;

    EnterCriticalSection(&gCriticalSection);

    ret = MainUpCallTable.lpWPUQuerySocketHandleContext(
            s,
            (PDWORD_PTR) &SocketContext,
            lpErrno
            );
    if (ret == SOCKET_ERROR)
    {
        dbgprint("FindAndLockSocketContext: WPUQuerySocketHandleContext failed: %d", *lpErrno);
    }
    else
    {
        InterlockedIncrement(&SocketContext->RefCount);
    }
    LeaveCriticalSection(&gCriticalSection);

    return SocketContext;
}

//
// Function: UnlockSocketContext
//
// Description:
//    This routine holds the LSP critical section and decrements the ref count
//    by one. It also checks if the socket has been closed while holding the
//    ref count. This can happen if two threads are accessing a socket simultaneously
//    and one calls closesocket. We don't want to remove the context from under
//    the second thread so it is marked as closing instead.
//
void UnlockSocketContext(SOCK_INFO *context, int *lpErrno)
{
    LONG    newval;

    EnterCriticalSection(&gCriticalSection);

    // Decrement the ref count and see if someone closed this socket (from another thread)
    newval = InterlockedDecrement(&context->RefCount);
    if ((newval == 0) && (context->dwOutstandingAsync == 0) && (context->bClosing))
    {
        // Socket has been closed so close the handle and free associated resources
        if (MainUpCallTable.lpWPUCloseSocketHandle(context->LayeredSocket, lpErrno) == SOCKET_ERROR)
        {
            dbgprint("UnlockSocketContext: WPUCloseSocketHandle() failed: %d", *lpErrno);
        }

        context->LayeredSocket = INVALID_SOCKET;

        RemoveSocketInfo(context->Provider, context);

        #ifdef DEBUG
        dbgprint("Closing socket %d Bytes Sent [%lu] Bytes Recv [%lu]", 
                context->LayeredSocket, context->BytesSent, context->BytesRecv);
        #endif

        ReleaseSocketLock(context);

        #ifdef DEBUG
        dbgprint("Freeing a SOCK_INFO (SocketContext) structure");
        #endif

        FreeSockInfo(context);
        context = NULL;
    }

    LeaveCriticalSection(&gCriticalSection);
}

//
// Function: AcquireSocketLock
// 
// Description:
//    This routine acquires the critical section which is a member of the 
//    socket's context structure. This is held when modifying the socket
//    context outside of looking up the context (which is performed by
//    FindAndLockSocketContext).
//
void AcquireSocketLock(SOCK_INFO *SockInfo)
{
    EnterCriticalSection(&SockInfo->SockCritSec);
}

//
// Function: ReleaseSocketLock
//
// Description:
//    This routine releases the socket context critical section.
//
void ReleaseSocketLock(SOCK_INFO *SockInfo)
{
    LeaveCriticalSection(&SockInfo->SockCritSec);
}

//
// Function: CreateSockInfo
//
// Description:
//    Allocates a new socket info context structure and initializes the fields
//    except for the LayeredSocket field. The context must be allocated first,
//    then the layered socket is created (with the SOCK_INFO structure as the
//    context information), and then the LayeredSocket field is set. If
//    the Inherit context is provided, information is copied to the new socket
//    context structure (such as with WSPAccept). If the Insert flag is TRUE
//    then the context is automatically inserted into the list of sockets
//    for the given provider. If not then the caller must insert the context
//    (WSPAccept does this to ensure all fields of the context are valid
//    including LayeredSocket before insertion so that the async thread
//    handler will work properly).
//
SOCK_INFO *CreateSockInfo(PROVIDER *Provider, SOCKET ProviderSocket, SOCK_INFO *Inherit, BOOL Insert)
{
    SOCK_INFO   *NewInfo=NULL;

    NewInfo = (SOCK_INFO *)HeapAlloc(hLspHeap,
                                     HEAP_ZERO_MEMORY,
                                     sizeof(SOCK_INFO));
    if (NewInfo == NULL)
    {
        dbgprint("HeapAlloc() failed: %d", GetLastError());
        return NULL;
    }
    NewInfo->ProviderSocket     = ProviderSocket;
    NewInfo->bClosing           = FALSE;
    NewInfo->dwOutstandingAsync = 0;
    NewInfo->BytesRecv          = 0;
    NewInfo->BytesSent          = 0;
    NewInfo->Provider           = Provider;
    NewInfo->hWnd               = (Inherit ? Inherit->hWnd : 0);
    NewInfo->uMsg               = (Inherit ? Inherit->uMsg : 0);

    InitializeCriticalSection(&NewInfo->SockCritSec);

    if (Insert == TRUE)
    {
        InsertSocketInfo(Provider, NewInfo);
    }

    return NewInfo;
}

//
// Function: FreeSockInfo
//
// Description:
//    This routine frees the socket context structure.
//
void FreeSockInfo(SOCK_INFO *info)
{
    DeleteCriticalSection(&info->SockCritSec);
    HeapFree(hLspHeap, 0, info);

    return;
}

//
// Function: InsertSocketInfo
//
// Description:
//    We keep track of all the sockets created for a particulare provider.
//    This routine inserts a newly created socket (and its SOCK_INFO) into
//    the list.
//
void InsertSocketInfo(PROVIDER *provider, SOCK_INFO *sock)
{
    if (!provider || !sock)
    {
        dbgprint("InsertSocketInfo: PROVIDER or SOCK_INFO == NULL!");
        return;
    }

    EnterCriticalSection(&provider->ProviderCritSec);

    sock->next = sock->prev = NULL;

    sock->next = provider->SocketList;
    if (provider->SocketList)
    {
        provider->SocketList->prev = sock;
    }
    provider->SocketList = sock;

    LeaveCriticalSection(&provider->ProviderCritSec);

    SetEvent(gAddContextEvent);
}

// 
// Function: RemoveSocketInfo
//
// Description:
//    This function removes a given SOCK_INFO structure from the referenced
//    provider. It doesn't free the structure, it just removes it from the 
//    list.
//
void RemoveSocketInfo(PROVIDER *provider, SOCK_INFO *si)
{
    EnterCriticalSection(&provider->ProviderCritSec);
    if (si->prev == NULL)
    {
        provider->SocketList = si->next;
        if (provider->SocketList)
            provider->SocketList->prev = NULL;
    }
    else
    {
        si->prev->next = si->next;
        if (si->next)
            si->next->prev = si->prev;
    }

    LeaveCriticalSection(&provider->ProviderCritSec);
}

//
// Function: CloseAndFreeSocketInfo
//
// Description:
//    Closes all sockets belonging to the specified provider and frees
//    the context information. If the lower provider socket is still 
//    valid, set an abortive linger, and close the socket.
//
void CloseAndFreeSocketInfo(PROVIDER *provider)
{
    SOCK_INFO    *si=NULL,
                 *siprev=NULL;
    struct linger linger;
    int           Error, ret;

    linger.l_onoff = 1;
    linger.l_linger = 0;

    // Walk the list of sockets
    si = provider->SocketList;
    while (si)
    {
        // Set the abortive linger
        ret = provider->NextProcTable.lpWSPSetSockOpt(
            si->ProviderSocket,
            SOL_SOCKET,
            SO_LINGER,
            (char *)&linger,
            sizeof(linger),
            &Error);
        if (ret != SOCKET_ERROR)
        {
            // Close the lower provider socket
            ret = provider->NextProcTable.lpWSPCloseSocket(
                si->ProviderSocket,
                &Error);
            if (ret == SOCKET_ERROR)
            {
                dbgprint("WSPCloseSocket() on handle %d failed: %d", si->ProviderSocket, Error);
            }
            #ifdef DEBUG
            else
            {
                dbgprint("Successfully closed socket %d", si->ProviderSocket);
            }
            #endif
        }
        #ifdef DEBUG
        else
        {
            dbgprint("WSPSetSockOpt(SO_LINGER) failed: %d", Error);
        }
        #endif

        // Close the layered handle
        MainUpCallTable.lpWPUCloseSocketHandle(
            si->LayeredSocket, 
            &Error);

        siprev = si;
        si = si->next;

        // Free the context structure
        FreeSockInfo(siprev);
    }
    return;
}

//
// Function: GetCallerSocket
//
// Description:
//    This function returns the SOCK_INFO structure for the given
//    provider socket. If provider is NULL then we'll search all
//    providers for the socket info. This routine is only used
//    in handling asynchronous window messages (WSAAsyncSelect)
//    since the window handler receives only the provider's socket
//    and we need to find the associated context structure.
//
SOCK_INFO *GetCallerSocket(PROVIDER *provider, SOCKET ProviderSock)
{
    SOCK_INFO *si;

    EnterCriticalSection(&gCriticalSection);

    if (provider)
    {
        // If we know the provider just search its list of sockets
        si = provider->SocketList;
        while(si)
        {
            if (si->ProviderSocket == ProviderSock)
            {
                LeaveCriticalSection(&gCriticalSection);
                return si;
            }
            si = si->next;
        }
    }
    else
    {
        // Don't know the provider so we must search all of them
        for(INT i=0; i < gLayerCount ;i++)
        {
            si = gBaseInfo[i].SocketList;
            while (si)
            {
                if (si->ProviderSocket == ProviderSock)
                {
                    LeaveCriticalSection(&gCriticalSection);
                    return si;
                }
                si = si->next;
            }
        }
    }

    LeaveCriticalSection(&gCriticalSection);
    return NULL;
}
