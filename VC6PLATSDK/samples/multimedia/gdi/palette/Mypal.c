
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1993 - 2000 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/***************************************************************************
 *                                                                         *
 *  PROGRAM     : MyPal.c                                                  *
 *                                                                         *
 *  PURPOSE     : Sets up a bar representation of the current physical     *
 *                palette and displays useful information regarding        *
 *                pixel colors and palette indices.                        *
 *                                                                         *
 *  FUNCTIONS   : WinMain() - calls initialization function,               *
 *                            processes message loop                       *
 *                                                                         *
 *                WndProc() - Window function for app. Processes           *
 *                            window messages.                             *
 *                                                                         *
 *              ShowColor() - Displays a little box on each side of the    *
 *                            caption bar displaying the pixel color at the*
 *                            mouse position.                              *
 ***************************************************************************/

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "mypal.h"

HANDLE          hPal;          /* Handle to the application's logical palette */
static INT      nSizeX;        /* Width of the application window             */
static INT      nSizeY;        /* Height of the application window            */
INT             nXBorder;      /* Width of window border                      */
INT             nXTitle;       /* Width of title bar                          */
INT             nYTitle;       /* Height of title bar                         */
BOOL            bCaptureOn;    /* Indicates if mouse capture is on            */
DWORD           dwIndex;       /* Last index selected in palette              */
CHAR            szTitlebuf[90];/* Buffer for pixel and palette info. text     */
HDC             hDCGlobal;     /* The Screen DC                               */
DWORD           dwNumColors;   /* Number of colors supported by device        */
INT             iRasterCaps;   /* Raster capabilities                         */
RECT            rClientRect;   /* Client rectangle coordinates                */
DWORD           dwPal[PALETTESIZE];   /* Stores palette entries for later lookup  */
INT             iGlobalXOffset;
INT             iGlobalYOffset;
INT             iYMiddle;

LONG APIENTRY WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

BOOL InPaletteBasedVideoMode()
{
    HDC hdc = GetDC(NULL);
    BOOL bRet;
    int iRasCaps;

    iRasCaps = GetDeviceCaps(hdc, RASTERCAPS);
    bRet = (iRasCaps & RC_PALETTE) ? TRUE : FALSE;

    ReleaseDC(NULL, hdc);

    return bRet;
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : void ShowColor(HWND hWnd, HDC hDC)                         *
 *                                                                          *
 *  PURPOSE    : Displays a little box on each side of the caption bar      *
 *               displaying the pixel color at the mouse position.          *
 *                                                                          *
 ****************************************************************************/
VOID ShowColor (
        HWND  hWnd,
        HDC   hDC)
{
     HBRUSH  hBrush, hOldBrush;

     hBrush    = CreateSolidBrush ( PALETTEINDEX(dwIndex) );
	 if (!hBrush)
		 return;
	 hOldBrush = SelectObject (hDC,hBrush) ;

     GetWindowRect (hWnd, (LPRECT)&rClientRect);

     PatBlt ( hDC,
              rClientRect.left + nXTitle + nXBorder + 1,
              rClientRect.top + nXBorder,
              nXTitle,
              nYTitle,
              PATCOPY);

     PatBlt(hDC,
            rClientRect.right - ( 3 * nXTitle + nXBorder + 2),
            rClientRect.top + nXBorder,
            nXTitle,
            nYTitle,
            PATCOPY);
     SelectObject (hDC, hOldBrush);
     DeleteObject (hBrush) ;
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : WinMain(HANDLE, HANDLE, LPSTR, int)                        *
 *                                                                          *
 *  PURPOSE    : Creates the app. window and processes the message loop.    *
 *                                                                          *
 ****************************************************************************/
int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
    )
{
     static CHAR szAppName [] = "MyPal";
     HWND        hWnd;
     WNDCLASS    wndclass;
     MSG         msg ;
     INT         xScreen;
     INT         yScreen;
     UNREFERENCED_PARAMETER( lpCmdLine );

     if (!hPrevInstance){
         wndclass.style         = CS_HREDRAW | CS_VREDRAW;
         wndclass.lpfnWndProc   = (WNDPROC) WndProc;
         wndclass.cbClsExtra    = 0;
         wndclass.cbWndExtra    = 0;
         wndclass.hInstance     = hInstance;
         wndclass.hIcon         = LoadIcon(hInstance, szAppName);
         wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
         wndclass.hbrBackground = GetStockObject (BLACK_BRUSH);
         wndclass.lpszMenuName  = szAppName;
         wndclass.lpszClassName = szAppName;

         if (!RegisterClass (&wndclass))
             return FALSE ;
     }

     /* Do some global initializations */
     xScreen     = GetSystemMetrics (SM_CXSCREEN);
     yScreen     = GetSystemMetrics (SM_CYSCREEN);
     nXBorder    = (INT)GetSystemMetrics (SM_CXFRAME);
     nXTitle     = (INT)GetSystemMetrics (SM_CXSIZE);
     nYTitle     = (INT)GetSystemMetrics (SM_CYSIZE);
     dwIndex      = 0;
     bCaptureOn  = FALSE;

     hDCGlobal   = GetDC (NULL);
     iRasterCaps = GetDeviceCaps(hDCGlobal, RASTERCAPS);
     iRasterCaps = (iRasterCaps & RC_PALETTE) ? TRUE : FALSE;

     if (iRasterCaps)
         dwNumColors = GetDeviceCaps(hDCGlobal, SIZEPALETTE);
     else
         dwNumColors = GetDeviceCaps( hDCGlobal, NUMCOLORS);
     ReleaseDC (NULL,hDCGlobal);

     nSizeX = ((xScreen - 2*nXBorder) / PALETTESIZE) * PALETTESIZE;

     /* create the app. window */
     hWnd = CreateWindow (szAppName,
                          "My Physical Palette ",
                          WS_OVERLAPPEDWINDOW,
                          (xScreen-nSizeX) / 2 - nXBorder,
                          4 * GetSystemMetrics (SM_CYCAPTION),
                          nSizeX + 2 * nXBorder,
                          4 * GetSystemMetrics (SM_CYCAPTION),
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
     ShowWindow (hWnd, nCmdShow);
     UpdateWindow (hWnd);

     while (GetMessage (&msg, NULL, 0, 0)){
           TranslateMessage (&msg) ;
           DispatchMessage (&msg) ;
     }

     return (int)msg.wParam ;
}

/******************************************************************************
 *                                                                            *
 *  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)                             *
 *                                                                            *
 *  PURPOSE:  Processes window messages and sets up a 256 bar representation  *
 *            of the current physical palette. Specifically, in response to:  *
 *                                                                            *
 *               WM_CREATE  -Allocates for and sets up a LOGPALETTE           *
 *                           structure, creates a logical palette the same    *
 *                           size as the physical palette and obtains a       *
 *                           handle to the logical palette.                   *
 *                                                                            *
 *               WM_DESTROY -Destroys the logical palette and shuts down app. *
 *                                                                            *
 *               WM_PAINT   -Resizes client area to hold as many vertical     *
 *                           color bars as there are physical palette entries.*
 *                           Also realises the current logical palette and    *
 *                           draws one color bar corresponding to each        *
 *                           palette entry                                    *
 *                                                                            *
 *           WM_RBUTTONDOWN -Captures the mouse and initiates the below       *
 *                           process:                                         *
 *                                                                            *
 *           WM_MOUSEMOVE   -Following a WM_RBUTTONDOWN, if the right mouse   *
 *                           key is depressed, displays info about the        *
 *                           pixel RGB value and palette index of the mouse   *
 *                           coordinates.                                     *
 *                                                                            *
 *           WM_RBUTTONUP   -Release mouse capture and terminates the above   *
 *                           process                                          *
 *                                                                            *
 *           WM_LBUTTONDOWN -Determines and displays the palette index and    *
 *                           RGB value of the bar under the mouse.            *
 *                                                                            *
 *           WM_KEYDOWN     -Allows use of the arrow keys in stepping thro'   *
 *                           palette entries.                                 *
 *                                                                            *
 *****************************************************************************/
 LONG APIENTRY WndProc (
     HWND         hWnd,
     UINT     iMessage,
     WPARAM         wParam,
     LPARAM         lParam)
 {
     HDC           hDC;
     PAINTSTRUCT   ps;
     DWORD         dwLoop;
     INT           nStart;
     HBRUSH        hBrush;
     HBRUSH        hOldBrush;
     
     MPOINT        pt;
     static INT    nIncr;
     static DWORD  dwColor;
     static DWORD  dwLastColor;
     static DWORD  i, x;
    
	 switch (iMessage) {
     case WM_DISPLAYCHANGE:
         // The video mode changed, update the number of colors
         dwNumColors = 1 << wParam;

         if (!InPaletteBasedVideoMode()) {  // Should we attempt to display a non palette mode
             MessageBox(hWnd, "<WM_DISPLAYCHANGE> The current video mode is not palette based.\nSwitch to a palette based video mode for this sample to work properly", NULL, MB_OK | MB_ICONHAND);
         }
         break;
         
     case WM_DESTROY:
         // delete the handle to the logical palette
         if (hPal)
             DeleteObject (hPal);
         PostQuitMessage (0) ;
         break ;
         
     case WM_CREATE:
         {
             NPLOGPALETTE    pLogPal;       /* Pointer to program's logical palette        */

             if (!InPaletteBasedVideoMode()) {  // Should we attempt to display a non palette mode
                 MessageBox(hWnd, "<WM_CREATE> The current video mode is not palette based.\nSwitch to a palette based video mode for this sample to work properly", NULL, MB_OK | MB_ICONHAND);
             }

             // Allocate enough memory for a logical palette with
             // PALETTESIZE entries and set the size and version fields
             // of the logical palette structure.
             pLogPal = (NPLOGPALETTE) LocalAlloc (LMEM_FIXED,
                 (sizeof (LOGPALETTE) +
                 (sizeof (PALETTEENTRY) * (PALETTESIZE))));
             
             if(!pLogPal){
                 MessageBox(hWnd, "<WM_CREATE> Not enough memory for palette.", NULL, MB_OK | MB_ICONHAND);
                 PostQuitMessage (0) ;
                 break;
             }
             
             pLogPal->palVersion    = 0x300;
             pLogPal->palNumEntries = PALETTESIZE;
             
             // fill in intensities for all palette entry colors 
             for (dwLoop = 0; dwLoop < PALETTESIZE; dwLoop++) {
                 *((WORD *) (&pLogPal->palPalEntry[dwLoop].peRed)) = (WORD)dwLoop;
                 pLogPal->palPalEntry[dwLoop].peBlue  = 0;
                 pLogPal->palPalEntry[dwLoop].peFlags = PC_EXPLICIT;
             }
             
             //  create a logical color palette according the information
             //  in the LOGPALETTE structure.
             hPal = CreatePalette ((LPLOGPALETTE) pLogPal) ;

             LocalFree(pLogPal);
         }
         break;
         
     case WM_GETMINMAXINFO:
         
         ((LPRGPT)lParam)->iInfo[6] = nXBorder * 2 + PALETTESIZE;
         ((LPRGPT)lParam)->iInfo[7] = nXBorder * 2 + nYTitle*3;
         
         return (long) DefWindowProc (hWnd, iMessage, wParam, lParam) ;
         break;
         
     case WM_PAINT:
         GetClientRect(hWnd,(LPRECT) &rClientRect);
                 
         if (!InPaletteBasedVideoMode()) {  // Should we attempt to display a palette
             hDC = BeginPaint(hWnd, &ps);
             
             PatBlt(hDC,0,0,rClientRect.right, rClientRect.bottom, BLACKNESS);
             SetWindowText (hWnd, (LPSTR)"The current video mode is not palette based.");   
             
             EndPaint(hWnd,&ps);

             return 0;
         }

         // Divide client width into equal-sized parts, one per palette
         // entry, and re-calculate client width so that it will display
         // exactly as many vertical bars as there are palette entries.
         nSizeX = (rClientRect.right - rClientRect.left);
         nSizeX = (nSizeX/dwNumColors) * dwNumColors;
         
         nSizeY = rClientRect.bottom - rClientRect.top;
         GetWindowRect(hWnd,(LPRECT) &rClientRect);
         
         // Adjust window width so that it can display exactly
         // as many vertical bars( of equal width) as there are palette
         // colors.
         
         SetWindowPos( hWnd,
             (HWND)NULL,
             0,
             0,
             nSizeX + 2*nXBorder,
             rClientRect.bottom - rClientRect.top,
             SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
         
         hDC = BeginPaint(hWnd, &ps);
         
         
         // Select the palette into the window device context and
         // make the Palette Manager map the logical palette to the
         // system palette (realize it).
         SelectPalette (hDC, hPal, 1);
         RealizePalette (hDC);
         
         // Calculate width of each color bar to be displayed 
         nIncr = nSizeX / dwNumColors;
         
         // Paint the individual bars separately on the app. window 
         for (nStart = dwLoop = 0; dwLoop < dwNumColors; dwLoop++) {
             
             // Since this app. uses a logical palette, use the
             // PALETTEINDEX macro to specify the palette entry
             // index instead of using an explicit RGB value.
                 
             hBrush       = CreateSolidBrush (PALETTEINDEX (dwLoop));
			 if (!hBrush)
				 break;
             dwPal[dwLoop] = GetNearestColor (hDC, PALETTEINDEX (dwLoop) );
             hOldBrush    = SelectObject (hDC,hBrush) ;
             PatBlt (hDC, nStart, 0, nIncr, nSizeY, PATCOPY);
             nStart       += nIncr;
             SelectObject (hDC, hOldBrush);
             DeleteObject (hBrush) ;
         }
         _sntprintf (szTitlebuf, 89,"    MyPal Colors = %d", dwNumColors);
		 szTitlebuf [89] = '\0';
         SetWindowText (hWnd, (LPSTR)szTitlebuf);
         
         EndPaint(hWnd,&ps);
         
         break ;
         
     case WM_MOUSEMOVE:
         // Are we in a palette based mode?
         if (!InPaletteBasedVideoMode())
             break;  // No, bail.
         
         if (wParam & MK_RBUTTON) {
             
             POINT pnt;
             
#ifdef WIN16
             /* Convert mouse position to screen coordinates */
             pnt.x = LOWORD(lParam);
             pnt.y = HIWORD(lParam);
#else
             LONG2POINT(lParam, pnt);       
#endif
             ClientToScreen(hWnd, &pnt);
             
             /* Get RGB value (color) of pixel under mouse coordinate */
             dwColor = GetPixel(hDCGlobal, pnt.x, pnt.y);
             
             /* If color value already exists in palette lookup table,
             * obtain it's index.
             */
             for (i=0 ; i < dwNumColors ; i++)
                 if ( dwColor == dwPal[i] )
                     break;
                 dwIndex = i;
                 
                 /* If previous color value was not identical to current one,
                 * display color boxes on either side of title bar,
                 * the R, G, B values and palette index of current color.
                 */
                 if (dwColor != dwLastColor) {
					 _sntprintf ( szTitlebuf, 89,
                         "    MyPal Colors = %d  Index=%d  R=%3u G=%3u B=%3u",
                         dwNumColors,
                         dwIndex,
                         (WORD)(BYTE) GetRValue (dwColor),
                         (WORD)(BYTE) GetGValue (dwColor),
                         (WORD)(BYTE) GetBValue (dwColor));
					 szTitlebuf [89] = '\0';
                     SetWindowText (hWnd, (LPSTR)szTitlebuf);
                     ShowColor (hWnd, hDCGlobal);
                     dwLastColor = dwColor;
                 }
         }
         break;
         
     case WM_RBUTTONDOWN:
         // Are we in a palette based mode?
         if (!InPaletteBasedVideoMode())
             break;  // No, bail.
             
         // Determine number of color bar under mouse, thus the index
         // of color in palette.
         x = LOWORD(lParam);
         dwIndex = (x / nIncr );
         
         _sntprintf ( szTitlebuf, 89, 
             "    MyPal Colors = %d  Index=%d  PalSize=%d RasterCaps:%d",
             dwNumColors,
             dwIndex,
             dwNumColors,
             iRasterCaps );
         szTitlebuf [89] = '\0';
         SetWindowText (hWnd, (LPSTR)szTitlebuf);
         
         // Set mouse capture so that subsequent WM_MOUSEMOVEs
         // (with right mouse button depressed) will allow MyPal
         // to display RGB info anywhere on the screen without losing
         // the focus.
         SetCapture (hWnd);
         bCaptureOn = TRUE;
         hDCGlobal = GetDC(NULL);
         if (hPal) {
             SelectPalette (hDCGlobal, hPal, FALSE);
             RealizePalette (hDCGlobal);
         }
         break;
         
     case WM_RBUTTONUP:
         // Stops displaying RGB and palette info and releases mouse
         // capture
         ReleaseDC (NULL, hDCGlobal);
         bCaptureOn = FALSE;
         ReleaseCapture ();
         break;
         
     case WM_MOVE:
         // If you have a wide column, this adds 1/2 so X is centered 
         iGlobalXOffset  = LOWORD (lParam);
         iGlobalYOffset  = HIWORD (lParam) + nXBorder;
         break;
         
     case WM_SIZE:
         iYMiddle = (HIWORD (lParam)/2);
         break;
         
     case WM_LBUTTONDOWN:
     case WM_KEYDOWN:
         // Are we in a palette based mode?
         if (!InPaletteBasedVideoMode())
             break;  // No, bail.
        
         
         if (iMessage == WM_LBUTTONDOWN){
             // determine which column was hit by the mouse 
             x = LOWORD(lParam);
             dwIndex = (x / nIncr );
         }
         else{
             // Use arrow keys to step thro' the palette entries 
             switch (wParam) {
             case VK_RIGHT:
             case VK_UP:
                 // go to next (higher) palette entry 
                 dwIndex++;
                 break;
             case VK_LEFT:
             case VK_DOWN:
                 // go to previous (lower) palette entry 
                 dwIndex--;
                 break;
             case VK_NEXT:
                 dwIndex += 10;
                 break;
             case VK_PRIOR:
                 dwIndex -= 10;
                 break;
             case VK_HOME:
                 // go to first palette entry 
                 dwIndex = 0;
                 break;
             case VK_END:
                 // go to last palette entry 
                 dwIndex = dwNumColors-1;
                 break;
             default:
                 return 0L;
                 break;
             }
             // Make sure the palette index is within range else
             // set it to the limiting values and give a warning beep.
             if (dwIndex > dwNumColors-1) {
                 dwIndex = dwNumColors-1;
                 MessageBeep(1);
             }
             
             pt.x = (SHORT)((dwIndex * nIncr) +
                 iGlobalXOffset   +
                 ((nIncr > 1) ? (nIncr / 2) : 1));
             pt.y = (SHORT)(iYMiddle + iGlobalYOffset);
             
             SetCursorPos (pt.x, pt.y);
         }
         
         if (TRUE == bCaptureOn) {
             MessageBeep(1);
             break;
         }
         
         // Select & realize the palette or the colors > 0x7
         // will not match up.
         hDC = GetDC(NULL);
		 if (hPal)
         {
			 SelectPalette  (hDC, hPal, 1);
			 RealizePalette (hDC) ;
             dwColor = GetNearestColor (hDC, PALETTEINDEX (dwIndex));
             _sntprintf ( szTitlebuf, 89,
				 "    MyPal Colors = %d  Index=%d  R=%3u G=%3u B=%3u",
				 dwNumColors,
                 dwIndex,
                 (WORD)(BYTE)GetRValue (dwColor),
                 (WORD)(BYTE)GetGValue (dwColor),
                 (WORD)(BYTE)GetBValue (dwColor)
				 );
		         szTitlebuf [89] = '\0';
         
                 SetWindowText (hWnd, (LPSTR)szTitlebuf);
                 ShowColor (hWnd,hDC);
		 }
         ReleaseDC(NULL, hDC);
         break;
         
     default:
         return (long) DefWindowProc (hWnd, iMessage, wParam, lParam) ;
         
    }
    return 0L ;
}
