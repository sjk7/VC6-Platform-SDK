// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993 - 2000  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     wndproc.c
//
//  PURPOSE:    Contains window procedure and message handlers for the 
//              main appbar window.
//
//  PLATFORMS:  Windows 95, Windows 98, Windows 2000, Windows NT 4.0
//
//  FUNCTIONS:
//      MainWndProc()       - Message handler for the main application window
//      Main_OnCreate()     - Handles window initialization
//      Main_OnActivate()   - Handles autohide showing and hiding
//      Main_OnWindowPosChanged - Notifies the system of the window change
//      Main_OnCommand()    - Processes WM_COMMAND messages
//      Main_OnSize()       - Notifies the system of the size change
//      Main_OnMove()       - Notifies the system the window moved
//      Main_OnRButtonDown()- Shows a context menu with appbar options
//      Main_OnDestroy()    - Handles the WM_DESTROY message
//      Main_OnTimer()      - Does autohide stuff
//      Main_OnNCHitTest()  - Prevents sizing in unacceptable directions
//      Main_OnPaint()      - Draws instructions into the window    
//      AboutDlgProc()      - Message handler for the application's about 
//                            dialog.
//



#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include "resource.h"
#include "globals.h"
#include "appbar.h"
 


//////////////////////////////////////////////////////////////////////////////
// Local prototypes

BOOL Main_OnCreate(HWND, LPCREATESTRUCT);
void Main_OnActivate(HWND, UINT, HWND, BOOL);
void Main_OnWindowPosChanged(HWND, const LPWINDOWPOS);
void Main_OnCommand(HWND, int, HWND, UINT);
void Main_OnSize(HWND, UINT, int, int);
void Main_OnMove(HWND, int, int);
void Main_OnRButtonDown(HWND, BOOL, int, int, UINT);
void Main_OnDestroy(HWND);
void Main_OnTimer(HWND, UINT);
UINT Main_OnNCHitTest(HWND, int, int);
void Main_OnPaint(HWND);
void Main_OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
void Main_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void Main_OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);


LRESULT CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);


//////////////////////////////////////////////////////////////////////////////
// Global Variables

static HFONT g_hFontTop, g_hFontBottom, g_hFontLeft, g_hFontRight;
static BOOL g_fMoving = FALSE;
static RECT g_rcDrag;


//
//  FUNCTION:   MainWndProc(HWND, UINT, WPARAM, LPARAM) 
//
//  PURPOSE:    Processes messages for the main application window.
//
//  PARAMETERS:
//      hwnd        - handle the the window receiving the message
//      uMsg        - identifier of the message
//      wParam      - additional info associated with the message
//      lParam      - additional info associated with the message
//
//  RETURN VALUE:
//      (LRESULT) Returns 0 by default if the message is handled by this 
//                procedure.
//

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, 
                             LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hwnd, WM_CREATE,           Main_OnCreate);
        HANDLE_MSG(hwnd, WM_ACTIVATE,         Main_OnActivate);
        HANDLE_MSG(hwnd, WM_WINDOWPOSCHANGED, Main_OnWindowPosChanged);
        HANDLE_MSG(hwnd, WM_COMMAND,          Main_OnCommand);
        HANDLE_MSG(hwnd, WM_SIZE,             Main_OnSize);
        HANDLE_MSG(hwnd, WM_MOVE,             Main_OnMove); 
        HANDLE_MSG(hwnd, WM_RBUTTONDOWN,      Main_OnRButtonDown);
        HANDLE_MSG(hwnd, WM_DESTROY,          Main_OnDestroy);
        HANDLE_MSG(hwnd, WM_TIMER,            Main_OnTimer);
        HANDLE_MSG(hwnd, WM_NCHITTEST,        Main_OnNCHitTest);
        HANDLE_MSG(hwnd, WM_PAINT,            Main_OnPaint);
        HANDLE_MSG(hwnd, WM_LBUTTONDOWN,      Main_OnLButtonDown);
        HANDLE_MSG(hwnd, WM_MOUSEMOVE,        Main_OnMouseMove);
        HANDLE_MSG(hwnd, WM_LBUTTONUP,        Main_OnLButtonUp);

        case APPBAR_CALLBACK:
            AppBar_Callback(hwnd, uMsg, wParam, lParam);
            return (0);
    
        default:                // Pass message on for default proccessing
            return DefWindowProc( hwnd, uMsg, wParam, lParam );
    }

    // If we performed non-default processing on the message, return FALSE
    return FALSE;
}


//
//  FUNCTION:   Main_OnCreate(HWND, LPCREATESTRUCT)
//
//  PURPOSE:    Handles any window initialization for this window class.
//
//  PARAMETERS:
//      hwnd           - Handle of the window being created.
//      lpCreateStruct - Pointer to the data used to create this window.
//
//  RETURN VALUE:
//      Returns TRUE to allow the window to be created, FALSE otherwise.
//

BOOL Main_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    POPTIONS pOptions;
    LOGFONT lf;

    // Initialize the common control DLL
    InitCommonControls();

    // Allocate an OPTIONS struct and attach to the appbar
    pOptions = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(OPTIONS));
    if (pOptions)
        SetWindowLongPtr(hwnd, 0,(LONG_PTR)pOptions);
    else
        return (FALSE);

    pOptions->fAutoHide = FALSE;
    pOptions->fOnTop = FALSE;
    pOptions->uSide = ABE_TOP;
    pOptions->cxWidth = CX_DEFWIDTH;
    pOptions->cyHeight = CY_DEFHEIGHT;

    // Register the appbar and attach it to the top by default
    AppBar_Register(hwnd);
    AppBar_SetSide(hwnd, ABE_TOP);

    // Create the fonts for drawing in the client area
    ZeroMemory(&lf,sizeof(LOGFONT));
    lf.lfHeight = 45;
    lf.lfEscapement = 2700;
    lf.lfOrientation = 0;
    lstrcpyn(lf.lfFaceName, TEXT("Arial"), sizeof(lf.lfFaceName)/sizeof(lf.lfFaceName[0]));
    g_hFontLeft = CreateFontIndirect(&lf);

    lf.lfEscapement = 0;
    g_hFontTop = CreateFontIndirect(&lf);
    
        
    return (TRUE);
}


//
//  FUNCTION:   Main_OnActivate(HWND, UINT, HWND, BOOL) 
//
//  PURPOSE:    Handles hiding and showing of the appbar if it has the autohide
//              state set.
//
//  PARAMETERS:
//      hwnd         - Handle of the window receiving the message.
//      state        - Specifies whether the winodw is being activated or 
//                     deactivated.
//      hwndActDeact - Identifies the window being activated or deactivated, 
//                     depending on the state parameter.
//      fMinimized   - A nonzero value indicates the window is minmized.
//

void Main_OnActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized)
{
    APPBARDATA abd;
    
    // Always send the activate message to the system
    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = hwnd;
    abd.lParam = 0;                
    SHAppBarMessage(ABM_ACTIVATE, &abd);

    // Now determine if we're getting or losing activation
    switch (state)
    {
        case WA_ACTIVE:
        case WA_CLICKACTIVE:
            // If we're gaining activation, make sure we're visible
            AppBar_UnHide(hwnd);
            KillTimer(hwnd, IDT_AUTOHIDE);
            break;

        case WA_INACTIVE:
            // If we're losing activation, check to see if we need to autohide.
            AppBar_Hide(hwnd);
            break;
    }
}


//
//  FUNCTION:   Main_OnWindowPosChanged(HWND, const LPWINDOWPOS)
//
//  PURPOSE:    Notifies the system that the appbar has changed position.
//
//  PARAMETERS: 
//      hwnd    - Handle of the appbar window receiving the message
//      lpwpos  - Pointer to a WINDOWPOS struct containing information about
//                the new window position.
//
    
void Main_OnWindowPosChanged(HWND hwnd, const LPWINDOWPOS lpwpos)
{
    APPBARDATA abd;

    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = hwnd;
    abd.lParam = 0;

    SHAppBarMessage(ABM_WINDOWPOSCHANGED, &abd);

    // DefWindowProc needs this to generate the WM_SIZE message.
    FORWARD_WM_WINDOWPOSCHANGED(hwnd, lpwpos, DefWindowProc);
}


//
//  FUNCTION:   Main_OnCommand(HWND, int, HWND, UINT) 
//
//  PURPOSE:    Handles the WM_COMMAND messages for the Win32Generic window 
//              class
//
//  PARAMETERS:
//      hwnd        - handle of the window receiving the message
//      id          - identifier of the command
//      hwndCtl     - handle of the control sending the message)
//      codeNotify  - specifies the notification code if the message is from
//                    a control
//
//  RETURN VALUE:
//      none
//
//  COMMENTS:
//      codeNotify is 1 if from an accelerator, 0 if from a menu.
//      If the message is not from a control hwndCtl is NULL.
//

void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
        case ID_FILE_EXIT:
            // The user wants to exit, so send our window a close message
            SendMessage(hwnd, WM_CLOSE, 0, 0L);
            break;

        case ID_HELP_ABOUT:
            // Display the "About" dialog
            DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_ABOUT), hwnd,
                      AboutDlgProc);
            break;

        case ID_PROPERTIES:
            ShowOptions(hwnd);
            break;

        case ID_APPBAR_REGISTER:
            AppBar_Register(hwnd);
            break;

        case ID_APPBAR_UNREGISTER:
            AppBar_UnRegister(hwnd);
            break;

        case ID_APPBAR_AUTOHIDE:
            AppBar_SetAutoHide(hwnd, TRUE);
            break;

        case ID_APPBAR_NOAUTOHIDE:
            AppBar_SetAutoHide(hwnd, FALSE);
            break;      

        case ID_APPBAR_TOP:
            AppBar_SetSide(hwnd, ABE_TOP);
            break;

        case ID_APPBAR_BOTTOM:
            AppBar_SetSide(hwnd, ABE_BOTTOM);
            break;

        case ID_APPBAR_LEFT:
            AppBar_SetSide(hwnd, ABE_LEFT);
            break;

        case ID_APPBAR_RIGHT:
            AppBar_SetSide(hwnd, ABE_RIGHT);
            break;
    }
}


//
//  FUNCTION:   Main_OnSize(HWND, UINT, int, int)
//
//  PURPOSE:    Notifies the system the appbar size has changed and updates the
//              width and height stored in the OPTIONS struct.
//
//  PARAMETERS:
//      hwnd    - Handle of the appbar window receiving the message.
//      state   - Determines the type of sizing that occured.
//      cx      - New width of the client area.
//      cy      - New height of the client area.
//
//  COMMENTS:
//      TODO: If the client rect size is zero and the bar is on the top or 
//      right, then the user will not be able to resize the window

void Main_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
    POPTIONS pOpt = GetAppbarData(hwnd);
    RECT rcWindow;

    if (g_fMoving || pOpt->fAutoHide)
        return;

    // If the client width or height is zero, spew out a warning.
    if (!pOpt->fHiding && ((cx == 0) || (cy == 0)))
        DebugMsg(TEXT("Client area has a zero dimension!\r\n"));

    // Let the system know the appbar size has changed
    AppBar_Size(hwnd);

    // Update the stored height and widths if the appbar is not hidden
    if (!pOpt->fHiding)
    {
        GetWindowRect(hwnd, &rcWindow);

        if (pOpt->uSide == ABE_TOP || pOpt->uSide == ABE_BOTTOM)
            pOpt->cyHeight = rcWindow.bottom - rcWindow.top;
        else
            pOpt->cxWidth = rcWindow.right - rcWindow.left;

        DebugMsg(TEXT("Main_OnSize: cxWidth = %d, cyHeight = %d\r\n"),
                 pOpt->cxWidth, pOpt->cyHeight);
    }
}


//
//  FUNCTION:   Main_OnMove(HWND, int, int)
//
//  PURPOSE:    Notifies the system the appbar has moved.
//
//  PARAMETERS:
//      hwnd    - Handle of the appbar window receiving the message.
//      x       - New x-coordinate of the upper left corner of the client area
//      y       - New y-coordinate of the upper left corner of the client area
//

void Main_OnMove(HWND hwnd, int x, int y)
{
    POPTIONS pOpt = GetAppbarData(hwnd);

    if (g_fMoving || pOpt->fAutoHide)
        return;
    AppBar_Size(hwnd);
}


//
//  FUNCTION:   Main_OnRButtonDown(HWND, BOOL, int, int, UINT)
//
//  PURPOSE:    Displays the context menu for the appbar.
//
//  PARAMETERS:
//      hwnd     - Handle of the window receiving this message.
//      x, y     - Position of the mouse in client coordinates.
//      keyFlags - State of the keyboard when the mouse button was pressed.
//
//

void Main_OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, 
                        UINT keyFlags)
{
    HMENU hMenu, hSubMenu;
    POINT pt = {x, y};
    MENUITEMINFO mii;
    POPTIONS pOptions = GetAppbarData(hwnd);
    UINT uItem;
    TCHAR szMenu[64];

    // Bring up the context menu
    hMenu = LoadMenu(g_hInstance, MAKEINTRESOURCE(IDR_CONTEXTMENU));
    hSubMenu = GetSubMenu(hMenu, 0);

    // Convert the mouse position to screen coordinates
    ClientToScreen(hwnd, &pt);

    // Set the default menu item
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STATE;
    mii.fState = MFS_DEFAULT;
    
    SetMenuItemInfo(hSubMenu, ID_PROPERTIES, FALSE, &mii);

    // Set the radio button to the side we're on
    if (ABE_TOP == pOptions->uSide)
        uItem = ID_APPBAR_TOP;
    else if (ABE_BOTTOM == pOptions->uSide)
        uItem = ID_APPBAR_BOTTOM;
    else if (ABE_LEFT == pOptions->uSide)
        uItem = ID_APPBAR_LEFT;
    else
        uItem = ID_APPBAR_RIGHT;

    mii.fMask = MIIM_TYPE | MIIM_STATE;
    (LPTSTR) mii.dwTypeData = szMenu;
    mii.cch = sizeof(szMenu);

    GetMenuItemInfo(hSubMenu, uItem, FALSE, &mii);

    mii.fType |= MFT_RADIOCHECK;
    mii.fState = MFS_CHECKED;

    SetMenuItemInfo(hSubMenu, uItem, FALSE, &mii);

    // Display the menu
    TrackPopupMenu(hSubMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);   
}


//
//  FUNCTION:   Main_OnDestroy(HWND) 
//
//  PURPOSE:    Handle any clean up and post the quit message to exit the 
//              message loop.
//
//  PARAMETERS:
//      hwnd    - handle of the window receiving this message
//

void Main_OnDestroy(HWND hwnd)
{
    POPTIONS pOptions = GetAppbarData(hwnd);

    // Make sure the appbar is unregistered
    if (g_fAppRegistered)
    {
        SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_APPBAR_UNREGISTER, 0), 0L);
    }

    // Free the OPTIONS struct associated with the appbar
    HeapFree(GetProcessHeap(), 0, pOptions);

    // Clean up the GDI objects we allocated
    DeleteObject(g_hFontTop);
    DeleteObject(g_hFontLeft);

    // Indicate that the message loop should exit since the main window
    // is being destroyed.
    PostQuitMessage(0);
}


//
//  FUNCTION:   Main_OnTimer(HWND, UINT)
//
//  PURPOSE:    Handles timer messages to either delay the showing or hiding
//              of an appbar with the autohide state set.
//
//  PARAMETERS:
//      hwnd    - Handle of the window receiving the timer.
//      id      - ID of the timer message.
//

void Main_OnTimer(HWND hwnd, UINT id)
{
    POPTIONS pOpt = GetAppbarData(hwnd);
    POINT pt;
    RECT rc;
    HWND hwndActive;

    switch (id)
    {
        // The AUTOHIDE timer has fired.  Check to see if the mouse is over our
        // window and if not hide the appbar.
        case IDT_AUTOHIDE:
            if ((pOpt->fAutoHide) && (!pOpt->fHiding))
            {
                // Get the mouse position, the window position, and active 
                // window
                GetCursorPos(&pt);
                GetWindowRect(hwnd, &rc);
                hwndActive = GetForegroundWindow();

                // If the mouse is outside of our window, or we are not active,
                // or at least one window is active, or we are not the parent
                // of an active window, the hide the appbar window.
                if ((!PtInRect(&rc, pt)) && (hwndActive != hwnd) && 
                    (hwndActive != NULL) && (GetWindowOwner(hwndActive) != hwnd))
                {
                    KillTimer(hwnd, id);
                    AppBar_Hide(hwnd);
                }
            }
            break;

        // The period between the time the user has entered our window and the 
        // time we should show the window has expired.  
        case IDT_AUTOUNHIDE:
            // Kill the timer, we only need it to fire once.
            KillTimer(hwnd, id);

            GetWindowRect(hwnd, &rc);
            if ((pOpt->fAutoHide) && (pOpt->fHiding))
            {
                // Check to see if the cursor is still in the appbar.  If so,
                // the unhide the window.
                GetCursorPos(&pt);
                if (PtInRect(&rc, pt))
                    AppBar_UnHide(hwnd);
            }
            break;
    }
}


//
//  FUNCTION:   Main_OnNCHitTest(HWND, int, int)
//
//  PURPOSE:    Determines if we're over an edge that is resizable and also
//              starts the window unhiding process.
//
//  PARAMETERS:
//      hwnd    - Handle of the window receiving this message.
//      x, y    - Position of the mouse in screen coordinates.
//
//  RETURN VALUE:
//      Returns a constant denoting what part of the window the mouse is over.
//      If the mouse is over a resizing border that is not on the inside of the
//      screen, the function returns HTCLIENT to prevent the user from being
//      able to resize the window in this direction.
//

UINT Main_OnNCHitTest(HWND hwnd, int x, int y)
{
    POPTIONS pOpt = GetAppbarData(hwnd);
    LRESULT  lHitTest;

    // Take care of the autohide stuff if needed
    AppBar_SetAutoUnhideTimer(hwnd);

    // Let DefWindowProc() tell us where the mouse is
    lHitTest = FORWARD_WM_NCHITTEST(hwnd, x, y, DefWindowProc);

    // We want to disable sizing in all directions except the inside edge.
    if ((pOpt->uSide == ABE_TOP) && (lHitTest == HTBOTTOM))
        return HTBOTTOM;
    
    if ((pOpt->uSide == ABE_BOTTOM) && (lHitTest == HTTOP))
        return HTTOP;

    if ((pOpt->uSide == ABE_LEFT) && (lHitTest == HTRIGHT))
        return HTRIGHT;

    if ((pOpt->uSide == ABE_RIGHT) && (lHitTest == HTLEFT))
        return HTLEFT;


    return HTCLIENT;                            
}


//
//  FUNCTION:   Main_OnPaint 
//
//  PURPOSE:    Displays a message in the AppBar client area
//
//  PARAMETERS:
//      hwnd - Handle of the window receiving the message.
//

void Main_OnPaint(HWND hwnd)
{
    POPTIONS pOpt = GetAppbarData(hwnd);
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;
    HFONT hfont;
    int x,y;

    // Get the client rect
    GetClientRect(hwnd, &rc);
    InvalidateRect(hwnd, NULL, TRUE);
          
    hdc = BeginPaint(hwnd, &ps);   

    // Figure out which side we're on so we can adjust the text accordingly
    switch (pOpt->uSide)
    {
        case ABE_TOP:
        case ABE_BOTTOM:
            hfont = SelectObject(hdc, g_hFontTop);
            x = 2;
            y = 2;
            break;

        case ABE_LEFT:
        case ABE_RIGHT:
            hfont = SelectObject(hdc, g_hFontLeft);
            x = rc.right - 2;
            y = 2;
            break;
    }

    // Draw the text and clean up           
    ExtTextOut(hdc, x, y, ETO_OPAQUE, NULL, TEXT("Right Click for Options"),
               lstrlen(TEXT("Right Click for Options")), NULL);

    SelectObject(hdc, hfont);
    EndPaint(hwnd, &ps);
    
}


//
//  FUNCTION:   Main_OnLButtonDown 
//
//  PURPOSE:    This handler is called when the user is beginning to drag the
//              appbar around the screen.  
//
//  PARAMETERS:
//      hwnd         - Handle of the appbar window being dragged.
//      fDoubleClick - TRUE if this is a double click.
//      x, y         - Position of the mouse in client coordinates when then 
//                     button was pressed.
//      keyFlags     - Keyboard state flags.
//


void Main_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    POPTIONS pOpt = GetAppbarData(hwnd);

    g_fMoving = TRUE;
    SetCapture(hwnd);   
}

//
//  FUNCTION:   Main_OnMouseMove 
//
//  PURPOSE:    We need to keep track of the mouse position, and update the 
//              appbar position when the mouse is in the appropriate quadrent
//              of the screen.
//
//  PARAMETERS:
//      hwnd     - Handle of the AppBar window.
//      x, y     - Position of the mouse in screen coordinates
//      keyFlags - Keyboard state flags.  Not used.
//

void Main_OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
    POINT ptCursor = {x, y};
    LONG cxScreen, cyScreen;
    DWORD dx, dy;
    WORD horiz, vert;
    POPTIONS pOpt = GetAppbarData(hwnd);
    APPBARDATA abd;

    // If we're not currently in the middle of moving the appbar window,
    // there's nothing to do.
    if (!g_fMoving)
        return;

    // Convert the mouse position to screen coordinates
    ClientToScreen(hwnd, &ptCursor);

    // Find out which edge of the screen we're closest to
    cxScreen = GetSystemMetrics(SM_CXSCREEN);
    cyScreen = GetSystemMetrics(SM_CYSCREEN);

    if (ptCursor.x < (cxScreen / 2))
    {
        dx = ptCursor.x;
        horiz = ABE_LEFT;
    }
    else
    {
        dx = cxScreen - ptCursor.x;
        horiz = ABE_RIGHT;
    }

    if (ptCursor.y < (cyScreen / 2))
    {
        dy = ptCursor.y;
        vert = ABE_TOP;
    }
    else
    {
        dy = cyScreen - ptCursor.y;
        vert = ABE_BOTTOM;
    }

    // Build a drag rectangle based on the edge of the screen that we're 
    // closest to.
    if ((cxScreen * dy) > (cyScreen * dx))
    {
        g_rcDrag.top = 0;
        g_rcDrag.bottom = cyScreen;
        if (horiz == ABE_LEFT)
        {
            g_rcDrag.left = 0;
            g_rcDrag.right = g_rcDrag.left + pOpt->cxWidth;
            pOpt->uSide = ABE_LEFT;
        }
        else
        {
            g_rcDrag.right = cxScreen;
            g_rcDrag.left = g_rcDrag.right - pOpt->cxWidth;
            pOpt->uSide = ABE_RIGHT;
        }
    }
    else
    {
        g_rcDrag.left = 0;
        g_rcDrag.right = cxScreen;
        if (vert == ABE_TOP)
        {
            g_rcDrag.top = 0;
            g_rcDrag.bottom = g_rcDrag.top + pOpt->cyHeight;
            pOpt->uSide = ABE_TOP;
        }
        else
        {
            g_rcDrag.bottom = cyScreen;
            g_rcDrag.top = g_rcDrag.bottom - pOpt->cyHeight;
            pOpt->uSide = ABE_BOTTOM;
        }
    }           

    // Finally, make sure this is an OK position with the system and move
    // the window.
    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = hwnd;

    AppBar_QueryPos(hwnd, &g_rcDrag);
    MoveWindow(hwnd, g_rcDrag.left, g_rcDrag.top, 
               g_rcDrag.right - g_rcDrag.left, 
               g_rcDrag.bottom - g_rcDrag.top, 
               TRUE);
}


//
//  FUNCTION:   Main_OnLButtonUp 
//
//  PURPOSE:    The user is done dragging the window around, so we need to 
//              let the system know we have a new space to occupy.
//
//  PARAMETERS:
//      hwnd     - Handle of the AppBar window.
//      x, y     - Position of the mouse in client coordinates.
//      keyFlags - Keyboard state flags.  Not used.
//

void Main_OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    APPBARDATA abd;
    POPTIONS pOpt = GetAppbarData(hwnd);

    if (!g_fMoving)
        return;

    // Update the global appbar rect used when we're autohiding.  This is
    // sloppy but it works for now.  It would be better to maintain two rects,
    // one for the hidden state and one for the unhidden state.
    g_rcAppBar = g_rcDrag;

    // Clean up the drag state info.
    ReleaseCapture();               

    // Calculate the hidden rect if we need to and then tell the system about
    // our new area.
    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = hwnd;

    if (pOpt->fAutoHide)
    {
        switch (pOpt->uSide)
        {
            case ABE_TOP:
                g_rcDrag.bottom = g_rcDrag.top + 2; 
                break;
            case ABE_BOTTOM:
                g_rcDrag.top = g_rcDrag.bottom - 2;
                break;
            case ABE_LEFT:
                g_rcDrag.right = g_rcDrag.left + 2;
                break;
            case ABE_RIGHT:
                g_rcDrag.left = g_rcDrag.right - 2;
                break;
        }
    }

    AppBar_QuerySetPos(pOpt->uSide, &g_rcDrag, &abd, FALSE);

    g_fMoving = FALSE;
}                     


//
//  FUNCTION:   AboutDlgProc(HWND, UINT, WPARAM, LPARAM) 
//
//  PURPOSE:    Processes messages for the About dialog box
//
//  PARAMETERS: 
//      hwnd    - window handle of the dialog box
//      uMsg    - identifier of the message being handled
//      wParam  - additional info associated with the message
//      lParam  - additional info associated with the message
//               
//  RETURN VALUE:
//      Except in response to the WM_INITDIALOG message, the dialog box 
//      procedure should return nonzero if it processes the message, and zero 
//      if it does not. 
//

LRESULT CALLBACK AboutDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, 
                              LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_INITDIALOG:
            // Should return nonzero to set focus to the first control in the
            // dialog, or zero if this routine sets the focus manually.            
            return (TRUE);

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, 0);
                    break;
            }
            return (TRUE);
    }
    return (FALSE);
}
