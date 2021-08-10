/***************************************************************************** 
 *       																	 * 
 *       THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF	 * 
 *       ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED 	 * 
 *       TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A	 * 
 *       PARTICULAR PURPOSE.                                              	 * 
 *                                                                        	 * 
 *       Copyright (C) 2000  Microsoft Corporation.  All rights reserved. 	 * 
 *                                                                        	 * 
 ****************************************************************************/

/*****************************************************************************
 *                                                                           *
 *   PROGRAM: ViewDIB.c                                                      *
 *                                                                           *
 *   PURPOSE: Demonstrate how to load, save, convert, display, and print     *
 *            DIB Sections                                                   *
 *                                                                           *
 *   FUNCTIONS:                                                              *
 *                                                                           *
 *   GetLastErrorBox() - Report GetLastError() values as text                *
 *   InitApplication() - initializes window data and registers window        *
 *   InitInstance() - saves instance handle and creates main window          *
 *   WinMain() - calls initialization function, processes message loop       *
 *   SetWindowTitle() - Sets the title text for the main window              *
 *   PrintDIBSection() - Prints a DIB section to a user selected printer     *
 *   WndProc() - processes messages                                          *
 *   About() - processes messages for "About" dialog box                     *
 *                                                                           *
 ****************************************************************************/

#include <windows.h>   // required for all Windows applications
#include <stdio.h>
#include <commdlg.h>
#include "DIBSectn.h"  // library of DIB Section manipulation functions
#include "OpenDIB.h"   // contains code for reading a DIB file name w/preview
#include "resource.h"  // specific to this program

HINSTANCE hInst;          // current instance

char szAppName[] = "ViewDIB";   // The name of this application
char szTitle[]   = "ViewDIB: DIB Section Demo"; // The title bar text

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About  (HWND, UINT, WPARAM, LPARAM);

/*****************************************************************************
 *                                                                           *
 * FUNCTION:  GetLastErrorBox(HWND, LPSTR)                                   *  
 *                                                                           *
 * PURPOSE:   Gets the error status and, if an error is indicated,           *
 *            converts the error number into text and displays it            *
 *            in a MessageBox.                                               *
 *                                                                           *	    
 ****************************************************************************/	    
DWORD GetLastErrorBox(HWND hWnd, LPSTR lpTitle)							    
{																		    
   LPVOID lpv;															    
   DWORD  dwRv;

   if (GetLastError() == 0) return 0;
   
   dwRv = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                        FORMAT_MESSAGE_FROM_SYSTEM,
                        NULL,
                        GetLastError(),
                        MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                        (LPVOID)&lpv,
                        0,
                        NULL);
   
   MessageBox(hWnd, lpv, lpTitle, MB_OK);
   
   if(dwRv)
      LocalFree(lpv);
   
   SetLastError(0);
   return dwRv;
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
    wc.hIcon         = LoadIcon (hInstance, "VD_ICON"); // Icon name from .RC
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW); // Cursor
    wc.hbrBackground = GetStockObject(NULL_BRUSH);
    wc.lpszMenuName  = "VD_MENU";              // Menu name from .RC
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
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{       
    MSG msg;
    HANDLE hAccelTable;
    
    if (!hPrevInstance) {       // Other instances of app running?
		if (!InitApplication(hInstance)) { // Initialize shared things
            return (FALSE);     // Exits if unable to initialize
        }
    }
	
    // Perform initializations that apply to a specific instance
    if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);
	
    // Load the keyboard a accelerators for this app
	hAccelTable = LoadAccelerators (hInstance, "VIEWDIB");
	
    /* Acquire and dispatch messages until a WM_QUIT message is received. */
    while (GetMessage(&msg, NULL, 0, 0))  {
        if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);// Translates virtual key codes
            DispatchMessage(&msg); // Dispatches message to window
        }
    }
	
    return (int)msg.wParam; // Returns the value from PostQuitMessage
	
    UNREFERENCED_PARAMETER(lpCmdLine); // This will prevent 'unused formal parameter' warnings
}

/*****************************************************************************
 *                                                                           *
 * FUNCTION: SetWindowTitle(HWND, LPSTR, HBITMAP)                            *
 *                                                                           *
 * PURPOSE: Sets the title text for the main window to include the name of   *
 *          the file that's currently being displayed along with the         *
 *          resolution and color depth.                                      *
 *                                                                           *
 ****************************************************************************/
void SetWindowTitle(HWND hWnd,LPSTR szFilename, HBITMAP hbm)
{
	DIBSECTION	ds;
	char		szNewTitle[MAX_PATH*2];
	
	if (hbm) {
		GetObject(hbm, sizeof(DIBSECTION), &ds);

		_snprintf(szNewTitle, sizeof(szNewTitle)-1,
				 "%s - %s  (%lu x %lu x %lu bpp)",
				 szAppName, 
				 szFilename, 
				 ds.dsBmih.biWidth, 
				 ds.dsBmih.biHeight, 
				 ds.dsBmih.biPlanes * ds.dsBmih.biBitCount);
    } else {
		lstrcpyn(szNewTitle, szAppName, sizeof(szNewTitle)-1);
    }
    szNewTitle[sizeof(szNewTitle)-1] = '\0';

    SetWindowText(hWnd, szNewTitle);
}

/*****************************************************************************
 *                                                                           *
 * FUNCTION: PrintDIBSection(HWND, HBITMAP)                                  *
 *                                                                           *
 * PURPOSE: Lets the user for a printer and then prints a DIB section to it. *
 *                                                                           *
 ****************************************************************************/

void PrintDIBSection(HWND hWnd, HBITMAP hbmp)				
{
	PRINTDLG pd;
	RECT rc;
	DOCINFO di;

	// Clear the structure so it doesn't contain random values
	ZeroMemory(&pd, sizeof(pd));
	
	// Initialize the structure for retrieving an HDC 
	pd.lStructSize = sizeof(PRINTDLG);
	pd.hwndOwner = hWnd;
	pd.Flags = PD_RETURNDC | PD_PRINTSETUP;

	// Let the user pick a printer
	if (!PrintDlg(&pd))
		return;
	
	// Make sure we got a DC
	if (!pd.hDC)
		return;

	if (pd.hDevMode) GlobalFree(pd.hDevMode);
	if (pd.hDevNames) GlobalFree(pd.hDevNames);

	// Get a rectangle that covers the entire page
	SetRect(&rc,0,0,GetDeviceCaps(pd.hDC, HORZRES), GetDeviceCaps(pd.hDC, VERTRES));

	// Initialize the DOCINFO with the document name
	ZeroMemory(&di, sizeof(di));
	di.cbSize = sizeof(di);
	di.lpszDocName = "ViewDIB Image";

	// Initiate document
	StartDoc(pd.hDC, &di);

	// Initiate page
	StartPage(pd.hDC);

	// Draw the image
	if (!DSDrawDIBSectionOnDC(pd.hDC, hbmp, &rc))
		GetLastErrorBox(hWnd, "Error during printing");

	EndPage(pd.hDC);
	EndDoc(pd.hDC);

	// Clean up
	DeleteDC(pd.hDC);
}

/*****************************************************************************
 *                                                                           *
 *   FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)                           *
 *                                                                           *
 *   PURPOSE:  Processes messages for main application window                *
 *                                                                           *
 ****************************************************************************/
LRESULT CALLBACK WndProc(
                HWND hWnd,         // window handle
                UINT message,      // type of message
                WPARAM uParam,     // additional information
                LPARAM lParam)     // additional information
{
    static char szDirName[MAX_PATH] = "";
	int wmId, wmEvent;
    static HBITMAP hbmp = NULL;
    static HANDLE hPalette = NULL;
    
    switch (message) {
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC    hDC = BeginPaint(hWnd, &ps);
			RECT   rect;
			HDC    hdcMem;
			BITMAP bm;
			
			// Get the extents of our drawing area
			GetClientRect(hWnd, &rect);
			
			if (hbmp) { // If we have a DIB section loaded
				
				// Get the attributes of our DIB section
				if (GetObject(hbmp, sizeof(BITMAP), &bm)) {
					// If our DIB has a color table
					if (DSBitsPerPixel(hbmp) <= 8)
						SetStretchBltMode(hDC, COLORONCOLOR); // Yes: COLORONCOLOR is sufficient
					else
						SetStretchBltMode(hDC, HALFTONE);     // No: It will probably look better in HALFTONE
					
					// If we have a palette, map the colors into the system palette
					if (hPalette) {
						SelectPalette(hDC, hPalette, FALSE);
						RealizePalette(hDC);
					}

					// Create a temporary memory DC to hold the DIB	section
					hdcMem = CreateCompatibleDC(hDC);
					SelectObject(hdcMem, hbmp);
					
					// Display it
					StretchBlt(hDC,    0, 0, rect.right, rect.bottom,
						       hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
					
					DeleteDC(hdcMem);
				}
			} else
				PatBlt(hDC, 0, 0, rect.right, rect.bottom, BLACKNESS);
			
			EndPaint(hWnd, &ps);
		}
		break;
		
	case WM_PALETTECHANGED:
		if ((HWND) uParam == hWnd)
			return 0;
		
    // Otherwise, fall through to WM_QUERYNEWPALETTE.
	case WM_QUERYNEWPALETTE:
		if (hPalette)
		{
			HDC hdc = GetDC(hWnd);
			HPALETTE hpal;
			UINT i;
			
			// If realizing the palette causes the palette to change,
			// redraw completely.
			hpal = SelectPalette (hdc, hPalette, FALSE);
			i = RealizePalette(hdc); // i == entries that changed 
			
			SelectPalette (hdc, hpal, FALSE);
			ReleaseDC(hWnd, hdc);
			
			// If any palette entries changed, repaint the entire window.
			if (i > 0) 
				InvalidateRect(hWnd, NULL, TRUE);
			return i;
		} 
		break;
        
	case WM_INITMENU:
		// Initialize all of the menu items
		EnableMenuItem((HMENU)uParam, IDM_PASTE,   (IsClipboardFormatAvailable(CF_DIB) || IsClipboardFormatAvailable(CF_BITMAP)) ? MF_ENABLED : MF_GRAYED);
		EnableMenuItem((HMENU)uParam, IDM_COPY,    hbmp ? MF_ENABLED : MF_GRAYED);
		EnableMenuItem((HMENU)uParam, IDM_SAVEDIB, hbmp ? MF_ENABLED : MF_GRAYED);
		EnableMenuItem((HMENU)uParam, IDM_PRINT,   hbmp ? MF_ENABLED : MF_GRAYED);
		EnableMenuItem((HMENU)uParam, IDM_DIBINFO, hbmp ? MF_ENABLED : MF_GRAYED);
		EnableMenuItem((HMENU)uParam, IDM_CD1BPP,  hbmp ? MF_ENABLED : MF_GRAYED);
		EnableMenuItem((HMENU)uParam, IDM_CD4BPP,  hbmp ? MF_ENABLED : MF_GRAYED); 
		EnableMenuItem((HMENU)uParam, IDM_CD8BPP,  hbmp ? MF_ENABLED : MF_GRAYED); 
		EnableMenuItem((HMENU)uParam, IDM_CD15BPP, hbmp ? MF_ENABLED : MF_GRAYED);
		EnableMenuItem((HMENU)uParam, IDM_CD16BPP, hbmp ? MF_ENABLED : MF_GRAYED);
		EnableMenuItem((HMENU)uParam, IDM_CD24BPP, hbmp ? MF_ENABLED : MF_GRAYED);
		EnableMenuItem((HMENU)uParam, IDM_CD32BPP, hbmp ? MF_ENABLED : MF_GRAYED);
		break;
		
	case WM_COMMAND:
		wmId    = LOWORD(uParam);
		wmEvent = HIWORD(uParam);
		
		switch (wmId) {
		case IDM_DIBINFO:  // Display the DIB section attributes to the user in a MessageBox
			{
				char szBuffer[256];
				DIBSECTION ds;

				// Bail if we don't have a DIB section
				if (!hbmp)  
					break;
				
				// Get the surface attributes 
				if (!GetObject(hbmp, sizeof(DIBSECTION), &ds))
					break;  // bail if there is an error

				// Compose the message
				_snprintf(szBuffer, sizeof(szBuffer)-1,
                                   "biSize       \t%lu\n"
								   "biWidth      \t%lu\n"
								   "biHeight     \t%lu\n"
								   "biPlanes     \t%u\n"
								   "biBitCount   \t%u\n"
								   "biCompression\t%lu\n"
								   "biSizeImage  \t%lu\n"
								   "biXPelsPerMtr\t%lu\n"
								   "biYPelsPerMtr\t%lu\n"
								   "biClrUsed    \t%lu\n"
								   "biClrImportant\t%lu\n",
					  ds.dsBmih.biSize,
					  ds.dsBmih.biWidth,
					  ds.dsBmih.biHeight,
					  ds.dsBmih.biPlanes,
					  ds.dsBmih.biBitCount,
					  ds.dsBmih.biCompression,
					  ds.dsBmih.biSizeImage,
					  ds.dsBmih.biXPelsPerMeter,
					  ds.dsBmih.biYPelsPerMeter,
					  ds.dsBmih.biClrUsed,
					  ds.dsBmih.biClrImportant);
               szBuffer[sizeof(szBuffer)-1] = '\0';

       		   // Tack on the bitfields information if the DIB section uses bitfields
				if (ds.dsBmih.biCompression == BI_BITFIELDS) {
					_snprintf(&szBuffer[lstrlen(szBuffer)], sizeof(szBuffer)-lstrlen(szBuffer)-1,
						     "Bitfields:\n\tR: 0x%08X\n\tG: 0x%08X\n\tB: 0x%08X",
							 ds.dsBitfields[0],ds.dsBitfields[1],ds.dsBitfields[2]);
                    szBuffer[sizeof(szBuffer)-1] = '\0';
				}

				// Show the user the information
				MessageBox (NULL, szBuffer, "DIB Section Information", MB_ICONINFORMATION);
			}
			break;

		// Handle format conversions
		case IDM_CD1BPP:
		case IDM_CD4BPP:
		case IDM_CD8BPP:
		case IDM_CD15BPP:
		case IDM_CD16BPP:
		case IDM_CD24BPP:
		case IDM_CD32BPP:
			{
				HBITMAP hbmNew;

				// Convert into the surface format the user asked for
				switch (wmId) {
					case IDM_CD1BPP: hbmNew = DSCopyBitmapEx(hbmp, NULL, 1); break;
					case IDM_CD4BPP: hbmNew = DSCopyBitmapEx(hbmp, NULL, 4); break;
					case IDM_CD8BPP: hbmNew = DSCopyBitmapEx(hbmp, NULL, 8); break;
					case IDM_CD15BPP: hbmNew = DSCopyBitmapEx(hbmp, NULL, 15); break;
					case IDM_CD16BPP: hbmNew = DSCopyBitmapEx(hbmp, NULL, 16); break;
					case IDM_CD24BPP: hbmNew = DSCopyBitmapEx(hbmp, NULL, 24); break;
					case IDM_CD32BPP: hbmNew = DSCopyBitmapEx(hbmp, NULL, 32); break;
				}

				// If we sucessfully converted, update the titlebar and redisplay
				if (hbmNew) {
					// Delete the old bitmap and palette 
					DeleteObject(hbmp);
					if (hPalette)
						DeleteObject(hPalette);
				
					// Update our bitmap and palette to reference the new image
					hbmp = hbmNew;		
					hPalette = DSCreatePaletteForDIBSection(hbmp);

					// Set our title to reflect the name of the file we loaded
					SetWindowTitle(hWnd, "Untitled.BMP", hbmp);
					
					// Force the new image to be displayed
					InvalidateRect(hWnd, NULL, FALSE);
				} else
					GetLastErrorBox(hWnd, "Error during format conversion");
			}
			break;

		// Print the DIB section
		case IDM_PRINT:
			if (hbmp)
				PrintDIBSection(hWnd, hbmp);
			break;
		
			// Copy the DIB section to the clipboard
		case IDM_COPY:
			if (hbmp) {
				DSPutDIBSectionOnClipboard(hbmp);
			}
			break;
			
		// Paste the DIB section from the clipboard
		case IDM_PASTE:
			{
				HBITMAP hbmNew;

				// Retrieve the DIB
				hbmNew = DSGetDIBSectionFromClipboard();

				if (hbmNew) {
					if (hbmp)
						DeleteObject(hbmp);
				
					if (hPalette)
						DeleteObject(hPalette);

					hbmp = hbmNew;
					hPalette = DSCreatePaletteForDIBSection(hbmp);

					// Set our title to reflect the origin/attributes of the image
					SetWindowTitle(hWnd, "<Clipboard>", hbmp);
					
					InvalidateRect(hWnd, NULL, FALSE);
				} else
					GetLastErrorBox(hWnd, "Error during paste");
			}
			break;

		case IDM_LOADDIB:
			{
				char szFilename[MAX_PATH] = "*.BMP";
				
				// Retreive a filename
                szDirName[sizeof(szDirName)-1] = '\0';
				if (GetDIBFilename(szFilename, szDirName, FALSE)) {
					
					// Save the current directory
					GetCurrentDirectory(MAX_PATH, szDirName);

					if (hbmp)
						DeleteObject(hbmp);
					
					if (hPalette)
						DeleteObject(hPalette);
					
					if (!DSLoadDIBSectionFromBMPFile(szFilename, &hbmp, (HPALETTE*)&hPalette)) {
						MessageBox(hWnd, "Unable to load file!", szFilename, MB_ICONSTOP);
						hbmp = NULL;
						hPalette = NULL;
					}
				} else  // user canceled
					return 0;
				
				// Set our title to reflect the name of the file we loaded
				SetWindowTitle(hWnd, szFilename, hbmp);

				InvalidateRect(hWnd, NULL, FALSE);
			}
			break;
			
		case IDM_SAVEDIB:
			{
				char szFilename[MAX_PATH] = "*.BMP";
				
				// Do we have a DIB loaded?
				if (!hbmp)
					break;

				// Retreive a filename
                szDirName[sizeof(szDirName)-1] = '\0';
				if (GetDIBFilename(szFilename, szDirName, TRUE)) {
					
					// Save the current directory
					GetCurrentDirectory(MAX_PATH, szDirName);

					// Save the current image to the filename the user selected
					DSStoreDIBSectionInBMPFile(szFilename, hbmp);

					// Set our title to reflect the new name of the file
					SetWindowTitle(hWnd, szFilename, hbmp);
				} else  // user canceled
					return 0;
			}
			break;
		
		case IDM_ABOUT:
			DialogBox(hInst,          // current instance
				"ABOUTBOX",      // dlg resource to use
				hWnd,            // parent handle
				(DLGPROC)About); // About() instance address
			break;
			
		case IDM_EXIT:
			DestroyWindow (hWnd);
			break;
			
		default:
			return (DefWindowProc(hWnd, message, uParam, lParam));
		}
		break;
		
        case WM_DESTROY:  // message: window being destroyed
			// Clean up the objects we created
			if (hbmp)
				DeleteObject(hbmp);
			
			if (hPalette)
				DeleteObject(hPalette);
			
			// Hasta la vista...
			PostQuitMessage(0);
			break;
			
        default:          // Passes it on if unproccessed
			return (DefWindowProc(hWnd, message, uParam, lParam));
    }
    return (0);
}


/*****************************************************************************
 *                                                                           *
 *   FUNCTION: About(HWND, UINT, WPARAM, LPARAM)                             *
 *                                                                           *
 *   PURPOSE:  Processes messages for "About" dialog box                     *
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
