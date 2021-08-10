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
#define UNICODE
#include "nshsamp.h"

//
// Global variables.
//
extern SAMPLE_HELPER_DATA g_OnlineData = {0, 0, 0, 0, FALSE, 0, LOW};
extern SAMPLE_HELPER_DATA g_OfflineData = {0, 0, 0, 0, FALSE, 0, LOW};
extern PSAMPLE_HELPER_DATA g_CurrentData = &g_OnlineData;
extern HANDLE g_hModule = 0;

//
// Declare the command structs.  You need to declare the
// structs based on how you will be grouping them.  So,
// for example, the three 'show' commands should be in
// the same struct so you can put them in a single group.
//
CMD_ENTRY g_TopLevelCommands[] =
{
    CREATE_CMD_ENTRY(SHOW_OBJECT, HandleShowObjectCommand),
    // Online, so this command won't be available in offline mode.
    CREATE_CMD_ENTRY_EX_VER(ADD_OBJECT, HandleAddObjectCommand, CMD_FLAG_ONLINE, CheckRunningOnWhistler),  
    // Interactive, so this command can't be used from the command line (see SDK).
    CREATE_CMD_ENTRY_EX(SET_OBJECT, HandleSetObjectCommand, CMD_FLAG_INTERACTIVE)  
};

//
// One nice thing about a grouped command like is that you can specify a different function
// for each command, and when that function is entered, two tokens have already been parsed
// for you.  In this example, if the user types "reset widgets", netsh will call 
// HandleResetWidgetCommand, and since there are no other arguments to parse, we can just
// reset the widget count.  Compare this to a top level command, where only the first token
// parsed for you.  In that case, you have to parse the rest of the command line to determine
// what to do, as in HandleShowObjectCommand or HandleAddObjectCommand.  On the other hand,
// now you need three functions whereas before you only needed one.
//
CMD_ENTRY g_ResetObjects[] =
{
    CREATE_CMD_ENTRY(RESET_OBJECT_WIDGETS,      HandleResetWidgetCommand),
    CREATE_CMD_ENTRY(RESET_OBJECT_SPROCKETS,    HandleResetSprocketCommand),
    CREATE_CMD_ENTRY(RESET_OBJECT_ALL,          HandleResetAllCommand)
};

CMD_ENTRY g_ShowError[] =
{
    CREATE_CMD_ENTRY(SHOWERROR,                 HandleShowErrorCommand)
};

CMD_ENTRY g_RandomCommands[] =
{
    CREATE_CMD_ENTRY(SET_INTERFACE,             HandleSetInterfaceCommand),
    CREATE_CMD_ENTRY(SET_GATEWAY,               HandleSetGatewayCommand)
};

CMD_ENTRY g_TopLevelSubInterfaceCommands[] =
{
    CREATE_CMD_ENTRY(SHOW_RANDOM,               HandleShowRandomSettingsCommand)
};

//
// Declare the group structs.
//
CMD_GROUP_ENTRY     g_Sample_Commands[] =
{
    // Local, so this group isn't valid for remote machines.
    CREATE_CMD_GROUP_ENTRY_EX(RESET_OBJECT, g_ResetObjects, CMD_FLAG_LOCAL)  
};

CMD_GROUP_ENTRY     g_SampleInterface_Commands[] =
{
    //
    // We'll specify our version callback function for this group.  Netsh calls
    // this function with parameters indicating what type of operating system
    // this command is to be executed on.  The callback, CheckRunningOnWhistler
    // in this case, should return TRUE if it finds that the operating system
    // is of acceptable type.  Otherwise, the callback should return FALSE
    // to indicate that this group is not valid for the indicated operating
    // system.  See the SDK for the explanation of the values passed to the 
    // version callback function.  Note that we chose not to specify any flags
    // for this group (thus the 0) but we could have.
    //
    CREATE_CMD_GROUP_ENTRY_EX_VER(SET_RANDOM_STUFF, g_RandomCommands, 0, CheckRunningOnWhistler)
};


DWORD WINAPI
GenericStopHelper(
IN      DWORD   dwReserved)
{
    //
    // Here we would perform any work that needs to be done
    // when netsh exits and helpers are stopped.  This would
    // include things like closing open handles, freeing
    // allocated memory, etc.  Note that you can have
    // a different StopHelper function for each helper
    // you register. (The NS_HELPER_ATTRIBUTES.pfnStop param
    // of the call to RegisterHelper in InitHelper below.)
    //
    return NO_ERROR;   
}

DWORD WINAPI
CommitFn(
IN      DWORD   dwAction)
{
    //
    // The handling of this action is admittedly simple in this example.
    // We simply have two copies of the data that we persist and consider
    // one the "online" set of data and one the "offline" set of data.
    // However, since neither the offline nor online sets of data need to
    // be "applied" to anything, it makes the distinction between them
    // somewhat meaningless.  The scheme used to support online/offline modes
    // is generally left up to the developer.
    //
    switch (dwAction)
    {
        case NETSH_COMMIT:
            //
            // Change to commit mode, otherwise known as online.
            //
            g_CurrentData = &g_OnlineData;
            break;
            
        case NETSH_UNCOMMIT:
            //
            // Change to uncommit mode, meaning all our data goes
            // to our offlinedata buffer.
            //
            g_CurrentData = &g_OfflineData;
            break;
            
        case NETSH_FLUSH:
            //
            // Flush all uncommitted changes.  We'll do this by
            // overwriting whatever data is in g_OfflineData with
            // what is in g_OnlineData.
            //
            CopyMemory(&g_OfflineData, &g_OnlineData, sizeof(SAMPLE_HELPER_DATA));
            break;
            
        case NETSH_SAVE:
            //
            // Copy the memory from our offline struct to our 
            // online one, then "apply" it.
            //
            CopyMemory(&g_OnlineData, &g_OfflineData, sizeof(SAMPLE_HELPER_DATA));
            g_CurrentData = &g_OnlineData;
            
            // SomeFunctionToApplyOurData(g_OnlineData);
            
            break;
            
        default:
            break;
    }       
    return NO_ERROR;
}

DWORD WINAPI
ConnectFn(
IN  LPCWSTR  pwszMachine)
{
    //
    // This function is called whenever the machine name changes.
    // If the context this was called for (you can specify a connect
    // function on a per context basis, see RegisterContext) is
    // supposed to be remotable, then the helper should verify
    // connectivity to the machine specified by pwszMachine and 
    // return an error if unable to reach the machine.
    //
    
    //
    // This is also where the helper might want to call RegisterContext
    // again on a context to remove or add commands at will.  This allows
    // the commands in your context to be dynamic, that is, commands
    // may be added and removed at will.  However, the versioning
    // functions tend to make a dynamic context unnecessary, as most
    // dynamic command changes are needed because of differing OS's the
    // commands are used on.  Note that NULL for pwszMachine indicates
    // that the machine to be connected to is the local machine.  When
    // and if the connect function returns an error code, the command
    // that was going to be executed (whether a context command or 
    // entering a context) will fail.
    //
    
    //
    // Uncomment this line to see how often the Connect function is called
    // and what gets passed to it.
    //
    //PrintMessageFromModule(g_hModule, GEN_CONNECT_SHOWSTRING, pwszMachine);
    
    return NO_ERROR;
}

BOOL WINAPI
CheckRunningOnWhistler(
IN  UINT     CIMOSType,
IN  UINT     CIMOSProductSuite,           
IN  LPCWSTR  CIMOSVersion,                
IN  LPCWSTR  CIMOSBuildNumber,            
IN  LPCWSTR  CIMServicePackMajorVersion,  
IN  LPCWSTR  CIMServicePackMinorVersion,  
IN  UINT     CIMProcessorArchitecture,
IN  DWORD    dwReserved
)
{
    //
    // Leave this code in here so it can be uncommented and recompiled.
    // Its output can be kind of distracting if on by default, so it 
    // was turned off.
    //
    /*
    PrintMessage(L"\n"
                 L"Entered CheckRunningOnWhistler.  Received arguments of \n"
                 L"Type %1!lu!\n"
                 L"ProductSuite %2!lu!\n"
                 L"Version %3!s!\n"
                 L"BuildNumber %4!s!\n"
                 L"ServicePackMajorVersion %5!s!\n"
                 L"ServicePackMinorVersion %6!s!\n"
                 L"ProcessorArchitecture %7!lu!\n",
                 CIMOSType,
                 CIMOSProductSuite,
                 CIMOSVersion,
                 CIMOSBuildNumber,
                 CIMServicePackMajorVersion,
                 CIMServicePackMinorVersion,
                 CIMProcessorArchitecture);
    */
             
    return TRUE;
}

DWORD WINAPI
InitHelperDll(
IN  DWORD   dwNetshVersion,
OUT PVOID	pReserved)
{   
    DWORD                   dwRet;
    NS_HELPER_ATTRIBUTES    MyAttributes;

    //
    // We could also implement a DllMain to get
    // this handle.
    //
    g_hModule = GetModuleHandle(L"nshsamp.dll");
    
    ZeroMemory(&MyAttributes, sizeof(MyAttributes));
    MyAttributes.dwVersion      = SAMPLE_HELPER_VERSION;
    
    //
    // This specifies the function netsh should call to
    // initialize the contexts for this helper.  We'll
    // use the same function for all the helpers, because
    // we can tell based on the pguidParent arg passed
    // to StartHelpers() which helper we need to register
    // contexts for.  If necessary, use a different start
    // function for each helper.  Just set the 
    // MyAttributes.pfnStart parameter before each call 
    // to RegisterHelper.
    //
    MyAttributes.pfnStart       = StartHelpers;
    
    //
    // We'll use a generic stop function for all helpers,
    // rather than one for each for simplicity.  One for
    // each is allowed, of course.
    //
    MyAttributes.pfnStop        = GenericStopHelper;

    //
    // Set the GUID of our helper.
    //
    MyAttributes.guidHelper     = g_ObjectGuid;
    
    //
    // Specify g_RootGuid as the parent helper to indicate 
    // that any contexts registered by this helper will be top 
    // level contexts.  Note that NULL as the parent GUID means
    // the same thing.
    //
    dwRet = RegisterHelper(&g_RootGuid, &MyAttributes);
    if (NO_ERROR == dwRet)
    {
        //
        // Set the GUID of our helper.
        //
        MyAttributes.guidHelper = g_SubContext;
        
        //
        // We want this helper's contexts to show up as children of 
        // g_ObjectGuid's context(s), so we specify it as the parent
        // helper istead of g_RootGuid.
        //
        dwRet = RegisterHelper(&g_ObjectGuid, &MyAttributes);
        if (NO_ERROR == dwRet)
        {
            //
            // Set the GUID of our helper.
            //
            MyAttributes.guidHelper = g_SampleInterface;
            
            //
            // Again, we want this helper's contexts to show up as children of
            // ifmon.dll's 'interface' context, so we specify it here.  To
            // see a list of all helpers, contexts, and their associated
            // GUID's, type 'show helper' within netsh.
            //
            dwRet = RegisterHelper(&g_Interface, &MyAttributes);
        }
    }
    return dwRet;
}

DWORD WINAPI
StartHelpers(
IN CONST GUID * pguidParent,
IN DWORD        dwVersion)
{
    BOOL                    bFoundMatch = TRUE;
    DWORD                   dwRet = ERROR_INVALID_PARAMETER;
    NS_CONTEXT_ATTRIBUTES   ContextAttributes;

    ZeroMemory(&ContextAttributes, sizeof(ContextAttributes));
    
    ContextAttributes.dwVersion         = SAMPLE_HELPER_VERSION;

    if (IsEqualGUID(*pguidParent, g_RootGuid))
    {
        //
        // The parent is the netsh root GUID, and the only
        // helper we have that registers root contexts is 
        // the 'object' helper, so set the relevant info.
        //
        ContextAttributes.dwFlags           = 0; 
        //
        // This is the default, but we are specifying for clarity.
        //
        ContextAttributes.ulPriority        = DEFAULT_CONTEXT_PRIORITY;
        ContextAttributes.pwszContext       = TOKEN_SAMPLE;
        ContextAttributes.guidHelper        = g_ObjectGuid;
        ContextAttributes.ulNumTopCmds      = sizeof(g_TopLevelCommands)/sizeof(CMD_ENTRY);
        ContextAttributes.pTopCmds          = (CMD_ENTRY (*)[])g_TopLevelCommands;
        ContextAttributes.ulNumGroups       = sizeof(g_Sample_Commands)/sizeof(CMD_GROUP_ENTRY);
        ContextAttributes.pCmdGroups        = (CMD_GROUP_ENTRY (*)[])g_Sample_Commands;
        ContextAttributes.pfnCommitFn       = CommitFn;
        ContextAttributes.pfnConnectFn      = ConnectFn;
        ContextAttributes.pfnDumpFn         = DumpSample;
        //
        // Just like commands or groups, you can specify a version
        // checking function for contexts.
        //
        ContextAttributes.pfnOsVersionCheck = CheckRunningOnWhistler;
    }
    else if (IsEqualGUID(*pguidParent, g_ObjectGuid))
    {
        //
        // The only helper we have that registers under
        // g_ObjectGuid is the 'subcontext' helper.
        //
        ContextAttributes.dwFlags           = 0;
        
        //
        // This is the default, but we are specifying for clarity.
        //
        ContextAttributes.ulPriority        = DEFAULT_CONTEXT_PRIORITY;
        
        ContextAttributes.pwszContext       = TOKEN_SUBCONTEXT;
        ContextAttributes.guidHelper        = g_SubContext;
        ContextAttributes.ulNumTopCmds      = sizeof(g_ShowError)/sizeof(CMD_ENTRY);
        ContextAttributes.pTopCmds          = (CMD_ENTRY (*)[])g_ShowError;
        ContextAttributes.ulNumGroups       = 0;
        ContextAttributes.pCmdGroups        = NULL;
        ContextAttributes.pfnCommitFn       = CommitFn;
        ContextAttributes.pfnConnectFn      = ConnectFn;
        ContextAttributes.pfnOsVersionCheck = NULL;
        
        //
        // We're choosing to have no dump function.
        // (There isn't really anything to dump for a 
        // function that just outputs error strings.)
        //
        ContextAttributes.pfnDumpFn         = NULL;
    }
    else if (IsEqualGUID(*pguidParent, g_Interface))
    {
        //
        // The only helper we have that registers under
        // g_Interface is the 'sampleinterface' helper.
        //
        
        //
        // Specifies that ulPriority should be paid attention.
        //
        ContextAttributes.dwFlags           = (DWORD)CMD_FLAG_PRIORITY;
        
        //
        // We change the priority of this so that its dump
        // function will be called before other dump functions.
        // UlPriority of 0 is the highest priority.  This can
        // be useful if some contexts require information
        // enumerated by a different context - for example
        // the 'interface' context has a ulPriority of 10 so
        // that other contexts can use the friendly names it
        // generates.  Those friendly names would otherwise
        // be inaccessible.  Note that the ulPriority of
        // this DumpFn is 0, so if you do a dump in the 'interface'
        // context, you would see this contexts dump info before
        // interface's dump information, even though this context
        // is located in a subhelper to 'interface'.
        //
        ContextAttributes.ulPriority        = 0; 
        ContextAttributes.pwszContext       = TOKEN_SAMPLEINTERFACE;
        ContextAttributes.guidHelper        = g_SampleInterface;
        ContextAttributes.ulNumTopCmds      = sizeof(g_TopLevelSubInterfaceCommands)/sizeof(CMD_ENTRY);
        ContextAttributes.pTopCmds          = (CMD_ENTRY (*)[])g_TopLevelSubInterfaceCommands;
        ContextAttributes.ulNumGroups       = sizeof(g_SampleInterface_Commands)/sizeof(CMD_GROUP_ENTRY);
        ContextAttributes.pCmdGroups        = (CMD_GROUP_ENTRY (*)[])g_SampleInterface_Commands;
        ContextAttributes.pfnCommitFn       = CommitFn;
        ContextAttributes.pfnConnectFn      = ConnectFn;
        ContextAttributes.pfnDumpFn         = DumpSampleInterface;
        ContextAttributes.pfnOsVersionCheck = NULL;
    }
    else
    {
        //
        // If netsh passed us some parent guid that we
        // haven't heard of, error out.
        //
        bFoundMatch = FALSE;
    }
    
    if (bFoundMatch)
    {
        dwRet = RegisterContext(&ContextAttributes);
    }
    
    return dwRet;
}
