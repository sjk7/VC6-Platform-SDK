// -----------------------------------------------------------------
// File name:  WEPCODE.C
//
// This is the source file that contains the DLL's Windows Exit
// Procedure (WEP).
//
// Description of functions:
//
//    WEP         -     The Windows Exit Procedure.  Every DLL must have
//                      one of these.
//
//
// Written by Microsoft Product Support Services, Windows Developer Support.
//
// Copyright 1991 - 2000 Microsoft Corporation.  All rights reserved.
// -----------------------------------------------------------------

#define     STRICT      // enable strict type checking

#include <windows.h>

// -----------------------------------------------------------------
//
// WEP()
//
// Purpose:  Called by Windows just before Windows unloads the DLL.
//
// Parameters:  int  nParameter     -  This is a dummy parameter.
//                                     Windows expects this parameter
//                                     so be sure to include it.
//
// Return Value:  Always returns 1 to indicate success.
//
// Comments:  Every DLL MUST have a WEP.  WEP, as defined here, is the
//            proper way to define a WEP; do not do anything else
//            except return 1 because the WEP is called on the Windows
//            Kernel's stack, which is very small.
//
// -----------------------------------------------------------------


int APIENTRY WEP (int nParameter)
{
    return (1);
}
