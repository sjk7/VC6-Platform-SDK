/******************************************************************************
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
* PARTICULAR PURPOSE.
* 
*  Copyright (C) 1999 - 2000  Microsoft Corporation.  All Rights Reserved.
* 
*   FILE:   QueList.C
* 
*   PURPOSE:    Implements an abstraction around a ListView common control
*      used to display the contents of a printer queue.
* 
*   FUNCTIONS:  
        CreateQueList()   - Creates the child window control
        ResizeQueList()   - Forces the control to the size Parents Client Area.
        InitQueList()     - Initializes the control and sets the column
                            Headings.
        SetQueListContents()  - Does a minimal update of the ListViews 
                                contents.
        ResizeWindowToControlWidth()  - Adjusts the Application Window so
                                        the client area is the controls
                                        desired size.
* 
******************************************************************************/


#define STRICT
#include <windows.h>   // required for all Windows applications
#include "resource.h"  // Windows resource IDs
#include "Queue.h"     // Data Structure for Queue data
#include "QueList.h"   // Declarations for these exported functions


extern HINSTANCE    g_hInst;        // Instance of the application
static unsigned short *g_pnColumns; // # of columns pulled from resources

/**********************************************************
 * Module private declarations
 **********************************************************/

static void ResizeWindowToControlWidth (HWND hWnd, HWND hWndControl);
static BOOL InitQueList (HWND hwndListView);


/**********************************************************
 * Publicly Exported declarations
 *********************************************************/


/****************************************************************************

    FUNCTION:   CreateQueList(HWND hwndParent)


    PURPOSE:   Used to initially, periodically, or upon user request, 
               completely fill in the data for the printer queue. 

    COMMENTS:

            If Printer Change Notifications are not used this function is 
            called by the polling thread each time it wakes up to refresh the
            data for the Printer Queue.

****************************************************************************/

HWND CreateQueList(HWND hwndParent)
{
    DWORD       dwStyle;
    HWND        hwndListView;

    /*
     * List View Styles for this control
     */
    dwStyle =   WS_TABSTOP | 
                WS_CHILD | 
                WS_BORDER | 
                LVS_REPORT | 
                WS_VISIBLE;
            
    hwndListView = CreateWindowEx(   WS_EX_CLIENTEDGE,          // ex style
                                     WC_LISTVIEW,               // class name - defined in commctrl.h
                                     "",                        // dummy text
                                     dwStyle,                   // style
                                     0,                         // x position
                                     0,                         // y position
                                     0,                         // width
                                     0,                         // height
                                     hwndParent,                // parent
                                     (HMENU)IDC_LISTVIEW,       // ID
                                     g_hInst,                   // instance
                                     NULL);                     // no extra data

    /* Very bad, Bail */
    if(!hwndListView)
       return NULL;

    /* Setup the control via resources */
    InitQueList(hwndListView);
    
    /* make the parent wide enough for the child window */
    ResizeWindowToControlWidth(hwndParent, hwndListView);

    return hwndListView;

} /* end of function CreateQueList */

/****************************************************************************

    FUNCTION:   ResizeQueList(HWND hwndListView, HWND hwndParent)


    PURPOSE:   Changes the Window's dimensions and location to fit
               perfectly withing the parent's client area.

    COMMENTS:

            Trivial.

****************************************************************************/

void ResizeQueList(HWND hwndListView, HWND hwndParent)
{
    RECT  rc;

    GetClientRect(hwndParent, &rc);

    MoveWindow( hwndListView, 
                rc.left,
                rc.top,
                rc.right - rc.left,
                rc.bottom - rc.top,
                TRUE);
} /* end of function ResizeQueList */

/****************************************************************************

    FUNCTION:   InitQueList( HWND )


    PURPOSE:   InitQueList sets up an existing ListView Common Control to 
               contain specific columns as defined by resources in the
               application.

    COMMENTS:

            The # of columns for the control is defined by IDR_COLUMNCOUNT in 
            the applications resources. The strings for the column headings
            are stored IDS_COLUMN1 + n resource strings. The default widths of
            the columns are stored in an array of shorts located at IDR_COLUMNWIDTHS.

****************************************************************************/

BOOL InitQueList(HWND hwndListView)
{
    LV_COLUMN       lvColumn;
    int             i, 
                    nColumns,
                    nListWidth;
    unsigned short  *pnColumnWidths;
    HRSRC           hColumnWidthsRsrc;
    HGLOBAL         hColumnWidths;
    HRSRC           hColumnCountRsrc;
    HGLOBAL         hColumnCount;
    char            szheading[ColumnHeadingSize+1];
    RECT            rcWindow;

    // empty the list just to make sure.
    ListView_DeleteAllItems(hwndListView);
    while ( ListView_DeleteColumn (hwndListView, 0) );

    /* pull out the # of columns from the resource */
    hColumnCountRsrc = FindResource(g_hInst, MAKEINTRESOURCE(IDR_COLUMNCOUNT), RT_RCDATA);
    hColumnCount = LoadResource(g_hInst, hColumnCountRsrc);
    g_pnColumns = (unsigned short *)LockResource(hColumnCount);
    nColumns = *g_pnColumns;        // promote to an int

    /* grab a pointer to an array of widths */
    hColumnWidthsRsrc = FindResource(g_hInst, MAKEINTRESOURCE(IDR_COLUMNWIDTHS), RT_RCDATA);
    hColumnWidths = LoadResource(g_hInst, hColumnWidthsRsrc);
    pnColumnWidths = (unsigned short *)LockResource(hColumnWidths);

    //initialize the columns
    nListWidth = 0;
    lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvColumn.fmt = LVCFMT_LEFT;
    for(i = 0; i < nColumns; i++)
    {
        /* adjust the size of each column */
        lvColumn.cx = pnColumnWidths[i];

        /* accumulate width of columns and their seperations */
        nListWidth += pnColumnWidths[i] +1;

        LoadString(g_hInst, IDS_COLUMN1+i, szheading, ColumnHeadingSize+1);
        lvColumn.pszText = szheading;
        ListView_InsertColumn(hwndListView, i, &lvColumn);
    }

    /* Resize the window */
    GetWindowRect(hwndListView, &rcWindow);
    MoveWindow(hwndListView, 
               rcWindow.left, 
               rcWindow.top, 
               nListWidth, 
               (rcWindow.bottom-rcWindow.top), 
               FALSE);
    
    
    return TRUE;

} /* end of function InitQueList */


/****************************************************************************

    FUNCTION:   SetQueListContents( HWND, QUEUEDATA * )


    PURPOSE:   SetQueListContents does a minimal update of cells of the
               ListView common control.

    COMMENTS:

            The QUEUEDATA data structure contains information indicating what
            parts of the data it contains has changed. This information is used
            to make sure that we change only those ListView items that need to 
            be updated. 

****************************************************************************/

void SetQueListContents(HWND hwndListView, QUEUEDATA *pQueue)
{
    LV_ITEM         lvItem;
    unsigned int    i,          // Rows
                    j,          // Columns
                    nItems;     // Initial # of lines in the list view

    SendMessage(hwndListView, WM_SETREDRAW, FALSE, 0);
    
    /* 
     * find out how many items already in the list view 
     * that we can reuse.
     */
    nItems = ListView_GetItemCount(hwndListView);

    for(i = 0; i < pQueue->nJobs; i++)
    {
        /* refresh listbox contents */
    
        /* setup for the Row */
        lvItem.mask = LVIF_TEXT;
        lvItem.iImage = 0;
        lvItem.iItem = i;
        
        for (j=0; j< *g_pnColumns; j++)
        {
            if (IsChanged(&pQueue->pJobs[i], (WORD)j))
            {
                /* fill in the LV_ITEM structure for the item */
                lvItem.pszText = GetColumnData(&pQueue->pJobs[i], (unsigned short)j);
                lvItem.iSubItem = j;            
                
                /* while we can reuse items, use SetItem for subitems */
                if (!j && i >= nItems)
                    ListView_InsertItem(hwndListView, &lvItem);
                else
                    ListView_SetItem(hwndListView, &lvItem);
                
                // we own the string passed back from GetColumnData
                free (lvItem.pszText);
            }

        }
        
        // Mark everything as current
        ClearChanges(&pQueue->pJobs[i]);

    }

    /* If the list shrunk, delete any remaining items. */
    for (; i < nItems; i++)
    {
        ListView_DeleteItem(hwndListView, i);
    }

    /* Update the window */
    SendMessage(hwndListView, WM_SETREDRAW, TRUE, 0);
    InvalidateRect(hwndListView, NULL, FALSE);

} /* end of function SetQueListContents */


/****************************************************************************

    FUNCTION:   ResizeWindowToControlWidth( HWND hWnd, HWND hWndControl )


    PURPOSE:   Resizes the parent Window so that the client area is the right
               size to contain the ListView common control as configured.

    COMMENTS:


****************************************************************************/

void ResizeWindowToControlWidth(HWND hWnd, HWND hWndControl)
{
    RECT    rcWindow, rcClient;

    /* Set required client area to accomodate our columns */
    GetClientRect(hWnd, &rcClient);
    GetWindowRect(hWndControl, &rcWindow);
    rcClient.right = rcClient.left + (rcWindow.right - rcWindow.left);

    /* Calculate the window size to accomodate the Client size */
    AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, TRUE);
    GetWindowRect(hWnd, &rcWindow);

    /* New Width and old Height */
    rcWindow.bottom = (rcClient.bottom-rcClient.top);
    rcWindow.right = (rcClient.right-rcClient.left);

    /* Adjust the window size */
    MoveWindow(hWnd, 
               rcWindow.left, 
               rcWindow.top, 
               rcWindow.right, 
               rcWindow.bottom, 
               FALSE);

} /* end of function ResizeWindowToControlWidth */

/* end of source file QueList.C */