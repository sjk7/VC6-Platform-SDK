// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------

#include <windows.h>
#include <ole2.h>
#include "cmallspy.hxx"

extern "C" void printf(CHAR*, ...);

const UINT NALLOCATIONS = 573;


int __cdecl main(int argc, char **argv)
{
    HRESULT     hr;
    LPMALLOCSPY pMallocSpy = new CMallocSpy();

    // Initialize
    CoInitialize(NULL);
    hr = CoRegisterMallocSpy(pMallocSpy);
    if (hr != S_OK)
    {
        printf("CoRegisterMallocSpy failed with %x\n", hr);
        CoUninitialize();
        return 0;
    }
    printf("CoRegisterMallocSpy succeeded.\n");

    // Allocate enoungh to force an expansion
    LPMALLOC pMalloc;
    void    *allocs[NALLOCATIONS];
    ULONG j;

    if ((hr = CoGetMalloc(MEMCTX_TASK, &pMalloc)) != S_OK)
    {
        printf("CoGetMalloc failed with %x\n", hr);
        CoUninitialize();
        return 0;
    }
    printf("CoGetMalloc succeeded.\n");
    printf("Allocating %u memory blocks.\n", NALLOCATIONS);
    for (j = 0; j < NALLOCATIONS; j++)
    {
        allocs[j] = pMalloc->Alloc(173);
    }

    // Now release everything
    printf("Releasing %u memory blocks.\n", NALLOCATIONS);
    for (j = 0; j < NALLOCATIONS; j++)
    {
        pMalloc->Free(allocs[j]);
        allocs[j] = NULL;
    }

    printf("Test complete.\n");
    // All done
    CoRevokeMallocSpy();
    CoUninitialize();
    return 0;
}


