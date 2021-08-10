/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1993 - 2000 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#include <windows.h>
#include "dyndlg.h"

LRESULT CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About (HWND, UINT, WPARAM, LPARAM );

DWORD Create1 (HWND);
DWORD Create2 (HWND);

WORD* lpwAlign (WORD*);
int nCopyAnsiToWideChar (WORD*, PTSTR);

HINSTANCE ghInst;


/**************************************************************************\
*
*  function:  WinMain ()
*
*  input parameters:  c.f. generic sample
*
\**************************************************************************/
int WINAPI WinMain (
    HINSTANCE hInstance, 
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, 
    int nCmdShow )
{
    HWND      hwnd     = NULL;
    MSG       msg      = {0};
    HANDLE    hLibrary = NULL;
    WNDCLASS  wc       = {0};
    BOOL      bSuccess = TRUE;
    BOOL      bRet     = FALSE;

    ghInst = hInstance;


    wc.lpfnWndProc   = (WNDPROC)MainWndProc;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(hInstance, TEXT("dyndlgIcon"));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(LTGRAY_BRUSH);
    wc.lpszMenuName  = TEXT("dyndlgMenu");
    wc.lpszClassName = TEXT("dyndlg");

    if (0 == RegisterClass(&wc)) 
    {
        bSuccess = FALSE;
        goto exit_func;
    }


    /* Create the main window.  Return false if CreateWindow() fails */
    hwnd = CreateWindow(
        TEXT("dyndlg"),
        TEXT("DynDlg"),
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,
        CW_USEDEFAULT, 0,
        CW_USEDEFAULT, 0,
        NULL, NULL, hInstance, NULL);

    if (NULL == hwnd) 
    {
        bSuccess = FALSE;
        goto exit_func;
    }


    /*
     * Load SPINCUBE.DLL containing the custom control.
     * The above library should be present in the current directory
     *
     * Generally it is better to pass an absolute path to LoadLibrary.
     * Otherwise the API might attempt to load a DLL from the current PATH,
     * which presents a potential security breach. Refer to MSDN
     * for the documentation on the SearchPath function for the search
     * strategy used by the operating system.
     */
    hLibrary = LoadLibrary (TEXT("SPINCUBE.DLL"));

    if (NULL == hLibrary)
    {
        if (PRIMARYLANGID(GetUserDefaultLangID ()) == LANG_JAPANESE)
        {
            MessageBox (hwnd, TEXT("LoadLibrary (SPINCUBE.DLL) が失敗しました。"),
                        TEXT("エラー, このアプリケーションは spincube が必要です"), 
                        MB_OK | MB_ICONEXCLAMATION);
        }
        else
        {
            MessageBox (hwnd, TEXT("LoadLibrary (SPINCUBE.DLL) failed"),
                        TEXT("Error, this app requires spincube."), 
                        MB_OK | MB_ICONEXCLAMATION);
        }
    }


    /* Demo: Just for fun, start out with one of the dialogs created. */
    PostMessage (hwnd, WM_COMMAND, IDM_DIALOG2, 0);


    ShowWindow (hwnd, SW_SHOWNORMAL);
    UpdateWindow (hwnd);
    

    /* Loop getting messages and dispatching them. */
    while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
    { 
        if (bRet == -1)
        {
            bSuccess = FALSE;
            goto exit_func;
        }
        else
        {
            TranslateMessage(&msg); 
            DispatchMessage(&msg); 
        }
    }


    if (NULL != hLibrary) 
    {
        bSuccess = FreeLibrary (hLibrary);
    }


exit_func:
    if (TRUE == bSuccess)
    {
        return (int)(msg.wParam);
    }
    else
    {
        return 0;
    }
}


/***************************************************************************\
*    FUNCTION: MainWndProc
\***************************************************************************/
LRESULT CALLBACK MainWndProc (
    HWND hwnd, 
    UINT message, 
    WPARAM wParam, 
    LPARAM lParam ) 
{
    BOOL bRetDWP = TRUE;

    switch (message) 
    {
        /**********************************************************************\
        *  Menu item support.
        *
        \**********************************************************************/
        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            {
                case IDM_EXIT:
                    PostQuitMessage (0);
                    break;
                
                case IDM_DIALOG1:
                    Create1 (hwnd);
                    break;

                case IDM_DIALOG2:
                    Create2 (hwnd);
                    break;

                case IDM_HELP:
                    WinHelp (hwnd, TEXT("dyndlg.hlp"), HELP_INDEX, 0L);
                    break;

                case IDM_ABOUT:
                    DialogBox (GetModuleHandle(NULL), TEXT("aboutBox"), hwnd, (DLGPROC)About);
                    bRetDWP = FALSE;
                    break;
            }  
            break;  /* end wm_command */

        case WM_DESTROY:
            WinHelp ( hwnd,  TEXT("dyndlg.hlp"), (UINT) HELP_QUIT, 0L );
            PostQuitMessage (0);
            break;
    } 


    if (bRetDWP)
    {
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    else
    {
        return 0;
    }
}


/****************************************************************************
    FUNCTION: About
****************************************************************************/
LRESULT CALLBACK About (
    HWND hwnd, 
    UINT message, 
    WPARAM wParam, 
    LPARAM lParam)
{
    BOOL bRet = FALSE;


    if (message == WM_INITDIALOG)
    {
        bRet = TRUE;
    }

    if ((message == WM_COMMAND) && (LOWORD(wParam) == IDOK)) 
    {
        EndDialog (hwnd, TRUE);
        bRet = TRUE;
    }

    if ((message == WM_SYSCOMMAND) && (wParam == SC_CLOSE)) 
    {
        EndDialog (hwnd, TRUE);
        bRet = TRUE;
    }


    return (LRESULT)bRet;
}




/****************************************************************************
    Create the first dialog dynamically.  Notice that we are NOT using
    structures here because too many of the fields are of variable length.
    Instead, just allocate some memory to play with, and start filling in
    the data at that pointer.

    p - pointer which is moved down through the DLGTEMPLATE information.
    pdlgtemplate - pointer to the TOP of the DLGTEMPLATE information.

    Here we create a simple dialog with one item.  The dialog has a title,
    the item has text, and the item class is specified by ordinal.  There
    is no font information.

    In case of error the function returns the error code obtained by calling
    GetLastError. Otherwise the function returns ERROR_SUCCESS
****************************************************************************/
DWORD Create1 (
    HWND hwnd )
{
    WORD*   p = NULL;
    WORD*   pdlgtemplate = NULL;
    int     nchar;
    DWORD   lStyle;
    INT_PTR pSize = 1000;
    DWORD   error = ERROR_SUCCESS;


    /* allocate some memory to play with  */
    p = (PWORD) LocalAlloc (LPTR, pSize);
    if (NULL == p)
    {
        error = GetLastError ();
        goto exit_func;
    }

    pdlgtemplate = p;


    /* start to fill in the dlgtemplate information.  addressing by WORDs */
    lStyle = DS_MODALFRAME | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;

    *p++ = LOWORD (lStyle);
    *p++ = HIWORD (lStyle);
    *p++ = 0;          // LOWORD (lExtendedStyle)
    *p++ = 0;          // HIWORD (lExtendedStyle)
    *p++ = 1;          // NumberOfItems
    *p++ = 10;         // x
    *p++ = 10;         // y
    *p++ = 100;        // cx
    *p++ = 100;        // cy
    *p++ = 0;          // Menu
    *p++ = 0;          // Class

  
    pSize -= (p - pdlgtemplate);
    pSize /= 2;
  
    /* copy the title of the dialog */
    if (PRIMARYLANGID(GetUserDefaultLangID ()) == LANG_JAPANESE)
    {
        nchar = nCopyAnsiToWideChar (p, TEXT("タイトル 1"));
    }
    else
    {
        nchar = nCopyAnsiToWideChar (p, TEXT("Title 1"));
    }
    p += nchar;


    /* add in the wPointSize and szFontName here iff the DS_SETFONT bit on */
    /* make sure the first item starts on a DWORD boundary */
    p = lpwAlign (p);


    /* now start with the first item */
    lStyle = BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD;

    *p++ = LOWORD (lStyle);
    *p++ = HIWORD (lStyle);
    *p++ = 0;          // LOWORD (lExtendedStyle)
    *p++ = 0;          // HIWORD (lExtendedStyle)
    *p++ = 10;         // x
    *p++ = 70;         // y
    *p++ = 80;         // cx
    *p++ = 20;         // cy
    *p++ = IDOK;       // ID

    /* fill in class i.d. Button in this case */
    *p++ = (WORD)0xffff;
    *p++ = (WORD)0x0080;

    /* copy the text of the first item */
    nchar = nCopyAnsiToWideChar (p, TEXT("OK"));
    p += nchar;

    *p++ = 0;  // advance pointer over nExtraStuff WORD

    if (NULL == CreateDialogIndirect (ghInst, (LPDLGTEMPLATE) pdlgtemplate, hwnd, (DLGPROC) About))
    {
        error = GetLastError ();
    }

    if (NULL != LocalFree (pdlgtemplate))
    {
        error = GetLastError ();
        DebugBreak ();
    }
    

exit_func:
    return error;
}




/****************************************************************************
    Create the second dialog dynamically.

    Here we create a dialog which has font information (DS_SETFONT),
    and which has two items with the item class specified by name.

    In case of error the function returns the error code obtained by calling
    GetLastError. Otherwise the function returns ERROR_SUCCESS
****************************************************************************/
DWORD Create2 (
    HWND hwnd )
{
    WORD* p = NULL;
    WORD* pdlgtemplate = NULL;
    int   nchar;
    DWORD lStyle;
    DWORD error = ERROR_SUCCESS;

    /* allocate some memory to play with  */
    p = (PWORD) LocalAlloc (LPTR, 1000);
    if (NULL == p)
    {
        error = GetLastError ();
        DebugBreak ();
        goto exit_func;
    }
    pdlgtemplate = p;


    /* start to fill in the dlgtemplate information.  addressing by WORDs */
    lStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | DS_SETFONT;
    *p++ = LOWORD (lStyle);
    *p++ = HIWORD (lStyle);
    *p++ = 0;          // LOWORD (lExtendedStyle)
    *p++ = 0;          // HIWORD (lExtendedStyle)
    *p++ = 2;          // NumberOfItems
    *p++ = 210;        // x
    *p++ = 10;         // y
    *p++ = 100;        // cx
    *p++ = 100;        // cy
    *p++ = 0;          // Menu
    *p++ = 0;          // Class


    /* copy the title of the dialog */
    if (PRIMARYLANGID(GetUserDefaultLangID ()) == LANG_JAPANESE)
    {
        nchar = nCopyAnsiToWideChar (p, TEXT("タイトル 2"));
    }
    else
    {
        nchar = nCopyAnsiToWideChar (p, TEXT("Title 2"));
    }
    p += nchar;

    /* Font information because of DS_SETFONT */
    *p++ = 18;     // point size
    nchar = nCopyAnsiToWideChar (p, TEXT("Times New Roman"));  // Face name
    p += nchar;


    /* make sure the first item starts on a DWORD boundary */
    p = lpwAlign (p);

    /* now start with the first item */
    lStyle = BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP;
    *p++ = LOWORD (lStyle);
    *p++ = HIWORD (lStyle);
    *p++ = 0;          // LOWORD (lExtendedStyle)
    *p++ = 0;          // HIWORD (lExtendedStyle)
    *p++ = 10;         // x
    *p++ = 60;         // y
    *p++ = 80;         // cx
    *p++ = 20;         // cy
    *p++ = IDOK;       // ID


    /* fill in class i.d., this time by name */
    nchar = nCopyAnsiToWideChar (p, TEXT("BUTTON"));
    p += nchar;


    /* copy the text of the first item */
    nchar = nCopyAnsiToWideChar (p, TEXT("OK"));
    p += nchar;

    *p++ = 0;  // advance pointer over nExtraStuff WORD

    /* make sure the second item starts on a DWORD boundary */
    p = lpwAlign (p);

#define SS_INMOTION 0x0002  /* from spincube.h */
    lStyle = WS_VISIBLE | WS_CHILD | SS_INMOTION;
    *p++ = LOWORD (lStyle);
    *p++ = HIWORD (lStyle);
    *p++ = 0;          // LOWORD (lExtendedStyle)
    *p++ = 0;          // HIWORD (lExtendedStyle)
    *p++ = 20;         // x
    *p++ = 5;          // y
    *p++ = 65;         // cx
    *p++ = 45;         // cy
    *p++ = 57;         // ID


    /* fill in class i.d., this time by name */

    /***** CUSTOM CONTROL
    * Fill in the class name that is specified in the DLL
    *  See the \q_a\samples\spincube sample for the source to this.
    *****/
    nchar = nCopyAnsiToWideChar (p, TEXT("Spincube"));
    p += nchar;

    /* copy the text of the second item, null terminate the string. */
    nchar = nCopyAnsiToWideChar (p, TEXT(""));
    p += nchar;

    *p++ = 0;  // advance pointer over nExtraStuff WORD

    if (NULL == CreateDialogIndirect (ghInst, (LPDLGTEMPLATE) pdlgtemplate, hwnd, (DLGPROC) About))
    {
        error = GetLastError ();
    }

    if (NULL != LocalFree (pdlgtemplate))
    {
        error = GetLastError ();
        DebugBreak ();
    }

exit_func:
    return error;
}




/****************************************************************************
    Helper routine.  Take an input pointer, return closest
     pointer that is aligned on a DWORD (4 byte) boundary.
****************************************************************************/
WORD* lpwAlign ( 
    WORD* pIn )
{
    DWORD_PTR ul;

    ul = (DWORD_PTR) pIn;
    ul +=3;
    ul >>=2;
    ul <<=2;
    return (WORD*) ul;
}



/****************************************************************************
    Helper routine.  Takes second parameter as Ansi string, copies
     it to first parameter as wide character (16-bits / char) string,
     and returns integer number of wide characters (words) in string
     (including the trailing wide char NULL).
****************************************************************************/
int nCopyAnsiToWideChar (
    WORD* pWCStr, 
    PTSTR pAnsiIn )
{
#ifdef UNICODE
    return lstrlen(lstrcpy(pWCStr, pAnsiIn)) + 1;
#else
    int cchAnsi = lstrlen(pAnsiIn);
    return MultiByteToWideChar(GetACP(), MB_PRECOMPOSED, 
                               pAnsiIn, cchAnsi, pWCStr, cchAnsi) + 1;
#endif
}
