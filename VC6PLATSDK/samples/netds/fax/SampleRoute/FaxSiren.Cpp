    /*--
    Copyright (c) 1998 - 2000  Microsoft Corporation
    
    Module Name:
    
        faxsiren.cpp
    
    Abstract:
    
        sample routing extension.  Sets an event when a fax is received, writes routing data into a log file.
        
    --*/
    
    #include <windows.h>
    #include <tchar.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <faxroute.h>
    #include <winfax.h>
    //support for sddl is only on win2000 and above
    #define _WIN32_WINNT 0x0500
    #include <sddl.h>
    //
    // macros
    //
    #define ValidString( String ) ((String) ? (String) : L"" )
    
    #ifdef DBG
    #define MYDEBUG( parm ) DebugPrint parm
    #else
    #define MYDEBUG( parm )
    #endif 
    

    //
    // constants
    //
    #define ROUTEITGUID           L"{5797dee0-e738-11d0-83c0-00c04fb6e984}"
    #define FAXSIREN              L"FaxSirenEvent"
    #define LOGNAME               L"%temp%\\ReceiveLog.txt"
    #define ININAME               L"%temp%\\FaxRoute.ini"
    #define SIRENDIR              L"SampleRouteFolder"
    
    #define EXTENSIONNAME         L"SampleRoute Routing Extension"
    #define EXTENSIONFRIENDLYNAME L"SampleRoute: Fax Siren"
    #define EXTENSIONPATH         L"%systemroot%\\system32\\SampleRoute.dll"
    
    #define FAXSIRENMETHOD        L"Siren"
    #define FAXSIRENFRIENDLYNAME  L"Routing Siren"
    #define FAXSIRENFUNCTION      L"RouteIt"
    
    
    //
    // forward declarations
    //
    BOOL
    WriteRoutingInfoIntoIniFile(
        LPWSTR TiffFileName,
        PFAX_ROUTE FaxRoute
        );
    
    BOOL
    AppendFileNametoLogFile(
        LPWSTR TiffFileName,
        PFAX_ROUTE FaxRoute
        );
    
    void 
    DebugPrint(
        LPWSTR,
        ...
        );
    
    BOOL WINAPI
    ExtensionCallback(
        IN HANDLE FaxHandle,
        IN LPVOID Context,
        IN OUT LPWSTR MethodName,
        IN OUT LPWSTR FriendlyName,
        IN OUT LPWSTR FunctionName,
        IN OUT LPWSTR Guid
        );
    
    
    //
    // globals
    //
    PFAXROUTEADDFILE    FaxRouteAddFile;
    PFAXROUTEDELETEFILE FaxRouteDeleteFile;
    PFAXROUTEGETFILE    FaxRouteGetFile;  
    PFAXROUTEENUMFILES  FaxRouteEnumFiles;
    PFAXROUTEMODIFYROUTINGDATA  FaxRouteModifyRoutingData;
    
    HANDLE              hHeap;
    HANDLE              hReceiveEvent;
    CRITICAL_SECTION    csRoute;
    LPWSTR              IniFile = NULL;
    LPWSTR              LogFile = NULL;
    HINSTANCE           MyhInstance;
    
    extern "C"
    DWORD
    DllEntry(
        HINSTANCE hInstance,
        DWORD     Reason,
        LPVOID    Context
        )
    
    /*++
    
    Routine Description:
    
        dll entrypoint 
    
    Arguments:
    
        hInstance   - Module handle
        Reason      - Reason for being called
        Context     - Register context
    
    Return Value:
    
        TRUE for success, otherwise FALSE.
    
    --*/
    
    {
        switch (Reason) {
        case DLL_PROCESS_ATTACH:
          MyhInstance = hInstance;
          DisableThreadLibraryCalls(hInstance);
          break;
        case DLL_PROCESS_DETACH:
    
           //
           // cleanup
           //
           if (hReceiveEvent) CloseHandle(hReceiveEvent);
           break;
        }
    
        return TRUE;
    }
    
    
    STDAPI 
    DllRegisterServer(
        VOID
        )
    /*++
    
    Routine Description:
    
      Function for the in-process server to create its registry entries
    
    Return Value:
    
      S_OK on success
      
    Notes:
      We leverage the DllRegisterServer entrypoint as an easy way to configure
      our routing extension for use on the system.  Note that the extension doesn't
      have any COM code in it per se, but this makes installation much simpler since
      the setup code doesn't have to use custom code to setup the routing extension.
    
    --*/
    {
    	HRESULT RetCode;
    	HMODULE hWinFax;
    	PFAXREGISTERROUTINGEXTENSION pFaxRegisterRoutingExtension;
    	PFAXCONNECTFAXSERVER pFaxConnectFaxServer;
    	PFAXCLOSE pFaxClose;
    	HANDLE hFax;
    	DWORD ExtensionCount = 0;
        TCHAR lpszWinFaxDllLocation[MAX_PATH+13]={0};
    	//
    	// we assume that the routing extension has already been installed into the 
    	// proper location by the setup code.
    	//
    	//we assume that winfax.dll is located in SystemDirectory path
    
    	if (GetSystemDirectory(lpszWinFaxDllLocation, MAX_PATH+1) == 0)
    	{
    		MYDEBUG(( L"GetSystemDirectory failed, ec = %d\n", GetLastError() ));
    		RetCode = E_UNEXPECTED;
    		goto e0;       
    	}
     
    	_tcscat(lpszWinFaxDllLocation,_T("\\winfax.dll") );
		if (_tcslen(lpszWinFaxDllLocation) >= MAX_PATH)
		{
    		MYDEBUG(( L"Library path too long\n", 0 ));
    		RetCode = E_UNEXPECTED;
    		goto e0;
    	}
    
    	hWinFax = LoadLibrary(lpszWinFaxDllLocation);
    	if (!hWinFax)
    	{
    		MYDEBUG(( L"LoadLibrary failed, ec = %d\n", GetLastError() ));
    		RetCode = E_UNEXPECTED;
    		goto e0;
    	}
    
    	pFaxRegisterRoutingExtension = (PFAXREGISTERROUTINGEXTENSION) GetProcAddress(hWinFax, "FaxRegisterRoutingExtensionW" );
    	pFaxConnectFaxServer = (PFAXCONNECTFAXSERVER) GetProcAddress(hWinFax, "FaxConnectFaxServerW");
    	pFaxClose = (PFAXCLOSE) GetProcAddress(hWinFax, "FaxClose" );
    
    	if (!pFaxRegisterRoutingExtension || !pFaxConnectFaxServer || !pFaxClose)
    	{
    		MYDEBUG(( L"GetProcAddress failed, ec = %d\n", GetLastError() ));
    		RetCode = E_UNEXPECTED;
    		goto e1;       
    	}
    
    	if (!pFaxConnectFaxServer( NULL, &hFax ))
    	{
    		MYDEBUG(( L"FaxConnectFaxServer failed, ec = %d\n", GetLastError() ));
    		RetCode = HRESULT_FROM_WIN32( GetLastError() );
    		goto e1;
    	}
    
    	if (!pFaxRegisterRoutingExtension(
    		hFax,
            EXTENSIONNAME,
            EXTENSIONFRIENDLYNAME,
            EXTENSIONPATH,
            ExtensionCallback,
            (LPVOID) &ExtensionCount
            ))
    	{
    		MYDEBUG(( L"FaxRegisterRoutingExtension failed, ec = %d\n", GetLastError() ));
    		RetCode = HRESULT_FROM_WIN32( GetLastError() );
    		goto e2;
    	} 
    	RetCode = S_OK;
    
    e2:
    	pFaxClose( hFax );
    e1:
    	FreeLibrary( hWinFax );
    e0:
    	return RetCode;
    }
    
    
    BOOL WINAPI
    ExtensionCallback(
    	IN HANDLE FaxHandle,
        IN LPVOID Context,
        IN OUT LPWSTR MethodName,
        IN OUT LPWSTR FriendlyName,
        IN OUT LPWSTR FunctionName,
        IN OUT LPWSTR Guid
        )
    /*++
    
    Routine Description:
    
      Callback function for adding our routing extensions
    
    Return Value:
    
      TRUE if we added another extension, FALSE if we're done adding extensions
      
    --*/
    {
    	PDWORD ExtensionCount = (PDWORD) Context;
    
    	//
    	// since we only have one extension, this is a really simple function
    	// --we don't really need the context data above, it's just here to 
    	//   illustrate what you might use the context data for.
    	//
    
        if (ExtensionCount)
    	{
    		MYDEBUG(( L"ExtensionCallback called for extension %d\n", *ExtensionCount ));
        }
    	else
    	{
    		MYDEBUG(( L"context data is NULL, can't continue\n", *ExtensionCount ));
            return FALSE;
        }
    
        if (*ExtensionCount != 0)
    	{
            //
            // we've added all of our methods, return FALSE to signify that we're done
            // 
            return FALSE;
        }
        
    	wcscpy(MethodName,   FAXSIRENMETHOD );
    	wcscpy(FriendlyName, FAXSIRENFRIENDLYNAME );
    	wcscpy(FunctionName, FAXSIRENFUNCTION );
    	wcscpy(Guid,         ROUTEITGUID );
    
        *ExtensionCount += 1;
        return TRUE;
    }
    
    
    
    //
    // required exports
    //
    
    BOOL WINAPI
    FaxRouteInitialize(
        IN HANDLE HeapHandle,
        IN PFAX_ROUTE_CALLBACKROUTINES FaxRouteCallbackRoutines
        )
    /*++
    
    Routine Description:
    
        This functions is called by the fax service to initialize the routing extension.  This function
        should only be called once per instantiation of the fax service
    
    Arguments:
    
        HeapHandle               - Heap handle for memory all allocations
        FaxRouteCallbackRoutines - structure containing callback functions    
    
    Return Value:
    
        TRUE for success, otherwise FALSE.
    
    --*/
    
    {
    	DWORD dwNeeded;
        SECURITY_ATTRIBUTES sa;
    
        //
        // make sure we can understand the structure
        //
        if ( FaxRouteCallbackRoutines->SizeOfStruct < sizeof(FAX_ROUTE_CALLBACKROUTINES) )
    	{
    		MYDEBUG (
    			(L"The passed in SizeOfStruct (%d) is smaller than expected (%d) ", 
    			FaxRouteCallbackRoutines->SizeOfStruct,
    				sizeof(FAX_ROUTE_CALLBACKROUTINES))
    				);
    		return FALSE;
    	}
    
        hHeap = HeapHandle;
        FaxRouteAddFile = FaxRouteCallbackRoutines->FaxRouteAddFile;
        FaxRouteDeleteFile = FaxRouteCallbackRoutines->FaxRouteDeleteFile;
        FaxRouteGetFile = FaxRouteCallbackRoutines->FaxRouteGetFile;
        FaxRouteEnumFiles = FaxRouteCallbackRoutines->FaxRouteEnumFiles;
        FaxRouteModifyRoutingData = FaxRouteCallbackRoutines->FaxRouteModifyRoutingData;
        
        InitializeCriticalSection( &csRoute );
    
        //
        // create a named event
        //
        // note that we need to create a security descriptor with a DACL (everyone read, administrators full control) because we want the named
        // event to be opened by programs that might not be running in same context as the fax service
        //
    
        sa.nLength = sizeof(SECURITY_ATTRIBUTES);
        sa.bInheritHandle = FALSE;
    	//owner is builtin administrators
    	//everyone read ace
    	//built-in administrators full control
        LPCWSTR pwszSD=L"O:BAG:BAD:(A;;GR;;;WD) (A;;GA;;;BA)";
    
    
        if (ConvertStringSecurityDescriptorToSecurityDescriptor(
    														pwszSD,
    														SDDL_REVISION_1, 
    														&(sa.lpSecurityDescriptor), 
    														NULL)) 
        {
    		MYDEBUG(( L"ConvertStringSecurityDescriptorToSecurityDescriptor failed, ec = %d\n", GetLastError() ));
            return FALSE;
        }
    
        hReceiveEvent = CreateEvent(&sa,FALSE,FALSE,FAXSIREN);
    
    	if (!hReceiveEvent)
    	{
    		if (GetLastError() != ERROR_ALREADY_EXISTS)
    		{
    			MYDEBUG (( L"CreateEvent failed, ec = %d\n", GetLastError() ));
    			return FALSE;
    		}
    	}
        LocalFree(sa.lpSecurityDescriptor);
    
        //
        // get path to files for logging, etc.
        //
        dwNeeded = ExpandEnvironmentStrings(ININAME,IniFile,0);    
        IniFile  = (LPWSTR) HeapAlloc(hHeap,HEAP_ZERO_MEMORY,(dwNeeded)*sizeof(WCHAR));
        if (!IniFile)
    	{
    		MYDEBUG((L"HeapAlloc failed, ec = %d\n", GetLastError() ));
    		return FALSE;
        }
        DWORD dwSuccess = ExpandEnvironmentStrings(ININAME,IniFile,dwNeeded);
    
        if (dwSuccess == 0)
    	{
    		return FALSE;
        }
    
        dwNeeded = ExpandEnvironmentStrings(LOGNAME,LogFile,0);
        LogFile  = (LPWSTR) HeapAlloc(hHeap,HEAP_ZERO_MEMORY,sizeof(WCHAR)*(dwNeeded));
        if (!LogFile)
    	{
    		MYDEBUG(( L"HeapAlloc failed, ec = %d\n", GetLastError() ));
    		return FALSE;
        }
        dwSuccess = ExpandEnvironmentStrings(LOGNAME,LogFile,dwNeeded);
    
        if (dwSuccess == 0)
    	{
    		return FALSE;
        }
    
    	MYDEBUG (( L"Logfile : %s\n", LogFile ));
        MYDEBUG (( L"Inifile : %s\n", IniFile ));
        return TRUE;
    }
    
    BOOL WINAPI
    FaxRouteGetRoutingInfo(
        IN  LPWSTR RoutingGuid,
        IN  DWORD DeviceId,
        IN  LPBYTE RoutingInfo,
        OUT LPDWORD RoutingInfoSize
        )
    
    /*++
    
    Routine Description:
    
        This functions is called by the fax service to
        get routing configuration data.
    
    Arguments:
    
        RoutingGuid         - Unique identifier for the requested routing method
        DeviceId            - Device that is being configured
        RoutingInfo         - Routing info buffer
        RoutingInfoSize     - Size of the buffer (in bytes)
    
    Return Value:
    
        TRUE for success, otherwise FALSE.
    
    --*/
    
    {
        //
        // the sample doesn't have any per device routing data, so this function is
        // just stubbed out -- if you have per device routing data, it would be
        // retrieved here.
        //
    	if (RoutingInfoSize)
    	{
    		*RoutingInfoSize = 0;
        }
        return TRUE;
    }
    
    
    BOOL WINAPI
    FaxRouteSetRoutingInfo(
        IN  LPWSTR RoutingGuid,
        IN  DWORD DeviceId,
        IN  LPBYTE RoutingInfo,
        IN  DWORD RoutingInfoSize
        )
    /*++
    
    Routine Description:
    
        This functions is called by the fax service to
        set routing configuration data.
    
    Arguments:
    
        RoutingGuid         - Unique identifier for the requested routing method
        DeviceId            - Device that is being configured
        RoutingInfo         - Routing info buffer
        RoutingInfoSize     - Size of the buffer (in bytes)
    
    Return Value:
    
        TRUE for success, otherwise FALSE.
    
    --*/
    {
        //
        // the sample doesn't have any per device routing data, so this function is
        // just stubbed out -- if you have per device routing data, it would be
        // commited to storage here.
        //
    	return TRUE;
    }
    
    BOOL WINAPI
    FaxRouteDeviceEnable(
        IN  LPWSTR RoutingGuid,
        IN  DWORD DeviceId,
        IN  LONG Enabled
        )
    /*++
    
    Routine Description:
    
        This functions is called by the fax service to determine if a routing extension is enabled or
        to enable a routing extension
    
    Arguments:
    
        RoutingGuid         - Unique identifier for the requested routing method
        DeviceId            - Device that is being configured
        Enabled             - meaning differs based on context (see FAXROUTE_ENABLE enumerated type)
    
    Return Value:
    
        depends on context.
    
    --*/
    {
        //
        // -note that we make the assumption that there are never more than 4 devices in this sample
        // -also note that this isn't thread safe
        // -a real routing extension wouldn't make these assumptions, and would probably have some 
        //  persistent store which kept track of the enabled state of an extension per-routing method
        //
    	static long MyEnabled[4] = {STATUS_ENABLE,STATUS_ENABLE,STATUS_ENABLE,STATUS_ENABLE};
        static DWORD DeviceIdIndex[4] = {0,0,0,0};
        DWORD count;
    
        //
        // make sure that we're dealing with our routing method
        // 
        if (wcsicmp(RoutingGuid,ROUTEITGUID) != 0)
    	{
    		MYDEBUG (( L"Passed a GUID (%s) for a method not in this extension!\n", RoutingGuid ));
            return FALSE;
        }
        
        for (count = 0 ; count <4; count ++)
    	{
    		if (DeviceIdIndex[count] == DeviceId)
    		{
    			break;
            }
    		else if (DeviceIdIndex[count] == 0)
    		{
    			DeviceIdIndex[count] = DeviceId;
            }
        }
    
        if (Enabled == QUERY_STATUS)
    	{
    		return MyEnabled[count];
        }
    
        MYDEBUG ((
    		L"Setting enabled state to %s\n", 
            (Enabled == STATUS_DISABLE) ? L"STATUS_DISABLE" : L"STATUS_ENABLE" 
            ));
    
    	MyEnabled[count] = Enabled;
        return TRUE;
    }
    
    
    BOOL WINAPI
    FaxRouteDeviceChangeNotification(
        IN  DWORD DeviceId,
        IN  BOOL  NewDevice
        )
    
    /*++
    
    Routine Description:
    
        This functions is called by the fax service to alert the routing extension that a device 
        has changed
    
    Arguments:
    
        DeviceId            - Device that has changed 
        NewDevice           - TRUE means device was added, FALSE means a device was removed 
    
    Return Value:
    
        TRUE for success
    
    --*/
    {
    	//
    	// We don't have any per device routing data, so this is just stubbed out
    	//
    	return TRUE;
    }
    
    
    //
    // routing method(s)
    //
    
    
    BOOL WINAPI
    RouteIt(
    	PFAX_ROUTE FaxRoute,
    	PVOID *FailureData,
    	LPDWORD FailureDataSize
    	)
    
    /*++
    
    Routine Description:
    
        This functions is called by the fax service to
        route a received fax.
    
    Arguments:
    
        FaxRoute            - Routing information
        FailureData         - Failure data buffer
        FailureDataSize     - Size of failure data buffer
    
    Return Value:
    
        TRUE for success, otherwise FALSE.
    
    --*/
    
    {
    	WCHAR TiffFileName[MAX_PATH];
        WCHAR Dir[_MAX_DIR],Drive[_MAX_DRIVE],File[_MAX_FNAME],Ext[_MAX_EXT];
        WCHAR CopyOfTiff[MAX_PATH+1];
        
        DWORD Size = sizeof(TiffFileName);
    
        //
        // serialize access to this function so that data is written into the logfile accurately
        //
        EnterCriticalSection( &csRoute );
        
    	if (!FaxRouteGetFile(
    		FaxRoute->JobId,
            1,
            TiffFileName,
            &Size))
    	{
    		MYDEBUG(( L"Couldn't FaxRouteGetFile, ec = %d", GetLastError() ));
    		LeaveCriticalSection( &csRoute );
    		return FALSE;
        }
    
        MYDEBUG ((
    		L"Received fax %s\n\tCSID :%s\n\t Name : %s\n\t #: %s\n\tDevice: %s\n", 
            TiffFileName,
            ValidString ( FaxRoute->Csid ),
            ValidString ( FaxRoute->ReceiverName),
            ValidString ( FaxRoute->ReceiverNumber),
            ValidString ( FaxRoute->DeviceName ) 
    		));
     
    	_wsplitpath(TiffFileName, Drive, Dir, File, Ext );
		if ((wcslen(Drive) + wcslen(SIRENDIR) + wcslen(File) + wcslen(Ext)) >= MAX_PATH) {
    		LeaveCriticalSection( &csRoute );
    		return FALSE;
        }

        wsprintf(CopyOfTiff,L"%s\\%s\\%s%s",Drive,SIRENDIR,File,Ext);
    
        //
        // copy the tiff so it persists after this routine exits
        //
        CopyFile(TiffFileName,CopyOfTiff,FALSE);
    
        //
        // write some logging data
        // 
        WriteRoutingInfoIntoIniFile(CopyOfTiff,FaxRoute);
        AppendFileNametoLogFile(TiffFileName, FaxRoute);
    
        //
        // signal event -- another application could use this named event to do something 
        // with the file that was just copied into this directory 
        // (note that the INI file isn't thread-safe accross applications, we could have the routing data overwritten by
        //  another fax being received)
        //
        SetEvent(hReceiveEvent);
    
        //
        // service needs to be able to interact with the current desktop for this to work
        //
        MessageBeep(MB_ICONEXCLAMATION);
    
        LeaveCriticalSection( &csRoute );
        return TRUE;
    }
    
    
    //
    // utility fcn's
    //
    
    BOOL WriteRoutingInfoIntoIniFile(LPWSTR TiffFileName,PFAX_ROUTE FaxRoute) 
    {
    	WCHAR Buffer[MAX_PATH*2];
        ULONG ulBufferSize = sizeof(Buffer);
		ULONG ulArraySize = ulBufferSize/sizeof(Buffer[0]);
    	//
    	// write each routing info member into ini file
    	// 
       
    	//filename
    	ZeroMemory(Buffer,ulBufferSize); 
		wcsncpy(Buffer,ValidString (TiffFileName), ulArraySize - 1); 
    	WritePrivateProfileString(
    		L"RoutingInfo",// pointer to section name 
    		L"FileName",// pointer to key name 
    		Buffer,   // pointer to string to add 
    		IniFile // pointer to initialization filename 
    		);
    
    
    	//jobid
	 	ZeroMemory(Buffer,ulBufferSize); 
    	wsprintf(Buffer, L"%u",FaxRoute->JobId);
    	WritePrivateProfileString(
    		L"RoutingInfo",// pointer to section name 
    		L"JobId",// pointer to key name 
    		Buffer,   // pointer to string to add 
    		IniFile // pointer to initialization filename 
    		);
    
    	//elapsedtime
	 	ZeroMemory(Buffer,ulBufferSize); 
    	wsprintf(Buffer, L"%u",FaxRoute->ElapsedTime);
    	WritePrivateProfileString(
    		L"RoutingInfo",// pointer to section name 
    		L"ElapsedTime",// pointer to key name 
    		Buffer,   // pointer to string to add 
    		IniFile // pointer to initialization filename 
    		);
    
    	//receivetime
	 	ZeroMemory(Buffer,ulBufferSize);
    	wsprintf(Buffer, L"%u",FaxRoute->ReceiveTime);
    	WritePrivateProfileString(
    		L"RoutingInfo",// pointer to section name 
    		L"ReceiveTime",// pointer to key name 
    		Buffer,   // pointer to string to add 
    		IniFile // pointer to initialization filename 
    		);
    	
    	//pagecount
	 	ZeroMemory(Buffer,ulBufferSize);
    	wsprintf(Buffer, L"%u",FaxRoute->PageCount);
    	WritePrivateProfileString(
    		L"RoutingInfo",// pointer to section name 
    		L"PageCount",// pointer to key name 
    		Buffer,   // pointer to string to add 
    		IniFile // pointer to initialization filename 
    		);
    
    	//Csid
	 	ZeroMemory(Buffer,ulBufferSize);
	 	wcsncpy(Buffer,ValidString (FaxRoute->Csid), ulArraySize - 1);
    	WritePrivateProfileString(
    		L"RoutingInfo",// pointer to section name 
    		L"Csid",// pointer to key name 
    		Buffer,   // pointer to string to add 
    		IniFile // pointer to initialization filename 
    		);
    
    	//CallerId
	 	ZeroMemory(Buffer,ulBufferSize);
	 	wcsncpy(Buffer, ValidString (FaxRoute->CallerId ), ulArraySize - 1);
    	WritePrivateProfileString(
    		L"RoutingInfo",// pointer to section name 
    		L"CallerId",// pointer to key name 
    		Buffer,   // pointer to string to add 
    		IniFile // pointer to initialization filename 
    		);
    
    	//RoutingInfo
	 	ZeroMemory(Buffer,ulBufferSize);
	 	wcsncpy(Buffer, ValidString (FaxRoute->RoutingInfo ), ulArraySize - 1);
    	WritePrivateProfileString(
    		L"RoutingInfo",// pointer to section name 
    		L"RoutingInfo",// pointer to key name 
    		Buffer,   // pointer to string to add 
    		IniFile // pointer to initialization filename 
    		);
    
    	//ReceiverName
	 	ZeroMemory(Buffer,ulBufferSize);
	 	wcsncpy(Buffer, ValidString (FaxRoute->ReceiverName ), ulArraySize - 1);
    	WritePrivateProfileString(
    		L"RoutingInfo",// pointer to section name 
    		L"ReceiverName",// pointer to key name 
    		Buffer,   // pointer to string to add 
    		IniFile // pointer to initialization filename 
    		);
    
    	//ReceiverNumber
	 	ZeroMemory(Buffer,ulBufferSize);
		wcsncpy(Buffer, ValidString (FaxRoute->ReceiverNumber ), ulArraySize - 1);
    	WritePrivateProfileString(
    		L"RoutingInfo",// pointer to section name 
    		L"ReceiverNumber",// pointer to key name 
    		Buffer,   // pointer to string to add 
    		IniFile // pointer to initialization filename 
    		);
    
    	//DeviceName
	 	ZeroMemory(Buffer,ulBufferSize);
	 	wcsncpy(Buffer, ValidString (FaxRoute->DeviceName ), ulArraySize - 1);
    	WritePrivateProfileString(
    		L"RoutingInfo",// pointer to section name 
    		L"DeviceName",// pointer to key name 
    		Buffer,   // pointer to string to add 
    		IniFile // pointer to initialization filename 
    		);
    
    	//DeviceId
	 	ZeroMemory(Buffer,ulBufferSize);
    	wsprintf(Buffer, L"%u",FaxRoute->DeviceId );
    	WritePrivateProfileString(
    		L"RoutingInfo",// pointer to section name 
    		L"DeviceId",// pointer to key name 
    		Buffer,   // pointer to string to add 
    		IniFile // pointer to initialization filename 
    		);
    
    	return TRUE;
    }
    
    BOOL AppendFileNametoLogFile (LPWSTR TiffFileName,PFAX_ROUTE FaxRoute) 
    {
    	HANDLE hFile = INVALID_HANDLE_VALUE;
    	WCHAR Buffer[2*MAX_PATH];
    	WCHAR szDateTime[104];
    	WCHAR lpDate[50];
    	WCHAR lpTime[50];
    
    	DWORD dwWrote = 0;
       
    	hFile = CreateFile(
    		LogFile,
    		GENERIC_WRITE,
    		FILE_SHARE_WRITE,
    		NULL,
    		OPEN_ALWAYS,
    		FILE_ATTRIBUTE_NORMAL,
    		NULL
    		);
    
    	if (hFile == INVALID_HANDLE_VALUE)
    	{
    		MYDEBUG (( L"CreateFile failed, ec = %d\n", GetLastError() ));
    		return FALSE;
    	}
    
    	if ( !GetDateFormat(
    		LOCALE_SYSTEM_DEFAULT,
    		DATE_SHORTDATE,
    		NULL,                // use system date
    		NULL,                // use locale format
    		lpDate,
    		(sizeof lpDate)/(sizeof lpDate[0]) ) )
    	{
    		MYDEBUG(( L"GetDateFormat failed, ec = %d\n", GetLastError() ));
    		return FALSE;
    	}
        
    
    	if ( !GetTimeFormat(
    		LOCALE_SYSTEM_DEFAULT,
    		TIME_NOSECONDS,
    		NULL,                // use system time
    		NULL,                // use locale format
    		lpTime,
    		(sizeof lpTime)/(sizeof lpTime[0]) ) )
    	{
    		MYDEBUG(( L"GetTimeFormat failed, ec = %d\n", GetLastError() ));
    		return FALSE;
    	}
    
    	wsprintf( szDateTime, TEXT("%-8s %-8s"), lpDate, lpTime);
    
    	wsprintf(Buffer, L"%s :Received %s\r\n",ValidString(szDateTime),ValidString(TiffFileName));
    
    	SetFilePointer(hFile,0,0,FILE_END);
    
    	if (!WriteFile(hFile,Buffer,lstrlen(Buffer)*sizeof(WCHAR),&dwWrote,NULL))
    	{
    		MYDEBUG (( L"WriteFile() failed, ec = %d\n", GetLastError() ));
    		CloseHandle(hFile);
    		return FALSE;
    	}
    
    	CloseHandle(hFile);
       return TRUE;
    }
    
    void
    DebugPrint(LPTSTR Format, ...)
    
    /*++
    
    Routine Description:
    
        Prints a debug string
    
    Arguments:
    
        format      - wsprintf() format string
        ...         - Variable data
    
    Return Value:
    
        None.
    
    --*/
    
    {
    	TCHAR Buffer[1024];
    	TCHAR AppName[MAX_PATH];
    	TCHAR ShortName[MAX_PATH];
    	SYSTEMTIME CurrentTime;
    	int len=0;
    
    	va_list marker;
    
    	ZeroMemory(AppName,MAX_PATH);
    	ZeroMemory(ShortName,MAX_PATH);
    
    	if (  GetModuleFileName(
    		NULL, // handle to module to find filename for 
    		AppName,
    		MAX_PATH)
    		)
    	{
    		_tsplitpath(AppName,NULL,NULL,ShortName,NULL);
    	}
    
    	ZeroMemory(&CurrentTime,sizeof(SYSTEMTIME));
    
    	GetLocalTime(&CurrentTime);
    
    	wsprintf(
    		Buffer, 
    		TEXT ("%02d.%02d.%02d.%03d %s: "),
    		CurrentTime.wHour,
    		CurrentTime.wMinute,
    		CurrentTime.wSecond,
    		CurrentTime.wMilliseconds,
    		ShortName
    		);
    
    	// init arg list
    	va_start(marker,Format);
    
    	// point to rest of blank buffer
    	len = lstrlen(Buffer);
    
    	_vsntprintf(
    		&Buffer[len], // don't want to overwrite the start of the string!
            sizeof(Buffer) - len - 3, //size of the rest of the buffer
            Format,
            marker
    		);
       
    	len = lstrlen(Buffer);
    	if (Buffer[len-1] == L'\n' )
    	{   
    		Buffer[len-1] = L'\r';
    		Buffer[len] = L'\n';
    		Buffer[len+1] = 0;
    	}
    	else
    	{
    		Buffer[len] = L'\r';
    		Buffer[len+1] = L'\n';
    		Buffer[len+2] = 0;
    	}
    	OutputDebugString(Buffer);
    	va_end(marker);
    }
