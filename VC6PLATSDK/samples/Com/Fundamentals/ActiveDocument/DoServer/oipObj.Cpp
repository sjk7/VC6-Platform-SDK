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

  File:          OIPObj.cpp
  
	Description:   COleInPlaceObject implementation.
	
**************************************************************************/

/**************************************************************************
#include statements
**************************************************************************/

#include "OIPObj.h"

/**************************************************************************
global variables
**************************************************************************/

/**************************************************************************

  COleInPlaceObject::COleInPlaceObject()
  
**************************************************************************/

COleInPlaceObject::COleInPlaceObject(COleDocument *pOleDoc)
{
	OutputDebugString(TEXT("COleInPlaceObject's constructor\n"));
	
	m_pOleDoc = pOleDoc;
}

/**************************************************************************

  COleInPlaceObject::~COleInPlaceObject()
  
**************************************************************************/

COleInPlaceObject::~COleInPlaceObject() 
{
	OutputDebugString(TEXT("COleInPlaceObject's destructor\n"));
}

/**************************************************************************

  COleInPlaceObject::QueryInterface()
  
**************************************************************************/

STDMETHODIMP COleInPlaceObject::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
	OutputDebugString(TEXT("COleInPlaceObject::QueryInterface\n"));
	
	return m_pOleDoc->QueryInterface(riid, ppReturn);
}

/**************************************************************************

  COleInPlaceObject::AddRef()
  
**************************************************************************/

STDMETHODIMP_(ULONG) COleInPlaceObject::AddRef()
{
	OutputDebugString(TEXT("COleInPlaceObject::AddRef\n"));
	
	return m_pOleDoc->AddRef();
}

/**************************************************************************

  COleInPlaceObject::Release()
  
**************************************************************************/

STDMETHODIMP_(ULONG) COleInPlaceObject::Release()
{
	OutputDebugString(TEXT("COleInPlaceObject::Release\n"));
	
	return m_pOleDoc->Release();
}

/**************************************************************************

  COleInPlaceObject::InPlaceDeactivate()
  
**************************************************************************/

STDMETHODIMP COleInPlaceObject::InPlaceDeactivate()
{
	OutputDebugString(TEXT("COleInPlaceObject::InPlaceDeactivate\n"));
	
	return m_pOleDoc->DeactivateInPlace();
}

/**************************************************************************

  COleInPlaceObject::UIDeactivate()
  
**************************************************************************/

STDMETHODIMP COleInPlaceObject::UIDeactivate()
{
	OutputDebugString(TEXT("COleInPlaceObject::UIDeactivate\n"));
	
	return m_pOleDoc->DeactivateUI();
}

/**************************************************************************

  COleInPlaceObject::SetObjectRects()
  
**************************************************************************/

STDMETHODIMP COleInPlaceObject::SetObjectRects(LPCRECT lprcPosRect, LPCRECT lprcClipRect)
{
	UNREFERENCED_PARAMETER(lprcPosRect);
	UNREFERENCED_PARAMETER(lprcClipRect);
	OutputDebugString(TEXT("COleInPlaceObject::SetObjectRects\n"));
	
	return S_OK;
}

/**************************************************************************

  COleInPlaceObject::GetWindow()
  
**************************************************************************/

STDMETHODIMP COleInPlaceObject::GetWindow(HWND *phwnd)
{
	OutputDebugString(TEXT("COleInPlaceObject::GetWindow\n"));
	
	return m_pOleDoc->GetWindow(phwnd);
}

/**************************************************************************

  COleInPlaceObject::ContextSensitiveHelp()
  
**************************************************************************/

STDMETHODIMP COleInPlaceObject::ContextSensitiveHelp(BOOL fEnterMode)
{
	UNREFERENCED_PARAMETER(fEnterMode);
	OutputDebugString(TEXT("COleInPlaceObject::ContextSensitiveHelp\n"));
	
	return E_NOTIMPL;
}

/**************************************************************************

  COleInPlaceObject::ReactivateAndUndo()
  
**************************************************************************/

STDMETHODIMP COleInPlaceObject::ReactivateAndUndo()
{
	OutputDebugString(TEXT("COleInPlaceObject::ReactivateAndUndo\n"));
	
	return INPLACE_E_NOTUNDOABLE;
}

