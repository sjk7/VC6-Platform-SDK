//+--------------------------------------------------------------------------
//
//      File:       RcuSync.cpp
//
//      Synopsis:   Sychronization objects.
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#include "rasutil.h"

//+----------------------------------------------------------------------------
//
// Synopsis: Critical Section constructor
//
//-----------------------------------------------------------------------------
RcuCritSec::RcuCritSec() : m_fInitialized(FALSE)
{
}

//+----------------------------------------------------------------------------
//
// Synopsis: Critical Section destructor
//
//-----------------------------------------------------------------------------
RcuCritSec::~RcuCritSec()
{
    if (m_fInitialized)
    {
        DeleteCriticalSection(&m_CritSec);
    }
}

//+----------------------------------------------------------------------------
//
// Synopsis: Initializes a critical section
//
//-----------------------------------------------------------------------------
HRESULT
RcuCritSec::Initialize()
{
    HRESULT hr = S_OK;
    
    m_fInitialized = TRUE;

    // Critical section initialization must take place within an SEH __try 
    // block since it can throw the STATUS_NO_MEMORY exception.
    //
    __try 
    {
        InitializeCriticalSection(&m_CritSec);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) 
    {
        hr = HRESULT_FROM_WIN32(GetExceptionCode());
        m_fInitialized = FALSE;
    }

    return hr;
}

//+----------------------------------------------------------------------------
//
// Synopsis: Enter a critical section.  
//
//-----------------------------------------------------------------------------
HRESULT
RcuCritSec::Enter()
{
    if (! m_fInitialized)
    {
        return E_FAIL;
    }
    
    EnterCriticalSection(&m_CritSec);
    return S_OK;
}

//+----------------------------------------------------------------------------
//
// Synopsis: Leave a critical section.  
//
//-----------------------------------------------------------------------------
VOID
RcuCritSec::Leave()
{
    LeaveCriticalSection(&m_CritSec);
}


//+----------------------------------------------------------------------------
//
// Synopsis: Create an event.  
//
//-----------------------------------------------------------------------------
RcuEvent::RcuEvent() : m_hEvent(NULL)
{
}

//+----------------------------------------------------------------------------
//
// Synopsis: Destroy an event.  
//
//-----------------------------------------------------------------------------
RcuEvent::~RcuEvent()
{
    if (m_hEvent)
    {
        CloseHandle(m_hEvent);
    }
}

//+----------------------------------------------------------------------------
//
// Synopsis: Initialize an event.  
//
//-----------------------------------------------------------------------------
HRESULT
RcuEvent::Initialize(
    IN RcuEventState esInitialState,
    IN BOOL fManualReset,
    IN BOOL fInherit,
    IN RcuSecurityDescriptor* pSD)
{
    SECURITY_ATTRIBUTES saEvent, *pSa = NULL;

    if ((TRUE == fInherit) || (pSD))
    {
        ZeroMemory(&saEvent, sizeof(saEvent));
        pSa = &saEvent;
        saEvent.bInheritHandle = fInherit;

        if (pSD)
        {
            // TODO: Add code to deal with security descriptor
        }
    }
    
    m_hEvent = CreateEvent(
                    pSa,
                    fManualReset,
                    (SIGNALED == esInitialState),
                    NULL);
    if (m_hEvent == NULL)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}

//+----------------------------------------------------------------------------
//
// Synopsis: Set the state of an event to SIGNALED.  
//
//-----------------------------------------------------------------------------
HRESULT
RcuEvent::Set()
{
    if (! SetEvent(m_hEvent))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}

//+----------------------------------------------------------------------------
//
// Synopsis: Sets the state of an event to NONSIGNALED 
//
//-----------------------------------------------------------------------------
HRESULT
RcuEvent::Reset()
{
    if (! ResetEvent(m_hEvent))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}

//+----------------------------------------------------------------------------
//
// Synopsis: Pulse an event 
//
//-----------------------------------------------------------------------------
HRESULT
RcuEvent::Pulse()
{
    if (! PulseEvent(m_hEvent))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}

//+----------------------------------------------------------------------------
//
// Synopsis: Create an RW lock.  
//
//      args:
//        m_pcsLock:     used to protect the counter
//        m_peNoReaders: an event that is signaled when there are no readers
//        m_lCounter:    0= not active, 
//                       positive= # of readers, 
//                       negative= # times the same writer aquired this lock
//                      
//-----------------------------------------------------------------------------
RcuRwLock::RcuRwLock() : m_pcsLock(NULL), m_peNoReaders(NULL), m_lCounter(0)
{
}

//+----------------------------------------------------------------------------
//
// Synopsis: Cleanup an RW Lock  
//
//-----------------------------------------------------------------------------
RcuRwLock::~RcuRwLock()
{
    if (m_pcsLock)
    {
        delete m_pcsLock;
    }
    if (m_peNoReaders)
    {
        delete m_peNoReaders;
    }
}

//+----------------------------------------------------------------------------
//
// Synopsis: Initialize an RW lock.  
//
//-----------------------------------------------------------------------------
HRESULT
RcuRwLock::Initialize()
{
    HRESULT hr = S_OK;

    m_pcsLock = new RcuCritSec;
    m_peNoReaders = new RcuEvent;
    if ((NULL == m_pcsLock) || (NULL == m_peNoReaders))
    {
        return E_OUTOFMEMORY;
    }

    hr = m_pcsLock->Initialize();
    if (FAILED(hr))
    {
        return hr;
    }
    
    hr = m_peNoReaders->Initialize(SIGNALED, TRUE);
    if (FAILED(hr))
    {
        return hr;
    }

    return hr;
}

//+----------------------------------------------------------------------------
//
// Synopsis: Aquires a RW lock. 
//
//-----------------------------------------------------------------------------
HRESULT
RcuRwLock::Lock(
        IN RcuRwLockRole Role)
{
    HRESULT hr = S_OK;

    // Both readers and writers enter the critical section to
    // update the event and counter
    //
    hr = m_pcsLock->Enter();
    if (FAILED(hr))
    {
        return hr;
    }

    if (READER == Role)
    {
        // Because we made it into the critical section, we know that there
        // are no writers currently active.  There can't be any writers 
        // waiting on the event yet, either.
        //
    
        // Update the counter and record that readers are active
        // if we're the first reader to enter.
        //
        if (InterlockedIncrement(&m_lCounter) == 1)
        {
            hr = m_peNoReaders->SetState(NONSIGNALED);
        }

        // Allow other readers to enter...
        //
        m_pcsLock->Leave();
    }
    else
    {
        // Because we made it into the critical section, we know that we
        // are the only writer.  There may, however, be several readers
        // that are still busy.
        //
    
        // Update the counter, waiting for any readers to 
        // finish
        //
        if (InterlockedDecrement(&m_lCounter) >= 0)
        {
            WaitForSingleObject(m_peNoReaders->GetHandle(), INFINITE);
        }

        // The writer doesn't leave the critical section until the caller
        // requests to leave the RW lock itself.  This causes all subsequent
        // readers and writers to stay queued up on the critical section
        // until this writer finishes its work.
        //
    }

    return hr;
}

//+----------------------------------------------------------------------------
//
// Synopsis: Releases an RW lock.
//
//-----------------------------------------------------------------------------
HRESULT
RcuRwLock::Unlock(
        IN RcuRwLockRole Role)
{
    HRESULT hr = S_OK;

    if (READER == Role)
    {
        // Update the counter.  If we're the last reader to leave, then update
        // the event accordingly.
        //
        if (InterlockedDecrement(&m_lCounter) <= 0)
        {
            hr = m_peNoReaders->SetState(SIGNALED);
        }
    }
    else
    {
        // Update the counter and leave the critical section
        //
        if (InterlockedIncrement(&m_lCounter) == 0)
        {
            m_pcsLock->Leave();
        }
    }

    return hr;
}
        



