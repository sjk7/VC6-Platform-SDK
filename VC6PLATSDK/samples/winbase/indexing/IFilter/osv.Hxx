//+---------------------------------------------------------------------------
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// File:        osv.hxx
//
// Contents:    OS Version API
//
//----------------------------------------------------------------------------

#if !defined( __OSV_HXX__ )
#define __OSV_HXX__

extern int g_nOSWinNT;

void InitOSVersion();

inline DWORD GetOSVersion()
{
    return g_nOSWinNT;
}

#endif // __OSV_HXX__
