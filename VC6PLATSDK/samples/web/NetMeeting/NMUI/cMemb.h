//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       CMEMB.H
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1995-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************


typedef struct tagUser {
	INmMember * pMember;
	int    iItem;
	ULONG  uId;
	LPTSTR pszName;
	LPTSTR pszAddr;
	NM_ADDR_TYPE uType;
	ULONG  uVersion;
	ULONG  uchCaps;
	BOOL   fLocal;
	BOOL   fMcu;
	BOOL   fTop;
	INmChannelAudio * m_pChannelAudio;
	INmChannelAppShare * m_pChannelAs;
	INmChannelFt       * m_pChannelFt;
	INmChannelData   * m_pChannelData;
} USER;
typedef USER * PUSER;

// from cMemb.cpp
VOID AddMember(INmMember * pMember);
VOID RemoveMember(INmMember * pMember);
VOID FreeAllUsers(void);
VOID FreeUser(PUSER pUser);
PUSER PUserFromINmMember(INmMember * pMember);
VOID UpdateUserChannel(PUSER pUser, INmChannel * pChannel, NM_MEMBER_NOTIFY uNotify);
PUSER PUserLocal();

// from dlg.cpp
VOID AddUserToUList(PUSER pUser, HWND hwndCombo, BOOL fEveryone);
VOID RemoveUserFromUList(PUSER pUser, HWND hwndCombo);
VOID UpdateConfView(void);

extern COBLIST * g_pListUser;

