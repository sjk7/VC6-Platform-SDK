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

#if !defined(__CAsyncXXX__)
#define __CAsyncXXX__

#include "CUnknown.h"


typedef ISynchronize *LPSYNCHRONIZE;
typedef ICallFactory *LPCALLFACTORY;



/*
 *	This is a general purpose helper class for Asynchronous interfaces. This class encapsulates all of
 *	the boiler plate code such as ICallFactory::CreateCall(), ISynchronize. 
 *	
 *	What you need to provide is the implemenation of the Asynchronous interface.
 *
 *  The following is an explaination of the template parameters.
 *
 *	1) The class which encapsulates the call object:		class T
 *	2) The class which supports the synchronous interface:  class ISyncFace
 *	3) The class which supports the asynchronous interface	class IAsyncFace
 *
 */
template<class T, class ISyncFace, class IAsyncFace>
class CAsyncXXX : public CUnknown,
				  public IAsyncFace,
				  public ISynchronize
{
	friend class IAsyncFace;
private:
	ISyncFace*		m_lpSyncface;	// Back pointer to asychronous interface
	T*				m_lpObj;		// Back pointer to class
	REFIID			m_iid;			// IID of asynchronous interface
	LPUNKNOWN	    m_lpUnkSync;	// IUnknown of the corresponding synchronous interface

	CAsyncXXX() :CUnknown(NULL,"CAsyncXXX"), m_iid(CLSID_NULL) {};

	CAsyncXXX(LPUNKNOWN lpUnk, REFIID iid);

	virtual	HRESULT __stdcall Init(const CFactoryData *pData);
	virtual HRESULT __stdcall Init(T *pT, ISyncFace *lpSyncface);

public:

	/*	This class can only be instanciated by way of the below Create() method. The reason for this is there are
	 *	are a number of items that need to be wired up in order for this to be initialized correctly. By restricting
	 *	the instanciation to a static method call I can insure this to always be setup correctly.
	 *
	 *	Within the call to ICallFactory::CreateCall(REFIID riid1, LPUNKNOWN pUnkCtrl, REFIID riid2, LPUNKNOWN *ppv)
	 *	you need to supply the following
	 *
	 *	1) Controlling IUnknown; COM _always_ aggreates the call object if the object and container are not within the
	 *	same apartment. The caller still is free to pass it's own controlling unknown if it wish special handling such
	 *	as using it's own implemenation of ISynchronize
	 *
	 *	2) IID of the Asynchronous interface
	 *
	 *	3) IID to return interface to return
	 *
	 *	4) Pointer to the instance of T. Currently this is not used however the intention is that some call objects may
	 *	need to use some of the functionality of the class which has encapsulated it
	 *
	 *	5) Pointer to the synchronize interface. The reason for this is that some methods may be able to finish quickly.
	 *	In this case you would want to handle the call synchronously; delegating to the synchronise interface allows you
	 *	to do so easily.
	 *
	 *	Below is an example of how to instanciate a call object.
	 *
	 *
	 *	*ppv = CAsyncXXX<CServer, ITest, CAsyncTest>::Create(pUnkCtrl, riid1, riid2, this, this);
	 *
	 *
	 */
	static LPUNKNOWN __stdcall Create(LPUNKNOWN lpUnkCtrl,		// Controlling Unknown
									REFIID riid1,				// IID of the asynchronous interface
									REFIID riid2,				// IID of the requested interface
									T *pT,						// Instance pointer of the containing class
									ISyncFace *lpSyncface);		// Instance pointer of the synchronous interface
	
	virtual ~CAsyncXXX();

	// Declare the delegating IUnknown.
	#pragma warning(disable : 4355)
	DECLARE_IUNKNOWN

	// IUnknown
	HRESULT __stdcall 
		NondelegatingQueryInterface(const IID& iid, void** ppv);
	
	// Notification to derived classes that we are releasing
	void __stdcall FinalRelease();

	// Helper functions that IAsyncFace will use to talk to ISynchronize. These methods encapsulate the common 
	// scenario where one QI's the call object for ISynchronize, calls one of it's methods and releases the interface
	HRESULT __stdcall Reset();
	HRESULT __stdcall Signal();
	HRESULT __stdcall Wait(ULONG dwFlags, ULONG dwMilliseconds);

	__inline ISyncFace* GetISync() {return m_lpSyncface;}


};


#include "CAsyncXXX.cpp"
#endif //__CAsyncXXX__
