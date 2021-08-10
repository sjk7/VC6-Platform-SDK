// HelloWorld.h: Definition of the HelloWorld class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELLOWORLD_H__E1E3EDF9_48D1_11D2_B22B_0000F87A6B50__INCLUDED_)
#define AFX_HELLOWORLD_H__E1E3EDF9_48D1_11D2_B22B_0000F87A6B50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// HelloWorld

class HelloWorld : 
	public IDispatchImpl<IHelloWorld, &IID_IHelloWorld, &LIBID_ADSFIRSTEXTLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<HelloWorld,&CLSID_HelloWorld>
{
public:
	HelloWorld() {}
BEGIN_COM_MAP(HelloWorld)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IHelloWorld)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(HelloWorld) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_HelloWorld)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IHelloWorld
public:
	STDMETHOD(Say)();
};

#endif // !defined(AFX_HELLOWORLD_H__E1E3EDF9_48D1_11D2_B22B_0000F87A6B50__INCLUDED_)
