// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993 - 2000  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     appbar.c
//
//  PURPOSE:    Contains routines to manage an appbar.
//
//  PLATFORMS:  Windows 95, Windows 98, Windows 2000, Windows NT 4.0
//
//  FUNCTIONS:
//      AppBar_Size()               - Updates appbar's size and position
//      AppBar_QueryPos()           - Asks the system if a rect is ok
//      AppBar_QuerySetPos()        - Moves the appbar if possible
//      AppBar_PosChanged()         - Calculates new appbar size and moves
//      AppBar_Callback()           - Callback for appbar notifcations
//      AppBar_Register()           - Registers appbar with the system
//      AppBar_UnRegister()         - Unregisters appbar with the system
//      AppBar_SetAutoHide()        - Sets the autohide state to on or off
//      AppBar_AutoHide()           - Sets autohide 
//      AppBar_NoAutoHide()         - Removes autohide
//      AppBar_SetSide()            - Sets the side the appbar is attached to
//      AppBar_SetAlwaysOnTop()     - Sets the always on top state
//      AppBar_Hide()               - Hides the appbar
//      AppBar_UnHide()             - Shows a hidden appbar
//      AppBar_SetAutoHideTimer()   - Sets a delay for the hiding
//      AppBar_SetAutoUnhideTimer() - Sets a delay for the showing
//      GetAppbarData()             - Retrieves the OPTIONS struct from the 
//                                    appbar window bytes
//


#include <windows.h>
#include <windowsx.h>
#include "globals.h"
#include "resource.h"
#include "appbar.h"



/////////////////////////////////////////////////////////////////////////////
// Local Prototypes

BOOL AppBar_AutoHide(HWND hwnd);
BOOL AppBar_NoAutoHide(HWND hwnd);

/////////////////////////////////////////////////////////////////////////////
// Global Variables
     
BOOL g_fAppRegistered = FALSE;      // TRUE if the appbar is registered
RECT g_rcAppBar;                    // Current rect of the appbar

DWORD g_cxWidth, g_cyHeight;

//
//  FUNCTION:   AppBar_Size(HWND) 
//
//  PURPOSE:    Handles updating the appbar's size and position.
//
//  PARAMETERS:
//      hwnd    - handle of the appbar
//
//  COMMENTS:
//

void AppBar_Size(HWND hwnd)
{
    RECT rc;
    APPBARDATA abd;
    POPTIONS pOpt;

    if (g_fAppRegistered)
    {
        DebugMsg("AppBarSize Called\r\n");

        pOpt = GetAppbarData(hwnd);

        abd.cbSize = sizeof(APPBARDATA);
        abd.hWnd = hwnd;

        GetWindowRect(hwnd, &rc);
        AppBar_QuerySetPos(pOpt->uSide, &rc, &abd, TRUE);
    }
}


//
//  FUNCTION:   AppBar_QueryPos 
//
//  PURPOSE:    Asks the system if the AppBar can occupy the rectangle specified
//              in lprc.  The system will change the lprc rectangle to make
//              it a valid rectangle on the desktop.
//
//  PARAMETERS:
//      hwnd - Handle to the AppBar window.
//      lprc - Rectange that the AppBar is requesting to occupy.
//

void AppBar_QueryPos(HWND hwnd, LPRECT lprc)
{
    POPTIONS pOpt = GetAppbarData(hwnd);
    APPBARDATA abd;
    int iWidth = 0;
    int iHeight = 0;

    // Fill out the APPBARDATA struct and save the edge we're moving to
    // in the appbar OPTIONS struct.
    abd.hWnd = hwnd;
    abd.cbSize = sizeof(APPBARDATA);
    abd.rc = *lprc;
    abd.uEdge = pOpt->uSide;

    // Calculate the part we want to occupy.  We only figure out the top
    // and bottom coordinates if we're on the top or bottom of the screen.
    // Likewise for the left and right.  We will always try to occupy the
    // full height or width of the screen edge.
    if ((ABE_LEFT == abd.uEdge) || (ABE_RIGHT == abd.uEdge))
    {
        iWidth = abd.rc.right - abd.rc.left;
        abd.rc.top = 0;
        abd.rc.bottom = GetSystemMetrics(SM_CYSCREEN);
    }
    else
    {
        iHeight = abd.rc.bottom - abd.rc.top;
        abd.rc.left = 0;
        abd.rc.right = GetSystemMetrics(SM_CXSCREEN);
    }

    // Ask the system for the screen space
    SHAppBarMessage(ABM_QUERYPOS, &abd);

    // The system will return an approved position along the edge we're asking
    // for.  However, if we can't get the exact position requested, the system
    // only updates the edge that's incorrect.  For example, if we want to 
    // attach to the bottom of the screen and the taskbar is already there, 
    // we'll pass in a rect like 0, 964, 1280, 1024 and the system will return
    // 0, 964, 1280, 996.  Since the appbar has to be above the taskbar, the 
    // bottom of the rect was adjusted to 996.  We need to adjust the opposite
    // edge of the rectangle to preserve the height we want.

    switch (abd.uEdge)
    {
        case ABE_LEFT:
            abd.rc.right = abd.rc.left + iWidth;
            break;

        case ABE_RIGHT:
            abd.rc.left = abd.rc.right - iWidth;
            break;

        case ABE_TOP:
            abd.rc.bottom = abd.rc.top + iHeight;
            break;

        case ABE_BOTTOM:
            abd.rc.top = abd.rc.bottom - iHeight;
            break;
    }


    *lprc = abd.rc; 
}


//
//  FUNCTION:   AppBar_QuerySetPos(UINT, LPRECT, PAPPBARDATA, BOOL) 
//
//  PURPOSE:    Asks the system if the appbar can move itself to a particular
//              side of the screen and then does move the appbar.
//
//  PARAMETERS:
//      uEdge   - Side of the screen to move to.  Can be ABE_TOP, ABE_BOTTOM,
//                ABE_LEFT, or ABE_RIGHT.
//      lprc    - Screen rect the appbar wishes to occupy.  This will be 
//                modified and will return the area the system will let the
//                appbar occupy.
//      pabd    - Pointer to the APPBARDATA struct used in all appbar system
//                calls.
//      fMove   - TRUE if the function should move the appbar, FALSE if the
//                caller will move the AppBar.
//

void AppBar_QuerySetPos(UINT uEdge, LPRECT lprc, PAPPBARDATA pabd, BOOL fMove)
{
    int iHeight = 0;
    int iWidth = 0;
    POPTIONS pOpt = GetAppbarData(pabd->hWnd);

    DebugMsg("AppBarQuerySetPos: uEdge=%d, lprc->left=%d, lprc->top=%d, "
             "lprc->right=%d, lprc->bottom=%d\r\n", uEdge, lprc->left,
             lprc->top, lprc->right, lprc->bottom);

    // Fill out the APPBARDATA struct and save the edge we're moving to
    // in the appbar OPTIONS struct.
    pabd->rc = *lprc;
    pabd->uEdge = uEdge;
    pOpt->uSide = uEdge;

    AppBar_QueryPos(pabd->hWnd, &(pabd->rc));


    // Tell the system we're moving to this new approved position.
    SHAppBarMessage(ABM_SETPOS, pabd);

    if (fMove)
    {
        // Move the appbar window to the new position
        MoveWindow(pabd->hWnd, pabd->rc.left, pabd->rc.top, 
                   pabd->rc.right - pabd->rc.left,
                   pabd->rc.bottom - pabd->rc.top, TRUE);
    }

    // Save the appbar rect.  We use this later when we autohide.  If we're
    // currently hidden, then don't mess with this.
    if (!pOpt->fAutoHide)
        g_rcAppBar = pabd->rc;
}


//
//  FUNCTION:   AppBar_PosChanged(PAPPBARDATA)
//
//  PURPOSE:    The system has changed our position for some reason.  We need
//              to recalculate the position on the screen we want to occupy
//              by determining how wide or thick we are and the update the
//              screen position.
//              
//
//  PARAMETERS:
//      pabd    - Pointer to the APPBARDATA structure used in all AppBar calls
//                to the system.
//

void AppBar_PosChanged(PAPPBARDATA pabd)
{
    RECT rc;
    RECT rcWindow;
    int iHeight;
    int iWidth;
    POPTIONS pOpt = GetAppbarData(pabd->hWnd);

    DebugMsg("AppBarPosChanged\r\n");
    
    // Start by getting the size of the screen.
    rc.top = 0;
    rc.left = 0;
    rc.right = GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = GetSystemMetrics(SM_CYSCREEN);

    // Update the g_rcAppbar so when we slide (if hidden) we slide to the 
    // right place.
    if (pOpt->fAutoHide)
    {
        g_rcAppBar = rc;
        switch (pOpt->uSide)
        {
            case ABE_TOP:
                g_rcAppBar.bottom = g_rcAppBar.top + g_cyHeight;
                break;

            case ABE_BOTTOM:
                g_rcAppBar.top = g_rcAppBar.bottom - g_cyHeight;
                break;

            case ABE_LEFT:
                g_rcAppBar.right = g_rcAppBar.left + g_cxWidth;
                break;

            case ABE_RIGHT:
                g_rcAppBar.left = g_rcAppBar.right - g_cxWidth;
                break;
        }           
    }        

    // Now get the current window rectangle and find the height and width
    GetWindowRect(pabd->hWnd, &rcWindow);
    iHeight = rcWindow.bottom - rcWindow.top;
    iWidth = rcWindow.right - rcWindow.left;

    // Depending on which side we're on, try to preserve the thickness of
    // the window    
    switch (pOpt->uSide) 
    {
        case ABE_TOP:
            rc.bottom = rc.top + iHeight;
            break;

        case ABE_BOTTOM:
            rc.top = rc.bottom - iHeight;
            break;

        case ABE_LEFT:
            rc.right = rc.left + iWidth;
            break;

        case ABE_RIGHT:
            rc.left = rc.right - iWidth;
            break;
    }        

    // Move the appbar.
    AppBar_QuerySetPos(pOpt->uSide, &rc, pabd, TRUE);

}


//
//  FUNCTION:   AppBar_Callback(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:    Handles notification messages sent from the system to our
//              appbar.
//
//  PARAMETERS:
//      hwnd    - Handle of the appbar window receiving the notification.
//      uMsg    - The appbar notification message that we registered.
//      wParam  - Contains the specific notification code.
//      lParam  - Extra information dependant on the notification code.
//

void AppBar_Callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    APPBARDATA abd;
    static HWND hwndZOrder = NULL;
    POPTIONS pOpt = GetAppbarData(hwnd);
    
    abd.cbSize = sizeof(abd);
    abd.hWnd = hwnd;
    
    switch (wParam) 
    {
        // Notifies the appbar that the taskbar's autohide or always-on-top 
        // state has changed.  The appbar can use this to conform to the settings
        // of the system taskbar.
        case ABN_STATECHANGE:
            DebugMsg("AppBarCallback: ABN_STATECHANGE\r\n");
            break;

        // Notifies the appbar when a full screen application is opening or 
        // closing.  When a full screen app is opening, the appbar must drop
        // to the bottom of the Z-Order.  When the app is closing, we should 
        // restore our Z-order position.
        case ABN_FULLSCREENAPP:
            DebugMsg("AppBarCallback: ABN_FULLSCREENAPP\r\n");
            if (lParam) 
            {
                // A full screen app is opening.  Move us to the bottom of the 
                // Z-Order.  

                // First get the window that we're underneath so we can correctly
                // restore our position
                hwndZOrder = GetWindow(hwnd, GW_HWNDPREV);
                
                // Now move ourselves to the bottom of the Z-Order
                SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, 
                             SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);            
            } 
            else 
            {
                // The app is closing.  Restore the Z-order            
                SetWindowPos(hwnd, pOpt->fOnTop ? HWND_TOPMOST : hwndZOrder,
                             0, 0, 0, 0, 
                             SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                
                hwndZOrder = NULL;
            }
            break;
        
        // Notifies the appbar when an event has occured that may effect the 
        // appbar's size and position.  These events include changes in the 
        // taskbar's size, position, and visiblity as well as adding, removing,
        // or resizing another appbar on the same side of the screen.
        case ABN_POSCHANGED:
            DebugMsg("AppBarCallback: ABN_POSCHANGED\r\n");

            // Update our position in response to the system change
            AppBar_PosChanged(&abd);
            break;
    }
}


//
//  FUNCTION:   AppBar_Register(HWND)
//
//  PURPOSE:    Registers the appbar with the system.
//
//  PARAMETERS:
//      hwnd    - handle of the appbar to register.
//
//  RETURN VALUE:
//      Returns TRUE if successful, FALSE otherwise.
//
//  COMMENTS:
//      Sets the system wide g_fAppRegistered variable.
//

BOOL AppBar_Register(HWND hwnd)
{
    APPBARDATA abd;
    
    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = hwnd;
    abd.uCallbackMessage = APPBAR_CALLBACK;

    g_fAppRegistered = (BOOL)SHAppBarMessage(ABM_NEW, &abd);
    return g_fAppRegistered;
}


//
//  FUNCTION:   AppBar_UnRegister(HWND)
//
//  PARAMETERS:
//      hwnd    - handle of the appbar to register.
//
//  RETURN VALUE:
//      Returns TRUE if successful, FALSE otherwise.
//
//  COMMENTS:
//      Sets the system wide g_fAppRegistered variable.
//

BOOL AppBar_UnRegister(HWND hwnd)
{
    APPBARDATA abd;
    
    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = hwnd;

    g_fAppRegistered = !SHAppBarMessage(ABM_REMOVE, &abd);
        
    return !g_fAppRegistered;
}       


//
//  FUNCTION:   AppBar_SetAutoHide(HWND, BOOL)
//
//  PURPOSE:    Causes the appbar window to either auto hide or stop auto
//              hiding.
//
//  PARAMETERS:
//      hwnd    - Handle of the appbar window to change the auto hide state.
//      fHide   - TRUE if we want the window to autohide, FALSE to stop.
//
//  RETURN VALUE:
//      Returns TRUE if successful, FALSE otherwise.
//

BOOL AppBar_SetAutoHide(HWND hwnd, BOOL fHide)
{
    if (fHide)
        return AppBar_AutoHide(hwnd);
    else
        return AppBar_NoAutoHide(hwnd);
}


//
//  FUNCTION:   AppBar_AutoHide(HWND)
//
//  PURPOSE:    Does the work of changing the appbar to autohide.  We check
//              to see if we can autohide, and if so unregister and tell
//              the system we are autohiding.
//
//  PARAMETERS:
//      hwnd    - Window handle of the appbar.
//
//  RETURN VALUE:
//      TRUE if successful, FALSE otherwise.
//

BOOL AppBar_AutoHide(HWND hwnd)
{
    HWND hwndAutoHide;
    APPBARDATA abd;
    POPTIONS pOpt = GetAppbarData(hwnd);
    BOOL fSuccess;  
    RECT rc;

    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = hwnd;
    abd.uEdge = pOpt->uSide;
    
    // First figure out if someone already has this side for 
    // autohiding
    hwndAutoHide = (HWND) SHAppBarMessage(ABM_GETAUTOHIDEBAR, &abd);
    if (hwndAutoHide != NULL)
    {
        DebugMsg(TEXT("ERROR: Another appbar is already hiding ")
                 TEXT("on this edge.  Cannot set to autohide.\r\n"));
        return (FALSE);
    }

    // We can autohide on this edge.  Set the autohide style.
    abd.lParam = TRUE;          

    fSuccess = (BOOL) SHAppBarMessage(ABM_SETAUTOHIDEBAR, &abd);
    if (!fSuccess)
    {
        DebugMsg(TEXT("ERROR: Error trying to set autohidebar.\r\n"));
        ErrorHandler();
        return (FALSE);
    }
    else
    {
        // Since we're allowed to autohide, we need to adjust our screen 
        // rectangle to the autohidden position.  This will allow the system
        // to resize the desktop.
        pOpt->fAutoHide = TRUE;
        g_cxWidth = pOpt->cxWidth;
        g_cyHeight = pOpt->cyHeight;

        rc = g_rcAppBar;
        switch (pOpt->uSide)
        {
            case ABE_TOP:
                rc.bottom = rc.top + 2; 
                break;
            case ABE_BOTTOM:
                rc.top = rc.bottom - 2;
                break;
            case ABE_LEFT:
                rc.right = rc.left + 2;
                break;
            case ABE_RIGHT:
                rc.left = rc.right - 2;
                break;
        }

        AppBar_QuerySetPos(pOpt->uSide, &rc, &abd, TRUE);
    }

    return (TRUE);
}


//
//  FUNCTION:   AppBar_NoAutoHide(HWND)
//
//  PURPOSE:    Does the work of changing the appbar to no-autohide.  We 
//              check to make sure we are actually auto hiding, and if so
//              re-register the appbar to get our desktop scren space back.
//
//  PARAMETERS:
//      hwnd    - Window handle of the appbar.
//
//  RETURN VALUE:
//      TRUE if successful, FALSE otherwise.
//

BOOL AppBar_NoAutoHide(HWND hwnd)
{
    HWND hwndAutoHide;
    APPBARDATA abd;
    POPTIONS pOpt = GetAppbarData(hwnd);
    BOOL fSuccess;  

    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = hwnd;
    abd.uEdge = pOpt->uSide;
    
    // First let's check to see if we're the appbar attached to the
    // side of the screen
    abd.uEdge = pOpt->uSide;
    hwndAutoHide = (HWND) SHAppBarMessage(ABM_GETAUTOHIDEBAR, &abd);
    if (hwndAutoHide != hwnd)
    {
        DebugMsg(TEXT("ERROR: We're not hidden currently\r\n"));
        return (FALSE);
    }

    // We can autohide or stop autohide on this edge.  Set the autohide style.
    abd.lParam = FALSE;         

    fSuccess = (BOOL) SHAppBarMessage(ABM_SETAUTOHIDEBAR, &abd);
    if (!fSuccess)
    {
        DebugMsg(TEXT("ERROR: Error trying to set autohidebar.\r\n"));
        ErrorHandler();
        return (FALSE);
    }
    else
    {
        // Need to change the appbar to get the screen desktop space
        // back.  Also need to reattach the appbar to that edge of the
        // screen.
        pOpt->fAutoHide = FALSE;        
        
        pOpt->cxWidth = g_cxWidth;
        pOpt->cyHeight = g_cyHeight;

        AppBar_SetSide(hwnd, pOpt->uSide);   
    }

    return (TRUE);
}


//
//  FUNCTION:   AppBar_SetSide(HWND, UINT)
//
//  PURPOSE:    Sets the side the AppBar is currently attached to.
//
//  PARAMETERS:
//      hwnd    - Window handle of the appbar.
//      uSide   - Side of the screen to attach to.  Can be ABE_TOP, ABE_BOTTOM,
//                ABE_LEFT, or ABE_RIGHT.
//
//  RETURN VALUE:
//      TRUE if successful, FALSE otherwise.
//

BOOL AppBar_SetSide(HWND hwnd, UINT uSide)
{
    APPBARDATA abd;
    RECT       rc;
    POPTIONS   pOpt = GetAppbarData(hwnd);
    BOOL       fAutoHide = FALSE;

    // Calculate the size of the screen so we can occupy the full width or
    // height of the screen on the edge we request.
    rc.top = 0;
    rc.left = 0;
    rc.right = GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = GetSystemMetrics(SM_CYSCREEN);

    // Fill out the APPBARDATA struct with the basic information
    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = hwnd;

    // If the appbar is autohidden, turn that off so we can move the bar
    if (pOpt->fAutoHide)
    {
        fAutoHide = pOpt->fAutoHide;

        // Turn off the redrawing of the desktop while we move things around.
        // If you put any breakpoints in this area you will lock up the desktop
        // Since turning off the desktop repaints turns it off for all the apps
        // in the system
        SetWindowRedraw(GetDesktopWindow(), FALSE);
        AppBar_SetAutoHide(hwnd, FALSE);
    }

    // Adjust the rectangle to set our height or width depending on the
    // side we want.
    switch (uSide)
    {
        case ABE_TOP:
            rc.bottom = rc.top + pOpt->cyHeight;
            break;
        case ABE_BOTTOM:
            rc.top = rc.bottom - pOpt->cyHeight;
            break;
        case ABE_LEFT:
            rc.right = rc.left + pOpt->cxWidth;
            break;
        case ABE_RIGHT:
            rc.left = rc.right - pOpt->cxWidth;
            break;
    }

    // Move the appbar to the new screen space.
    AppBar_QuerySetPos(uSide, &rc, &abd, TRUE);
    
    // If the appbar was hidden, rehide it now
    if (fAutoHide)
    {
        AppBar_SetAutoHide(hwnd, TRUE);

        SetWindowRedraw(GetDesktopWindow(), TRUE);
        RedrawWindow(GetDesktopWindow(), NULL, NULL, 
                     RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);         
    }

    return (TRUE);
}   
                                

//
//  FUNCTION:   AppBar_SetAlwaysOnTop(HWND, BOOL) 
//
//  PURPOSE:    Set's the Always-On-Top state for the appbar.
//
//  PARAMETERS:
//      hwnd    - Window handle of the AppBar to set the state for.
//      fOnTop  - TRUE to set the AppBar to Always-On-Top, FALSE otherwise
//

void AppBar_SetAlwaysOnTop(HWND hwnd, BOOL fOnTop)
{
    POPTIONS pOpt = GetAppbarData(hwnd);

    // Update the window position to HWND_TOPMOST if we're to be always
    // on top, or HWND_NOTOPMOST if we're not.
    SetWindowPos(hwnd, (fOnTop) ? HWND_TOPMOST : HWND_NOTOPMOST,
                 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

    // Store the setting in the appbar OPTIONS struct.
    pOpt->fOnTop = fOnTop;
}


//
//  FUNCTION:   AppBar_Hide(HWND)
//
//  PURPOSE:    Causes the appbar to hide itself.
//
//  PARAMETERS:
//      hwnd    - Handle of the AppBar to hide.
//

void AppBar_Hide(HWND hwnd)
{
    POPTIONS pOpt = GetAppbarData(hwnd);
    RECT rc;

    // Don't want to hide if AutoHide not set
    if (!pOpt->fAutoHide)
    {
        return;
    }

    // Calculate a hidden rectangle to use
    rc = g_rcAppBar;
    switch (pOpt->uSide)
    {
        case ABE_TOP:
            rc.bottom = rc.top + 2; 
            break;
        case ABE_BOTTOM:
            rc.top = rc.bottom - 2;
            break;
        case ABE_LEFT:
            rc.right = rc.left + 2;
            break;
        case ABE_RIGHT:
            rc.left = rc.right - 2;
            break;
    }

    pOpt->fHiding = TRUE;   
    SlideWindow(hwnd, &rc);
}


//
//  FUNCTION:   AppBar_UnHide(HWND) 
//
//  PURPOSE:    Causes a hidden appbar to unhide itself.
//
//  PARAMETERS:
//      hwnd    - Handle of the appbar to unhide.
//

void AppBar_UnHide(HWND hwnd)
{
    POPTIONS pOpt = GetAppbarData(hwnd);

    SlideWindow(hwnd, &g_rcAppBar);
    pOpt->fHiding = FALSE;

    AppBar_SetAutoHideTimer(hwnd);
}


//
//  FUNCTION:   AppBar_SetAutoHideTimer(HWND) 
//
//  PURPOSE:    Starts the auto hide timer.
//
//  PARAMETERS:
//      hwnd    - Handle of the appbar to set the timer for.
//
//  COMMENTS:
//      This is called to cause a delay between when the user's mouse leaves
//      the appbar area and the appbar is slid off the screen.
//

void AppBar_SetAutoHideTimer(HWND hwnd)
{
    POPTIONS pOpt = GetAppbarData(hwnd);

    if (pOpt->fAutoHide)
        SetTimer(hwnd, IDT_AUTOHIDE, 500, NULL);
}


//
//  FUNCTION:   AppBar_SetAutoUnhideTimer(HWND)
//
//  PURPOSE:    Starts the auto-UNhide timer.
//
//  PARAMETERS: 
//      hwnd    - Handle of the appbar to set the timer for.    
//
//  COMMENTS:
//      This is called to cause a delay between the time where the mouse enters
//      the appbar window and the time where the appbar displays itself.
//

void AppBar_SetAutoUnhideTimer(HWND hwnd)
{
    POPTIONS pOpt = GetAppbarData(hwnd);

    if (pOpt->fAutoHide && pOpt->fHiding)
        SetTimer(hwnd, IDT_AUTOUNHIDE, 50, NULL);
}


//
//  FUNCTION:   GetAppbarData(HWND)
//
//  PURPOSE:    Retrieves a pointer to the OPTIONS structure stored in the
//              window's extra bytes.
//
//  PARAMETERS:
//      hwnd    - Handle of the window to retrieve the pointer from.
//
//  RETURN VALUE:
//      Returns a pointer to an OPTIONS struct
//

POPTIONS GetAppbarData(HWND hwnd)        
{
    return (POPTIONS) GetWindowLongPtr(hwnd, 0);
}
