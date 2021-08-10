//+--------------------------------------------------------------------------
//
//      File:       RcuSync.h
//
//      Synopsis:   Sychronization objects.
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------


#pragma once

#ifndef __RcuSync_h
#define __RcuSync_h

#ifdef __cplusplus

class RcuSecurityDescriptor;  // TODO: Remove this when it is designed/implemented

//+----------------------------------------------------------------------------
//
// Synopsis: Critical section object
//
//-----------------------------------------------------------------------------
class RcuCritSec
{
public:
    RcuCritSec();
    ~RcuCritSec();

    HRESULT
    Initialize();

    HRESULT
    Enter();

    VOID
    Leave();
    
private:
    CRITICAL_SECTION m_CritSec;  
    BOOL m_fInitialized;
};

//+----------------------------------------------------------------------------
//
// Synopsis: Event object
//
//-----------------------------------------------------------------------------
enum RcuEventState
{
    SIGNALED,
    NONSIGNALED
};

class RcuEvent
{
public:
    RcuEvent();
    ~RcuEvent();

    HRESULT
    Initialize(
        IN RcuEventState esInitialState,
        IN BOOL fManualReset,
        IN BOOL fInherit = FALSE,
        IN RcuSecurityDescriptor* pSD = NULL);

    HANDLE
    GetHandle() const
    {
        return m_hEvent;
    }
    
    HRESULT
    SetState(
        IN RcuEventState esState)
    {
        return (SIGNALED == esState) ? Set() : Reset();
    }

    HRESULT
    Set();

    HRESULT
    Reset();

    HRESULT
    Pulse();

private:
    HANDLE m_hEvent; 
};

//+----------------------------------------------------------------------------
//
// Synopsis: Multiple-reader-single-writer lock
//
//-----------------------------------------------------------------------------

enum RcuRwLockRole
{
    READER,
    WRITER
};

class RcuRwLock
{
public:
    RcuRwLock();
    ~RcuRwLock();

    HRESULT
    Initialize();

    HRESULT
    Lock(
        IN RcuRwLockRole Role);

    HRESULT
    Unlock(
        IN RcuRwLockRole Role);

private:
    RcuCritSec* m_pcsLock;
    RcuEvent* m_peNoReaders;
    LONG m_lCounter;
};




#endif
#endif


