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

/******************************************************************************

  File:          OleDoc.h
  
	Description:   COleDocumentView definitions.
	
******************************************************************************/

#ifndef OLEDOC_H
#define OLEDOC_H

#include "DOServer.h"

/**************************************************************************

  COleDocument class definition
  
**************************************************************************/

class COleDocumentView;
class COleObject;
class CDataObject;
class COleInPlaceObject;
class COleInPlaceActiveObject;
class CPersistStorage;
class CPersistFile;

class COleDocument : public IOleDocument
{
	friend class COleDocumentView;
	friend class COleObject;
	friend class CDataObject;
	friend class COleInPlaceObject;
	friend class COleInPlaceActiveObject;
	friend class CPersistStorage;
	
private:
	COLORREF                m_Color;
	DWORD                   m_dwRegister;
	LPOLECLIENTSITE         m_pOleClientSite;
	DWORD                   m_ObjRefCount;
	BOOL                    m_fDirty;
	BOOL                    m_fNoScribbleMode;
	LPOLEADVISEHOLDER       m_pOleAdviseHolder;
	BOOL                    m_fCreated;
	
	COleDocumentView        *m_pOleDocView;
	COleObject              *m_pOleObject;
	CDataObject             *m_pDataObject;
	COleInPlaceObject       *m_pOleInPlaceObject;
	COleInPlaceActiveObject *m_pOleInPlaceActiveObject;
	CPersistStorage         *m_pPersistStorage;
	CPersistFile            *m_pPersistFile;
	
public:
	COleDocument();
	~COleDocument();
	
	//IUnknown methods
	STDMETHODIMP QueryInterface(REFIID, LPVOID*);
	STDMETHODIMP_(DWORD) AddRef();
	STDMETHODIMP_(DWORD) Release();
	
	//IOleDocument methods
	STDMETHODIMP CreateView(IOleInPlaceSite*, IStream*, DWORD, IOleDocumentView**);
	STDMETHODIMP GetDocMiscStatus(DWORD*);
	STDMETHODIMP EnumViews(IEnumOleDocumentViews**, IOleDocumentView**);
	
	//public utility methods
	BOOL RegisterServer(void);
	BOOL CreateFile(HWND);
	BOOL CreateFile(LPTSTR);
	
private:
	STDMETHODIMP GetWindow(HWND*);
	STDMETHODIMP DeactivateUI();
	STDMETHODIMP DeactivateInPlace();
	
	friend BOOL CALLBACK ColorHookProc(HWND, UINT, WPARAM, LPARAM);
};

#endif   //OLEDOC_H
