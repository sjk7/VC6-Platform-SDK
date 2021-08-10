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
DumpSampleInterface(
    IN      LPCWSTR     pwszRouter,
    IN OUT  LPWSTR     *ppwcArguments,
    IN      DWORD       dwArgCount,
    IN      LPCVOID     pvData
    )
{
    DWORD       dwRet;
    UINT        OSType;
    UINT        OSProductSuite;
    WCHAR       OSVersion[MAX_PATH];
    WCHAR       OSBuildNumber[MAX_PATH];
    WCHAR       ServicePackMajorVersion[MAX_PATH];
    WCHAR       ServicePackMinorVersion[MAX_PATH];
    UINT        ProcessorArchitecture;
    LPWSTR      lpArchitecture = NULL;
    
    //
    // This function is provided by netsh so that you can take different
    // actions in any function depending on the machine type.
    //
    dwRet = GetHostMachineInfo(
                &OSType,
                &OSProductSuite,
                OSVersion,
                OSBuildNumber,
                ServicePackMajorVersion,
                ServicePackMinorVersion,
                &ProcessorArchitecture);
                
    if (NO_ERROR == dwRet)
    {   
        
        
        //
        // Note that these values (0 and 6) are WMI values that specify
        // the architecture.  At the time of this writing, these values
        // as listed in MSDN were off by one, ie x86 was listed as 1 and
        // IA64 was listed as 7.  The values here are the correct values 
        // to check against.
        //
        switch(ProcessorArchitecture)
        {
            case 0:
                lpArchitecture = TOKEN_X86;
                break;
            case 6:
                lpArchitecture = TOKEN_IA64;
                break;
            default:
                lpArchitecture = TOKEN_UNKNOWN;
                break;
        }
    }
        
    LPWSTR lpPotential = 0;

    switch(g_CurrentData->Potential)
    {
        case LOW:
            lpPotential = TOKEN_LOW;
            break;
        case MEDIUM:
            lpPotential = TOKEN_MEDIUM;
            break;
        case HIGH:
            lpPotential = TOKEN_HIGH;
            break;
    }
    
    //
    // Output the string that shows our settings.
    // The idea here is to spit out a script that,
    // when run from the command line (netsh -f script)
    // will cause your component to be configured
    // exactly as it is when this dump command is run.
    //
    PrintMessageFromModule(g_hModule, DUMP_SAMPINTERFACE,
                           TOKEN_SET,
                           TOKEN_INTERFACE,
                           TOKEN_ID,
                           g_CurrentData->InterfaceID,
                           g_CurrentData->bEnabled ? TOKEN_ENABLED : TOKEN_DISABLED,
                           TOKEN_SUPERMETRIC,
                           g_CurrentData->Supermetric,
                           TOKEN_POTENTIAL,
                           lpPotential,
                           // Second set command starts here.
                           TOKEN_GATEWAY,
                           TOKEN_USERDATA,
                           (DWORD)LOBYTE(LOWORD(g_CurrentData->GatewayUserData)),
                           (DWORD)HIBYTE(LOWORD(g_CurrentData->GatewayUserData)),
                           (DWORD)LOBYTE(HIWORD(g_CurrentData->GatewayUserData)),
                           (DWORD)HIBYTE(HIWORD(g_CurrentData->GatewayUserData)),
                           lpArchitecture);
                
    return NO_ERROR;
}

DWORD WINAPI
HandleSetInterfaceCommand(
IN      LPCWSTR pwszMachine,
IN OUT  LPWSTR  *ppwcArguments,
IN      DWORD   dwCurrentIndex,
IN      DWORD   dwArgCount,
IN      DWORD   dwFlags,
IN      LPCVOID pvData,
OUT     BOOL    *pbDone)
{
    DWORD dwRet = ERROR_SHOW_USAGE;
    const DWORD MAX_CMDS = 4;
    DWORD dwTagType[MAX_CMDS];
    
    //
    // This command line is more complicated, and allows us
    // to show the results of using PreprocessCommand on a
    // more complicated command line.
    //
    
    TAG_TYPE ValidCommands[] =
    {
        {TOKEN_ID,  NS_REQ_PRESENT, FALSE},
        {TOKEN_ENABLED, NS_REQ_ZERO, FALSE},
        {TOKEN_DISABLED, NS_REQ_ZERO, FALSE},
        {TOKEN_SUPERMETRIC, NS_REQ_ZERO, FALSE},
        {TOKEN_POTENTIAL, NS_REQ_ZERO, FALSE}
    };
    
    dwRet = PreprocessCommand(
        0,
        ppwcArguments,
        dwCurrentIndex,
        dwArgCount,
        ValidCommands,
        sizeof(ValidCommands)/sizeof(TAG_TYPE),
        // At least two commands are required - the id specification for the interface and some other bit of data.
        2,
        MAX_CMDS,
        dwTagType);
        
    if (NO_ERROR == dwRet)
    {
        for (DWORD i = 0; i < (dwArgCount - dwCurrentIndex); i++)
        {
            //
            // This switch works because these were #defined to match with
            // ValidCommands above.
            //
            // #define ID                              0
            // #define ENABLED                         1
            // #define DISABLED                        2
            // #define SUPERMETRIC                     3
            // #define POTENTIAL                       4
            //

            switch (dwTagType[i])
            {
                case ID:
                    g_CurrentData->InterfaceID = wcstoul(ppwcArguments[i + dwCurrentIndex], NULL, 10);
                    break;
                case ENABLED:
                    g_CurrentData->bEnabled = TRUE;
                    break;
                case DISABLED:
                    g_CurrentData->bEnabled = FALSE;
                    break;
                case SUPERMETRIC:
                    g_CurrentData->Supermetric = wcstoul(ppwcArguments[i + dwCurrentIndex], NULL, 10);
                    break;
                case POTENTIAL:
                    if (MatchToken(ppwcArguments[i + dwCurrentIndex], TOKEN_LOW))
                    {
                        g_CurrentData->Potential = LOW;
                    }
                    else if (MatchToken(ppwcArguments[i + dwCurrentIndex], TOKEN_MEDIUM))
                    {
                        g_CurrentData->Potential = MEDIUM;
                    }
                    else if (MatchToken(ppwcArguments[i + dwCurrentIndex], TOKEN_HIGH))
                    {
                        g_CurrentData->Potential = HIGH;
                    }
                    break;
                default:
                    //
                    // Shouldn't reach this point.
                    //
                    dwRet = ERROR_INVALID_SYNTAX;
                    break;
            }
        }
    }
    
    return dwRet;
}

DWORD WINAPI
HandleSetGatewayCommand(
IN      LPCWSTR pwszMachine,
IN OUT  LPWSTR  *ppwcArguments,
IN      DWORD   dwCurrentIndex,
IN      DWORD   dwArgCount,
IN      DWORD   dwFlags,
IN      LPCVOID pvData,
OUT     BOOL    *pbDone)
{
    DWORD dwRet = ERROR_SHOW_USAGE;
    const DWORD MAX_CMDS = 4;
    const DWORD MAX_VALUE = 255;
    
    DWORD dwTagType[MAX_CMDS];
    
    
    TAG_TYPE ValidCommands[] =
    {
        //
        // Specify that it is acceptable to put this token in a command
        // multiple times.
        //
        {TOKEN_USERDATA,     NS_REQ_ALLOW_MULTIPLE, FALSE}
    };
    
    //
    // Since our command should have an = in it, PreprocessCommand will
    // do most of the parsing for us.
    //
    dwRet = PreprocessCommand(
        0,
        ppwcArguments,
        dwCurrentIndex,
        dwArgCount,
        ValidCommands,
        sizeof(ValidCommands)/sizeof(TAG_TYPE),
        1,
        // We'll put a limit of MAX_CMDS pieces of data (so it fits in one DWORD.)
        MAX_CMDS,
        dwTagType);
        
    if (NO_ERROR == dwRet)
    {
        //
        // Reset GatewayUserData to 0.
        //
        g_CurrentData->GatewayUserData = 0;
        
        for (DWORD i = dwCurrentIndex; i < dwArgCount; i++)
        {
            //
            // If we got to this point, then we can just start converting bits of data
            // because there is only one possible argument.
            //
            DWORD dwResult = wcstoul(ppwcArguments[i], NULL, 10);
            if (dwResult > 0 && dwResult < MAX_VALUE)
            {
                //
                // Store our data in the global DWORD by bitshifting each
                // arg by (i - dwCurrentIndex) * 8 bits.  So, the first time
                // through, i - dwCurrentIndex will be 0, and the value
                // won't be shifted.  The second time through, i - dwCurrentIndex
                // is 1, so the value will be shifted left by 8 bits, which
                // when |'d with g_GatewayUserData, will store our number in the
                // second byte.
                //
                g_CurrentData->GatewayUserData |= dwResult << ((i - dwCurrentIndex) * 8);
            }
            else
            {
                dwRet = ERROR_SHOW_USAGE;
            }
        }
    }
   
    return dwRet;
}

DWORD WINAPI
HandleShowRandomSettingsCommand(
IN      LPCWSTR pwszMachine,
IN OUT  LPWSTR  *ppwcArguments,
IN      DWORD   dwCurrentIndex,
IN      DWORD   dwArgCount,
IN      DWORD   dwFlags,
IN      LPCVOID pvData,
OUT     BOOL    *pbDone)
{
    LPWSTR lpPotential = 0;
    
    switch(g_CurrentData->Potential)
    {
        case LOW:
            lpPotential = TOKEN_LOW;
            break;
        case MEDIUM:
            lpPotential = TOKEN_MEDIUM;
            break;
        case HIGH:
            lpPotential = TOKEN_HIGH;
            break;
    }
    
    //
    // Output the current settings.
    //
    PrintMessageFromModule(g_hModule, 
                           GEN_SAMPLEINTERFACE_SETTINGS, 
                           g_CurrentData->InterfaceID, 
                           g_CurrentData->bEnabled ? TOKEN_ENABLED : TOKEN_DISABLED, 
                           g_CurrentData->Supermetric,
                           lpPotential);
                           
    PrintMessageFromModule(g_hModule,
                           GEN_SAMPLEGATEWAY_SETTINGS,
                           (DWORD)LOBYTE(LOWORD(g_CurrentData->GatewayUserData)),
                           (DWORD)HIBYTE(LOWORD(g_CurrentData->GatewayUserData)),
                           (DWORD)LOBYTE(HIWORD(g_CurrentData->GatewayUserData)),
                           (DWORD)HIBYTE(HIWORD(g_CurrentData->GatewayUserData)));
                           
    
    //
    // There wasn't really any error checking to do for this one
    // so just return NO_ERROR.
    //
    return NO_ERROR;
}