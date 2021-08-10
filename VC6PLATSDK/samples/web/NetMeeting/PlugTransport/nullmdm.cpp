//****************************************************************************
//  Module:     PLUGTRANSPORT.EXE     
//  File:       NULLMDM.CPP
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


#include "precomp.h"


//*******************
//GLOBALS
//*******************

BYTE    g_szNULLMStartString[] = "NULLMDM";
ULONG   g_nConnID = 0;


//**********************************
//
// CLASS CPSTN
//
//**********************************

//****************************************************************************
//
//    FUNCTION:   CPSTN::CPSTN()
//
//    PURPOSE:    Construction

//    COMMENTS:
//      
//
//****************************************************************************

CPSTN::CPSTN()
{
   m_pNullModem = NULL;
   m_szComPortName[0] = '\0';
}


//****************************************************************************
//
//    FUNCTION:   CPSTN::~CPSTN()
//
//    PURPOSE:    Destruction

//    COMMENTS:
//      
//
//****************************************************************************

CPSTN::~CPSTN()
{}


//****************************************************************************
//
//    FUNCTION:   HRESULT CPSTN::CreateComPort(UINT nTransportID, LPSTR pszComPort)
//
//    PURPOSE:    Prepares the COM port specified by pszComPort to use it

//    COMMENTS:
//
//
//****************************************************************************

HRESULT CPSTN::CreateComPort(UINT nTransportID, LPTSTR pszComPort)
{
    TPhysicalError rc;
  
    m_pNullModem = new CNullModem();
    if (NULL == m_pNullModem)
    {
        return E_OUTOFMEMORY;
    }

    lstrcpyn(m_szComPortName, pszComPort, COMPORTNAMEMAXLENGTH);

    rc = m_pNullModem->TPhysInitialize(nTransportID);
    if (TPHYS_SUCCESS != rc)
    {
        return E_FAIL;
    }

    rc = m_pNullModem->TPhysConnectRequest(m_szComPortName);
    if (TPHYS_SUCCESS != rc)
    {
        return E_FAIL;
    }

    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT CPSTN::CloseComPort()
//
//    PURPOSE:    Closes an open COM port

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT CPSTN::CloseComPort()
{
    if (NULL != m_pNullModem)
    {
        TPhysicalError rc;
        HRESULT hr = S_OK;

        rc = m_pNullModem->TPhysDisconnect();
        if (TPHYS_SUCCESS != rc)
            hr = E_FAIL;

        rc = m_pNullModem->TPhysTerminate();
        if (TPHYS_SUCCESS != rc)
            hr = E_FAIL;

        delete m_pNullModem;
        m_pNullModem = NULL;

        return hr;
    }
    // Port already closed or never opened
    return S_FALSE;
}


//****************************************************************************
//
//    FUNCTION:   HANDLE CPSTN::GetCommLink()
//
//    PURPOSE:    Get the handle to the COM link

//    COMMENTS:
//      
//
//****************************************************************************

HANDLE CPSTN::GetCommLink()
{ 
    if (m_pNullModem)
        return m_pNullModem->GetCommLink();
    
    return NULL;
}


//**********************************
//
// CLASS CNullMdm
//
//**********************************

//****************************************************************************
//
//    FUNCTION:   CNullModem::CNullModem(void)
//
//    PURPOSE:    Construction

//    COMMENTS:
//       
//
//****************************************************************************

CNullModem::CNullModem(void)
:
    m_fInitialized(FALSE),
    m_nTransportID(0),
    m_nConnectionID(0),
    m_hevtOverlapped(NULL),
    m_dwEventMask(0),
    m_fCommPortInUse(FALSE)
{
    ::ZeroMemory(&m_Line, sizeof(m_Line));
    ::ZeroMemory(&m_Overlapped, sizeof(m_Overlapped));
    ::ZeroMemory(&m_DefaultTimeouts, sizeof(m_DefaultTimeouts));

    m_hevtOverlapped = ::CreateEvent(NULL, TRUE, FALSE, NULL); // manual reset
    ASSERT(NULL != m_hevtOverlapped);
    
}


//****************************************************************************
//
//    FUNCTION:   CNullModem::~CNullModem(void)
//
//    PURPOSE:    Destruction

//    COMMENTS:
//      
//
//****************************************************************************

CNullModem::~CNullModem(void)
{
    if (m_fInitialized)
    {
        TPhysTerminate();
    }

    if (NULL != m_hevtOverlapped)
    {
        ::CloseHandle(m_hevtOverlapped);
    }
}


//****************************************************************************
//
//    FUNCTION:   TPhysicalError CNullModem::TPhysInitialize(UINT nTransportID)
//
//    PURPOSE:    Initialize the object

//    COMMENTS:
//      
//
//****************************************************************************

TPhysicalError CNullModem::TPhysInitialize(UINT nTransportID)
{
    TPhysicalError rc = TPHYS_SUCCESS;

    //
    // If we have already been initialized then this is a reinit call from
    // the node controller so just do nothing.
    //
    if (! m_fInitialized)
    {
        //
        // zero out the SESSION INFO structure
        //
        ::ZeroMemory(&m_Line, sizeof(m_Line));

        //
        // Store control information
        //
        m_nTransportID  = nTransportID;
        m_fInitialized  = TRUE;
        m_nConnectionID = ++g_nConnID;

        ASSERT(TPHYS_SUCCESS == rc);
    }
   
    return rc;
}


//****************************************************************************
//
//    FUNCTION:   TPhysicalError CNullModem::TPhysTerminate(void)
//
//    PURPOSE: 

//    COMMENTS:
//       
//
//****************************************************************************

TPhysicalError CNullModem::TPhysTerminate(void)
{
    if (! m_fInitialized)
    {
        return(TPHYS_RESULT_NOT_INITIALIZED);
    }

    m_nTransportID = 0;
    m_fInitialized = FALSE;
    
    return(TPHYS_SUCCESS);
}


//****************************************************************************
//
//    FUNCTION:   TPhysicalError CNullModem::TPhysConnectRequest(LPTSTR pszComPort)
//
//    PURPOSE:    It checks the port, opens it ans initliazes it

//    COMMENTS:
//       
//
//****************************************************************************

TPhysicalError CNullModem::TPhysConnectRequest(LPTSTR pszComPort)
{
    TPhysicalError  rc          = TPHYS_SUCCESS;
    HANDLE          hCommLink   = INVALID_HANDLE_VALUE;
    DCB             dcb;
    DWORD           dwWritten   = 0;

    if (! m_fInitialized)
    {
        // NULL MODEM OOB not initialized
        return TPHYS_RESULT_NOT_INITIALIZED;
    }

    // Select a comm port for the call.
    if (CALL_STATE_IDLE == m_Line.eCallState || CALL_STATE_DROP == m_Line.eCallState)
    {
        // Also prime our local copy of the conninfo structure for use in callbacks
        m_Line.connInfo.resultCode   = 0;
        m_Line.connInfo.connectionID = m_nConnectionID;
    }
    else
    {
        // No comm port is available
        return TPHYS_RESULT_COMM_PORT_BUSY;
    }

    // Only alow one at at time
    if (m_fCommPortInUse)
    {
        // Waiting for a previous null mode connection
        rc = TPHYS_RESULT_WAITING_FOR_CONNECTION;
        goto bail;
    }
    m_fCommPortInUse = true;

    // Check the name of the comm port. Comm port names MUST start with 'com'.
    if (_tcsnicmp(TEXT("com"), pszComPort, 3) != 0)
    {
        rc = TPHYS_RESULT_INVALID_ADDRESS;
        goto bail;
    }
    
    // Open the comm port
    hCommLink = ::CreateFile(pszComPort,
                             GENERIC_READ | GENERIC_WRITE,
                             0,                    // exclusive access
                             NULL,                 // no security attrs
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // overlapped I/O
                             NULL );
    if (hCommLink == INVALID_HANDLE_VALUE)
    {
        // TPhysConnectRequest: CreateFile failed
        rc = TPHYS_RESULT_COMM_PORT_BUSY;
        goto bail;
    }

    m_Line.hCommLink = hCommLink;

    // remember the default timeouts
    ::GetCommTimeouts(hCommLink, &m_DefaultTimeouts);

    // Let the other side know that we are trying to connect
    if (! ::EscapeCommFunction(hCommLink, SETDTR))
    {
        // TPhysConnectRequest: Unable to Set DTR
    }

    ::ZeroMemory(&m_Overlapped, sizeof(m_Overlapped));
    m_Overlapped.hEvent = m_hevtOverlapped;
    m_dwEventMask = 0;

    ::ResetEvent(m_hevtOverlapped);

    if (! ::WriteFile(hCommLink, g_szNULLMStartString, sizeof(g_szNULLMStartString), &dwWritten, &m_Overlapped))
    {
        DWORD dwErr = ::GetLastError();
        if (ERROR_IO_PENDING != dwErr)
        {
            // TPhysConnectRequest: WriteFile failed
            ::ResetEvent(m_hevtOverlapped);
            rc = TPHYS_RESULT_COMM_PORT_BUSY;
            goto bail;
        }
        else
        {
            DWORD dwWait = ::WaitForSingleObject(m_hevtOverlapped, INFINITE);
            BOOL fRet = ::GetOverlappedResult(hCommLink, &m_Overlapped, &dwWritten, TRUE);
            ASSERT(fRet);
            ASSERT(dwWritten == sizeof(g_szNULLMStartString));
        }
    }
    else
    {
        ASSERT(dwWritten == sizeof(g_szNULLMStartString));
    }

    ::ResetEvent(m_hevtOverlapped);

    // Get the default dcb
    ::ZeroMemory(&dcb, sizeof(dcb));
    dcb.DCBlength = sizeof(DCB);

    ::GetCommState(hCommLink, &dcb);

    // Set our state so we can get notification in the comm port
    dcb.BaudRate = COMM_PORT_BAUD_RATE;
    dcb.StopBits = COMM_PORT_STOP_BITS;
    dcb.ByteSize = COMM_PORT_DATA_BITS;
    dcb.fBinary = 1;                        // binary mode, no EOF check 
    dcb.fParity = 0;                        // enable parity checking 
    dcb.fOutxCtsFlow = 1;                   // CTS output flow control 
    dcb.fOutxDsrFlow = 0;                   // DSR output flow control 
    dcb.fDtrControl = DTR_CONTROL_ENABLE;   // DTR flow control type 
    dcb.fDsrSensitivity = 0;                // DSR sensitivity 
    dcb.fTXContinueOnXoff = 0;              // XOFF continues Tx 
    dcb.fOutX = 0;                          // XON/XOFF out flow control 
    dcb.fInX = 0;                           // XON/XOFF in flow control 
    dcb.fErrorChar = 0;                     // enable error replacement 
    dcb.fNull = 0;                          // enable null stripping 
    dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;// RTS flow control 
    dcb.XonLim = 0;                         // transmit XON threshold 
    dcb.XoffLim = 0;                        // transmit XOFF threshold 
    dcb.fErrorChar = 0;                     // enable error replacement 
    dcb.fNull = 0;                          // enable null stripping 
    dcb.fAbortOnError = 0;                  // abort reads/writes on error 
    dcb.Parity = 0;    

    ::SetCommState(hCommLink, &dcb);

    ::PurgeComm(hCommLink, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

    m_Line.eCallState = CALL_STATE_MAKE;
    m_Line.hevtCall = m_hevtOverlapped;
    m_Line.pstnHandle = (PHYSICAL_HANDLE) hCommLink;
    m_Line.fCaller = TRUE;

    if (! ::SetCommMask(hCommLink,
                EV_RXCHAR |         // Any Character received
                EV_CTS |            // CTS changed state
                EV_DSR |            // DSR changed state
                EV_RLSD|            // RLSD changed state
                EV_RXFLAG))         // Certain character
    {
        // TPhysConnectRequest:  Unable to SetCommMask
    }

    ::ZeroMemory(&m_Overlapped, sizeof(m_Overlapped));
    m_Overlapped.hEvent = m_hevtOverlapped;
    m_dwEventMask = 0;

    ::ResetEvent(m_hevtOverlapped);

    if (! ::WaitCommEvent(hCommLink, &m_dwEventMask, &m_Overlapped))
    {
        DWORD dwErr = ::GetLastError();
        if (ERROR_IO_PENDING != dwErr)
        {
            // TPhysConnectRequest: WaitCommEvent failed
            m_fCommPortInUse = FALSE;
        }
    }

    DoConnect();

bail:

    return(rc);
}


//****************************************************************************
//
//    FUNCTION:   TPhysicalError CNullModem::TPhysDisconnect(void)
//
//    PURPOSE:    Closes the com port. Wrapper around DropCall that does the work

//    COMMENTS:
//      
//
//****************************************************************************

TPhysicalError CNullModem::TPhysDisconnect(void)
{
    if (! m_fInitialized)
    {
        // Not initialized
        return(TPHYS_RESULT_NOT_INITIALIZED);
    }

    // close the com port
    DropCall();

    return(TPHYS_SUCCESS);
}


//****************************************************************************
//
//    FUNCTION:   void CNullModem::DropCall(void)
//
//    PURPOSE:    Closes the com port

//    COMMENTS:
//       
//
//****************************************************************************

void CNullModem::DropCall(void)
{
    // close the device handle                                              
    if (NULL != m_Line.hCommLink)
    {
        CALL_STATE eCallState = m_Line.eCallState;
        m_Line.eCallState = CALL_STATE_IDLE;

        // If this call is connected it is not using the comm thread
        if (eCallState != CALL_STATE_CONNECTED)
        {
            m_fCommPortInUse = FALSE;
        }

        // restore comm timeouts
        SetCommTimeouts(m_Line.hCommLink, &m_DefaultTimeouts);

        ::CloseHandle(m_Line.hCommLink);
        m_Line.hCommLink = NULL;
    }
}


//****************************************************************************
//
//    FUNCTION:   void CNullModem::SetConnectedPort(void)
//
//    PURPOSE:    Configures the communication device according to the 
//                specifications in the device-control block (DCB structure)

//    COMMENTS:
//       
//
//****************************************************************************

void CNullModem::SetConnectedPort(void)
{
    DCB     dcb;

    ::ZeroMemory(&dcb, sizeof(dcb));
    dcb.DCBlength = sizeof(DCB);

    //  Set comm mask and state
    ::SetCommMask(m_Line.hCommLink, 0);    // RLSD changed state

    ::GetCommState(m_Line.hCommLink, &dcb);
    dcb.BaudRate = COMM_PORT_BAUD_RATE;
    dcb.StopBits = COMM_PORT_STOP_BITS;
    dcb.ByteSize = COMM_PORT_DATA_BITS;
    dcb.fBinary = 1;           // binary mode, no EOF check 
    dcb.fParity = 0;           // enable parity checking 
    dcb.fOutxDsrFlow = 0;      // DSR output flow control 
    dcb.fDsrSensitivity = 0;   // DSR sensitivity 
    dcb.fTXContinueOnXoff = 0; // XOFF continues Tx 
    dcb.fOutX = 0;             // XON/XOFF out flow control 
    dcb.fInX = 0;              // XON/XOFF in flow control 
    dcb.fErrorChar = 0;        // enable error replacement 
    dcb.fNull = 0;             // enable null stripping 
    dcb.XonLim = 0;            // transmit XON threshold 
    dcb.XoffLim = 0;           // transmit XOFF threshold 
    dcb.Parity = 0;

    ::SetCommState(m_Line.hCommLink, &dcb);
}


//****************************************************************************
//
//    FUNCTION:   BOOL CNullModem::WaitForConnection(void)
//
//    PURPOSE:    Wait for connection and handle the notification

//    COMMENTS:
//      
//
//****************************************************************************

BOOL CNullModem::WaitForConnection(void)
{
    BOOL fRet = FALSE;

    while (true)
    {
        DWORD dwWait = ::WaitForSingleObject(m_hevtOverlapped, COMM_PORT_TIMEOUT);

        ::ResetEvent(m_hevtOverlapped);

        if (dwWait == WAIT_ABANDONED || dwWait == WAIT_TIMEOUT || dwWait == WAIT_FAILED)
        {
            DropCall();
            m_fCommPortInUse = FALSE;
            // WaitForConnection: Unable to WaitCommEvent
            goto Failure;
        }

        ASSERT(m_hevtOverlapped == m_Line.hevtCall);
        if (CALL_STATE_MAKE != m_Line.eCallState && CALL_STATE_ANSWER != m_Line.eCallState)
        {
            // WaitForConnection: Got a bad event
            goto Failure;
        }

        switch (m_Line.eCallState)
        {
        case CALL_STATE_MAKE:
            {
                // The other side was connected and cleared DTR
                if (m_dwEventMask & (EV_RXCHAR))
                {
                    ::EscapeCommFunction(m_Line.hCommLink, CLRDTR);
                    ::EscapeCommFunction(m_Line.hCommLink, SETDTR);
                    SetConnectedPort();
                    m_Line.fCaller = FALSE;
                    goto Success;
                }

                // The other side just connected
                else
                if(m_dwEventMask & (EV_DSR | EV_RLSD | EV_CTS))
                {
                    // Change the state of this connection so we dont get here again
                    m_Line.eCallState = CALL_STATE_ANSWER;

                    // Wait sometime so the other side can transition to the wait state
                    ::Sleep(2000);
                    
                    // Tell the other side we connected before
                    ::EscapeCommFunction(m_Line.hCommLink, SETBREAK);

                    ::ZeroMemory(&m_Overlapped, sizeof(m_Overlapped));
                    m_Overlapped.hEvent = m_Line.hevtCall;
                    m_dwEventMask = 0;

                    ::ResetEvent(m_Overlapped.hEvent);

                    if (! ::WaitCommEvent(m_Line.hCommLink, &m_dwEventMask, &m_Overlapped))
                    {
                        DWORD dwErr = ::GetLastError();
                        if (ERROR_IO_PENDING != dwErr)
                        {
                            // TPhysConnectRequest:  Unable to WaitCommEvent
                            DropCall();
                            goto Failure;
                        }
                    }
                }
            }
            break;
            
        case CALL_STATE_ANSWER:
            {
                ::EscapeCommFunction(m_Line.hCommLink, CLRBREAK);
                SetConnectedPort();
                goto Success;
            }
            break;
        }
    } // while

Success:

    fRet = TRUE;

Failure:

    return fRet;
}


//****************************************************************************
//
//    FUNCTION:   DWORD CNullModem::DoConnect(void)
//
//    PURPOSE: 

//    COMMENTS:       
//
//****************************************************************************

DWORD CNullModem::DoConnect(void)
{
    ULONG    rc = 0;

    while (m_fCommPortInUse)
    {
        // Wait for connection to happen
        if (WaitForConnection())
        {
            SetBuffers();
            SetTimeouts();

            // Call T120 physicall request
            if (m_Line.fCaller)
            {
                // rc = g_lpfnPTPhysicalConnectRequest(0, // CALL_CONTROL_MANUAL
                //                        &m_Line.hCommLink, NULL, &m_Line.pstnHandle);
            }
            else
            {
                m_Line.connInfo.connectionID = m_nConnectionID;
                m_Line.connInfo.resultCode = TPHYS_SUCCESS;
            }
            
            if (rc != 0)
            {
                m_Line.connInfo.resultCode = TPHYS_RESULT_CONNECT_FAILED;

                DropCall();
            }
            else
            {
                m_Line.eCallState = CALL_STATE_CONNECTED;
                m_Line.connInfo.resultCode = TPHYS_SUCCESS;

                // This comm port doesn't need the thread anymore
                m_fCommPortInUse = FALSE;
            }
        }
        else
        {
            m_Line.connInfo.resultCode = TPHYS_RESULT_CONNECT_FAILED;

            // Something went wrong in the wait, get out of the loop
            break;
        }
    }        

    return 0;
}


//****************************************************************************
//
//    FUNCTION:   void CNullModem::SetBuffers(void)
//
//    PURPOSE:    Initializes the communication parameters 

//    COMMENTS:       
//        
//
//****************************************************************************

void CNullModem::SetBuffers(void)
{
    BOOL fRet = ::SetupComm(m_Line.hCommLink, /* rx */ 10240, /* tx */ 1024);
    ASSERT(fRet);
}


//****************************************************************************
//
//    FUNCTION:   void CNullModem::SetTimeouts(void)
//
//    PURPOSE:    Sets the time-out parameters for all read and write operations 
//                on the specified communications device

//    COMMENTS:
//       
//
//****************************************************************************

void CNullModem::SetTimeouts(void)
{
    COMMTIMEOUTS    com_timeouts;
    ::ZeroMemory(&com_timeouts, sizeof(com_timeouts));
    com_timeouts.ReadIntervalTimeout = 100;   //10
    com_timeouts.ReadTotalTimeoutMultiplier = 0;
    com_timeouts.ReadTotalTimeoutConstant = 100;
    com_timeouts.WriteTotalTimeoutMultiplier = 0;
    com_timeouts.WriteTotalTimeoutConstant = 10000;
    BOOL fRet = ::SetCommTimeouts(m_Line.hCommLink, &com_timeouts);
    ASSERT(fRet);

}


