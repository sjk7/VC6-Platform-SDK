//****************************************************************************
//  Module:     NMCHAT.EXE
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

INmMember * g_pMemberLocal = NULL;


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
	{
		return -1;
	}

	LV_FINDINFO findInfo;
	ClearStruct(&findInfo);						// Zero's memory
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
	if(NULL == pMember)
	{
		return NULL;
	}
	
	HRESULT hr	= NO_ERROR;
	BSTR bstr	= NULL;
	INmMember * pMemberTop = NULL;

	PUSER pUser = new USER;
	if (NULL == pUser)
	{
		return NULL;
	}

	ClearStruct(pUser);						// Zero's memory

	pUser->pMember = pMember;
	pMember->AddRef();

	hr = pMember->GetName(&bstr);
	if (SUCCEEDED(hr))
	{
		pUser->pszName = PszFromBstr(bstr);
		SysFreeString(bstr);
	}

	hr = pMember->GetNmVersion(&pUser->uVersion);

	pUser->fLocal = S_OK == pMember->IsSelf();
	pUser->fMcu = S_OK == pMember->IsMCU();

	pUser->fTop = FALSE;
	if (SUCCEEDED(g_pConference->GetTopProvider(&pMemberTop)))
	{
		pUser->fTop = (pMember == pMemberTop);
		pMemberTop->Release();
	}

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

	if(NULL == pUser)
	{
		return;
	}

	FreePlpv(&pUser->pszName);
	
	if (NULL != pUser->pMember)
	{
		pUser->pMember->Release();
	}

	delete pUser;
}


//****************************************************************************
//
// VOID FreeAllUsers(void)
//
//****************************************************************************

VOID FreeAllUsers(void)
{
	if (NULL == g_pListUser)
	{
		return;
	}

	while (!g_pListUser->IsEmpty())
	{
		USER * pUser = (USER *) g_pListUser->RemoveHead();
		ASSERT(NULL != pUser);
		FreeUser(pUser);
	}

	delete g_pListUser;
	g_pListUser = NULL;
}


//****************************************************************************
//
// VOID AddMember(INmMember * pMember)
//
//****************************************************************************

VOID AddMember(INmMember * pMember)
{
	PUSER pUser = AllocUser(pMember);
	if (NULL == pUser)
	{
		return;
	}
	
	AddNode(pUser, &g_pListUser);

	LV_ITEM  lvItem;
	ClearStruct(&lvItem);						// Zero's memory
	lvItem.iItem = g_pListUser->GetItemCount();
	lvItem.mask = LVIF_PARAM | LVIF_TEXT;
	lvItem.pszText = (S_OK == pMember->IsSelf()) ? TEXT("everyone") : pUser->pszName;
	lvItem.cchTextMax = lstrlen(pUser->pszName);
	lvItem.lParam = (LPARAM) pUser;
	ListView_InsertItem(ghwndUser, &lvItem);

	DisplaySysMsg(TEXT("<joined>"), pMember);
}


//****************************************************************************
//
// VOID RemoveMember(INmMember * pMember)
//
//****************************************************************************

VOID RemoveMember(INmMember * pMember)
{
	if (NULL == g_pListUser)
	{
		return;
	}

	POSITION pos = g_pListUser->GetHeadPosition();
	while (NULL != pos)
	{
		POSITION posSav = pos;
		PUSER pUser = (PUSER) g_pListUser->GetNext(pos);
		if (pMember == pUser->pMember)
		{
			ASSERT(pMember == pUser->pMember);
			DisplaySysMsg(TEXT("<left>"), pMember);

			ListView_DeleteItem(ghwndUser, ItemFromPUser(pUser));
			FreeUser(pUser);
			g_pListUser->RemoveAt(posSav);
			return;
		}
	}
}


//****************************************************************************
//
// INmMember * GetSelectedMember(void)
//
//****************************************************************************

INmMember * GetSelectedMember(void)
{
	int iItem = 0;

	if (NULL == g_pListUser)
	{
		return NULL;
	}

	iItem = ListView_GetNextItem(ghwndUser, -1, LVNI_ALL | LVNI_SELECTED);
	if (-1 == iItem)
	{
		return NULL;
	}

	LV_ITEM lv;
	lv.mask = LVIF_PARAM;
	lv.iItem = iItem;
	ListView_GetItem(ghwndUser, &lv);

	return ((PUSER) lv.lParam)->pMember;
}

