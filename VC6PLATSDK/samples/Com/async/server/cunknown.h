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
#if !defined(__CUnknown_h__)
#define __CUnknown_h__

#include <objidl.h>


///////////////////////////////////////////////////////////
//
// Macro's for setting DCOM security structures
//   
//

#define SETAUTHINFO(ai, athnsvc, athzsvc, name, athnl, impl, ident, cap) \
	{ \
	(ai).dwAuthnSvc=athnsvc; \
	(ai).dwAuthzSvc=athzsvc; \
	(ai).pwszServerPrincName=name; \
	(ai).dwAuthnLevel=athnl; \
	(ai).dwImpersonationLevel=impl; \
	(ai).pAuthIdentityData=ident; \
	(ai).dwCapabilities=cap; \
	}

#define SETDEFAUTHINFO(ai, athnl, impl) \
	SETAUTHINFO(ai, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, athnl, impl, NULL, RPC_C_QOS_CAPABILITIES_DEFAULT)


#define SETDEFSERVERINFO(psi, name) \
	{ \
	(psi)->dwReserved1=0; \
	(psi)->pwszName=name; \
	(psi)->pAuthInfo=reinterpret_cast<COAUTHINFO*>((psi)+1); \
	SETDEFAUTHINFO(*(psi)->pAuthInfo,RPC_C_AUTHN_LEVEL_CONNECT,RPC_C_IMP_LEVEL_IMPERSONATE); \
	(psi)->dwReserved2=0; \
	}
	
#define SETAUTHIDENTITY(aid, usr, pw, d) \
	{ \
	(aid).User=usr; \
	(aid).UserLength=lstrlenW(usr); \
	(aid).Domain=d; \
	(aid).DomainLength=d==NULL?0:lstrlenW(d); \
	(aid).Password=pw; \
	(aid).PasswordLength=pw==NULL?0:lstrlenW(pw); \
	(aid).Flags=SEC_WINNT_AUTH_IDENTITY_UNICODE; \
	}





///////////////////////////////////////////////////////////
//
// Nondelegating IUnknown interface
//   - Nondelegating version of IUnknown
//
interface INondelegatingUnknown
{
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface(const IID& iid, void** ppv) = 0;
	virtual ULONG   __stdcall NondelegatingAddRef() = 0;
	virtual ULONG   __stdcall NondelegatingRelease() = 0;
};


///////////////////////////////////////////////////////////
//
// Declaration of CUnknown 
//   - Base class for implementing IUnknown
//

struct CFactoryData;

class CUnknown : public INondelegatingUnknown
{

friend class CFactory;

protected:
	// Nondelegating IUnknown implementation
	virtual HRESULT __stdcall NondelegatingQueryInterface(const IID&,
	                                                      void**);
	virtual ULONG   __stdcall NondelegatingAddRef();
	virtual ULONG   __stdcall NondelegatingRelease();

	// Constructor
	CUnknown(IUnknown* pUnknownOuter, LPCSTR className = "CUnknown");

	// Destructor
	virtual ~CUnknown();

	// Initialization (especially for aggregates)
	virtual HRESULT __stdcall Init(const CFactoryData *pData) = 0;
	virtual HRESULT Init() {return S_OK;}

	// Notification to derived classes that we are releasing
	virtual void __stdcall FinalRelease();

	// Count of currently active components
	static DWORD ActiveComponents() 
		{ return s_cActiveComponents ;}
	
	// Helper function
	HRESULT _stdcall FinishQI(IUnknown* pI, REFIID iid, void** ppv);

public:
	LPUNKNOWN GetOuterUnknown() const
		{ return m_pUnknownOuter;}

protected:
	virtual HRESULT __stdcall Quit();

private:
	// Reference count for this object
	long m_cRef;
	
	// Pointer to (external) outer IUnknown
	IUnknown* m_pUnknownOuter;

	// Count of all active instances
	static long s_cActiveComponents;

	LPCSTR m_lpstrClass;
};


///////////////////////////////////////////////////////////
//
// Delegating IUnknown
//   - Delegates to the nondelegating IUnknown, or to the
//     outer IUnknown if the component is aggregated.
//
#define DECLARE_IUNKNOWN		                             \
	virtual HRESULT __stdcall	                             \
		QueryInterface(const IID& iid, void** ppv)           \
	{	                                                     \
		return GetOuterUnknown()->QueryInterface(iid,ppv) ;  \
	} ;	                                                     \
	virtual ULONG __stdcall AddRef()	                     \
	{	                                                     \
		return GetOuterUnknown()->AddRef() ;                 \
	} ;	                                                     \
	virtual ULONG __stdcall Release()	                     \
	{	                                                     \
		return GetOuterUnknown()->Release() ;                \
	} ;
#endif
