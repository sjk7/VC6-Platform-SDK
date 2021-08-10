// HelloWorld.cpp : Implementation of CADsFirstExtApp and DLL registration.

#include "stdafx.h"
#include "ADsFirstExt.h"
#include "HelloWorld.h"


/////////////////////////////////////////////////////////////////////////////
// Constructor/Destructor
/////////////////////////////////////////////////////////////////////////////
HelloWorld::HelloWorld()
{
	HRESULT hr;
	ITypeLib   *pITypeLib;
	m_pTypeInfo = NULL;
	hr = LoadRegTypeLib( LIBID_ADSFIRSTEXTLib, 
                              1, 
                              0, 
                              PRIMARYLANGID(GetSystemDefaultLCID()), 
                              &pITypeLib );
	if ( SUCCEEDED(hr) )
	{

		hr   = pITypeLib->GetTypeInfoOfGuid( IID_IHelloWorld, &m_pTypeInfo);
	}

	pITypeLib->Release();
	   
}

HelloWorld::~HelloWorld()
{
	if ( m_pTypeInfo )
	{
		m_pTypeInfo->Release();
	}
	
}


/////////////////////////////////////////////////////////////////////////////
// InterfaceSupportsErrorInfo
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP HelloWorld::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IHelloWorld,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}



//////////////////////////////////////////////////// 
// Delegating IDispatch Methods to the aggregator
//////////////////////////////////////////////////////
STDMETHODIMP HelloWorld::GetTypeInfoCount(UINT* pctinfo)
{
   IDispatch *pDisp;
   HRESULT    hr;
   hr = OuterQueryInterface( IID_IDispatch, (void**) &pDisp );
   if ( SUCCEEDED(hr) )
   {
	   hr = pDisp->GetTypeInfoCount( pctinfo );
	   pDisp->Release();
   }   
   return hr;
}


STDMETHODIMP HelloWorld::GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
{
   IDispatch *pDisp;
   HRESULT    hr;
   hr = OuterQueryInterface( IID_IDispatch, (void**) &pDisp );
   if ( SUCCEEDED(hr) )
   {
	   hr = pDisp->GetTypeInfo( itinfo, lcid, pptinfo );
	   pDisp->Release();
   }
   
   return hr;
}

STDMETHODIMP HelloWorld::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		LCID lcid, DISPID* rgdispid)
{
   IDispatch *pDisp;
   HRESULT    hr;
   hr = OuterQueryInterface( IID_IDispatch, (void**) &pDisp );
   if ( SUCCEEDED(hr) )
   {
	   hr = pDisp->GetIDsOfNames( riid, rgszNames, cNames, lcid, rgdispid);
	   pDisp->Release();
   }
   
   return hr;
 
}

STDMETHODIMP HelloWorld::Invoke(DISPID dispidMember, REFIID riid,
		LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,
		EXCEPINFO* pexcepinfo, UINT* puArgErr)
{
   IDispatch *pDisp;
   HRESULT    hr;
   hr = OuterQueryInterface( IID_IDispatch, (void**) &pDisp );
   if ( SUCCEEDED(hr) )
   {
	   hr = pDisp->Invoke( dispidMember, riid, lcid, wFlags, pdispparams, pvarResult,
		                   pexcepinfo, puArgErr);
	   pDisp->Release();
   }
   
   return hr;
}

///////////////////////////////////////////////////////////////////////////////
// End delegating IDispatch Methods
///////////////////////////////////////////////////////////////////////////////



STDMETHODIMP HelloWorld::Say()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	IADs *pADs;
	HRESULT hr;
	BSTR    bstr;
	TCHAR  szText[128];



	hr = OuterQueryInterface(IID_IADs, (void **) &pADs );
	if ( !SUCCEEDED(hr) )
	{
		return hr;
	}

	hr = pADs->get_Name(&bstr);
	if ( !SUCCEEDED(hr) )
	{
		pADs->Release();
		return hr;
	}


		////////////////////////////////////////
	// Check for buffer overrun.
	UINT nMaxLen = sizeof(szText)/sizeof(TCHAR);
	UINT nLength = SysStringLen(bstr);
	TCHAR  szHelloFmt[] = _T("Hello %S");
	UINT fmtLen = sizeof(szHelloFmt)/sizeof(TCHAR);

	if ( nMaxLen <= (nLength+fmtLen) )
	{
		_tcscpy(szText,_T("Your string is too long"));

	}
	else
	{
		wsprintf(szText, _T("Hello %S"), bstr );
	}


	SysFreeString(bstr);


	::MessageBox(NULL, szText, _T("From ADSI Extension"), MB_OK);
	pADs->Release();

	return S_OK;
}
