// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include <comsvcs.h>
#include "ComSpyCtl.h"
#include "ComSpyAudit.h"
#include "CCOMSpy.h"
#include "SysLCESub.h"
#include "ResourceSub.h"


/////////////////////////////////////////////////////////////////////////////
// CResourceSub

STDMETHODIMP CResourceSub::OnResourceCreate(
    COMSVCSEVENTINFO * pInfo, 
	ULONG64 ObjectID,
    LPCOLESTR pszType,
    ULONG64 resId,
	BOOL enlisted)
{
	m_pSpy -> AddEventToList(pInfo->perfCount, _TEXT("OnResourceCreate"), GuidToBstr(pInfo->guidApp));
	m_pSpy -> AddParamValueToList(L"Type", pszType);

	WCHAR szObjectID[32];
	wsprintfW(szObjectID, L"0x%016X", ObjectID);
	m_pSpy -> AddParamValueToList(L"ObjectID", szObjectID);

	WCHAR szResID[32];
	wsprintfW(szResID, L"0x%016X", resId);
	m_pSpy -> AddParamValueToList(L"ResourceID", szResID);

	WCHAR szEnlisted[10];
	if (enlisted)
		wsprintfW(szEnlisted, L"TRUE");
	else
		wsprintfW(szEnlisted, L"FALSE");
	m_pSpy -> AddParamValueToList(L"Enlisted", szEnlisted);
		
	IF_AUDIT_DO(OnResourceCreate)(pInfo->perfCount,GuidToBstr(pInfo->guidApp), szObjectID, pszType, szResID,enlisted);

	return S_OK;
}


STDMETHODIMP CResourceSub::OnResourceAllocate(
	COMSVCSEVENTINFO * pInfo, 
	ULONG64 ObjectID,
    LPCOLESTR pszType,
    ULONG64 resId,
	BOOL enlisted,
	DWORD NumRated,
	DWORD Rating)
{
	
	m_pSpy -> AddEventToList(pInfo->perfCount, _TEXT("OnResourceAllocate"),GuidToBstr(pInfo->guidApp));
	m_pSpy -> AddParamValueToList(L"Type", pszType);

	WCHAR szObjectID[32];
	wsprintfW(szObjectID, L"0x%016X", ObjectID);
	m_pSpy -> AddParamValueToList(L"ObjectID", szObjectID);

	WCHAR szResID[32];
	wsprintfW(szResID, L"0x%016X", resId);
	m_pSpy -> AddParamValueToList(L"ResourceID", szResID);

	WCHAR szEnlisted[10];
	if (enlisted)
		wsprintfW(szEnlisted, L"TRUE");
	else
		wsprintfW(szEnlisted, L"FALSE");
	m_pSpy -> AddParamValueToList(L"Enlisted", szEnlisted);

	WCHAR szNumRated[16];
	wsprintfW(szNumRated, L"0x%08X", NumRated);
	m_pSpy -> AddParamValueToList(L"NumRated", szNumRated);

	WCHAR szRating[16];
	wsprintfW(szRating, L"0x%08X", Rating);
	m_pSpy -> AddParamValueToList(L"Rating", szRating);

	IF_AUDIT_DO(OnResourceAllocate)(pInfo->perfCount,GuidToBstr(pInfo->guidApp), szObjectID, pszType, szResID,enlisted,szNumRated,szRating);
	return S_OK;
}


STDMETHODIMP CResourceSub::OnResourceRecycle(
	COMSVCSEVENTINFO * pInfo, 
	ULONG64 ObjectID,
    LPCOLESTR pszType,
    ULONG64 resId)
{
	m_pSpy -> AddEventToList(pInfo->perfCount, _TEXT("OnResourceRecycle"),GuidToBstr(pInfo->guidApp));
	m_pSpy -> AddParamValueToList(L"Type", pszType);

	WCHAR szObjectID[32];
	wsprintfW(szObjectID, L"0x%016X", ObjectID);
	m_pSpy -> AddParamValueToList(L"ObjectID", szObjectID);

	WCHAR szResID[32];
	wsprintfW(szResID, L"0x%016X", resId);
	m_pSpy -> AddParamValueToList(L"ResourceID", szResID);

	IF_AUDIT_DO(OnResourceRecycle)(pInfo->perfCount,GuidToBstr(pInfo->guidApp), szObjectID, pszType, szResID);
	return S_OK;
}


STDMETHODIMP CResourceSub::OnResourceDestroy(
    COMSVCSEVENTINFO * pInfo, 
	ULONG64 ObjectID,
	HRESULT hr,
    LPCOLESTR pszType,
    ULONG64 resId)
{
	m_pSpy -> AddEventToList(pInfo->perfCount, _TEXT("OnResourceDestroy"),GuidToBstr(pInfo->guidApp));
	
	m_pSpy -> AddParamValueToList(L"Type", pszType);

	WCHAR szObjectID[32];
	wsprintfW(szObjectID, L"0x%016X", ObjectID);
	m_pSpy -> AddParamValueToList(L"ObjectID", szObjectID);

	WCHAR szResID[32];
	wsprintfW(szResID, L"0x%016X", resId);
	m_pSpy -> AddParamValueToList(L"ResourceID", szResID);

	WCHAR szHResult[16];
	wsprintfW(szHResult, L"0x%08X", hr);
	m_pSpy -> AddParamValueToList(L"Destroy HR", szHResult);

	IF_AUDIT_DO(OnResourceDestroy)(pInfo->perfCount, GuidToBstr(pInfo->guidApp), szObjectID, hr,pszType, szResID);
	return S_OK;
}

STDMETHODIMP CResourceSub::OnResourceTrack(
											COMSVCSEVENTINFO * pInfo, 
											ULONG64 ObjectID,
											LPCOLESTR pszType,
											ULONG64 resId,
											BOOL enlisted)
{
	m_pSpy -> AddEventToList(pInfo->perfCount, _TEXT("OnResourceTrack"), GuidToBstr(pInfo->guidApp));

	m_pSpy -> AddParamValueToList(L"Type", pszType);

	WCHAR szObjectID[32];
	wsprintfW(szObjectID, L"0x%016X", ObjectID);
	m_pSpy -> AddParamValueToList(L"ObjectID", szObjectID);

	WCHAR szResID[32];
	wsprintfW(szResID, L"0x%016X", resId);
	m_pSpy -> AddParamValueToList(L"ResourceID", szResID);

	WCHAR szEnlisted[10];
	if (enlisted)
		wsprintfW(szEnlisted, L"TRUE");
	else
		wsprintfW(szEnlisted, L"FALSE");
	m_pSpy -> AddParamValueToList(L"Enlisted", szEnlisted);
		
	IF_AUDIT_DO(OnResourceTrack)(pInfo->perfCount,GuidToBstr(pInfo->guidApp), szObjectID, pszType, szResID,enlisted);


	return S_OK;
}

