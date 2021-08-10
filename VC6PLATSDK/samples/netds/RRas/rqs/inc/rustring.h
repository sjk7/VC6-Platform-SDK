//+--------------------------------------------------------------------------
//
//  File:       RuString.h
//
//  Synopsis:   String helper functions
//
//  Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//---------------------------------------------------------------------------
 
#pragma once

#ifndef __RuString_h
#define __RuString_h

//----------------------------------------------------------------------------
//
//                              Narrow <-> Wide conversions
//
//----------------------------------------------------------------------------

PSTR
RuStringDupWtoA(
    IN      PWSTR   psz
);

PWSTR
RuStringDupAtoW(
    IN      PSTR    pszansi
);


#endif // __RuString_h

