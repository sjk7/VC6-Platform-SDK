/*+==========================================================================

File: FullServ.h

Summary:  Declaration of CFullServ and CAsyncFullServ

----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/

#ifndef __FULLSERV_H_
#define __FULLSERV_H_

#include "resource.h"       // main symbols

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:       CFullServ
  Summary:     Provides a synchronous implementation of ISample, and handles
			   calls to IFullServ asynchronously by creating call objects for
			   AsyncIFullServ
  Interfaces:  IFullServ
			   ISample
			   ICallFactory
  Aggregation: Supported
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/  
class ATL_NO_VTABLE CFullServ :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFullServ, &CLSID_FullServ>,
	public IFullServ,
	public ISample,
	public ICallFactory
{
public:
	CFullServ()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FULLSERV)
DECLARE_AGGREGATABLE(CFullServ)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFullServ)
	COM_INTERFACE_ENTRY(IFullServ)
	COM_INTERFACE_ENTRY(ISample)
	COM_INTERFACE_ENTRY(ICallFactory)
END_COM_MAP()

// IFullServ
public:
	//IFullServ
	STDMETHOD(Sum)(/*[in]*/ int i, /*[in]*/ int j, /*[out,retval]*/int * sum);
	//ICallFactory
	STDMETHOD(CreateCall)(REFIID riid1,IUnknown *pUnk,
						  REFIID riid2,IUnknown **ppObj);
	//ISample
	STDMETHOD(Work)(/*[in]*/ int i, /*[in]*/ int j, /*[out,retval]*/int * sum);

};

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:       CONotify
  Summary:     This class is the call object created by CFullServ::CreateCall
  Interfaces:  AsyncIFullServ - the asynchronous version of IFullServ
			   ISynchronize - A call object must implement ISynchronize. In
			   this case the call object auto aggregates CLSID_ManualResetEvent
  Aggregation: Supported
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/  
class CAsyncFullServ : public CComObjectRootEx<CComMultiThreadModel>,
					   public CComCoClass<CAsyncFullServ,&CLSID_AsyncFullServ>,
					   public AsyncIFullServ
{
public:
	CAsyncFullServ(){
		m_callInProgress = FALSE;
	}
	
	void Init(IFullServ * pIFullServ){
		m_pIFullServ = pIFullServ;//calls addref
	}

private:
	CComPtr<IFullServ> m_pIFullServ;//Pointer to sync interface
	BOOL m_callInProgress;
	int m_i,m_j,m_sum; // member vars used for Sum
	HRESULT m_hr; //used to store the HRESULT of Begin

public:
DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()
DECLARE_POLY_AGGREGATABLE(CAsyncFullServ)
BEGIN_COM_MAP(CAsyncFullServ)
	COM_INTERFACE_ENTRY(AsyncIFullServ)
	COM_INTERFACE_ENTRY_AUTOAGGREGATE(IID_ISynchronize,m_pAggISync.p,CLSID_ManualResetEvent)
END_COM_MAP()


	CComPtr<IUnknown> m_pAggISync;

	//AsyncIFullServ
	STDMETHOD(Begin_Sum)(int i, int j);
	STDMETHOD(Finish_Sum)(int* sum);

	//Called by worker thread
	STDMETHOD(doSum)();


};

#endif //__FULLSERV_H_
