// NewsEvent.h : Declaration of the CNewsEvent

#ifndef __NEWSEVENT_H_
#define __NEWSEVENT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNewsEvent
class ATL_NO_VTABLE CNewsEvent : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CNewsEvent, &CLSID_NewsEvent>
{
public:
	CNewsEvent()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_NEWSEVENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNewsEvent)
END_COM_MAP()

// INewsEvent
public:
};

#endif //__NEWSEVENT_H_
