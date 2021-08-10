//****************************************************************************
//  Module:     NMCHAT.EXE
//  File:       UI.CPP
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

#include "precomp.h"


//****************************************************************************
//
// Special resource constants
//
//****************************************************************************

#define IDW_MSG   100
#define IDW_USER  101
#define IDW_EDIT  102

// See _rgColMember
#define ILV_NAME    0
#define ILV_TIME    1
#define ILV_TEXT    2

const int DYP_EDIT   = 30;  // Fixed Height of Edit control
const int DXP_USER   = 80;  // Fixed Width of User List
const int YP_TOP     = 3;
const int XP_LEFT    = 0;


//****************************************************************************
//
// Prototypes
//
//****************************************************************************

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void UiSizeMsgWindow(int dx, int dy);
void UiSendText(void);
void UiClearText(void);
void UiDisplayMessage(LPTSTR pszMsg, LPTSTR pszUser);
CMember * UiGetSelectedMember(void);


//****************************************************************************
//
// Global Variables
//
//****************************************************************************

HINSTANCE g_hInstExe    = NULL;          // Current Instance
HACCEL    g_hAccelTable = NULL;          // Menu accelerators
HMENU     g_hMenu       = NULL;          // Main Menu
HWND      g_hwndMain    = NULL;          // Main Window
HWND      g_hwndMsg     = NULL;          // Message window
HWND      g_hwndEdit    = NULL;          // Edit Control
HWND      g_hwndUser    = NULL;          // User List

// string constants (no change for international)
#define MY_CLASS_NAME       TEXT("MyClassName")

// List column information

typedef struct
{
    UINT  dwWidth;
    LPTSTR lpsz;
}
    COL;


// See ILV_*
static COL _rgColMsg[] =
{
    {DXP_USER,  TEXT("Name")},
    {80,        TEXT("Time")},
    {400,       TEXT("Message")},
};


//****************************************************************************
//
// BOOL CreateMsgWindow(void)
//
// Create the main message listview
//
//****************************************************************************

BOOL CreateMsgWindow(void)
{
    g_hwndMsg = ::CreateWindow(TEXT("SysListView32"), NULL,
                    WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | LVS_REPORT,
                    0, 0, 0, 0, g_hwndMain, (HMENU) IDW_USER, g_hInstExe, NULL);
    if (NULL != g_hwndMsg)
    {
        // Initialize column data
        int iCol	= 0;
		int	iRet	= 0;
        COL  *lpCol	= NULL;
        LV_COLUMN lvc;

        lpCol = _rgColMsg;
        ::ZeroMemory(&lvc, sizeof(lvc));
        lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvc.fmt = LVCFMT_LEFT;
        for (iCol = 0; iCol < ARRAY_ELEMENTS(_rgColMsg); iCol++)
        {
            lvc.iSubItem = iCol;
            lvc.cx = lpCol->dwWidth;
            lvc.pszText = lpCol->lpsz;
            
            iRet = ListView_InsertColumn(g_hwndMsg, iCol, &lvc);
            ASSERT(-1 != iRet);
            lpCol++;
        }
    }
    return (BOOL) g_hwndMsg;
}


//****************************************************************************
//
// BOOL CreateUserList(void)
//
// Create a listbox for the users
//
//****************************************************************************

BOOL CreateUserList(void)
{
    g_hwndUser = ::CreateWindow(TEXT("SysListView32"), NULL,
                        WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
                        0, 0, DXP_USER, 0, g_hwndMain, (HMENU) IDW_MSG, g_hInstExe, NULL);
    if (NULL != g_hwndUser)
    {
        // Initialize column data
        int iRet = 0;
        LV_COLUMN lvc;
        ::ZeroMemory(&lvc, sizeof(lvc));
        lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvc.fmt = LVCFMT_LEFT;
        lvc.iSubItem = 0;
        lvc.cx = DXP_USER;
        lvc.pszText = TEXT("Send To");
        iRet = ListView_InsertColumn(g_hwndUser, 0, &lvc);
        ASSERT(-1 != iRet);
    }
    return (BOOL) g_hwndUser;
}


WNDPROC lpProcEdit = NULL;
LRESULT FAR PASCAL SubClsEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//****************************************************************************
//
// LRESULT FAR PASCAL SubClsEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT FAR PASCAL SubClsEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if ((uMsg == WM_CHAR) && (VK_RETURN == wParam))
    {
        ::UiSendText();
        return 0L;
    }

    return ::CallWindowProc(lpProcEdit, hwnd, uMsg, wParam, lParam);
}


//****************************************************************************
//
// BOOL CreateEditWindow(void)
//
//****************************************************************************

BOOL CreateEditWindow(void)
{
    g_hwndEdit = ::CreateWindow(TEXT("EDIT"), NULL,
                        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                        0, 0, 0, DYP_EDIT, g_hwndMain, (HMENU) IDW_EDIT, g_hInstExe, NULL);
    if (NULL != g_hwndEdit)
    {
        // set the font for the window

        lpProcEdit = (WNDPROC) ::GetWindowLong(g_hwndEdit, GWL_WNDPROC);
        ::SetWindowLong(g_hwndEdit, GWL_WNDPROC, (LONG)(WNDPROC) SubClsEdit);
    }

    return (BOOL) g_hwndEdit;
}


//****************************************************************************
//
// BOOL InitMainUI(void)
//
// Initialize the window data and register the window class
//
//****************************************************************************

BOOL InitMainUI(void)
{
    TCHAR szTitle[MAX_PATH + 1];
    WNDCLASS  wc;

	::ZeroMemory(szTitle, (MAX_PATH + 1) * sizeof(TCHAR));
	::ZeroMemory(&wc, sizeof(WNDCLASS));

    ASSERT(NULL != g_hInstExe);

    g_hAccelTable = ::LoadAccelerators(g_hInstExe, MAKEINTRESOURCE(ID_APPACCEL));

    ::LoadString(g_hInstExe, IDS_APP_TITLE, szTitle, CCHMAX(szTitle));

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = g_hInstExe;
    wc.hIcon         = LoadIcon(g_hInstExe, MAKEINTRESOURCE(ICO_MAIN));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDM_APP);
    wc.lpszClassName = MY_CLASS_NAME;

    // Register the window class and return FALSE if unsuccesful.
    ::RegisterClass(&wc);

    // Create a main window for this application instance.
    g_hwndMain = ::CreateWindow(MY_CLASS_NAME, szTitle, WS_OVERLAPPEDWINDOW,
                                0, 0, 400, 300, NULL, NULL, g_hInstExe, NULL);
    ASSERT(NULL != g_hwndMain);

    g_hMenu = ::GetMenu(g_hwndMain);
    ASSERT(NULL != g_hMenu);

    return (NULL != g_hwndMain && NULL != g_hMenu);
}


//****************************************************************************
//
// BOOL ProcessStartup(LPSTR lpszCmd, int nCmdShow)
//
// Initialize the application after checking command line, etc.
//
//****************************************************************************

BOOL ProcessStartup(LPSTR lpszCmd, int nCmdShow)
{
    ::GetInvokeInfo(&g_InvokeInfo);
    if (g_InvokeInfo.fValid)
    {
        if (::FindWindow(MY_CLASS_NAME, NULL))
        {
            return FALSE;
        }
    }

    ::InitCommonControls();

    HRESULT hr = ::CoInitialize(NULL);
    if (SUCCEEDED(hr))
    {
        if (::InitMainUI())
        {
            if (::CreateMsgWindow())
            {
                if (::CreateUserList())
                {
                    if (::CreateEditWindow())
                    {
                        ASSERT(NULL != g_hwndMain);
                        ::ShowWindow(g_hwndMain, nCmdShow);
                        ::UpdateWindow(g_hwndMain);
                        ::SetFocus(g_hwndEdit);

                        hr = ::InitConfMgr();
                        if (SUCCEEDED(hr))
                        {
                            hr = ::InitApplet();
                            if (SUCCEEDED(hr))
                            {
                                return TRUE;
                            }
                        }
                    }
                }
            }
        }
    }

    return FALSE;
}


//****************************************************************************
//
// void ProcessCleanup(void)
//
//****************************************************************************

void ProcessCleanup(void)
{
    // Release all objects to which this app has a reference
    ::FreeConference();
    ::FreeApplet();
    ::FreeConfMgr();

    // Uninitialize OLE
    ::CoUninitialize();
}


//****************************************************************************
//
// int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR  lpszCmd, int nCmdShow)
//
// Main Windows entrypoint
//
//****************************************************************************

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR lpszCmd, int nCmdShow)
{
    g_hInstExe = hInstance;

    if (::ProcessStartup(lpszCmd, nCmdShow))
    {
        MSG  msg;
        while (::GetMessage(&msg, NULL, 0, 0))
        {
            if (! ::TranslateAccelerator(msg.hwnd, g_hAccelTable, &msg))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
    }

    ::ProcessCleanup();

    return 0;
}


//****************************************************************************
//
// void UiDisplayMsg(LPTSTR pszMsg, LPTSTR pszUser)
//
//****************************************************************************

void UiDisplayMsg(LPTSTR pszMsg, LPTSTR pszUser)
{
    if (NULL == pszUser)
    {
        pszUser = TEXT("");
    }
    ::UiDisplayMessage(pszMsg, pszUser);
}


//****************************************************************************
//
// void UiDisplaySysMsg(LPTSTR pszMsg, LPTSTR pszUser)
//
//****************************************************************************

void UiDisplaySysMsg(LPTSTR pszMsg, LPTSTR pszUser)
{
    if (NULL == pszUser)
    {
        pszUser = TEXT("");
    }
    ::UiDisplayMessage(pszMsg, pszUser);
}


//****************************************************************************
//
// void UiDisplayMessage(LPTSTR pszMsg, LPTSTR pszUser)
//
//****************************************************************************

void UiDisplayMessage(LPTSTR pszMsg, LPTSTR pszUser)
{
    int iItem = 0;
    LV_ITEM  lvItem;
    SYSTEMTIME sysTime;
    TCHAR szTime[MAX_PATH + 1];
	::ZeroMemory(szTime, (MAX_PATH + 1) * sizeof(TCHAR));

    ::ZeroMemory(&lvItem, sizeof(lvItem));
    lvItem.iItem = 0x0FFFFFFF;
    lvItem.mask = LVIF_PARAM | LVIF_TEXT;
    lvItem.pszText = pszUser;
    lvItem.cchTextMax = ::lstrlen(lvItem.pszText);
    iItem = ListView_InsertItem(g_hwndMsg, &lvItem);

    // print out the time
    ::GetLocalTime(&sysTime);

	_sntprintf(szTime,MAX_PATH, TEXT("%02d:%02d:%02d"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
    ListView_SetItemText(g_hwndMsg, iItem, ILV_TIME, szTime);

    // print out the text
    ListView_SetItemText(g_hwndMsg, iItem, ILV_TEXT, pszMsg);    
}



//****************************************************************************
//
// void UiSendText(void)
//
// Send the line of text in the edit control.
//
//****************************************************************************

void UiSendText(void)
{
    UINT  cb = 0;
    TCHAR sz[MAX_PATH + 1];

	::ZeroMemory(sz, (MAX_PATH + 1) * sizeof(TCHAR));

    // Get the text line
    cb = ::SendMessage(g_hwndEdit, WM_GETTEXT, (WPARAM) CCHMAX(sz), (LPARAM) sz);
    ::SendMessage(g_hwndEdit, EM_SETSEL, (WPARAM) 0, (LPARAM)-1);
    ::SendMessage(g_hwndEdit, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");

    if (0 != cb && NULL != g_pSession)
    {
        CMember * pMember = ::UiGetSelectedMember();
        AppletUserID uidReceiver = (NULL != pMember) ? pMember->GetUID() : 0;

        g_pSession->SendData(uidReceiver, ++cb, (LPBYTE) sz);
    }
}


//****************************************************************************
//
// void UiClearText(void)
//
//****************************************************************************

void UiClearText(void)
{
    ListView_DeleteAllItems(g_hwndMsg);
}


//****************************************************************************
//
// void UiSizeMsgWindow(int dx, int dy)
//
//****************************************************************************

void UiSizeMsgWindow(int dx, int dy)
{
    ::MoveWindow(g_hwndEdit, XP_LEFT, dy - DYP_EDIT, dx, DYP_EDIT, TRUE);
    dy -= (YP_TOP + DYP_EDIT);

    ::MoveWindow(g_hwndUser, XP_LEFT, YP_TOP, DXP_USER, dy, TRUE);
    dx -= DXP_USER;

    ::MoveWindow(g_hwndMsg, XP_LEFT + DXP_USER, YP_TOP, dx, dy, TRUE);
}



//****************************************************************************
//
// void UiAddMember(CMember *pMember)
//
//****************************************************************************

void UiAddMember(CMember *pMember)
{
   	LPTSTR pszName = NULL;
    if (NULL != pMember)
    {
        pszName = pMember->GetName();
    }
    else
    {
        pszName = TEXT("everyone");
    }

    LV_ITEM  lvItem;
    ::ZeroMemory(&lvItem, sizeof(lvItem));
    lvItem.iItem = ListView_GetItemCount(g_hwndUser);
    lvItem.mask = LVIF_PARAM | LVIF_TEXT;
    lvItem.pszText = pszName;
    lvItem.cchTextMax = ::lstrlen(pszName);
    lvItem.lParam = (LPARAM) pMember;
    ListView_InsertItem(g_hwndUser, &lvItem);

    if (NULL != pMember)
    {
        ::UiDisplaySysMsg(TEXT("<joined>"), pszName);
    }
}


//****************************************************************************
//
// void UiRemoveMember(CMember *pMember)
//
//****************************************************************************

void UiRemoveMember(CMember *pMember)
{
    if (NULL != pMember)
    {
        ::UiDisplaySysMsg(TEXT("<left>"), pMember->GetName());
    }

    LV_FINDINFO findInfo;
    ::ZeroMemory(&findInfo, sizeof(findInfo));
    findInfo.flags = LVFI_PARAM;
    findInfo.lParam = (LPARAM) pMember; 
    int iItem = ListView_FindItem(g_hwndUser, -1, &findInfo);
    ListView_DeleteItem(g_hwndUser, iItem);
}


//****************************************************************************
//
// CMember * UiGetSelectedMember(void)
//
//****************************************************************************

CMember * UiGetSelectedMember(void)
{
    int iItem = ListView_GetNextItem(g_hwndUser, -1, LVNI_ALL | LVNI_SELECTED);
    if (-1 != iItem)
    {
        LV_ITEM lv;
        lv.mask = LVIF_PARAM;
        lv.iItem = iItem;
        ListView_GetItem(g_hwndUser, &lv);
        return (CMember *) lv.lParam;
    }
    return NULL;
}


//****************************************************************************
//
// void CmdExit(void)
//
// Shutdown the application.
//
//****************************************************************************

void CmdExit(void)
{
    ::DestroyWindow(g_hwndMain);
}


//****************************************************************************
//
// void CmdAbout(void)
//
// Display the about box
//
//****************************************************************************

void CmdAbout(void)
{
    TCHAR szVersion[MAX_PATH + 1];
	::ZeroMemory(szVersion, (MAX_PATH + 1) * sizeof(TCHAR));

    ::LoadString(g_hInstExe, IDS_VERSION, szVersion, CCHMAX(szVersion));

    ::ShellAbout(g_hwndMain, szVersion, NULL, LoadIcon(g_hInstExe, MAKEINTRESOURCE(ICO_MAIN)));
}


//****************************************************************************
//
// void CmdRegisterLocal(void)
//
// Register local chat such that in the future NetMeeting knows how to
// invoke this applet.
//
//****************************************************************************

void CmdRegisterLocal(void)
{
    HRESULT hr = ::RegisterNonStandardAppletInvokeInfo();
    ASSERT(S_OK == hr);
}


//****************************************************************************
//
// void CmdInvokeRemote(void)
//
// Invoke the same applet on all the machines participating in this conference.
//
//****************************************************************************

void CmdInvokeRemote(void)
{
    if (NULL != g_pSession)
    {
        g_pSession->InvokeApplet();
    }
}


//****************************************************************************
//
// LRESULT MsgCmdMain(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
//
// Handle a WM_COMMAND message
//
//****************************************************************************

LRESULT MsgCmdMain(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    switch (GET_WM_COMMAND_ID(wParam, lParam))
    {
		case IDM_EXIT:
		{
			::CmdExit();
			break;
		}
		case IDM_VIEW_CLEAR:
		{
			::UiClearText();
			break;
		}
		case IDM_ABOUT:
		{
			::CmdAbout();
			break;
		}
		case IDM_REGISTER_LOCAL:
		{
			::CmdRegisterLocal();
			break;
		}
		case IDM_INVOKE_ALL:
		{
			::CmdInvokeRemote();
			break;
		}
    }
    return 0L;
}


//****************************************************************************
//
// LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
// Main Window proc
//
//****************************************************************************

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lRet = 0;
    switch (uMsg)
    {
		case WM_COMMAND:
		{
			lRet = ::MsgCmdMain(hwnd, wParam, lParam);
			break;
		}
		case WM_DESTROY:
		{
			::PostQuitMessage(0);
			break;
		}
		case WM_CLOSE:
		{
			::CmdExit();
			break;
		}
		case WM_SIZE:
		{
			::UiSizeMsgWindow(LOWORD(lParam), HIWORD(lParam));
			break;
		}
		case WM_GETMINMAXINFO:
		{
			((LPMINMAXINFO) lParam)->ptMinTrackSize.x = 325;
			((LPMINMAXINFO) lParam)->ptMinTrackSize.y = 250;
			break;
		}
		default:
		{
			lRet = ::DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
		}
    }
    return lRet;
}


