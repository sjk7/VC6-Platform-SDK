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
//    This sample illustrates how to develop a layered service provider.
//    This sample is a pass through sample which only counts the bytes
//    transfered on the socket.
//
//    This file contains support functions that are common to the lsp and
//    the instlsp sample for enumerating the Winsock catalog of service
//    providers.
//
//    Note all allocations made in this routine use the process heap and
//    not the LSP heap since these routines are also used by the LSP
//    installer (which doesn't create its own heap).
//    

#include <ws2spi.h>
#include <sporder.h>
#include "install.h"

#include <stdio.h>
#include <stdlib.h>

//
// Function: GetProviders
//
// Description:
//    This enumerates the Winsock catalog via the global variable ProtocolInfo.
//
LPWSAPROTOCOL_INFOW EnumerateProviders(WINSOCK_CATALOG Catalog, LPINT TotalProtocols)
{
	LPWSAPROTOCOL_INFOW ProtocolInfo = NULL;
	DWORD               ProtocolInfoSize = 0;
	INT                 ErrorCode,
                        rc;
    
    if (TotalProtocols == NULL)
        return NULL;

	*TotalProtocols = 0;

#ifdef _WIN64
	// Find out how many entries we need to enumerate
    if (Catalog == LspCatalog64Only)
    {
        // Find the size of the buffer
        rc = WSCEnumProtocols(NULL, ProtocolInfo, &ProtocolInfoSize, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            if (ErrorCode != WSAENOBUFS)
                return NULL;
        }

        // Allocate the buffer
        ProtocolInfo = (LPWSAPROTOCOL_INFOW) HeapAlloc(GetProcessHeap(), 0, ProtocolInfoSize);
        if (ProtocolInfo == NULL)
        {
            return NULL;
        }

        // Enumerate the catalog for real
        rc = WSCEnumProtocols(NULL, ProtocolInfo, &ProtocolInfoSize, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            HeapFree(GetProcessHeap(), 0, ProtocolInfo);
            return NULL;
        }

        // Update the count
        *TotalProtocols = rc;
    }
    else if (Catalog == LspCatalog32Only)
    {
        HMODULE            hModule;
        LPWSCENUMPROTOCOLS fnWscEnumProtocols32=NULL;

        // Load ws2_32.dll
        hModule = LoadLibrary(TEXT("ws2_32.dll"));
        if (hModule == NULL)
            return NULL;

        // Find the 32-bit catalog enumerator
        fnWscEnumProtocols32 = (LPWSCENUMPROTOCOLS)GetProcAddress(hModule, "WSCEnumProtocols32");
        if (fnWscEnumProtocols32 == NULL)
            return NULL;
        
        // Find the required buffer size
        rc = fnWscEnumProtocols32(NULL, ProtocolInfo, &ProtocolInfoSize, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            if (ErrorCode != WSAENOBUFS)
                return NULL;
        }

        // Allocate the buffer
        ProtocolInfo = (LPWSAPROTOCOL_INFOW)HeapAlloc(GetProcessHeap(), 0, ProtocolInfoSize);
        if (ProtocolInfo == NULL)
        {
            return NULL;
        }

        // Enumrate the catalog for real this time
        rc = fnWscEnumProtocols32(NULL, ProtocolInfo, &ProtocolInfoSize, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            HeapFree(GetProcessHeap(), 0, ProtocolInfo);
            return NULL;
        }

        // Update the count 
        *TotalProtocols = rc;

        FreeLibrary(hModule);
    }
#else
    if (Catalog == LspCatalog32Only)
    {
        // Find the size of the buffer
        rc = WSCEnumProtocols(NULL, ProtocolInfo, &ProtocolInfoSize, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            if (ErrorCode != WSAENOBUFS)
                return NULL;
        }

        // Allocate the buffer
        ProtocolInfo = (LPWSAPROTOCOL_INFOW) HeapAlloc(GetProcessHeap(), 0, ProtocolInfoSize);
        if (ProtocolInfo == NULL)
        {
            return NULL;
        }

        // Enumerate the catalog for real
        rc = WSCEnumProtocols(NULL, ProtocolInfo, &ProtocolInfoSize, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            HeapFree(GetProcessHeap(), 0, ProtocolInfo);
            return NULL;
        }

        // Update the count
        *TotalProtocols = rc;
    }
    else if (Catalog == LspCatalog64Only)
    {
        fprintf(stderr, "Unable to enumerate 64-bit Winsock catalog from 32-bit process!\n");
    }
#endif
    else
    {
        // Find the size of the buffer
        rc = WSCEnumProtocols(NULL, ProtocolInfo, &ProtocolInfoSize, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            if (ErrorCode != WSAENOBUFS)
                return NULL;
        }

        // Allocate the buffer
        ProtocolInfo = (LPWSAPROTOCOL_INFOW) HeapAlloc(GetProcessHeap(), 0, ProtocolInfoSize);
        if (ProtocolInfo == NULL)
        {
            return NULL;
        }

        // Enumerate the catalog for real
        rc = WSCEnumProtocols(NULL, ProtocolInfo, &ProtocolInfoSize, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            HeapFree(GetProcessHeap(), 0, ProtocolInfo);
            return NULL;
        }

        // Update the count
        *TotalProtocols = rc;
    }

	return ProtocolInfo;
}

//
// Function: FreeProviders
//
// Description:
//    This function frees the global catalog.
//
void FreeProviders(LPWSAPROTOCOL_INFOW ProtocolInfo)
{
	HeapFree(GetProcessHeap(), 0, ProtocolInfo);
}
