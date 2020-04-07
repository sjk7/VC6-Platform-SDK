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

///////////////////////////////////////////////////////////////////////////////////
// 
// CSur.cpp 
// 
// CSurrogate implementation.   
//
//////////////////////////////////////////////////////////////////////////////////
#include "common.h"
#include "csur.h"

// IUnknown

//
// IUknown::QueryInterface() - 
//
// ISurrogate and IUknown are all the surrogate object supports.  
//
STDMETHODIMP CSurrogate::QueryInterface(REFIID riid, void **ppv)
{
	*ppv = 0;
	if (riid == IID_IUnknown || riid == IID_ISurrogate)
		*ppv = (ISurrogate *) this;
	else 
		return E_NOINTERFACE;
	((IUnknown*) *ppv)->AddRef();
	return S_OK;
}

//
//	IUnknown::AddRef() - 
//
//  We've allocated this object on the stack in 
//	WinMain().  Therefore we don't have a real lifetime for it
// 
STDMETHODIMP_(ULONG) CSurrogate::AddRef()
{
	return 2;  
}

//
//	IUnknown::Release() -
//
//  We've allocated this object on the stack in 
//	WinMain().  Therefore we don't have a real lifetime for it so 
//	we won't delete it here.
//
STDMETHODIMP_(ULONG) CSurrogate::Release()
{
	return 1;  
}


// ISurrogate 

//
// ISurrogate::LoadDllServer() - 
//
// LoadDllServer() is called when a new object is being created. 
// Create the wrapper class factory object and register it.  Keep track of it in our 
// stack object.  
// 
STDMETHODIMP CSurrogate::LoadDllServer(REFCLSID rclsid)
{
	OutputDebugString("ISurrogate::LoadDllServer() called.");
	// instantiate a new class factory wrapper object
	CClassFactoryWrapper * pcfw = new CClassFactoryWrapper(rclsid);

	if (!pcfw) return E_OUTOFMEMORY;

	// register this new class factory wrapper (use REGCLS_SURROGATE)
	pcfw->AddRef();
	HRESULT hr = CoRegisterClassObject(rclsid, (IClassFactory*)pcfw,
										CLSCTX_LOCAL_SERVER, REGCLS_SURROGATE, 
										&pcfw->m_dwReg);

	// push this one into our stack
	if (SUCCEEDED(hr)) 
		m_stkClassFactories.push(pcfw);
	else 
		pcfw->Release();
	return hr;
}

//
// ISurrogate::FreeSurrogate() - 
//
// We don't need to "revoke" the surrogate object.  We do need to revoke the class 
// factory objects we've created and this is called by COM to allow us to do that.  
// It's also a chance to quit the application since we're not needed any more.
//
STDMETHODIMP CSurrogate::FreeSurrogate()
{
	OutputDebugString("ISurrogate::FreeSurrogate() called.");
	// revoke all of our class factory wrapper objects from COM
	size_t i = m_stkClassFactories.size();
	while (i--)
	{
		CoRevokeClassObject(m_stkClassFactories.top()->m_dwReg);
		m_stkClassFactories.top()->Release();
		m_stkClassFactories.pop();
	}

	// terminate the message pump
	PostQuitMessage(0);
	return S_OK;
}


