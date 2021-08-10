//****************************************************************************
//  Module:     PLUGTRANSPORT.EXE     
//  File:       NULLMDM.H
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1995-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************



#ifndef _NULL_MODEM_H_
#define _NULL_MODEM_H_

#define COMPORTNAMEMAXLENGTH   64


typedef enum tagTPhysicalError
{
    TPHYS_SUCCESS                       =   0,
    TPHYS_RESULT_INUSE                  = 100,
    TPHYS_RESULT_FAIL                   = 101,
    TPHYS_RESULT_NOT_INITIALIZED        = 102,
    TPHYS_RESULT_CONNECT_FAILED         = 103,
    TPHYS_CONNECT_RESPONSE_FAILED       = 104,
    TPHYS_RESULT_NOT_LISTENING          = 105,
    TPHYS_RESULT_INVALID_CONNECTION     = 106,
    TPHYS_RESULT_INVALID_ADDRESS        = 107,
    TPHYS_RESULT_CONNECT_REJECTED       = 108,
    TPHYS_RESULT_SUCCESS_ALTERNATE      = 109,
    TPHYS_RESULT_COMM_PORT_BUSY         = 110,
    TPHYS_RESULT_WAITING_FOR_CONNECTION = 111,
}
    TPhysicalError;


typedef struct tphys_connect_info
{
    UINT       connectionID;
    UINT       resultCode;
}
    TPHYS_CONNECT_INFO, * PTPHYS_CONNECT_INFO;

typedef UINT        PHYSICAL_HANDLE;


///////////////////////////////////////////////////////////////////////////////
// Structure containing state information for each NULLMODEM line
///////////////////////////////////////////////////////////////////////////////
typedef enum tagCALL_STATE
{
    CALL_STATE_IDLE         = 0,    // Call is idle
    CALL_STATE_MAKE         = 1,    // Establishing phone connection
    CALL_STATE_ANSWER       = 2,    // Answering a new call
    CALL_STATE_DROP         = 3,    // Dropping the phone connection
    CALL_STATE_CONNECTED    = 4,    // Phone connection established and passed onto TDD.
}
    CALL_STATE;

typedef struct tagLINE_INFO
{
    HANDLE              hevtCall;       // handle to the call
    HANDLE              hCommLink;      // handle to COM device - call
    BOOL                fCaller;        // FALSE = incoming call
    CALL_STATE          eCallState;     // one of the following states
    PHYSICAL_HANDLE     pstnHandle;
    TPHYS_CONNECT_INFO  connInfo;
}
    LINE_INFO;


class CNullModem
{
public:

    CNullModem(void);
    ~CNullModem(void);

    TPhysicalError TPhysInitialize(UINT transport_id);
    TPhysicalError TPhysTerminate(void);
    TPhysicalError TPhysConnectRequest(LPTSTR pszComPort);
    TPhysicalError TPhysDisconnect(void);

    HANDLE GetCommLink(void) { return m_Line.hCommLink; }

private:

    DWORD DoConnect(void);

    void SetBuffers(void);
    void SetTimeouts(void);

    void DropCall(void);
    BOOL WaitForConnection(void);
    void SetConnectedPort(void);
    void SetComPortState(void);

private:

    BOOL            m_fInitialized;
    UINT            m_nTransportID;          // ID required by RNC
    UINT            m_nConnectionID;         // next conn ID to allocate   
    LINE_INFO       m_Line;

    HANDLE          m_hevtOverlapped;
    DWORD           m_dwEventMask;
    BOOL            m_fCommPortInUse;
    OVERLAPPED      m_Overlapped;

    COMMTIMEOUTS    m_DefaultTimeouts;
};

class CPSTN
{
public:
 CPSTN(void);
 ~CPSTN(void);
 HRESULT CreateComPort(UINT nTransportID, LPTSTR pszComPort);
 HRESULT CloseComPort();
 HANDLE GetCommLink(void);

private:
 CNullModem* 	m_pNullModem;
 TCHAR			m_szComPortName[COMPORTNAMEMAXLENGTH];
};


#define COMM_PORT_TIMEOUT       60000    //  60 seconds
#define COMM_PORT_BAUD_RATE     19200    // or 57600 or others
#define COMM_PORT_STOP_BITS     ONESTOPBIT
#define COMM_PORT_DATA_BITS     8

#endif // _NULL_MODEM_H_

