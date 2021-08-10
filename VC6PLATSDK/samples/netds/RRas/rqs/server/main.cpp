//+--------------------------------------------------------------------------
//
//      File:       main.cpp
//
//      Synopsis:   Main file for ras quarantine removal utility (server)
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#include <Rqs.h>
#include <conio.h>

#define RQS_CONTROLS_ACCEPTED SERVICE_ACCEPT_STOP;

//+--------------------------------------------------------------------------
//
// Synopsis: Thread function to execute an instance of the quarantine engine.
//           Used only in stand-alone mode (e.g. not when running as a 
//           service.
//
//+--------------------------------------------------------------------------
DWORD WINAPI
MainThread(
    IN LPVOID lpParameter)
{
    RqsEngine* pEngine = (RqsEngine*)lpParameter;
    HRESULT hr = S_OK;

    hr = pEngine->Initialize();
    if (S_OK != hr)
    {
        printf("Unable to initialize engine %x\n", hr);
        return hr;
    }

    hr = pEngine->Execute();
    if (S_OK != hr)
    {
        printf("Engine execute error: %x\n", hr);
    }        
    
    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Console mode execution
//
//+--------------------------------------------------------------------------
INT 
MainExecute()
{
    HRESULT hr;
    HANDLE hThread = NULL;
    RqsEngine Engine;

    hr = RuSocket::Initialize();
    if (S_OK != hr)
    {
        printf("Socket initialization failed %x\n", hr);
        return -1;
    }

    Engine.SetConsoleTracing(TRUE);

    // Create a thread to execute the server
    //
    hThread = CreateThread(
                    NULL,
                    0,
                    MainThread,
                    (LPVOID)&Engine,
                    0,
                    NULL);
    if (hThread)
    {
        // Wait for the user to enter something.  Signal that we're done when it
        // happens
        //
        printf("Press any key to stop...\n");
        _getch();
        
        printf("Stopping...\n");
        Engine.Stop();
        
        // Wait for the engine to complete its stop
        //
        WaitForSingleObjectEx(hThread, INFINITE, FALSE);
        printf("Stop complete.\n");
        CloseHandle(hThread);
    }
    else
    {
        printf("Unable to create execution thread. %x\n", GetLastError());
    }

    RuSocket::Cleanup();

    return 0;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Console mode execution
//
//+--------------------------------------------------------------------------
INT 
MainConsole(
    int argc, 
    char** argv)
{
    //  Note that argc > 1 was verified in main()
    //
    if (strcmp(argv[1], "/?") == 0)
    {
        printf("Usage:\n");
        printf("  %s /run         Execute quarantine engine\n", argv[0]);
        printf("  %s /?           Display this help\n", argv[0]);
        printf("\n");
    }

    else if (strcmp(argv[1], "/run") == 0)
    {
        MainExecute();
    }

    return 0;
}


//+--------------------------------------------------------------------------
//
// Synopsis: Service control handler
//
//+--------------------------------------------------------------------------
DWORD
WINAPI
ServiceHandlerEx(
    DWORD                 fdwControl,
    DWORD                 fdwEventType,
    LPVOID                lpEventData,
    LPVOID                lpContext)
{
    RqsEngine* pEngine = reinterpret_cast<RqsEngine*>(lpContext);

    if (NULL == pEngine)
    {
        return ERROR_INVALID_PARAMETER;
    }

    pEngine->Trace(
        "ServiceHandlerEx enter.  ctrl=%d type=%d", 
        fdwControl, 
        fdwEventType);

    DWORD dwRetCode =  ERROR_SUCCESS;
    SERVICE_STATUS status;
    ZeroMemory (&status, sizeof(status));
    status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;

    switch (fdwControl)
    {
        case SERVICE_CONTROL_INTERROGATE:
            pEngine->Trace("ServiceHandlerEx: pause/cont/interrogate");
            status.dwCurrentState       = SERVICE_RUNNING;
            status.dwControlsAccepted   = RQS_CONTROLS_ACCEPTED;
            status.dwCheckPoint         = pEngine->GetCheckpoint();
            SetServiceStatus(pEngine->GetServiceHandle(), &status);
            break;

            // Do not worry about shutdown as we do not want to slow down
            // down shutdown time.  We do not need to clean up anything that
            // the reboot would not on its own.  On service stop, make sure to
            // clean up connections in progress.
            //
        case SERVICE_CONTROL_STOP:
            pEngine->Trace("ServiceHandlerEx: stop/shutdown");
            status.dwCurrentState = SERVICE_STOP_PENDING;
            SetServiceStatus(pEngine->GetServiceHandle(), &status);
            pEngine->Stop();
            break;

        default:
            //  We should never get here, but just in case we get a state we did not
            //  expect we will return an invalid parameter error.
            //
            dwRetCode = ERROR_CALL_NOT_IMPLEMENTED;
    }

    return dwRetCode;
} // ServiceHandler

//+--------------------------------------------------------------------------
//
// Synopsis: ServiceMain
//
//+--------------------------------------------------------------------------
VOID WINAPI
ServiceMain(
    DWORD dwArgc, 
    LPTSTR *lpszArgv)
{
    SERVICE_STATUS sStatus;
    HRESULT hr;
    RqsEngine Engine;
    SERVICE_STATUS_HANDLE hService;

    Engine.Trace("Service Main entered.");
    
    ZeroMemory (&sStatus, sizeof(sStatus));
    sStatus.dwServiceType = SERVICE_WIN32_SHARE_PROCESS;

    // Register the control request handler.
    //
    hService = RegisterServiceCtrlHandlerEx(
                    TEXT("rqs"),
                    ServiceHandlerEx,
                    (LPVOID)&Engine);
    if (NULL == hService)
    {
        Engine.Trace("Unable to set service control handler");
        return;
    }
    Engine.SetServiceHandle(hService);

    // Mark the service as start pending
    //
    sStatus.dwCheckPoint = 1;
    sStatus.dwWaitHint = 5000; // Our best guess of RQS's initialization is that it should take no more than 5 seconds
    sStatus.dwCurrentState = SERVICE_START_PENDING;
    SetServiceStatus(hService, &sStatus);

    // Perform initialization.
    //
    BOOL bSocketInitialized = FALSE;
    hr = RuSocket::Initialize();
    if (S_OK != hr)
    {
        Engine.Trace("Socket initialization failed %x", hr);
        sStatus.dwWin32ExitCode = HRESULT_CODE(hr);
        goto exit;
    }
    
    bSocketInitialized = TRUE;

    hr = Engine.Initialize();
    if (S_OK != hr)
    {
        Engine.Trace("Initialization failed %x", hr);
        sStatus.dwWin32ExitCode = HRESULT_CODE(hr);
        goto exit;
    }
    
    // Initialization succeeded.  Update status.
    //
    sStatus.dwControlsAccepted = RQS_CONTROLS_ACCEPTED;
    sStatus.dwCurrentState     = SERVICE_RUNNING;
    SetServiceStatus(hService, &sStatus);

    // Tell the engine to execute. This method will return when all
    // pending clients are serviced and we are ready to stop.
    //
    Engine.Execute();

    //
    // Update return code status.
    //
    sStatus.dwWin32ExitCode = NO_ERROR;
    sStatus.dwServiceSpecificExitCode = 0;


exit:
    
    if (bSocketInitialized)
    {
        RuSocket::Cleanup();
    }

    sStatus.dwControlsAccepted = 0;
    sStatus.dwCurrentState     = SERVICE_STOPPED;
    SetServiceStatus(hService, &sStatus);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Main function
//
//+--------------------------------------------------------------------------
int 
__cdecl 
main(
    int argc, 
    char *argv[ ], 
    char *envp[ ])
{
    SERVICE_TABLE_ENTRY DispatchTable[] = 
    { 
        { L"rqs",        ServiceMain }, 
        {  NULL,         NULL} 
    }; 

    if (argc == 1)
    {
        StartServiceCtrlDispatcher( DispatchTable);
    }
    else
    {
        MainConsole(argc, argv);
    }
    
    return 0;
}

