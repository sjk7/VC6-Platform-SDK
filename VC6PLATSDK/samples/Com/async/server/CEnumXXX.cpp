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

template<class T, class ELT_T, class IFACE>
CEnumXXX<T, ELT_T, IFACE>::CEnumXXX(LPUNKNOWN lpUnk, REFIID iid, DWORD nCount) 
		: m_lpunk(lpUnk), m_iid(iid), m_cRef(0), m_iCur(0), m_cELT(nCount), m_prgELT(NULL) 
{
	_ASSERT(m_lpunk);
}

template<class T, class ELT_T, class IFACE>
CEnumXXX<T, ELT_T, IFACE>::~CEnumXXX() 
{
	RELEASEINTERFACE(m_lpunk);	// Release the strong lock on the container interface add in the call to QI	
	delete [] m_prgELT;
}


template<class T, class ELT_T, class IFACE>
T* __stdcall CEnumXXX<T, ELT_T, IFACE>::Create(LPUNKNOWN lpUnk, DWORD nCount, ELT_T* elemlist)
{
	T* penum = new T(lpUnk, nCount);
	if ( penum && penum->Init(elemlist))
		return penum;
	else
	{
		delete penum;
		return NULL;
	}
}



template<class T, class ELT_T, class IFACE>
bool __stdcall CEnumXXX<T, ELT_T, IFACE>::Init(ELT_T *elemlist)
{
#if 0
	m_prgELT = new ELT_T[m_cELT];
	if (!m_prgELT)
		return false;

	for (DWORD i = 0; i < m_cELT; i++)
		m_prgELT[i] = elemlist[i];
#endif

/*
 * Note this can be a shallow copy since CEnumXXX maintains a refcount on the "owner"
 * of this class _and_ the "owner" agrees never to free the memory until it _itself_
 * is destroyed. A typical useage will be this
 * 
 * 	CEnumConnectionPoints *penum = CEnumConnectionPoints::Create(this, m_cCP, elemlist);
	HRESULT hr = penum->QueryInterface(IID_IEnumConnectionPoints, reinterpret_cast<PVOID*>(ppenum));
 *
 * Each time this class returns an interface via QueryInterface it will addref the "owners" 
 * lpUnk pointer. There by assuring that the memory passed in is valid for the life of this interface.
 */
	_ASSERT(elemlist);
	m_prgELT = elemlist;
	return true;
}


/* What I do is in the implementation of CEnumXXX::QueryInterface() AddRef the container. The container
 * passees in it's IUnknown as a constructor parameter. This will maintain a strong look on the container.
 * When the refcount drops to zero in CEnumXXX::Release() this will call CEnumXXX::FinalRelease()
 * which will then release the last strong lock on the container. If this is not done then I could orphan this
 * enumerator i.e.
 *
 * pDataObject->EnumFormatEtc(DATA_GET, &pEnumFmt);
 * pDataObject->Release();
 * 
 * pEnumFmt is now orphaned. Perhaps this is just plain a bug on the users part; I don't know but it does
 * follow the Fetch, Use, Release methodology of COM
 */
template<class T, class ELT_T, class IFACE>
HRESULT __stdcall CEnumXXX<T, ELT_T, IFACE>::QueryInterface(REFIID iid, PVOID *ppv)
{
#if defined(_DEBUG)
	LPWSTR lpstrIID;
	StringFromIID(iid, &lpstrIID);
	DEBUGTRACE(_TEXT("CEnumXXX::QueryInterface has been asked for %S"), lpstrIID);
	CoTaskMemFree(lpstrIID);
#endif

	CHECKPOINTER(ppv);
	
	if (iid == IID_IUnknown || iid == m_iid)
	{
		*ppv = reinterpret_cast<IFACE*>(this);
		static_cast<LPUNKNOWN>(*ppv)->AddRef();
		return S_OK;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
}

template<class T, class ELT_T, class IFACE>
ULONG __stdcall CEnumXXX<T, ELT_T, IFACE>::AddRef()
{
	DEBUGTRACE(_T("In CEnumXXX::AddRef refcounts = %i"), m_cRef+1);
/*
 * Need to AddRef the Container since it owns the list of elements to be enumerated
 */
	m_lpunk->AddRef();	// Add a strong lock on the container interface
	return InterlockedIncrement(reinterpret_cast<PLONG>(&m_cRef));
}


template<class T, class ELT_T, class IFACE>
ULONG __stdcall CEnumXXX<T, ELT_T, IFACE>::Release()
{
	_ASSERT(m_cRef > 0); // not thread safe
	DEBUGTRACE(_T("In CEnumXXX::Release refcounts = %i"), m_cRef-1);

	if (InterlockedDecrement(reinterpret_cast<PLONG>(&m_cRef)) == 0)
	{
		FinalRelease();
		delete this;
		return 0;
	}
	m_lpunk->Release();	// Release strong lock added in by the AddRef()
	return m_cRef;
}

template<class T, class ELT_T, class IFACE>
void __stdcall CEnumXXX<T, ELT_T, IFACE>::FinalRelease()
{
	DEBUGTRACE(_T("CEnumXXX::FinalRelease"));
}

template<class T, class ELT_T, class IFACE>
HRESULT __stdcall CEnumXXX<T, ELT_T, IFACE>::Next(ULONG celt, ELT_T* rgelt, PULONG pceltFetched)
{
	HRESULT hr;

	if (celt == 0 || (!pceltFetched && celt > 1))
		return E_INVALIDARG;

	CHECKPOINTER(rgelt);

	if (celt > m_cELT - m_iCur)
	{
		celt = m_cELT - m_iCur;
		celt == 0 ? (hr = E_FAIL) : (hr = S_FALSE);
	}
	else 
		hr = S_OK;

	DWORD i,j;
	T* pT = static_cast<T*>(this);

	for (j=0, i=m_iCur; j < celt; i++,j++)
	{
		CHECKPOINTER(&rgelt[j]);
		if (!pT->Copy(&rgelt[j], m_prgELT[i])) // the semantics of Copy are entirely determined by the object being enumerated
			return E_FAIL;
	}
	m_iCur = i;
	if (pceltFetched)
		*pceltFetched = j;

	return hr;
}

template<class T, class ELT_T, class IFACE>
HRESULT __stdcall CEnumXXX<T, ELT_T, IFACE>::Skip(ULONG celt)
{
	HRESULT hr;
	if (celt + m_iCur > m_cELT)
	{
		m_iCur = m_cELT;
		hr = S_FALSE;
	}
	else 
	{
		m_iCur += celt;
		hr = S_OK;
	}
	return hr;
}

template<class T, class ELT_T, class IFACE>
HRESULT __stdcall CEnumXXX<T, ELT_T, IFACE>::Reset(void)
{
	m_iCur = 0;
	return S_OK;
}

template<class T, class ELT_T, class IFACE>
HRESULT __stdcall CEnumXXX<T, ELT_T, IFACE>::Clone(IFACE **ppenum)
{
	CHECKPOINTER(ppenum);

	ELT_T* prgELT = new ELT_T[m_cELT];
	if (!prgELT)
		return E_OUTOFMEMORY;

	for (DWORD i = 0; i < m_cELT; i++)
		prgELT[i] = m_prgELT[i];

	T* penum = Create(m_lpunk, m_cELT, prgELT);
	return penum->QueryInterface(m_iid, reinterpret_cast<PVOID*>(ppenum));
}

