// VCSecuritySampleClass.h : Declaration of the CVCSecuritySampleClass

#ifndef __VCSECURITYSAMPLECLASS_H_
#define __VCSECURITYSAMPLECLASS_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVCSecuritySampleClass
class ATL_NO_VTABLE CVCSecuritySampleClass : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVCSecuritySampleClass, &CLSID_VCSecuritySampleClass>,
	public IDispatchImpl<IVCSecuritySampleClass, &IID_IVCSecuritySampleClass, &LIBID_VCSECURITYSAMPLELib>
{
public:
	CVCSecuritySampleClass()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VCSECURITYSAMPLECLASS)

BEGIN_COM_MAP(CVCSecuritySampleClass)
	COM_INTERFACE_ENTRY(IVCSecuritySampleClass)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IVCSecuritySampleClass
public:
	STDMETHOD(WhoAmI)(/*[out, retval]*/ BSTR*);
	STDMETHOD(AmIAnAdministrator)(/*[out, retval]*/ short*);
};

#endif //__VCSECURITYSAMPLECLASS_H_
