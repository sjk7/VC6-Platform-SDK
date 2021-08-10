//+---------------------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  File:       mmscbuf.hxx
//
//  Contents:   Memory Mapped Stream buffer for consecutive buffer mapping
//
//  Classes:    CMmStreamConsecBuf
//
//
//----------------------------------------------------------------------------

#if !defined __MMSCBUF_HXX__
#define __MMSCBUF_HXX__

#include <pmmstrm.hxx>

//+---------------------------------------------------------------------------
//
//  Class:      CMmStreamConsecBuf
//
//  Purpose:    Memory Mapped Stream Buffer for consecutive buffer mapping
//
//
//----------------------------------------------------------------------------
class CMmStreamConsecBuf: public CMmStreamBuf
{
public:

    CMmStreamConsecBuf();

    void Init( PMmStream * pMmStream );

    void Map ( ULONG cb );

    void Rewind ();

    BOOL Eof();

private:

    PMmStream *     _pMmStream;
    LARGE_INTEGER   _liOffset;
};

#endif
