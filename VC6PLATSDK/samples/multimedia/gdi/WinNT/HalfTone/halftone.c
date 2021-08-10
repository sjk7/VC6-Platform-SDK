/*****************************************************************************\
*       
*       THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
*       ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED 
*       TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
*       PARTICULAR PURPOSE.                                              
*                                                                        
*       Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved. 
*                                                                        
\*****************************************************************************/

/*****************************************************************************
 *                                                                           *
 *   PROGRAM: HalfTone.c                                                     *
 *                                                                           *
 *   PURPOSE: Demonstrate halftone stretching capabilities of Windows NT     *
 *                                                                           *
 *   FUNCTIONS:                                                              *
 *                                                                           *
 *   GetLastErrorBox() - Report GetLastError() values as text                *
 *   WinMain() - calls initialization function, processes message loop       *
 *   InitApplication() - initializes window data and registers window        *
 *   InitInstance() - saves instance handle and creates main window          *
 *   WndProc() - processes messages                                          *
 *   CenterWindow() - used to center the "About" box over application window *
 *   About() - processes messages for "About" dialog box                     *
 *                                                                           *
 *****************************************************************************/

#include <windows.h>   // required for all Windows applications
#include <commctrl.h>
#include <commdlg.h>
#include <strsafe.h>
#include "resource.h"   // specific to this program

HINSTANCE hInst;          // current instance
HICON hIcon = NULL;
HANDLE ghWnd;
COLORADJUSTMENT caHalf;
HWND hWndMain;

char szAppName[] = "HalfTone";   // The name of this application
char szTitle[]   = "Halftone Stretching Demo"; // The title bar text

BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About  (HWND, UINT, WPARAM, LPARAM);


/*****************************************************************************
 *                                                                           *
 * FUNCTION: WinMain(HINSTANCE, HINSTANCE, LPSTR, int)                       *
 *                                                                           *
 * PURPOSE: calls initialization function, processes message loop            *
 *                                                                           *
 * COMMENTS:                                                                 *
 *                                                                           *
 *    Windows recognizes this function by name as the initial entry point    *
 *    for the program.  This function calls the application initialization   *
 *    routine, if no other instance of the program is running, and always    *
 *    calls the instance initialization routine.  It then executes a message *
 *    retrieval and dispatch loop that is the top-level control structure    *
 *    for the remainder of execution.  The loop is terminated when a WM_QUIT *
 *    message is received, at which time this function exits the application *
 *    instance by returning the value passed by PostQuitMessage().           *
 *                                                                           *
 *    If this function must abort before entering the message loop, it       *
 *    returns the conventional value NULL.                                   *
 *                                                                           *
 ****************************************************************************/
int APIENTRY WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow)
{       
    MSG msg;
    HANDLE hAccelTable;
    
    if (!hPrevInstance) {       // Other instances of app running?
            if (!InitApplication(hInstance)) { // Initialize shared things
            return (FALSE);     // Exits if unable to initialize
        }
    }

    /* Perform initializations that apply to a specific instance */

    if (!InitInstance(hInstance, nCmdShow)) {
            return (FALSE);
    }

    hAccelTable = LoadAccelerators (hInstance, "HALFTONE");

    /* Acquire and dispatch messages until a WM_QUIT message is received. */

    while (GetMessage(&msg, // message structure
       NULL,   // handle of window receiving the message
       0,      // lowest message to examine
       0))     // highest message to examine
    {
        if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);// Translates virtual key codes
            DispatchMessage(&msg); // Dispatches message to window
        }
    }

    return (msg.wParam); // Returns the value from PostQuitMessage

    UNREFERENCED_PARAMETER(lpCmdLine); // This will prevent 'unused formal parameter' warnings
}


/*****************************************************************************
 *                                                                           *
 *  FUNCTION: InitApplication(HINSTANCE)                                     *
 *                                                                           *
 *  PURPOSE: Initializes window data and registers window class              *
 *                                                                           *
 *  COMMENTS:                                                                *
 *                                                                           *
 *    This function is called at initialization time only if no other        *
 *    instances of the application are running.  This function performs      *
 *    initialization tasks that can be done once for any number of running   *
 *    instances.                                                             *
 *                                                                           *
 *    In this case, we initialize a window class by filling out a data       *
 *    structure of type WNDCLASS and calling the Windows RegisterClass()     *
 *    function.  Since all instances of this application use the same window *
 *    class, we only need to do this when the first instance is initialized. *
 *                                                                           *
 *****************************************************************************/
BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS  wc;

    // Fill in window class structure with parameters that describe the
    // main window.

    wc.style         = CS_VREDRAW | CS_HREDRAW;  // Class style(s).
    wc.lpfnWndProc   = (WNDPROC)WndProc;       // Window Procedure
    wc.cbClsExtra    = 0;                      // No per-class extra data.
    wc.cbWndExtra    = 0;                      // No per-window extra data.
    wc.hInstance     = hInstance;              // Owner of this class
    wc.hIcon         = LoadIcon (hInstance, "HT_ICON"); // Icon name from .RC
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW); // Cursor
    wc.hbrBackground = GetStockObject(NULL_BRUSH);
    wc.lpszMenuName  = "HT_MENU";              // Menu name from .RC
    wc.lpszClassName = szAppName;              // Name to register as

    // Register the window class and return success/failure code.
    return (RegisterClass(&wc));
}


/*****************************************************************************
 *                                                                           *
 *   FUNCTION:  InitInstance(HINSTANCE, int)                                 *
 *                                                                           *
 *   PURPOSE:  Saves instance handle and creates main window                 *
 *                                                                           *
 *   COMMENTS:                                                               *
 *                                                                           *
 *      This function is called at initialization time for every instance of *
 *      this application.  This function performs initialization tasks that  *
 *      cannot be shared by multiple instances.                              *
 *                                                                           *
 *      In this case, we save the instance handle in a static variable and   *
 *      create and display the main program window.                          *
 *                                                                           *
 ****************************************************************************/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND            hWnd; // Main window handle.

    // Save the instance handle in static variable, which will be used in
    // many subsequence calls from this application to Windows.

    hInst = hInstance; // Store instance handle in our global variable

    // Create a main window for this application instance.
    hWndMain = 
    hWnd = CreateWindow(
            szAppName,           // See RegisterClass() call.
            szTitle,             // Text for window title bar.
            WS_OVERLAPPEDWINDOW,// Window style.
            CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, // Use default positioning
            NULL,                // Overlapped windows have no parent.
            NULL,                // Use the window class menu.
            hInstance,           // This instance owns this window.
            NULL                 // We don't use any data in our WM_CREATE
    );

    // If window could not be created, return "failure"
    if (!hWnd) {
            return (FALSE);
    }

    // Make the window visible; update its client area; and return "success"
    ShowWindow(hWnd, nCmdShow); // Show the window
    UpdateWindow(hWnd);         // Sends WM_PAINT message

    return (TRUE);              // We succeeded...

}

#define GetControlScrollPos(hDlg, uBar) SendMessage(GetDlgItem(hDlg, uBar), TBM_GETPOS, (WPARAM)0, (LPARAM)0)
#define SetSliderPos(hSld, iPos) SendMessage(hSld, TBM_SETPOS, (WPARAM)TRUE, (LONG)iPos)

void SetupControls(HWND hDlg, UINT uBar, UINT uEdit, int iMin, int iMax, int iPos, BOOL bScale)
{
    HWND hWndTrack = GetDlgItem(hDlg, uBar);

    if (!hWndTrack) return;

    SendMessage(hWndTrack, TBM_SETRANGE, TRUE, MAKELONG((short)iMin, (short)iMax));
    SendMessage(hWndTrack, TBM_SETTICFREQ, ((iMax-iMin) / 50)+1, (LPARAM)0);

    SetSliderPos(hWndTrack, iPos);

    if (bScale) iPos *=10;

    SetDlgItemInt(hDlg, uEdit, iPos, TRUE);
}

                                      
BOOL CALLBACK HalftoneDialog (HWND hDlg,        /* window handle of the dialog box */
                              UINT message,     /* type of message */
                              WPARAM uParam,    /* message-specific information */
                              LPARAM lParam)
{
  BOOL bError;
  static COLORADJUSTMENT caOld = {0};
  static BOOL bUpdate = TRUE;

  switch (message) {
  case WM_INITDIALOG:           /* message: initialize dialog box */
    // Store the old copy so that we can cancel out
    caOld = caHalf;

    CheckDlgButton(hDlg, IDC_UPDATE, bUpdate);

    SendDlgItemMessage (hDlg, IDC_FLAGS, CB_ADDSTRING, 0, (LPARAM) "None");
    SendDlgItemMessage (hDlg, IDC_FLAGS, CB_ADDSTRING, 0, (LPARAM) "Negative");
    SendDlgItemMessage (hDlg, IDC_FLAGS, CB_ADDSTRING, 0, (LPARAM) "Log Filter");
    SendDlgItemMessage (hDlg, IDC_FLAGS, CB_SETCURSEL, caHalf.caFlags, 0);

    SendDlgItemMessage (hDlg, IDC_ILLUMINATE, CB_ADDSTRING, 0, (LPARAM) "Device's default");
    SendDlgItemMessage (hDlg, IDC_ILLUMINATE, CB_ADDSTRING, 0, (LPARAM) "Tungsten lamp");
    SendDlgItemMessage (hDlg, IDC_ILLUMINATE, CB_ADDSTRING, 0, (LPARAM) "Noon sunlight");
    SendDlgItemMessage (hDlg, IDC_ILLUMINATE, CB_ADDSTRING, 0, (LPARAM) "NTSC daylight");
    SendDlgItemMessage (hDlg, IDC_ILLUMINATE, CB_ADDSTRING, 0, (LPARAM) "Normal print");
    SendDlgItemMessage (hDlg, IDC_ILLUMINATE, CB_ADDSTRING, 0, (LPARAM) "Bond paper print");
    SendDlgItemMessage (hDlg, IDC_ILLUMINATE, CB_ADDSTRING, 0, (LPARAM) "Standard daylight");
    SendDlgItemMessage (hDlg, IDC_ILLUMINATE, CB_ADDSTRING, 0, (LPARAM) "Northern daylight");
    SendDlgItemMessage (hDlg, IDC_ILLUMINATE, CB_ADDSTRING, 0, (LPARAM) "Cool white lamp");
    SendDlgItemMessage (hDlg, IDC_ILLUMINATE, CB_SETCURSEL, caHalf.caIlluminantIndex, 0);

    SetupControls(hDlg, IDC_REDGAMMASLIDER,     IDC_REDGAMMA,     250,  6500, caHalf.caRedGamma / 10, TRUE);
    SetupControls(hDlg, IDC_GREENGAMMASLIDER,   IDC_GREENGAMMA,   250,  6500, caHalf.caGreenGamma / 10, TRUE);
    SetupControls(hDlg, IDC_BLUEGAMMASLIDER,    IDC_BLUEGAMMA,    250,  6500, caHalf.caBlueGamma / 10, TRUE);
    
    SetupControls(hDlg, IDC_REFBLACKSLIDER,     IDC_REFBLACK,       0,  4000, caHalf.caReferenceBlack, FALSE);
    SetupControls(hDlg, IDC_REFWHITESLIDER,     IDC_REFWHITE,    6000, 10000, caHalf.caReferenceWhite, FALSE);
    
    SetupControls(hDlg, IDC_CONTRASTSLIDER,     IDC_CONTRAST,     -100,  100, caHalf.caContrast, FALSE);
    SetupControls(hDlg, IDC_BRIGHTNESSSLIDER,   IDC_BRIGHTNESS,   -100,  100, caHalf.caBrightness, FALSE);
    SetupControls(hDlg, IDC_COLORFULNESSSLIDER, IDC_COLORFULNESS, -100,  100, caHalf.caColorfulness, FALSE);
    SetupControls(hDlg, IDC_TINTSLIDER,         IDC_TINT,         -100,  100, caHalf.caRedGreenTint, FALSE);
    return (TRUE);

  case WM_HSCROLL:
        {
            int iTemp = SendMessage((HWND)lParam, TBM_GETPOS, (WPARAM)0, (LPARAM)0);
            
            if ((HWND)lParam == GetDlgItem(hDlg, IDC_REDGAMMASLIDER)) 
                SetDlgItemInt(hDlg, IDC_REDGAMMA, iTemp*10, TRUE);
            
            if ((HWND)lParam == GetDlgItem(hDlg, IDC_GREENGAMMASLIDER)) 
                SetDlgItemInt(hDlg, IDC_GREENGAMMA, iTemp*10, TRUE);

            if ((HWND)lParam == GetDlgItem(hDlg, IDC_BLUEGAMMASLIDER)) 
                SetDlgItemInt(hDlg, IDC_BLUEGAMMA, iTemp*10, TRUE);

            if ((HWND)lParam == GetDlgItem(hDlg, IDC_REFBLACKSLIDER)) 
                SetDlgItemInt(hDlg, IDC_REFBLACK, iTemp, TRUE);

            if ((HWND)lParam == GetDlgItem(hDlg, IDC_REFWHITESLIDER)) 
                SetDlgItemInt(hDlg, IDC_REFWHITE, iTemp, TRUE);

            if ((HWND)lParam == GetDlgItem(hDlg, IDC_CONTRASTSLIDER)) 
                SetDlgItemInt(hDlg, IDC_CONTRAST, iTemp, TRUE);

            if ((HWND)lParam == GetDlgItem(hDlg, IDC_BRIGHTNESSSLIDER)) 
                SetDlgItemInt(hDlg, IDC_BRIGHTNESS, iTemp, TRUE);

            if ((HWND)lParam == GetDlgItem(hDlg, IDC_COLORFULNESSSLIDER)) 
                SetDlgItemInt(hDlg, IDC_COLORFULNESS, iTemp, TRUE);

            if ((HWND)lParam == GetDlgItem(hDlg, IDC_TINTSLIDER)) 
                SetDlgItemInt(hDlg, IDC_TINT, iTemp, TRUE);

            caHalf.caRedGamma = (WORD)GetDlgItemInt (hDlg, IDC_REDGAMMA, &bError, FALSE);
            caHalf.caGreenGamma = (WORD)GetDlgItemInt (hDlg, IDC_GREENGAMMA, &bError, FALSE);
            caHalf.caBlueGamma = (WORD)GetDlgItemInt (hDlg, IDC_BLUEGAMMA, &bError, FALSE);
            caHalf.caReferenceBlack = (WORD)GetDlgItemInt (hDlg, IDC_REFBLACK, &bError, FALSE);
            caHalf.caReferenceWhite = (WORD)GetDlgItemInt (hDlg, IDC_REFWHITE, &bError, FALSE);
            caHalf.caContrast = (WORD)GetDlgItemInt (hDlg, IDC_CONTRAST, &bError, FALSE);
            caHalf.caBrightness = (WORD)GetDlgItemInt (hDlg, IDC_BRIGHTNESS, &bError, FALSE);
            caHalf.caColorfulness = (WORD)GetDlgItemInt (hDlg, IDC_COLORFULNESS, &bError, FALSE);
            caHalf.caRedGreenTint = (WORD)GetDlgItemInt (hDlg, IDC_TINT, &bError, TRUE);
            
            if (IsDlgButtonChecked(hDlg, IDC_UPDATE))
                InvalidateRect(hWndMain, NULL, FALSE);
        }
        return FALSE;

  case WM_COMMAND:          /* message: received a command */

    if (HIWORD(uParam) == CBN_SELCHANGE) {
        caHalf.caFlags = (WORD) SendDlgItemMessage (hDlg, IDC_FLAGS, CB_GETCURSEL, 0, 0);
        caHalf.caIlluminantIndex = (WORD) SendDlgItemMessage (hDlg, IDC_ILLUMINATE, CB_GETCURSEL, 0, 0);
        
        if (IsDlgButtonChecked(hDlg, IDC_UPDATE))
            InvalidateRect(hWndMain, NULL, FALSE);
    }

    if (LOWORD (uParam) == IDOK || LOWORD (uParam) == IDCANCEL) {   /* System menu close command? */

      if (LOWORD (uParam) != IDOK)  // if cancel was pressed
        caHalf = caOld; // restore the old version
      else
        bUpdate = IsDlgButtonChecked(hDlg, IDC_UPDATE);

      EndDialog (hDlg, TRUE);   /* Exit the dialog */
      return (TRUE);
    }
    break;
  }
  return (FALSE);           /* Didn't process the message */

  lParam;                   /* This will prevent 'unused formal parameter' warnings */
}
 
/****************************************************************************

        FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)

        PURPOSE:  Processes messages

        MESSAGES:

        WM_COMMAND    - application menu (About dialog box)
        WM_DESTROY    - destroy window

        COMMENTS:

        To process the IDM_ABOUT message, call MakeProcInstance() to get the
        current instance address of the About() function.  Then call Dialog
        box which will create the box according to the information in your
        HALFTONE.rc file and turn control over to the About() function.  When
        it returns, free the intance address.

****************************************************************************/

LRESULT CALLBACK WndProc(
                HWND hWnd,         // window handle
                UINT message,      // type of message
                WPARAM uParam,     // additional information
                LPARAM lParam)     // additional information
{
    int wmId, wmEvent;
    static HBITMAP hbmp = NULL;
    static HANDLE hPalette = NULL;
	
    switch (message) {
        case WM_CREATE:
            {
                HDC hDC = GetDC(NULL);
                
				if (!hDC)
					return -1;  // Something is profoundly wrong, bail!

                // Initialize the global color adjustment structure
                caHalf.caSize = sizeof(caHalf);
                
                // Does the OS we are running on support GetColorAdjustment?
                if (!GetColorAdjustment (hDC, &caHalf)) {
                    MessageBox(hWnd, "Please be sure that the version of the OS you are running supports "
                                     "HALFTONE stretching.",
                                     "Unable to retrieve COLORADJUSTMENT settings", MB_ICONSTOP);
                    return  -1;   // No, bail!
                } 

                // Create a halftone palette
                hPalette = CreateHalftonePalette(hDC);

                InitCommonControls();     

                ReleaseDC(NULL, hDC);
            }
            return 0;

        case WM_PAINT:
            {
               PAINTSTRUCT ps;
               HDC    hDC = BeginPaint(hWnd, &ps);
			   BOOL   bError;  // Track the error status
               RECT   rect;
               HDC    hdcMem;
               BITMAP bm;
               
               // Get the extents of our drawing area
               GetClientRect(hWnd, &rect);
               
               if (hbmp) { // If we have a DIB section loaded
                   // Prepare for our DC for a halftone stretch
                   bError = (SetStretchBltMode(hDC, HALFTONE) == 0);
				   bError |= (SetColorAdjustment(hDC, &caHalf) == 0);
                   
				   bError |= (SelectPalette(hDC, hPalette, FALSE) == NULL);
                   bError |= (RealizePalette(hDC) == GDI_ERROR);
                                      
                   // Get the extents of our DIB
                   bError |= (GetObject(hbmp, sizeof(BITMAP), &bm) == 0);

                   hdcMem = CreateCompatibleDC(hDC);
				   bError |= (hdcMem == NULL);

                   if (!bError) {
					   SelectObject(hdcMem, hbmp);
					   StretchBlt(hDC,    0, 0, rect.right, rect.bottom,
								  hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
				   } else // reprt that an error 
					   PostMessage(hWnd, WM_COMMAND, IDM_ERRORMESSAGE, 0);  

                   DeleteDC(hdcMem);
               } else
                   PatBlt(hDC, 0, 0, rect.right, rect.bottom, BLACKNESS);

               EndPaint(hWnd, &ps);
            }
            break;

        case WM_PALETTECHANGED:
            if ((HWND) uParam == hWnd)
                return 0;

        /* Otherwise, fall through to WM_QUERYNEWPALETTE. */
        case WM_QUERYNEWPALETTE:
            {
                HDC hdc = GetDC(hWnd);
                HPALETTE hpal;
                UINT i;

                /*
                 * If realizing the palette causes the palette to change,
                 * redraw completely.
                 */
                hpal = SelectPalette (hdc, hPalette, FALSE);
                i = RealizePalette(hdc); /* i == entries that changed  */

                SelectPalette (hdc, hpal, FALSE);
                ReleaseDC(hWnd, hdc);

                /* If any palette entries changed, repaint the entire window. */
                if (i > 0) 
                    InvalidateRect(hWnd, NULL, TRUE);
                return i;
            }
        
    
        case WM_COMMAND:
            wmId    = LOWORD(uParam);
            wmEvent = HIWORD(uParam);

            switch (wmId) {
				case IDM_ERRORMESSAGE:
					// Report that an error has occurred and exit
					MessageBox(hWnd, "An error has occurred in the handling of the WM_PAINT\n"
							         "Press OK to exit this application.", "Error!", MB_ICONSTOP);
					PostQuitMessage(-1);
					break;

                case IDM_LOADDIB:
                        {
                            OPENFILENAME ofn = {0};
                            char szNewTitle[MAX_PATH];
                            char szDirName[MAX_PATH];
                            char szFilename[MAX_PATH] = "*.BMP";

                            /* Get the windows directory name, and store in szDirName */
                            GetWindowsDirectory(szDirName, sizeof(szDirName));
                            
                            /* Set all structure members to zero. */
                            ZeroMemory(&ofn, sizeof(OPENFILENAME));

                            ofn.lStructSize = sizeof(OPENFILENAME);
                            ofn.hwndOwner = hWnd;
                            ofn.lpstrFilter = "BMP Files (*.BMP)\0 *.BMP\0\0";
                            ofn.lpstrFile = szFilename;
                            ofn.nMaxFile = sizeof(szFilename);
                            ofn.lpstrDefExt = "BMP";
                            ofn.lpstrInitialDir = szDirName;
                            ofn.Flags = OFN_EXPLORER | OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                            if (hbmp)
                                DeleteObject(hbmp);

                            if (GetOpenFileName(&ofn)) {
                               hbmp = LoadImage(NULL, 
                                             szFilename, 
                                             IMAGE_BITMAP, 0, 0,
                                             LR_CREATEDIBSECTION | LR_LOADFROMFILE );
                               if (!hbmp)
                                  MessageBox(hWnd, "Unable to load file!", szFilename, MB_ICONSTOP);
                            } else {
                                if (strlen(szFilename) != 0)
                                  MessageBox(hWnd, "Unable to load file!", szFilename, MB_ICONSTOP);
                                
                                return 0;
                            }
                            
                            // Set our title to reflect the name of the file we loaded
                            StringCchCopy(szNewTitle, MAX_PATH, szTitle);
                            StringCchCat (szNewTitle, MAX_PATH, " - ");
                            StringCchCat (szNewTitle, MAX_PATH, szFilename);
                            SetWindowText(hWnd, szNewTitle);

                            InvalidateRect(hWnd, NULL, FALSE);
                        }
                        break;
    
                case IDM_PROPERTIES:
                        DialogBox (hInst,       /* current instance */
                                   "HT_DIALOG", /* dlg resource to use */
                                   hWnd,        /* parent handle */
                                   (DLGPROC) HalftoneDialog);   /* Halftone() instance address */

                        // Redraw with the new properties
                        InvalidateRect(hWnd, NULL, FALSE);
                        break;

                case IDM_ABOUT:
                    DialogBox(hInst,          // current instance
                             "ABOUTBOX",      // dlg resource to use
                             hWnd,            // parent handle
                             (DLGPROC)About); // About() instance address

                    break;
                
                case IDM_EXIT:
                        if (hbmp)
                            DeleteObject(hbmp);

                        DestroyWindow (hWnd);
                        break;

                default:
                        return (DefWindowProc(hWnd, message, uParam, lParam));
            }
            break;

        case WM_DESTROY:  // message: window being destroyed
				if (hPalette)
					DeleteObject(hPalette);
                PostQuitMessage(0);
                break;
    
        default:          // Passes it on if unproccessed
                return (DefWindowProc(hWnd, message, uParam, lParam));
    }
    return (0);
}

/*****************************************************************************
 *                                                                           *
 *   FUNCTION: CenterWindow (HWND, HWND)                                     *
 *                                                                           *
 *   PURPOSE:  Center one window over another                                *
 *                                                                           *
 *   COMMENTS:                                                               *
 *                                                                           *
 *   Dialog boxes take on the screen position that they were designed at,    *
 *   which is not always appropriate. Centering the dialog over a particular *
 *   window usually results in a better position.                            *
 *                                                                           *
 ****************************************************************************/

BOOL CenterWindow (HWND hwndChild, HWND hwndParent)
{
        RECT    rChild, rParent;
        int     wChild, hChild, wParent, hParent;
        int     wScreen, hScreen, xNew, yNew;
        HDC     hdc;

        // Get the Height and Width of the child window
        GetWindowRect (hwndChild, &rChild);
        wChild = rChild.right - rChild.left;
        hChild = rChild.bottom - rChild.top;

        // Get the Height and Width of the parent window
        GetWindowRect (hwndParent, &rParent);
        wParent = rParent.right - rParent.left;
        hParent = rParent.bottom - rParent.top;

        // Get the display limits
        hdc = GetDC (hwndChild);
        wScreen = GetDeviceCaps (hdc, HORZRES);
        hScreen = GetDeviceCaps (hdc, VERTRES);
        ReleaseDC (hwndChild, hdc);

        // Calculate new X position, then adjust for screen
        xNew = rParent.left + ((wParent - wChild) /2);
        if (xNew < 0) {
                xNew = 0;
        } else if ((xNew+wChild) > wScreen) {
                xNew = wScreen - wChild;
        }

        // Calculate new Y position, then adjust for screen
        yNew = rParent.top  + ((hParent - hChild) /2);
        if (yNew < 0) {
                yNew = 0;
        } else if ((yNew+hChild) > hScreen) {
                yNew = hScreen - hChild;
        }

        // Set it, and return
        return SetWindowPos (hwndChild, NULL,
                xNew, yNew, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}


/*****************************************************************************
 *                                                                           *
 *   FUNCTION: About(HWND, UINT, WPARAM, LPARAM)                             *
 *                                                                           *
 *   PURPOSE:  Processes messages for "About" dialog box                     *
 *                                                                           *
 *   MESSAGES:                                                               *
 *                                                                           *
 *   WM_INITDIALOG - initialize dialog box                                   *
 *   WM_COMMAND    - Input received                                          *
 *                                                                           *
 *   COMMENTS:                                                               *
 *                                                                           *
 *   Display version information from the version section of the             *
 *   application resource.                                                   *
 *                                                                           *
 *   Wait for user to click on "Ok" button, then close the dialog box.       *
 *                                                                           *
 ****************************************************************************/

LRESULT CALLBACK About(
                HWND hDlg,           // window handle of the dialog box
                UINT message,        // type of message
                WPARAM uParam,       // message-specific information
                LPARAM lParam)
{
    switch (message) {
        case WM_INITDIALOG:  // message: initialize dialog box
            // Center the dialog over the application window
            CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
            return (TRUE);

        case WM_COMMAND:                      // message: received a command
            if (LOWORD(uParam) == IDOK || LOWORD(uParam) == IDCANCEL) { 
                EndDialog(hDlg, TRUE);        // Exit the dialog
                return (TRUE);
            }
            break;
    }
    return (FALSE); // Didn't process the message

    UNREFERENCED_PARAMETER(lParam); // This will prevent 'unused formal parameter' warnings
}
