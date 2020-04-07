/*+==========================================================================

File: CallBackClient.h

Summary:  Declaration of CCallBack

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

#ifndef __CALLBACKCLIENT_H_
#define __CALLBACKCLIENT_H_

#include "FullSvr_i.c"

HRESULT WINAPI QueryFunc(void*,REFIID,LPVOID*,DWORD_PTR); //forward decl

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:       CCallBack
  Summary:     this COM object cannot be created externally, and is used only
			   to recieve a call back on completion of a non-blocking method
			   call
  Interfaces:  ISynchronize
  Aggregation: Supported
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/  
class ATL_NO_VTABLE CCallBack : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISynchronize
{
public:
	CCallBack()
	{
		m_pCallObjUnk = NULL;
	}

	HRESULT FinalConstruct(){
		//Create contained sync object
		return CoCreateInstance(CLSID_ManualResetEvent,NULL,CLSCTX_INPROC_SERVER,IID_ISynchronize,(void**)&smartPtrISynchronize.p);
	}

	HRESULT FinalRelease(){
		//Release the call object
		if(m_pCallObjUnk) m_pCallObjUnk->Release();
		return S_OK;
	}

DECLARE_GET_CONTROLLING_UNKNOWN();

DECLARE_AGGREGATABLE(CCallBack);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCallBack)
	COM_INTERFACE_ENTRY(ISynchronize)
	COM_INTERFACE_ENTRY_FUNC_BLIND(0, QueryFunc )//Pass QI to QueryFunc
END_COM_MAP()

private:
	CComPtr<ISynchronize> smartPtrISynchronize;//contained synch object
	IUnknown * m_pCallObjUnk;//Call objects IUnknown

	STDMETHOD(CallBack)();

public:

	STDMETHOD(StartCall)(int i, int j);
	STDMETHOD(MyQuery)(REFIID riid,LPVOID* ppv);

//ISynchronize
	STDMETHOD(Signal)();
	STDMETHOD(Reset)();
	STDMETHOD(Wait)(DWORD flags,DWORD timeout);


};

#endif // __CALLBACKCLIENT_H