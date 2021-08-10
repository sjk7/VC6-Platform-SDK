//****************************************************************************
//  Module:     NMSHARE.EXE     
//  File:       CHWND.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1997-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************


#include "precomp.h"

COBLIST * g_pListApp = (COBLIST *) NULL;


//****************************************************************************
//
// int AddApp(INmSharableApp * pApp)
//
//****************************************************************************

int AddApp(INmSharableApp * pApp)
{
	TCHAR sz[MAX_PATH + 1];
	ZeroMemory(sz,(MAX_PATH + 1) * sizeof(TCHAR));
	_sntprintf(sz,MAX_PATH,TEXT("%08X"), pApp);
	
	//wsprintf(sz, TEXT("%08X"), pApp);

	pApp->AddRef();
	AddNode(pApp, &g_pListApp);

	LV_ITEM  lvItem;
	ClearStruct(&lvItem);
	lvItem.iItem = g_pListApp->GetItemCount();
	lvItem.mask = LVIF_PARAM | LVIF_TEXT;
	lvItem.pszText = sz;
	lvItem.cchTextMax = lstrlen(sz);
	lvItem.lParam = (LPARAM) pApp;
	return ListView_InsertItem(ghwndApp, &lvItem);
}


//****************************************************************************
//
// int ItemFromPApp(INmSharableApp * pApp)
//
//****************************************************************************

int ItemFromPApp(INmSharableApp * pApp)
{
	if (NULL == ghwndApp)
		return -1;

	LV_FINDINFO findInfo;
	ClearStruct(&findInfo);
	findInfo.flags = LVFI_PARAM;
    findInfo.lParam = (LPARAM) pApp; 
    return ListView_FindItem(ghwndApp, -1, &findInfo);
}


//****************************************************************************
//
// VOID FreeAllApps(void)
//
//****************************************************************************

VOID FreeAllApps(void)
{
	if (NULL != g_pListApp)
	{
		while (!g_pListApp->IsEmpty())
		{
			INmSharableApp * pApp = (INmSharableApp *) g_pListApp->RemoveHead();
			ASSERT(NULL != pApp);
			pApp->Release();
		}
	}
}


//****************************************************************************
//
// VOID UpdateApp(INmSharableApp * pApp)
//
//****************************************************************************

VOID UpdateApp(INmSharableApp * pApp)
{
	HRESULT hr = S_OK;
	LPTSTR  psz = NULL;
	BSTR    bstr;

	HWND    hwnd = 0;
	int     iItem = 0;
	NM_SHAPP_STATE uState;

	iItem = ItemFromPApp(pApp);
	if (-1 == iItem)
	{
		iItem = AddApp(pApp);
		if (-1 == iItem)
			return;
	}

	hr = pApp->GetHwnd(&hwnd);
	if (SUCCEEDED(hr))
	{
		TCHAR sz[MAX_PATH + 1];
		ZeroMemory(sz,(MAX_PATH + 1) * sizeof(TCHAR));
		_sntprintf(sz,MAX_PATH,TEXT("%08X"), hwnd);
		
		//TCHAR sz[MAX_PATH];
		//wsprintf(sz, TEXT("%08X"), hwnd);
		ListView_SetItemText(ghwndApp, iItem, ILV_HWND, sz);
	}

	hr = pApp->GetState(&uState);
	if (SUCCEEDED(hr))
	{
		ListView_SetItemText(ghwndApp, iItem, ILV_STATUS,
			(NM_SHAPP_SHARED == uState) ? TEXT("Shared") : TEXT("Not Shared"));
	}

	hr = pApp->GetName(&bstr);
	if (SUCCEEDED(hr))
	{
		psz = PszFromBstr(bstr);
		SysFreeString(bstr);

		ListView_SetItemText(ghwndApp, iItem, ILV_NAME, psz);
		FreePlpv(&psz);
	}
}


//****************************************************************************
//
// VOID UpdateAppList(void)
//
//****************************************************************************

VOID UpdateAppList(void)
{
	// Update all apps
	// - enumerate all
	// - ensure all are in list
	// - check data for each
}


//****************************************************************************
//
// LRESULT MsgNotifyAppList(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT MsgNotifyAppList(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LV_DISPINFO *pLvdi = (LV_DISPINFO *)lParam;

	switch(pLvdi->hdr.code)
	{
		case NM_DBLCLK:
		case NM_RETURN:
		{
			HRESULT hr = S_OK;
			NM_SHAPP_STATE uState;

			int iItem = ListView_GetNextItem(ghwndApp, -1, LVNI_ALL | LVNI_SELECTED);
			if (-1 == iItem)
				break;

			LV_ITEM lvi;
			ClearStruct(&lvi);
			lvi.iItem = iItem;
			lvi.mask = LVIF_PARAM;
			if (!ListView_GetItem(ghwndApp, &lvi))
				break;

			INmSharableApp * pApp = (INmSharableApp *) lvi.lParam;
			ASSERT(NULL != pApp);
			hr = pApp->GetState(&uState);
			if (FAILED(hr))
				break;

			if (NM_SHAPP_NOT_SHARED == uState)
				uState = NM_SHAPP_SHARED;
			else
				uState = NM_SHAPP_NOT_SHARED;

			hr = pApp->SetState(uState);
			break;
		}
		default:
			break;
	}

	return 0;
}

