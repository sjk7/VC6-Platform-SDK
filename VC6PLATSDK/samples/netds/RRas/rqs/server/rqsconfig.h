//+--------------------------------------------------------------------------
//
//      File:       RqsConfig.h
//
//      Synopsis:   Class to read configuration for the server-side quarantine
//                  removal utility.
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#pragma once

class RqsEngine;

typedef struct _RqsConfigString
{
    CHAR* pszString;
    UINT uiLength;
} RqsConfigString;

class RqsConfig
{
public:
    RqsConfig();
    ~RqsConfig();

    VOID Clear();

    HRESULT LoadTrace();
    HRESULT LoadConfig();
    HRESULT Load();
    
    UINT GetPort() const; 
    BOOL GetTraceEnabled() const;
    BOOL GetDebugTrace() const;
    CONST WCHAR* GetLibrary() const;

    BOOL Find(IN CHAR* pszString) const;

    static const PWSTR GetConfigPath();
    static const PWSTR GetTracePath();

    VOID TraceSelf(const RqsEngine& Engine);
    
private:
    RqsConfigString* m_pStrings;
    UINT m_uiCount;
    UINT m_uiPort;
    BOOL m_fTraceEnabled;
    BOOL m_fDebuggerTrace;
    PWSTR m_pszLibrary;

    VOID ClearStrings(IN RqsConfigString* pStrings, IN UINT uiCount);
    
};

