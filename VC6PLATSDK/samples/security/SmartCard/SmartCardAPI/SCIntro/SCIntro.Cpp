/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

 Copyright (C) 1998 - 2000.  Microsoft Corporation.  All rights reserved.

 Module:      SCIntro.cpp

 Abstract:    Main program of SCIntro sample for Smart Card SDK sample. See
              ReadMe.txt for more detail information about this sample.

 Environment: Win32 console, C++ w/SEH, UNICODE ready.

------------------------------------------------------------------------------*/

////////////////////
//
// INCLUDE
//

#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <winscard.h>


///////////////
//
// Prototype
//

LONG IntroduceReaderGroup(IN SCARDCONTEXT hContext, OUT LPTSTR  lpszReaderGroup, IN DWORD cchReaderGroup);
LONG AddReadersToGroup   (IN SCARDCONTEXT hContext, IN  LPCTSTR lpszReaderGroup);
LONG IntroduceCardType   (IN SCARDCONTEXT hContext, IN  LPCTSTR lpszCardName);

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 Function : _tmain

 Synopsis : Entry point of SCIntro.

 Parameter: Standard ANSI C command line parameters.

 Return   : SCARD_S_SUCCESS or error code

------------------------------------------------------------------------------*/

extern "C" int __cdecl
_tmain (int argc, _TCHAR  * argv[])
{
    LONG lResult;
    _TCHAR szReaderGroup[_MAX_PATH];
    SCARDCONTEXT hContext = NULL;

    __try
    {
        //
        // Establish context with the resource manager.
        //
        lResult = SCardEstablishContext(SCARD_SCOPE_USER,
                                        NULL,
                                        NULL,
                                        &hContext);
        if (lResult != SCARD_S_SUCCESS)
        {
            __leave;
        }

        //
        // Introduce reader group to the system.
        //
        lResult = IntroduceReaderGroup(hContext, szReaderGroup, sizeof(szReaderGroup) / sizeof(szReaderGroup[0]));
        if (lResult != SCARD_S_SUCCESS)
        {
            __leave;
        }

        //
        // Prompt user to select reader(s) to be added to the reader group.
        //
        lResult = AddReadersToGroup(hContext, szReaderGroup);
        if (lResult != SCARD_S_SUCCESS)
        {
            __leave;
        }

        //
        // Promt user to select card(s) to be added to the system.
        //
        lResult = IntroduceCardType(hContext, szReaderGroup);
        if (lResult != SCARD_S_SUCCESS)
        {
            __leave;
        }
    }

    __finally
    {
        //
        // Don't forget to release the context handle if established.
        //
        if (hContext != NULL)
        {
            LONG lReturn = SCardReleaseContext(hContext);

            //
            // If successful so far, then capture return code of
            // SCardReleaseContext(); otherwise, don't bother
            //
            if (lResult == SCARD_S_SUCCESS)
            {
                lResult = lReturn;
            }
        }
    }

    //
    // Inform user if an error had occurred.
    //
    if (lResult != SCARD_S_SUCCESS)
    {
        _tprintf(_T("\nError [0x%lx]: Program terminated abnormally.\n"),
                 lResult);
    }

    return((int) lResult);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 Function : IntroduceReaderGroup

 Synopsis : Prompt user to type in a reader group name to be introduced to the
            smart card sub-system.

 Parameter: - IN SCARDCONTEXT hContext

              Resource manager context returned by SCardEstablishContext(), or
              NULL if the query is not directed towards a specific context.

            - OUT LPTSTR lpszReaderGroup

              Pointer to reader group name to be assigned to the new reader
              group.

            - IN DWORD cchReaderGroup

              # of chars that can fit in lpszReaderGroup.

 Return   : SCARD_S_SUCCESS or error code

------------------------------------------------------------------------------*/

LONG IntroduceReaderGroup (IN SCARDCONTEXT hContext,
                           OUT LPTSTR lpszReaderGroup,
						   IN DWORD cchReaderGroup)
{
    LONG   lResult         = SCARD_S_SUCCESS;
    LPTSTR lpmszGroupNames = NULL;

    //
    // Parameter check
    //
    if (lpszReaderGroup == NULL)
    {
        return SCARD_E_INVALID_PARAMETER;
    }

    //
    // Print header.
    //
    _tprintf(_T("\n"));
    _tprintf(_T("Introduce Reader Group\n"));
    _tprintf(_T("======================\n"));
    _tprintf(_T("\n"));

    //
    // Prompt user for a new reader group name.
    //
    _tprintf(_T("Type in a new reader group name: "));

	*lpszReaderGroup = 0;
    _fgetts(lpszReaderGroup, cchReaderGroup, stdin);

    _tprintf(_T("\n"));

    if (lstrlen(lpszReaderGroup) == 0)
    {
        return SCARD_E_INVALID_VALUE;
    }

    __try
    {
        //
        // First make sure the reader group does not exist.
        //
        DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;

        lResult = SCardListReaderGroups(hContext,
                                        (LPTSTR) &lpmszGroupNames,
                                        &dwAutoAllocate);
        if (lResult != SCARD_S_SUCCESS)
        {
            __leave;
        }

        for (LPTSTR lpszGroupName = lpmszGroupNames;
            *lpszGroupName != _T('\0');
            lpszGroupName += lstrlen(lpszGroupName) + 1)
        {
            //
            // All smart card component names are case insensitive.
            //
            if (lstrcmpi(lpszGroupName, lpszReaderGroup) == 0)
            {
                break;
            }
        }

        //
        // Introduce the group, if not already exists
        //
        if (*lpszGroupName == _T('\0'))
        {
            lResult = SCardIntroduceReaderGroup(hContext, lpszReaderGroup);
            if (lResult != SCARD_S_SUCCESS)
            {
                __leave;
            }

            _tprintf(_T("Reader group [%s] successfully added.\n\n"),
                     lpszReaderGroup);
        }
        else
        {
            _tprintf(_T("Reader group [%s] already exists.\n\n"), lpszReaderGroup);
        }
    }

    __finally
    {
        LONG lReturn;

        //
        // Don't forget to release memory, if allocated.
        //
        if (lpmszGroupNames != NULL)
        {
            lReturn = SCardFreeMemory(hContext, (LPVOID) lpmszGroupNames);

            //
            // If successful so far, then capture return code of
            // SCardFreeMemory(); otherwise, don't bother.
            //
            if (lResult == SCARD_S_SUCCESS)
            {
                lResult = lReturn;
            }
        }
    }

    return lResult;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 Function : AddReadersToGroup

 Synopsis : Prompt user to select one or more readers to be added to the
            specified reader group.

 Parameter: - IN SCARDCONTEXT hContext

              Resource manager context returned by SCardEstablishContext(), or
              NULL if the query is not directed towards a specific context.

            - IN LPCTSTR lpszReaderGroup

              Pointer to reader group name for which reader(s) will be added.

 Return   : SCARD_S_SUCCESS or error code

------------------------------------------------------------------------------*/

LONG AddReadersToGroup (IN SCARDCONTEXT hContext,
                        IN LPCTSTR lpszReaderGroup)
{
    LONG   lResult           = SCARD_S_SUCCESS;
    LPTSTR lpmszReaderNames  = NULL;
    LPTSTR lpmszGroupReaders = NULL;

    //
    // Parameter check
    //
    if (lpszReaderGroup == NULL || *lpszReaderGroup == NULL)
    {
        return SCARD_E_INVALID_PARAMETER;
    }

    //
    // Print header.
    //
    _tprintf(_T("\n"));
    _tprintf(_T("Add Reader(s) To Group\n"));
    _tprintf(_T("======================\n"));
    _tprintf(_T("\n"));

    __try
    {
        //
        // List all readers known to the system.
        //
        DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;

        lResult = SCardListReaders(hContext,
                                   NULL,
                                   (LPTSTR) &lpmszReaderNames,
                                   &dwAutoAllocate);
        if (lResult != SCARD_S_SUCCESS)
        {
            __leave;
        }

        LPTSTR readers[MAXIMUM_SMARTCARD_READERS];
        DWORD  dwNumReaders   = 0;

        for (LPTSTR lpszReaderName = lpmszReaderNames;
            *lpszReaderName != _T('\0');
            lpszReaderName += lstrlen(lpszReaderName) + 1, dwNumReaders++)
        {
            readers[dwNumReaders] = lpszReaderName;
            _tprintf(_T("%02d: %s\n"), dwNumReaders, lpszReaderName);
        }

        if (dwNumReaders == 0)
        {
            //
            // No registered reader found. However, we should not have gotten so
            // far to here, because no reader situation should have been caught
            // by the above SCardListReaders() call with an erro code of
            // SCARD_E_NO_READERS_AVAILABLE.
            //
            // Note: Introduction of reader to the system is normally handled
            //       by the setup program provided by vendor.
            //
            lResult = SCARD_E_NO_READERS_AVAILABLE;
            __leave;
        }

        //
        // Prompt user to select reader(s) to be added to this reader group.
        // Note: The input format is very primitive. It expects one or more
        //       reader numbers (listed to the left of the reader name) to be
        //       entered and separated by space.
        //
        _tprintf(_T("Select above reader(s) to be added to this reader group: "));

        _TCHAR SelectedReaders[MAXIMUM_SMARTCARD_READERS * 4] = {_T('\0')};;

        _fgetts(SelectedReaders, sizeof(SelectedReaders) / sizeof(SelectedReaders[0]), stdin);

        _tprintf(_T("\n"));

        //
        // For each reader selected, add the reader only if the reader
        // is not already in this reader group.
        //
        dwAutoAllocate = SCARD_AUTOALLOCATE;

        lResult = SCardListReaders(hContext,
                                   lpszReaderGroup,
                                   (LPTSTR) &lpmszGroupReaders,
                                   &dwAutoAllocate);
        if (lResult != SCARD_S_SUCCESS)
        {
            //
            // If no reader in group, treat it as successful.
            //
            if (lResult != SCARD_E_NO_READERS_AVAILABLE)
            {
                __leave;
            }

            lResult = SCARD_S_SUCCESS;
        }

        LPTSTR reader = _tcstok(SelectedReaders, _T(" \n"));

        while (reader != NULL && lResult == SCARD_S_SUCCESS)
        {
            //
            // Make sure selection is valid.
            //
            DWORD nReader = (DWORD) _ttoi(reader);

            if (nReader < dwNumReaders)
            {
                LPTSTR lpszGroupReader = NULL;

                //
                // Make sure reader is not already in this reader group.
                //
                if (lpmszGroupReaders != NULL)
                {
                    for (lpszGroupReader = lpmszGroupReaders;
                        *lpszGroupReader != _T('\0');
                        lpszGroupReader += lstrlen(lpszGroupReader) + 1)
                    {
                        //
                        // All smart card component names are case insensitive.
                        //
                        if (lstrcmpi(lpszGroupReader, readers[nReader]) == 0)
                        {
                            break;
                        }
                    }
                }

                //
                // Only add if reader not already in this reader group.
                //
                if (lpszGroupReader == NULL || *lpszGroupReader == _T('\0'))
                {
                    lResult = SCardAddReaderToGroup(hContext,
                                                    readers[nReader],
                                                    lpszReaderGroup);
                    if (lResult != SCARD_S_SUCCESS)
                    {
                        __leave;
                    }

                    _tprintf(_T("Reader [%s] is successfully added to "
                                _T("this reader group.\n")), readers[nReader]);
                }
                else
                {
                    _tprintf(_T("Reader [%s] already exists in this "
                                _T("reader group.\n")), readers[nReader]);
                }
            }

            //
            // Next reader.
            //
            reader = _tcstok(NULL, _T(" \n"));
        }
    }

    __finally
    {
        LONG lReturn;

        //
        // Don't forget to release memory, if allocated.
        //
        if (lpmszGroupReaders != NULL)
        {
            lReturn = SCardFreeMemory(hContext,
                                      (LPVOID) lpmszGroupReaders);

            //
            // If successful so far, then capture return code of
            // SCardFreeMemory(); otherwise, don't bother.
            //
            if (lResult == SCARD_S_SUCCESS)
            {
                lResult = lReturn;
            }
        }

        if (lpmszReaderNames != NULL)
        {
            lReturn = SCardFreeMemory(hContext, (LPVOID) lpmszReaderNames);

            //
            // If successful so far, then capture return code of
            // SCardFreeMemory(); otherwise, don't bother.
            //
            if (lResult == SCARD_S_SUCCESS)
            {
                lResult = lReturn;
            }
        }
    }

    return lResult;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 Function : IntroduceCardType

 Synopsis : Prompt user to insert card into reader(s) of a specified reader
            group, and introduce any card found in the selected reader(s) to
            the system.

 Parameter: - IN SCARDCONTEXT hContext

              Resource manager context returned by SCardEstablishContext(), or
              NULL if the query is not directed towards a specific context.

            - IN LPCTSTR lpszReaderGroup

              Pointer to reader group name for which the readers should be
              checked for present of card to be introduced.

 Return   : SCARD_S_SUCCESS or error code

 Remarks  : Card is normally introduced to the system by software provided by
            the card manufacturer. Normally, during introduction of card, a SSP
            and/or CSP is also specified. For simplicity, no SSP and/or CSP is
            specified in this example.

------------------------------------------------------------------------------*/

LONG IntroduceCardType (IN SCARDCONTEXT hContext,
                        IN LPCTSTR lpszReaderGroup)
{
    LONG   lResult          = SCARD_S_SUCCESS;
    LPTSTR lpmszReaderNames = NULL;
    LPTSTR lpmszCardNames   = NULL;

    //
    // Print header.
    //
    _tprintf(_T("\n"));
    _tprintf(_T("Introduce Card Type\n"));
    _tprintf(_T("===================\n"));
    _tprintf(_T("\n"));

    //
    // Parameter check
    //
    if (lpszReaderGroup == NULL || *lpszReaderGroup == NULL)
    {
        return SCARD_E_INVALID_PARAMETER;
    }

    __try
    {
        //
        // List all readers in the specified group.
        //
        DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;

        lResult = SCardListReaders(hContext,
                                   lpszReaderGroup,
                                   (LPTSTR) &lpmszReaderNames,
                                   &dwAutoAllocate);
        if (lResult != SCARD_S_SUCCESS)
        {
            __leave;
        }

        //
        // Note that MAXIMUM_SMARTCARD_READERS (10) only refers to maximum # of
        // non-PnP readers. The resource manager is capable of handling any number
        // of PnP readers, in addition to the 10 non-PnP readers (your physical
        // system is the limiting factor).
        //

        LPTSTR readers[MAXIMUM_SMARTCARD_READERS];
        DWORD  dwNumReaders = 0;

        for (LPTSTR lpszReaderName = lpmszReaderNames;
            *lpszReaderName != _T('\0') &&
            dwNumReaders < MAXIMUM_SMARTCARD_READERS;
            lpszReaderName += lstrlen(lpszReaderName) + 1, dwNumReaders++)
        {
            readers[dwNumReaders] = lpszReaderName;
        }

        if (dwNumReaders == 0)
        {
            //
            // No registered reader found. However, we should not have gotten so
            // far to here, because no reader situation should have been caught
            // by the above SCardListReaders() call with an erro code of
            // SCARD_E_NO_READERS_AVAILABLE.
            //
            // Note: Introduction of reader to the system is normally handled
            //       by the setup program provided by vendor.
            //
            lResult = SCARD_E_NO_READERS_AVAILABLE;
            __leave;
        }

        //
        // List all cards known to the system.
        //
        dwAutoAllocate = SCARD_AUTOALLOCATE;

        lResult = SCardListCards(hContext,
                                 NULL,
                                 NULL,
                                 0,
                                 (LPTSTR) &lpmszCardNames,
                                 &dwAutoAllocate);
        if (lResult != SCARD_S_SUCCESS)
        {
            __leave;
        }

        while (TRUE)
        {
            //
            // Prompt user to select reader for which the card to be introduced
            // resides.
            // Note: For simplicity, the input format is very primitive. If the
            //       user should type something longer than the input buffer
            //       length, the program could crash.
            //
            for (DWORD i = 0; i < dwNumReaders; i++)
            {
                _tprintf(_T("%02d: %s\n"), i, readers[i]);
            }

            _TCHAR SelectedReader[80] = {_T('\0')};

            _tprintf(_T("Select reader where the card is [x to exit]: "));

            _fgetts(SelectedReader, sizeof(SelectedReader) / sizeof(SelectedReader[0]), stdin);

            _tprintf(_T("\n"));

            //
            // Make sure selection is valid.
            //
            if (_toupper(SelectedReader[0]) == _T('X'))
            {
                break;
            }

            DWORD nReader = (DWORD) _ttoi(SelectedReader);

            if (nReader < dwNumReaders)
            {
                _TCHAR szCardName[_MAX_PATH] = {_T('\0')};

                //
                // Prompt user for the card friendly name.
                //
                _tprintf(_T("Type in card name: "));

                _fgetts(szCardName, sizeof(szCardName) / sizeof(szCardName[0]), stdin);

                _tprintf(_T("\n"));

                //
                // Make sure card name is valid.
                //
                if (lstrlen(szCardName))
                {
                    //
                    // Make sure card name does not already exist.
                    //
                    for (LPTSTR lpszCardName = lpmszCardNames;
                        *lpszCardName != _T('\0');
                        lpszCardName += lstrlen(lpszCardName) + 1)
                    {
                        //
                        // All smart card component names are case insensitive.
                        //
                        if (lstrcmpi(lpszCardName, szCardName) == 0)
                        {
                            break;
                        }
                    }

                    //
                    // Add card only if it does not already exist.
                    //
                    if (*lpszCardName == _T('\0'))
                    {
                        //
                        // See if a card is in the reader, and find out
                        // its ATR, if present.
                        //
                        SCARD_READERSTATE rsReader;

                        ZeroMemory((LPVOID) &rsReader, sizeof(rsReader));
                        rsReader.szReader = (LPCTSTR) readers[nReader];
                        rsReader.dwCurrentState = SCARD_STATE_UNAWARE;

                        lResult = SCardGetStatusChange(hContext,
                                                       INFINITE,
                                                       &rsReader,
                                                       1);
                        if (lResult != SCARD_S_SUCCESS)
                        {
                            __leave;
                        }

                        //
                        // Is the card in the reader.
                        //
                        if ((rsReader.dwEventState & SCARD_STATE_PRESENT))
                        {
                            //
                            // Add the card!
                            //
                            lResult = SCardIntroduceCardType(hContext,
                                                             szCardName,
                                                             NULL,
                                                             NULL,
                                                             0,
                                                             rsReader.rgbAtr,
                                                             NULL,
                                                             rsReader.cbAtr );
                            if (lResult != SCARD_S_SUCCESS)
                            {
                                __leave;
                            }

                            _tprintf(_T("Card [%s] is successfully introduced.\n\n"),
                                     szCardName);
                        }
                        else
                        {
                            _tprintf(_T("No smart card found in this reader.\n"));
                        }
                    }
                    else
                    {
                        _tprintf(_T("Card [%s] already exists.\n"), szCardName);
                    }
                }
                else
                {
                    _tprintf(_T("Invalid card name.\n"));
                }
            }

            _tprintf(_T("\n"));
        }
    }

    __finally
    {
        LONG lReturn;

        //
        // Don't forget to release memory, if allocated.
        //
        if (lpmszCardNames != NULL)
        {
            lReturn = SCardFreeMemory(hContext,
                                      (LPVOID) lpmszCardNames);

            //
            // If successful so far, then capture return code of
            // SCardFreeMemory(); otherwise, don't bother.
            //
            if (lResult == SCARD_S_SUCCESS)
            {
                lResult = lReturn;
            }
        }

        if (lpmszReaderNames != NULL)
        {
            lReturn = SCardFreeMemory(hContext, (LPVOID) lpmszReaderNames);

            //
            // If successful so far, then capture return code of
            // SCardFreeMemory(); otherwise, don't bother.
            //
            if (lResult == SCARD_S_SUCCESS)
            {
                lResult = lReturn;
            }
        }
    }

    return lResult;
}

