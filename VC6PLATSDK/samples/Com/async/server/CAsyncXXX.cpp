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
#include "Debug.h"

/*
 *	This static member function instanciates the call object by way of a two part initialization.
 */
template<class T, class ISyncFace, class IAsyncFace>
LPUNKNOWN __stdcall CAsyncXXX<T, ISyncFace, IAsyncFace>::Create
							(LPUNKNOWN lpUnkCtrl, REFIID riid1, REFIID riid2, T *pT, ISyncFace *lpSyncface)
{
	DEBUGTRACE(_T("CAsyncXXX::Create()"));

	/* Create the uninitialized object. The reason for this two part creation mechanism is that there is no
	 * easy way to handle failures within a ctor. Therefore only the operations certain to succeed are done 
	 * within the ctor. The more complex initializations that could fail are done in the call to Init()
	 */
	CAsyncXXX<T, ISyncFace, IAsyncFace> *pAsync = new CAsyncXXX<T, ISyncFace, IAsyncFace>(lpUnkCtrl, riid1);

	if (!pAsync)
		return NULL;

	pAsync->NondelegatingAddRef();
	LPUNKNOWN lpUnk = NULL;
	HRESULT hr;
	if (SUCCEEDED(hr = pAsync->Init(pT, lpSyncface)))
	{
		hr = pAsync->NondelegatingQueryInterface(riid2, reinterpret_cast<PVOID*>(&lpUnk));
		
	}
	pAsync->NondelegatingRelease();
	
	if (FAILED(hr))
		DEBUGTRACE(_T("Error instanciating Call Object: HRESULT is %#X"), hr);

	return lpUnk;
}


#pragma warning(disable : 4355)
template<class T, class ISyncFace, class IAsyncFace>
CAsyncXXX<T, ISyncFace, IAsyncFace>::CAsyncXXX(LPUNKNOWN lpUnk, REFIID iid)
		:CUnknown(lpUnk,"CAsyncXXX"), CAsyncTest(this),
		m_lpSyncface(NULL), m_lpObj(NULL), m_iid(iid), m_lpUnkSync(NULL)
{
	DEBUGTRACE(_T("CAsyncXXX ctor"));
}


template<class T, class ISyncFace, class IAsyncFace>
CAsyncXXX<T, ISyncFace, IAsyncFace>::~CAsyncXXX() 
{
	DEBUGTRACE(_T("CAsyncXXX dtor"));
}


template<class T, class ISyncFace, class IAsyncFace>
long __stdcall CAsyncXXX<T, ISyncFace, IAsyncFace>::Init(const CFactoryData *pData)
{
	DEBUGTRACE(_T("This function should never be called"));
	DebugBreak();
	return 0;
}


template<class T, class ISyncFace, class IAsyncFace>
HRESULT __stdcall CAsyncXXX<T, ISyncFace, IAsyncFace>::Init(T *pT, ISyncFace *lpSyncface)
{
	DEBUGTRACE(_T("In CAsyncXXX::Init"));
	_ASSERT(pT);
	_ASSERT(lpSyncface);

	/*
	 *	The life type of class T is contained within the life time of ISyncFace
	 */
	 m_lpObj = pT;
	(m_lpSyncface = lpSyncface)->AddRef();


	/*
	 *	Note that the CLSID_ManualResetEvent object is aggreated by the call to GetOuterUnknown(). This is done so that 
	 *	both objects created in the same apartment or different apartments can be treated the same. 
	 *
	 *	The GetOuterUnknown() method will either return the controlling Unknown passed into ICallFactory::CreateCall() 
	 *	if aggregated or itself in the non-aggreated case. The client will either be using the ISynchronize interface returned
	 *	from the CoCreateInstance() method below in the typical inproc case or COM's implemenation of ISynchronize in 
	 *	the typical Local server case. In each case the call object must use the same ISynchronize 
	 *	implementation as the client does.
	 *
	 */
	HRESULT hr = CoCreateInstance(CLSID_ManualResetEvent, GetOuterUnknown(), CLSCTX_INPROC, IID_IUnknown, reinterpret_cast<PVOID*>(&m_lpUnkSync));
	_ASSERT(SUCCEEDED(hr) && m_lpUnkSync);

	return S_OK;
}


template<class T, class ISyncFace, class IAsyncFace>
HRESULT __stdcall CAsyncXXX<T, ISyncFace, IAsyncFace>::NondelegatingQueryInterface(REFIID iid, PVOID *ppv)
{
	CHECKPOINTER(ppv);
	
	if (iid == IID_IUnknown)
	{
		return FinishQI(reinterpret_cast<LPUNKNOWN>
		                   (static_cast<INondelegatingUnknown*>(this)), iid, ppv) ;
	}
	else if (iid == m_iid)
	{
		return FinishQI(static_cast<IAsyncFace*>(this), iid, ppv);
	}
	else if (iid == IID_ISynchronize)
	{
		return m_lpUnkSync->QueryInterface(IID_ISynchronize, ppv);
	}

	return CUnknown::NondelegatingQueryInterface(iid, ppv);
}



/*
 *	Reset(), Signal() and Wait() are helper functions that wrap either COM's implemenation of ISynchronize or 
 *	the CLSID_ManualResetEvent object. 
 */
template<class T, class ISyncFace, class IAsyncFace>
HRESULT __stdcall CAsyncXXX<T, ISyncFace, IAsyncFace>::Reset()
{
	LPSYNCHRONIZE   lpSync = NULL;
	HRESULT hr = QueryInterface(IID_ISynchronize, reinterpret_cast<PVOID*>(&lpSync));
	_ASSERT(SUCCEEDED(hr) && lpSync);
	hr = lpSync->Reset();
	RELEASEINTERFACE(lpSync);
	return S_OK;
}

template<class T, class ISyncFace, class IAsyncFace>
HRESULT __stdcall CAsyncXXX<T, ISyncFace, IAsyncFace>::Signal()
{
	LPSYNCHRONIZE   lpSync = NULL;
	HRESULT hr = QueryInterface(IID_ISynchronize, reinterpret_cast<PVOID*>(&lpSync));
	_ASSERT(SUCCEEDED(hr) && lpSync);
	hr = lpSync->Signal();
	_ASSERT(SUCCEEDED(hr));
	RELEASEINTERFACE(lpSync);
	return hr;
}


template<class T, class ISyncFace, class IAsyncFace>
HRESULT __stdcall CAsyncXXX<T, ISyncFace, IAsyncFace>::Wait(ULONG dwFlags, ULONG dwMilliseconds)
{
	LPSYNCHRONIZE   lpSync = NULL;
	HRESULT hr = QueryInterface(IID_ISynchronize, reinterpret_cast<PVOID*>(&lpSync));
	_ASSERT(SUCCEEDED(hr) && lpSync);
	hr = lpSync->Wait(dwFlags, dwMilliseconds);
	_ASSERT(SUCCEEDED(hr));
	RELEASEINTERFACE(lpSync);
	return hr;
}


template<class T, class ISyncFace, class IAsyncFace>
void __stdcall CAsyncXXX<T, ISyncFace, IAsyncFace>::FinalRelease()
{
	DEBUGTRACE(_T("CAsyncXXX::FinalRelease"));
	RELEASEINTERFACE(m_lpUnkSync);
	RELEASEINTERFACE(m_lpSyncface);
}
