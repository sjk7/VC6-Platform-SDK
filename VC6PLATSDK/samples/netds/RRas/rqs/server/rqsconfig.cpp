//+--------------------------------------------------------------------------
//
//      File:       RqsConfig.cpp
//
//      Synopsis:   Class to read configuration for the server-side quarantine
//                  removal utility.
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#include <Rqs.h>

static const UINT g_uiPort = 7250;

static int __cdecl 
RqsCompare(
    IN const void* elem1,
    IN const void* elem2)
{
    RqsConfigString* p1 = (RqsConfigString*) elem1;
    RqsConfigString* p2 = (RqsConfigString*) elem2;
   
    return strcmp( p1->pszString, p2->pszString );
}

//+--------------------------------------------------------------------------
//
// Synopsis: Creates a configuration object 
//
//+--------------------------------------------------------------------------
RqsConfig::RqsConfig() : m_pStrings(NULL), m_uiCount(0), 
                        m_uiPort(g_uiPort), m_fTraceEnabled(FALSE),
                        m_fDebuggerTrace(FALSE), m_pszLibrary(NULL)
{
}

//+--------------------------------------------------------------------------
//
// Synopsis: Destroys a configuration object 
//
//+--------------------------------------------------------------------------
RqsConfig::~RqsConfig()
{
    Clear();
}

//+--------------------------------------------------------------------------
//
// Synopsis: Helper function clears a table of strings. 
//
//+--------------------------------------------------------------------------
VOID
RqsConfig::ClearStrings(
    IN RqsConfigString* pStrings,
    IN UINT uiCount)
{
    UINT i; 
    
    for (i = 0; i < uiCount; i++)
    {
        RuFree(pStrings[i].pszString);
    }
    delete [] pStrings;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Clears a configuration object 
//
//+--------------------------------------------------------------------------
VOID 
RqsConfig::Clear()
{

    if (m_pStrings)
    {
        ClearStrings(m_pStrings, m_uiCount);
    }

    m_pszLibrary = NULL;
    m_pStrings = NULL;
    m_uiCount = 0;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Returns the port 
//
//+--------------------------------------------------------------------------
UINT 
RqsConfig::GetPort() const
{   
    return m_uiPort;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Returns whether debugger tracing is enabled
//
//+--------------------------------------------------------------------------
BOOL
RqsConfig::GetDebugTrace() const
{   
    return m_fDebuggerTrace;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Returns whether tracing is enabled
//
//+--------------------------------------------------------------------------
BOOL
RqsConfig::GetTraceEnabled() const
{   
    return m_fTraceEnabled;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Returns the library to load for authentication.
//
//+--------------------------------------------------------------------------
CONST WCHAR*
RqsConfig::GetLibrary() const
{   
    if (m_pszLibrary)
    {
        return m_pszLibrary;
    }

    return L"mprapi.dll";
}

//+--------------------------------------------------------------------------
//
// Synopsis: Loads the trace settings 
//
//+--------------------------------------------------------------------------
HRESULT 
RqsConfig::LoadTrace()
{
    HRESULT hr = S_OK;
    RUREGVALUE ruVals[] =
    {
        {
            L"EnableConsoleTracing", 
            REG_DWORD, 
            0, 
            NULL, 
            0
        },
        {
            L"EnableFileTracing", 
            REG_DWORD, 
            0, 
            NULL, 
            0
        }
    };

    __try
    {
        m_fTraceEnabled = FALSE;
    
        hr = RuRegGet(
                GetTracePath(),
                ruVals,
                RU_ELEMENT_COUNT(ruVals));
        if (hr != NO_ERROR)
        {
           hr = HRESULT_FROM_WIN32(hr);
           __leave;
        }

        // If either value is set, then set m_fTracing
        //
        if (S_OK == ruVals[0].hr)
        {
            if (*((DWORD*)ruVals[0].pbData))
            {
                m_fTraceEnabled = TRUE;
            }
        }

        if (S_OK == ruVals[1].hr)
        {
            if (*((DWORD*)ruVals[1].pbData))
            {
                m_fTraceEnabled = TRUE;
            }
        }

    }

    __finally
    {
        RuRegFreeValues(ruVals, RU_ELEMENT_COUNT(ruVals));
    }

    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Loads configuration settings 
//
//+--------------------------------------------------------------------------
HRESULT 
RqsConfig::LoadConfig()
{
    DWORD dwErr = NO_ERROR;
    HRESULT hr = S_OK;
    WCHAR* pszCur;
    UINT uiCount = 0, uiLen;
    CHAR* pszString;
    RqsConfigString* pStrings = NULL;
    RUREGVALUE ruVals[] =
    {
        {
            L"AllowedSet", 
            REG_MULTI_SZ, 
            0, 
            NULL, 
            0
        },
        {
            L"Port", 
            REG_DWORD, 
            0, 
            NULL, 
            0
        },
        {
            L"DebuggerTrace", 
            REG_DWORD, 
            0, 
            NULL, 
            0
        },
        {
            L"Authenticator", 
            REG_SZ,
            0, 
            NULL, 
            0
        }
    };

    __try
    {
        // Read the multisz from the registry
        //
        dwErr = RuRegGet(
                   GetConfigPath(),
                   ruVals,
                   RU_ELEMENT_COUNT(ruVals));
        if (dwErr != NO_ERROR)
        {
           hr = HRESULT_FROM_WIN32(dwErr);
           __leave;
        }

        // Read in the [optional] allowed set.  
        //
        if (S_OK == ruVals[0].hr)
        {
            // Count the number of wide-character strings
            //
            pszCur = (WCHAR*) ruVals[0].pbData;
            while (*pszCur)
            {
                uiCount++;
                pszCur += wcslen(pszCur) + 1;
            }
            if (uiCount)
            {
                // Allocate the array of ansi strings
                //
                pStrings = new RqsConfigString[uiCount];
                if (pStrings == NULL)
                {
                    hr = E_OUTOFMEMORY;
                    __leave;
                }
                ZeroMemory(pStrings, sizeof(pStrings) * uiCount);

                uiCount = 0;
                pszCur = (WCHAR*) ruVals[0].pbData;
                while (*pszCur)
                {
                    // Covert the unicode string to ansi
                    //
                    pszString = RuStringDupWtoA(pszCur);
                    if (pszString == NULL)
                    {
                        hr = E_OUTOFMEMORY;
                        __leave;
                    }

                    // If the string ends in '*', then we only want to compare 
                    // the characters up to that wildcard symbol
                    //
                    uiLen = (UINT)strlen(pszString);
                    if (pszString[uiLen - 1] == '*')
                    {
                        pStrings[uiCount].uiLength = uiLen - 1;
                    }
                    else
                    {
                        pStrings[uiCount].uiLength = 0;
                    }

                    pStrings[uiCount].pszString = pszString;
                    pszCur += wcslen(pszCur) + 1;
                    uiCount++;
                }

                // Sort the set of allowed strings
                //
                qsort(
                    pStrings, 
                    uiCount, 
                    sizeof(RqsConfigString), 
                    RqsCompare);

                ClearStrings(m_pStrings, m_uiCount);                    
                m_pStrings = pStrings;
                m_uiCount = uiCount;
            }
        }

        // Read in the [optional] port
        //
        if (S_OK == ruVals[1].hr)
        {
            m_uiPort = *((DWORD*)ruVals[1].pbData);
        }

        // Read in the [optional] debug trace flag
        //
        if (S_OK == ruVals[2].hr)
        {
            m_fDebuggerTrace = *((DWORD*)ruVals[2].pbData);
        }
        
        // Read in the [optional] authenticator
        //
        if (S_OK == ruVals[3].hr)
        {
            m_pszLibrary = (reinterpret_cast<CONST PWSTR>(ruVals[3].pbData));
        }
        
    }

    __finally
    {
        RuRegFreeValues(ruVals, RU_ELEMENT_COUNT(ruVals));
        if ((S_OK != hr) && (pStrings))
        {
            ClearStrings(pStrings, uiCount);
        }
    }

    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Loads the configuration object 
//
//+--------------------------------------------------------------------------
HRESULT 
RqsConfig::Load()
{
    HRESULT hr = S_OK;

    // Ignore the error return from LoadTrace -- it's safe to continue
    // without it.
    //
    LoadTrace();
    hr = LoadConfig();

    return hr;
}
//+--------------------------------------------------------------------------
//
// Synopsis: Finds a string in the "allowed strings table" of the 
//           configuration object.
//
//+--------------------------------------------------------------------------
BOOL 
RqsConfig::Find(
    IN CHAR* pszString) const
{
    INT iRet;
    
    for (UINT i = 0; i < m_uiCount; i++)
    {
        // Wild card strings have non-zero length.  If the length is 0, 
        // it means we should do an exact string comparison.
        //
        if (m_pStrings[i].uiLength == 0)
        {
            iRet = strcmp(
                        m_pStrings[i].pszString, 
                        pszString);
        }
        else
        {
            iRet = strncmp(
                    m_pStrings[i].pszString, 
                    pszString, 
                    m_pStrings[i].uiLength);
        }
                
        if (iRet == 0)
        {
            return TRUE;
        }
        else if (iRet == 1)
        {
            return FALSE;
        }
    }

    return FALSE;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Returns the registry path where configuration is stored 
//
//+--------------------------------------------------------------------------
const PWSTR 
RqsConfig::GetConfigPath()
{
    return L"HKLM\\System\\CurrentControlSet\\Services\\Rqs";
}

//+--------------------------------------------------------------------------
//
// Synopsis: Returns the registry path where the tracing enabling/disabling
//           is stored.
//
//+--------------------------------------------------------------------------
const PWSTR
RqsConfig::GetTracePath()
{
    return L"HKLM\\Software\\Microsoft\\Tracing\\Rqs";
}

//+--------------------------------------------------------------------------
//
// Synopsis: Traces the current configuration using the engine provided
//
//+--------------------------------------------------------------------------
VOID 
RqsConfig::TraceSelf(
    IN const RqsEngine& Engine)
{
    UINT i;

    Engine.Trace("Port %d", m_uiPort);
    Engine.Trace("Trace: %d", m_fTraceEnabled);
    Engine.Trace("Debugger Trace: %d", m_fDebuggerTrace);
    Engine.Trace("%d strings:", m_uiCount);
    
    for (i = 0; i < m_uiCount; i++)
    {
       Engine.Trace(
            "[%04d] %s", 
            m_pStrings[i].uiLength, 
            m_pStrings[i].pszString);
    }

}

