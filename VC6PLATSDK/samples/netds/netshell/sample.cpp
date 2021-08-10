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
DumpSample(
    IN      LPCWSTR     pwszRouter,
    IN OUT  LPWSTR     *ppwcArguments,
    IN      DWORD       dwArgCount,
    IN      LPCVOID     pvData
    )
{
    //
    // Output the string that shows our settings.
    // The idea here is to spit out a script that,
    // when run from the command line (netsh -f script)
    // will cause your component to be configured
    // exactly as it is when this dump command was run.
    //
    PrintMessageFromModule(g_hModule, DUMP_SAMP,
                           TOKEN_SET,
                           TOKEN_WIDGETS,
                           g_CurrentData->WidgetCount,
                           TOKEN_SPROCKETS,
                           g_CurrentData->SprocketCount);
                     
    return NO_ERROR;
    
} 


DWORD WINAPI
HandleAddObjectCommand(
IN      LPCWSTR pwszMachine,
IN OUT  LPWSTR  *ppwcArguments,
IN      DWORD   dwCurrentIndex,
IN      DWORD   dwArgCount,
IN      DWORD   dwFlags,
IN      LPCVOID pvData,
OUT     BOOL    *pbDone)
{
    //
    // Init the return value to ERROR_SHOW_USAGE.  This value
    // if returned, will cause netsh to display the extended 
    // usage for this command.  (HLP_ADD_OBJECT_EX in this case.)
    //
    DWORD dwRet = ERROR_SHOW_USAGE;
    
    //
    // We know the add xxxx x command has two tokens that we care
    // about - the type (widgets, sprockets, all) and the number
    // to add after the type.  From that, we know:
    // 1.  There should be 4 arguments for a valid command.  No more,
    //          no less.
    // 2.  The third arg should be one of the three type id's.
    // 3.  The fourth arg should be a number.
    //
    
    //
    // So, for 1, make sure we have 4 args.
    //
    
    if (4 == dwArgCount)
    {
        long lCountToAdd;
        
        //
        // We'll take care of 3 first, because we need it converted
        // to a number in any case.  CRT function WCSTOL is best to use
        // here.
        //
        if (lCountToAdd = wcstol(ppwcArguments[dwCurrentIndex + 1], NULL, 10))
        {
            //
            // For 2, we'll use MatchToken to match the tokens.
            // If we found a match, return ERROR_OKAY so that
            // netsh will output an "Ok." string to indicate
            // the command was successful.  Returning
            // ERROR_SUPPRESS_OUTPUT indicates that the command
            // was successful but netsh shouldn't output anything
            // to indicate so.
            //
            if (MatchToken(ppwcArguments[dwCurrentIndex], TOKEN_WIDGETS))
            {
                g_CurrentData->WidgetCount += lCountToAdd;
                dwRet = ERROR_OKAY;
            }
            else if(MatchToken(ppwcArguments[dwCurrentIndex], TOKEN_SPROCKETS))
            {
                g_CurrentData->SprocketCount += lCountToAdd;
                dwRet = ERROR_OKAY;
            }
            else if(MatchToken(ppwcArguments[dwCurrentIndex], TOKEN_ALL))
            {
                g_CurrentData->WidgetCount += lCountToAdd;
                g_CurrentData->SprocketCount += lCountToAdd;
                //
                // Since we are returning ERROR_SUPPRESS_OUTPUT
                // to prevent netsh's default "Ok." we will output
                // our own string instead.
                //
                PrintMessageFromModule(g_hModule, GEN_CMD_OKAY);
                dwRet = ERROR_SUPPRESS_OUTPUT;
            }
        }
        else
        {
            //
            // Put a message here telling the user what went wrong.  Note that
            // in your .rc file, you need to specify ... (ellipsis) args via
            // FormatMessage style, ie %1!s! instead of just %s.
            //
            PrintMessageFromModule(g_hModule, ERR_NO_VALID_COUNT, ppwcArguments[3]);
        }
    }
    else
    {
        PrintMessageFromModule(g_hModule, ERR_INVALID_NUM_ARGS, 3);
    }
    
    return dwRet;
}

DWORD WINAPI
HandleShowObjectCommand(
IN      LPCWSTR pwszMachine,
IN OUT  LPWSTR  *ppwcArguments,
IN      DWORD   dwCurrentIndex,
IN      DWORD   dwArgCount,
IN      DWORD   dwFlags,
IN      LPCVOID pvData,
OUT     BOOL    *pbDone)
{
    //
    // Init the return value to ERROR_SHOW_USAGE.  This value
    // will cause netsh to display the extended usage for this
    // command.
    //
    DWORD dwRet = ERROR_SHOW_USAGE;
    
    //
    // We only need check the first token after the command 
    // (ppwcArguments[2].  We could use MatchToken like in
    // HandleAddObjectCommand, but for the purposes of showing
    // examples we'll use MatchEnumTag, though MatchEnumTag
    // isn't quite aimed towards this kind of command line 
    // arrangement.  First, we initialize our valid tokens
    // struct.  This is designed to be like a C enum - each
    // identifier is associated with a value.  You send it
    // a particular argument, it returns you the value 
    // associated with that argument (if its a valid argument.)
    // 
    //
    TOKEN_VALUE ValidTokens[] =
    {
        {TOKEN_WIDGETS,     WIDGETS},
        {TOKEN_SPROCKETS,   SPROCKETS},
        {TOKEN_ALL,         ALL}
    };
    
    //
    // Make sure our arg count is correct.
    //
    if (3 == dwArgCount)
    {
        //
        // Then call MatchEnumTag with our argument of interest.
        // if NO_ERROR is returned, then MatchEnumTag must have 
        // found a valid match.
        //
        DWORD dwResult = 0xffffffff;
        if (NO_ERROR == MatchEnumTag(0,
                                    ppwcArguments[dwCurrentIndex],
                                    sizeof(ValidTokens)/sizeof(TOKEN_VALUE),
                                    ValidTokens,
                                    &dwResult))
        {
            //
            // Since we found a match, assume we can return a success code
            // unless dwResult isn't 1, 2, or 3.  That shouldn't happen
            // however.
            //
            dwRet = ERROR_OKAY;
            switch(dwResult)
            {
                case WIDGETS:
                    PrintMessageFromModule(g_hModule, GEN_CURRENT_COUNT, TOKEN_WIDGETS, g_CurrentData->WidgetCount);
                    break;
                case SPROCKETS:
                    PrintMessageFromModule(g_hModule, GEN_CURRENT_COUNT, TOKEN_SPROCKETS, g_CurrentData->SprocketCount);
                    break;
                case ALL:
                    PrintMessageFromModule(g_hModule, GEN_CURRENT_COUNT, TOKEN_WIDGETS, g_CurrentData->WidgetCount);
                    PrintMessageFromModule(g_hModule, GEN_CURRENT_COUNT, TOKEN_SPROCKETS, g_CurrentData->SprocketCount);
                    break;
                default:
                    dwRet = ERROR_INVALID_SYNTAX;
            }
        }
    }
    return dwRet;
}

DWORD WINAPI
HandleSetObjectCommand(
IN      LPCWSTR pwszMachine,
IN OUT  LPWSTR  *ppwcArguments,
IN      DWORD   dwCurrentIndex,
IN      DWORD   dwArgCount,
IN      DWORD   dwFlags,
IN      LPCVOID pvData,
OUT     BOOL    *pbDone)
{
    DWORD dwRet;
    
    //
    // This command involves setting something equal to a value
    // provided by the user.  The netsh function we will use
    // to parse the command line will be PreProcessCommand,
    // which the most extensive of the argument handling
    // functions netsh offers.  The first thing to note
    // about PreprocessCommand is that it removes all identifiers
    // from your given command string.  For example, the command
    // "set widgets=10 sprockets=2", after being sent through
    // PreprocessCommand, will result in a arguments that would read
    // "set 10 2" which is much easier to.  Of course, PreprocessCommand
    // has a method for telling the caller which commands those 
    // resulting numbers refer to.
    //
    
    //
    // First we set up our array of valid commands, note that
    // the entries are aligned so that ValidCommands[WIDGETS]
    // and ValidCommands[SPROCKETS] makes sense.
    //
    TAG_TYPE ValidCommands[] =
    {
        {TOKEN_WIDGETS,     NS_REQ_ZERO, FALSE},
        {TOKEN_SPROCKETS,   NS_REQ_ZERO, FALSE},
    };
    
    //
    // We'll need an array of DWORD's that is equal or larger
    // than the total number interesting arguments 
    // (dwArgCount - dwCurrentIndex).  Rather than allocate memory
    // dynamically, we'll just use a stack allocated array of 
    // DWORD's knowing the largest number of arguments there can be. (2)
    // easier.
    //
    const DWORD MAX_ARGS =       2;

    DWORD dwTagType[MAX_ARGS];
    
    
    //
    // Note that if there are too many or too few args for the command
    // to be valid, PreprocessCommand returns something other than
    // NO_ERROR,
    //
    dwRet = PreprocessCommand(
        0,                                      // This argument is not used; should be 0.
        ppwcArguments,                          // Argv style array (netsh passed us this.)
        dwCurrentIndex,                         // Means ppwcArguments[dwCurrentIndex] is the first argument of interest.  
                                                // PpwcArguments[0] is going to be the context,
                                                // PpwcArguments[1] is the first command, 'add' in this case.
                                                // So ppwcARguments[2] is the first argument of interest.
        dwArgCount,                             // Total count of all the args in ppwcArguments.
        ValidCommands,                          // Our array of valid commands struct.
        sizeof(ValidCommands)/sizeof(TAG_TYPE), // Number of entries in the ValidCommands array.
        1,                                      // Minimum number of arguments needed to be a valid command.
        MAX_ARGS,                               // Maximum number of arguments allowed to be a valid command.
        dwTagType);                             // Array of DWORD's used to indicate which command in ValidCommands.
                                                // The token in the command line referred to.
                                                
    //
    // When the call to PreprocessCommand has returned, the values of ValidCommands[x].bPresent tell you which commands 
    // were present in the command line.  Generally, you don't need to use the bPresent BOOL to process the results;
    // Rather, use bPresent to implement more advanced error handling for commands that have complicated command lines
    // (such and such arg was present, but you forgot this other arg.)
    //
    
    //
    // Each consecutive value in the dwTagType array refers to consecutive args in ppwcArguments starting with 
    // ppwcArguments[dwCurrentIndex].  So, when PreprocessCommand returns and dwTagType[0] is 1, that means that 
    // the first arg the user gave netsh was the command referred to by ValidCommands[1], or the "sprockets" command.  
    // As you'll recall, since PreprocessCommand got rid of the "sprockets=" part of "sprockets=2" token, processing 
    // all that remains, "2", is easy.
    //
    
    if (NO_ERROR == dwRet)
    { 
        //
        // Change the return to ERROR_OKAY so netsh spits out confirmation if
        // everything goes ok after this point.
        //
        dwRet = ERROR_OKAY;
        
        //
        // For each argument..
        //
        for (DWORD i = 0; i < (dwArgCount - dwCurrentIndex); i++)
        {
            //
            // Check its corresponding value in the dwTagType array.
            //
            switch (dwTagType[i])
            {
                //
                // This works because i defined these to match with 
                // ValidCommands above.
                //
                // #define WIDGETS                         0
                // #define SPROCKETS                       1
                //
                case WIDGETS:
                    g_CurrentData->WidgetCount = wcstoul(ppwcArguments[dwCurrentIndex + i], NULL, 10);
                    break;
                case SPROCKETS:
                    g_CurrentData->SprocketCount = wcstoul(ppwcArguments[dwCurrentIndex + i], NULL, 10);
                    break;
                default: 
                    // Since 0 and 1 are the only valid values, means the arg wasn't recognized.
                    // Shouldn't reach this point because PreprocessCommand wouldn't have returned
                    // NO_ERROR if this was the case.
                    dwRet = ERROR_INVALID_SYNTAX;
                    break;
            }
        }
    }
    else
    {
        dwRet = ERROR_SHOW_USAGE;
    }

    return dwRet;
}

DWORD WINAPI
HandleResetWidgetCommand(
IN      LPCWSTR pwszMachine,
IN OUT  LPWSTR  *ppwcArguments,
IN      DWORD   dwCurrentIndex,
IN      DWORD   dwArgCount,
IN      DWORD   dwFlags,
IN      LPCVOID pvData,
OUT     BOOL    *pbDone)
{
    
    g_CurrentData->WidgetCount = 0;
    
    //
    // Carry out the command, but return ERROR_SHOW_USAGE
    // to show what happens. netsh should display the 
    // HLP_RESET_OBJECT_WIDGETS_EX message.  Note that 
    // the other commands in this group, "sprockets" and 
    // "all" don't return ERROR_SHOW_USAGE, so there is 
    // no reason to specify the extended help strings 
    // (HLP_RESET_OBJECT_SPROCKETS_EX and 
    // HLP_RESET_OBJECT_ALL_EX) for each command.  They are
    // #define'd though, so that the CREATE_CMD_ENTRY macros 
    // will still work.
    //
    return ERROR_SHOW_USAGE;
}

DWORD WINAPI
HandleResetSprocketCommand(
IN      LPCWSTR pwszMachine,
IN OUT  LPWSTR  *ppwcArguments,
IN      DWORD   dwCurrentIndex,
IN      DWORD   dwArgCount,
IN      DWORD   dwFlags,
IN      LPCVOID pvData,
OUT     BOOL    *pbDone)
{
    g_CurrentData->SprocketCount = 0;
    
    //
    // We'll carry out the command, but show what happens when
    // ERROR_INVALID_SYNTAX is returned - netsh outputs an error
    // message.
    //
    return ERROR_INVALID_SYNTAX;
}

DWORD WINAPI
HandleResetAllCommand(
IN      LPCWSTR pwszMachine,
IN OUT  LPWSTR  *ppwcArguments,
IN      DWORD   dwCurrentIndex,
IN      DWORD   dwArgCount,
IN      DWORD   dwFlags,
IN      LPCVOID pvData,
OUT     BOOL    *pbDone)
{
    g_CurrentData->WidgetCount = 0;
    g_CurrentData->SprocketCount = 0;
    
    //
    // Carry out the command and return NO_ERROR.  Same behavior as
    // returning ERROR_SUPPRESS_OUTPUT.
    // 
    return NO_ERROR;
}