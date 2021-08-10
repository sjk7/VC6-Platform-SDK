//+--------------------------------------------------------------------------
//
//      File:       RuReg.cpp
//
//      Synopsis:   Registry manipulating api's 
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#include "RasUtil.h"
#include <shlwapi.h>

/*****************************************************************************
                    Prefix in pszKeyPath
-----------------------------------------------------------------------------    
(1)pszKeyPath specifies the location of the registry key to edit
(2)for predefined registry categories:

        HKEY_CLASSES_ROOT
        HKEY_CURRENT_CONFIG
        HKEY_CURRENT_USER
        HKEY_LOCAL_MACHINE
        HKEY_USERS

        HKLM
        HKCU
    We use the same name in the pszKeyPath. Example:
     L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Tracing\\RASDLG"
*****************************************************************************/

typedef struct _RURASREGROOT
{
       PWSTR pszName;
       HKEY  hkRegRoot;
}RURASREGROOT;


static const RURASREGROOT g_ruRegRoot[]=
    {  
       {L"HKEY_CLASSES_ROOT", HKEY_CLASSES_ROOT},
       {L"HKEY_CURRENT_CONFIG", HKEY_CURRENT_CONFIG},
       {L"HKEY_CURRENT_USER", HKEY_CURRENT_USER},
       {L"HKCU",HKEY_CURRENT_USER},
       {L"HKEY_LOCAL_MACHINE",HKEY_LOCAL_MACHINE},
       {L"HKLM",HKEY_LOCAL_MACHINE},
       {L"HKEY_USERS",HKEY_USERS}
    };

#ifndef RURASREGROOTNUM
#define RURASREGROOTNUM    RU_ELEMENT_COUNT(g_ruRegRoot)
#endif


//+----------------------------------------------------------------------------
//
// Synopsis: Internal function, parse the input registry key path
//
//-----------------------------------------------------------------------------
static
HRESULT
RuGetRegRootIndex(
    IN CONST PWSTR pszKeyPath,
    OUT HKEY * phKey,
    OUT PWSTR * ppszSubPath
    )
{
    int i;
    HRESULT hr = S_OK;

    do
    {
        if ( NULL == pszKeyPath ||
             NULL == phKey      ||
             NULL == ppszSubPath )
        {
            hr = E_INVALIDARG;
            break;
        }

        for( i = 0; i < RURASREGROOTNUM; i++ )
        {
            if( pszKeyPath == wcsstr( pszKeyPath, g_ruRegRoot[i].pszName))
            {
                // The key path should include '\' and at leat one more 
                // character
                if( wcslen(pszKeyPath) <= 2 + wcslen( g_ruRegRoot[i].pszName ) )
                {
                    hr = E_INVALIDARG;
                    break;
                }
                
                *phKey = g_ruRegRoot[i].hkRegRoot;
                *ppszSubPath = pszKeyPath + wcslen(g_ruRegRoot[i].pszName)+1;
                hr = S_OK;
                break;
            }
        }
    }
    while(FALSE);
        
    return hr;
}    

//+----------------------------------------------------------------------------
//
// Synopsis: Returns an open registry key at the given path.  In general, the
//           RuReg* functions are supposed to abstract this key.  However, some
//           Api's and applications require that the key itself be passed.  
//           This function is only to be used in those rare situations.
//
//           This function is also used by other RuReg* functions to open the
//           registry key.
//
//-----------------------------------------------------------------------------
HRESULT
RuRegOpenKey(
    IN CONST PWSTR pszKeyPath, 
    IN BOOL fCreate,
    OUT HKEY* phKey)
{
    HRESULT hr;
    HKEY hkRoot = NULL;
    PWSTR pszSubPath = NULL;

    hr = RuGetRegRootIndex(pszKeyPath, &hkRoot, &pszSubPath);
    if (hr != S_OK)
    {
        return hr;
    }

    if (fCreate)
    {
        hr = RegCreateKeyExW( 
                     hkRoot,
                     pszSubPath,
                     0,
                     NULL,
                     REG_OPTION_NON_VOLATILE,
                     KEY_ALL_ACCESS,
                     NULL,
                     phKey,
                     NULL
                     );
    }
    else
    {
        hr = RegOpenKeyExW( 
                    hkRoot,
                    pszSubPath,
                    0,
                    KEY_ALL_ACCESS,
                    phKey);
    }                    

    if( S_OK != hr )
    {
        hr = HRESULT_FROM_WIN32(hr);
    }

    return hr;
}

//+----------------------------------------------------------------------------
//
// Synopsis: retrieve value/values under a registry key
//
//  ret: The function returns S_OK if at least one value was successfully read.  
//       Each value contains an error code field that is set to indicate status.
//
//  (1)
//  Get the value/values under a specific registry key, if succeeded, the 
//  function will allocate memory to store data and store the memory pointer in 
//  pRegVal[i].pbData, it is the caller's responsibility to free the allocated 
//  memory by calling RuFree() or RuRegFreeValues()
//  (2)
//  if return Value is not NO_ERROR, uiSize in pRegVal will 
//  be set to 0 and pbData in pRegVal will be set to NULL
//
//-----------------------------------------------------------------------------
HRESULT
RuRegGet(
    IN CONST PWSTR pszKeyPath,
    IN OUT RUREGVALUE * pRegVal,
    IN DWORD dwCount
    )
{
    HKEY hKey=0L;
    DWORD i, iSuccess;
    DWORD dwErr = NO_ERROR;
    HRESULT hr;

    do
    {
        if( NULL == pszKeyPath ||
            NULL == pRegVal    ||
            0 == dwCount )
        {
            hr = E_INVALIDARG;
            break;
        }

        hr = RuRegOpenKey(pszKeyPath, FALSE, &hKey);
        RU_BREAK_IF_NOT_OK(hr);

        for( i = 0; i < dwCount; i++)
        {
            pRegVal[i].dwSize = 0L;
            pRegVal[i].pbData = NULL;
        }
        
        iSuccess = 0;
        for ( i = 0; i < dwCount; i++ )
        {   
            //Get the size of the data
            //
            pRegVal[i].pbData = NULL;
            dwErr = RegQueryValueExW(
                        hKey,
                        pRegVal[i].pszName,
                        0,
                        &pRegVal[i].dwType,
                        NULL,
                        &pRegVal[i].dwSize
                        );
            if( ERROR_SUCCESS != dwErr )
            {
                pRegVal[i].hr = HRESULT_FROM_WIN32(dwErr);
                continue;
            }

            pRegVal[i].pbData = (BYTE*)RuAlloc(pRegVal[i].dwSize,0);
            if( NULL == pRegVal[i].pbData)
            {
                pRegVal[i].hr = E_OUTOFMEMORY;
                continue;
            }

            dwErr = RegQueryValueExW(
                hKey,
                pRegVal[i].pszName,
                0,
                &pRegVal[i].dwType,
                pRegVal[i].pbData,
                &pRegVal[i].dwSize
                );

            if( ERROR_SUCCESS != dwErr)
            {
                pRegVal[i].hr = HRESULT_FROM_WIN32(dwErr);
                continue;
            }
            
            iSuccess++;
        }

        // If nothing was successfully read, then return the error code from
        // the first value
        //
        if (iSuccess == 0)
        {
            hr = pRegVal[0].hr;
        }
        else
        {
            hr = S_OK;
        }
                      
    }
    while(FALSE);

    if(hKey)
    {
        RegCloseKey(hKey);
    }

    return hr;
}

//+----------------------------------------------------------------------------
//
// Synopsis: Simple helper function frees an array of values returned by 
//           RuRegGet.
//
//-----------------------------------------------------------------------------
VOID
RuRegFreeValues(
    IN CONST RUREGVALUE* pValues,
    IN UINT uiCount)
{    
    UINT i; 
    
    for (i = 0; i < uiCount; i++)
    {
        if (pValues[i].pbData)
        {
            RuFree(pValues[i].pbData);
        }
    }
}        

