//+---------------------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  File:       mmbuf.cxx
//
//  Contents:   Memory Mapped Buffer, Safe ptr to stream
//
//  Classes:    CMmStreamBuf
//
//----------------------------------------------------------------------------

#include <pch.cxx>
#pragma hdrstop

#include <pmmstrm.hxx>

CMmStreamBuf::~CMmStreamBuf()
{
    if (_buf && _pStream )
        _pStream->Unmap(*this);
}

SMmStream::~SMmStream()
{
    delete _pStream;
}

