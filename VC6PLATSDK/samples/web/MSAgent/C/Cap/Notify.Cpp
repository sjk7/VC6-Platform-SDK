/*	
	Copyright (c) 1998 - 2000 by Microsoft Corporation

	THE INFORMATION AND CODE PROVIDED HEREUNDER (COLLECTIVELY REFERRED TO
	AS "SOFTWARE") IS PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. IN
	NO EVENT SHALL MICROSOFT CORPORATION OR ITS SUPPLIERS BE LIABLE FOR
	ANY DAMAGES WHATSOEVER INCLUDING DIRECT, INDIRECT, INCIDENTAL,
	CONSEQUENTIAL, LOSS OF BUSINESS PROFITS OR SPECIAL DAMAGES, EVEN IF
	MICROSOFT CORPORATION OR ITS SUPPLIERS HAVE BEEN ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGES. SOME STATES DO NOT ALLOW THE EXCLUSION OR
	LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES SO THE
	FOREGOING LIMITATION MAY NOT APPLY.

	This software may be copied and distributed royalty-free subject to
	the following conditions:

	1. You must copy all software without modification and must include
	   all pages, if the software is distributed without inclusion in your
	   software product. If you are incorporating the software in
	   conjunction with and as a part of your software product which adds
	   substantial value, you may modify and include portions of the
	   software.

	2. You must place all copyright notices and other protective
	   disclaimers and notices contained on the software on all copies of
	   the software and your software product.

	3. Unless the software is incorporated in your software product which
	   adds substantial value, you may not distribute this software for
	   profit.

	4. You may not use Microsoft's name, logo, or trademarks to market
	   your software product.

	5. You agree to indemnify, hold harmless, and defend Microsoft and its
	   suppliers from and against any claims or lawsuits, including
	   attorneys' fees, that arise or result from the use or distribution
	   of your software product and any modifications to the software.		
*/


#include "stdafx.h"
#include "Notify.h"
#include "MainDlg.h"


// IUnknown methods

STDMETHODIMP AgentNotifySink::QueryInterface (REFIID riid, LPVOID *ppv) {

    *ppv = NULL;

    if ((riid == IID_IUnknown) || (riid == IID_IAgentNotifySink) ||
		(riid == IID_IAgentNotifySinkEx))
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


// IDispatch methods (Boilerplate implementation)

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

	hRes = pLib->GetTypeInfoOfGuid(IID_IAgentNotifySinkEx, ppTypeInfo);
        
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


// IAgentNotifySinkEx methods

STDMETHODIMP AgentNotifySink::Command(long dwCommandID, IUnknown * punkUserInput) {

	_ASSERT(m_pMainDlg);

	m_pMainDlg->OnCharacterCommand(dwCommandID);

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


STDMETHODIMP AgentNotifySink::Click(long dwCharID, short fwKeys, long x, long y) {

	_ASSERT(m_pMainDlg);

	if (fwKeys & MK_RBUTTON)
		m_pMainDlg->OnCharacterRightClick(x, y);

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::DblClick(long dwCharID, short fwKeys, long x, long y) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::DragStart(long dwCharID, short fwKeys, long x, long y) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::DragComplete(long dwCharID, short fwKeys, long x, long y) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::RequestStart(long dwRequestID) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::RequestComplete(long dwRequestID, long hrStatus) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::BookMark(long dwBookMarkID) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::Idle(long dwCharID, long bStart) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::Move(long dwCharID, long x, long y, long lCause) {

	_ASSERT(m_pMainDlg);

	m_pMainDlg->OnCharacterMove(x, y);

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


STDMETHODIMP AgentNotifySink::ListeningState(long dwCharID, long bListening, long dwCause) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::DefaultCharacterChange(BSTR bszGUID) {

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::AgentPropertyChange() {

	_ASSERT(m_pMainDlg);

	m_pMainDlg->OnPropertyChange();

	return NOERROR;
}


STDMETHODIMP AgentNotifySink::ActiveClientChange(long dwCharID, long bActive) {

	return NOERROR;
}

