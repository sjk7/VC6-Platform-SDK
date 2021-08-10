//+--------------------------------------------------------------------------
//
//      File:       RqsEngine.h
//
//      Synopsis:   Engine that drives the server-side ras quarantine removal
//                  utility.
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#pragma once

class ClientList;
class RqsClient;

typedef 
DWORD 
(APIENTRY *RqsRemoveQuarantineFunc)(HANDLE, HANDLE, BOOL);

//+--------------------------------------------------------------------------
//
// Synopsis: Types of events that occur to the Engine
//
//+--------------------------------------------------------------------------
enum RqsEvent
{
    Connect,
    Read,
    UpdateConfig,
    UpdateTrace,
    Quit,
    ConfigServerSocket,
    Error
};

//+--------------------------------------------------------------------------
//
// Synopsis: The engine that drives the whole system
//
//+--------------------------------------------------------------------------
class RqsEngine
{
public:
    // Construction/destruction
    //
    RqsEngine();
    ~RqsEngine();
    HRESULT Initialize();

    // Execution
    //
    HRESULT Execute();
    VOID Stop() {m_eQuit.Set();}

    // Client control
    //
    HRESULT ClientAdd(IN RqsClient* pClient); 
    VOID ClientRemove(); 
    HRESULT ClientReadMessages();
    BOOL ClientAuthenticate(IN CHAR* pszString);
    HRESULT ClientClearQuarantine(IN DWORD dwAddress, IN CONST CHAR* pszAddress, IN CONST CHAR* pszUsername);
    VOID ClientLogInfo(IN DWORD dwEvent, IN CONST CHAR* pszIp, IN CONST CHAR* pszUsername, IN CONST CHAR* pszString);

    // Service management 
    //
    VOID SetServiceHandle(SERVICE_STATUS_HANDLE hService) {m_hService = hService;}
    SERVICE_STATUS_HANDLE GetServiceHandle() {return m_hService;}
    DWORD GetCheckpoint() {return m_dwCheckPoint;}
    HRESULT ConnectRRAS(IN OPTIONAL DWORD dwRetries = 0);

    // Tracing
    //
    VOID Trace(IN LPSTR pszTrace, IN ...) const;
    VOID TraceSelf();
    VOID SetConsoleTracing(IN BOOL fConsole) {m_fConsoleTrace = fConsole;};
    
private:
    RqsConfig m_Config;
    RuServerSocket m_sServer;
    RcuEvent m_eSocketAccept;
    RcuEvent m_eSocketRead;
    RcuEvent m_eQuit;
    RcuEvent m_eConfig;
    RcuEvent m_eTrace;
    RcuEvent m_eInterfaceAdded;
    RcuRwLock m_rwlConfig;
    volatile LONG m_ulClientCount;
    SERVICE_STATUS_HANDLE m_hService;
    DWORD m_dwCheckPoint;
    HINSTANCE m_hInstMprApi;
    HANDLE m_hServer;
    RqsRemoveQuarantineFunc m_qFunc;
    BOOL m_fRtTrace;
    DWORD m_dwTraceId;
    BOOL m_fConsoleTrace;
    BOOL m_fDebugTrace;
    HKEY m_hkTrace;
    HKEY m_hkConfig;
    HANDLE m_hLog;
    RcuCritSec m_csClientsLock;
    ClientList m_lClients;
    BOOL m_bRegisteredForConnectionNotification;
    CHAR m_szInternalAddress [16];

    HRESULT InitializeEvents();
    
    VOID Clear();
    HRESULT Wait(OUT RqsEvent* pAction);
    HRESULT ScheduleWork(LPTHREAD_START_ROUTINE pFunc, RqsClient* pClient = NULL);
    HRESULT ClientConnect();
    static DWORD WINAPI ClientConnectCb(IN LPVOID pvContext);
    static DWORD WINAPI ClientReadCb(IN LPVOID pvContext);
    static DWORD WINAPI ClientCompleteCb(IN LPVOID pvContext);
    static DWORD WINAPI InitializeServerSocketCb(IN LPVOID pvContext);

    HRESULT ReloadConfig();
    HRESULT ReloadTrace();
    void TraceCurrentServerConnections();
    WORD GetEventType(DWORD dwEventId);
    HRESULT GetInternalIpAddress(OUT CHAR* pszIpAddress, IN DWORD dwCount);
    DWORD GetIpAddressFromInterfaceName(IN CONST WCHAR* pwszInterfaceName, OUT CHAR* pszIpAddress, IN DWORD dwCount);
    DWORD GetIpAddressFromInterfaceIndex(IN DWORD dwInterfaceId, OUT CHAR* pszIpAddress, IN DWORD dwCount);
    HRESULT InitializeServerSocket();
    HRESULT RegisterForConnectionNotification();
    HRESULT DeregisterForConnectionNotification();
};
