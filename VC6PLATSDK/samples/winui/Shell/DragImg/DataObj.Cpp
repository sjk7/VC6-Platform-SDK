/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1999 - 2000 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DataObj.cpp

   Description:   

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "DataObj.h"
#include "EnumFE.h"
#include "Render.h"
#include <shlobj.h>

/**************************************************************************
   global variables and definitions
**************************************************************************/

extern USHORT  g_cfFileContents;
extern USHORT  g_cfFileGroupDescriptor;

/**************************************************************************

   CDataObject::CDataObject()

**************************************************************************/

CDataObject::CDataObject()
{
m_cRefCount = 1;
m_pFormatEtc = NULL;
m_pStgMedium = NULL;
m_cDataCount = 0;
}

/**************************************************************************

   CDataObject::~CDataObject()

**************************************************************************/

CDataObject::~CDataObject()
{
if(m_pFormatEtc)
   delete m_pFormatEtc;

if(m_pStgMedium)
   {
   DWORD i;

   for(i = 0; i < m_cDataCount; i++)
      ReleaseStgMedium(&m_pStgMedium[i]);

   delete m_pStgMedium;
   }
}

///////////////////////////////////////////////////////////////////////////
//
// IUnknown Implementation
//

/**************************************************************************

   CDataObject::QueryInterface()

**************************************************************************/

STDMETHODIMP CDataObject::QueryInterface(REFIID riid, LPVOID *ppvOut)
{
*ppvOut = NULL;

//IUnknown
if(IsEqualIID(riid, IID_IUnknown))
   {
   *ppvOut = this;
   }

//IDataObject
else if(IsEqualIID(riid, IID_IDataObject))
   {
   *ppvOut = (IDataObject*)this;
   }

if(*ppvOut)
   {
   (*(LPUNKNOWN*)ppvOut)->AddRef();
   return S_OK;
   }

return E_NOINTERFACE;
}

/**************************************************************************

   CDataObject::AddRef()

**************************************************************************/

STDMETHODIMP_(ULONG) CDataObject::AddRef(void)
{
return ++m_cRefCount;
}

/**************************************************************************

   CDataObject::Release()

**************************************************************************/

STDMETHODIMP_(ULONG) CDataObject::Release(void)
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
// IDataObject Implementation
//

/**************************************************************************

   CDataObject::GetData()

**************************************************************************/

STDMETHODIMP CDataObject::GetData(LPFORMATETC pFE, LPSTGMEDIUM pSM)
{
if(pFE == NULL || pSM == NULL)
   return E_INVALIDARG;

ZeroMemory(pSM, sizeof(STGMEDIUM));

DWORD i;

for(i = 0; i < m_cDataCount; i++)
   {
   if(   (pFE->tymed & m_pFormatEtc[i].tymed) && 
         (pFE->dwAspect == m_pFormatEtc[i].dwAspect) && 
         (pFE->cfFormat == m_pFormatEtc[i].cfFormat) &&
         (pFE->lindex == m_pFormatEtc[i].lindex))
      {
      HRESULT  hr;

      hr = CopyStgMedium(&m_pStgMedium[i], pSM);

      if(pSM->tymed == TYMED_HGLOBAL)
         {
         //this tell's the caller not to free the global memory
         QueryInterface(IID_IUnknown, (LPVOID*)&pSM->pUnkForRelease);
         }

      return hr;
      }
   }

return DV_E_FORMATETC;
}

/**************************************************************************

   CDataObject::GetDataHere()

**************************************************************************/

STDMETHODIMP CDataObject::GetDataHere(LPFORMATETC pFE, LPSTGMEDIUM pSM)
{
return E_NOTIMPL;
}

/**************************************************************************

   CDataObject::QueryGetData()

**************************************************************************/

STDMETHODIMP CDataObject::QueryGetData(LPFORMATETC pFE)
{ 
if(!pFE)
   return DV_E_FORMATETC;
  
if(!(DVASPECT_CONTENT & pFE->dwAspect))
   return DV_E_DVASPECT;

//now check for an appropriate TYMED.
DWORD    i;
HRESULT  hr = DV_E_TYMED;

for(i = 0; i < m_cDataCount; i++)
   {
   if(pFE->tymed & m_pFormatEtc[i].tymed)
      {
      if(pFE->cfFormat == m_pFormatEtc[i].cfFormat)
         return S_OK;
      else
         hr = DV_E_CLIPFORMAT;
      }
   else
      hr = DV_E_TYMED;
   }

return hr;
}

/**************************************************************************

   CDataObject::GetCanonicalFormatEtc()

**************************************************************************/

STDMETHODIMP CDataObject::GetCanonicalFormatEtc(LPFORMATETC pFE1, LPFORMATETC pFE2)
{
return DATA_S_SAMEFORMATETC;
}

/**************************************************************************

   CDataObject::SetData()

**************************************************************************/

STDMETHODIMP CDataObject::SetData(LPFORMATETC pFE , LPSTGMEDIUM pSM, BOOL fRelease)
{
LPFORMATETC pfeNew;
LPSTGMEDIUM psmNew;

m_cDataCount++;

pfeNew = new FORMATETC[m_cDataCount];
psmNew = new STGMEDIUM[m_cDataCount];

if(pfeNew && psmNew)
   {
   ZeroMemory(pfeNew, sizeof(FORMATETC) * m_cDataCount);
   ZeroMemory(psmNew, sizeof(STGMEDIUM) * m_cDataCount);
   
   //copy the existing data
   if(m_pFormatEtc)
      {
      CopyMemory(pfeNew, m_pFormatEtc, sizeof(FORMATETC) * (m_cDataCount - 1));
      }
   if(m_pStgMedium)
      {
      CopyMemory(psmNew, m_pStgMedium, sizeof(STGMEDIUM) * (m_cDataCount - 1));
      }
   
   //add the new data
   pfeNew[m_cDataCount - 1] = *pFE;
   if(fRelease)
      {
      psmNew[m_cDataCount - 1] = *pSM;
      }
   else
      {
      CopyStgMedium(pSM, &psmNew[m_cDataCount - 1]);
      }

   LPFORMATETC pfeTemp = m_pFormatEtc;
   m_pFormatEtc = pfeNew;
   pfeNew = pfeTemp;

   LPSTGMEDIUM psmTemp = m_pStgMedium;
   m_pStgMedium = psmNew;
   psmNew = psmTemp;
   }

if(pfeNew)
   delete [] pfeNew;

if(psmNew)
   delete [] psmNew;

if(m_pFormatEtc && m_pStgMedium)
   return S_OK;

return E_OUTOFMEMORY;
}

/**************************************************************************

   CDataObject::EnumFormatEtc()

**************************************************************************/

STDMETHODIMP CDataObject::EnumFormatEtc(DWORD dwDir, LPENUMFORMATETC *ppEnum)
{
*ppEnum = NULL;

switch(dwDir)
   {
   case DATADIR_GET:
      {
      *ppEnum = new CEnumFormatEtc(m_pFormatEtc, m_cDataCount);

      if(*ppEnum)
         return S_OK;

      break;
      }
   
   default:
      return OLE_S_USEREG;
   }

return E_OUTOFMEMORY;
}

/**************************************************************************

   CDataObject::DAdvise()

**************************************************************************/

STDMETHODIMP CDataObject::DAdvise(  LPFORMATETC pFE, 
                                    DWORD advf, 
                                    LPADVISESINK pAdvSink, 
                                    LPDWORD pdwConnection)
{
return E_NOTIMPL;
}

/**************************************************************************

   CDataObject::DUnadvise()

**************************************************************************/

STDMETHODIMP CDataObject::DUnadvise(DWORD dwConnection)
{
return E_NOTIMPL;
}

/**************************************************************************

   CDataObject::EnumDAdvise()

**************************************************************************/

STDMETHODIMP CDataObject::EnumDAdvise(LPENUMSTATDATA *ppenumAdvise)
{
return OLE_E_ADVISENOTSUPPORTED;
}

