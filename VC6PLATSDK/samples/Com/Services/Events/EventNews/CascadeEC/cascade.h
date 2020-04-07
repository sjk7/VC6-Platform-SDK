// Cascade.h : Declaration of the CCascade

#ifndef __CASCADE_H_
#define __CASCADE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCascade
class ATL_NO_VTABLE CCascade : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCascade, &CLSID_CascadeEC>
{
public:
	CCascade()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CASCADE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCascade)
END_COM_MAP()

// ICascade
public:
};

#endif //__CASCADE_H_
