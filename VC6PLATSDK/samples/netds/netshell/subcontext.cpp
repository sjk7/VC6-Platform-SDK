// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft Netsh Sample.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------
#include "nshsamp.h"

extern SAMPLE_HELPER_DATA g_OnlineData;
extern SAMPLE_HELPER_DATA g_OfflineData;
extern PSAMPLE_HELPER_DATA g_CurrentData;
extern HANDLE g_hModule;

DWORD WINAPI
HandleShowErrorCommand(
IN      LPCWSTR pwszMachine,
IN OUT  LPWSTR  *ppwcArguments,
IN      DWORD   dwCurrentIndex,
IN      DWORD   dwArgCount,
IN      DWORD   dwFlags,
IN      LPCVOID pvData,
OUT     BOOL    *pbDone)
{
    DWORD dwRet = ERROR_SHOW_USAGE;
    DWORD dwNumArgs = dwArgCount - dwCurrentIndex;
    
    //
    // If there are args for us to process..
    //
    if (dwNumArgs)
    {
        dwRet = ERROR_OKAY;
        
        for (DWORD i = dwCurrentIndex; i < dwArgCount; i++)
        {
            ULONG ulErrorNumber = wcstoul(ppwcArguments[i], NULL, 10);
            if (!ulErrorNumber)
            {
                ulErrorNumber = wcstoul(ppwcArguments[i], NULL, 16);
            }
            
            //
            // Use PrintError's first type of functionality, that being
            // printing out system error messages, be they netsh error 
            // messages, (see netsh.h), ras errors, mpr errors, or win32
            // errors.
            //
            PrintMessage(L"%1!u!: ", ulErrorNumber);
            //
            // Pad the PrintError call with some extra zero's - this will prevent us from AV'ing
            // if we try to look at an error string that requires extra inputs.  (Hack, but 
            // since it is expected that you know which error string you are outputting, it's
            // unavoidable.)
            //
            if (!PrintError(0, ulErrorNumber, 0, 0, 0, 0, 0, 0))
            {
                //
                // PrintError returns 0 if something didn't work (usually means
                // invalid error id), so we can use its other function, which
                // is to print out error messages from a given module.  Note that
                // this is essentially the same functionality as 
                // PrintMessageFromModule.
                //
                PrintError(g_hModule, ERR_INVALID_ERROR_CODE, ulErrorNumber, ulErrorNumber);
            }
        }
    }
    
    return dwRet;
}
