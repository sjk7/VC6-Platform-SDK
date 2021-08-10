// HelloWorld.cpp : Implementation of CADsFirstExtApp and DLL registration.

#include "stdafx.h"
#include "ADsFirstExt.h"
#include "HelloWorld.h"


/////////////////////////////////////////////////////////////////////////////
//

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

STDMETHODIMP HelloWorld::Say()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	IADs *pADs;
	HRESULT hr;
	BSTR    bstr;
	TCHAR  szText[256];



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
