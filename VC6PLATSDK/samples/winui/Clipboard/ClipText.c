
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1993 - 2000 Microsoft Corp.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/****************************************************************************

    PROGRAM: Cliptext.c

    PURPOSE: Demonstrates copying text to and from the clipboard

    FUNCTIONS:

        WinMain() - calls initialization function, processes message loop
        InitApplication() - initializes window data and registers window
        InitInstance() - saves instance handle and creates main window
        MainWndProc() - processes messages
        About() - processes messages for "About" dialog box
        OutOfMemory() - displays warning message

****************************************************************************/

#include "cliptext.h"
#include <string.h>

HINSTANCE hInst;
HACCEL hAccTable;
HWND   hwnd;

HANDLE hText = NULL;

TCHAR szInitialClientAreaText[] = 
   TEXT("This program demonstrates the use of the Edit menu to copy and ")
   TEXT("paste text to and from the clipboard.  Try using the Copy command ")
   TEXT("to move this text to the clipboard, and the Paste command to replace ")
   TEXT("this text with data from another application.  \r\n\r\n")
   TEXT("You might want to try running Notepad and Clipbrd alongside this ")
   TEXT("application so that you can watch the data exchanges take place.  ");

HANDLE hData;                            /* handles to clip data  */
LPTSTR lpData;                           /* pointers to clip data */

/* functions declared here, because of MIPS lack of passing C_DEFINES*/
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, INT);
LRESULT APIENTRY MainWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR APIENTRY About(HWND, UINT, WPARAM, LPARAM);
VOID OutOfMemory(VOID);

/****************************************************************************

    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)

    PURPOSE: calls initialization function, processes message loop

****************************************************************************/
int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    MSG msg = {0};
    BOOL bRet = FALSE;
    BOOL bSuccess = TRUE;

    if (!InitApplication(hInstance))
    {
        bSuccess = FALSE;
        goto exit_func;
    }

    if (!InitInstance(hInstance, nCmdShow))
    {
        bSuccess = FALSE;
        goto exit_func;
    }


    while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
    { 
        if (bRet == -1)
        {
            bSuccess = FALSE;
            goto exit_func;
        }
        else
        {
            /* Only translate message if it is not an accelerator message */
            if (!TranslateAccelerator(hwnd, hAccTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg); 
            }
        }
    }

exit_func:
    if (bSuccess)
    {
        return (int) (msg.wParam);
    }
    else
    {
        return 0;
    }
}


/****************************************************************************

    FUNCTION: InitApplication(HANDLE)

    PURPOSE: Initializes window data and registers window class

****************************************************************************/
BOOL InitApplication(
    HANDLE hInstance)
{
    WNDCLASS  wc = {0};

    wc.lpfnWndProc = (WNDPROC) MainWndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 
    wc.lpszMenuName =  TEXT("CliptextMenu");
    wc.lpszClassName = TEXT("CliptextWClass");

    return (RegisterClass(&wc));
}


/****************************************************************************

    FUNCTION:  InitInstance(HANDLE, int)

    PURPOSE:  Saves instance handle and creates main window

****************************************************************************/
BOOL InitInstance(
    HINSTANCE hInstance, 
    INT nCmdShow)
{
    LPTSTR lpszText = NULL;
    BOOL bSuccess = TRUE;

    hInst = hInstance;

    hAccTable = LoadAccelerators(hInst, TEXT("ClipTextAcc"));

    if (!(hText 
          = GlobalAlloc(GMEM_MOVEABLE,(DWORD)sizeof(szInitialClientAreaText)))) 
    {
        OutOfMemory();
        bSuccess = FALSE;
        goto exit_func;
    }
      
    if (!(lpszText = GlobalLock(hText))) 
    {
        OutOfMemory();
        bSuccess = FALSE;
        goto exit_func;
    }

    lstrcpyn(lpszText, szInitialClientAreaText, 
             sizeof(szInitialClientAreaText)/sizeof(szInitialClientAreaText[0]) - 1);
    GlobalUnlock(hText);

    hwnd = CreateWindow(
        TEXT("CliptextWClass"),
        TEXT("Cliptext Sample Application"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0,
        CW_USEDEFAULT, 0,
        NULL, NULL, hInstance, NULL );

    if (!hwnd)
    {
        bSuccess = FALSE;
        goto exit_func;
    }

    ShowWindow(hwnd, nCmdShow);
    bSuccess = UpdateWindow(hwnd);

exit_func:    
    return bSuccess;
}

/****************************************************************************

    FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)

    PURPOSE:  Processes messages

    MESSAGES:

        WM_COMMAND    - message from menu
        WM_INITMENU   - initialize menu
        WM_PAINT      - update window
        WM_DESTROY    - destroy window

    COMMENTS:

        WM_INITMENU - when this message is received, the application checks
        to see if there is any text data in the clipboard, and enables or
        disables the Paste menu item accordingly.

        Seclecting the Copy menu item will send the text "Hello Windows" to
        the clipboard.

        Seclecting the Paste menu item will copy whatever text is in the
        clipboard to the application window.

****************************************************************************/
LRESULT APIENTRY MainWndProc(
    HWND hWnd, 
    UINT message, 
    WPARAM wParam, 
    LPARAM lParam)
{
    HDC         hDC         = NULL;
    PAINTSTRUCT ps          = {0};
    RECT        rectClient  = {0};
    LPTSTR      lpszText    = NULL;
    HANDLE      hClipData   = NULL;  /* handles to clip data  */
    LPTSTR      lpClipData  = NULL;  /* pointers to clip data */


    switch (message) 
    {
        case WM_INITMENU:
            if (wParam == (WPARAM)GetMenu(hWnd)) 
            {
    			if (OpenClipboard(hWnd)) 
    			{
#ifdef UNICODE
                    if (IsClipboardFormatAvailable(CF_UNICODETEXT))
#else
                    if (IsClipboardFormatAvailable(CF_TEXT) || IsClipboardFormatAvailable(CF_OEMTEXT))
#endif // UNICODE
                    {
                        EnableMenuItem((HMENU)wParam, IDM_PASTE, MF_ENABLED);
                    }
			        else
			        {
                        EnableMenuItem((HMENU)wParam, IDM_PASTE, MF_GRAYED);
			        }
                    CloseClipboard();
                	return (TRUE);
                }
                else                           /* Clipboard is not available */
                {
                    return (FALSE);
                }
            }
            return (TRUE);

        case WM_COMMAND:
            switch(LOWORD(wParam)) 
            {
                case IDM_ABOUT:
                    DialogBox(hInst, TEXT("AboutBox"), hWnd, About);
                    break;

                    /* file menu commands */

                case IDM_NEW:    /* fall-through */
                case IDM_OPEN:   /* fall-through */
                case IDM_SAVE:   /* fall-through */
                case IDM_SAVEAS: /* fall-through */
                case IDM_PRINT:
                    MessageBox (GetFocus (),
                                TEXT("Command not implemented."),
                                TEXT("ClipText Sample Application"),
                                MB_ICONASTERISK | MB_OK );
                    break;  

                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;

                /* edit menu commands */
                case IDM_UNDO:  /* fall-through */
                case IDM_CLEAR:
                    MessageBox (GetFocus (),
                                TEXT("Command not implemented."),
                                TEXT("ClipText Sample Application"),
                                MB_ICONASTERISK | MB_OK);
                    break;  

                case IDM_CUT:  /* fall-through */
                case IDM_COPY:
                    if (hText != NULL) 
                    {
                        /* Allocate memory and copy the string to it */
                        if (!(hData 
                             = GlobalAlloc(GMEM_DDESHARE, GlobalSize (hText)))) 
                        {
                            OutOfMemory();
                            return (TRUE);
                        }
                        if (!(lpData = GlobalLock(hData))) 
                        {
                            OutOfMemory();
                            return (TRUE);
                        }
                        if (!(lpszText = GlobalLock (hText))) 
                        {
                            OutOfMemory();
                            return (TRUE);
                        }
                        lstrcpyn(lpData, lpszText, (int)GlobalSize (hText));
                        GlobalUnlock(hData);
                        GlobalUnlock (hText);

                        /* Clear the current contents of the clipboard, and set
                         * the data handle to the new string.
                         */
                        if (OpenClipboard(hWnd)) 
                        {
                            EmptyClipboard();
#ifdef UNICODE
                            SetClipboardData(CF_UNICODETEXT, hData);
#else
                            SetClipboardData(CF_TEXT, hData);
#endif // UNICODE
                            CloseClipboard();
                        }
                        hData = NULL;

                        if (LOWORD(wParam) == IDM_CUT) 
                        {
                            GlobalFree (hText);
                            hText = NULL;
                            EnableMenuItem(GetMenu (hWnd), IDM_CUT, MF_GRAYED);
                            EnableMenuItem(GetMenu(hWnd), IDM_COPY, MF_GRAYED);
                            InvalidateRect (hWnd, NULL, TRUE);
                            UpdateWindow (hWnd);
                        }
                    }
                    return (TRUE);

                case IDM_PASTE:
                    if (OpenClipboard(hWnd)) 
                    {
                        /* get text from the clipboard */
#ifdef UNICODE
                        if (!(hClipData = GetClipboardData(CF_UNICODETEXT))) 
#else
                        if (!(hClipData = GetClipboardData(CF_TEXT))) 
#endif // !UNICODE
                        {
                            CloseClipboard();
                            break;
                        }

                        if (hText != NULL) 
                        {
                            GlobalFree(hText);
                        }

                        if (!(hText = GlobalAlloc(GMEM_MOVEABLE, GlobalSize(hClipData)))) 
                        {
                            OutOfMemory();
                            CloseClipboard();
                            break;
                        }
                        
                        if (!(lpClipData = GlobalLock(hClipData))) 
                        {
                            OutOfMemory();
                            CloseClipboard();
                            break;
                        }
                        
                        if (!(lpszText = GlobalLock(hText))) 
                        {
                            OutOfMemory();
                            CloseClipboard();
                            break;
                        }
                        
                        lstrcpyn(lpszText, lpClipData, (int)GlobalSize(hClipData));
                        GlobalUnlock(hClipData);
                        CloseClipboard();
                        GlobalUnlock(hText);
                        EnableMenuItem(GetMenu(hWnd), IDM_CUT, MF_ENABLED);
                        EnableMenuItem(GetMenu(hWnd), IDM_COPY, MF_ENABLED);

                        /* copy text to the application window */

                        InvalidateRect(hWnd, NULL, TRUE);
                        UpdateWindow(hWnd);
                        return (TRUE);
                    }
                    else
                    {
                        return (FALSE);
                    }
                }
                break;

            case WM_SIZE:
                InvalidateRect(hWnd, NULL, TRUE);
                break;

            case WM_PAINT:
                hDC = BeginPaint (hWnd, &ps);
                if (hText != NULL) 
                {
                    if (!(lpszText = GlobalLock (hText))) 
                    {
                        OutOfMemory();
                    } 
                    else 
                    {
                        GetClientRect (hWnd, &rectClient);
                        DrawText (hDC, lpszText, -1, &rectClient, 
                                  DT_EXTERNALLEADING | DT_NOPREFIX | DT_WORDBREAK);
                        GlobalUnlock (hText);
                    }
                }
                EndPaint (hWnd, &ps);
                break;

            case WM_DESTROY:
                PostQuitMessage(0);
                break;

            default:
                return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return (0);
}


/****************************************************************************

    FUNCTION: About(HWND, unsigned, WORD, LONG)

    PURPOSE:  Processes messages for "About" dialog box

    MESSAGES:

        WM_INITDIALOG - initialize dialog box
        WM_COMMAND    - Input received

****************************************************************************/
INT_PTR APIENTRY About( 
    HWND hDlg, 
    UINT message, 
    WPARAM wParam, 
    LPARAM lParam)
{
    BOOL bRet = FALSE;
    
    switch (message) 
    {
        case WM_INITDIALOG:
            bRet = TRUE;
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK ||
                LOWORD(wParam) == IDCANCEL) 
            {
                EndDialog(hDlg, TRUE);
                bRet = TRUE;
            }
            break;
    }

    return (INT_PTR)bRet;
}


/****************************************************************************

    FUNCTION: OutOfMemory(void)

    PURPOSE:  Displays warning message

****************************************************************************/
VOID OutOfMemory()
{
    MessageBox(
        GetFocus(),
        TEXT("Out of Memory"),
        NULL,
        MB_ICONHAND | MB_SYSTEMMODAL);
    return;
}
