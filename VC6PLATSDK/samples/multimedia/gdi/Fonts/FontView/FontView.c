
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1993 - 2000 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#define NOMINMAX
#include <windows.h>
#include <stdio.h>

#include "FontView.H"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char szAppName[] = "FontView";
char szAppTitle[] = "FontView - A Font Examination Utility";

BOOL bZoomed = FALSE;

HWND    hwndMain, hwndClient;
HWND    hwndMenuField, hwndTimeField;
HWND    hwndLabel1, hwndCreateParam, hwndCreateValue, hwndZoom;

LOGFONT lf = {0,0,0,0,0,0,0,0,0,0,0,0,0,""};

HMENU   hSysMenuMain = (HMENU)NULL;
HMENU   hFileMenu    = (HMENU)NULL;
HMENU   hEditMenu    = (HMENU)NULL;
HMENU   hViewMenu    = (HMENU)NULL;
HMENU   hMetricsMenu = (HMENU)NULL;
HMENU   hHelpMenu    = (HMENU)NULL;
HMENU   hSysMenuAdv  = (HMENU)NULL;
HMENU   hMenu        = (HMENU)NULL;

LONG_PTR APIENTRY WndProc         (HWND, UINT, WPARAM, LPARAM);
LONG_PTR APIENTRY ClientProc      (HWND, UINT, WPARAM, LPARAM);
LONG_PTR APIENTRY ClientCharSetProc      (HWND, UINT, WPARAM, LPARAM);
LONG_PTR APIENTRY ClientGlyphProc      (HWND, UINT, WPARAM, LPARAM);

BOOL FillInParam (HWND, int);
BOOL FillInValue (HWND, int);
int FAR PASCAL EnumFontNames (LPLOGFONT, LPTEXTMETRIC, DWORD, LPARAM);

WNDPROC fpCharSetProc = 0;
WNDPROC fpGlyphProc = 0;

/* Dialogs.C Prototypes */
BOOL APIENTRY SimpleDlgProc   (HWND, UINT, WPARAM, LPARAM);
BOOL APIENTRY CreateDlgProc   (HWND, UINT, WPARAM, LPARAM);
BOOL APIENTRY MetricsDlgProc   (HWND, UINT, WPARAM, LPARAM);
BOOL APIENTRY EnumDlgProc   (HWND, UINT, WPARAM, LPARAM);

/* Display.C Prototypes */
void DrawAscii (HDC hdc, RECT *pRect, WORD direction);
BYTE FindChar (HDC hdc, RECT *pRect, int x, int y);
void DrawGlyph (HDC hdc, RECT *pRect, BYTE glyph, HFONT hfont);

/* ToolBar.C Prototypes */
BOOL InitToolBar (HANDLE);
BOOL CreateToolBar (HWND, HANDLE, int);
BOOL AdjustToolBar (HWND);
HWND AddToolLabel (HANDLE , int, LPSTR, int, DWORD);
HWND AddToolCombo (HANDLE, int, int, DWORD);
HWND AddToolButton (HANDLE, int, LPSTR, int, int, DWORD);
BOOL AddToolSpace (int, int);
int ToolBarHeight (HWND);

/* StatusBar.C Prototypes */
BOOL InitStatusBar (HANDLE);
BOOL CreateStatusBar (HWND, HANDLE, int);
BOOL AdjustStatusBar (HWND);
HWND AddStatusField (HANDLE, int, int, int, BOOL);
int StatusBarHeight (HWND);


int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{

    MSG         msg;
    WNDCLASS    wndclass;
    HANDLE      hAccelTable;

    if (!hPrevInst) {
        wndclass.style         = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc   = (WNDPROC)WndProc;
        wndclass.cbClsExtra    = 0;
        wndclass.cbWndExtra    = 0;
        wndclass.hInstance     = hInst;
        wndclass.hIcon         = LoadIcon (hInst, szAppName);
        wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
        wndclass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);
        wndclass.lpszMenuName  = szAppName;
        wndclass.lpszClassName = szAppName;

        if (!RegisterClass (&wndclass)) {
            return FALSE;
        }

        wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wndclass.lpfnWndProc   = (WNDPROC)ClientProc;
        wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wndclass.lpszMenuName  = NULL;
        wndclass.lpszClassName = "FontClient";

        if (!RegisterClass (&wndclass)) {
            return FALSE;
        }

        fpCharSetProc = MakeProcInstance ((WNDPROC)ClientCharSetProc, hInst);
        fpGlyphProc   = MakeProcInstance ((WNDPROC)ClientGlyphProc, hInst);

        if (!InitToolBar (hInst)) {
            return FALSE;
        }

        if (!InitStatusBar (hInst)) {
            return FALSE;
        }
    }


    hwndMain = CreateWindow (szAppName, szAppName,
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, 0,
        CW_USEDEFAULT, 0,
        NULL, NULL, hInst, NULL);

    if (!hwndMain) {
        return FALSE;
    }
    /* Get handles to the various menus. Some of these we will use later */
    /* to display menu descriptions in the status bar */
        hSysMenuMain = GetSystemMenu(hwndMain,FALSE);
    hMenu = GetMenu(hwndMain);
    if (hMenu) {
        hFileMenu = GetSubMenu(hMenu,0);
        hEditMenu = GetSubMenu(hMenu,1);
        hViewMenu = GetSubMenu(hMenu, 2);
        hMetricsMenu = GetSubMenu(hMenu,3);
        hHelpMenu = GetSubMenu(hMenu,4);
    }

    if (CreateToolBar (hwndMain, hInst, ID_TOOLBAR)) {
        hwndLabel1 = AddToolLabel (hInst, 0, "CreateFont:", 0, SS_RIGHT);
        AddToolSpace (6, 0);
        hwndCreateParam = AddToolCombo (hInst, ID_CREATEPARAM, -25, CBS_DROPDOWN | WS_VSCROLL);
        FillInParam (hwndCreateParam, 0);

        AddToolSpace (10, 0);
        hwndCreateValue = AddToolCombo (hInst, ID_CREATEVALUE, -30, CBS_DROPDOWN | WS_VSCROLL);
        FillInValue (hwndCreateValue, CFP_BASE+0);

        AddToolSpace (10, 0);
        hwndZoom = AddToolButton (hInst, ID_ZOOM, "ZOOM", 24, 0, BS_OWNERDRAW);

    } else {
        return FALSE;
    }


    if (CreateStatusBar (hwndMain, hInst, ID_STATUSBAR)) {
        hwndMenuField = AddStatusField (hInst, ID_MENUFIELD, 100, 0, FALSE);
        hwndTimeField = AddStatusField (hInst, ID_TIMEFIELD, -13, -13, TRUE);
        if (hwndTimeField) {
            SetTimer (hwndMain, 1, 1000, NULL);
        }
    } else {
        return FALSE;
    }

    hwndClient = CreateWindow ("FontClient", "FontClient",
        WS_CHILD | WS_CLIPSIBLINGS | WS_BORDER | WS_VISIBLE,
        0, 0, 0, 0,
        hwndMain,(HMENU)666, hInst, NULL);

    SetWindowLongPtr (hwndClient, GWLP_WNDPROC, (DWORD_PTR)fpCharSetProc);
    bZoomed = FALSE;

    if (!hwndMain) {
        return FALSE;
    }

    ShowWindow (hwndMain, nCmdShow);
    InvalidateRect (hwndZoom, NULL, TRUE);

    hAccelTable = LoadAccelerators (hInst, szAppName);

    while (GetMessage (&msg, NULL, 0, 0)) {
        if (!TranslateAccelerator (hwndMain, hAccelTable, &msg)) {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }


    return (int)msg.wParam;

    lpCmdLine; // Just to resolve reference
}


/* ================================================================================================ *\
    Fill in the first combo box with all the different 'CreateFont' parameters that we can change
\* ================================================================================================ */
BOOL FillInParam (HWND hwnd, int focus)
{
    int index;

    index = 0;
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"nHeight");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_HEIGHT);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"nWidth");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_WIDTH);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"nEscapement");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_ESCAPEMENT);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"nOrientation");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_ORIENTATION);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"nWeight");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_WEIGHT);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"cItalic");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_ITALIC);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"cUnderline");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_UNDERLINE);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"cStrikeOut");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_STRIKEOUT);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"cCharSet");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_CHARSET);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"cOutputPrecision");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_OUTPUTPRECISION);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"cClipPrecision");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_CLIPPRECISION);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"cQuality");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_QUALITY);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"cPitch...");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_PITCH);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"c...Family");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_FAMILY);
    SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"lpFacename");
    SendMessage (hwnd, CB_SETITEMDATA, index++, CFP_FACENAME);
    SendMessage (hwnd, CB_SETCURSEL, focus, 0);
    return TRUE;
}

/* ================================================================================================ *\
    Fill in the second combo box with valid values, based on the current setting in the first combo
\* ================================================================================================ */
BOOL FillInValue (HWND hwnd, int param)
{
    int i, index, focus;
    LONG_PTR data;
    char szTmp[80];
    ATOM atom;
    HDC  hdc;
    FARPROC lpEnumFonts;
    HINSTANCE hInst;

    SendMessage (hwnd, CB_RESETCONTENT, 0, 0);
    focus = -1;
    index = 0;

    // Each of the following cases will contain two different 'loops', the first one will fill the
    // combo box with values, the second will locate the current setting in the combobox and set
    // the focus to it. If the value is not currently in the combobox, then it will be inserted at
    // the proper location.

    switch (param) {
        case CFP_HEIGHT:
            // Lets just toss in a range of heights, from -72 to 72, by twos
            // If the user wants to enter in a custom value, they need to use
            // the 'CreateFont' dialog for now.
            for (i=-72; i<72; i+=2) {
                if (i < 0) {
                    _snprintf (szTmp, sizeof(szTmp), "%d = cell height = %u", i, abs(i));
                } else if (i == 0) {
                    _snprintf (szTmp,sizeof(szTmp), "%u = default", i);
                } else {
                    _snprintf (szTmp, sizeof(szTmp), "%u = character height", i);
                }
                SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)szTmp);
                SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD)i);
            }

            for (i=0; i<index; i++) {
                data = (long)SendMessage (hwnd, CB_GETITEMDATA, i, 0);
                if (data == lf.lfHeight) {
                    focus = i;
                    break;
                } else if (data > lf.lfHeight) {
                    _snprintf (szTmp, sizeof(szTmp), "%u", lf.lfHeight);
                    SendMessage (hwnd, CB_INSERTSTRING, i, (DWORD_PTR)(LPSTR)szTmp);
                    SendMessage (hwnd, CB_SETITEMDATA, i, (DWORD_PTR)lf.lfHeight);
                    focus = i;
                    break;
                }
            }
            if (focus == -1) {
                _snprintf (szTmp, sizeof(szTmp), "%u", lf.lfHeight);
                focus = (int)SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)szTmp);
                SendMessage (hwnd, CB_SETITEMDATA, focus, (DWORD_PTR)lf.lfHeight);
            }

            break;

        case CFP_WIDTH:
            // Lets just toss in a range of widths, from 0 to 72, by twos
            // If the user wants to enter in a custom value, they need to use
            // the 'CreateFont' dialog for now.
            for (i=0; i<72; i+=2) {
                if (i==0) {
                    _snprintf (szTmp, sizeof(szTmp), "%u = default aspect", i);
                } else {
                    _snprintf (szTmp, sizeof(szTmp), "%u", i);
                }
                SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)szTmp);
                SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)i);
            }
            for (i=0; i<index; i++) {
                data = SendMessage (hwnd, CB_GETITEMDATA, i, 0);
                if (data == lf.lfWidth) {
                    focus = i;
                    break;
                } else if (data > lf.lfWidth) {
                    _snprintf (szTmp, sizeof(szTmp), "%u", lf.lfWidth);
                    SendMessage (hwnd, CB_INSERTSTRING, i, (DWORD_PTR)(LPSTR)szTmp);
                    SendMessage (hwnd, CB_SETITEMDATA, i, (DWORD_PTR)lf.lfWidth);
                    focus = i;
                    break;
                }
            }
            break;

        case CFP_ESCAPEMENT:
            for (i=0; i<4500; i+=10) {
                _snprintf (szTmp, sizeof(szTmp), "%u = (%u/10 degrees)", i, i);
                SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)szTmp);
                SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)i);
            }
            for (i=0; i<index; i++) {
                data = SendMessage (hwnd, CB_GETITEMDATA, i, 0);
                if (data == lf.lfEscapement) {
                    focus = i;
                    break;
                } else if (data > lf.lfEscapement) {
                    _snprintf (szTmp, sizeof(szTmp), "%u = (%u/10 degrees)", lf.lfEscapement, data);
                    SendMessage (hwnd, CB_INSERTSTRING, i, (DWORD_PTR)(LPSTR)szTmp);
                    SendMessage (hwnd, CB_SETITEMDATA, i, (DWORD_PTR)lf.lfEscapement);
                    focus = i;
                    break;
                }
            }
            break;

        case CFP_ORIENTATION:
            for (i=0; i<4500; i+=10) {
                _snprintf (szTmp, sizeof(szTmp), "%u = (%u/10 degrees)", i, i);
                SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)szTmp);
                SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)i);
            }
            for (i=0; i<index; i++) {
                data = SendMessage (hwnd, CB_GETITEMDATA, i, 0);
                if (data == lf.lfOrientation) {
                    focus = i;
                    break;
                } else if (data > lf.lfOrientation) {
                    _snprintf (szTmp, sizeof(szTmp), "%u = (%u/10 degrees)", lf.lfOrientation, data);
                    SendMessage (hwnd, CB_INSERTSTRING, i, (DWORD_PTR)(LPSTR)szTmp);
                    SendMessage (hwnd, CB_SETITEMDATA, i, (DWORD_PTR)lf.lfOrientation);
                    focus = i;
                    break;
                }
            }
            break;

        case CFP_WEIGHT:
            index = 0;
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"0 = FW_DONTCARE");
            SendMessage (hwnd, CB_SETITEMDATA, index++, 0);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"100 = FW_THIN");
            SendMessage (hwnd, CB_SETITEMDATA, index++, 100);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"200 = FW_EXTRALIGHT");
            SendMessage (hwnd, CB_SETITEMDATA, index++, 200);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"300 = FW_LIGHT");
            SendMessage (hwnd, CB_SETITEMDATA, index++, 300);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"400 = FW_NORMAL");
            SendMessage (hwnd, CB_SETITEMDATA, index++, 400);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"500 = FW_MEDIUM");
            SendMessage (hwnd, CB_SETITEMDATA, index++, 500);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"600 = FW_SEMIBOLD");
            SendMessage (hwnd, CB_SETITEMDATA, index++, 600);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"700 = FW_BOLD");
            SendMessage (hwnd, CB_SETITEMDATA, index++, 700);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"800 = FW_EXTRABOLD");
            SendMessage (hwnd, CB_SETITEMDATA, index++, 800);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"900 = FW_HEAVY");
            SendMessage (hwnd, CB_SETITEMDATA, index++, 900);

            for (i=0; i<index; i++) {
                data = SendMessage (hwnd, CB_GETITEMDATA, i, 0);
                if (data == lf.lfWeight) {
                    focus = i;
                    break;
                } else if (data > lf.lfWeight) {
                    _snprintf (szTmp, sizeof(szTmp), "%u", lf.lfWeight);
                    SendMessage (hwnd, CB_INSERTSTRING, i, (DWORD_PTR)(LPSTR)szTmp);
                    focus = i;
                    break;
                }
            }
            break;

        case CFP_ITALIC:
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"FALSE");
            SendMessage (hwnd, CB_SETITEMDATA, 0, (DWORD_PTR)FALSE);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"TRUE");
            SendMessage (hwnd, CB_SETITEMDATA, 1, (DWORD_PTR)TRUE);
            focus = (lf.lfItalic?1:0);
            break;

        case CFP_UNDERLINE:
            index=0;
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"FALSE");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)FALSE);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"TRUE");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)TRUE);
            focus = (lf.lfUnderline?1:0);
            break;

        case CFP_STRIKEOUT:
            index=0;
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"FALSE");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)FALSE);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"TRUE");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)TRUE);  \
            focus = (lf.lfStrikeOut?1:0);
            break;

        case CFP_CHARSET:
            index = 0;
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"0 = ANSI_CHARSET");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)ANSI_CHARSET);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"SYMBOL_CHARSET");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)SYMBOL_CHARSET);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"SHIFTJIS_CHARSET");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)SHIFTJIS_CHARSET);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"OEM_CHARSET");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)OEM_CHARSET);
            for (i=0; i<index; i++) {
                data = SendMessage (hwnd, CB_GETITEMDATA, i, 0);
                if (data == (long)lf.lfCharSet) {
                    focus = i;
                    break;
                }
            }
            break;

            break;

        case CFP_OUTPUTPRECISION:
            index=0;
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"0 = OUT_DEFAULT_PRECIS");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)OUT_DEFAULT_PRECIS);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"OUT_STRING_PRECIS");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)OUT_STRING_PRECIS);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"OUT_CHARACTER_PRECIS");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)OUT_CHARACTER_PRECIS);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"OUT_STROKE_PRECIS");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)OUT_STROKE_PRECIS);
            for (i=0; i<index; i++) {
                data = SendMessage (hwnd, CB_GETITEMDATA, i, 0);
                if (data == (long)lf.lfOutPrecision) {
                    focus = i;
                    break;
                }
            }
            break;

        case CFP_CLIPPRECISION:
            index=0;
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"0 = CLIP_DEFAULT_PRECIS");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)CLIP_DEFAULT_PRECIS);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"CLIP_CHARACTER_PRECIS");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)CLIP_CHARACTER_PRECIS);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"CLIP_STROKE_PRECIS");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)CLIP_STROKE_PRECIS);
            for (i=0; i<index; i++) {
                data = SendMessage (hwnd, CB_GETITEMDATA, i, 0);
                if (data == (long)lf.lfClipPrecision) {
                    focus = i;
                    break;
                }
            }
            break;

        case CFP_QUALITY:
            index=0;
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"0 = DEFAULT_QUALITY");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)DEFAULT_QUALITY);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"DRAFT_QUALITY");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)DRAFT_QUALITY);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"PROOF_QUALITY");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)PROOF_QUALITY);
            for (i=0; i<index; i++) {
                data = SendMessage (hwnd, CB_GETITEMDATA, i, 0);
                if (data == (long)lf.lfQuality) {
                    focus = i;
                    break;
                }
            }
            break;

        case CFP_PITCH:
            index=0;
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"0 = DEFAULT_PITCH");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD)DEFAULT_PITCH);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"FIXED_PITCH");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)FIXED_PITCH);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"VARIABLE_PITCH");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)VARIABLE_PITCH);
            for (i=0; i<index; i++) {
                data = SendMessage (hwnd, CB_GETITEMDATA, i, 0);
                if (data == (long)(0x03&lf.lfPitchAndFamily)) {
                    focus = i;
                    break;
                }
            }
            break;

        case CFP_FAMILY:
            index=0;
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"0 = FF_DONTCARE");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)FF_DONTCARE);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"FF_ROMAN");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD)FF_ROMAN);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"FF_SWISS");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)FF_SWISS);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"FF_MODERN");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD)FF_MODERN);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"FF_SCRIPT");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)FF_SCRIPT);
            SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"FF_DECORATIVE");
            SendMessage (hwnd, CB_SETITEMDATA, index++, (DWORD_PTR)FF_DECORATIVE);
            for (i=0; i<index; i++) {
                data = SendMessage (hwnd, CB_GETITEMDATA, i, 0);
                if (data == (long)(0xFC&lf.lfPitchAndFamily)) {
                    focus = i;
                    break;
                }
            }
            break;

        case CFP_FACENAME:
            index = (int)SendMessage (hwnd, CB_ADDSTRING, 0, (DWORD_PTR)(LPSTR)"(none)");
            SendMessage (hwnd, CB_SETITEMDATA, index, 0);
            if (lstrcmp(lf.lfFaceName, "(none)") == 0) {
                lf.lfFaceName[0] = 0;
            }
            hdc = GetDC (hwnd);

            hInst = (HINSTANCE)GetWindowLongPtr (hwnd, GWLP_HINSTANCE);
            lpEnumFonts = MakeProcInstance ((FARPROC)EnumFontNames, hInst);
            EnumFonts (hdc, NULL, (FONTENUMPROC)lpEnumFonts, (LPARAM)&hwnd);
            FreeProcInstance (lpEnumFonts);
            ReleaseDC (hwnd, hdc);
            atom = GlobalFindAtom ((LPSTR)lf.lfFaceName);
            if (atom == (ATOM)0 && (lstrlen (lf.lfFaceName)>0)) {
                index = (int)SendMessage (hwnd, CB_ADDSTRING, 0, (LONG_PTR)(LPSTR)lf.lfFaceName);
                focus = index;
            } else if (lstrlen(lf.lfFaceName)==0) {
                index = (int)SendMessage (hwnd, CB_FINDSTRING, (UINT)-1, (LONG_PTR)(LPSTR)"(none)");
                focus = index;
            } else {
                index = (int)SendMessage (hwnd, CB_GETCOUNT, 0, 0);
                for (i=0; i<index; i++) {
                    data = SendMessage (hwnd, CB_GETITEMDATA, i, 0);
                    if ((DWORD)data == (DWORD)atom) {
                        focus = i;
                        break;
                    }
                }
            }
            break;
    }
    if (focus >= 0) {
        SendMessage (hwnd, CB_SETCURSEL, focus, 0);
    } else {
        SendMessage (hwnd, CB_SETCURSEL, 0, 0);
    }
    return TRUE;
}


// Font enumeration callback. This adds the font name to the atom list.
int FAR PASCAL EnumFontNames (LPLOGFONT lpLogFont, LPTEXTMETRIC lpTextMetric, DWORD nFontType, LPARAM lData)
{
    HWND hwnd;
    FARPROC lpFontEnumProc;
    HDC  hdc;
    ATOM atom;
    HWND hwndCombo;
    int  index;

    hwnd = GetFocus();
    hdc  = GetDC(hwnd);
    hwndCombo = (HWND)lData;

    atom = GlobalFindAtom ((LPSTR)lpLogFont->lfFaceName);
    if (atom == (ATOM)0) {
        atom = GlobalAddAtom (lpLogFont->lfFaceName);
    }
    index = (int) SendMessage(hwndCombo, CB_FINDSTRING, (UINT)-1, (LONG_PTR)(LPSTR)lpLogFont->lfFaceName);
    if (index == CB_ERR) {
        index = (int)SendMessage (hwndCombo, CB_ADDSTRING, 0, (LONG_PTR)(LPSTR)lpLogFont->lfFaceName);
        SendMessage (hwndCombo, CB_SETITEMDATA, index, atom);
    }

    ReleaseDC(hwnd, hdc);

    return TRUE;

    lpTextMetric;   // unreferenced formal paramater
    nFontType;      // unreferenced formal parameter
    lpFontEnumProc; // unreferenced formal parameter
}


// A quick little routine that will center one window over another, handy for dialog boxes.
BOOL CenterWindow (HWND hwndChild, HWND hwndParent)
{
    RECT    rChild, rParent;
    int     wChild, hChild, wParent, hParent;
    int     wScreen, hScreen, xNew, yNew;
    HDC     hdc;

    GetWindowRect (hwndChild, &rChild);
    wChild = rChild.right - rChild.left;
    hChild = rChild.bottom - rChild.top;

    GetWindowRect (hwndParent, &rParent);
    wParent = rParent.right - rParent.left;
    hParent = rParent.bottom - rParent.top;

    hdc = GetDC (hwndChild);
    wScreen = GetDeviceCaps (hdc, HORZRES);
    hScreen = GetDeviceCaps (hdc, VERTRES);
    ReleaseDC (hwndChild, hdc);

    xNew = rParent.left + ((wParent - wChild) /2);
    if (xNew < 0) {
        xNew = 0;
    } else if ((xNew+wChild) > wScreen) {
        xNew = wScreen - wChild;
    }

    yNew = rParent.top  + ((hParent - hChild) /2);
    if (yNew < 0) {
        yNew = 0;
    } else if ((yNew+hChild) > hScreen) {
        yNew = hScreen - hChild;
    }

    return SetWindowPos (hwndChild, NULL, xNew, yNew, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}


LONG_PTR APIENTRY WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInst = 0;
    HDC hdc;
    PAINTSTRUCT ps;
    FARPROC lpDlgFunc;
    char    szMsg [80];
    time_t  lTime;
    struct tm *datetime;

#define HOUR (datetime->tm_hour)
#define MIN (datetime->tm_min)
#define SEC (datetime->tm_sec)

    char    szTime [20];
    int     index;
    RECT rect;

static INT_PTR  idMenuSelect;
    INT_PTR     tmp;
    LONG_PTR wmEvent, wmId;
    HWND    wmhWnd;
    POINT   point;
    BOOL bRedraw;
    INT_PTR wmMenuCmd, wmFlags;
    HMENU wmhMenu;

        if (hwnd) {
        hInst = (HINSTANCE)GetWindowLongPtr (hwnd, GWLP_HINSTANCE);
        }

    switch (msg) {
    case WM_CREATE:
            return DefWindowProc (hwnd, msg, wParam, lParam);
            break;

        case WM_TIMER:
            time (&lTime);
            datetime = localtime (&lTime);
            _snprintf (szTime, sizeof(szTime), "%02d:%02d:%02d %s",
            (HOUR%12?HOUR%12:12), MIN, SEC, (LPSTR)(HOUR/12?"PM":"AM"));
            SetWindowText (hwndTimeField, szTime);
            break;

        case WM_SIZE:
            AdjustToolBar (hwnd);
            AdjustStatusBar (hwnd);
            GetClientRect (hwnd, &rect);
            rect.top += ToolBarHeight (hwnd);
            rect.bottom -= StatusBarHeight (hwnd);
            SetWindowPos (hwndClient, NULL, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, SWP_NOZORDER);
            break;

        case WM_CHAR:
            switch (wParam) {
                case VK_F10:
                    wParam = VK_MENU;
                    return DefWindowProc (hwnd, msg, wParam, lParam);
                    break;
            }
            break;

        case WM_PARENTNOTIFY:
            wmEvent = wParam; 
            point.x = (int)LOWORD(lParam);
            point.y = (int)HIWORD(lParam);

            ClientToScreen (hwnd, &point);
            wmhWnd  = WindowFromPoint(point);
            if (wmhWnd) {
                wmId = GetWindowLongPtr (wmhWnd, GWLP_ID);
                        } else {
                                break;
                        }
            switch (wmEvent) {
                case WM_LBUTTONDOWN:
                case WM_MBUTTONDOWN:
                case WM_RBUTTONDOWN:
                    if (!LoadString (hInst, (UINT)wmId, szMsg, sizeof(szMsg))) {
                        _snprintf ((LPSTR)szMsg, sizeof(szMsg), "Unable to load ParentNotify string #%u", wmId);
                    }
                    SetWindowText (hwndMenuField, szMsg);
                    break;
            }
            break;

        case WM_COMMAND:
            wmId = LOWORD(wParam);
            wmEvent = HIWORD(wParam);
            switch (wmId) {
                case ID_CREATEPARAM:

                    switch (wmEvent) {
                        case CBN_SETFOCUS: //Indicates that the combo box has received input focus.
                        case CBN_DROPDOWN: //Informs the owner of the combo box that its list box is about to be dropped down.
                            if (!LoadString (hInst, (UINT) wmId, szMsg, sizeof(szMsg))) {
                                _snprintf ((LPSTR)szMsg, sizeof(szMsg), "Unable to load FontName string #%u", wmId);
                            }
                            SetWindowText (hwndMenuField, szMsg);
                            break;

                        case CBN_SELCHANGE: //Sent when the selection has been changed.
                            index = (int)SendMessage (hwndCreateParam, CB_GETCURSEL, 0, 0);
                            if (index != CB_ERR) {
                                SendMessage (hwndCreateParam, CB_GETLBTEXT, index, (LONG_PTR)(LPSTR)szMsg);
                                FillInValue (hwndCreateValue, CFP_BASE+index);
                            } else {
                                _snprintf (szMsg, sizeof(szMsg), "FontName: CB_ERR while retrieving text");
                            }
                            SetWindowText (hwndMenuField, szMsg);
                            break;
                    }
                    break;

                case ID_CREATEVALUE:
                    switch (wmEvent){
                        int iCreateParam;
                        int iParamValue;

                        case CBN_SETFOCUS: //Indicates that the combo box has received input focus.
                        case CBN_DROPDOWN: //Informs the owner of the combo box that its list box is about to be dropped down.
                            if (!LoadString (hInst, (UINT)wmId, szMsg, sizeof(szMsg))) {
                                _snprintf (szMsg, sizeof(szMsg), "Unable to load FontSize string #%u", wmId);
                            }
                            break;

                        case CBN_SELCHANGE: //Sent when the selection has been changed.
                            index = (int)SendMessage (hwndCreateValue, CB_GETCURSEL, 0, 0);
                            bRedraw = FALSE;
                            if (index != CB_ERR) {
                                SendMessage (hwndCreateValue, CB_GETLBTEXT, index, (LONG_PTR)(LPSTR)szMsg);
                                iCreateParam =
                                    (int)SendMessage (hwndCreateParam, CB_GETITEMDATA,
                                        (DWORD_PTR)SendMessage (hwndCreateParam, CB_GETCURSEL, 0, (DWORD_PTR)0),
                                    (DWORD_PTR)0);
                                iParamValue = (int)SendMessage (hwndCreateValue, CB_GETITEMDATA, index, 0);

                                switch (iCreateParam) {
                                    BYTE tmpByte;

                                    case CFP_HEIGHT:
                                        if (lf.lfHeight != iParamValue) {
                                            lf.lfHeight = iParamValue;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_WIDTH:
                                        if (lf.lfWidth != iParamValue) {
                                            lf.lfWidth = iParamValue;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_ESCAPEMENT:
                                        if (lf.lfEscapement != iParamValue) {
                                            lf.lfEscapement= iParamValue;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_ORIENTATION:
                                        if (lf.lfOrientation!= iParamValue) {
                                            lf.lfOrientation= iParamValue;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_WEIGHT:
                                        if (lf.lfWeight != iParamValue) {
                                            lf.lfWeight= iParamValue;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_ITALIC:
                                        if ((int)lf.lfItalic != iParamValue) {
                                            lf.lfItalic = (BYTE)iParamValue;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_UNDERLINE:
                                        if (lf.lfUnderline != (BYTE)iParamValue) {
                                            lf.lfUnderline= (BYTE)iParamValue;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_STRIKEOUT:
                                        if (lf.lfStrikeOut != (BYTE)iParamValue) {
                                            lf.lfStrikeOut= (BYTE)iParamValue;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_CHARSET:
                                        if (lf.lfCharSet != (BYTE)iParamValue) {
                                            lf.lfCharSet= (BYTE)iParamValue;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_OUTPUTPRECISION:
                                        if (lf.lfOutPrecision != (BYTE)iParamValue) {
                                            lf.lfOutPrecision = (BYTE)iParamValue;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_CLIPPRECISION:
                                        if (lf.lfClipPrecision != (BYTE)iParamValue) {
                                            lf.lfClipPrecision = (BYTE)iParamValue;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_QUALITY:
                                        if (lf.lfQuality != (BYTE)iParamValue) {
                                            lf.lfQuality = (BYTE)iParamValue;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_PITCH:
                                        tmpByte = lf.lfPitchAndFamily;
                                        tmpByte &= 0xFC;
                                        tmpByte |= iParamValue;
                                        if (tmpByte != lf.lfPitchAndFamily) {
                                            lf.lfPitchAndFamily = tmpByte;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_FAMILY:
                                        tmpByte = lf.lfPitchAndFamily;
                                        tmpByte &= 0x03;
                                        tmpByte |= iParamValue;
                                        if (tmpByte != lf.lfPitchAndFamily) {
                                            lf.lfPitchAndFamily = tmpByte;
                                            bRedraw = TRUE;
                                        }
                                        break;

                                    case CFP_FACENAME:
                                        if (lstrcmp (lf.lfFaceName, szMsg)!=0) {
                                            if (lstrcmp(lf.lfFaceName, "(none)") == 0) {
                                                lf.lfFaceName[0] = 0;
                                            } else {
                                                _snprintf (lf.lfFaceName, sizeof(lf.lfFaceName)/sizeof(TCHAR), "%s",(LPSTR)szMsg);
                                                bRedraw = TRUE;
                                            }
                                        }
                                        break;
                                }
                            } else {
                                _snprintf (szMsg, sizeof(szMsg), "CreateValue: CB_ERR while retrieving text");
                            }
                            if (bRedraw) {
                                InvalidateRect (hwndClient, NULL, TRUE);
                            }
                            SetWindowText (hwndMenuField, szMsg);
                            break;
                    }
                    break;

                // The Menu Selections
                case IDM_NEW:
                case IDM_OPEN:
                case IDM_CLOSE:
                case IDM_SAVE:
                case IDM_SAVEAS:
                case IDM_PRINT:
                case IDM_PRINTSET:
                    SetWindowText (hwndMenuField, "This command is not yet implemented.");
                    break;

                case IDM_EXIT:
                    DestroyWindow(hwnd);
                    break;

                case IDM_UNDO:
                case IDM_CUT:
                case IDM_COPY:
                case IDM_PASTE:
                case IDM_DELETE:
                case IDM_FIND:
                case IDM_REPLACE:
                    SetWindowText (hwndMenuField, "This command is not yet implemented.");
                    break;


                                case ID_ZOOM:
                                        if (bZoomed) {
                        SetWindowLongPtr (hwndClient, GWLP_WNDPROC, (LONG_PTR)fpCharSetProc);
                        bZoomed = FALSE;
                    } else {
                        SetWindowLongPtr (hwndClient, GWLP_WNDPROC, (LONG_PTR)fpGlyphProc);
                        bZoomed = TRUE;
                    }
                    InvalidateRect (hwndClient, NULL, TRUE);
                    break;

                case IDM_CHARSET: // Display the full characater set
                    SetWindowLongPtr (hwndClient, GWLP_WNDPROC, (LONG_PTR)fpCharSetProc);
                    InvalidateRect (hwndClient, NULL, TRUE);
                    bZoomed = FALSE;
                    break;

                case IDM_GLYPH: // Display a single glyph from the font
                    SetWindowLongPtr (hwndClient, GWLP_WNDPROC, (LONG_PTR)fpGlyphProc);
                    InvalidateRect (hwndClient, NULL, TRUE);
                    bZoomed = TRUE;
                    break;

                    break;

                case IDM_TOOLBAR: // This would hide the tool bar
                    SetWindowText (hwndMenuField, "This command is not yet implemented.");
                    break;

                case IDM_STATUSBAR: // This would hide the status bar
                    SetWindowText (hwndMenuField, "This command is not yet implemented.");
                    break;

                case IDM_CREATEFONT:
                    lpDlgFunc = MakeProcInstance((FARPROC) CreateDlgProc, hInst);
                    DialogBoxParam(hInst, "CreateFont", hwnd, (DLGPROC)lpDlgFunc, (DWORD_PTR)(LPLOGFONT)&lf);
                    FreeProcInstance(lpDlgFunc);
                    index = (int)SendMessage (hwndCreateParam, CB_GETCURSEL, 0, 0);
                    if (index != CB_ERR) {
                        FillInValue (hwndCreateValue, CFP_BASE+index);
                    } else {
                        _snprintf (szMsg, sizeof(szMsg), "CreateFont: CB_ERR while setting values");
                    }
                    InvalidateRect (hwndClient, NULL, TRUE);

                    break;

                case IDM_TEXTMETRIC:
                    lpDlgFunc = MakeProcInstance((FARPROC) MetricsDlgProc, hInst);
                    DialogBoxParam(hInst, "TextMetric", hwnd, (DLGPROC)lpDlgFunc, (DWORD_PTR)(LPLOGFONT)&lf);
                    FreeProcInstance(lpDlgFunc);
                    index = (int)SendMessage (hwndCreateParam, CB_GETCURSEL, 0, 0);
                    if (index != CB_ERR) {
                        FillInValue (hwndCreateValue, CFP_BASE+index);
                    } else {
                        _snprintf (szMsg, sizeof(szMsg), "CreateFont: CB_ERR while setting values");
                    }
                    InvalidateRect (hwndClient, NULL, TRUE);
                    break;

                case IDM_ENUMFONTS:
                    lpDlgFunc = MakeProcInstance((FARPROC) EnumDlgProc, hInst);
                    DialogBoxParam(hInst, "EnumFonts", hwnd, (DLGPROC)lpDlgFunc, (DWORD_PTR)(LPLOGFONT)&lf);
                    FreeProcInstance(lpDlgFunc);
                    index = (int)SendMessage (hwndCreateParam, CB_GETCURSEL, 0, 0);
                    if (index != CB_ERR) {
                        FillInValue (hwndCreateValue, CFP_BASE+index);
                    } else {
                        _snprintf (szMsg, sizeof(szMsg), "CreateFont: CB_ERR while setting values");
                    }
                    InvalidateRect (hwndClient, NULL, TRUE);
                    break;

                case IDM_OUTLINEMETRICS:
                    SetWindowText (hwndMenuField, "This command is not yet implemented.");
                    break;

                case IDM_HELP_CONTENTS:
                    WinHelp (hwnd, "FontView.HLP", HELP_KEY, (DWORD_PTR)(LPSTR)"CONTENTS");
                    break;
                case IDM_HELP_INDEX:
                    WinHelp (hwnd, "FontView.HLP", HELP_KEY, (DWORD_PTR)(LPSTR)"INDEX");
                    break;
                case IDM_HELP_OVERVIEW:
                    WinHelp (hwnd, "FontView.HLP", HELP_KEY, (DWORD_PTR)(LPSTR)"OVERVIEW");
                    break;
                case IDM_HELP_GLOSSARY:
                    WinHelp (hwnd, "FontView.HLP", HELP_KEY, (DWORD_PTR)(LPSTR)"GLOSSARY");
                    break;
                case IDM_HELP_TUTORIAL:
                    WinHelp (hwnd, "FontView.HLP", HELP_KEY, (DWORD_PTR)(LPSTR)"TUTORIAL");
                    break;
                case IDM_HELP_DEMO:
                    WinHelp (hwnd, "FontView.HLP", HELP_KEY, (DWORD_PTR)(LPSTR)"DEMO");
                    break;
                case IDM_HELP_HELP:
                    WinHelp (hwnd, "FontView.HLP", HELP_KEY, (DWORD_PTR)(LPSTR)"HELP");
                    break;

                case IDM_ABOUT:
                    lpDlgFunc = MakeProcInstance((FARPROC) SimpleDlgProc, hInst);
                    DialogBox(hInst,
                        (wmId==IDM_ABOUT)?"FONTVIEW":"UsageBox",
                        hwnd,
                        (DLGPROC)lpDlgFunc);
                    FreeProcInstance(lpDlgFunc);
                    break;



            }
            break;

    case WM_PAINT:
        hdc = BeginPaint (hwnd, &ps);
        EndPaint (hwnd, &ps);
        break;

    case WM_MENUSELECT:
        /* A menu item is hilited, get description text for status bar */
        tmp = idMenuSelect;

        wmMenuCmd = LOWORD(wParam);
        wmFlags = HIWORD(wParam);
        wmhMenu = (HMENU)lParam;

        if((wmhMenu == 0) && (wmFlags == -1)) {
                tmp = idMenuSelect = 0;
                SetWindowText(hwndMenuField, "Ready...");
        } else if(wmhMenu == 0) {
            /* don't do anything for this */
        } else if(wmFlags & MF_POPUP) {
            if((HMENU)wmMenuCmd == hSysMenuMain)
                    idMenuSelect = IDM_SYSMENU;
            else if((HMENU)wmMenuCmd == hFileMenu)
                    idMenuSelect = IDM_FILE;
            else if((HMENU)wmMenuCmd == hEditMenu)
                    idMenuSelect = IDM_EDIT;
            else if((HMENU)wmMenuCmd == hViewMenu)
                    idMenuSelect = IDM_VIEW;
            else if((HMENU)wmMenuCmd == hMetricsMenu)
                    idMenuSelect = IDM_DIALOG;
            else if((HMENU)wmMenuCmd == hHelpMenu)
                    idMenuSelect = IDM_HELP;
        } else {
            if(wmMenuCmd != 0) {            /* separators have wparam of 0 */
                idMenuSelect = wmMenuCmd;
            }
        }

        if (idMenuSelect != tmp) {
            if (!LoadString ( hInst, (int)idMenuSelect, szMsg, sizeof(szMsg))) {
                _snprintf ((LPSTR)szMsg, sizeof(szMsg), "Unable to load menu string #%u", idMenuSelect);
            }
            SetWindowText (hwndMenuField, szMsg);
        }
        break;

        case WM_QUERYENDSESSION:
            return (MessageBox (GetFocus(), "Exit Application?", szAppTitle,
                MB_ICONQUESTION | MB_YESNO) == IDYES);

        case WM_DESTROY:
            if (hwnd == hwndMain) {
                PostQuitMessage (0);
            }
            break;

        default:
            return DefWindowProc (hwnd, msg, wParam, lParam);
    }
    return 0L;
}

LONG_PTR APIENTRY ClientProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
        default:
            return DefWindowProc (hwnd, msg, wParam, lParam);
    }
}


LONG_PTR APIENTRY ClientCharSetProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInst;
    PAINTSTRUCT ps;
    HFONT hfont, hfontPrev;
    RECT rect;
    HDC hdc;
    int x, y;
    BYTE glyph;

        if (hwnd) {
        hInst = (HINSTANCE)GetWindowLongPtr (hwnd, GWLP_HINSTANCE);
        }
    switch (msg) {
        case WM_PAINT:
            hdc = BeginPaint (hwnd, &ps);
            hfont = CreateFontIndirect (&lf);
            hfontPrev = SelectObject (hdc, hfont);
            GetClientRect (hwnd, &rect);
            DrawAscii (hdc, &rect, 0);
            SelectObject (hdc, hfontPrev);
            DeleteObject (hfont);
            EndPaint (hwnd, &ps);
            break;

        case WM_LBUTTONDBLCLK:
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            //OutputDebugString ("WM_LBUTTONDOWN\n\r");
            hdc = GetWindowDC (hwnd);
            hfont = CreateFontIndirect (&lf);
            hfontPrev = SelectObject (hdc, hfont);
            GetClientRect (hwnd, &rect);

            glyph = FindChar (hdc, &rect, x, y);
            if (glyph) {
                SetWindowLongPtr (hwndClient, GWLP_WNDPROC, (LONG_PTR)fpGlyphProc);
                bZoomed = TRUE;
                SendMessage (hwndClient, WM_USER, (UINT)glyph, 0);
                InvalidateRect (hwndClient, NULL, TRUE);
            }

            SelectObject (hdc, hfontPrev);
            DeleteObject (hfont);
            ReleaseDC (hwnd, hdc);
            break;


        default:
            return DefWindowProc (hwnd, msg, wParam, lParam);
    }
    return 0L;
}

LONG_PTR APIENTRY ClientGlyphProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInst;
    PAINTSTRUCT ps;
    HFONT hfont, hfontPrev;
    RECT rect;
    HDC hdc;
    TEXTMETRIC tm;
    static BYTE glyph = 'A';

        if (hwnd) {
        hInst = (HINSTANCE)GetWindowLongPtr (hwnd, GWLP_HINSTANCE);
        }

    switch (msg) {
        case WM_LBUTTONDBLCLK:
        case WM_LBUTTONDOWN:
            glyph--;
            InvalidateRect (hwnd, NULL, TRUE);
            break;

        case WM_RBUTTONDBLCLK:
        case WM_RBUTTONDOWN:
            glyph++;
            InvalidateRect (hwnd, NULL, TRUE);
            break;

        case WM_USER:
            glyph = (BYTE)wParam;
            break;

        case WM_PAINT:
            hdc = BeginPaint (hwnd, &ps);
            hfont = CreateFontIndirect (&lf);
            hfontPrev = SelectObject (hdc, hfont);
            GetClientRect (hwnd, &rect);

            GetTextMetrics (hdc, &tm);
            if (glyph < tm.tmFirstChar) {
                MessageBeep (0);
                glyph = tm.tmFirstChar;
            }
            if (glyph > tm.tmLastChar) {
                MessageBeep(0);
                glyph = tm.tmLastChar;
            }

            DrawGlyph (hdc, &rect, glyph, hfont);
            SelectObject (hdc, hfontPrev);
            DeleteObject (hfont);
            EndPaint (hwnd, &ps);
            break;

        default:
            return DefWindowProc (hwnd, msg, wParam, lParam);
    }
    return 0L;
}
