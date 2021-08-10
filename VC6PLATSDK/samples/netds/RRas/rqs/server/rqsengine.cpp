//+--------------------------------------------------------------------------
//
//      File:       RqsEngine.cpp
//
//      Synopsis:   Engine that drives the server-side ras quarantine removal
//                  utility.
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#include <rqs.h>

//+--------------------------------------------------------------------------
//
// Synopsis: Structure to be passed to the callback functions 
//
//+--------------------------------------------------------------------------
typedef struct _RqsEngineCbInfo
{
    RqsEngine* pEngine;
    RqsClient* pClient;
} RqsEngineCbInfo;

//+--------------------------------------------------------------------------
//
// Synopsis: Instantiates a quarantine engine object 
//
//+--------------------------------------------------------------------------
RqsEngine::RqsEngine() : m_ulClientCount(0), m_hService(NULL), m_dwCheckPoint(0),
                         m_hServer(NULL), m_hInstMprApi(NULL), 
                         m_fConsoleTrace(FALSE), m_dwTraceId(INVALID_TRACEID),
                         m_fDebugTrace(FALSE), m_fRtTrace(FALSE),
                         m_hkTrace(NULL), m_hkConfig(NULL), m_hLog(NULL),
                         m_Config(), m_sServer(), m_eSocketAccept(),
                         m_eSocketRead(), m_eQuit(), m_eTrace(), 
                         m_rwlConfig(), m_csClientsLock(), m_bRegisteredForConnectionNotification(FALSE)
{
    m_szInternalAddress[0] = '\0';
}

//+--------------------------------------------------------------------------
//
// Synopsis: Cleans up a quarantine engine object 
//
//+--------------------------------------------------------------------------
RqsEngine::~RqsEngine()
{
    Clear();

    if (m_bRegisteredForConnectionNotification)
    {
        DeregisterForConnectionNotification();
    }
    if (m_hkConfig)
    {
        RegCloseKey(m_hkConfig);
    }
    if (m_hkTrace)
    {
        RegCloseKey(m_hkTrace);
    }
    if (m_hServer)
    {
        MprAdminServerDisconnect(m_hServer);
    }
    if (m_hInstMprApi)
    {
        FreeLibrary(m_hInstMprApi);
    }
    if (m_dwTraceId != INVALID_TRACEID)
    {
        TraceDeregisterExA( m_dwTraceId, 0 );
    }
    if (m_hLog)
    {
        DeregisterEventSource(m_hLog);
    }
    
}

//+--------------------------------------------------------------------------
//
// Synopsis: Clears a quarantine engine object 
//
//+--------------------------------------------------------------------------
VOID
RqsEngine::Clear()
{
    m_Config.Clear();
    m_sServer.Close();
    m_ulClientCount = 0;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Helper method initializes all of the events 
//
//+--------------------------------------------------------------------------
HRESULT 
RqsEngine::InitializeEvents()
{
    HRESULT hr = S_OK;
    
    __try
    {   
        hr = m_eQuit.Initialize(NONSIGNALED, FALSE);
        RU_LEAVE_IF_NOT_OK(hr);
        m_dwCheckPoint++;

        hr = m_eConfig.Initialize(NONSIGNALED, FALSE);
        RU_LEAVE_IF_NOT_OK(hr);
        m_dwCheckPoint++;

        hr = m_eTrace.Initialize(NONSIGNALED, FALSE);
        RU_LEAVE_IF_NOT_OK(hr);
        m_dwCheckPoint++;

        hr = m_eInterfaceAdded.Initialize(NONSIGNALED, FALSE);
        RU_LEAVE_IF_NOT_OK(hr);
        m_dwCheckPoint++;

        // Cause the registry functions to signal us when change occurs
        //
        if (m_hkConfig)
        {
            hr = RegNotifyChangeKeyValue(
                    m_hkConfig, 
                    FALSE,
                    REG_NOTIFY_CHANGE_LAST_SET,
                    m_eConfig.GetHandle(),
                    TRUE);
            if (hr != ERROR_SUCCESS)
            {
                Trace("Warning: unable to set up config event %x", hr);
                hr = S_OK;
            }
        }
        m_dwCheckPoint++;
        
        if (m_hkTrace)
        {
            hr = RegNotifyChangeKeyValue(
                    m_hkTrace, 
                    FALSE,
                    REG_NOTIFY_CHANGE_LAST_SET,
                    m_eTrace.GetHandle(),
                    TRUE);
            if (hr != ERROR_SUCCESS)
            {
                Trace("Warning: unable to set up trace event %x", hr);
                hr = S_OK;
            }
        }
        m_dwCheckPoint++;

    }

    __finally
    {
    }

    return hr;
}


//+--------------------------------------------------------------------------
//
// Synopsis: Initializes a quarantine server object 
//
//+--------------------------------------------------------------------------
HRESULT 
RqsEngine::Initialize()
{
    HRESULT hr = S_OK;
    
    __try
    {   
        // Register event log handle.  
        //
        m_hLog = RegisterEventSource(NULL, L"Rqs");
        if (m_hLog == NULL)
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            __leave;
        }
    
        // Initialize all of the members of the class
        //
        hr = m_eSocketAccept.Initialize(NONSIGNALED, FALSE);
        RU_LEAVE_IF_NOT_OK(hr);
        m_dwCheckPoint++;

        hr = m_eSocketRead.Initialize(NONSIGNALED, FALSE);
        RU_LEAVE_IF_NOT_OK(hr);
        m_dwCheckPoint++;

        hr = m_rwlConfig.Initialize();
        RU_LEAVE_IF_NOT_OK(hr);
        m_dwCheckPoint++;

        hr = m_Config.Load();
        RU_LEAVE_IF_NOT_OK(hr);
        m_dwCheckPoint++;
        m_fRtTrace = m_Config.GetTraceEnabled();
        m_fDebugTrace = m_Config.GetDebugTrace();

        hr = m_csClientsLock.Initialize();
        RU_LEAVE_IF_NOT_OK(hr);

        // Establish tracing ability if possible
        //
        m_dwTraceId = TraceRegisterExA( "Rqs", 0 );

        // Load the quarantine removal function
        //
        m_hInstMprApi = LoadLibrary(m_Config.GetLibrary());
        if (m_hInstMprApi)
        {
            m_qFunc = (RqsRemoveQuarantineFunc) 
                GetProcAddress(
                    m_hInstMprApi, 
                    "MprAdminConnectionRemoveQuarantine");
        }

        // Get references to the registry keys
        //
        hr = RuRegOpenKey(RqsConfig::GetConfigPath(), FALSE, &m_hkConfig);
        if (S_OK != hr)
        {
            Trace("Warning, unable to listen for configuration changes %x", hr);
        }

        hr = RuRegOpenKey(RqsConfig::GetTracePath(), FALSE, &m_hkTrace);
        if (S_OK != hr)
        {
            Trace("Warning, unable to listen for trace changes %x", hr);
        }

        hr = InitializeEvents();
        RU_LEAVE_IF_NOT_OK(hr);

        hr = ConnectRRAS();
        if (SUCCEEDED(hr))
        {
            //  Init the Server socket to listen for incoming requests.
            //
            hr = InitializeServerSocket();

            if (ERROR_NO_SUCH_INTERFACE == HRESULT_CODE(hr))
            {
                hr = RegisterForConnectionNotification();
                RU_LEAVE_IF_NOT_OK(hr);

                hr = S_OK;
                Trace("Internal interface not found.");
                Trace("Waiting for first connection so that RRAS will create the internal interface.");
            }

            RU_LEAVE_IF_NOT_OK(hr);
            m_dwCheckPoint++;        
        
        }
        else if ((HRESULT_CODE(hr) == RPC_S_UNKNOWN_IF) || (HRESULT_CODE(hr) == RPC_S_SERVER_UNAVAILABLE))
        {
            // RRAS isn't available yet.  Schedule a workitem to wait for RRAS and then init the
            // server socket.
            //
            hr = ScheduleWork(InitializeServerSocketCb);
        }
        RU_LEAVE_IF_NOT_OK(hr);
    } 

    __finally
    {
        if (S_OK != hr)
        {
            Clear();
        }
    }

    TraceSelf();

    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Establishes an RPC connection to the RRAS service. 
//
//+--------------------------------------------------------------------------
HRESULT 
RqsEngine::ConnectRRAS(IN OPTIONAL DWORD dwRetries)
{
    DWORD dwRet;
    BOOL bWrittenWaitingMessage = FALSE;

    if (m_hServer)
    {
        return S_OK;
    }
    
    do
    {
        // Connect to the remote access server 
        //
        dwRet = MprAdminServerConnect(NULL, &m_hServer);

        if (dwRet == ERROR_SUCCESS)
        {
            Trace("Connected to RRAS.");
            break;
        }
        else if (((dwRet == RPC_S_UNKNOWN_IF) || (dwRet == RPC_S_SERVER_UNAVAILABLE)) && (dwRetries > 0))
        {
            //  We weren't able to connect to RRAS because it isn't fully initialized yet, so lets 
            //  sleep for a second and try again
            //
            if (!bWrittenWaitingMessage)
            {
                Trace("Unable to connect to RRAS.  RRAS has not finished initializing yet, waiting...");
                bWrittenWaitingMessage = TRUE;
            }
            Sleep(1000);
            dwRetries--;
        }
        else
        {
            //
            //  Unexpected error.
            //
            m_hServer = NULL;
            break;
        }

    } while(dwRetries > 0);


    return HRESULT_FROM_WIN32(dwRet);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Causes the quarantine engine to execute.
//
//+--------------------------------------------------------------------------
HRESULT 
RqsEngine::Execute()
{
    HRESULT hr = S_FALSE;
    RqsEvent Action;
    BOOL fDone = FALSE;
    
    while (!fDone)
    {
        // Wait for something to happen
        //
        hr = Wait(&Action);
        RU_BREAK_IF_NOT_OK(hr);

        // Do your thing
        //
        switch (Action)
        {
            case Connect:
                hr = ScheduleWork(ClientConnectCb);
                break;

            case Read:
                hr = ScheduleWork(ClientReadCb);
                break;

            case UpdateConfig:
                hr = ReloadConfig();
                break;

            case UpdateTrace:
                hr = ReloadTrace();
                break;

            case ConfigServerSocket:
                DeregisterForConnectionNotification();
                hr = InitializeServerSocket();

                if (SUCCEEDED(hr))
                {
                    TraceSelf();
                }
                else
                {
                    fDone = TRUE;            
                }
                break;

            case Quit:
                fDone = TRUE;
                break;
        }
        
        if (S_OK != hr)
        {
            Trace("Execution error %d 0x%x", Action, hr);
            hr = S_OK;
        }
        
    }

    // Wait for the pending clients to complete
    //
    while (m_ulClientCount)
    {
        Trace("Waiting for %d pending clients...", m_ulClientCount);
        Sleep(0);
    }

    return hr;

}

//+--------------------------------------------------------------------------
//
// Synopsis: Private helper function causes the engine to wait for events 
//           to occur including the "stop working" event.
//
//+--------------------------------------------------------------------------
HRESULT 
RqsEngine::Wait(
    OUT RqsEvent* pAction)
{
    DWORD dwRet;
    HANDLE hEvents[6];
    UINT uiCount = sizeof(hEvents) / sizeof(HANDLE);
    HRESULT hr = S_OK;

    hEvents[0] = m_eQuit.GetHandle();
    hEvents[1] = m_eSocketAccept.GetHandle();
    hEvents[2] = m_eConfig.GetHandle();
    hEvents[3] = m_eTrace.GetHandle();
    hEvents[4] = m_eSocketRead.GetHandle();
    hEvents[5] = m_eInterfaceAdded.GetHandle();

    dwRet = WaitForMultipleObjectsEx(
                uiCount,
                hEvents,
                FALSE,
                INFINITE,
                FALSE);
    switch (dwRet)
    {
        case WAIT_OBJECT_0:
            *pAction = Quit;
            break;

        case WAIT_OBJECT_0 + 1:
            *pAction = Connect;
            break;

        case WAIT_OBJECT_0 + 2:
            *pAction = UpdateConfig;
            break;

        case WAIT_OBJECT_0 + 3:
            *pAction = UpdateTrace;
            break;

        case WAIT_OBJECT_0 + 4:
            *pAction = Read;
            break;

        case WAIT_OBJECT_0 + 5:
            *pAction = ConfigServerSocket;
            break;

        default:
            *pAction = Error;
            hr = HRESULT_FROM_WIN32( GetLastError() );
            break;
    }

    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Schedules a given type of work to occur.
//
//+--------------------------------------------------------------------------
HRESULT 
RqsEngine::ScheduleWork(
    IN LPTHREAD_START_ROUTINE pFunc,
    IN RqsClient* pClient)
{
    HRESULT hr;
    RqsEngineCbInfo* pInfo = NULL;
    
    pInfo = new RqsEngineCbInfo;
    if (NULL == pInfo)
    {
        return E_OUTOFMEMORY;
    }
    
    ZeroMemory(pInfo, sizeof(RqsEngineCbInfo));
    pInfo->pEngine = this;
    pInfo->pClient = pClient;

    if (0 == QueueUserWorkItem(
                    pFunc, 
                    reinterpret_cast<PVOID>(pInfo), 
                    WT_EXECUTEINIOTHREAD))
    {
       hr = HRESULT_FROM_WIN32(GetLastError());
       delete pInfo; // note normally pInfo is deleted by the callback functions    
    }
    else
    {
       hr = S_OK;
    }


    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Adds a client to the list that this engine is servicing
//
//+--------------------------------------------------------------------------
HRESULT
RqsEngine::ClientAdd(
    IN RqsClient* pClient)
{
    HRESULT hr;
    
    m_csClientsLock.Enter();
    hr = m_lClients.InsertBack(pClient);
    m_csClientsLock.Leave();

    if (hr == S_OK)
    {
        Trace("Added client %s", pClient->GetAddressPsz());
        InterlockedIncrement(&m_ulClientCount);
    }

    return hr;
}
//+--------------------------------------------------------------------------
//
// Synopsis: Informs the engine of a client that is leaving
//
//+--------------------------------------------------------------------------
VOID
RqsEngine::ClientRemove()
{
    InterlockedDecrement(&m_ulClientCount);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Processes a client connection
//
//+--------------------------------------------------------------------------
HRESULT
RqsEngine::ClientConnect()
{
    RuSocket* pSocket = NULL;
    RqsClient* pClient = NULL;
    HRESULT hr = S_FALSE;
  
    __try
    {
        // Create a new client socket
        //
        pSocket = new RuSocket();
        if (NULL == pSocket)
        {
            hr = E_OUTOFMEMORY;
            __leave;
        }

        // Create the new client control block
        //
        pClient = new RqsClient();
        if (pClient == NULL)
        {
            hr = E_OUTOFMEMORY;
            __leave;
        }
        
        // Accept the next client socket
        //
        hr = m_sServer.Listen(pSocket);
        RU_LEAVE_IF_NOT_OK(hr);

        // Assign the open client socket to the new client control block
        //
        pClient->SetEngine(this);
        pClient->AssignSocket(pSocket);

        // Add this client to the engine
        //
        hr = ClientAdd(pClient);
        RU_LEAVE_IF_NOT_OK(hr);

        // Cause the read event to signal when data is ready for this client
        //
        hr = pSocket->SetEvent(m_eSocketRead.GetHandle(), FD_READ);
        if (S_OK != hr)
        {
            Trace(
                "Unable to set read event for socket %s, hr = %d", 
                pClient->GetAddressPsz(),
                hr);
            hr = S_OK;                
            __leave;
        }
      
    }

    __finally
    {
        if (hr != S_OK)
        {
            if (pSocket)
            {
                delete pSocket;
            }
            if (pClient)
            {
                delete pClient;
            }
        }
    }

    return hr;            
}

//+--------------------------------------------------------------------------
//
// Synopsis: Reponds to the event that signals that some client has data 
//           ready to be read.
//
//+--------------------------------------------------------------------------
HRESULT
RqsEngine::ClientReadMessages()
{
    HRESULT hr = S_OK;
    ClientList::Iterator Iter;
    RqsClient* pClient;
    RqsClientState cState;

    m_csClientsLock.Enter();

    for (m_lClients.GetIterator(Iter); !Iter.AtEnd(); )
    {
        pClient = Iter.GetItem();
        pClient->ReceiveMessage();
        cState = pClient->GetState();

        if ((cState == ClientError) || (cState == ReceiveComplete))
        {
            Trace(
                "Client receive %s %s (%s)", 
                ((cState == ReceiveComplete) ? "completed successfully for" : "failed for"),
                pClient->GetAddressPsz(),
                pClient->GetUsername());

            // Remove the client from the list
            //            
            Iter.Next();
            hr = m_lClients.RemoveItem(pClient);
            if (hr != S_OK)
            {
                Trace("Unable to remove client from list %x", hr);
                break;
            }

            // If this client is ready to complete, schedule it to happen
            //
            if (cState == ReceiveComplete)
            {    
                // Note the client complete callback will free
                // pClient and call ClientRemove when it is finished.
                //
                hr = ScheduleWork(ClientCompleteCb, pClient);
                if (S_OK != hr)
                {
                    Trace(
                        "Unable to complete client 0x%x, %s (%s)",
                        hr,
                        pClient->GetAddressPsz(),
                        pClient->GetUsername());
                    delete pClient;
                    ClientRemove();
                }
            }
            else // ClientError state
            {
                delete pClient;
                ClientRemove();
            }
                        
            // The iterator has already been incremented at this point
            //
        }
        else
        {
            Iter.Next(); // client isn't done receiving, skip it
        }

    }

    m_csClientsLock.Leave();
        
    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Thread pool callback to process the event that says a client has
//           data ready to read.
//
//+--------------------------------------------------------------------------
DWORD WINAPI
RqsEngine::ClientReadCb(
    IN LPVOID pvContext)
{
    HRESULT hr;

    RqsEngineCbInfo* pInfo = 
        reinterpret_cast<RqsEngineCbInfo*>(pvContext);

    RqsEngine* pEngine = pInfo->pEngine;

    hr = pEngine->ClientReadMessages();

    if (S_OK != hr)
    {
        pEngine->Trace("Error received from ClientReadMessages %x", hr);
    }

    delete pInfo;

    return HRESULT_CODE(hr);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Thread pool callback to process a client connect event
//
//+--------------------------------------------------------------------------
DWORD WINAPI
RqsEngine::ClientConnectCb(IN LPVOID pvContext)
{
    HRESULT hr;

    RqsEngineCbInfo* pInfo = 
        reinterpret_cast<RqsEngineCbInfo*>(pvContext);

    RqsEngine* pEngine = pInfo->pEngine;

    hr = pEngine->ClientConnect();

    if (S_OK != hr)
    {
        pEngine->Trace("Error returned from ClientConnect %x", hr);
    }
    
    delete pInfo;

    return HRESULT_CODE(hr);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Thread pool callback to Connect to RRAS and Init the Server socket
//
//+--------------------------------------------------------------------------
DWORD WINAPI
RqsEngine::InitializeServerSocketCb(IN LPVOID pvContext)
{
    HRESULT hr;

    RqsEngineCbInfo* pInfo = 
        reinterpret_cast<RqsEngineCbInfo*>(pvContext);

    if (NULL == pInfo)
    {
        return ERROR_INVALID_PARAMETER;
    }

    RqsEngine* pEngine = pInfo->pEngine;

    //
    //  Try to connect to RRAS for up to 5 minutes
    //
    hr = pEngine->ConnectRRAS(300);

    if (SUCCEEDED(hr))
    {
        hr = pEngine->InitializeServerSocket();
        if (ERROR_NO_SUCH_INTERFACE == HRESULT_CODE(hr))
        {
            hr = pEngine->RegisterForConnectionNotification();
            pEngine->Trace("Internal interface not found.");
            pEngine->Trace("Waiting for first connection so that RRAS will create the internal interface.");
        }
    }
    
    delete pInfo;

    if (S_OK != hr)
    {
        pEngine->Trace("InitializeServerSocketCb, error 0x%x, exiting.", hr);
        pEngine->Stop();
    }

    return HRESULT_CODE(hr);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Thread pool callback to process a client after it has received
//           its entire message.
//
//+--------------------------------------------------------------------------
DWORD WINAPI
RqsEngine::ClientCompleteCb(
    IN LPVOID pvContext)
{
    HRESULT hr;
    RqsEngineCbInfo* pInfo = 
        reinterpret_cast<RqsEngineCbInfo*>(pvContext);

    if (NULL == pInfo)
    {
        return ERROR_INVALID_PARAMETER;
    }

    RqsEngine* pEngine = pInfo->pEngine;
    RqsClient* pClient = pInfo->pClient;
    BOOL fAccept;

    __try
    {
        // Make sure we're connected to the RRAS service
        //
        hr = pEngine->ConnectRRAS();
        if (S_OK != hr)
        {
            pEngine->Trace(
                "Can't connect to RRAS service 0x%x.  Dropping client %s (%s).", 
                hr,
                pClient->GetAddressPsz(),
                pClient->GetUsername());
            __leave;                
        }
        
        // Figure out whether to accept the client
        //
        fAccept = pEngine->ClientAuthenticate(pClient->GetString());
        
        pEngine->Trace(
            "[%s] %s (%s) %s", 
            (fAccept) ? "Accept" : "Reject",
            pClient->GetAddressPsz(),
            pClient->GetUsername(),
            pClient->GetString()
            );

        // Try to remove the quarantine
        //
        if (fAccept)
        {
            hr = pEngine->ClientClearQuarantine(pClient->GetAddressN(), 
                     pClient->GetAddressPsz(),
                     pClient->GetUsername());

            if (S_OK == hr)
            {
                pEngine->ClientLogInfo(
                    RQS_LOG_SUCCESS, 
                    pClient->GetAddressPsz(),
                    pClient->GetUsername(),
                    pClient->GetString());                
            }
            else if (HRESULT_FROM_WIN32(ERROR_NOT_FOUND) == hr)
            {
                pEngine->ClientLogInfo(
                    RQS_LOG_SUCCESS_BUT_NO_QUARANTINE, 
                    pClient->GetAddressPsz(), 
                    pClient->GetUsername(),
                    pClient->GetString());                
                hr = S_OK;                    
            }
            else 
            {
                pEngine->ClientLogInfo(
                    RQS_LOG_SUCCESS_BUT_PROBLEM_ENCOUNTERED, 
                    pClient->GetAddressPsz(), 
                    pClient->GetUsername(),
                    pClient->GetString());                
                pEngine->Trace("Unable to remove client quarantine. 0x%x", hr);
                fAccept = FALSE;
            }
        }
        else
        {
            pEngine->ClientLogInfo(
                RQS_LOG_REJECT, 
                pClient->GetAddressPsz(), 
                pClient->GetUsername(),
                pClient->GetString());                
        }

        hr = pClient->SendResponse(fAccept);
        RU_LEAVE_IF_NOT_OK(hr);

    }

    __finally
    {
        delete pInfo;
        delete pClient;
        pEngine->ClientRemove();
    }

    return HRESULT_CODE(hr);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Authenticates a client 
//
//+--------------------------------------------------------------------------
BOOL
RqsEngine::ClientAuthenticate(
    IN CHAR* pszString)
{
    HRESULT hr;
    BOOL fOk;

    hr = m_rwlConfig.Lock(READER);
    if (S_OK != hr)
    {
        Trace("Unable to lock configuration object.");
        return FALSE;
    }
    
    fOk = m_Config.Find(pszString);

    hr = m_rwlConfig.Unlock(READER);
    if (hr != S_OK)
    {
        Trace("Unable to unlock configuration object.");
        return FALSE;
    }

    return fOk;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Removes a client's quarantine 
//
//+--------------------------------------------------------------------------
HRESULT
RqsEngine::ClientClearQuarantine(
    IN DWORD dwAddress,
    CONST CHAR* pszAddress,
    CONST CHAR* pszUsername)
{   
    HRESULT hr = S_FALSE;
    
    if (m_qFunc != NULL)
    {
        Trace("Removing Quarantine on IP address %s (%s)", pszAddress, pszUsername);

        //  Here is where we call MprAdminConnectionRemoveQuarantine to
        //  remove the client's quarantine IP Filters or its quarantine
        //  disconnect timer.  Note that we use the client's IP address
        //  to uniquely identify it to the RRAS server.  We also could
        //  have used a handle to the RAS connection.
        //
        DWORD dwError = m_qFunc(m_hServer, UlongToPtr(dwAddress), TRUE);

        if (dwError == ERROR_NOT_FOUND)
        {
            Trace("Quarantine removal failed, user was either never quarantined or was already removed from quarantine.");
        }
        else if (dwError != ERROR_SUCCESS)
        {
            Trace("Quarantine removal failed, error %d.", dwError);
        }

        hr = HRESULT_FROM_WIN32(dwError);
    }
    else
    {
        Trace("Quarantine support not available.");
    }

    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Reloads configuration
//
//+--------------------------------------------------------------------------
HRESULT 
RqsEngine::ReloadTrace()
{
    HRESULT hr, hr2;

    hr = m_rwlConfig.Lock(WRITER);
    if (S_OK != hr)
    {
        Trace("Unable to lock configuration object.");
        return hr;
    }

    __try
    {
        hr = m_Config.LoadTrace();
        if (S_OK != hr)
        {
            Trace("Unable to reload configuration trace.");
        }
        
        hr2 = m_rwlConfig.Unlock(WRITER);
        if (hr2 != S_OK)
        {
            Trace("Unable to unlock configuration object.");
        }
        RU_LEAVE_IF_NOT_OK(hr);

        // Assign the new trace values.  
        //
        m_fRtTrace = m_Config.GetTraceEnabled();
        TraceSelf();
        
        // Re-register the configuration event
        //
        hr = RegNotifyChangeKeyValue(
                m_hkTrace, 
                FALSE,
                REG_NOTIFY_CHANGE_LAST_SET,
                m_eTrace.GetHandle(),
                TRUE);
        if (hr != ERROR_SUCCESS)
        {
            Trace("Warning: unable to re-setup trace event %x", hr);
            hr = S_OK;
        }
        
    }

    __finally
    {
    }

    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Reloads configuration
//
//+--------------------------------------------------------------------------
HRESULT 
RqsEngine::ReloadConfig()
{
    HRESULT hr, hr2;

    hr = m_rwlConfig.Lock(WRITER);
    if (S_OK != hr)
    {
        Trace("Unable to lock configuration object.");
        return hr;
    }

    __try
    {
        m_Config.Clear();
        hr = m_Config.LoadConfig();
        if (S_OK != hr)
        {
            Trace("Unable to reload configuration object.");
        }
        
        hr2 = m_rwlConfig.Unlock(WRITER);
        if (hr2 != S_OK)
        {
            Trace("Unable to unlock configuration object.");
        }
        RU_LEAVE_IF_NOT_OK(hr);

        // Assign the new configuration values.  Note that the accepted
        // value set has been updated at this point.
        //
        m_fDebugTrace = m_Config.GetDebugTrace();
        TraceSelf();
        
        // Re-register the configuration event
        //
        hr = RegNotifyChangeKeyValue(
                m_hkConfig, 
                FALSE,
                REG_NOTIFY_CHANGE_LAST_SET,
                m_eConfig.GetHandle(),
                TRUE);
        if (hr != ERROR_SUCCESS)
        {
            Trace("Warning: unable to re-setup config event %x", hr);
            hr = S_OK;
        }
        
    }

    __finally
    {
    }

    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Common tracing api. 
//
//+--------------------------------------------------------------------------
VOID 
RqsEngine::Trace(
    IN LPSTR pszTrace, 
    IN ...) const
{
    va_list arglist;
    CHAR szTemp[2048];
    HANDLE hFileOut;
    INT iCount;
    DWORD dwTemp;

    szTemp[0] = 0;

    if ((!m_fConsoleTrace) && (!m_fDebugTrace) && (!m_fRtTrace))
    {
        return;
    }

    va_start(arglist, pszTrace);
    iCount = _vsnprintf(szTemp, sizeof(szTemp)/sizeof(szTemp[0]) - 1, pszTrace, arglist);
    va_end(arglist);
    
    szTemp[sizeof(szTemp)/sizeof(szTemp[0]) - 1] = 0; // make sure to NULL terminate as _vsnprintf doesn't guarantee that

    // If we're running in stand-alone mode, output to the console
    //
    if ((m_fConsoleTrace))
    {
        hFileOut = GetStdHandle(STD_OUTPUT_HANDLE);
        WriteFile(hFileOut, szTemp, iCount, &dwTemp, NULL);
        WriteFile(hFileOut, "\n", 2, &dwTemp, NULL);
    }

    // If we're running as a service, then output to the trace logs
    //
    else if (m_fRtTrace)
    {
        if (m_dwTraceId != INVALID_TRACEID)
        {
            TracePrintfA(m_dwTraceId, szTemp);
        }
    } 

    // If the m_fDebugTrace variable has been set in the debugger, then 
    // output to the debugger
    //
    if (m_fDebugTrace)
    {
        OutputDebugStringA(szTemp);
        OutputDebugStringA("\n");
    }

}

//+--------------------------------------------------------------------------
//
// Synopsis: Traces out this engine instance. 
//
//+--------------------------------------------------------------------------
VOID 
RqsEngine::TraceSelf() 
{
    Trace("Engine object:");
    Trace("==============");
    Trace("Client count:   %d", m_ulClientCount);
    Trace("Service:        %x", m_hService);
    Trace("Checkpoint:     %d", m_dwCheckPoint);
    Trace("Mpr handle:     %x", m_hInstMprApi);
    Trace("Mprs handle:    %x", m_hServer);
    Trace("Console trace:  %d", m_fConsoleTrace);
    Trace("Debug Trace:    %d", m_fDebugTrace);
    Trace("RtUtils Trace:  %d", m_fRtTrace);
    Trace("Trace Id:       %d", m_dwTraceId);
    Trace("Trace key:      %x", m_hkTrace);
    Trace("Config key:     %x", m_hkConfig);
    Trace("Internal IP:    %s", (m_szInternalAddress[0] ? m_szInternalAddress : "<Unable to connect to RRAS>"));

    Trace("Configuration object:");
    Trace("=====================");
    m_Config.TraceSelf(*this);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Figures out what type of event log message we are logging.
//
//+--------------------------------------------------------------------------
WORD RqsEngine::GetEventType(DWORD dwEventId)
{
    WORD wEventType;

    DWORD dwSeverity = (dwEventId >> 30) & 0x3;

    switch(dwSeverity)
    {
        case 0:
            wEventType = EVENTLOG_SUCCESS;
            break;
        case 1:
            wEventType = EVENTLOG_INFORMATION_TYPE;
            break;
        case 2:
            wEventType = EVENTLOG_WARNING_TYPE;
            break;
        case 3:
        default:
            wEventType = EVENTLOG_ERROR_TYPE;
            break;
    }

    return wEventType;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Records success or failure to the event log.
//
//+--------------------------------------------------------------------------
VOID 
RqsEngine::ClientLogInfo(
    IN DWORD dwEventId,
    IN CONST CHAR* pszIp,
    IN CONST CHAR* pszUsername, 
    IN CONST CHAR* pszString)
{
    WCHAR *pszAddressW = NULL, *pszStringW = NULL, *pszUsernameW = NULL, *pszArgs[3];
    BOOL fOk;

    pszAddressW = RuStringDupAtoW(const_cast<PSTR>(pszIp));
    pszStringW = RuStringDupAtoW(const_cast<PSTR>(pszString));
    pszUsernameW = RuStringDupAtoW(const_cast<PSTR>(pszUsername));

    pszArgs[0] = (pszAddressW) ? pszAddressW : L"";
    pszArgs[1] = (pszUsernameW) ? pszUsernameW : L"";
    pszArgs[2] = (pszStringW) ? pszStringW : L"";

    fOk = ReportEvent(
                m_hLog,
                GetEventType(dwEventId),
                0,
                dwEventId,
                NULL,
                3,
                0,
                (LPCWSTR *)pszArgs,
                NULL);
    if (! fOk)
    {
        Trace("ReportEvent error %x", GetLastError());
    }

    if (pszStringW)
    {
        RuFree( pszStringW );
    }

    if (pszAddressW)
    {
        RuFree( pszAddressW );
    }

    if (pszUsernameW)
    {
        RuFree( pszUsernameW );
    }

}

//+--------------------------------------------------------------------------
//
// Synopsis: Gets the IP address for the given interface identifier
//
//+--------------------------------------------------------------------------
DWORD 
RqsEngine::GetIpAddressFromInterfaceIndex(
    IN DWORD dwInterfaceId, 
    OUT CHAR* pszIpAddress, 
    IN DWORD dwCount)
{
    if ((NULL == pszIpAddress) || (0 == dwCount))
    {
        return ERROR_INVALID_PARAMETER;
    }

    PMIB_IPADDRTABLE pIpAddrTable = NULL;
    DWORD dwSize = 0;
    DWORD dwRet;

    __try
    {
        // Figure out how much memory we need
        //
        dwRet = GetIpAddrTable (NULL, &dwSize, TRUE);

        if (ERROR_INSUFFICIENT_BUFFER != dwRet)
        {
            __leave;
        }

        pIpAddrTable = (PMIB_IPADDRTABLE)RuAlloc(dwSize, TRUE);

        if (!pIpAddrTable)
        {
            dwRet = ERROR_NOT_ENOUGH_MEMORY;
            __leave;
        }

        // Actually get the IP address table.
        //
        dwRet = GetIpAddrTable (pIpAddrTable, &dwSize, TRUE);

        if (ERROR_SUCCESS != dwRet)
        {
            __leave;
        }

        //  Init the Ip Address string to the empty string
        //
        pszIpAddress[0] = '\0';

        // Find the required index.
        //
        for (DWORD dwLoopIndex = 0; dwLoopIndex < pIpAddrTable->dwNumEntries; dwLoopIndex++)
        {
            if (pIpAddrTable->table[dwLoopIndex].dwIndex == dwInterfaceId)
            {
                //  Print the IP address into the string
                //
                DWORD dwAddr = pIpAddrTable->table[dwLoopIndex].dwAddr;
                _snprintf(pszIpAddress, dwCount, "%d.%d.%d.%d", IP4(dwAddr), IP3(dwAddr), IP2(dwAddr), IP1(dwAddr));

                //
                //  Ensure NULL termination
                //
                pszIpAddress[dwCount - 1] = '\0';

                break;
            }
        }

        // Make sure we found something.
        //
        if (pszIpAddress[0] == '\0')
        {
            dwRet = ERROR_NOT_FOUND;
        }
    }

    __finally
    {
        if (pIpAddrTable)
        {
            RuFree(pIpAddrTable);
        }
    }

    return dwRet;
}


//+--------------------------------------------------------------------------
//
// Synopsis: Gets the IP address for the given interface name
//
//+--------------------------------------------------------------------------
DWORD 
RqsEngine::GetIpAddressFromInterfaceName(
    IN CONST WCHAR* pwszInterfaceName, 
    OUT CHAR* pszIpAddress, 
    IN DWORD dwCount)
{
    if ((NULL == pwszInterfaceName) || (NULL == pszIpAddress) || (0 == dwCount))
    {
        return ERROR_INVALID_PARAMETER;
    }

    //  First we need to call GetIfTable to get the list of interfaces to match
    //  against the one passed in.  Once we have found our interface in the
    //  interface table, then we will have the associated interface index that we
    //  can use with the the IP address table to get the associated IP address for our interface.
    //
    DWORD dwRet;
    DWORD dwSize = 0;
    PMIB_IFTABLE pInterfaceTable = NULL;
    PMIB_IFROW pInterface = NULL;

    __try
    {
        // Figure out how much memory we need.
        //
        dwRet = GetIfTable(NULL, &dwSize, TRUE);
    
        if (ERROR_INSUFFICIENT_BUFFER != dwRet)
        {
            __leave;
        }

        pInterfaceTable = (PMIB_IFTABLE)RuAlloc(dwSize, TRUE);

        if (!pInterfaceTable)
        {
            dwRet = ERROR_NOT_ENOUGH_MEMORY;
            __leave;
        }

        // Actually get the interface table.
        //
        dwRet = GetIfTable(pInterfaceTable, &dwSize, TRUE);

        if (ERROR_SUCCESS != dwRet)
        {
            __leave;
        }

        // Find the interface index.  If we cannot find the requested
        // interface name, return ERROR_NO_SUCH_INTERFACE.  This is a
        // signal to the caller that RRAS may not have created the
        // reqested interface yet.
        //
        dwRet = ERROR_NO_SUCH_INTERFACE;
        for (DWORD dwIndex = 0; dwIndex < pInterfaceTable->dwNumEntries; dwIndex++)
        {
            pInterface = &(pInterfaceTable->table[dwIndex]);
            if (0 == lstrcmpiW(pInterface->wszName, pwszInterfaceName))
            {
                // Use the interface index to get the IP address
                //
                dwRet = GetIpAddressFromInterfaceIndex (pInterface->dwIndex, pszIpAddress, dwCount);
                break;
            }                
        }
    }

    __finally
    {
        if (pInterfaceTable)
        {
            RuFree(pInterfaceTable);
        }
    }

    return dwRet;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Returns the IP Address of the internal interface of RRAS
//
//+--------------------------------------------------------------------------
HRESULT
RqsEngine::GetInternalIpAddress(
    OUT CHAR* pszIpAddress, 
    IN DWORD dwCount)
 {
    // Check inputs
    //
    if ((NULL == pszIpAddress) || (0 == dwCount))
    {
        return E_INVALIDARG;
    }

    DWORD dwRet;
    HANDLE hMprConfig = NULL;
    MPR_INTERFACE_0* pMprInterface = NULL;
    DWORD dwNumEntries = 0;
    DWORD dwTotalEntries = 0;

    //  First call MprConfigServerConnect so we can get a config handle
    //
    __try
    {
        dwRet = MprConfigServerConnect(NULL, &hMprConfig);

        if (NO_ERROR != dwRet)
        {
            __leave;
        }

        //  Get the interfaces that RRAS knows about.
        //
        dwRet = MprConfigInterfaceEnum(hMprConfig, 0, (LPBYTE*)&pMprInterface, -1, &dwNumEntries, &dwTotalEntries, NULL);

        if ((NO_ERROR != dwRet) || (dwNumEntries != dwTotalEntries))
        {
            __leave;
        }

        //  Find the internal interface
        //
        dwRet = ERROR_NOT_FOUND;
        for (DWORD dwIndex = 0; dwIndex < dwNumEntries; dwIndex++)
        {
            if (ROUTER_IF_TYPE_INTERNAL == pMprInterface[dwIndex].dwIfType)
            {
                //  Now all we need to do is find the IP address of the internal interface.
                //
                dwRet = GetIpAddressFromInterfaceName (pMprInterface[dwIndex].wszInterfaceName, pszIpAddress, dwCount);

                if (ERROR_SUCCESS == dwRet)
                {
                    Trace("Internal interface found, %s", pszIpAddress);
                }
                __leave;
            }
        }
    }

    __finally
    {
        if (pMprInterface)
        {
            MprConfigBufferFree(pMprInterface);        
        }

        if (hMprConfig)
        {
            MprConfigServerDisconnect(hMprConfig);        
        }
    }

    return HRESULT_FROM_WIN32(dwRet);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Initializes the socket that RQS uses to listen for requests.
//
//+--------------------------------------------------------------------------
HRESULT 
RqsEngine::InitializeServerSocket()
{
    HRESULT hr;

    // Attempt to connect to the RRAS service.  We need to connect to
    // the RRAS service so we can figure out the correct interface to
    // listen on ... ie. the internal interface.
    //
    __try
    {
        hr = ConnectRRAS();
        RU_LEAVE_IF_NOT_OK(hr);

        hr = GetInternalIpAddress(m_szInternalAddress, sizeof(m_szInternalAddress));
        RU_LEAVE_IF_NOT_OK(hr);

        hr = m_sServer.Create(m_Config.GetPort(), m_szInternalAddress);

        if (HRESULT_CODE(hr) == WSAEADDRINUSE)
        {
            Trace("\n\tUnable to acquire port %d.  Make sure that RQS is not already", m_Config.GetPort());
            Trace("\trunning or that another application is not already using this port.\n");
        }
        else if (SUCCEEDED(hr))
        {
            HANDLE hEvent = m_eSocketAccept.GetHandle();

            if (NULL == hEvent)
            {
                __leave;
            }

            // Signal whenever a new connection arrives
            //
            hr = m_sServer.SetEvent(hEvent);
            RU_LEAVE_IF_NOT_OK(hr);
        }
    }

    __finally
    {
    }


    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Registers for connection notifications from RRAS
//
//+--------------------------------------------------------------------------
HRESULT
RqsEngine::RegisterForConnectionNotification()
{
    DWORD dwRet;

    __try
    {
        HANDLE hEvent = m_eInterfaceAdded.GetHandle();

        if (NULL == hEvent)
        {
            // m_eInterfaceAdded isn't initialized yet.
            //
            dwRet = ERROR_INVALID_HANDLE;
            __leave;
        }

        HRESULT hr = ConnectRRAS();
        if (FAILED(hr))
        {
            dwRet = HRESULT_CODE(hr);
            __leave;
        }

        dwRet = MprAdminRegisterConnectionNotification(m_hServer, hEvent);

        if (ERROR_SUCCESS == dwRet)
        {
            m_bRegisteredForConnectionNotification = TRUE;
        }
    }

    __finally
    {
    }

    return HRESULT_FROM_WIN32(dwRet);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Deregisters for connection notifications from RRAS
//
//+--------------------------------------------------------------------------
HRESULT
RqsEngine::DeregisterForConnectionNotification()
{
    DWORD dwRet;

    __try
    {
        HANDLE hEvent = m_eInterfaceAdded.GetHandle();

        if (NULL == hEvent)
        {
            // m_eInterfaceAdded isn't initialized yet.
            //
            dwRet = ERROR_INVALID_HANDLE;
            __leave;
        }

        HRESULT hr = ConnectRRAS();
        if (FAILED(hr))
        {
            dwRet = HRESULT_CODE(hr);
            __leave;
        }

        dwRet = MprAdminDeregisterConnectionNotification(m_hServer, hEvent);

        if (ERROR_SUCCESS == dwRet)
        {
            m_bRegisteredForConnectionNotification = FALSE;
        }
    }

    __finally
    {
    }

    return HRESULT_FROM_WIN32(dwRet);
}

