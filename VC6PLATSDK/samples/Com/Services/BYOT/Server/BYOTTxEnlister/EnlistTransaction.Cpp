// EnlistTransaction.cpp : Implementation of CEnlistTransaction
#include "stdafx.h"
#include "TxEnlister.h"
#include "EnlistTransaction.h"
#include <comsvcs.h>

/////////////////////////////////////////////////////////////////////////////
// CEnlistTransaction

STDMETHODIMP CEnlistTransaction::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IEnlistTransaction
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CEnlistTransaction::EnlistTransaction(BSTR bstrTipUrl)
{
	// TODO: Add your implementation code here

	if (!bstrTipUrl)
		return E_POINTER;

	m_bstrTipUrl = bstrTipUrl;

	return S_OK;
}

STDMETHODIMP CEnlistTransaction::CreateInstance(BSTR bstrProgId, IDispatch **ppDispatch)
{
   HRESULT						hr					= S_OK;
   ICreateWithTipTransactionEx*	pCreateWithTipTx	= NULL;
   GUID							guidObj				= {0};
   GUID							guidByotServer		= {0};
   MULTI_QI						mqi					= {0};	

   
 	// TODO: Add your implementation code here
 
 	if (NULL == bstrProgId || NULL == ppDispatch)
 		return E_POINTER;
 
 	hr = CLSIDFromProgID(bstrProgId, &guidObj);
 	if (FAILED(hr))
 		return hr;
 
 	hr = CLSIDFromProgID(L"Byot.ByotServerEx", &guidByotServer);
 	if (FAILED(hr))
 		return hr;
 
 	mqi.pIID	= &IID_ICreateWithTipTransactionEx;
 	mqi.pItf	= pCreateWithTipTx;
 	mqi.hr		= S_OK;
 
 	hr = CoCreateInstanceEx(guidByotServer,
 							NULL,
 							CLSCTX_INPROC_SERVER,
 							NULL, 
 							1, 
 							&mqi); 
 	if (FAILED(hr))
 		return hr;
 
 	if (FAILED(mqi.hr))
 		return hr;
 
	pCreateWithTipTx = (ICreateWithTipTransactionEx*)mqi.pItf;
 	hr = pCreateWithTipTx->CreateInstance(m_bstrTipUrl,
 									guidObj,
 									IID_IDispatch,
 									(void**)ppDispatch);
	pCreateWithTipTx->Release();
 
 	return hr;
}
