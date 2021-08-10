/******************************************************************************
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
* PARTICULAR PURPOSE.
* 
*  Copyright (C) 1999 - 2000  Microsoft Corporation.  All Rights Reserved.
* 
*   FILE:   QueList.H
* 
*   PURPOSE:    Declares the QueList control's public functions
* 
*   FUNCTIONS:  
*       ResizeQueList () - Resizes the control to the client area of the Parent.
*       CreateQueList () - Creates the control as a child of the Parent.
*       SetQueListContents () - Syncs controls contents with the Queue data structure.
* 
******************************************************************************/

#include <commctrl.h>


#define ColumnHeadingSize   20      /* Max column name string size */

void    ResizeQueList       (HWND hwndListView, HWND hwndParent);
HWND    CreateQueList       (HWND hwndParent);
void    SetQueListContents  (HWND hwndListView, QUEUEDATA *pQueue);

/* end of header file QueList.H */