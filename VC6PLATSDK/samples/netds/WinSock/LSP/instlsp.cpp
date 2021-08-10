// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1999  Microsoft Corporation.  All Rights Reserved.
//
// Module Name: instlsp.cpp
//
// Description:
//
//    This sample illustrates how to develop a layered service provider.
//    This LSP is simply a pass through sample which counts the bytes transfered
//    on each socket. 
//
//    This file contains an installation program to insert the layered sample
//    into the Winsock catalog of providers.
//    
//
// Compile:
//
//    Compile with the Makefile:
//      nmake /f Makefile
//
// Execute:
//
//    This project produces a executable file instlsp.exe. The installation app
//    allows you to install the LSP over any provider. Note however that if you
//    choose to install over a single provider, you should install over all 
//    providers of that address family (e.g. if you install over UDP, install
//    over TCP and RAW providers as well). The arguments are:
//
//       -a             Install over all providers
//       -c Catalog     Indicates which catalog to operate on (for Win64)
//       -f             Remove all layered providers (last ditch recovery)
//       -i             Install the LSP
//       -l             Print the layered entries only
//       -m             Displays a logical, ordered map of the LSPs installed
//       -n "String"    Name of the layered provider (catalog name, not dll name)
//       -o  CatID      Layer over the given provider (indicated by the catalog id)
//       -p             Print the Winsock catalog (and catalog ids)
//       -r  CatID      Remove the LSP
//
//    For example, first print out the catalog:
//       instlsp.exe -p
//        1001 - MSAFD ATM AAL5
//        1002 - MSAFD Tcpip [TCP/IP]
//        1003 - MSAFD Tcpip [UDP/IP]
//        1004 - MSAFD Tcpip [RAW/IP]
//        1005 - RSVP UDP Service Provider
//        1006 - RSVP TCP Service Provider
//        1019 - MSAFD AppleTalk [ADSP]
//        1020 - MSAFD AppleTalk [ADSP] [Pseudo Stream]
//        1021 - MSAFD AppleTalk [PAP]
//        1022 - MSAFD AppleTalk [RTMP]
//        1023 - MSAFD AppleTalk [ZIP]
//
//    To install over AppleTalk
//       instlsp.exe -i -o 1019 -o 1020 -o 1021 -o 1022 -o 1023 -n "Foobar LSP"
//
//    Print the new catalog out:
//       instlsp.exe -p
//        1041 - Foobar LSP over [MSAFD AppleTalk [ADSP]]
//        1042 - Foobar LSP over [MSAFD AppleTalk [PAP]]
//        1043 - Foobar LSP over [MSAFD AppleTalk [RTMP]]
//        1044 - Foobar LSP over [MSAFD AppleTalk [ZIP]]
//        1001 - MSAFD ATM AAL5
//        1002 - MSAFD Tcpip [TCP/IP]
//        1003 - MSAFD Tcpip [UDP/IP]
//        1004 - MSAFD Tcpip [RAW/IP]
//        1005 - RSVP UDP Service Provider
//        1006 - RSVP TCP Service Provider
//        1019 - MSAFD AppleTalk [ADSP]
//        1020 - MSAFD AppleTalk [ADSP] [Pseudo Stream]
//        1021 - MSAFD AppleTalk [PAP]
//        1022 - MSAFD AppleTalk [RTMP]
//        1023 - MSAFD AppleTalk [ZIP]
//        1040 - Foobar LSP
//
//    To remove the LSP, supply the catalog ID of the hidden entry to remove:
//       instlsp.exe -r 1040 
//
//    In case all else fails (removes all LSPs installed):
//       instlsp.exe -f
//
#include <winsock2.h>
#include <ws2spi.h>
#include <objbase.h>

#include <rpc.h>
#include <rpcdce.h>

#include <sporder.h>
#include <winnt.h>
#include <windows.h>

#include "install.h"

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PATH_LEN        128
#define MAX_PROVIDERS           256     

#define DEFAULT_LSP_NAME        "Test LSP"

#define MAX(a,b)                ( (a) > (b) ? (a) : (b) )
#define MIN(a,b)                ( (a) < (b) ? (a) : (b) )

// This structure is used to create the logical ordered LSP mappings
typedef struct _LSP_ENTRY
{
    WCHAR               wszLspDll[MAX_PATH];    // LSPs DLL name (and possible path)
    WSAPROTOCOL_INFOW   DummyEntry;             // Provider entry for dummy LSP entry

    WSAPROTOCOL_INFOW  *LayeredEntries;         // All layered providers beloging to LSP
    int                 Count;                  // Number of layered providers

    GUID               *LayeredGuids;           // List of GUIDs the LAYERED providers 
                                                //  are installed under (doesn't include
                                                //  the GUID the dummy entry is installed 
                                                //  under)
    int                 LayeredGuidCount;       // Number of GUIDs in the array

    int                 MaxChainLength;         // Used for sorting: the longest protocol
                                                //  chain of all the layered providers
    int                 LspOrder;               // Used for sorting: the lowest position
                                                //  within a layered entries protocol
                                                //  chain that a base provider sits
} LSP_ENTRY;

//
// Global variable: Function pointer to WSCUpdateProvider if on Windows XP or greater.
//                  Uninstalling an LSP when other LSPs are layered over it is really
//                  difficult; however on Windows XP and greater the WSCUpdateProvider
//                  function makes this dirt simple. On older platforms its a real
//                  pain.
LPWSCUPDATEPROVIDER  fnWscUpdateProvider=NULL;
HMODULE              hModule=NULL;

//
// Function prototypes
//

// Display usage information
void 
usage(
    char *progname
    );

// Enumerate the catalog and print it
void 
PrintProviders(
    WINSOCK_CATALOG Catalog, 
    BOOL bLayeredOnly, 
    BOOL bVerbose
    );

// Install the array of providers with the given GUID and LSP path
int  
InstallProvider(
    WINSOCK_CATALOG Catalog, 
    GUID *Guid, 
    WCHAR *lpwszLspPath, 
    WSAPROTOCOL_INFOW *pProvider, 
    INT iProviderCount
    );

// Remove all providers associated with the given GUID
int  
DeinstallProvider(
    WINSOCK_CATALOG Catalog, 
    GUID *Guid
    );

// Reorder the Winsock catalog with 'dwLayeredId' providers appearing first
int  
ReorderCatalog(
    WINSOCK_CATALOG Catalog, 
    DWORD dwLayeredId
    );

// Determines whether the given ID occurs in the protocol chain
BOOL 
IsIdInChain(
    WSAPROTOCOL_INFOW *pinfo, 
    DWORD Id
    );

// Searches the catalog for all providers referencing ProviderId and removes them
int  
RemoveProvider(
    WINSOCK_CATALOG Catalog, 
    DWORD ProviderId
    );

// Remove all LSP entries
int  
RemoveAllLayeredEntries(
    WINSOCK_CATALOG Catalog
    );

// Create the provider structure for the dummy (hidden) LSP entry
WSAPROTOCOL_INFOW * 
CreateDummyEntry(
    WINSOCK_CATALOG Catalog, 
    INT CatalogId, 
    WCHAR *lpwszLspName
    );

// Create the provider structures for the layered protocol LSP entries
WSAPROTOCOL_INFOW * 
CreateLayeredEntries(
    WINSOCK_CATALOG Catalog, 
    WCHAR *lpwszLspName, 
    GUID *Guid, 
    DWORD *pdwIdArray, 
    INT iIdArrayCount, 
    DWORD *LayeredId
    );

// Reorders both catalogs so providers referencing dwLayerId are first
DWORD *
ReorderACatalog(
    WINSOCK_CATALOG Catalog,
    DWORD   dwLayerId,
    INT   *dwEntryCount
    );

// Returns a logical, ordered mapping of the LSPs installed
LSP_ENTRY *
BuildLspMap(
    WSAPROTOCOL_INFOW *pProviders,
    int  iProviderCount,
    int *pLspCount
    );

// Counts how many providers of the given type are present
int
GetProviderCount(
    WSAPROTOCOL_INFOW *pProviders,
    int iProviderCount,
    int ProviderType
    );

// Prints the LSP map to the console
void
PrintLspMap(
    LSP_ENTRY *pLspMap,
    int iLspCount
    );

// Frees all memory allocated in an LSP map
void
FreeLspMap(
    LSP_ENTRY *pLspMap,
    int iLspCount
    );

// Removes all references to catalog IDs beloging to a removed LSP from the LSP map
void
PruneLspMap(
    LSP_ENTRY *pLspMap, 
    int iLspCount, 
    DWORD *pdwRemovedProviders, 
    int iRemoveCount
    );

// Replaces all references to an catalog ID with the new ID in the LSP map
void
UpdateLspMap(
    LSP_ENTRY *pLspMap,
    int iLspCount,
    DWORD dwOldValue,
    DWORD dwNewValue,
    DWORD *pdwCatalogOrder,
    int iProviderCount
    );

// Returns an array of all provider structures installed under the given GUID
WSAPROTOCOL_INFOW *
GetLayeredEntriesByGuid(
    WSAPROTOCOL_INFOW *pEntries, 
    int iEntryCount,
    GUID *MatchGuid, 
    int *iLayeredCount
    );

// Maps newly reinstalled providers back to the old provider structure
void
MapNewEntriesToOld(
    LSP_ENTRY *pEntry, 
    WSAPROTOCOL_INFOW *pProvider, 
    int iProviderCount
    );

// Compares whether two provider structures are equal (except for name and catalog ID)
BOOL
IsEqualProtocolEntries(
    WSAPROTOCOL_INFOW *pInfo1,
    WSAPROTOCOL_INFOW *pInfo2
    );

//
// Function: main
//
// Description:
//    Parse the command line arguments and call either the install or remove
//    routine.
//
int _cdecl main(int argc, char *argv[])
{
    WSADATA             wsd;
    LPWSAPROTOCOL_INFOW pProtocolInfo   = NULL,
                        pDummyEntry     = NULL,
                        pLayeredEntries = NULL;
    WINSOCK_CATALOG     eCatalog        = LspCatalog32Only;
    INT                 iTotalProtocols = 0;
    DWORD               pdwCatalogIdArray[MAX_PROVIDERS],
                        dwCatalogIdArrayCount = 0,       // How many to install over
                        dwRemoveCatalogId;
    BOOL                bInstall                   = TRUE,
                        bInstallOverAll            = FALSE,
                        bRemoveAllLayeredEntries   = FALSE,
                        bPrintProviders            = FALSE,
                        bDisplayOnlyLayeredEntries = FALSE,
                        bVerbose                   = FALSE,
                        bMapLsp                    = FALSE;
    WCHAR               wszLspName[WSAPROTOCOL_LEN];
    char               *lpszLspName=NULL;
    int                 rc, i;
    LSP_ENTRY          *pLspMap=NULL;
    int                 iLspCount=0;

    // Load Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
    {
        fprintf(stderr, "Unable to load Winsock: %d\n", GetLastError());
        return -1;
    }

    // Parse the command line
    for(i=1; i < argc ;i++)
    {
        if ( (strlen(argv[i]) != 2) && (argv[i][0] != '-') && (argv[i][0] != '/') )
        {
            usage(argv[0]);
        }
        switch (tolower(argv[i][1]))
        {
            case 'a':               // Install LSP over all currently installed providers
                bInstallOverAll = TRUE;
                break;
            case 'c':               // For 64-bit: which catalog to operate on?
                if (i+1 >= argc)
                    usage(argv[0]);
                switch (tolower(argv[i+1][0]))
                {
                    case 'b':       // Both Winsock catalogs
                        eCatalog = LspCatalogBoth;
                        break;
                    case '6':       // 64-bit Winsock catalog only
                        eCatalog = LspCatalog64Only;
                        break;
                    case '3':       // 32-bit Winsock catalog only
                        eCatalog = LspCatalog32Only;
                        break;
                    default:
                        usage(argv[0]);
                        break;
                }
                i++;
                break;
            case 'f':               // Uninstall all layered providers
                bRemoveAllLayeredEntries = TRUE;
                bInstall = FALSE;
                break;
            case 'i':               // install
                bInstall = TRUE;
                break;
            case 'l':               // print the layered providers only
                bPrintProviders = TRUE;
                bDisplayOnlyLayeredEntries = TRUE;
                break;
            case 'm':               // Map and print the LSP structure
                bMapLsp = TRUE;
                bInstall = FALSE;
                break;
            case 'n':               // name of the LSP to install (not the DLL name)
                if (i+1 >= argc)
                    usage(argv[0]);
                lpszLspName = argv[++i];
                break;
            case 'o':               // catalog id (to install over)
                if (i+1 >= argc)
                    usage(argv[0]);
                if (dwCatalogIdArrayCount < MAX_PROVIDERS)
                    pdwCatalogIdArray[dwCatalogIdArrayCount++] = atoi(argv[++i]);
                else
                    printf("Maximum providers exceeded! Ignoring provider %d\n",
                        atoi(argv[++i]));
                break;
            case 'p':               // print the catalog
                bPrintProviders = TRUE;
                bDisplayOnlyLayeredEntries = FALSE;
                break;
            case 'r':               // remove
                bInstall = FALSE;
                if (i+1 >= argc)
                    usage(argv[0]);
                dwRemoveCatalogId = atol(argv[++i]);
                break;
            case 'v':               // verbose mode (when printing with -p option)
                bVerbose = TRUE;
                break;
            default:
                usage(argv[0]);
                break;
        }
    }

#ifndef _WIN64
    if (eCatalog == LspCatalog64Only)
    {
        fprintf(stderr, "\n\nUnable to manipulate 64-bit Winsock catalog from 32-bit process!\n\n");
        return -1;
    }
#endif

    if (bPrintProviders)
    {
        // Print the 32-bit catalog
        if ((eCatalog == LspCatalogBoth) || (eCatalog == LspCatalog32Only))
        {
            printf("\n\nWinsock 32-bit Catalog:\n");
            printf("=======================\n");
            PrintProviders(LspCatalog32Only, bDisplayOnlyLayeredEntries, bVerbose);
        }
        // Print the 64-bit catalog
        if ((eCatalog == LspCatalogBoth) || (eCatalog == LspCatalog64Only))
        {
            printf("\n\nWinsock 64-bit Catalog:\n");
            printf("=======================\n");
            PrintProviders(LspCatalog64Only, bDisplayOnlyLayeredEntries, bVerbose);
        }
    }
    else if (bInstall)
    {
        GUID    ProviderChainGuid;
        DWORD   dwLayeredId;

        //
        // Install the LSP over the given entries. If selected to install over all
        // entries, then enumerate the catalog to obtain all the available providers.
        //

        if (lpszLspName == NULL)
        {
            lpszLspName = DEFAULT_LSP_NAME;
        }

        // Convert the LSP name to UNICODE since the Winsock catalog is all UNICODE
        rc = MultiByteToWideChar(
                CP_ACP, 
                0, 
                lpszLspName, 
                strlen(lpszLspName)+1,
                wszLspName, 
                WSAPROTOCOL_LEN 
                );
        if (rc == 0)
        {
            fprintf(stderr, "MultiByteToWideChar failed to convert '%s'; Error = %d\n",
                lpszLspName, GetLastError());
            goto cleanup;
        }

        if (bInstallOverAll)
        {
            // Make sure user didn't specify '-a' and '-o' flags
            if (dwCatalogIdArrayCount != 0)
            {
                fprintf(stderr, "\n\nError! Cannot specify both '-a' and '-o' flags!\n\n");
                goto cleanup;
            }

            // Enumerate the appropriate catalog we will be working on
            pProtocolInfo = EnumerateProviders(eCatalog, &iTotalProtocols);
            if (pProtocolInfo == NULL)
            {
                fprintf(stderr, "EnumerateProviders: Unable to enumerate Winsock catalog\n");
                goto cleanup;
            }
        
            // Get the catalog IDs for all existing providers
            for(i=0; i < iTotalProtocols ;i++)
            {
                if (pProtocolInfo[i].ProtocolChain.ChainLen != LAYERED_PROTOCOL)
                {
                    if (dwCatalogIdArrayCount < MAX_PROVIDERS)
                        pdwCatalogIdArray[dwCatalogIdArrayCount++] = pProtocolInfo[i].dwCatalogEntryId;
                    else
                        printf("Maximum providers exceeded! Ignoring provider %d\n",
                                pProtocolInfo[i].dwCatalogEntryId);
                }
            }

            FreeProviders(pProtocolInfo);
            pProtocolInfo = NULL;
        }

        // Make sure we have at least one provider to install over
        if (dwCatalogIdArrayCount == 0)
        {
            fprintf(stderr, "\n\nError! Must specify at least one provider to layer over!\n\n");
            goto cleanup;
        }

        printf("LSP name is '%S'\n", wszLspName);

        // Create the 'dummy' protocol entry
        pDummyEntry = CreateDummyEntry(eCatalog, pdwCatalogIdArray[0], wszLspName);
        if (pDummyEntry == NULL)
        {
            fprintf(stderr, "CreateDummyEntry failed!\n");
            goto cleanup;
        }

        // 'ProviderGuid' is the GUID for the dummy entry defined in lspguid.cpp

        //
        // NOTE: If you want to create multiple LSPs to install over each other
        //       you have to modify 2 files: lspguid.cpp and lsp.def. In lspguid.cpp
        //       you need to change to GUID to something unique and change the LSP
        //       name (e.g. lsp2.dll) and rebuild. The lsp.def file only needs the
        //       DLL name updated. Also note that the new instlsp.exe
        //       generated will only install lsp2.dll so keep it seperate from the
        //       original lsp.dll and instlsp.exe normally generated.
        //

        // Install the 'dummy' protocol entry for the LSP
        rc = InstallProvider(eCatalog, &ProviderGuid, ProviderPath, pDummyEntry, 1);
        if (rc != NO_ERROR)
        {
            fprintf(stderr, "Unable to install the dummy LSP entry!\n");
            goto cleanup;
        }

        // Don't need this struture any more
        HeapFree(GetProcessHeap(), 0, pDummyEntry);
        pDummyEntry = NULL;

        // Create the layered chain entries
        pLayeredEntries = CreateLayeredEntries(eCatalog, wszLspName, &ProviderGuid, pdwCatalogIdArray, dwCatalogIdArrayCount, &dwLayeredId);
        if (pLayeredEntries == NULL)
        {
            fprintf(stderr, "Unable to create layered provider entries!\n");
            goto cleanup;
        }

        // Create a GUID for the protocol chain entries
        if (UuidCreate(&ProviderChainGuid) != RPC_S_OK)
        {
            fprintf(stderr, "UuidCreate failed: %d\n", GetLastError());
            goto cleanup;
        }

        // Install the layered chain providers
        rc = InstallProvider(eCatalog, &ProviderChainGuid, ProviderPath, pLayeredEntries, dwCatalogIdArrayCount);
        if (rc != NO_ERROR)
        {
            fprintf(stderr, "Unable to install layered chain entries!\n");
            goto cleanup;
        }

        // Reorder the winsock catalog so the layered chain entries appear first
        rc = ReorderCatalog(eCatalog, dwLayeredId);
        if (rc != NO_ERROR)
        {
            fprintf(stderr, "Unable to reorder Winsock catalog!\n");
            goto cleanup;
        }

        HeapFree(GetProcessHeap(), 0, pLayeredEntries);
        pLayeredEntries = NULL;
    }
    else if (bMapLsp)
    {
        // Display the 32-bit LSP catalog map
        if ((eCatalog == LspCatalogBoth) || (eCatalog == LspCatalog32Only))
        {
            printf("\n32-bit Winsock LSP Map:\n\n");

            pProtocolInfo = EnumerateProviders(LspCatalog32Only, &iTotalProtocols);
            if (pProtocolInfo == NULL)
            {
                fprintf(stderr, "EnumerateProviders: Unable to enumerate Winsock catalog\n");
                goto cleanup;
            }

            pLspMap = BuildLspMap(pProtocolInfo, iTotalProtocols, &iLspCount);
            if (pLspMap != NULL)
            {
                PrintLspMap(pLspMap, iLspCount);

                FreeLspMap(pLspMap, iLspCount);
                pLspMap = NULL;
            }
            else
            {
                printf("\nNo LSPs installed\n\n");
            }
            FreeProviders(pProtocolInfo);
            pProtocolInfo = NULL;
        }
        // Display the 64-bit LSP catalog map
        if ((eCatalog == LspCatalogBoth) || (eCatalog == LspCatalog64Only))
        {
            printf("\n64-bit Winsock LSP Map:\n\n");

            pProtocolInfo = EnumerateProviders(LspCatalog64Only, &iTotalProtocols);
            if (pProtocolInfo == NULL)
            {
                fprintf(stderr, "main: EnumerateProviders: Unable to enumerate Winsock catalog\n");
                goto cleanup;
            }

            pLspMap = BuildLspMap(pProtocolInfo, iTotalProtocols, &iLspCount);
            if (pLspMap != NULL)
            {
                PrintLspMap(pLspMap, iLspCount);

                FreeLspMap(pLspMap, iLspCount);
                pLspMap = NULL;
            }
            else
            {
                printf("\nNo LSPs installed\n\n");
            }
            FreeProviders(pProtocolInfo);
            pProtocolInfo = NULL;
        }
    }
    else
    {
        if (bRemoveAllLayeredEntries == TRUE)
        {
            if ((eCatalog == LspCatalogBoth) || (eCatalog == LspCatalog32Only))
                RemoveAllLayeredEntries(LspCatalog32Only);

            if ((eCatalog == LspCatalogBoth) || (eCatalog == LspCatalog64Only))
                RemoveAllLayeredEntries(LspCatalog64Only);
        }
        else
        {
            //
            // See if we're on a platform that supports WSCUpdateProvider. If so then
            // uninstalling an LSP is easy; otherwise, it is very painful if you're
            // removing an LSP that has other LSPs on top if it.
            //
            hModule = LoadLibraryA("ws2_32.dll");
            if (hModule == NULL)
            {
                fprintf(stderr, "main: Unable to load ws2_32.dll: %d\n", GetLastError());
                goto cleanup;
            }
            else
            {
                fnWscUpdateProvider = (LPWSCUPDATEPROVIDER)GetProcAddress(hModule, "WSCUpdateProvider");

                if ((eCatalog == LspCatalogBoth) || (eCatalog == LspCatalog32Only))
                    RemoveProvider(LspCatalog32Only, dwRemoveCatalogId);

                if ((eCatalog == LspCatalogBoth) || (eCatalog == LspCatalog64Only))
                    RemoveProvider(LspCatalog64Only, dwRemoveCatalogId);

                FreeLibrary(hModule);
                hModule = NULL;
            }

        }
    }

cleanup:

    //
    // Free any dynamic allocations and/or handles
    //

    if (pLayeredEntries)
        HeapFree(GetProcessHeap(), 0, pLayeredEntries);

    if (pDummyEntry)
        HeapFree(GetProcessHeap(), 0, pDummyEntry);

    if (pProtocolInfo)
        FreeProviders(pProtocolInfo);

    if (hModule != NULL)
        FreeLibrary(hModule);

    if (pLspMap)
        FreeLspMap(pLspMap, iLspCount);

    WSACleanup();
    return 0;
}

//
// Function: usage
//
// Description:
//    Prints usage information.
//
void usage(char *progname)
{
    printf("usage: %s -i -r [CatId] -o [CatId] -p\n", progname);
    printf(
           "       -a           Install over all providers (base or layered)\n"
           "                       Cannot be combined with '-o' option\n"
           "       -c Catalog   Indicates which catalog to operate on\n"
           "          b            Both 64-bit and 32-bit Winsock catalogs\n"
           "          6            64-bit Winsock catalog only\n"
           "          3            32-bit Winsock catalog only\n"
           "       -i           Install LSP\n"
           "       -f           Remove all layered entries\n"
           "       -l           Print layered providers only\n"
           "       -m           Display a map of the LSPs and the order they are\n"
           "                       installed in\n"
           "       -n Str       Name of LSP\n"
           "       -o CatId     Install over specified LSP\n"
           "                       This option may be specified multiple times\n"
           "                       Cannot be combined with '-a' option\n"
           "       -p           Print all layers and their catalog IDs\n"
           "       -r CatId     Remove LSP\n"
           "       -v           Print verbose catalog information (used with -p)\n"
           );
    ExitProcess(-1);
}

//
// Function: PrintProviders
//
// Description: 
//    This function prints out each entry in the Winsock catalog and its
//    catalog ID if the parameter, bLayeredOnly, is FALSE. If TRUE then
//    print only those layered catalog entries.
//
void PrintProviders(WINSOCK_CATALOG Catalog, BOOL bLayeredOnly, BOOL bVerbose)
{
    WSAPROTOCOL_INFOW  *pProtocolInfo=NULL;
    INT                 iProtocolCount=0,
                        i;

	pProtocolInfo = EnumerateProviders(Catalog, &iProtocolCount);
    if (pProtocolInfo == NULL)
    {
        return;
    }
    for(i=0; i < iProtocolCount ;i++)
    {
        if (!bLayeredOnly)
        {
            if (bVerbose)
                PrintProtocolInfo(&pProtocolInfo[i]);
            else
                printf("%04d - %S\n", pProtocolInfo[i].dwCatalogEntryId,
                      pProtocolInfo[i].szProtocol);
        }
        else if (pProtocolInfo[i].ProtocolChain.ChainLen == LAYERED_PROTOCOL)
        {
            if (bVerbose)
                PrintProtocolInfo(&pProtocolInfo[i]);
            else
                printf("%04d - %S\n", pProtocolInfo[i].dwCatalogEntryId,
                      pProtocolInfo[i].szProtocol);
        }
    }
    FreeProviders(pProtocolInfo);

    return;
}

//
// Function: CreateDummyEntry
//
// Description:
//    This creates a single WSAPROTOCOL_INFOW structure which describes the
//    hidden "dummy" entry for an LSP. This is required since the layered
//    chain entries must reference the catalog ID of the LSP and a catalog ID
//    cannot be obtained until an entry is installed.
//
WSAPROTOCOL_INFOW *
CreateDummyEntry(
    WINSOCK_CATALOG Catalog, 
    INT CatalogId, 
    WCHAR *lpwszLspName
    )
{
    WSAPROTOCOL_INFOW *pProtocolInfo=NULL,
                      *pDummyEntry=NULL;
    INT                iProtocolCount=0;
    int                i;

    // Enumerate the catalog
    pProtocolInfo = EnumerateProviders(Catalog, &iProtocolCount);
    if (pProtocolInfo == NULL)
    {
        fprintf(stderr, "CreateDummyEntry: EnumerateProviders failed!\n");
        return NULL;
    }

    // Find one of the providers we are layering over
    for(i=0; i < iProtocolCount ;i++)
    {
        if (pProtocolInfo[i].dwCatalogEntryId == CatalogId)
        {
            // Allocate space and copy the provider structure
            pDummyEntry = (WSAPROTOCOL_INFOW *)HeapAlloc(GetProcessHeap(), 0, sizeof(WSAPROTOCOL_INFOW));
            if (pDummyEntry == NULL)
            {
                return NULL;
            }

            // Copy the entry as a basis for the dummy entry
            memcpy(pDummyEntry, &pProtocolInfo[i], sizeof(WSAPROTOCOL_INFOW));

            break;
        }
    }

    // Verify we found a provider
    if (pDummyEntry == NULL)
    {
        fprintf(stderr, "\n\nError! Unable to find provider with ID of %d\n\n",
                CatalogId);
        return NULL;
    }

    // Remove the flag indicating IFS support (as our LSP does not provide IFS handles)
    pDummyEntry->dwServiceFlags1 &= (~XP1_IFS_HANDLES);
    // Set the flags indicating this is a hidden ("dummy") entry
    pDummyEntry->dwProviderFlags |= PFL_HIDDEN;
    pDummyEntry->ProtocolChain.ChainLen = LAYERED_PROTOCOL;

    // Copy the LSP name
    wcsncpy(pDummyEntry->szProtocol, lpwszLspName, WSAPROTOCOL_LEN);

    FreeProviders(pProtocolInfo);

    return pDummyEntry;
}

//
// Function: CreateLayeredEntries
//
// Description:
//    This finds all the providers the LSP is layering over and builds
//    the layered chain entries which make up the LSP. This routine 
//    returns the catalog ID of the LSP's dummy entry (because it is
//    needed to reorder the catlog after the chain entries are installed).
//
WSAPROTOCOL_INFOW * 
CreateLayeredEntries(
    WINSOCK_CATALOG Catalog,        // Which catalog are we operating on
    WCHAR *lpwszLspName,            // Name of the LSP
    GUID *Guid,                     // GUID that the LSP's dummy entry was installed under
    DWORD *pdwIdArray,              // Array of catalog IDs we're layering over
    INT iIdArrayCount,              // Number of entries in array
    DWORD *LayeredId                // [OUT] Returns the catalog ID of dummy entry
    )
{
    WSAPROTOCOL_INFOW   *pProvider=NULL,
                        *pLayeredEntries=NULL;
    DWORD                LayeredCatalogId=0;
    INT                  iProviderCount=0,
                         idx,
                         i, j, k;

    if (LayeredId == NULL)
        return NULL;

    // Enumerate the catalog
    pProvider = EnumerateProviders(Catalog, &iProviderCount);
    if (pProvider == NULL)
    {
        return NULL;
    }

    // Find the dummy entry so we can extract its catalog ID
    for(i=0; i < iProviderCount ;i++)
    {
        if (memcmp(&pProvider[i].ProviderId, Guid, sizeof(GUID)) == 0)
        {
            LayeredCatalogId = pProvider[i].dwCatalogEntryId;
            break;
        }
    }

    // Make sure we found the dummy provider
    if (LayeredCatalogId == 0)
    {
        fprintf(stderr, "CreateLayeredEntries: Unable to find dummy provider in catalog!\n");
        FreeProviders(pProvider);
        return NULL;
    }

    // Allocate space for our layered entries
    pLayeredEntries = (WSAPROTOCOL_INFOW *)HeapAlloc(GetProcessHeap(), 0, sizeof(WSAPROTOCOL_INFOW) * iIdArrayCount);
    if (pLayeredEntries == NULL)
    {
        fprintf(stderr, "CreateLayeredEntries: HeapAlloc failed: %d\n", GetLastError());
        FreeProviders(pProvider);
        return NULL;
    }

    // Go through the catalog and build the layered entries
    idx = 0;
    for(i=0; i < iProviderCount ;i++)
    {
        for(j=0; j < iIdArrayCount ;j++)
        {
            if (pProvider[i].dwCatalogEntryId == pdwIdArray[j])
            {
                memcpy(&pLayeredEntries[idx], &pProvider[i], sizeof(WSAPROTOCOL_INFOW));

                // Put our LSP name in the protocol field
                _snwprintf(pLayeredEntries[idx].szProtocol, WSAPROTOCOL_LEN,
                        L"%s over [%s]",
                        lpwszLspName,
                        pProvider[i].szProtocol
                        );

                // Move all the protocol chain entries down by 1 position
                for(k = pProvider[i].ProtocolChain.ChainLen; k > 0 ;k--)
                {
                    pLayeredEntries[idx].ProtocolChain.ChainEntries[k] = pProvider[i].ProtocolChain.ChainEntries[k-1];
                }

                // The second entry is always the ID of the current pProvider[i]
                //     In case of multiple LSPs then if we didn't do this the [1] index
                //     would contain the ID of that LSP's dummy entry and not the entry
                //     itself.
                pLayeredEntries[idx].ProtocolChain.ChainEntries[1] = pProvider[i].dwCatalogEntryId;

                // Insert our LSP in the chain and increment the count
                pLayeredEntries[idx].ProtocolChain.ChainEntries[0] = LayeredCatalogId;
                pLayeredEntries[idx].ProtocolChain.ChainLen++;

                // Again, this LSP doesn't provide true IFS handles so remove the flag
                pLayeredEntries[idx].dwServiceFlags1 &= (~XP1_IFS_HANDLES);

                idx++;
            }
        }
    }

    FreeProviders(pProvider);

    // Return the ID of the LSP's dummy entry
    *LayeredId = LayeredCatalogId;
    
    return pLayeredEntries;
}

//
// Function: InstallProvider
//
// Description:
//    This is a wrapper for the WSCInstallProvider function. Depending on
//    which catalog is specified, this routine calls the correct install
//    routine.
//
int 
InstallProvider(
    WINSOCK_CATALOG Catalog,            // Which catalog are we operating on
    GUID *Guid,                         // GUID under which provider will be installed
    WCHAR *lpwszLspPath,                // Path to LSP's DLL
    WSAPROTOCOL_INFOW *pProvider,       // Array of provider structures to install
    INT iProviderCount                  // Number of providers in array
    )
{
    WSAPROTOCOL_INFOW *pEnumProviders=NULL;
    INT                iEnumProviderCount,
                       ErrorCode,
                       rc, i;

#ifdef _WIN64
    if (Catalog == LspCatalog32Only)
    {
        // Can't install only in 32-bit catalog from 64-bit
        fprintf(stderr, "\n\nError! It is not possible to install only in 32-bit catalog from 64-bit process!\n\n");
        return SOCKET_ERROR;
    }
    else if (Catalog == LspCatalog64Only)
    {
        // Just need to call WSCInstallProvider
        rc = WSCInstallProvider(Guid, lpwszLspPath, pProvider, iProviderCount, &ErrorCode);
    }
    else
    {
        // To install in both we must call WSCInstallProviderPath64_32
        rc = WSCInstallProvider64_32(Guid, lpwszLspPath, pProvider, iProviderCount, &ErrorCode);
    }
#else
    if (Catalog == LspCatalog32Only)
    {
        // From a 32-bit process we can only install into 32-bit catalog
        rc = WSCInstallProvider(Guid, lpwszLspPath, pProvider, iProviderCount, &ErrorCode);
    }
    else
    {
        // From a 32-bit process, we can't touch the 64-bit catalog at all
        fprintf(stderr, "\n\nError! It is not possible to install into the 64-bit catalog from a 32-bit process!\n\n");
        return SOCKET_ERROR;
    }
#endif
    if (rc == SOCKET_ERROR)
    {
        fprintf(stderr, "InstallProvider: WSCInstallProvider* failed: %d\n", ErrorCode);
    }

    // Go back and enumerate what we just installed
    pEnumProviders = EnumerateProviders(Catalog, &iEnumProviderCount);
    if (pEnumProviders != NULL)
    {
        for(i=0; i < iEnumProviderCount ;i++)
        {
            if (memcmp(&pEnumProviders[i].ProviderId, Guid, sizeof(GUID)) == 0)
            {
                printf("Installed: [%4d] %S\n", pEnumProviders[i].dwCatalogEntryId,
                    pEnumProviders[i].szProtocol);
            }
        }
        FreeProviders(pEnumProviders);
    }

    return rc;
}

//
// Function: DeinstallProvider
//
// Description:
//    This is a wrapper for the WSCDeinstallProvider* functions. Depending on
//    which Winsock catalog is specified, this routine calls the right uninstall
//    function.
//
int 
DeinstallProvider(
    WINSOCK_CATALOG Catalog,            // Which Winsock catalog to operate on
    GUID *Guid                          // GUID of provider to remove
    )
{
    INT     ErrorCode,
            rc;

#ifdef _WIN64
    if (Catalog == LspCatalogBoth)
    {
        // Remove from 64-bit catalog
        rc = WSCDeinstallProvider(Guid, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            if (ErrorCode != WSAEFAULT)
                fprintf(stderr, "DeinstallProvider: WSCDeinstallProvider failed: %d\n", ErrorCode);
        }

        // Remove from the 32-bit catalog
        rc = WSCDeinstallProvider32(Guid, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            if (ErrorCode != WSAEFAULT)
                fprintf(stderr, "DeinstallProvider: WSCDeinstallProvider32 failed: %d\n", ErrorCode);
        }
    }
    else if (Catalog == LspCatalog64Only)
    {
        // Remove from 64-bit catalog
        rc = WSCDeinstallProvider(Guid, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            if (ErrorCode != WSAEFAULT)
                fprintf(stderr, "DeinstallProvider: WSCDeinstallProvider failed: %d\n", ErrorCode);
        }
    }
    else
    {
        // Remove from the 32-bit catalog
        rc = WSCDeinstallProvider32(Guid, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            if (ErrorCode != WSAEFAULT)
                fprintf(stderr, "DeinstallProvider: WSCDeinstallProvider32 failed: %d\n", ErrorCode);
        }
    }
#else
    if (Catalog == LspCatalog32Only)
    {
        // Remove from the 32-bit catalog
        rc = WSCDeinstallProvider(Guid, &ErrorCode);
        if (rc == SOCKET_ERROR)
        {
            if (ErrorCode != WSAEFAULT)
                fprintf(stderr, "DeinstallProvider: WSCDeinstallProvider failed: %d\n", ErrorCode);
        }
    }
    else
    {
        fprintf(stderr, "Unable to remove providers in 64-bit catalog from 32-bit process!\n");
        return SOCKET_ERROR;
    }
#endif

    return NO_ERROR;
}

//
// Function: ReorderACatalog
//
// Description:
//    This routine enumerates a single catalog (32 or 64 bit) and reorders
//    the catalog according to the supplied catalog ID. That is, any provider
//    with that ID at the head of it's protocol chain is moved to the beginning
//    of the catalog.
//
DWORD *
ReorderACatalog(
    WINSOCK_CATALOG Catalog,
    DWORD   dwLayerId,
    INT   *dwEntryCount
    )
{
    WSAPROTOCOL_INFOW   *pProvider=NULL;
    DWORD               *pdwProtocolOrder=NULL;
    INT                  iProviderCount,
                         idx,
                         i;

    // Validate parameters
    if ((dwEntryCount == NULL) || (Catalog == LspCatalogBoth))
        return NULL;

    // Enumerate the catalog
    pProvider = EnumerateProviders(Catalog, &iProviderCount);
    if (pProvider == NULL)
    {
        fprintf(stderr, "ReorderACatalog: Unable to enumerate Winsock catalog!\n");
        goto cleanup;
    }

    // Allocate space for the array of catalog IDs (the catalog order)
    pdwProtocolOrder = (DWORD *)HeapAlloc(GetProcessHeap(), 0, sizeof(DWORD) * iProviderCount);
    if (pdwProtocolOrder == NULL)
    {
        fprintf(stderr, "ReorderACatalog: HeapAlloc failed: %d\n", GetLastError());
        goto cleanup;
    }

    idx = 0;

    // First put all the layered entries at the head of the catalog
    for(i=0; i < iProviderCount ;i++)
    {
        if (IsIdInChain(&pProvider[i], dwLayerId) == TRUE)
        {
            pdwProtocolOrder[idx++] = pProvider[i].dwCatalogEntryId;
        }
    }

    // Put the remaining entries after the layered chain entries
    for(i=0; i < iProviderCount ;i++)
    {
        if (IsIdInChain(&pProvider[i], dwLayerId) == FALSE)
        {
            pdwProtocolOrder[idx++] = pProvider[i].dwCatalogEntryId;
        }
    }

cleanup:

    if (pProvider)
        FreeProviders(pProvider);

    // Update the count
    *dwEntryCount = iProviderCount;


    return pdwProtocolOrder;
}

//
// Function: ReorderCatalog
//
// Description:
//    This routine reorders the Winsock catalog such that those entries
//    which reference the given catalog ID (dwLayerId) as the first entry
//    in the chain array occur at the head of the catalog. This routine
//    also operates on the specified Winsock catalog.
//
int ReorderCatalog(WINSOCK_CATALOG Catalog, DWORD dwLayeredId)
{
    DWORD     *pdwProtocolOrder;
    INT        iProviderCount,
               rc;

    rc = NO_ERROR;
#ifdef _WIN64
    if ((Catalog == LspCatalog32Only) || (Catalog == LspCatalogBoth))
    {
        printf("Reordering 32-bit Winsock catalog...\n");
        pdwProtocolOrder = ReorderACatalog(LspCatalog32Only, dwLayeredId, &iProviderCount);
        if (pdwProtocolOrder == NULL)
        {
            fprintf(stderr, "ReorderCatalog: ReorderACatalog failed!\n");
        }
        else
        {
            rc = WSCWriteProviderOrder32(pdwProtocolOrder, iProviderCount);
            if (rc == SOCKET_ERROR)
            {
                fprintf(stderr, "ReorderCatalog: WSCWriteProviderOrder32 failed: %d\n", rc);
            }

            HeapFree(GetProcessHeap(), 0, pdwProtocolOrder);
            pdwProtocolOrder = NULL;
        }
    }
    if ((Catalog == LspCatalog64Only) || (Catalog == LspCatalogBoth))
    {
        printf("Reordering 64-bit Winsock catalog...\n");
        pdwProtocolOrder = ReorderACatalog(LspCatalog64Only, dwLayeredId, &iProviderCount);
        if (pdwProtocolOrder == NULL)
        {
            fprintf(stderr, "ReorderCatalog: ReorderACatalog failed!\n");
        }
        else
        {
            rc = WSCWriteProviderOrder(pdwProtocolOrder, iProviderCount);
            if (rc == SOCKET_ERROR)
            {
                fprintf(stderr, "ReorderCatalog: WSCWriteProviderOrder failed: %d\n", rc);
            }

            HeapFree(GetProcessHeap(), 0, pdwProtocolOrder);
            pdwProtocolOrder = NULL;
        }
    }
#else
    if ((Catalog == LspCatalog32Only) || (Catalog == LspCatalogBoth))
    {
        printf("Reordering 32-bit Winsock catalog...\n");
        pdwProtocolOrder = ReorderACatalog(LspCatalog32Only, dwLayeredId, &iProviderCount);
        if (pdwProtocolOrder == NULL)
        {
            fprintf(stderr, "ReorderCatalog: ReorderACatalog failed!\n");
        }
        else
        {
            rc = WSCWriteProviderOrder(pdwProtocolOrder, iProviderCount);
            if (rc == SOCKET_ERROR)
            {
                fprintf(stderr, "ReorderCatalog: WSCWriteProviderOrder failed: %d\n", rc);
            }

            HeapFree(GetProcessHeap(), 0, pdwProtocolOrder);
            pdwProtocolOrder = NULL;
        }
    }
#endif

    return rc;
}

//
// Function: RemoveIdFromChain
//
// Description:
//    This function removes the given CatalogId from the protocol chain 
//    for pinfo.
//
int RemoveIdFromChain(WSAPROTOCOL_INFOW *pinfo, DWORD CatalogId)
{
    int     i, j;

    for(i=0; i < pinfo->ProtocolChain.ChainLen ;i++)
    {
        if (pinfo->ProtocolChain.ChainEntries[i] == CatalogId)
        {
            for(j=i; j < pinfo->ProtocolChain.ChainLen-1 ; j++)
            {
                pinfo->ProtocolChain.ChainEntries[j] = pinfo->ProtocolChain.ChainEntries[j+1];
            }
            pinfo->ProtocolChain.ChainLen--;
            return 0;
        }
    }
    return 1;
}

//
// Function: IsIdinChain
//
// Description:
//    This function determines whether the given catalog id is referenced
//    in the protocol chain of pinfo.
//
BOOL IsIdInChain(WSAPROTOCOL_INFOW *pinfo, DWORD Id)
{
    for(int i=0; i < pinfo->ProtocolChain.ChainLen ;i++)
    {
        if (pinfo->ProtocolChain.ChainEntries[i] == Id)
            return TRUE;
    }
    return FALSE;
}

//
// Function: RemoveProvider
//
// Description:
//    This function removes a layered provider. Things can get tricky if
//    we're removing a layered provider which has been layered over by 
//    another provider.
//
int RemoveProvider(WINSOCK_CATALOG Catalog, DWORD dwProviderId)
{
    WSAPROTOCOL_INFOW   *pProvider=NULL,
                        *pLayeredEntries=NULL;
    LSP_ENTRY           *pLspMap=NULL;
    DWORD               *pdwRemovedProviders=NULL,
                        *pdwCatalogOrder=NULL;
    INT                  iOriginalProviderCount=0,
                         iProviderCount=0,
                         iRemoveCount=0,
                         iLayerCount=0,
                         iLspCount=0,
                         ErrorCode,
                         Status,
                         rc, 
                         i, j;
    WCHAR                wszProviderPath[DEFAULT_PATH_LEN];
    INT                  iProviderPathLen=DEFAULT_PATH_LEN-1;

    Status = NO_ERROR;

    // Enumerate the catalog
    pProvider = EnumerateProviders(Catalog, &iProviderCount);
    if (pProvider == NULL)
    {
        fprintf(stderr, "RemoveProvider: Unable to enumerate catalog!\n");
        Status = SOCKET_ERROR;
        goto cleanup;
    }

    // Make sure this is a layered provider ID
    for(i=0; i < iProviderCount ;i++)
    {
        if ((pProvider[i].dwCatalogEntryId == dwProviderId) && 
            (pProvider[i].ProtocolChain.ChainLen == BASE_PROTOCOL))
        {
            fprintf(stderr, "\n\nError! Attempting to remove base provider: %S\n\n",
                pProvider[i].szProtocol);
            Status = SOCKET_ERROR;
            goto cleanup;
        }
    }

    // First count how many entries directly belong to this provider
    iRemoveCount = 0;
    for(i=0; i < iProviderCount ;i++)
    {
        if (((pProvider[i].ProtocolChain.ChainLen > 0) &&
             (pProvider[i].ProtocolChain.ChainEntries[0] == dwProviderId) ) ||
             (pProvider[i].dwCatalogEntryId == dwProviderId))
        {
            iRemoveCount++;
        }
    }

    // Save off the catalog entry IDs of the removed providers
    pdwRemovedProviders = (DWORD *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, iRemoveCount * sizeof(DWORD));
    if (pdwRemovedProviders == NULL)
    {
        fprintf(stderr, "\n\nError! HeapAlloc failed: %d\n", GetLastError());
        Status = SOCKET_ERROR;
        goto cleanup;
    }

    iRemoveCount = 0;

    // Uninstall the LSP dummy and chain entries
    for(i=0; i < iProviderCount ;i++)
    {
        if (((pProvider[i].ProtocolChain.ChainLen > 0) &&
             (pProvider[i].ProtocolChain.ChainEntries[0] == dwProviderId) ) || 
            (pProvider[i].dwCatalogEntryId == dwProviderId))
        {
            // Save removed catalog entry ID
            pdwRemovedProviders[iRemoveCount++] = pProvider[i].dwCatalogEntryId;

            // Display message and actually remove the provider
            printf("Removing: [%4d] %S\n", pProvider[i].dwCatalogEntryId,
                pProvider[i].szProtocol);
            DeinstallProvider(Catalog, &pProvider[i].ProviderId);
        }
    }

    // Enumerate the catalog again -- we may need to do more cleanup
    FreeProviders(pProvider);

    pProvider = EnumerateProviders(Catalog, &iProviderCount);
    if (pProvider == NULL)
    {
        fprintf(stderr, "RemoveProvider: Unable to enumerate Winsock catalog!\n");
        Status = SOCKET_ERROR;
        goto cleanup;
    }

    // If we're on Windows XP then life is easy
    if (fnWscUpdateProvider != NULL)
    {
        for(i=0; i < iProviderCount ;i++)
        {
            for(j=0; j < iRemoveCount ;j++)
            {
                if (IsIdInChain(&pProvider[i], pdwRemovedProviders[j]) == TRUE)
                {
                    // Remove the defunct LSP provider id
                    RemoveIdFromChain(&pProvider[i], pdwRemovedProviders[j]);

                    // Get the path to this provider
                    rc = WSCGetProviderPath(
                            &pProvider[i].ProviderId,
                            wszProviderPath,
                            &iProviderPathLen,
                            &ErrorCode
                            );
                    if (rc == SOCKET_ERROR)
                    {
                        fprintf(stderr, "RemoveProvider: WSCGetProviderPath failed: %d\n",
                                ErrorCode);
                        continue;
                    }

                    // Update it's provider entry
                    rc = fnWscUpdateProvider(
                            &pProvider[i].ProviderId,
                            wszProviderPath,
                            &pProvider[i],
                            1,
                            &ErrorCode
                            );
                    if (rc == SOCKET_ERROR)
                    {
                        fprintf(stderr, "RemoveProvider: WSCUpdateProvider failed: %d\n",
                                ErrorCode);
                    }
                    break;
                }
            }
        }

    }
    else
    {
        BOOL bDependent;

        // First check to see if any other LSPs were layered over ours
        bDependent = FALSE;
        for(i=0; (i < iProviderCount) && (!bDependent) ;i++)
        {
            for(j=0; j < iRemoveCount ;j++)
            {
                if ( IsIdInChain(&pProvider[i], pdwRemovedProviders[j]) )
                {
                    bDependent = TRUE;
                    break;
                }
            }
        }

        if (bDependent == TRUE)
        {
            // Yuck - need to fix up all the dependent providers layered
            // above our LSP. This is a lot more complicated without the
            // WSCUpdateProvider function. The problem is that to change
            // the protocol chains of the providers layered over the
            // removed LSP, you have to uninstall it, modify the chain,
            // and reinstall it. This itself isn't too bad but if there
            // are other LSPs layered over the one just re-installed, it
            // needs to be fixed now (since by re-isntalling the LSP, it
            // gets assigned a different provider ID).

            // In this case we're taking the "easy" way out. We will uninstall
            // ALL LSPs and reinstall them regardless of whether or not
            // they are dependent. Otherwise, the logic for determing which
            // other LSPs are affected by changes gets complicated and would
            // be prone to (more) errors.

            // First save off the catalog order

            // NOTE: iProviderCount is assumed to be an invariant throughout this
            //       process. If someone else is installing LSPs while we're doing
            //       this we'd be in trouble anyway.

            iOriginalProviderCount = iProviderCount;

            pdwCatalogOrder = (DWORD *)HeapAlloc(
                    GetProcessHeap(),
                    HEAP_ZERO_MEMORY,
                    sizeof(DWORD) * iOriginalProviderCount
                    );
            if (pdwCatalogOrder == NULL)
            {
                fprintf(stderr, "RemoveProvider: HeapAlloc failed: %d\n", GetLastError());
                goto cleanup;
            }

            for(i=0; i < iProviderCount ;i++)
            {
                pdwCatalogOrder[i] = pProvider[i].dwCatalogEntryId;
            }

            // Obtain the mapping of the LSP install order
            pLspMap = BuildLspMap(pProvider, iProviderCount, &iLspCount);
            if (pLspMap == NULL)
            {
                fprintf(stderr, "RemoveProvider: BuildLspMap returned NULL!\n");
                goto cleanup;
            }

            // Remove all instances of the removed LSP from the LSP map chains
            PruneLspMap(pLspMap, iLspCount, pdwRemovedProviders, iRemoveCount);

            // First uninstall all the LSPs
            for(i=0; i < iLspCount ;i++)
            {
                // Uninstall the dummy entry
                DeinstallProvider(Catalog, &pLspMap[i].DummyEntry.ProviderId);

                // Uninstall all the associated layered entries
                for(j=0; j < pLspMap[i].LayeredGuidCount ;j++)
                {
                    DeinstallProvider(Catalog, &pLspMap[i].LayeredGuids[j]);
                }
            }

            // No go back and re-install them
            for(i=0; i < iLspCount ;i++)
            {
                rc = InstallProvider(
                        Catalog, 
                       &pLspMap[i].DummyEntry.ProviderId, 
                        pLspMap[i].wszLspDll,
                       &pLspMap[i].DummyEntry, 
                        1
                        );
                if (rc != NO_ERROR)
                {
                    fprintf(stderr, "RemoveProvider: Unable to install dummy provider for %ws; error %d\n",
                        pLspMap[i].DummyEntry.szProtocol,
                        rc
                        );
                    goto cleanup;
                }

                // Enumerate the catalog 
                FreeProviders(pProvider);

                pProvider = EnumerateProviders(Catalog, &iProviderCount);
                if (pProvider == NULL)
                {
                    fprintf(stderr, "RemoveProvider: Unable to enumerate Winsock catalog!\n");
                    Status = SOCKET_ERROR;
                    goto cleanup;
                }

                // Find the new ID for the dummy entry
                for(j=0; j < iProviderCount ;j++)
                {
                    if ( memcmp( &pProvider[j].ProviderId, &pLspMap[i].DummyEntry.ProviderId, sizeof(GUID) ) == 0 )
                    {
                        // Save the new ID
                        pLspMap[i].DummyEntry.dwProviderReserved = pProvider[j].dwCatalogEntryId;
                        break;
                    }
                }

                // Go update all occurences of the old ID with the new ID
                UpdateLspMap(
                    pLspMap, 
                    iLspCount, 
                    pLspMap[i].DummyEntry.dwCatalogEntryId,
                    pLspMap[i].DummyEntry.dwProviderReserved,
                    pdwCatalogOrder,
                    iOriginalProviderCount
                    );

                // Install the layered entries associated with this LSP
                for(j=0; j < pLspMap[i].LayeredGuidCount ;j++)
                {
                    pLayeredEntries = GetLayeredEntriesByGuid(
                            pLspMap[i].LayeredEntries, 
                            pLspMap[i].Count,
                           &pLspMap[i].LayeredGuids[j], 
                           &iLayerCount
                            );
                    if (pLayeredEntries == NULL)
                    {
                        fprintf(stderr, "GetLayeredEntriesByGuid: Failed!\n");
                        continue;
                    }
                
                    // Reinstalled the layered entries
                    rc = InstallProvider(
                            Catalog, 
                           &pLspMap[i].LayeredGuids[j], 
                            pLspMap[i].wszLspDll,
                            pLayeredEntries,
                            iLayerCount
                            );
                    if (rc != NO_ERROR)
                    {
                        fprintf(stderr, "RemoveProvider: Unable to install layered provider(s) for %ws; error %d\n",
                            pLspMap[i].DummyEntry.szProtocol,
                            rc
                            );
                        goto cleanup;
                    }

                    HeapFree(GetProcessHeap(), 0, pLayeredEntries);
                    pLayeredEntries = NULL;
                }

                // Enumerate the catalog 
                FreeProviders(pProvider);

                pProvider = EnumerateProviders(Catalog, &iProviderCount);
                if (pProvider == NULL)
                {
                    fprintf(stderr, "RemoveProvider: Unable to enumerate Winsock catalog!\n");
                    Status = SOCKET_ERROR;
                    goto cleanup;
                }

                // Now go through and find the updated catalog entry IDs
                MapNewEntriesToOld(&pLspMap[i], pProvider, iProviderCount);

                // Now update the LSP map to reference these new IDs instead of the old
                for(j=0; j < pLspMap[i].Count ;j++)
                {
                    UpdateLspMap(
                        pLspMap, 
                        iLspCount, 
                        pLspMap[i].LayeredEntries[j].dwCatalogEntryId,
                        pLspMap[i].LayeredEntries[j].dwProviderReserved,
                        pdwCatalogOrder,
                        iOriginalProviderCount
                        );
                }
            }

            // Now all the LSPs are back in place -- we need to reorder the catalog
            // back to the way it was
            #ifdef _WIN64
            if (Catalog == LspCatalog32Only)
            {
                rc = WSCWriteProviderOrder32(pdwCatalogOrder, iProviderCount);
            }
            else
            {
                rc = WSCWriteProviderOrder(pdwCatalogOrder, iProviderCount);
            }
            #else
                rc = WSCWriteProviderOrder(pdwCatalogOrder, iProviderCount);
            #endif
            if (rc == SOCKET_ERROR)
            {
                fprintf(stderr, "RemoveProvider: WSCWriteProviderOrder failed: %d\n", WSAGetLastError());
            }

            printf("Catalog Order: ");
            for(i=0; i < iProviderCount ;i++)
            {
                printf("%d ", pdwCatalogOrder[i]);
            }
            printf("\n");

            // Free the catalog order info
            HeapFree(GetProcessHeap(), 0, pdwCatalogOrder);
            pdwCatalogOrder = NULL;
        }
    }

cleanup:

    //
    // Cleanup allocations
    //

    if (pLayeredEntries)
        HeapFree(GetProcessHeap(), 0, pLayeredEntries);

    if (pProvider)
        FreeProviders(pProvider);

    if (pdwRemovedProviders)
        HeapFree(GetProcessHeap(), 0, pdwRemovedProviders);

    if (pLspMap)
        FreeLspMap(pLspMap, iLspCount);

    if (pdwCatalogOrder)
        HeapFree(GetProcessHeap(), 0, pdwCatalogOrder);

    return Status;
}

//
// Function: RemoveAllLayeredEntries
//
// Description:
//    In the event that the layered entries become totally hosed up. This
//    function will remove any non base provider.
//
int RemoveAllLayeredEntries(WINSOCK_CATALOG Catalog)
{
    WSAPROTOCOL_INFOW   *pProviders=NULL,
                        *pAssociated=NULL;
    WCHAR                szGuidString[MAX_PATH];
    LSP_ENTRY           *pLspMap=NULL;
    INT                  iProviderCount,
                         iAssociatedCount,
                         iLspCount,
                         Status,
                         rc,
                         i, j, k;

    Status = NO_ERROR;

    // First enumerate the catalog
    pProviders = EnumerateProviders(Catalog, &iProviderCount);
    if (pProviders == NULL)
    {
        fprintf(stderr, "RemoveAllLayeredEntries: Unable to enumerate catalog!\n");
        Status = SOCKET_ERROR;
        goto cleanup;
    }

    // Build a mapping of the LSPs installed on the system
    pLspMap = BuildLspMap(pProviders, iProviderCount, &iLspCount);
    if (pLspMap == NULL)
    {
        printf("\nNo LSPs to remove!\n");
    }
    else
    {
        printf("\n%d LSPs installed:\n", iLspCount);
        for(i=0; i < iLspCount ;i++)
        {
            printf("   %d: %ws with %d layered entries\n",
                pLspMap[i].DummyEntry.dwCatalogEntryId, pLspMap[i].DummyEntry.szProtocol,
                pLspMap[i].Count);
        }

        printf("\nRemoving LSPs...\n\n");

        for(i=0; i < iLspCount ;i++)
        {
            // First remove the dummy entry
            printf("Removing dummy entry for: %ws\n", pLspMap[i].DummyEntry.szProtocol);
            rc = DeinstallProvider(Catalog, &pLspMap[i].DummyEntry.ProviderId);

            printf("Removing the associated layered entries with GUIDs:\n");
            for(j=0; j < pLspMap[i].LayeredGuidCount ;j++)
            {
                StringFromGUID2(pLspMap[i].LayeredGuids[j], szGuidString, MAX_PATH-1);
                printf("\tGUID: %ws\n", szGuidString);

                // Get a list of all providers under this GUID so we can print it out
                pAssociated = GetLayeredEntriesByGuid(
                        pLspMap[i].LayeredEntries, 
                        pLspMap[i].Count,
                       &pLspMap[i].LayeredGuids[j], 
                       &iAssociatedCount
                        );
                if (pAssociated == NULL)
                {
                    fprintf(stderr, "RemoveAllLayeredProviders: GetLayeredEntriesByGuid failed!\n");
                    goto cleanup;
                }

                for(k=0; k < iAssociatedCount ;k++)
                {
                    printf("\t  %d: %ws\n", pAssociated[k].dwCatalogEntryId,
                            pAssociated[k].szProtocol);
                }

                HeapFree(GetProcessHeap(), 0, pAssociated);
                pAssociated = NULL;

                rc = DeinstallProvider(Catalog, &pLspMap[i].LayeredGuids[j]);
                if (rc == SOCKET_ERROR)
                {
                    fprintf(stderr, "RemoveAllLayeredProviders: DeinstallProvider failed!\n");
                }
                else
                {
                    printf("\tUninstalled providers for %ws\n", szGuidString);
                }
            }
        }

        FreeLspMap(pLspMap, iLspCount);
        pLspMap = NULL;
    }

cleanup:

    if (pProviders)
        FreeProviders(pProviders);

    if (pLspMap)
        FreeLspMap(pLspMap, iLspCount);

    if (pAssociated)
        HeapFree(GetProcessHeap(), 0, pAssociated);

    return Status;
}

//
// Function: BuildLspMap
//
// Description:
//    This routine builds a map of all LSPs installed according to what order
//    they are in the catalog. That is, the information returned will be ordered
//    in the way the LSPs need to be installed. For example if LSP1 is installed
//    over the base TCP and UDP providers and LSP2 is installed over LSP1, then 
//    this routine will return two LSP_ENTRY structures with LSP1 first followed
//    by LSP2. The algorithm for determining the order is to first sort by where
//    a base provider ID occurs in an LSP chain with lower numbered ones first.
//    For example, LSP1 layered directly over TCP will have a base ID (TCP) in
//    chain position 1 while LSP (layered over LSP1) will have the base ID in
//    chain index 2. This is the ChainOrder field (and it is the minimum value
//    for all layered providers). After this first sort, it is possible to have
//    several LSPs with the same ChainOrder value. Within these groupings the
//    entries are sorted by the maximum LSP chain length. Each LSP has a number
//    of layered providers each with its own chain (and the chains could be
//    different lengths). The MaxChainLength value is the longest chain length
//    of all providers belonging to a given LSP. Each grouping of LspOrder is then
//    sorted by MaxChainLengthin ascending order.
//
LSP_ENTRY *
BuildLspMap(
    WSAPROTOCOL_INFOW *pProviders,
    int  iProviderCount,
    int *pLspCount
    )
{
    LSP_ENTRY *pLsps=NULL,
               lsptmp;
    DWORD     *pBaseList=NULL;
    BOOL       bFound;
    int        iLspCount=0,
               iBaseCount=0,
               iProviderPathLen,
               ErrorCode,
               LspOrder,
               start,
               end,
               idx,
               rc,
               i, j, k;

    iLspCount = GetProviderCount(pProviders, iProviderCount, LAYERED_PROTOCOL);

    if ( iLspCount == 0 )
    {
        // No LSPs installed, nothing to do
        goto cleanup;
    }

    // Allocate space for our structure which represents the LSPs installed
    pLsps = (LSP_ENTRY *) HeapAlloc(
            GetProcessHeap(),
            HEAP_ZERO_MEMORY,
            sizeof(LSP_ENTRY) * iLspCount
            );
    if (pLsps == NULL)
    {
        fprintf(stderr, "BuildLspMap: HeapAlloc failed: %d\n", GetLastError());
        goto cleanup;
    }

    idx = 0;
    for(i=0; i < iProviderCount ;i++)
    {
        if ( pProviders[i].ProtocolChain.ChainLen == LAYERED_PROTOCOL )
        {
            // Copy the dummy entry
            memcpy( &pLsps[idx].DummyEntry, &pProviders[i], sizeof(WSAPROTOCOL_INFOW) );

            // Get the DLL path
            iProviderPathLen = MAX_PATH-1;
            rc = WSCGetProviderPath(
                    &pLsps[idx].DummyEntry.ProviderId,
                     pLsps[idx].wszLspDll,
                    &iProviderPathLen,
                    &ErrorCode
                    );
            if (rc == SOCKET_ERROR)
            {
                fprintf(stderr, "BuildLspMap: WSCGetProviderPath failed: %d\n", ErrorCode);
                goto cleanup;
            }

            //
            // Now go find all the layered entries associated with the dummy provider
            //

            // First get the count
            for(j=0; j < iProviderCount ;j++)
            {
                if ( IsIdInChain( &pProviders[j], pLsps[idx].DummyEntry.dwCatalogEntryId ) )
                {
                    pLsps[idx].Count++;
                }
            }

            // Allocate space
            pLsps[idx].LayeredEntries = (WSAPROTOCOL_INFOW *)HeapAlloc(
                    GetProcessHeap(),
                    HEAP_ZERO_MEMORY,
                    sizeof(WSAPROTOCOL_INFOW) * pLsps[idx].Count
                    );
            if (pLsps[idx].LayeredEntries == NULL)
            {
                fprintf(stderr, "BuildLspMap: HeapAlloc failed: %d\n", GetLastError());
                goto cleanup;
            }

            // Now go find the entries
            pLsps[idx].Count = 0;
            for(j=0; j < iProviderCount ;j++)
            {
                if ( IsIdInChain( &pProviders[j], pLsps[idx].DummyEntry.dwCatalogEntryId ) )
                {
                    memcpy( &pLsps[idx].LayeredEntries[pLsps[idx].Count],
                            &pProviders[j],
                            sizeof(WSAPROTOCOL_INFOW)
                            );
                    
                    pLsps[idx].MaxChainLength = MAX( 
                            pLsps[idx].MaxChainLength,
                            pLsps[idx].LayeredEntries[pLsps[idx].Count].ProtocolChain.ChainLen 
                            );

                    // Keep track of how many GUIDs are used to install the layered entries
                    if (pLsps[idx].Count == 0)
                    {
                        pLsps[idx].LayeredGuids = (GUID *)HeapAlloc(
                                GetProcessHeap(),
                                HEAP_ZERO_MEMORY,
                                sizeof(GUID)
                                );
                        if (pLsps[idx].LayeredGuids == NULL)
                        {
                            fprintf(stderr, "BuildLspMap: HeapAlloc failed: %d\n", GetLastError());
                            goto cleanup;
                        }

                        memcpy( &pLsps[idx].LayeredGuids[0], &pProviders[j].ProviderId, sizeof(GUID) );
                        pLsps[idx].LayeredGuidCount++;
                    }
                    else
                    {
                        // See if we've already seen this guid
                        bFound = FALSE;
                        for(k=0; k < pLsps[idx].LayeredGuidCount ;k++)
                        {
                            if ( memcmp( &pLsps[idx].LayeredGuids[k],
                                         &pProviders[j].ProviderId,
                                         sizeof(GUID) ) == 0 )
                             {
                                bFound = TRUE;
                                break;
                             }
                        }
                        if (bFound == FALSE)
                        {
                            GUID    *tmpguid=NULL;

                            // New GUID -- we need to add it to the array
                            tmpguid = (GUID *)HeapAlloc(
                                    GetProcessHeap(),
                                    HEAP_ZERO_MEMORY,
                                    sizeof(GUID) * (pLsps[idx].LayeredGuidCount + 1)
                                    );
                            if (tmpguid == NULL)
                            {
                                fprintf(stderr, "BuildLspMap: HeapAlloc failed: %d\n", GetLastError());
                                goto cleanup;
                            }

                            memcpy( tmpguid, pLsps[idx].LayeredGuids, sizeof(GUID) * pLsps[idx].LayeredGuidCount );
                            memcpy( &tmpguid[pLsps[idx].LayeredGuidCount], &pProviders[j].ProviderId, sizeof(GUID) );

                            HeapFree(GetProcessHeap(), 0, pLsps[idx].LayeredGuids);

                            pLsps[idx].LayeredGuids = tmpguid;
                            pLsps[idx].LayeredGuidCount++;
                        }
                    }

                    pLsps[idx].Count++;

                }
            }

            pLsps[idx].LspOrder = MAX_PROTOCOL_CHAIN;

            idx++;
        }
    }

    //
    // We now have an array of "LSPs" -- now order them
    //

    // First get a list of base provider IDs
    iBaseCount = GetProviderCount(pProviders, iProviderCount, BASE_PROTOCOL);
    if (iBaseCount == 0)
    {
        fprintf(stderr, "BuildLspMap: GetProviderCount(BASE_PROTOCOL) returned zero!\n");
        goto cleanup;
    }

    // Allocate space for the array of base provider ID's
    pBaseList = (DWORD *) HeapAlloc(
            GetProcessHeap(),
            HEAP_ZERO_MEMORY,
            sizeof(DWORD) * iBaseCount
            );
    if (pBaseList == NULL)
    {
        fprintf(stderr, "BuildLspMap: HeapAlloc failed: %d\n", GetLastError());
        goto cleanup;
    }

    // Copy the base provider ID's to our array
    idx = 0;
    for(i=0; i < iProviderCount ;i++)
    {
        if ( pProviders[i].ProtocolChain.ChainLen == BASE_PROTOCOL )
        {
            pBaseList[idx++] = pProviders[i].dwCatalogEntryId;
        }
    }

    for(LspOrder = 1; LspOrder < MAX_PROTOCOL_CHAIN ;LspOrder++)
    {
        for(i=0; i < iLspCount ;i++)
        {
            for(j=0; j < pLsps[i].Count ;j++)
            {
                for(k=0; k < iBaseCount ;k++)
                {
                    if ( pLsps[i].LayeredEntries[j].ProtocolChain.ChainEntries[LspOrder] ==
                         pBaseList[k] )
                    {
                        pLsps[i].LspOrder = MIN( pLsps[i].LspOrder, LspOrder );
                        break;
                    }
                }
            }
        }
    }

    // Sort the entries according to the LspOrder field
    for(i=0; i < iLspCount ;i++)
    {
        for(j=i; j < iLspCount ;j++)
        {
            if ( pLsps[i].LspOrder > pLsps[j].LspOrder )
            {
                // Exchange positions
                memcpy( &lsptmp,   &pLsps[i], sizeof(LSP_ENTRY) );
                memcpy( &pLsps[i], &pLsps[j], sizeof(LSP_ENTRY) );
                memcpy( &pLsps[j], &lsptmp,   sizeof(LSP_ENTRY) );
            }
        }
    }

    // Now need to sort by MaxChainLength withing the LspOrder groupings

    for(LspOrder=1; LspOrder < MAX_PROTOCOL_CHAIN ;LspOrder++)
    {
        // Find the start and end positions within the array for the given
        // LspOrder value
        start = -1;
        end   = -1;
        for(i=0; i < iLspCount ;i++)
        {
            if ( pLsps[i].LspOrder == LspOrder)
            {
                start = i;
                break;
            }
        }
        if (start != -1)
        {
            for(j=start; j < iLspCount ;j++)
            {
                if ( pLsps[j].LspOrder != LspOrder)
                {
                    end = j-1;
                    break;
                }
            }
        }
        
        if ( (start != -1) && (end != -1) )
        {
            for(i=start; i < end ;i++)
            {
                for(j=i; j < end ;j++)
                {
                    if ( pLsps[i].MaxChainLength > pLsps[j].MaxChainLength )
                    {
                        memcpy( &lsptmp,   &pLsps[i], sizeof(LSP_ENTRY) );
                        memcpy( &pLsps[i], &pLsps[j], sizeof(LSP_ENTRY) );
                        memcpy( &pLsps[j], &lsptmp,   sizeof(LSP_ENTRY) );
                    }
                }
            }
        }
    }


cleanup:
    
    if (pLspCount)
        *pLspCount = iLspCount;

    if (pBaseList)
        HeapFree(GetProcessHeap(), 0, pBaseList);

    return pLsps;
}

//
// Function: GetProviderCount
//
// Description:
//    Returns the number of providers installed matching the given Provider Type.
//    The possible provider types are BASE_PROTOCOL or LAYERED_PROTOCOL. That is,
//    this function either returns the count of base providers or the number of
//    dummy LSP providers installed.
//
int
GetProviderCount(
    WSAPROTOCOL_INFOW *pProviders,
    int iProviderCount,
    int ProviderType
    )
{
    int Count, i;

    Count = 0;
    for(i=0; i < iProviderCount ;i++)
    {
        if ( pProviders[i].ProtocolChain.ChainLen == ProviderType )
            Count++;
    }
    return Count;
}

//
// Function: PrintLspMap
//
// Description:
//    Print the array of LSP_ENTRY structures to the console. The LSP_ENTRY
//    array is ordered in the same order the LSPs were installed.
//
void
PrintLspMap(
    LSP_ENTRY *pLspMap,
    int iLspCount
    )
{
    WCHAR   szGuidString[MAX_PATH];
    int     i, j, k;

    if (pLspMap == NULL)
    {
        printf("\tNo LSPs currently installed\n\n");
    }
    else
    {
        for(i=0; i < iLspCount ;i++)
        {
            // Display the LSP name and its DLL (and path)
            printf("%3d LSP: %ws   DLL '%ws'\n", i, pLspMap[i].DummyEntry.szProtocol,
                pLspMap[i].wszLspDll);

            // Display the GUIDs under which the layered entries of this LSP are installed
            printf("\t LSP Installed under %d GUIDs\n", pLspMap[i].LayeredGuidCount);
            for(k=0; k < pLspMap[i].LayeredGuidCount ;k++)
            {
                StringFromGUID2(pLspMap[i].LayeredGuids[k], szGuidString, MAX_PATH-1);
                printf("\t\t%ws\n", szGuidString);
            }

            // Display the layered entries and the protocol chains
            for(j=0; j < pLspMap[i].Count ;j++)
            {
                printf("\t Layer %ws Chain %d [ ", pLspMap[i].LayeredEntries[j].szProtocol,
                    pLspMap[i].LayeredEntries[j].ProtocolChain.ChainLen);

                for(k=0; k < pLspMap[i].LayeredEntries[j].ProtocolChain.ChainLen ;k++)
                {
                    printf("%d ", pLspMap[i].LayeredEntries[j].ProtocolChain.ChainEntries[k]);
                }
                printf("]\n");
            }
        }
    }
}

//
// Function: FreeLspMap
//
// Description:
//    Frees all memory associated with an LSP_ENTRY array.
void
FreeLspMap(
    LSP_ENTRY *pLspMap,
    int iLspCount
    )
{
    int     i;

    for(i=0; i < iLspCount ;i++)
    {
        // Free the layered providers first
        if ( pLspMap[i].LayeredEntries != NULL )
            HeapFree(GetProcessHeap(), 0, pLspMap[i].LayeredEntries);
        if ( pLspMap[i].LayeredGuids != NULL )
            HeapFree(GetProcessHeap(), 0, pLspMap[i].LayeredGuids);
    }
    HeapFree(GetProcessHeap(), 0, pLspMap);
}

//
// Function: PruneLspMap
//
// Description:
//    In the event WSCUpdateProvider is not available, the uninstaller must
//    remove and reinstall all dependent LSPs. After the LSP is removed, this
//    routine goes through the LSP map and removes any reference to provider
//    IDs belonging to the removed LSP (both base and layered provider IDs).
//    The pdwRemovedProviders is an array of provider IDs that belong to the
//    removed LSP.
//
void
PruneLspMap(
    LSP_ENTRY *pLspMap, 
    int iLspCount, 
    DWORD *pdwRemovedProviders, 
    int iRemoveCount
    )
{
    int i, j, k;

    // Go through all LSPs
    for(i=0; i < iLspCount ;i++)
    {
        // Go through all providers belonging to this LSP
        for(j=0; j < pLspMap[i].Count ;j++)
        {
            // Search for a removed provider
            for(k=0; k < iRemoveCount ;k++)
            {
                RemoveIdFromChain(&pLspMap[i].LayeredEntries[j], pdwRemovedProviders[k]);
            }
        }
    }
}

//
// Function: UpdateLspMap
//
// Description:
//   This routine updates catalog entry IDs in the LSP map. In the event
//   WSCUpdateProvider is not available, the uninstaller must remove all
//   dependent LSPs and reinstall them. This requires updating any references
//   to these reinstalled LSPs to their new values (as reinstalling a provider
//   changes the catalog ID). After a provider is LSP, the uninstaller matches
//   the older provider to the new to obtain the new provider ID (via
//   MapNewEntriesToOld). This routine takes and old provider ID and updates all
//   references within the LSP map to the new provider's ID.
//
void
UpdateLspMap(
    LSP_ENTRY *pLspMap,
    int iLspCount,
    DWORD dwOldValue,
    DWORD dwNewValue,
    DWORD *pdwCatalogOrder,
    int iProviderCount
    )
{
    int i, j, k;

    // Update the LSP_ENTRY mappings with the new value
    for(i=0; i < iLspCount ;i++)
    {
        // Go through all providers beloging to this LSP
        for(j=0; j < pLspMap[i].Count ;j++)
        {
            // Go through the protocol chain and update references if they match
            for(k=0; k < pLspMap[i].LayeredEntries[j].ProtocolChain.ChainLen ;k++)
            {
                if (pLspMap[i].LayeredEntries[j].ProtocolChain.ChainEntries[k] == dwOldValue)
                {
                    pLspMap[i].LayeredEntries[j].ProtocolChain.ChainEntries[k] = dwNewValue;
                }
            }
        }
    }

    // Update the provider order mapping
    for(i=0; i < iProviderCount ;i++)
    {
        if (pdwCatalogOrder[i] == dwOldValue)
            pdwCatalogOrder[i] =  dwNewValue;
    }
}

//
// Function: GetLayeredEntriesByGuid
//
// Description:
//    This routine is used by the uninstaller when WSCUpdateProvider is not 
//    available. If after an LSP is removed, there are other LSPs which depend
//    on that LSP, the uninstaller must remove and reinstall all LSPs and fix up
//    the catalog ID references within the protocol chain. This routine is used
//    when reinstalling LSP providers. Because the layered entries belonging to
//    an LSP may be installed either under unique (individual) GUIDs or whole
//    groups of providers may be installed under the same GUID. This routine
//    Takes an array of WSAPROTOCOL_INFOW entries belonging to one LSP and
//    returns an array of provider structures which match the given GUID.
//
WSAPROTOCOL_INFOW *
GetLayeredEntriesByGuid(
    WSAPROTOCOL_INFOW *pEntries, 
    int iEntryCount,
    GUID *MatchGuid, 
    int *iLayeredCount
    )
{
    WSAPROTOCOL_INFOW *MatchedEntries=NULL;
    int                count, 
                       i;

    // First count how many entries belong to this GUID
    count = 0;
    for(i=0; i < iEntryCount ;i++)
    {
        if ( memcmp( MatchGuid, &pEntries[i].ProviderId, sizeof(GUID)) == 0 )
        {
            count++;
        }
    }

    // Allocate space for the number of matching provider entries
    MatchedEntries = (WSAPROTOCOL_INFOW *)HeapAlloc(
            GetProcessHeap(),
            HEAP_ZERO_MEMORY,
            sizeof(WSAPROTOCOL_INFOW) * count
            );
    if (MatchedEntries == NULL)
    {
        fprintf(stderr, "GetLayeredEntriesByGuid: HeapAlloc failed: %d\n", GetLastError());
        return NULL;
    }

    // Go back and copy the matching providers into our array
    count = 0;
    for(i=0; i < iEntryCount ;i++)
    {
        if ( memcmp( MatchGuid, &pEntries[i].ProviderId, sizeof(GUID)) == 0 )
        {
            memcpy( &MatchedEntries[count++], &pEntries[i], sizeof(WSAPROTOCOL_INFOW) );
        }
    }

    // Update the return count
    if (iLayeredCount)
        *iLayeredCount = count;

    return MatchedEntries;
}

//
// Function: MapNewEntriesToOld
//
// Description:
//    This routine is used by the uninstaller if WSCUpdateProvider is not available.
//    In this case, after one LSP is removed there may be others that referenced
//    that LSP. The uninstaller removes those entries and reinstalls them (and
//    removes the reference the the removed LSP). Once a dependent provider is
//    reinstalled we need to see if even other LSP references the reinstalled
//    provider and if so we need to update all references (catalog IDs) to that
//    LSP. This routine takes the Winsock catalog after a dependent LSP has
//    been resinstalled (pProvider and iProviderCount) and matches the newly
//    installed providers back to the LSP map we started with. This is so we
//    can get the older catalog ID along with the new catalog ID of each LSP
//    entry.
//
void
MapNewEntriesToOld(
    LSP_ENTRY *pEntry, 
    WSAPROTOCOL_INFOW *pProvider, 
    int iProviderCount
    )
{
    int     i, j;
            
    for(i=0; i < pEntry->Count ;i++)
    {
        for(j=0; j < iProviderCount ;j++)
        {
            if ( IsEqualProtocolEntries( &pEntry->LayeredEntries[i], &pProvider[j] ) )
            {
                pEntry->LayeredEntries[i].dwProviderReserved = pProvider[j].dwCatalogEntryId;
                break;
            }
        }
    }
}

//
// Function: IsEqualProtocolEntries
//
// Description:
//    This routine compares two WSAPROTOCOL_INFOW structures to determine 
//    whether they are equal. This is done when a provider is uninstalled
//    and then reinstalled. After reinstallation we need to match the old
//    provider to the new (after reenumerating the catalog) so we can find
//    its new catalog ID. The fields used for determining a match are all
//    fields except the catalog ID (dwCatalogEntryId) and the protocol
//    string (szProtocol).
//
BOOL
IsEqualProtocolEntries(
    WSAPROTOCOL_INFOW *pInfo1,
    WSAPROTOCOL_INFOW *pInfo2
    )
{
    if ( (memcmp(&pInfo1->ProviderId, &pInfo2->ProviderId, sizeof(GUID)) == 0) &&
         (pInfo1->dwServiceFlags1 == pInfo2->dwServiceFlags1) &&
         (pInfo1->dwServiceFlags2 == pInfo2->dwServiceFlags2) &&
         (pInfo1->dwServiceFlags3 == pInfo2->dwServiceFlags3) &&
         (pInfo1->dwServiceFlags4 == pInfo2->dwServiceFlags4) &&
         (pInfo1->ProtocolChain.ChainLen == pInfo2->ProtocolChain.ChainLen) &&
         (pInfo1->iVersion == pInfo2->iVersion) &&
         (pInfo1->iAddressFamily == pInfo2->iAddressFamily) &&
         (pInfo1->iMaxSockAddr == pInfo2->iMaxSockAddr) &&
         (pInfo1->iMinSockAddr == pInfo2->iMinSockAddr) &&
         (pInfo1->iSocketType == pInfo2->iSocketType) &&
         (pInfo1->iProtocol == pInfo2->iProtocol) &&
         (pInfo1->iProtocolMaxOffset == pInfo2->iProtocolMaxOffset) &&
         (pInfo1->iNetworkByteOrder == pInfo2->iNetworkByteOrder) &&
         (pInfo1->iSecurityScheme == pInfo2->iSecurityScheme) &&
         (pInfo1->dwMessageSize == pInfo2->dwMessageSize)
       )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
