// ByotTransObj.cpp : Implementation of CByotTransObj
#include "stdafx.h"
#include <comsvcs.h>
#include "ByotTransaction.h"
#include "ByotTransObj.h"

//const GUID IID_ObjectContextTip = {92FD41CA,BAD9,11d2,9A2D,00C04F797BC9}

/////////////////////////////////////////////////////////////////////////////
// CByotTransObj

STDMETHODIMP CByotTransObj::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IByotTransaction
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CByotTransObj::BeginTransaction()
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CByotTransObj::CommitTransaction()
{
	// TODO: Add your implementation code here
	
  HRESULT				hr			= S_OK;
  IObjectContext*		pObjCtx		= NULL;

	// TODO: Add your implementation code here

	hr = GetObjectContext(&pObjCtx);
	if (FAILED(hr))
		return hr;
	
	hr = pObjCtx->SetComplete ();
	if (FAILED(hr))
		return hr;

	return hr;
}

STDMETHODIMP CByotTransObj::AbortTransaction()
{
  HRESULT				hr			= S_OK;
  IObjectContext*		pObjCtx		= NULL;

	// TODO: Add your implementation code here

	hr = GetObjectContext(&pObjCtx);
	if (FAILED(hr))
		return hr;
	
	hr = pObjCtx->SetAbort ();
	if (FAILED(hr))
		return hr;

	return hr;
}

STDMETHODIMP CByotTransObj::get_TipURL(BSTR *pVal)
{
  HRESULT				hr			= S_OK;
  IObjectContext*		pObjCtx		= NULL;
  IObjectContextTip*	pObjCtxTip	= NULL;
  BSTR					bstrTipURL	= NULL;
  
	// TODO: Add your implementation code here
	if (!pVal)
		return E_POINTER;

	hr = GetObjectContext(&pObjCtx);
	if (FAILED(hr))
		goto ErrorExit;

	hr = pObjCtx->QueryInterface (IID_IObjectContextTip, (void**)&pObjCtxTip);
	if (FAILED(hr))
		goto ErrorExit;
	
	hr = pObjCtxTip->GetTipUrl(&bstrTipURL);
	if (FAILED(hr))
		goto ErrorExit;

ErrorExit:

	*pVal = bstrTipURL;

	if (pObjCtxTip)
		pObjCtxTip->Release();
	if (pObjCtx)
		pObjCtx->Release ();
	
	return hr;
}
