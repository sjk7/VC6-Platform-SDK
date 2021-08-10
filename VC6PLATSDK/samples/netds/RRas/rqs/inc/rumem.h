//+--------------------------------------------------------------------------
//
//      File:       RuMem.h
//
//      Synopsis:   Memory allocation api's 
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#ifndef _RAS_RUMEM_H
#define _RAS_RUMEM_H

#include "RasUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

BOOL RuFree(IN PVOID pvMem);

PVOID RuAlloc(
    IN DWORD dwSize,    // how many bytes of memory to allocate
    IN BOOL fZero       // If the allocated memory should be Initialized to 0
    );

#ifdef __cplusplus
}
#endif

#endif
