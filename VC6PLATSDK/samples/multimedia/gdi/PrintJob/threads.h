/******************************************************************************
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
*  PARTICULAR PURPOSE.
* 
*  Copyright (C) 1999 - 2000  Microsoft Corporation.  All Rights Reserved.
* 
    FILE:   Threads.H

    PURPOSE:    Provides functions for managing the threads which perform
        the monitoring of the print queues.

    FUNCTIONS:  
        CreatThreadSyncResources () - Creates mutex's for thread management.
        DestroyThreadSyncResources () - Cleans up thread management resources.
        StartPolling () - Creates a new polling thread.
        PollingUpdate () - Polling thread entry point.
        StartNotifications () - Creates a new Printer Change notification thread.
        NotificationUpdate () - Printer Change thread entry point.
        StopUpdateThread () - Terminates either thread type.
        ActiveUpdateThread () - Checks to see if either thread type exists.
        TriggerUpdateThreadRefresh () - Forces either thread type to do a refresh.
* 
******************************************************************************/


/* thread management */
BOOL    CreateThreadSyncResources(void);
BOOL    DestroyThreadSyncResources(void);

/* Polling thread functions */
HANDLE  StartPolling(HWND hWnd, HANDLE hPrinter, HANDLE hPrevThread);
unsigned __stdcall PollingUpdate(void *pParameters);

/* Printer Change notification thread functions */
HANDLE  StartNotifications(HWND hWnd, HANDLE hPrinter, HANDLE hPrevThread);
unsigned __stdcall NotificationUpdate(void *pParameters);

/* Update Mechanism independent thread management */
BOOL    StopUpdateThread(HANDLE hThread, BOOL fCloseAppNow);
BOOL    ActiveUpdateThread(void);
BOOL    TriggerUpdateThreadRefresh(void);

/* end of header file Threads.H */
