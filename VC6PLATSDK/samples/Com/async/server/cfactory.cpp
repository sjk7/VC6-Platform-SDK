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
#include <objbase.h>

#include "Registry.h"
#include "CFactory.h"
#include "Debug.h"


///////////////////////////////////////////////////////////
//
// Static variables
//
long CFactory::s_cServerLocks = 0;    // Count of locks

#if 1 // defined(_DLL_SERVER_)		
extern DWORD g_dwTLS;
// extern HMODULE g_hModule;
#endif

extern CFactoryData g_FactoryDataArray[];
extern int g_cFactoryDataEntries;
extern CLSID g_clsid;
extern LPOLESTR g_progID;
extern HANDLE g_CloseEvent;
extern HMODULE g_hModule;


//
// Forward defines
//

///////////////////////////////////////////////////////////
//
// CFactory implementation
//
CFactory::CFactory(const CFactoryData* pFactoryData)
: m_cRef(0), m_pFactoryData(pFactoryData)
{
	DEBUGTRACE(_T("In CFactory ctor"));
	_ASSERT(m_pFactoryData);
	g_clsid = *m_pFactoryData->m_pCLSID;
	g_progID = m_pFactoryData->m_szProgID;
}


CFactory::~CFactory()
{
	DEBUGTRACE(_T("In CFactory dtor")); 
}

//
// IUnknown implementation
//
HRESULT __stdcall CFactory::QueryInterface(REFIID iid, void** ppv)
{ 	
#if defined(_DEBUG)
	LPWSTR lpstrIID;
	StringFromIID(iid, &lpstrIID);
	DEBUGTRACE(_TEXT("IClassFactory::QueryInterface has been asked for %S"), lpstrIID);
	CoTaskMemFree(lpstrIID);
#endif
	CHECKPOINTER(ppv);

	if ((iid == IID_IUnknown) || (iid == IID_IClassFactory))
	{
		*ppv = this;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	static_cast<LPUNKNOWN>(*ppv)->AddRef();
	return S_OK;
}

ULONG __stdcall CFactory::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

ULONG __stdcall CFactory::Release()
{
	if (InterlockedDecrement(&m_cRef) == 0)
	{
		delete this;
		return 0;
	}
	return m_cRef;
}

//
// IClassFactory implementation
//
HRESULT __stdcall CFactory::CreateInstance(IUnknown* pUnknownOuter,
                                           const IID& iid,
                                           void** ppv)
{
	DEBUGTRACE(_T("In IClassFactory::CreateInstance"));
	HRESULT hr;
	CHECKPOINTER(ppv);

	// Aggregate only if the requested IID is IID_IUnknown.
	if ((pUnknownOuter != NULL) && (iid != IID_IUnknown))
	{
		hr = CLASS_E_NOAGGREGATION;
		goto END;
	}

	_ASSERT(m_pFactoryData->version == MAKEVERSION(1, 0));

	// Create the component.
	CUnknown* pNewComponent;
	hr = m_pFactoryData->CreateInstance(pUnknownOuter, &pNewComponent);
	                                            
	if (FAILED(hr))
	{
		goto END;
	}

	// Initialize the component.
	pNewComponent->NondelegatingAddRef();
	hr = pNewComponent->Init(m_pFactoryData);
	if (SUCCEEDED(hr))
	{
		// Get the requested interface.
		hr = pNewComponent->NondelegatingQueryInterface(iid, ppv);
	}
	pNewComponent->NondelegatingRelease();
END:
	DEBUGTRACE(_T("IClassFactory::CreateInstance returning [%X]"), hr);
	return hr ;
}


// LockServer
HRESULT __stdcall CFactory::LockServer(BOOL bLock)
{
	DEBUGTRACE(_T("IClassFactory::LockServer called with bLock = [%s]"), bLock ? "TRUE" : "FALSE");
	if (bLock) 
	{
		InterlockedIncrement(&s_cServerLocks);
#if !defined(_DLL_SERVER_)		
		CoAddRefServerProcess();
#endif // _DLL_SERVER_
	}
	else
	{
		InterlockedDecrement(&s_cServerLocks);
#if !defined(_DLL_SERVER_)		
		if (CoReleaseServerProcess() == 0) // Last reference to server time to cleanup and exit
#if defined(_APARTMENT_)
			PostQuitMessage(0);
#else	// Free Threaded
			SetEvent(g_CloseEvent); 
#endif // _APARTMENT_
#endif // _DLL_SERVER_
	}
	return S_OK;
}

//
// Register all components.
//
HRESULT CFactory::RegisterAll()
{
	HRESULT hr;
	for(int i = 0 ; i < g_cFactoryDataEntries ; i++)
		if (FAILED(hr = RegisterServer(g_hModule, g_FactoryDataArray[i])))
			break;
	return hr;
}

HRESULT CFactory::UnregisterAll()
{
	HRESULT hr;
	for(int i = 0 ; i < g_cFactoryDataEntries ; i++)
		if (FAILED(hr = UnregisterServer(g_hModule, g_FactoryDataArray[i])))
			break;
	return hr;
}

#if defined(_DLL_SERVER_)
#error("_DLL_SERVER_ defined")
///////////////////////////////////////////////////////////
//
// GetClassObject
//   - Create a class factory based on a CLSID.
//
HRESULT CFactory::GetClassObject(const CLSID& clsid,
                                 const IID& iid,
                                 void** ppv)
{
	DEBUGTRACE(_T("In CFactory::GetClassObject"));
	HRESULT hr;
	CHECKPOINTER(ppv);

	if ((iid != IID_IUnknown) && (iid != IID_IClassFactory))
	{
		hr = E_NOINTERFACE ;
		goto END;
	}

	// Traverse the array of data looking for this class ID.
	int i;
	for (i = 0; i < g_cFactoryDataEntries; i++)
	{
		const CFactoryData* pData = &g_FactoryDataArray[i] ;
		if (pData->IsClassID(clsid))
		{
			// Found the ClassID in the array of components we can
			// create.  So create a class factory for this component.
			// Pass the CFactoryData structure to the class factory
			// so that it knows what kind of components to create.
			*ppv = (IUnknown*) new CFactory(pData) ;
			if (*ppv == NULL)
			{
				hr = E_OUTOFMEMORY ;
				goto END;
			}
			return NOERROR ;
		}
	}
	hr = CLASS_E_CLASSNOTAVAILABLE ;
END:
	DEBUGTRACE(_T("CFactory::GetClassObject returning [%X]"), hr);
	return hr;
}


//
// Determine if the component can be unloaded.
//
HRESULT CFactory::CanUnloadNow()
{
	if (CUnknown::ActiveComponents() || IsLocked())
	{
		DEBUGTRACE(_T("CFactory::CanUnloadNow returning S_FALSE"));
		return S_FALSE ;
	}
	else
	{
		DEBUGTRACE(_T("CFactory::CanUnloadNow returning S_OK"));
		return S_OK ;
	}
}

//////////////////////////////////////////////////////////
//
// Exported functions
//

STDAPI DllCanUnloadNow()
{
	return CFactory::CanUnloadNow() ;
}

//
// Get class factory
//
STDAPI DllGetClassObject(const CLSID& clsid,
                         const IID& iid,
                         void** ppv)
{
	return CFactory::GetClassObject(clsid, iid, ppv) ;
}

//
// Server registration
//
STDAPI DllRegisterServer()
{

	return CFactory::RegisterAll() ;
}


STDAPI DllUnregisterServer()
{
	return CFactory::UnregisterAll() ;
}

///////////////////////////////////////////////////////////
//
// DLL module information
//
BOOL APIENTRY DllMain(HANDLE hModule, 
                      DWORD dwReason, 
                      void* lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		g_dwTLS = TlsAlloc();
		g_hModule = hModule ;
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		TlsFree(g_dwTLS);
	return TRUE ;
}
#endif // _DLL_SERVER_
