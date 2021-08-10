// IADsError.h: Definition of the ADsError class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IADSERROR_H__417D01E1_F1C6_11D2_BC88_00C04FD430AF__INCLUDED_)
#define AFX_IADSERROR_H__417D01E1_F1C6_11D2_BC88_00C04FD430AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// ADsError

class ADsError : 
	public IDispatchImpl<IADsError, &IID_IADsError, &LIBID_ADSERRORLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<ADsError,&CLSID_ADsError>
{
public:
	ADsError() {}
BEGIN_COM_MAP(ADsError)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IADsError)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(ADsError) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_ADsError)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IADsError
public:
	STDMETHOD(GetErrorMessage)(/*[in]*/ long hResult, /*[out,retval]*/ BSTR *pbMsg);
};

#endif // !defined(AFX_IADSERROR_H__417D01E1_F1C6_11D2_BC88_00C04FD430AF__INCLUDED_)
