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

  File:          OIPAObj.h
  
	Description:   COleInPlaceActiveObect definitions.
	
**************************************************************************/

#ifndef INPLACEACTIVEOBJECT_H
#define INPLACEACTIVEOBJECT_H

/**************************************************************************
#include statements
**************************************************************************/

#include "DOServer.h"

/**************************************************************************

  COleInPlaceActiveObject class definition
  
**************************************************************************/

class COleDocument;

class COleInPlaceActiveObject : public IOleInPlaceActiveObject
{
private:
	COleDocument   *m_pOleDoc;
	BOOL           m_fEnableModeless;
	
public:
	COleInPlaceActiveObject::COleInPlaceActiveObject(COleDocument*);
	COleInPlaceActiveObject::~COleInPlaceActiveObject();
	
	// IUnknown methods
	STDMETHODIMP QueryInterface(REFIID, LPVOID*);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	
	//IOleInPlaceActiveObject methods
	STDMETHODIMP OnDocWindowActivate(BOOL);
	STDMETHODIMP OnFrameWindowActivate(BOOL);
	STDMETHODIMP GetWindow(HWND*);
	STDMETHODIMP ContextSensitiveHelp(BOOL);
	STDMETHODIMP TranslateAccelerator(LPMSG);
	STDMETHODIMP ResizeBorder(LPCRECT, LPOLEINPLACEUIWINDOW, BOOL);
	STDMETHODIMP EnableModeless(BOOL);
	
};

#endif   //INPLACEACTIVEOBJECT_H
