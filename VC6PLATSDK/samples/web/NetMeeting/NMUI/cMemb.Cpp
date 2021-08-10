//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       CMEMB.CPP
//  Content:    INmMember Routines
//              
//
//  Copyright (c) Microsoft Corporation 1995-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include "precomp.h"

COBLIST	* g_pListUser	= NULL	;
UINT	  gcUsers		= 0		;


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
			if	(NULL == pUser)
			{
				ERROR_MSG(TEXT("PUserFromINmMember: NULL == pUser"));
				break;
			}

			if (pMember == pUser->pMember)
				return pUser;
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
	if (NULL == ghwndLView)
		return -1;

	LV_FINDINFO findInfo;
	ZeroMemory(&findInfo, sizeof(findInfo));
	findInfo.flags = LVFI_PARAM;
    findInfo.lParam = (LPARAM) pUser;
    return ListView_FindItem(ghwndLView, -1, &findInfo);
}


//****************************************************************************
//
// PUSER PUserLocal()
//
// Return a pointer to the local user information
//
//****************************************************************************

PUSER PUserLocal()
{
	if (NULL != g_pListUser)
	{
		POSITION pos = g_pListUser->GetHeadPosition();
		while (NULL != pos)
		{
			PUSER pUser = (PUSER) g_pListUser->GetNext(pos);
			if	(NULL == pUser)
			{
				ERROR_MSG(TEXT("PUserLocal: NULL == pUser"));
				break;
			}

			if (pUser->fLocal)
				return pUser;
		}
	}

	return NULL;
}

//****************************************************************************
//
// VOID UpdateUserDisplay(PUSER pUser)
//
//****************************************************************************

VOID UpdateUserDisplay(PUSER pUser)
{
	if	(NULL == pUser)
	{
		ERROR_MSG(TEXT("UpdateUserDisplay: NULL == pUser"));
		return;
	}

	int iItem = ItemFromPUser(pUser);
	TCHAR sz[MAX_PATH + 1];
	ZeroMemory(sz, (MAX_PATH + 1) * sizeof(TCHAR));

	ASSERT(NULL != ghwndLView);

	_sntprintf(sz, MAX_PATH, TEXT("%d\0"), pUser->uVersion);
	ListView_SetItemText(ghwndLView, iItem, ILV_VERSION, sz);
	
	_sntprintf(sz, MAX_PATH, TEXT("%d\0"), pUser->fMcu);
	ListView_SetItemText(ghwndLView, iItem, ILV_MCU, sz);

	_sntprintf(sz, MAX_PATH, TEXT("%d\0"), pUser->fLocal);
	ListView_SetItemText(ghwndLView, iItem, ILV_LOCAL, sz);

	_sntprintf(sz, MAX_PATH, TEXT("%X\0"), pUser->m_pChannelAudio);
	ListView_SetItemText(ghwndLView, iItem, ILV_AUDIO, sz);

	_sntprintf(sz, MAX_PATH, TEXT("%X\0"), pUser->m_pChannelAs);
	ListView_SetItemText(ghwndLView, iItem, ILV_AS, sz);

	_sntprintf(sz, MAX_PATH, TEXT("%X\0"), pUser->m_pChannelFt);
	ListView_SetItemText(ghwndLView, iItem, ILV_FT, sz);

	_sntprintf(sz, MAX_PATH, TEXT("%08X\0"), pUser->uchCaps);
	ListView_SetItemText(ghwndLView, iItem, ILV_CAPS, sz);

	ListView_SetItemText(ghwndLView, iItem, ILV_ADDR,
		(NULL == pUser->pszAddr) ? TEXT("?") : pUser->pszAddr);

	_sntprintf(sz, MAX_PATH, TEXT("%08X\0"), pUser->uId);
	ListView_SetItemText(ghwndLView, iItem, ILV_ID, sz);

}

//****************************************************************************
//
// VOID UpdateUserCount(void)
//
//****************************************************************************

VOID UpdateUserCount(void)
{
	TCHAR sz[MAX_PATH + 1];
	ZeroMemory(sz, (MAX_PATH + 1) * sizeof(TCHAR));

	if (1 == gcUsers)
	{
		lstrcpyn(sz, TEXT("1 user\0"), MAX_PATH+1);
		sz[MAX_PATH] = 0;
	}
	else
		_sntprintf(sz, MAX_PATH, TEXT("%d users\0"), gcUsers);

	UpdateStatusBar(sz, IDSBP_USERCOUNT, 0);
}


//****************************************************************************
//
// PUSER AllocUser(INmMember * pMember)
//
//****************************************************************************

PUSER AllocUser(INmMember * pMember)
{
	if	(NULL == pMember)
	{
		ERROR_MSG(TEXT("AllocUser: NULL == pMember"));
		return NULL;
	}

	HRESULT			hr			= NO_ERROR;
	BSTR			bstr		= NULL;
	INmConference *	pConference	= NULL;

	PUSER pUser = new USER;
	if (NULL == pUser)
	{
		return NULL;
	}

	ZeroMemory(pUser, sizeof(USER));

	pUser->pMember = pMember;
	pMember->AddRef();

	hr = pMember->GetName(&bstr);
	if (FAILED(hr))
	{
		WARN_MSG(TEXT("Problem with GetName"));
	}
	else
	{
		pUser->pszName = PszFromBstr(bstr);
		SysFreeString(bstr);
	}

	hr = pMember->GetAddr(&bstr, &pUser->uType);
	if (FAILED(hr))
	{
		WARN_MSG(TEXT("Problem with GetAddr"));
	}
	else
	{
		pUser->pszAddr = PszFromBstr(bstr);
		SysFreeString(bstr);
	}

	hr = pMember->GetNmchCaps(&pUser->uchCaps);
	if (FAILED(hr))
	{
		WARN_MSG(TEXT("Problem with GetNmchCaps"));
		pUser->uchCaps = 0;
	}

	hr = pMember->GetNmVersion(&pUser->uVersion);
	if (FAILED(hr))
	{
		WARN_MSG(TEXT("Problem with GetNmVersion"));
		pUser->uVersion = 0;
	}

	hr = pMember->GetID(&pUser->uId);
	if (FAILED(hr))
	{
		WARN_MSG(TEXT("Problem with GetID"));
		pUser->uId = 0;
	}

	pUser->fLocal = S_OK == pMember->IsSelf();
	pUser->fMcu = S_OK == pMember->IsMCU();
	pUser->fTop = FALSE;
	hr = pMember->GetConference(&pConference);
	if (FAILED(hr))
	{
		WARN_MSG(TEXT("Problem with GetConference"));
	}
	else
	{
		INmMember * pMemberTop	= NULL;
		if (SUCCEEDED(pConference->GetTopProvider(&pMemberTop)))
		{
			pUser->fTop = (pMember == pMemberTop);
			pMemberTop->Release();
		}
		pConference->Release();
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
	if	(NULL == pUser)
	{
		ERROR_MSG(TEXT("FreeUser: NULL == pUser"));
		return;
	}

	FreePlpv(&pUser->pszName);
	FreePlpv(&pUser->pszAddr);
	
	if (NULL != pUser->pMember)
	{
		OBJECT_MSG(TEXT("[%08X] member released"), pUser->pMember);
		pUser->pMember->Release();
		pUser->pMember = NULL;
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
	if (NULL != g_pListUser)
	{
		while (!g_pListUser->IsEmpty())
		{
			PUSER	pUser = (PUSER) g_pListUser -> GetHead();
			if	(NULL == pUser)
			{
				ERROR_MSG(TEXT("FreeAllUsers: NULL == pUser"));
				break;
			}

			RemoveMember(pUser->pMember);
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
	PUSER pUser = AllocUser(pMember);
	if (NULL == pUser)
	{
		return;
	}
	
	if	(NULL == AddNode(pUser, &g_pListUser))
	{
		ERROR_MSG(TEXT("AddMember: AddNode returned Null"));
		return;
	}

	LV_ITEM  lvItem;
	ZeroMemory(&lvItem, sizeof(LV_ITEM));

	lvItem.iItem = gcUsers;
	lvItem.mask = LVIF_PARAM | LVIF_TEXT;
	lvItem.pszText = pUser->pszName;
	lvItem.cchTextMax = lstrlen(pUser->pszName);
	lvItem.lParam = (LPARAM) pUser;
	ListView_InsertItem(ghwndLView, &lvItem);

	gcUsers++;
	UpdateUserCount();
	UpdateUserDisplay(pUser);

	AddUserToUList(pUser, ghwndUList, FALSE);
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

	POSITION pos = g_pListUser->GetHeadPosition();
	while (NULL != pos)
	{
		POSITION posSav = pos;

		PUSER pUser = (PUSER) g_pListUser->GetNext(pos);
		if	(NULL == pUser)
		{
			ERROR_MSG(TEXT("RemoveMember: NULL == pUser"));
			return;
		}

		if (pMember == pUser->pMember)
		{
			RemoveUserFromUList(pUser, ghwndUList);
			ListView_DeleteItem(ghwndLView, ItemFromPUser(pUser));
			FreeUser(pUser);
			pUser = NULL;

			g_pListUser->RemoveAt(posSav);

			gcUsers--;
			UpdateUserCount();
			return;
		}
	}
}

//****************************************************************************
//
// VOID UpdateUserChannel(PUSER pUser, INmChannel * pChannel, NM_MEMBER_NOTIFY uNotify)
//
//****************************************************************************

VOID UpdateUserChannel(PUSER pUser, INmChannel * pChannel, NM_MEMBER_NOTIFY uNotify)
{
	ULONG	  uch		= 0		;
	//PVOID	* ppChannel = NULL	;
	
	ASSERT(NULL != pChannel);
	if	((NULL == pChannel) || (NULL == pUser))
	{
		ERROR_MSG(TEXT("UpdateUserChannel: Null parameter passed in"));
		return;
	}

	if (FAILED(pChannel->GetNmch(&uch)))
	{
		return;
	}

	if (NM_MEMBER_ADDED == uNotify)
	{
	switch (uch)
	{
		case NMCH_AUDIO:
		{
			INmChannelAudio * pChannelAudio	= NULL;
			if (SUCCEEDED(pChannel->QueryInterface(IID_INmChannelAudio, (PVOID *) &pChannelAudio)))
			{
				if	(NULL == pChannelAudio)
				{
					ERROR_MSG(TEXT("UpdateUserChannel: pChannelAudio == NULL"));
					break;
				}

				if ((S_OK == pChannelAudio->IsIncoming()) != pUser->fLocal)
				{
					ASSERT((NULL == pUser->m_pChannelAudio) || (pChannelAudio == pUser->m_pChannelAudio));
					pUser->m_pChannelAudio = pChannelAudio;
				}

				pChannelAudio->Release();
			}
			break;
		}

		case NMCH_SHARE:
			if (NULL == pUser->m_pChannelAs)
			{
				INmChannelAppShare * pChannelAs	= NULL;
				if (SUCCEEDED(pChannel->QueryInterface(IID_INmChannelAppShare, (PVOID *) &pChannelAs)))
				{
					if	(NULL == pChannelAs)
					{
						ERROR_MSG(TEXT("UpdateUserChannel: pChannelAs == NULL"));
						break;
					}

					pUser->m_pChannelAs = pChannelAs;
					pChannelAs->Release();
				}
			}
			break;

		case NMCH_FT:
			if (NULL == pUser->m_pChannelFt)
			{
				INmChannelFt * pChannelFt;
				if (SUCCEEDED(pChannel->QueryInterface(IID_INmChannelFt, (PVOID *) &pChannelFt)))
				{
					if	(NULL == pChannelFt)
					{
						ERROR_MSG(TEXT("UpdateUserChannel: pChannelFt == NULL"));
						break;
					}

					pUser->m_pChannelFt = pChannelFt;
					pChannelFt->Release();
				}
			}
			break;

		case NMCH_VIDEO:
		case NMCH_DATA:
		case NMCH_NONE:
		case NMCH_ALL:
		default:
			break;
	}
	} /* CONFN_MEMBER_ADDED */

	UpdateUserDisplay(pUser);
}


//****************************************************************************
//
// VOID UpdateUserInfo(PUSER pUser)
//
//****************************************************************************

VOID UpdateUserInfo(PUSER pUser)
{
	if	(NULL == pUser)
	{
		ERROR_MSG(TEXT("NULL == pUser"));
		return;
	}

	ULONG   ul		= 0;
	HRESULT hr		= NO_ERROR;
	LPTSTR  psz		= NULL;
	BSTR    bstr	= NULL;

	INmMember * pMember = pUser->pMember;

	hr = pMember->GetName(&bstr);
	if (FAILED(hr))
	{
		WARN_MSG(TEXT("Problem with GetName"));
	}
	else
	{
		psz = PszFromBstr(bstr);
		SysFreeString(bstr);

		if (0 != lstrcmp(pUser->pszName, psz))
		{
			WARN_MSG(TEXT("Replacing Name [%s] => [%s]"), 
				(NULL == pUser->pszName) ? TEXT("NULL") : pUser->pszName, 
				(NULL == psz) ? TEXT("NULL") : psz);
		}
		FreePlpv(&pUser->pszName);
		pUser->pszName = psz;
	}

	hr = pMember->GetAddr(&bstr, &pUser->uType);
	if (FAILED(hr))
	{
		WARN_MSG(TEXT("Problem with GetAddr"));
	}
	else
	{
		psz = PszFromBstr(bstr);
		SysFreeString(bstr);

		if(NULL != pUser->pszAddr)
		{
			if (0 != lstrcmp(pUser->pszAddr, psz))
			{
				WARN_MSG(TEXT("Replacing Addr [%s] => [%s]"), 
					(NULL == pUser->pszAddr) ? TEXT("NULL") : pUser->pszAddr,
					(NULL == psz) ? TEXT("NULL") : psz);
			}
			FreePlpv(&pUser->pszAddr);
		}
		pUser->pszAddr = psz;
	}

	hr = pMember->GetNmchCaps(&ul);
	if (FAILED(hr))
	{
		WARN_MSG(TEXT("Problem with GetNmchCaps"));
		pUser->uchCaps = 0;
	}
	else if (pUser->uchCaps != ul)
	{
		WARN_MSG(TEXT("Updating uchCaps [%08X] => [%08X]"), pUser->uchCaps, ul);
		pUser->uchCaps = ul;
	}

	hr = pMember->GetNmVersion(&ul);
	if (FAILED(hr))
	{
		WARN_MSG(TEXT("Problem with GetNmVersion"));
		pUser->uVersion = 0;
	}
	else if (pUser->uVersion != ul)
	{
		WARN_MSG(TEXT("Updating version [%08X] => [%08X]"), pUser->uVersion, ul);
		pUser->uchCaps = ul;
	}

	if (pUser->fLocal != (S_OK == pMember->IsSelf()) )
	{
		ERROR_MSG(TEXT("Local User status changed?"));
	}

	if (pUser->fMcu != (S_OK == pMember->IsMCU()))
	{
		ERROR_MSG(TEXT("MCU status changed?"));
	}
}


//****************************************************************************
//
// VOID UpdateConfView(void)
//
//****************************************************************************

VOID UpdateConfView(void)
{
	if (NULL == g_pListUser)
		return;

	POSITION pos = g_pListUser->GetHeadPosition();
	while (NULL != pos)
	{
		PUSER pUser = (PUSER) g_pListUser->GetNext(pos);
		UpdateUserInfo(pUser);
		UpdateUserDisplay(pUser);
	}
}

