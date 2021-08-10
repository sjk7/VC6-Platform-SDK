// HelloWorld.h: Definition of the HelloWorld class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELLOWORLD_H__E1E3EDF9_48D1_11D2_B22B_0000F87A6B50__INCLUDED_)
#define AFX_HELLOWORLD_H__E1E3EDF9_48D1_11D2_B22B_0000F87A6B50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols
//#import "c:\winnt\system32\activeds.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

/////////////////////////////////////////////////////////////////////////////
// HelloWorld

class HelloWorld : 
	//public IDispatchImpl<IHelloWorld, &IID_IHelloWorld, &LIBID_ADSFIRSTEXTLib>, 
    public IHelloWorld,
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<HelloWorld,&CLSID_HelloWorld>,
	public IADsExtension
{
protected:
	ITypeInfo   *m_pTypeInfo;

public:
	HelloWorld();
	~HelloWorld();

BEGIN_COM_MAP(HelloWorld)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IHelloWorld)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IADsExtension)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(HelloWorld) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_HelloWorld)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	// IDispatch
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo); 
	STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo** pptinfo);
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		LCID lcid, DISPID* rgdispid);
	STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid,
		LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,
		EXCEPINFO* pexcepinfo, UINT* puArgErr);

// IHelloWorld
public:

	STDMETHOD(Say)();
// IADsExtension
	STDMETHOD(Operate)(ULONG dwCode, VARIANT varData1, VARIANT varData2, VARIANT varData3)
	{
		HRESULT hr = S_OK;

		switch (dwCode) 
		{

			case ADS_EXT_INITCREDENTIALS:
				  // For debugging purpose you can prompt a dialog box
				  // MessageBox(NULL, "INITCRED", "ADsExt", MB_OK);
				  break;
 
			default:
				  hr = E_FAIL;
				  break;

		}        

        return hr;
		
	}

	
	STDMETHOD(PrivateGetIDsOfNames)(REFIID riid, OLECHAR ** rgszNames, unsigned int cNames, LCID lcid, DISPID  * rgdispid)
	{
		
	  if (rgdispid == NULL)
	  {
			return E_POINTER;
	  }
	
		return  DispGetIDsOfNames(m_pTypeInfo, rgszNames, cNames, rgdispid);
	}

 

	STDMETHOD(PrivateInvoke)(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS * pdispparams, VARIANT * pvarResult, EXCEPINFO * pexcepinfo, UINT * puArgErr)
	{
			 return DispInvoke( (IHelloWorld*)this, 
				m_pTypeInfo,
				dispidMember, 
				wFlags, 
				pdispparams, 
				pvarResult, 
				pexcepinfo, 
				puArgErr );
	}
};

#endif // !defined(AFX_HELLOWORLD_H__E1E3EDF9_48D1_11D2_B22B_0000F87A6B50__INCLUDED_)
