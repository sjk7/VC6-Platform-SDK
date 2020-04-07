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
#ifndef __CFactory_h__
#define __CFactory_h__

#include "CUnknown.h"
///////////////////////////////////////////////////////////
//
//  Component creation function
//
class CUnknown;

typedef HRESULT (_stdcall *FPCREATEINSTANCE)(IUnknown*, CUnknown**);

typedef enum {INPROC, CONTROL, LOCAL, REMOTE} SERVERTYPE;

#define MAKEVERSION(M, m) ((DWORD)(WORD)(m) | (DWORD)(WORD)(M) << 16) // M=Major, m=minor

///////////////////////////////////////////////////////////
//
// CFactoryData
//   - Information CFactory needs to create a component
//     supported by the DLL
//
struct CFactoryData
{
	
	DWORD version;

	// InProc, Local, Control
	SERVERTYPE server;

	// Threading model
	LPCSTR threadingModel;

	// The class ID for the component
	const CLSID* m_pCLSID;

	// Pointer to the function that creates it
	FPCREATEINSTANCE CreateInstance;

	// Name of the component to register in the registry
	LPCSTR m_RegistryName;

	// ProgID
	LPOLESTR m_szProgID;

	// Version-independent ProgID
	LPOLESTR m_szVerIndProgID;

	// Short User type
	LPCSTR m_szname;
	
	// Appliction name
	LPCSTR m_szAppName;

	// Helper function for finding the class ID
	BOOL IsClassID(const CLSID& clsid) const
		{ return (*m_pCLSID == clsid) ;}

	// GUID of the typelib
	const GUID* m_pLIBID;
	
	// Locale ID for typelib
	LCID  m_lcid;

	// Version of typelib
	DWORD m_LibVersion;

	// Flag set to TRUE if the server has a custom proxy
	bool m_fProxy;

	// Verbs recognized by IOleObject::DoVerb
	LPCSTR m_oleVerbs;

	// OLEMISC flags specific to this object
	DWORD	m_oleMisc;
};


///////////////////////////////////////////////////////////
//
// Class Factory
//
class CFactory : public IClassFactory
{
private:
	// IUnknown
	virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv);
	virtual ULONG   __stdcall AddRef();
	virtual ULONG   __stdcall Release();
	
	// IClassFactory
	virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter,
	                                         const IID& iid,
	                                         void** ppv);
	virtual HRESULT __stdcall LockServer(BOOL bLock); 

	CFactory() {};

#if defined(_DLL_SERVER_)	
	// Function to determine if component can be unloaded
	friend HRESULT __stdcall DllCanUnloadNow();
	friend HRESULT __stdcall DllGetClassObject(const CLSID& clsid,
											const IID& iid,
											void** ppv);

	static HRESULT CanUnloadNow();

	// Helper function to DllGetClassObject();
	static HRESULT GetClassObject(const CLSID& clsid,
	                              const IID& iid, 
	                              void** ppv);
#endif

public:
	// Constructor - Pass pointer to data of component to create.
	CFactory(const CFactoryData* pFactoryData);

	// Destructor
	~CFactory();

	// Functions to [un]register all components
	static HRESULT RegisterAll();

	static HRESULT UnregisterAll();

private:
	// state variables

	// Reference Count
	long m_cRef;

	friend HRESULT _stdcall CUnknown::Quit();

	static long s_cServerLocks;

public:
	//
	// Static FactoryData support functions
	//
	static BOOL IsLocked()
	{ return (CFactory::s_cServerLocks > 0);}

	
	static DWORD lockCount() 
	{ return CFactory::s_cServerLocks;}

protected:
	// Pointer to information about class this factory creates
	const CFactoryData* m_pFactoryData;
};
#endif // __CFactory_h__
