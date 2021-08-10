//+--------------------------------------------------------------------------
//
//      File:       RuMem.cpp
//
//      Synopsis:   Memory allocation api's 
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#include "RuMem.h"

// Generic Memory Free function
//
BOOL
RuFree(
    IN PVOID pvMem       // The pointer to the memory block to free
    )
{
    BOOL fSuccess = FALSE;
    
    do
    {
        if ( NULL == pvMem )
        {
            fSuccess = FALSE;
            break;
        }

        HANDLE hHeap = GetProcessHeap();

        fSuccess = HeapFree(hHeap, 
                            0,
                            pvMem);
    }
    while(FALSE);

    return fSuccess;
}

// Generic memroy allocation function. If succeded, returns the allocated memory pointer, if 
// failed, returns NULL pointer
//
PVOID                       
RuAlloc(
    IN DWORD dwSize,    // how many bytes of memory to allocate
    IN BOOL fZero       // If the allocated memory should be Initialized to 0
    )
{
    PVOID  pvMem = NULL;
    
    HANDLE hHeap = GetProcessHeap();


    if ( NULL == hHeap )
    {
        return NULL;
    }
        
    pvMem = HeapAlloc( hHeap,
                       fZero ? HEAP_ZERO_MEMORY: 0,
                       dwSize);
    return pvMem;
}

