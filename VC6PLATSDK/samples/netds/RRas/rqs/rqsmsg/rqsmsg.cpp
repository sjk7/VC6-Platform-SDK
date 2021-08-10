//+--------------------------------------------------------------------------
//
//      File:       rqsmsg.cpp
//
//      Synopsis:   Event log main function.
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#include <windows.h>

//+--------------------------------------------------------------------------
//
// Synopsis: DLL main
//
//+--------------------------------------------------------------------------
BOOL
WINAPI
DLLMAIN(
    IN HINSTANCE hInstance,
    IN DWORD dwReason,
    IN PVOID pUnused
    ) 
{
    switch(dwReason) 
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);
            break;

        case DLL_PROCESS_DETACH:
            break;

        default:
            break;
    }

    return TRUE;
}

