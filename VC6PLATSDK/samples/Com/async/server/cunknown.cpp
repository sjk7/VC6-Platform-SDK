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
#include "CUnknown.h"
#include "CFactory.h"
#include "Debug.h"
///////////////////////////////////////////////////////////
//
// Static variables
//
long CUnknown::s_cActiveComponents = 0;	// Count of active objects



///////////////////////////////////////////////////////////
//
// Constructor
//
CUnknown::CUnknown(LPUNKNOWN pUnknownOuter, LPCSTR className)
: m_cRef(0), m_lpstrClass(className)
{
	DEBUGTRACE(_T("In CUnknown ctor"));
	// Set m_pUnknownOuter pointer.
	if (pUnknownOuter == NULL)
	{
		DEBUGTRACE(_T("Not aggregating; delegate to nondelegating IUnknown")) ;
		m_pUnknownOuter = reinterpret_cast<IUnknown*>
		                     (static_cast<INondelegatingUnknown*>
		                     (this)) ;  
	}
	else
	{
		DEBUGTRACE(_T("Aggregating; delegate to outer IUnknown")) ;
		m_pUnknownOuter = pUnknownOuter ;
	}

	// Increment count of active components.
	::InterlockedIncrement(&s_cActiveComponents) ;
}

//
// Destructor
//
CUnknown::~CUnknown()
{
	DEBUGTRACE(_T("In CUnknown dtor"));
	InterlockedDecrement(&s_cActiveComponents) ;
}

//
// FinalRelease - called by Release before it deletes the component
//
void CUnknown::FinalRelease()
{
	DEBUGTRACE(_T("Increment reference count for final release")) ;
	m_cRef = 1 ;
}

//
// Nondelegating IUnknown
//   - Override to handle custom interfaces.
//
HRESULT __stdcall 
	CUnknown::NondelegatingQueryInterface(const IID& iid, void** ppv)
{
	// CUnknown supports only IUnknown.
#if defined(_DEBUG)
	LPWSTR lpstrIID;
	StringFromIID(iid, &lpstrIID);
	DEBUGTRACE(_T("%s::QueryInterface has been asked for %S returning %s"), m_lpstrClass, lpstrIID,
		iid == IID_IUnknown ? "S_OK" : "E_NOINTERFACE");
	CoTaskMemFree(lpstrIID);
#endif

	CHECKPOINTER(ppv);

	if (iid == IID_IUnknown)
	{
		return FinishQI(reinterpret_cast<LPUNKNOWN>
		                   (static_cast<INondelegatingUnknown*>(this)), iid, ppv) ;
	}	
	else
	{
		*ppv = NULL ;
		return E_NOINTERFACE ;
	}
}

//
// AddRef
//
ULONG __stdcall CUnknown::NondelegatingAddRef()
{
	DEBUGTRACE(_T("In %s::NondelegatingAddRef refcounts = %i"), m_lpstrClass, m_cRef+1);
	return ::InterlockedIncrement(&m_cRef) ;
}

//
// Release
//
ULONG __stdcall CUnknown::NondelegatingRelease()
{
	_ASSERT(m_cRef > 0); // not thread safe
	DEBUGTRACE(_T("In %s::NondelegatingRelease refcounts = %i"), m_lpstrClass, m_cRef-1);
	if (InterlockedDecrement(&m_cRef) == 0)
	{
		FinalRelease() ;
		delete this ;
		return 0 ;
	}
	return m_cRef ;
}

//
// FinishQI
//   - Helper function to simplify overriding
//     NondelegatingQueryInterface
//
HRESULT _stdcall CUnknown::FinishQI(IUnknown* pI, REFIID iid, void** ppv) 
{
#if defined(_DEBUG)
	LPWSTR lpstrIID;
	StringFromIID(iid, &lpstrIID);
	DEBUGTRACE(_T("%s::QueryInterface has been asked for %S returning S_OK"), m_lpstrClass, lpstrIID);
	CoTaskMemFree(lpstrIID);
#endif

	*ppv = pI ;
	pI->AddRef() ;
	return S_OK ;
}


HRESULT _stdcall CUnknown::Quit()
{
	// clean up any outstanding interfaces including those which have been aggregated
	m_cRef = 1;
	CFactory::s_cServerLocks = 0;
	// the reason the count is 1 is to keep the proxy alive till the client has time to call CUnknown::Release()
	return S_OK;
}
