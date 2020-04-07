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
#include "idog_i.c"
#include "cdog.h"

// {F40B88C1-D534-11d1-9D01-0060081982D5}
//static const IID IID_IDog = 
//{ 0xf40b88c1, 0xd534, 0x11d1, { 0x9d, 0x1, 0x0, 0x60, 0x8, 0x19, 0x82, 0xd5 } };

// {F40B88C2-D534-11d1-9D01-0060081982D5}
//static const CLSID CLSID_Dog = 
//{ 0xf40b88c2, 0xd534, 0x11d1, { 0x9d, 0x1, 0x0, 0x60, 0x8, 0x19, 0x82, 0xd5 } };

// IUnknown
STDMETHODIMP CDog::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{   
    *ppv = NULL;
    
    if (iid == IID_IUnknown || iid == IID_IDog)
        *ppv = (IDog*)this;
    else 
        return ResultFromScode(E_NOINTERFACE); 

    AddRef();
    return NOERROR;    
}

STDMETHODIMP_(ULONG) CDog::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) CDog::Release()
{   
    if(InterlockedDecrement(&m_cRef) == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}

// IDog
STDMETHODIMP CDog::Bark()
{
  OutputDebugString("Bark!");
  return S_OK;
}

STDMETHODIMP CDog::Scratch()
{
  OutputDebugString("Scratch, scratch...");
  return S_OK;
}
