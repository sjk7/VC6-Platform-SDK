//****************************************************************************
//  Module:     NMSHARE.EXE     
//  File:       CMEMB.CPP
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

COBLIST * g_pListUser = (COBLIST *) NULL;


//****************************************************************************
//
// PUSER PUserFromINmMember(INmMember * pMember)
//
//****************************************************************************

PUSER PUserFromINmMember(INmMember * pMember)
{
	if (NULL != g_pListUser)
	{
		POSITION pos = g_pListUser->GetHeadPosition();
		while (NULL != pos)
		{
			PUSER pUser = (PUSER) g_pListUser->GetNext(pos);
			if (pMember == pUser->pMember)
			{
				ASSERT(pMember == pUser->pMember);
				return pUser;
			}
		}
	}

	return NULL;
}


//****************************************************************************
//
// int ItemFromPUser(PUSER pUser)
//
//****************************************************************************

int ItemFromPUser(PUSER pUser)
{
	if (NULL == ghwndUser)
		return -1;

	LV_FINDINFO findInfo;
	ClearStruct(&findInfo);
	findInfo.flags = LVFI_PARAM;
    findInfo.lParam = (LPARAM) pUser; 
    return ListView_FindItem(ghwndUser, -1, &findInfo);
}


//****************************************************************************
//
// PUSER AllocUser(INmMember * pMember)
//
//****************************************************************************

PUSER AllocUser(INmMember * pMember)
{
	HRESULT hr = S_OK;
	BSTR bstr;

	if (NULL == pMember)
	{
		return NULL;
	}

	PUSER pUser = new USER;
	if (NULL == pUser)
	{
		return NULL;
	}
	ClearStruct(pUser);

	pUser->pMember = pMember;
	pMember->AddRef();

	hr = pMember->GetName(&bstr);
	if (SUCCEEDED(hr))
	{
		pUser->pszName = PszFromBstr(bstr);
		SysFreeString(bstr);
	}
	//*** What happens if GetName fails? ***

	return pUser;
}


//****************************************************************************
//
// VOID FreeUser(PUSER pUser)
//
//****************************************************************************

VOID FreeUser(PUSER pUser)
{
	ASSERT(NULL != pUser);

	if (NULL != pUser)
	{
		FreePlpv(&pUser->pszName);
		
		if (NULL != pUser->pMember)
		{
			pUser->pMember->Release();
		}
	}
}

VOID FreeAllUsers(void)
{
	if (NULL != g_pListUser)
	{
		while (!g_pListUser->IsEmpty())
		{
			RemoveMember(((PUSER) g_pListUser->GetHead())->pMember);
		}
	}
}


//****************************************************************************
//
// VOID AddMember(INmMember * pMember)
//
//****************************************************************************

VOID AddMember(INmMember * pMember)
{
	if (NULL == pMember)
	{
		return;
	}

	PUSER pUser = AllocUser(pMember);
	
	if (NULL == pUser)
	{
		return;
	}
	
	AddNode(pUser, &g_pListUser);

	LV_ITEM  lvItem;
	ClearStruct(&lvItem);
	lvItem.iItem = g_pListUser->GetItemCount();
	lvItem.mask = LVIF_PARAM | LVIF_TEXT;
	lvItem.pszText = pUser->pszName;
	lvItem.cchTextMax = lstrlen(pUser->pszName);
	lvItem.lParam = (LPARAM) pUser;
	ListView_InsertItem(ghwndUser, &lvItem);

	TCHAR szMsg[MAX_PATH + 1];
	ZeroMemory(szMsg,(MAX_PATH + 1) * sizeof(TCHAR));
	_sntprintf(szMsg,MAX_PATH,TEXT("%s joined"), pUser->pszName);

	DisplayMsg(szMsg);

}


//****************************************************************************
//
// VOID RemoveMember(INmMember * pMember)
//
//****************************************************************************

VOID RemoveMember(INmMember * pMember)
{
	if (NULL == g_pListUser)
		return;

	if (NULL == pMember)
		return;

	POSITION pos = g_pListUser->GetHeadPosition();
	while (NULL != pos)
	{
		POSITION posSav = pos;
		PUSER pUser = (PUSER) g_pListUser->GetNext(pos);
		if (pMember == pUser->pMember)
		{
			TCHAR szMsg[MAX_PATH + 1];
			ZeroMemory(szMsg,(MAX_PATH + 1) * sizeof(TCHAR));
			_sntprintf(szMsg,MAX_PATH,TEXT("%s left"), pUser->pszName);

			DisplayMsg(szMsg);

			ListView_DeleteItem(ghwndUser, ItemFromPUser(pUser));
			FreeUser(pUser);
			g_pListUser->RemoveAt(posSav);
			return;
		}
	}
}


