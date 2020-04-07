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

//+---------------------------------------------------------------------
//
//  File:       cmallspy.hxx
//
//  Contents:   CMallocSpy definitions
//
//----------------------------------------------------------------------




class CMallocSpy : public IMallocSpy
{
public:
    CMallocSpy(void);
    ~CMallocSpy(void);

    // IUnknown methods
    STDMETHOD(QueryInterface) (REFIID riid, LPVOID *ppUnk);
    STDMETHOD_(ULONG, AddRef) (void);
    STDMETHOD_(ULONG, Release) (void);


    // IMallocSpy methods
    STDMETHOD_(SIZE_T, PreAlloc) (SIZE_T cbRequest);
    STDMETHOD_(void *, PostAlloc) (void *pActual);

    STDMETHOD_(void *, PreFree) (void *pRequest, BOOL fSpyed);
    STDMETHOD_(void, PostFree) (BOOL fSpyed);

    STDMETHOD_(SIZE_T, PreRealloc) (void *pRequest, SIZE_T cbRequest,
                                   void **ppNewRequest, BOOL fSpyed);
    STDMETHOD_(void *, PostRealloc) (void *pActual, BOOL fSpyed);

    STDMETHOD_(void *, PreGetSize) (void *pRequest, BOOL fSpyed);
    STDMETHOD_(SIZE_T, PostGetSize) (SIZE_T cbActual, BOOL fSpyed);

    STDMETHOD_(void *, PreDidAlloc) (void *pRequest, BOOL fSpyed);
    STDMETHOD_(BOOL, PostDidAlloc) (void *pRequest, BOOL fSpyed, BOOL fActual);

    STDMETHOD_(void, PreHeapMinimize) (void);
    STDMETHOD_(void, PostHeapMinimize) (void);


private:
    ULONG    m_cRef;
    SIZE_T   m_cbRequest;

};
