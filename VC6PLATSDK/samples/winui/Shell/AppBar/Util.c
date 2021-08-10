// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993 - 2000  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     util.c
//
//  PURPOSE:    Contains utility functions used by the AppBar.
//
//  PLATFORMS:  Windows 95, Windows 98, Windows 2000, Windows NT 4.0
//
//  FUNCTIONS:
//      SlideWindow()   - Sides the appbar on and off the screen
//
//  COMMENTS:
//
//

#include <windows.h>
#include <windowsx.h>
#include "globals.h"
#include "appbar.h"

const int g_dtSlideHide = 400;
const int g_dtSlideShow = 200;

//
//  FUNCTION:   SlideWindow(HWND, LPRECT) 
//
//  PURPOSE:    Slides the AppBar off the edge of the screen when the AppBar
//              has the AutoHide state set.
//
//  PARAMETERS:
//      hwnd    - handle of the window to scroll off the screen
//      prc     - rectangle you wish the appbar to occupy
//
//  COMMENTS:
//

void SlideWindow(HWND hwnd, LPRECT prc)
{
    RECT rcOld;
    RECT rcNew;
    int x, y, dx, dy, dt, t, t0;
    BOOL fShow;
    HANDLE hThreadMe;
    int priority;

    rcNew = *prc;

    if ((g_dtSlideShow > 0) && (g_dtSlideHide > 0)) 
    {
        GetWindowRect(hwnd, &rcOld);

        fShow = (rcNew.bottom - rcNew.top) > (rcOld.bottom - rcOld.top) ||
                (rcNew.right - rcNew.left) > (rcOld.right - rcOld.left);

        dx = (rcNew.right - rcOld.right) + (rcNew.left - rcOld.left);
        dy = (rcNew.bottom - rcOld.bottom) + (rcNew.top - rcOld.top);

        if (fShow)
        {
            rcOld = rcNew;
            OffsetRect(&rcOld, -dx, -dy);
            SetWindowPos(hwnd, NULL, rcOld.left, rcOld.top,
                    rcOld.right - rcOld.left, rcOld.bottom - rcOld.top,
                    SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME);

            dt = g_dtSlideShow;
        }
        else
        {
            dt = g_dtSlideHide;
        }

        hThreadMe = GetCurrentThread();
        priority = GetThreadPriority(hThreadMe);
        SetThreadPriority(hThreadMe, THREAD_PRIORITY_HIGHEST);

        t0 = GetTickCount();
        while ((t = GetTickCount()) < t0 + dt)
        {
            x = rcOld.left + dx * (t - t0) / dt;
            y = rcOld.top + dy * (t - t0) / dt;

            SetWindowPos(hwnd, NULL, x, y, 0, 0,
                         SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
            if (fShow)
                UpdateWindow(hwnd);
            else
                UpdateWindow(GetDesktopWindow());
        }

        SetThreadPriority(hThreadMe, priority);
    }

    SetWindowPos(hwnd, NULL, rcNew.left, rcNew.top,
                 rcNew.right - rcNew.left, rcNew.bottom - rcNew.top,
                 SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME);

}


