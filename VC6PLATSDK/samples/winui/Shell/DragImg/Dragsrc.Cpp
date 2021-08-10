/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1999 - 2000 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DragSrc.cpp

   Description:   

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "DragSrc.h"

/**************************************************************************

   CDragSource::CDragSource()

**************************************************************************/

CDragSource::CDragSource()
{
m_cRefCount = 1;
}

/**************************************************************************

   CDragSource::~CDragSource()

**************************************************************************/

CDragSource::~CDragSource()
{
}

///////////////////////////////////////////////////////////////////////////
//
// IUnknown Implementation
//

/**************************************************************************

   CDragSource::QueryInterface()

**************************************************************************/

STDMETHODIMP CDragSource::QueryInterface(REFIID riid, LPVOID* ppvOut)
{
*ppvOut = NULL;

//IUnknown
if(IsEqualIID(riid, IID_IUnknown))
   {
   *ppvOut = this;
   }

//IDropSource
else if(IsEqualIID(riid, IID_IDropSource))
   {
   *ppvOut = (IDropSource*)this;
   }

if(*ppvOut)
   {
   (*(LPUNKNOWN*)ppvOut)->AddRef();
   return S_OK;
   }

return E_NOINTERFACE;
}

/**************************************************************************

   CDragSource::AddRef()

**************************************************************************/

STDMETHODIMP_(ULONG) CDragSource::AddRef(void)
{
return ++m_cRefCount;
}

/**************************************************************************

   CDragSource::Release()

**************************************************************************/

STDMETHODIMP_(ULONG) CDragSource::Release(void)
{
if(--m_cRefCount == 0)
   {
   delete this;
   return 0;
   }
   
return m_cRefCount;
}

///////////////////////////////////////////////////////////////////////////
//
// IDropSource Implementation
//

/**************************************************************************

   CDragSource::GiveFeedback()

**************************************************************************/

STDMETHODIMP CDragSource::GiveFeedback(DWORD dwEffect)
{
return DRAGDROP_S_USEDEFAULTCURSORS;
}

/**************************************************************************

   CDragSource::QueryContinueDrag()

**************************************************************************/

STDMETHODIMP CDragSource::QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState)
{
if(fEscapePressed)
   return DRAGDROP_S_CANCEL;

if(!(grfKeyState & MK_LBUTTON))
   return DRAGDROP_S_DROP;

return S_OK;
}
