//+--------------------------------------------------------------------------
//
//      File:       RuReg.h
//
//      Synopsis:   Registry manipulating api's 
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#ifndef _RU_REG_H
#define _RU_REG_H

#include "RasUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

//  pszName: the name of the value to Set/Get
//  dwType:  the type of the data
//  dwSize:  the size of pbData in bytes
//  pbData:  pointer to the data 
//  dwErr:   on output, specifies an error on read/write of the value
//
//  For DWORD, BYTE, dwSize is the actual size of the data for REG_SZ,
//  REG_EXPAND_SZ, or REG_MULTI_SZ, dwSize includes the terminating NULL 
//  character.
//
typedef struct _RUREGVALUE
{
    PWSTR  pszName;
    DWORD  dwType; 
    DWORD  dwSize;  // the size of the data like the registry API
    BYTE * pbData; 
    HRESULT  hr;   
} RUREGVALUE, * PRUREGVALUE;

HRESULT
RuRegOpenKey(
    IN CONST PWSTR pszKeyPath, 
    IN BOOL fCreate,
    OUT HKEY* phKey);

HRESULT
RuRegGet(
    IN CONST PWSTR pszKeyPath,
    IN OUT RUREGVALUE * pRegVal,
    IN DWORD dwCount
    );

VOID
RuRegFreeValues(
    IN CONST RUREGVALUE* pValues,
    IN UINT uiCount);
    
    
   
#ifdef __cplusplus
}
#endif

#endif
