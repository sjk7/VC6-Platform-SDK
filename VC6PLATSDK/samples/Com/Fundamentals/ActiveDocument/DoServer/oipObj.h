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

  File:          OIPObj.h
  
	Description:   COleInPlaceObject definitions.
	
**************************************************************************/

#ifndef OLEINPLACEOBJECT_H
#define OLEINPLACEOBJECT_H

/**************************************************************************
#include statements
**************************************************************************/

#include "DOServer.h"

/**************************************************************************

  CPersistStorage class definition
  
**************************************************************************/

class COleDocument;

class COleInPlaceObject : public IOleInPlaceObject
{
private:
	COleDocument   *m_pOleDoc;
	
public:
	COleInPlaceObject::COleInPlaceObject(COleDocument*);
	COleInPlaceObject::~COleInPlaceObject();
	
	//IUnknown methods
	STDMETHODIMP QueryInterface(REFIID, LPVOID*);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	
	//IOleInPlaceObject methods
	STDMETHODIMP InPlaceDeactivate();
	STDMETHODIMP UIDeactivate() ;
	STDMETHODIMP SetObjectRects(LPCRECT, LPCRECT);
	STDMETHODIMP GetWindow(HWND*) ;
	STDMETHODIMP ContextSensitiveHelp(BOOL);
	STDMETHODIMP ReactivateAndUndo();
};

#endif   //OLEINPLACEOBJECT_H
