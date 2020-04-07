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

  File:          OIPAObj.cpp
  
	Description:   COleInPlaceActiveObject implementation.
	
**************************************************************************/

/**************************************************************************
#include statements
**************************************************************************/

#include "OIPAObj.h"

/**************************************************************************

  COleInPlaceActiveObject::COleInPlaceActiveObject()
  
**************************************************************************/

COleInPlaceActiveObject::COleInPlaceActiveObject(COleDocument *pOleDoc)
{
	OutputDebugString(TEXT("COleInPlaceActiveObject's constructor\n"));
	
	m_pOleDoc = pOleDoc;
	
	m_fEnableModeless = FALSE;
}

/**************************************************************************

  COleInPlaceActiveObject::~COleInPlaceActiveObject()
  
**************************************************************************/

COleInPlaceActiveObject::~COleInPlaceActiveObject()
{
	OutputDebugString(TEXT("COleInPlaceActiveObject's destructor\n"));
}

/**************************************************************************

  COleInPlaceActiveObject::QueryInterface()
  
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
	OutputDebugString(TEXT("COleInPlaceActiveObject::QueryInterface\n"));
	
	return m_pOleDoc->QueryInterface(riid, ppReturn);
}

/**************************************************************************

  COleInPlaceActiveObject::AddRef()
  
**************************************************************************/

STDMETHODIMP_(ULONG) COleInPlaceActiveObject::AddRef()
{
	OutputDebugString(TEXT("COleInPlaceActiveObject::AddRef\n"));
	
	return m_pOleDoc->AddRef();
}

/**************************************************************************

  COleInPlaceActiveObject::Release()
  
**************************************************************************/

STDMETHODIMP_(ULONG) COleInPlaceActiveObject::Release()
{
	OutputDebugString(TEXT("COleInPlaceActiveObject::Release\n"));
	
	return m_pOleDoc->Release();
}

/**************************************************************************

  COleInPlaceActiveObject::OnDocWindowActivate()
  
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::OnDocWindowActivate(BOOL fActivate)
{
	OutputDebugString(TEXT("COleInPlaceActiveObject::OnDocWindowActivate\n"));
	
	//If we are getting activated, merge our menus.
	if(fActivate)
	{
		if(m_pOleDoc->m_pOleDocView)
		{
			m_pOleDoc->m_pOleDocView->MergeMenus();
		}
	}
	
	return S_OK;
}

/**************************************************************************

  COleInPlaceActiveObject::OnFrameWindowActivate()
  
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::OnFrameWindowActivate(BOOL fActivate)
{
	UNREFERENCED_PARAMETER(fActivate);
	OutputDebugString(TEXT("COleInPlaceActiveObject::OnFrameWindowActivate\n"));
	
	return S_OK;
}

/**************************************************************************

  COleInPlaceActiveObject::GetWindow()
  
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::GetWindow(HWND *phwnd)
{
	OutputDebugString(TEXT("COleInPlaceActiveObject::GetWindow\n"));
	
	return m_pOleDoc->GetWindow(phwnd);
}

/**************************************************************************

  COleInPlaceActiveObject::ContextSensitiveHelp()
  
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::ContextSensitiveHelp(BOOL fEnterMode)
{
	UNREFERENCED_PARAMETER(fEnterMode);
	OutputDebugString(TEXT("COleInPlaceActiveObject::ContextSensitiveHelp\n"));
	
	return E_NOTIMPL;
}

/**************************************************************************

  COleInPlaceActiveObject::TranslateAccelerator()
  
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::TranslateAccelerator(LPMSG lpmsg)
{
	UNREFERENCED_PARAMETER(lpmsg);
	OutputDebugString(TEXT("COleInPlaceActiveObject::TranslateAccelerator\n"));
	
	// no accelerator table, return FALSE
	return S_FALSE;
}

/**************************************************************************

  COleInPlaceActiveObject::ResizeBorder()
  
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::ResizeBorder(   LPCRECT lprectBorder,
												   LPOLEINPLACEUIWINDOW lpUIWindow,
												   BOOL fFrameWindow)
{
	UNREFERENCED_PARAMETER(lprectBorder);
	UNREFERENCED_PARAMETER(lpUIWindow);
	UNREFERENCED_PARAMETER(fFrameWindow);
	OutputDebugString(TEXT("COleInPlaceActiveObject::ResizeBorder\n"));
	
	return S_OK;
}

/**************************************************************************

  COleInPlaceActiveObject::EnableModeless()
  
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::EnableModeless(BOOL fEnable)
{
	OutputDebugString(TEXT("COleInPlaceActiveObject::EnableModeless\n"));
	
	m_fEnableModeless = fEnable;
	
	return S_OK;
}
