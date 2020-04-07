// NewsEvent.cpp : Implementation of CNewsEvent
#include "stdafx.h"
#include "PersistATL.h"
#include "NewsEvent.h"

/////////////////////////////////////////////////////////////////////////////
// CNewsEvent

STDMETHODIMP CNewsEvent::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&__uuidof(INewsEvent)
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CNewsEvent::NewsFlash(DATE dtTimeStamp, BSTR Symbol, BSTR Headline, BSTR URL)
{
	TCHAR* tzText=0;
	USES_CONVERSION;

	tzText = W2T(Headline);
	MessageBox(NULL,tzText,_T("Inside the Subscriber"),MB_OK);
	return S_OK;
}

STDMETHODIMP CNewsEvent::ShortQuote(BSTR Symbol, double BidPrice, double AskPrice, DATE LastTradeTime, double LastTradePrice, double NetChange, double DailyHigh, double DailyLow)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CNewsEvent::LongQuote(BSTR Symbol, double BidPrice, double AskPrice, BSTR LastTradeTime, double LastTradePrice, double NetChange, double DailyHigh, double DailyLow, long AskSize, long BidSize, double OpenPrice, double ClosePrice, BSTR CloseDate)
{
	// TODO: Add your implementation code here

	return S_OK;
}
