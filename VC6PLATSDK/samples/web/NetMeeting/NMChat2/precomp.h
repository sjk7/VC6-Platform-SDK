//****************************************************************************
//  Module:     NMCHAT.EXE
//  File:       PRECOMP.H
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1999-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#ifndef _PRECOMP_H
#define _PRECOMP_H

// System Include files
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>
#include <ocidl.h>
#include <stdio.h>

#include "imsconf2.h"
#include "iapplet.h"


#define ARRAY_ELEMENTS(rg)      (sizeof(rg) / sizeof(rg[0]))
#define CCHMAX(sz)              (sizeof(sz) / sizeof(TCHAR))

#define MAX_MEMBERS         8

#ifdef DEBUG
__inline void MyDebugBreak(void) { ::DebugBreak(); }
#define ASSERT(f)       if (! (f)) { MyDebugBreak(); }
#else
#define ASSERT(f)
#endif

class CApplet;
class CAppletSession;
class CMember;

void UiDisplayMsg(LPTSTR pszMsg, LPTSTR pszMemberName = NULL);
void UiDisplaySysMsg(LPTSTR pszMsg, LPTSTR pszMemberName = NULL);
void UiAddMember(CMember *pMember);
void UiRemoveMember(CMember *pMember);
extern HWND g_hwndMain;
extern HINSTANCE g_hInstExe;

#include "conf.h"
#include "session.h"
#include "applet.h"

#include "resource.h"

#endif /* _PRECOMP_H */
