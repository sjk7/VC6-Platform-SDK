//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved.
//
//  ColumnProvider.cpp
//
//      Implementation of the CColumnProvider class.
//
//////////////////////////////////////////////////////////////////////

#include "ShortName.h"
#include "ColumnProvider.h"
#include "Resource.h"

#define NUM_COLUMNS 2

#define STR_FMTID_ShortFilename TEXT("{706005E1-0888-11D3-B1C2-00600893AD51}")
GUID FMTID_ShortFilename = {0x706005E1, 0x0888, 0x11D3, {0xB1, 0xC2, 0x00, 0x60, 0x08, 0x93, 0xAD, 0x51}};

#define STR_FMTID_FullPath TEXT("{706005E2-0888-11D3-B1C2-00600893AD51}")
GUID FMTID_FullPath = {0x706005E2, 0x0888, 0x11D3, {0xB1, 0xC2, 0x00, 0x60, 0x08, 0x93, 0xAD, 0x51}};

SHCOLUMNINFO sci[NUM_COLUMNS] =
{
    {{0}, VT_BSTR, LVCFMT_LEFT, 30, SHCOLSTATE_TYPE_STR | SHCOLSTATE_SECONDARYUI, TEXT("Short Filename"), TEXT("Displays the 8.3 filename.")},
    {{0}, VT_BSTR, LVCFMT_LEFT, 30, SHCOLSTATE_TYPE_STR | SHCOLSTATE_SECONDARYUI, TEXT("Short Pathname"), TEXT("Displays the 8.3 pathname to the file or folder.")}
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColumnProvider::CColumnProvider()
{
    m_nRefCount = 0;
    nDllRefCount++;

    sci[0].scid.fmtid = FMTID_ShortFilename;
    sci[1].scid.fmtid = FMTID_FullPath;
}

CColumnProvider::~CColumnProvider()
{
    nDllRefCount--;
}


//////////////////////////////////////////////////////////////////////
//  IUnknown Methods
//////////////////////////////////////////////////////////////////////
STDMETHODIMP CColumnProvider::QueryInterface(REFIID riid, LPVOID *ppvObject)
{
    HRESULT hr = E_NOINTERFACE;

    *ppvObject = NULL;
    if (IsEqualIID (riid, IID_IUnknown) || IsEqualIID (riid, IID_IColumnProvider))
    {
        *ppvObject = (LPVOID)(LPCLASSFACTORY) this;
    }

    if (*ppvObject != NULL)
    {
        ((LPUNKNOWN)*ppvObject)->AddRef ();
        hr = S_OK;
    }
    return hr;
}

STDMETHODIMP_(ULONG) CColumnProvider::AddRef()
{
    m_nRefCount++;
    return m_nRefCount;
}

STDMETHODIMP_(ULONG) CColumnProvider::Release()
{
    if (--m_nRefCount == 0)
    {
        delete this;
        return 0;
    }
    return m_nRefCount;
}


//////////////////////////////////////////////////////////////////////
//  IColumnProvider Methods
//////////////////////////////////////////////////////////////////////
STDMETHODIMP CColumnProvider::Initialize (LPCSHCOLUMNINIT psci)
{
    //
    //  Perform any needed initialization here
    //
    return S_OK;
}

STDMETHODIMP CColumnProvider::GetColumnInfo (DWORD dwIndex, LPSHCOLUMNINFO psci)
{
    //
    //  Return information on each column we support. Return S_FALSE
    //  to indicate that we have returned information on all our 
    //  columns. GetColumnInfo will be called repeatedly until S_FALSE
    //  or an error is returned
    //
    if (dwIndex >= NUM_COLUMNS)
        return S_FALSE;

    psci->scid.fmtid = sci[dwIndex].scid.fmtid;
    psci->scid.pid = sci[dwIndex].scid.pid;

    psci->vt = sci[dwIndex].vt;

    psci->fmt = sci[dwIndex].fmt;

    psci->cChars = sci[dwIndex].cChars;

    psci->csFlags = sci[dwIndex].csFlags;

    lstrcpyn (psci->wszTitle, sci[dwIndex].wszTitle, ARRAYSIZE(psci->wszTitle));
    lstrcpyn (psci->wszDescription, sci[dwIndex].wszDescription, ARRAYSIZE(psci->wszDescription));
    return S_OK;
}


STDMETHODIMP CColumnProvider::GetItemData (LPCSHCOLUMNID pscid, LPCSHCOLUMNDATA pscd, VARIANT *pvartData)
{
  VARIANT varTemp;
  HRESULT hresult = S_FALSE;
    //
    //  The shell is asking for data for an item in one of our 
    //  columns. Verify that a correct format ID has been passed and
    //  return the proper information
    //
    WCHAR wszShortPath[MAX_PATH];

    //
    // Get the short path name for the file/folder
    //
    if (GetShortPathName (pscd->wszFile, wszShortPath, MAX_PATH)) {
      
      //
      // Is the text for the short filename column is being requested
      //
      if (IsEqualGUID (pscid->fmtid, FMTID_ShortFilename) && pscid->pid == 0)
	{
	  //
	  // Don't do anything for directories
	  //
	  if (!(pscd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
	    
	    varTemp.vt =  VT_BSTR;
	    varTemp.bstrVal = SysAllocString (PathFindFileName (wszShortPath));
	    if (varTemp.bstrVal) {
	      *pvartData = varTemp;
	      hresult = S_OK;
	    } else { 
	      hresult = E_OUTOFMEMORY;
	    }
	  }
	}
    }
    //
    // Is the text for the short pathname column is being requested
    //
    else if (IsEqualGUID (pscid->fmtid, FMTID_FullPath) && pscid->pid == 0)
    {
      varTemp.vt =  VT_BSTR;
      varTemp.bstrVal = SysAllocString (wszShortPath);
      if (varTemp.bstrVal) {
	*pvartData = varTemp;
	hresult = S_OK;
      } else { 
	hresult = E_OUTOFMEMORY;
      }
    }

    return hresult;
}
