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

/**************************************************************************

  File:          OleObj.h
  
	Description:   COleObject definitions.
	
**************************************************************************/

#ifndef OLEOBJECT_H
#define OLEOBJECT_H

/**************************************************************************
#include statements
**************************************************************************/

#include "DOServer.h"

/**************************************************************************

  COleObject class definition
  
**************************************************************************/

class COleDocument;

class COleObject : public IOleObject
{
private:
	COleDocument   *m_pOleDoc;
	BOOL           m_fOpen;
	
public:
	COleObject::COleObject(COleDocument *pOleDoc);
	COleObject::~COleObject();
	
	//IUnknown methods
	STDMETHODIMP QueryInterface(REFIID, LPVOID*);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	
	//IOleObject methods
	STDMETHODIMP SetClientSite(LPOLECLIENTSITE);
	STDMETHODIMP Advise(LPADVISESINK, LPDWORD);
	STDMETHODIMP SetHostNames(LPCOLESTR, LPCOLESTR);
	STDMETHODIMP DoVerb(LONG, LPMSG, LPOLECLIENTSITE, LONG, HWND, LPCRECT);
	STDMETHODIMP GetExtent(DWORD, LPSIZEL);
	STDMETHODIMP Update();
	STDMETHODIMP Close(DWORD);
	STDMETHODIMP Unadvise(DWORD);
	STDMETHODIMP EnumVerbs(LPENUMOLEVERB*);
	STDMETHODIMP GetClientSite(LPOLECLIENTSITE*);
	STDMETHODIMP SetMoniker(DWORD, LPMONIKER);
	STDMETHODIMP GetMoniker(DWORD, DWORD, LPMONIKER*);
	STDMETHODIMP InitFromData(LPDATAOBJECT, BOOL, DWORD);
	STDMETHODIMP GetClipboardData(DWORD, LPDATAOBJECT*);
	STDMETHODIMP IsUpToDate();
	STDMETHODIMP GetUserClassID(CLSID*);
	STDMETHODIMP GetUserType(DWORD, LPOLESTR*);
	STDMETHODIMP SetExtent(DWORD, LPSIZEL);
	STDMETHODIMP EnumAdvise(LPENUMSTATDATA*);
	STDMETHODIMP GetMiscStatus(DWORD, LPDWORD);
	STDMETHODIMP SetColorScheme(LPLOGPALETTE);
	
};

#endif   //OLEOBJECT_H
