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

/////////////////////////////////////////////////////////////////////////////////////////
// 
// CFWrap.cpp 
// 
// CClassFactoryWrapper implementation.  This is a class factory object that we register
// on behalf of the inproc object.  This way, creation of the object comes through this 
// object and we can do whatever is appropriate.  It needs to support IUknown, 
// IClassFactory and IMarshal.  If the client calls CoGetClassObject() for the inproc 
// object's CLSID, then our class factory object will be marshaled remotely to be 
// given to the client.  If the client is asking for something other than IClassFactory 
// from the class factory object, then we won't be able to support it and therefore will 
// have to defer to the real class factory object of the inproc server.  That's why, 
// when our class factory object is marshaled via IMarshal::MarshalInterface(), we 
// simply CoGetClassObject() for the inproc CLSID and marshal it using CLSID_StdMarhal.      
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "common.h"
#include "cfwrap.h"

CClassFactoryWrapper::CClassFactoryWrapper(REFCLSID rclsid) : m_cRef(0)
{
	m_clsid = rclsid;
}

CClassFactoryWrapper::~CClassFactoryWrapper() {}

// IUnknown

STDMETHODIMP CClassFactoryWrapper::QueryInterface(REFIID riid, void **ppv)
{
	*ppv = 0;
	if (riid == IID_IUnknown || riid == IID_IClassFactory)
		*ppv = (IClassFactory *) this;
	else if (riid == IID_IMarshal)
		*ppv = (IMarshal*) this;
	else 
		return E_NOINTERFACE;
	((IUnknown*) *ppv)->AddRef();
	return S_OK;
}

STDMETHODIMP_(ULONG) CClassFactoryWrapper::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) CClassFactoryWrapper::Release()
{
	ULONG result = InterlockedDecrement(&m_cRef);
	if (!result)
		delete this;
	return result;
}

// IClassFactory

// 
// IClassFactory::CreateInstance() - 
// 
// Create the inproc object directly and return it's interface pointer.
// 
STDMETHODIMP CClassFactoryWrapper::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void **ppv)
{
	OutputDebugString("Creating Inproc Object...");
	return CoCreateInstance(m_clsid, pUnkOuter, CLSCTX_INPROC_SERVER, riid, ppv);
}

//
// IClassFactory::LockServer()  
// 
STDMETHODIMP CClassFactoryWrapper::LockServer(BOOL fLock)
{
	return S_OK;
}

// IMarshal 

//
// IMarshal::GetUnmarshalClass() - 
//
// COM is marshaling the class factory wrapper object to the client. It needs the CLSID 
// of the object on the client side that will do the unmarshaling.  We return the standard
// marshaler since we use it to marshal in IMarshal::MarshalInterface().
//
STDMETHODIMP CClassFactoryWrapper::GetUnmarshalClass(REFIID riid, void *pv, DWORD dwDstCtx, 
													 void *pvDstCtx, DWORD flags, CLSID *pCid)
{
	OutputDebugString("IMarshal::GetUnmarshalClass() returning CLSID_StdMarshal.");
	*pCid = CLSID_StdMarshal;  
	return S_OK;
}

//
// IMarshal::GetMarshalSizeMax()
//
STDMETHODIMP CClassFactoryWrapper::GetMarshalSizeMax(REFIID riid, void *pv, DWORD dwDstCtx, 
													 void *pvDstCtx, DWORD flags, DWORD *pSize)
{
	return E_UNEXPECTED;
}

//
// IMarshal::MarshalInterface() - 
//
// As described in the module prolog, if we're being marshaled out of proc, we defer to 
// the actual inproc class factory.  We don't know what interface may be requested and 
// therefore give up control of creation. 
//
STDMETHODIMP CClassFactoryWrapper::MarshalInterface(IStream *pStm, REFIID riid, void *pv, 
													DWORD dwDstCtx, void *pvDstCtx, DWORD flags)
{
	// return a marshaled interface pointer to the inproc
	// object's class factory object. marshal into the stream pStm

	OutputDebugString("IMarshal::MarhsalInterface() called.");
	IUnknown *pUnk = 0;
	HRESULT hr = CoGetClassObject(m_clsid, CLSCTX_INPROC_SERVER, 0, IID_IUnknown,
									(LPVOID*) &pUnk);

	if (SUCCEEDED(hr))
	{
		// marshal the class factory object pUnk using the standard marshaler
		hr = CoMarshalInterface(pStm, riid, pUnk, dwDstCtx, pvDstCtx, flags);
		pUnk->Release();
	}
	return hr;
}

//
// IMarshal::UnmarshalInterface() 
//
STDMETHODIMP CClassFactoryWrapper::UnmarshalInterface(IStream *pStm, REFIID riid, void **ppv)
{
	return E_UNEXPECTED;
}

//
// IMarshal::ReleaseMarshalData() - 
//
//
// Release the stream we used to marshal the inproc object's class factory object.
//
STDMETHODIMP CClassFactoryWrapper::ReleaseMarshalData(IStream* pStm)
{
	OutputDebugString("IMarshal::ReleaseMarshalData() called.");
	return CoReleaseMarshalData(pStm);
}

//
// IMarshal::DisconnectObject() 
//
STDMETHODIMP CClassFactoryWrapper::DisconnectObject(DWORD dwReserved)
{
	return S_OK;
}





