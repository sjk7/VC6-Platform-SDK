
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1993 - 2000 Microsoft Corp.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/***************************************************************************
 *                                                                         *
 *  PROGRAM     : Menu.c                                                   *
 *                                                                         *
 *  PURPOSE     : To give a demonstration of the use of popup menus, user  *
 *                defined menus and menu functions.                        *
 *                                                                         *
 *  FUNCTIONS   : WinMain()           - Calls the initialization function  *
 *                                      and enters the message loop.       *
 *                                                                         *
 *                MenuInit()          - Registers the app. window class.   *
 *                                                                         *
 *                AboutDialogProc ()  - Dialog function for the About..    *
 *                                      dialog.                            *
 *                                                                         *
 *                ShrinkBitmap()      - Shrinks a 64x64 bitmap to a size   *
 *                                      useable for a user-defined menu    *
 *                                      checkmark.                         *
 *                                                                         *
 *                HandleCreate()      - Creates a new menu and appends it  *
 *                                      to the main menu                   *
 *                                                                         *
 *                HandlePaint()       - Handles repainting the app's client*
 *                                      area                               *
 *                                                                         *
 *                HandleChangeColors()- Changes the state of the "colors"  *
 *                                      menu item.                         *
 *                                                                         *
 *                HandleDrawItem()    - Redraws the menu items in the      *
 *                                      "colors" menu                      *
 *                                                                         *
 *                HandlePopupMenu()   - handles display of the "floating"  *
 *                                      popup.                             *
 *                                                                         *
 *                MenuWindowProc()    - Window function for the app.       *
 *                                                                         *
 *                                                                         *
 ***************************************************************************/
#include <windows.h>
#include <tchar.h>
#include "menu.h"


HINSTANCE hInst;
HMENU     hBigMenu;
HBITMAP   hbmCheckOn;
HBITMAP   hbmCheckOff;

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : WinMain (HINSTANCE, HINSTANCE, LPSTR, int)                 *
 *                                                                          *
 *  PURPOSE    : Creates the main app. window, calls an initialization      *
 *               function and enters the message loop.                      *
 *                                                                          *
 ****************************************************************************/
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow )
{
    HWND hWnd = NULL;
    MSG  msg = {0};   /* message */
    BOOL bRet = FALSE;
    BOOL bSuccess = TRUE;

    if (!MenuInit (hInstance))
    {
        bSuccess = FALSE;
        goto exit_func;
    }

    hInst = hInstance;

    /* Create the app. window */
    hWnd = CreateWindow (TEXT("menu"),
                         TEXT("Menu Example"),
                         WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT, 0,
                         CW_USEDEFAULT, 0,
                         NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        bSuccess = FALSE;
        goto exit_func;
    }

    ShowWindow (hWnd, nCmdShow);
    UpdateWindow (hWnd);
    
    while (bRet = GetMessage (&msg, NULL, 0, 0) != 0)
    {
        if (bRet == -1)
        {
            bSuccess = FALSE;
            goto exit_func;
        }
        else
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }

exit_func:
    if (bSuccess)
    {
        return (int) msg.wParam;
    }
    else
    {
        return 0;
    }
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : MenuInit (hInstance)                                       *
 *                                                                          *
 *  PURPOSE    : Registers the main window class.                           *
 *                                                                          *
 *  RETURNS    : TRUE   -  if RegisterClass() went off ok                   *
 *               FALSE  -  otherwise.                                       *
 *                                                                          *
 ****************************************************************************/
BOOL MenuInit (
    HINSTANCE hInstance )
{
    WNDCLASS wc = {0};

    wc.lpfnWndProc   = (WNDPROC) MenuWindowProc;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon (hInstance, TEXT("menu"));
    wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName  = TEXT("MenuMenu");
    wc.lpszClassName = TEXT("menu");
    
    return RegisterClass (&wc);
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : AboutDialogProc (hDlg, message, wParam, lParam)            *
 *                                                                          *
 *  PURPOSE    : Dialog function for the About menu... dialog.              *
 *                                                                          *
 ****************************************************************************/
INT_PTR CALLBACK AboutDialogProc (
    HWND   hDlg,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam )
{
    BOOL ret = FALSE;
    
    switch (msg)
    {
        case WM_INITDIALOG:
            ret = TRUE;
            break;

        case WM_COMMAND:
            // LOWORD added for portability
            if (LOWORD(wParam) == IDOK)
            {
                EndDialog (hDlg, 0);
                ret = TRUE;
            }
            else
            {
                ret = FALSE;
            }
            break;

        case WM_SYSCOMMAND:
            if (wParam == SC_CLOSE)
            {
                EndDialog (hDlg, 0);
                ret = TRUE;
            }
            else
            {
                ret = FALSE;
            }
            break;

            
        default:
            ret = FALSE;
            break;
    }
    
    return (INT_PTR) ret;
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : ShrinkBitmap(hwnd, hbm)                                    *
 *                                                                          *
 *  PURPOSE    : This function shrinks a 64x64 bitmap into a bitmap useable *
 *               for the user-defined checkmark for menu items. This can be *
 *               easily generalized to shrink bitmaps of any size.          *
 *                                                                          *
 *  RETURNS    : HBITMAP - A handle to the new bitmap.                      *
 *                                                                          *
 ****************************************************************************/
HBITMAP ShrinkBitmap (
    HWND    hwnd,
    HBITMAP hbm )
{
    HDC     hdc            = NULL;
    HDC     hmemorydcNew   = NULL;
    HDC     hmemorydcOld   = NULL;
    LONG    checkMarkSize  = 0;
    HBITMAP hCheckBitmap   = NULL;
    HBITMAP hOldBitmapSave = NULL;
    HBITMAP hNewBitmapSave = NULL;

    hdc = GetDC (hwnd);

    /* Create DCs for the source (old) and target (new) bitmaps */
    hmemorydcNew = CreateCompatibleDC (hdc);
    hmemorydcOld = CreateCompatibleDC (hdc);

    /* Determine the dimensions of the default menu checkmark and
     * create a target bitmap of the same dimensions
     */
    checkMarkSize = GetMenuCheckMarkDimensions ();
    hCheckBitmap  = CreateCompatibleBitmap (hdc,
                                            LOWORD (checkMarkSize),
                                            HIWORD (checkMarkSize));

    /* Select the source bitmap and the target bitmap into their
     * respective DCs.
     */
    hOldBitmapSave = SelectObject (hmemorydcNew, hCheckBitmap);
    hNewBitmapSave = SelectObject (hmemorydcOld, hbm);

    /* Shrink the source bitmap into the target DC */
    StretchBlt (hmemorydcNew,
                0, 0,
                LOWORD(checkMarkSize),
                HIWORD(checkMarkSize),
                hmemorydcOld,
                0, 0,
                64, 64,
                SRCCOPY);

    /* De-select the bitmaps and clean up .. */
    SelectObject (hmemorydcNew, hOldBitmapSave);
    SelectObject (hmemorydcOld, hNewBitmapSave);
    DeleteDC (hmemorydcNew);
    DeleteDC (hmemorydcOld);
    ReleaseDC (hwnd, hdc);

    /* .. and return a handle to the target bitmap */
    return hCheckBitmap;
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : HandleCreate ( hwnd )                                      *
 *                                                                          *
 *  PURPOSE    : Creates a new (empty) menu and appends to it the "State"   *
 *               menu items. It sets up the user-defined checkmarks for the *
 *               menu. It then inserts this menu into the main menu bar.    *
 *                                                                          *
 ****************************************************************************/
VOID HandleCreate (
    HWND hwnd)
{
    HMENU   hMenu    = NULL;
    HMENU   hWndMenu = NULL;

    /* Create a new menu into the menubar on the fly */
    hMenu = CreateMenu ();
    if (!hMenu)
    {
        return;
    }

    /* Append the state menu items to it */
    AppendMenu (hMenu, MF_STRING, IDM_STATE1, TEXT("South Dakota"));
    AppendMenu (hMenu, MF_STRING, IDM_STATE2, TEXT("Washington"));
    AppendMenu (hMenu, MF_STRING, IDM_STATE3, TEXT("California"));
    if (!AppendMenu (hMenu, MF_STRING, IDM_STATE4, TEXT("Oregon")))
    {
        /* It is unlikely the other appends will fail and this will succeed.
         * So just check this one. And if it fails, Destroy the menu for
         * good measure and return.
         */
        DestroyMenu(hMenu);
        return;
    }
    hbmCheckOn  = ShrinkBitmap (hwnd, LoadBitmap (hInst, TEXT("checkon")));
    hbmCheckOff = ShrinkBitmap (hwnd, LoadBitmap (hInst, TEXT("checkoff")));

    /* Set up the user-defined check marks */
    SetMenuItemBitmaps (hMenu, 0, MF_BYPOSITION, hbmCheckOff, hbmCheckOn);
    SetMenuItemBitmaps (hMenu, 1, MF_BYPOSITION, hbmCheckOff, hbmCheckOn);
    SetMenuItemBitmaps (hMenu, 2, MF_BYPOSITION, hbmCheckOff, hbmCheckOn);
    SetMenuItemBitmaps (hMenu, 3, MF_BYPOSITION, hbmCheckOff, hbmCheckOn);

    /* Now insert the menu into the main menu bar. */
    hWndMenu = GetMenu (hwnd);
    InsertMenu (hWndMenu, 2, MF_POPUP|MF_BYPOSITION, (DWORD_PTR)hMenu, TEXT("States"));

    return;
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : HandlePaint ( hwnd )                                       *
 *                                                                          *
 *  PURPOSE    : Handles the repainting of the main app's client area.      *
 *                                                                          *
 ****************************************************************************/
VOID HandlePaint (
    HWND hwnd )
{
    HDC         hdc = NULL;
    PAINTSTRUCT ps  = {0};
    RECT        rc  = {0};
    TCHAR       text[] = TEXT("Click in the window for a popup menu");

    hdc = BeginPaint (hwnd, (LPPAINTSTRUCT)&ps);

    /* Center the text in the client area */
    GetClientRect (hwnd, &rc);
    DrawText (hdc,
              text,
              (INT)_tcslen (text),
              &rc,
              DT_CENTER | DT_WORDBREAK);
    EndPaint(hwnd, (LPPAINTSTRUCT)&ps);
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : HandleChangeColors (hwnd)                                  *
 *                                                                          *
 *  PURPOSE    : Toggles the state of the Owner Draw item in the Colors     *
 *               menu. If it is on, the "Black", "Blue", "Red", and "Green" *
 *               individual menu text items are modified so that they will  *
 *               contain bands of color. Otherwise, the colors are replaced *
 *               by the text.                                               *
 *                                                                          *
 ****************************************************************************/
VOID HandleChangeColors (
    HWND hwnd )
{
    HMENU hMenu      = NULL;
    BOOL  fOwnerDraw = FALSE;

    /* Get a handle to the Colors menu. This is at position 1. */
    hMenu = GetSubMenu (GetMenu (hwnd), IDCOLORS_POS);

    /* Get the current state of the item */
    fOwnerDraw = GetMenuState ( hMenu,
                                IDM_COLOROWNERDR, MF_BYCOMMAND) & MF_CHECKED;

    /* Toggle the state of the item. */
    CheckMenuItem ( hMenu,
                    IDM_COLOROWNERDR,
                    MF_BYCOMMAND | (fOwnerDraw ? MF_UNCHECKED : MF_CHECKED));

    if (!fOwnerDraw)
    {
        /* Change the items to owner-draw items. Pass the RGB value for the
         * color as the application-supplied data. This makes it easier for
         * us to draw the items.
         */
        ModifyMenu(hMenu,
                   IDM_BLACK,
                   MF_OWNERDRAW | MF_BYCOMMAND,
                   IDM_BLACK,
                   (LPCTSTR)(INT_PTR)RGB (0,0,0));

        ModifyMenu(hMenu,
                   IDM_BLUE,
                   MF_OWNERDRAW | MF_BYCOMMAND,
                   IDM_BLUE,
                   (LPCTSTR)(INT_PTR)RGB (0,0,255));

        ModifyMenu(hMenu,
                   IDM_RED,
                   MF_OWNERDRAW | MF_BYCOMMAND,
                   IDM_RED,
                   (LPCTSTR)(INT_PTR)RGB (255,0,0));

        ModifyMenu(hMenu,
                   IDM_GREEN,
                   MF_OWNERDRAW | MF_BYCOMMAND,
                   IDM_GREEN,
                   (LPCTSTR)(INT_PTR)RGB (0,255,0));
    }
    else 
    {
        /* Change the items to normal text items. */
        ModifyMenu(hMenu, IDM_BLACK, MF_BYCOMMAND, IDM_BLACK, TEXT("Black"));
        ModifyMenu(hMenu, IDM_BLUE,  MF_BYCOMMAND, IDM_BLUE,  TEXT("Blue"));
        ModifyMenu(hMenu, IDM_RED,   MF_BYCOMMAND, IDM_RED,   TEXT("Red"));
        ModifyMenu(hMenu, IDM_GREEN, MF_BYCOMMAND, IDM_GREEN, TEXT("Green"));
    }
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : HandleDrawItem ( hwnd, lpdis)                              *
 *                                                                          *
 *  PURPOSE    : Called in response to a WM_DRAWITEM message, i.e. when the *
 *               colors menu is being modified to an owner-draw menu, or    *
 *               one of the items is selected. It sizes the checkmark bitmap*
 *               to fit next to a color band and draws the color bands and  *
 *               the checkmark on the popup menu.                           *
 *                                                                          *
 ****************************************************************************/
VOID HandleDrawItem (
        HWND             hwnd,
        LPDRAWITEMSTRUCT lpdis )

{
    HDC     hdcBitmap      = NULL;
    HBITMAP hbmSave        = NULL;
    HBRUSH  hbr            = NULL;
    RECT    rc             = {0};
    LONG    checkMarkSize  = 0;
    DWORD   textColorSave  = 0;
    DWORD   bkColorSave    = 0;

    /* Get the size of the checkmark so we can leave room for it since we
     * want to be able to check the selected color.
     */
    checkMarkSize = GetMenuCheckMarkDimensions ();

    if (lpdis->itemAction == ODA_SELECT ||
        lpdis->itemAction == ODA_DRAWENTIRE)
    {
        CopyRect ((LPRECT)&rc, (LPRECT)&lpdis->rcItem);
        InflateRect ((LPRECT)&rc, (-2 - LOWORD(checkMarkSize)), -2);

        if (lpdis->itemState & ODS_SELECTED)
        {
            /* Item has been selected -- hilite with a gray frame */
            hbr = GetStockObject (GRAY_BRUSH);
            FrameRect (lpdis->hDC, (LPRECT)&rc, hbr);
        }
        else if (lpdis->itemAction == ODA_SELECT)
        {
            /* Item has been de-selected -- remove gray frame */
            hbr = CreateSolidBrush (GetSysColor (COLOR_MENU));
            FrameRect (lpdis->hDC, (LPRECT)&rc, hbr);
            DeleteObject (hbr);
        }
    }

    if (lpdis->itemAction == ODA_DRAWENTIRE)
    {
        /* Paint the color item in the color requested. */
        hbr = CreateSolidBrush ((COLORREF) lpdis->itemData);
        CopyRect ((LPRECT)&rc, (LPRECT)&lpdis->rcItem);
        InflateRect ((LPRECT)&rc, -10-LOWORD(checkMarkSize), -10);
        FillRect (lpdis->hDC, (LPRECT)&rc, hbr);
        DeleteObject (hbr);

        if (lpdis->itemState & ODS_CHECKED)
        {
            /* Draw the check mark if the item is checked. */
            hdcBitmap = CreateCompatibleDC (lpdis->hDC);
            hbmSave = SelectObject (hdcBitmap, hbmCheckOn);

            textColorSave = SetTextColor (lpdis->hDC, 0x00000000L);
            bkColorSave   = SetBkColor (lpdis->hDC, 0x00FFFFFFL);

            /* Use Magic bitblt op so that monochrome bitmaps preserve
               background and foreground colors. */
            BitBlt (lpdis->hDC,
                    lpdis->rcItem.left,
                    lpdis->rcItem.top+
                           (MEASUREITEMHEIGHT - HIWORD (checkMarkSize)) / 2,
                    LOWORD (checkMarkSize),
                    HIWORD (checkMarkSize),
                    hdcBitmap,
                    0,
                    0,
                    ROP_PSDPxax);

            /* Restore colors and bitmap and clean up */
            SetTextColor (lpdis->hDC, textColorSave);
            SetBkColor (lpdis->hDC, bkColorSave);
            SelectObject (hdcBitmap, hbmSave);
            DeleteDC (hdcBitmap);
        }
    }
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : HandlePopupMenu (hwnd, point)                              *
 *                                                                          *
 *  PURPOSE    : Handles the display of the "floating" popup that appears   *                                                           *
 *               on a mouse click in the app's client area.                 *
 *                                                                          *
 ****************************************************************************/
VOID HandlePopupMenu (
        HWND   hwnd,
        POINT point )

{
    HMENU hMenu           = NULL;
    HMENU hMenuTrackPopup = NULL;

    /* Get the menu for the popup from the resource file. */
    hMenu = LoadMenu (hInst, TEXT("PopupMenu"));
    if (!hMenu)
    {
        return;
    }

    /* Get the first menu in it which we will use for the call to
     * TrackPopup(). This could also have been created on the fly using
     * CreatePopupMenu and then we could have used InsertMenu() or
     * AppendMenu.
     */
    hMenuTrackPopup = GetSubMenu (hMenu, 0);

    /* Convert the mouse point to screen coordinates since that is what
     * TrackPopup expects.
     */
    ClientToScreen (hwnd, (LPPOINT)&point);

    /* Draw and track the "floating" popup */
    TrackPopupMenu (hMenuTrackPopup, 0, point.x, point.y, 0, hwnd, NULL);

    /* Destroy the menu since were are done with it. */
    DestroyMenu (hMenu);
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : MenuWindowProc (hWnd, message, wParam, lParam)                *
 *                                                                          *
 *  PURPOSE    : Window function for the main app. window. Processes all the*
 *               menu selections and oter messages.                         *
 *                                                                          *
 ****************************************************************************/
LRESULT CALLBACK MenuWindowProc (
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam )

{
    HMENU hMenu   = NULL;
    RECT  rc      = {0};
    POINT pt      = {0};
    BOOL  bRetDWP = FALSE;


    switch (message)
    {
        case WM_SYSCOMMAND:
            /* Show the About ... dialog */
            if (wParam == ID_ABOUT)
            {
                DialogBox (hInst,
                           TEXT("AboutBox"),
                           hWnd,
                           AboutDialogProc);
                break;
            }
            else
            {
                bRetDWP = TRUE;
                goto exit_func;
            }

        case WM_COMMAND:
            // LOWORD added for portability
            switch (LOWORD(wParam))
            {
                 case IDM_EXIT:
                   DestroyWindow (hWnd);
                   break;

                 case IDM_ABOUT:
                   /* Bring up the About.. dialog box */
                   DialogBox (hInst,
                              TEXT("AboutBox"),
                              hWnd,
                              AboutDialogProc);
                   break;

                 case IDM_COLOROWNERDR:
                     /* Change colors in color menu depending on state of this
                        menu item. */
                     HandleChangeColors (hWnd);
                     break;

                 case IDM_STATE1: /* fall through */
                 case IDM_STATE2: /* fall through */
                 case IDM_STATE3: /* fall through */
                 case IDM_STATE4: 
                      /* Get a handle to the states menu... */
                      hMenu = GetSubMenu (GetMenu (hWnd), IDSTATES_POS);

                      /* Uncheck all the items. */
                      CheckMenuItem (hMenu, IDM_STATE1,
                                     MF_BYCOMMAND | MF_UNCHECKED);
                      CheckMenuItem (hMenu, IDM_STATE2,
                                     MF_BYCOMMAND | MF_UNCHECKED);
                      CheckMenuItem (hMenu, IDM_STATE3,
                                     MF_BYCOMMAND | MF_UNCHECKED);
                      CheckMenuItem (hMenu, IDM_STATE4,
                                     MF_BYCOMMAND | MF_UNCHECKED);

                      /* ...and just check the selected one.*/
                      CheckMenuItem (hMenu, (WORD)wParam,
                                     MF_BYCOMMAND | MF_CHECKED);
                     break;

                 case IDM_BLACK: /* fall through */
                 case IDM_RED:   /* fall through */
                 case IDM_BLUE:  /* fall through */
                 case IDM_GREEN: 
                      /* Get a handle to the Colors menu. */
                      hMenu = GetSubMenu (GetMenu (hWnd),IDCOLORS_POS);

                      /* Uncheck all the items. */
                      CheckMenuItem (hMenu, IDM_BLACK,
                                     MF_BYCOMMAND | MF_UNCHECKED);
                      CheckMenuItem (hMenu, IDM_RED,
                                     MF_BYCOMMAND | MF_UNCHECKED);
                      CheckMenuItem (hMenu, IDM_BLUE,
                                     MF_BYCOMMAND | MF_UNCHECKED);
                      CheckMenuItem (hMenu, IDM_GREEN,
                                     MF_BYCOMMAND | MF_UNCHECKED);

                      /* ...and just check the selected one.*/
                      CheckMenuItem (hMenu, (WORD)wParam,
                                     MF_BYCOMMAND | MF_CHECKED);
                      break;

                 case IDM_FONT:
                      /* Messages sent to us from TrackPopupMenu when
                       * items are selected from the "floating" popups
                       */
                      MessageBox (hWnd,
                                  TEXT("A font was selected"),
                                  TEXT("Popup Menu Alert"),
                                  MB_APPLMODAL|MB_OK);
                      break;

                 case IDM_SIZE:
                      MessageBox (hWnd,
                                  TEXT("A size was selected"),
                                  TEXT("Popup Menu Alert"),
                                  MB_APPLMODAL|MB_OK);
                      break;

                 case IDM_STYLE:
                      MessageBox (hWnd,
                                  TEXT("A style was selected"),
                                  TEXT("Popup Menu Alert"),
                                  MB_APPLMODAL|MB_OK);
                      break;
            }
            break;

        case WM_SIZE:
            if (lParam)
            {
                /* If window is being sized to a non zero value...
                 * invalidate it's client area.
                 */
                InvalidateRect (hWnd, NULL, TRUE);
            }
            break;

        case WM_PAINT:
            HandlePaint (hWnd);
            break;

        case WM_MEASUREITEM:
            /* Use the same width for all items. We could examine the item id
               and use different widths/heights for each item. */
            ((LPMEASUREITEMSTRUCT)lParam)->itemWidth  = MEASUREITEMWIDTH;
            ((LPMEASUREITEMSTRUCT)lParam)->itemHeight = MEASUREITEMHEIGHT;
            return TRUE;
            break;

        case WM_DRAWITEM:
            /* Redraw the "colors" menu in normal/ownerdrawmode */
            HandleDrawItem (hWnd,(LPDRAWITEMSTRUCT)lParam);
            return TRUE;
            break;

        case WM_CREATE:
            /* Create the menu */
            HandleCreate (hWnd);
            break;

        case WM_DESTROY:
            /* Delete the on/off bitmaps so that they don't waste memory. */
            DeleteObject (hbmCheckOn);
            DeleteObject (hbmCheckOff);

            PostQuitMessage (0);
            break;

        case WM_LBUTTONDOWN:
            /* Draw the "floating" popup in the app's client area */
            GetClientRect (hWnd, (LPRECT)&rc);

            // Temporary porting macro
            LONG2POINT(lParam, pt);
            if (PtInRect ((LPRECT)&rc, pt))
            {
                HandlePopupMenu (hWnd, pt);
            }
            break;

        default:
            bRetDWP = TRUE;
            goto exit_func;
            break;
    }

exit_func:
    if (bRetDWP)
    {
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
    else
    {
        return 0;
    }
}
