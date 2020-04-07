// NewsEvent.h : Declaration of the CNewsEvent

#ifndef __NEWSEVENT_H_
#define __NEWSEVENT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNewsEvent
class ATL_NO_VTABLE CNewsEvent : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CNewsEvent, &__uuidof(NewsEvent)>,
	public ISupportErrorInfo,
	public IDispatchImpl<INewsEvent, &__uuidof(INewsEvent), &LIBID_PERSISTATLLib>
{
public:
	CNewsEvent()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_NEWSEVENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNewsEvent)
	COM_INTERFACE_ENTRY(INewsEvent)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// INewsEvent
public:
	STDMETHOD(LongQuote)( /*[in]*/ BSTR Symbol, /*[in]*/ double BidPrice, /*[in]*/ double AskPrice,/*[in]*/ BSTR LastTradeTime, /*[in]*/ double LastTradePrice, /*[in]*/ double NetChange, /*[in]*/ double DailyHigh, /*[in]*/ double DailyLow,/*[in]*/ long AskSize, /*[in]*/ long BidSize, /*[in]*/ double OpenPrice, /*[in]*/ double ClosePrice, /*[in]*/ BSTR CloseDate );
	STDMETHOD(ShortQuote)( /*[in]*/ BSTR Symbol, /*[in]*/ double BidPrice, /*[in]*/ double AskPrice, /*[in]*/ DATE LastTradeTime, /*[in]*/ double LastTradePrice, /*[in]*/ double NetChange, /*[in]*/ double DailyHigh, /*[in]*/ double DailyLow );
	STDMETHOD(NewsFlash)(/*[in]*/ DATE dtTimeStamp, /*[in]*/ BSTR Symbol, /*[in]*/ BSTR Headline,/*[in]*/ BSTR URL );
};

#endif //__NEWSEVENT_H_
