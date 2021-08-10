#include "Notify.h"


//==========================================================================
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1997 - 2000 Microsoft Corporation.  All Rights Reserved.
//
//--------------------------------------------------------------------------
//
// AgentNotifySink
//
//		Boilerplate IDispatch implementation with stubs for all 
//		IAgentNotifySink methods except for RequestComplete.
//
//==========================================================================


extern long g_lDone;


// IUnknown methods

STDMETHODIMP AgentNotifySink::QueryInterface (REFIID riid, LPVOID *ppv) {

    *ppv = NULL;

    if ((riid == IID_IUnknown) || (riid == IID_IAgentNotifySink))
        *ppv = this;

    if (*ppv == NULL)
        return E_NOINTERFACE;

    ((LPUNKNOWN)*ppv)->AddRef();

    return NOERROR;
}


STDMETHODIMP_ (ULONG) AgentNotifySink::AddRef() {

	return ++m_cRefs;
}


STDMETHODIMP_(ULONG) AgentNotifySink::Release() {

	if (--m_cRefs != 0)
		return m_cRefs;

	delete this;
	return 0;
}


// IDispatch methods

STDMETHODIMP AgentNotifySink::GetTypeInfoCount(UINT *pctInfo) {

    *pctInfo = 1;
    return NOERROR;
}


STDMETHODIMP AgentNotifySink::GetTypeInfo(UINT itInfo, LCID lcid, ITypeInfo **ppTypeInfo) {

    HRESULT hRes;
    ITypeLib *pLib;

    *ppTypeInfo = NULL;

	if (itInfo != 0)
        return TYPE_E_ELEMENTNOTFOUND;

    if (ppTypeInfo == NULL)
        return E_POINTER;

	if ((PRIMARYLANGID(lcid) != LANG_NEUTRAL) && 
		(PRIMARYLANGID(lcid) != LANG_ENGLISH))
		return DISP_E_UNKNOWNLCID;

    hRes = LoadRegTypeLib(LIBID_AgentServerObjects, 
						  1, 
						  0,
						  PRIMARYLANGID(lcid), 
						  &pLib);
    if (FAILED(hRes))
        return hRes;

	hRes = pLib->GetTypeInfoOfGuid(IID_IAgentNotifySink, ppTypeInfo);
        
	pLib->Release();

    if (FAILED(hRes))
        return hRes;

    (*ppTypeInfo)->AddRef();

    return NOERROR;
}


STDMETHODIMP AgentNotifySink::GetIDsOfNames(REFIID riid, OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgDispID) {

    HRESULT hRes;
    ITypeInfo *pInfo;

	// REFIID must be NULL

	if (riid != IID_NULL)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

	// Get the TypeInfo for the specified lcid

    hRes = GetTypeInfo(0, lcid, &pInfo);

	if (FAILED(hRes))
		return hRes;

	// Use the TypeInfo to get the DISPIDs of the specified names.
	// That's the whole point here.  Let TypeInfo do the work so
	// we don't have to.

	hRes = pInfo->GetIDsOfNames(rgszNames, cNames, rgDispID);

	pInfo->Release();

    return hRes;
}


STDMETHODIMP AgentNotifySink::Invoke(DISPID dispID, REFIID riid, LCID lcid, 
									 unsigned short wFlags, DISPPARAMS *pDispParams, 
									 VARIANT *pVarResult, EXCEPINFO *pExcepInfo, 
									 UINT *puArgErr) {

	HRESULT hRes;
	ITypeInfo *pInfo;

    // The riid parameter is always supposed to be IID_NULL

	if (riid != IID_NULL)
        return DISP_E_UNKNOWNINTERFACE;

	// Get the type info for the specified lcid

    hRes = GetTypeInfo(0, lcid, &pInfo);

    if (FAILED(hRes))
        return hRes;

    // Clear exceptions

    SetErrorInfo(0L, NULL);

	hRes = pInfo->Invoke(this, 
						 dispID, 
						 wFlags, 
						 pDispParams, 
						 pVarResult, 
						 pExcepInfo, 
						 puArgErr);


    pInfo->Release();

    return hRes;
}


// IAgentNotifySink methods

STDMETHODIMP AgentNotifySink::Command(long dwCommandID, IUnknown * punkUserInput) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::ActivateInputState(long dwCharID, long bActivated) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::Restart() {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::Shutdown() {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::VisibleState(long dwCharID, long bVisible, long lCause) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::Click(long dwCharID, short fwKeys, long X, long Y) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::DblClick(long dwCharID, short fwKeys, long X, long Y) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::DragStart(long dwCharID, short fwKeys, long X, long Y) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::DragComplete(long dwCharID, short fwKeys, long X, long Y) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::RequestStart(long dwRequestID) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::RequestComplete(long dwRequestID, long hrStatus) {

	// When we get g_lDone exit the sample app

	if (dwRequestID == g_lDone)
		PostQuitMessage(0);

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::BookMark(long dwBookMarkID) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::Idle(long dwCharID, long bStart) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::Move(long dwCharID, long X, long Y, long lCause) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::Size(long dwCharID, long lWidth, long lHeight) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::BalloonVisibleState(long dwCharID, long bVisible) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::HelpComplete(long dwCharID, long dwCommandID, long dwCause) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::ListeningState(long dwCharacterID, long bListenState, long dwCause) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::DefaultCharacterChange(BSTR bszGUID) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::AgentPropertyChange() {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::ActiveClientChange(long dwCharID, long lStatus) {

	return NOERROR;
}
