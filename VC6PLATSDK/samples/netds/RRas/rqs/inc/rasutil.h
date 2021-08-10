//+---------------------------------------------------------------------------
//
//  Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//  File:       RasUtil.h
//
//  Contents:   Master include file for ras utilities.
//
//  Notes:
//
//----------------------------------------------------------------------------

#pragma once

#ifndef __RasUtil_h
#define __RasUtil_h

#include "RuSocket.h"
#include "RuMem.h"
#include "RuReg.h"
#include "RuString.h"
#include "RcuSync.h"

#define RU_ELEMENT_COUNT( x )   ( sizeof( x ) / sizeof( *x ) )

#define RU_LEAVE_IF_NOT_OK(x)   if ( S_OK != (x)) __leave;
#define RU_LEAVE_IF_NULL(x)     if ( NULL == (x)) __leave;
#define RU_LEAVE_HR_IF_NULL(x, ret)  if ( NULL == (x) ) { hr = (ret); __leave; }

#define RU_RETURN_IF_NOT_OK(x)        if ( S_OK != (x)) return (x);
#define RU_RETURN_IF_NULL_PARAM(x)    if ( NULL == (x) ) return E_INVALIDARG;

#define RU_BREAK_IF_NOT_OK(x) if (S_OK != (x)) break;
#define RU_BREAK_IF_NULL(x)   if ( NULL == (x)) break;
#define RU_BREAK_HR_IF_NULL( x, ret )  if ( NULL == (x) ) { hr = (ret); break; }

#define S_RU_EQUALS                     ((HRESULT)0x000abc01L)
#define S_RU_GREATER                    ((HRESULT)0x000abc02L)
#define S_RU_LESS                       ((HRESULT)0x000abc03L)

#endif

