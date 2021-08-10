/******************************************************************************
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
*  PARTICULAR PURPOSE.
* 
*  Copyright (C) 1999 - 2000  Microsoft Corporation.  All Rights Reserved.
* 
    FILE:   Threads.C

    PURPOSE:    Implements the thread related functions for the PrintJob
      sample.

    FUNCTIONS:  
        CreateThreadSyncResources() - Creates synchronziation resources.

        DestroyThreadSyncResources() - Destroys synchronization resources.

        PollingUpdate() - Thread entry for watching queues by polling.

        StartPolling() - Creates a thread using PollingUpdate to show a printer
                         queue.

        StartNotifications() - Creates a thread using NotificationsUpdate to 
                               get and show changes to a printer queue.

        NotificationUpdate() - Thread Entry point for Printer Change Notifications

        ActiveUpdateThread() - Test for a running update thread.

        StopUpdateThread() - Shuts down and update thread.

        TriggerUpdateThreadRefresh() - Signals update thread to refresh.
* 
******************************************************************************/


#define STRICT
#include <windows.h>
#include <process.h>
#include "Threads.h"
#include "Queue.h"
#include "QueList.h"
#include "Errors.h"
#include "QueCore.h"


/* Thread synchronization globals */
DWORD   g_nPollIntervalms = 1500;       /* milliseconds polling resolution */
HANDLE  g_hTerminateEvent = NULL;       /* Signalling event for thread to terminate. */
HANDLE  g_hForceRefreshEvent = NULL;    /* Signal for thread to wakeup and refresh */
BOOL    fCloseApp = FALSE;              /* If true, the thread should post a WM_CLOSE */

/* Thread parameters */
typedef struct _threadparameters
{
    HWND    hWnd;                       /* the main aplication window */
    HANDLE  hPrinter;                   /* the printer to watch */
    HANDLE  hPrevThread;                /* The previous thread to be closed */
} THREADPARAM;


/******************************************************************************

  FUNCTION: CreateThreadSyncResources( void )

  PURPOSE:  On application initialization this should be called to create all
            the resources needed to synchronize the threads. 

  COMMENTS:
            Creates: g_hForceRefreshEvent, g_hTerminateEvent.

******************************************************************************/

BOOL CreateThreadSyncResources(void)
{
    /* Initialize Resources */
    g_hForceRefreshEvent = g_hTerminateEvent = NULL;


    /* 
     * Create thread termination resource 
     * If signaled, our worker thread must exit.
     * The resource is created initially signaled so that
     * we can use it to test for a running thread.
     */
    g_hTerminateEvent = CreateEvent(NULL,       /* no inheritance */
                                    TRUE,       /* Reset is manual */
                                    TRUE,       /* Initially signaled */
                                    "UpdateThreadTerminateEvent");
    if (!g_hTerminateEvent)
        goto Fail;
    
    /* 
     * Create thread refresh trigger resource 
     * If signaled, our worker thread must immediately refresh.
     * The resource is created not initially signaled so that
     * it does not trigger a superflouos update.
     */
    g_hForceRefreshEvent = CreateEvent(NULL,        /* no inheritance */
                                    TRUE,       /* Reset is manual */
                                    FALSE,      /* Initially signaled */
                                    "UpdateThreadRefreshEvent");
    if (!g_hForceRefreshEvent)
        goto Fail;

    return TRUE;
       
Fail:
    DestroyThreadSyncResources();
    return FALSE;

} /* end of function CreateThreadSyncResources */


/******************************************************************************

  FUNCTION: DestroyThreadSyncResources( void )

  PURPOSE:  On application shutdown this should be called to destroy all
            the resources needed to synchronize the threads. 

  COMMENTS:
            Destroys: g_hForceRefreshEvent, g_hTerminateEvent.

******************************************************************************/

BOOL DestroyThreadSyncResources(void)
{
    if (g_hTerminateEvent)
        CloseHandle(g_hTerminateEvent);
    if (g_hForceRefreshEvent)
        CloseHandle(g_hForceRefreshEvent);
    return TRUE;

} /* end of DestroyThreadSyncResources */


/******************************************************************************

  FUNCTION: PollingUpdate( DWORD )

  PURPOSE:  Thread entry point for performing printer queue updates using
            a polling algorithm. 

  COMMENTS:
            This thread uses WaitForMultipleObjects to wake up every
            g_nPollIntervalms milliseconds and refresh the contents of our
            printer queue. 

            It terminates on g_hTerminateEvent.

            DWORD is a handle to global memory formated as a THREADPARAM
            structure.

******************************************************************************/

unsigned __stdcall PollingUpdate(void *pParameters)
{
    THREADPARAM ThreadParam;    /* what we are to work with */
    THREADPARAM *pThreadParam;
    QUEUEDATA   Queue;          /* To keep our copy of the print queue */
    HANDLE      Handles[2];     /* one for refresh, one for terminate */
    HGLOBAL     hParameters;

    /* Transfer parameters to the thread's stack and free global memory */
    hParameters = (HGLOBAL)pParameters;
    pThreadParam = (THREADPARAM *)GlobalLock((HGLOBAL)hParameters);
    ThreadParam = *pThreadParam;
    
    /* we do not intend to pass anything back to the application so free memory */
    GlobalUnlock((HGLOBAL)hParameters);
    GlobalFree((HGLOBAL)hParameters);

    /* Terminate and Wait for previous thread to close down before we continue */
    if (ThreadParam.hPrevThread)
    {
        StopUpdateThread(ThreadParam.hPrevThread, FALSE);
        WaitForSingleObject(ThreadParam.hPrevThread, INFINITE);
        CloseHandle(ThreadParam.hPrevThread);
    }
    
    /* reinitialize the Termination Event so we don't exit the polling loop */
    ResetEvent(g_hTerminateEvent);
    
    /* initialize our Queue data structure*/
    ZeroMemory(&Queue, sizeof(Queue));
    Queue.Printer.hPrinter = ThreadParam.hPrinter;
    
    /* setup for WaitForMultipleObjects */
    Handles[0] = g_hTerminateEvent;
    Handles[1] = g_hForceRefreshEvent;
    /*
     * Loop until we are told to quit, waiting each time by
     * the polling interval.
     */
    do {
        /* Setup for refresh override */
        ResetEvent(g_hForceRefreshEvent);
        
        /* Get the data and show it */
        Refresh(ThreadParam.hWnd, &Queue);
        
        /* Wait for a terminate event, a refresh event, or the polling period */
        WaitForMultipleObjects(2, Handles, FALSE, g_nPollIntervalms);
    
    /* Keep going as long as we have not been told to quit! */
    } while (WaitForSingleObject(g_hTerminateEvent, 0) != WAIT_OBJECT_0);

    
    /* Cleanup */
    ClosePrinter(ThreadParam.hPrinter);
    FreeQueueData(&Queue);
    
    /* Thread posts the close message at the request of the Window Procedure 
     * so application will attempt to close down again and succeed since the 
     * thread has died.
     * We close down the app this way in order to avoid messaging deadlocks
     * by having the Window Procedure wait on this thread to exit.
     */
    if (fCloseApp)
        PostMessage(ThreadParam.hWnd, WM_CLOSE, 0, 0);
    
    return TRUE;

} /* end of Thread entry point function PollingUpdate */


/******************************************************************************

  FUNCTION: StartPolling( HWND, HANDLE, HANDLE )

  PURPOSE:  Creates a thread which polls for all changes to a printer queue. 

  COMMENTS:
            HWND is the main application window handle followed by a HANDLE to
            the opened printer and the HANDLE to any previous thread.

            This function creates the polling thread and returns immediately.
            The thread entry point is NotificationUpdate().

            The return value is the handle to the created thread.

******************************************************************************/

HANDLE StartPolling(HWND hWnd, HANDLE hPrinter, HANDLE hPrevThread)
{   
    UINT       ThreadID;
    THREADPARAM *pThreadParam;
    HGLOBAL     hParam;
    HANDLE      hThread;

    /* create parameters to thread */
    hParam = GlobalAlloc(GHND, sizeof(THREADPARAM));
    pThreadParam = (THREADPARAM *)GlobalLock(hParam);
    pThreadParam->hWnd = hWnd;               /* Main application Window */
    pThreadParam->hPrinter = hPrinter;       /* Printer now owned by thread */
    pThreadParam->hPrevThread = hPrevThread; /* Previous thread to terminate */
    GlobalUnlock(hParam);

    /* Thread is responsible for deleteing the Global memory containing the
     * parameters.
     * The thread is responsible for closing the printer
     * and the thread is responsible for killing & closing the previous thread
     * It also is responsible for closing the application if it is asked.
     *
     * Note we use _beginthreadex from the runtime library to avoid problems
     * between the run time library and the OS CreateThread
     */
    hThread = (HANDLE)_beginthreadex(NULL,
                    0,
                    PollingUpdate,
                    (void *)hParam,
                    1,
                    &ThreadID);

    return hThread;

} /* end of function StartPolling */


/******************************************************************************

  FUNCTION: StartNotifications( HWND, HANDLE, HANDLE )

  PURPOSE:  Creates a thread which uses Printer Change Notifications to be 
            alerted when changes occur to a printer queue. 

  COMMENTS:
            HWND is the main application window handle followed by a HANDLE to
            the opened printer and the HANDLE to any previous thread.

            This function creates the thread and returns immediately.
            The thread entry point is NotificationUpdate().

            The return value is the handle to the created thread.

******************************************************************************/

HANDLE StartNotifications(HWND hWnd, HANDLE hPrinter, HANDLE hPrevThread)
{   
    UINT        ThreadID;
    THREADPARAM *pThreadParam;
    HGLOBAL     hParam;
    HANDLE      hThread;

    /* create parameters to thread */
    hParam = GlobalAlloc(GHND, sizeof(THREADPARAM));
    pThreadParam = (THREADPARAM *)GlobalLock(hParam);
    pThreadParam->hWnd = hWnd;
    pThreadParam->hPrinter = hPrinter;
    pThreadParam->hPrevThread = hPrevThread;
    GlobalUnlock(hParam);

    /* Thread is responsible for deleteing the Global memory containing the
     * parameters.
     * The thread is responsible for closing the printer
     * and the thread is responsible for killing & closing the previous thread
     * It also is responsible for closing the application if it is asked.
     *
     * Note we use _beginthreadex from the runtime library to avoid problems
     * between the run time library and the OS CreateThread
     */
    hThread = (HANDLE)_beginthreadex(NULL,
                    0,
                    NotificationUpdate,
                    (void *)hParam,
                    1,
                    &ThreadID);
    return hThread;

} /* end of function StartNotifications */


/******************************************************************************

  FUNCTION: NotificationUpdate( DWORD )

  PURPOSE:  Thread entry point for using Printer Change Notifications to be 
            alerted when changes occur to a printer queue. 

  COMMENTS:
            The DWORD contains a handle to global memory formated as a 
            THREADPARAM structure.

******************************************************************************/

unsigned __stdcall NotificationUpdate(void *pParameters)
{
    THREADPARAM             ThreadParam;            /* Parameters for the thread */
    THREADPARAM *           pThreadParam;
    HANDLE                  hPrinterNotification;   /* The PrinterChangeNotification object */
    HANDLE                  Handles[3];             /* Array of objects waited on in the loop */
    HGLOBAL                 hParam;
    DWORD                   WaitResult;             /* High level info from the PrinterChangeNotification */
    DWORD                   OldFlags;               /* Temporary variable */
    PRINTER_NOTIFY_INFO *   pNotification = NULL;   /* The stuff that changed to cause the notification */
    WORD                    JobFields[] = 
        {                                   /* Job Fields we want notifications for */
        JOB_NOTIFY_FIELD_STATUS,            /* Status bits */
        JOB_NOTIFY_FIELD_STATUS_STRING,     /* Status String */
        JOB_NOTIFY_FIELD_DOCUMENT,          /* Document Name */
        JOB_NOTIFY_FIELD_USER_NAME,         /* Name of Documents owner */
        JOB_NOTIFY_FIELD_TOTAL_PAGES,       /* Total pages in the job */
        JOB_NOTIFY_FIELD_PAGES_PRINTED,     /* # of pages of the job that have printed */
        JOB_NOTIFY_FIELD_SUBMITTED,         /* The time and date job was submitted */
        JOB_NOTIFY_FIELD_BYTES_PRINTED,     /* # of bytes sent to printer */
        JOB_NOTIFY_FIELD_TOTAL_BYTES        /* Total bytes in the print job */
        };
    WORD                    PrinterFields[] = 
        {
        PRINTER_NOTIFY_FIELD_STATUS,        /* Status bits of printer queue */
        PRINTER_NOTIFY_FIELD_CJOBS,         /* # of jobs in printer queue */
        PRINTER_NOTIFY_FIELD_PRINTER_NAME,  /* Name of the printer queue */
        PRINTER_NOTIFY_FIELD_SERVER_NAME,   /* Name of the server when the queue is remote */
        PRINTER_NOTIFY_FIELD_SHARE_NAME     /* The queue's sharename */
        };
	
    PRINTER_NOTIFY_OPTIONS_TYPE Notifications[2] =                  
        {                                   /* The notification we want to be notified of */
            {
                JOB_NOTIFY_TYPE,            /* We want notifications on print jobs */
                0,
                0,
                0,
                sizeof(JobFields)/sizeof(JobFields[0]), /* We specified 9 fields in the JobFields array */
                NULL						/* Precisely which fields we want notifications for */
            },
            {
                PRINTER_NOTIFY_TYPE,        /* We want notification on the printer queue too */
                0,
                0,
                0,
                sizeof(PrinterFields)/sizeof(PrinterFields[0]), /* How many printer fields? */
                NULL						/* Precisely what printer fields we want */
            }
        };
	
    PRINTER_NOTIFY_OPTIONS NotificationOptions = 
        {
            2,                                  /* Version of structure, see docs */
            PRINTER_NOTIFY_OPTIONS_REFRESH,     /* Options for FindNextPrinterChangeNotification */
            2,                                  /* # of Printer_Notify_Info structures */
            NULL			                    /* What we want notifications of */
        };


    QUEUEDATA               Queue;              /* Our copy of the printer queue's data */

	Notifications[0].pFields = JobFields;
	Notifications[1].pFields = PrinterFields;
	NotificationOptions.pTypes = Notifications;
    
    /* 
     * Transfer parameters to the thread's stack and 
     * free the global memory 
     */
    hParam = (HGLOBAL)pParameters;
    pThreadParam = (THREADPARAM *)GlobalLock((HGLOBAL)hParam);
    ThreadParam = *pThreadParam;
    
    /* 
     * we do not intend to pass anything back to the 
     * application so free the memory used to get us Params.
     */
    GlobalUnlock((HGLOBAL)hParam);
    GlobalFree((HGLOBAL)hParam);

    /* Terminate and Wait for previous thread to close down before we continue */
    if (ThreadParam.hPrevThread)
    {
        StopUpdateThread(ThreadParam.hPrevThread, FALSE);
        WaitForSingleObject(ThreadParam.hPrevThread, INFINITE);
        CloseHandle(ThreadParam.hPrevThread);
    }
    
    /* reinitialize the Termination Event so we can proceed */
    ResetEvent(g_hTerminateEvent);

    hPrinterNotification = FindFirstPrinterChangeNotification(
        ThreadParam.hPrinter,           /* The printer of interest */
        PRINTER_CHANGE_DELETE_JOB,      /* We need to know when a job is removed */
        0,                              /* reserved */
        &NotificationOptions);          /* The details of what notifications that are needed */

    /* Check for an error */
    if (hPrinterNotification == INVALID_HANDLE_VALUE)
    {
        ErrorBox(GetLastError(), "FindFirstPrinterChangeNotification");
        return 0;
    }


    /* 
     * Loop on the Notifications, a terminate event, or a refresh event
     */
    
    /* setup for a WaitForMultipleObjects */
    Handles[0] = hPrinterNotification;
    Handles[1] = g_hTerminateEvent;
    Handles[2] = g_hForceRefreshEvent;
    
    /* Initialize for our local data structure */
    ZeroMemory(&Queue, sizeof(Queue));
    Queue.Printer.hPrinter = ThreadParam.hPrinter;

    /* Initialize the display and our local copy of the printer queue data */
    Refresh(ThreadParam.hWnd, &Queue);
    
    /* 
     * Loop while we are stilling waiting on Notifications.
     */
    while (hPrinterNotification != INVALID_HANDLE_VALUE)
    {
        /* wait for a printer notification, terminate event, or refresh event */
        WaitForMultipleObjects(3, Handles, FALSE, INFINITE);

        /* check to see if the thread needs to quit. */
        if (WaitForSingleObject(g_hTerminateEvent, 0) == WAIT_OBJECT_0)
        {
            /* This should be the only way out of the loop */
            FindClosePrinterChangeNotification(hPrinterNotification);
            hPrinterNotification = INVALID_HANDLE_VALUE;
        }
        
        /* or check to see if the notification object for the printer queue is signaled */
        else if (WaitForSingleObject(hPrinterNotification, 0) == WAIT_OBJECT_0)
        {
            /* get the changes and reset the notification */
            if (!FindNextPrinterChangeNotification(hPrinterNotification,
                &WaitResult,            /* for the PRINTER_CHANGE_DELETE_JOB notice */
                &NotificationOptions,   /* The notifications */
                &pNotification))        /* address of pointer that gets what changed */
            {
                ErrorBox(GetLastError(), "FindNextPrinterChangeNotification");
            }
            
            /* Did a notification overflow occur? */
            if (pNotification && pNotification->Flags & PRINTER_NOTIFY_INFO_DISCARDED)
            {
                /* An overflow of notifications occured, must refresh to continue */

                OldFlags = NotificationOptions.Flags;
                
                NotificationOptions.Flags = PRINTER_NOTIFY_OPTIONS_REFRESH;

                FreePrinterNotifyInfo(pNotification);
                if (!FindNextPrinterChangeNotification(hPrinterNotification,
                    &WaitResult,
                    &NotificationOptions,
                    &pNotification))
                {
                    ErrorBox(GetLastError(), "FindNextPrinterChangeNotification refresh call.");
                }
                NotificationOptions.Flags = OldFlags;

                /* Start Over with Refreshed Data */
                Refresh(ThreadParam.hWnd, &Queue);

            }

            /* process the notification of changes */
            if (WaitResult & PRINTER_CHANGE_DELETE_JOB)
            {
                /* a job was deleted so start over clean */
                Refresh(ThreadParam.hWnd, &Queue);
            }
            else
            {
                /* track and show the changes */
                RefreshFromNotification(ThreadParam.hWnd, &Queue, pNotification);
            }
            FreePrinterNotifyInfo(pNotification);
            pNotification = NULL;
        }
        
        /* Or, maybe the user wants to refresh the view of the print queue */
        else if (WaitForSingleObject(g_hForceRefreshEvent, 0) == WAIT_OBJECT_0)
        {
            Refresh(ThreadParam.hWnd, &Queue);
            ResetEvent(g_hForceRefreshEvent);
        }


    }
    
    /* Done watching for notifications, cleanup */
    ClosePrinter(ThreadParam.hPrinter);
    FreeQueueData(&Queue);
    
    /* Thread posts the close message when the application is going away so the
     * the application willattempt to close down again and succeed since the 
     * thread has died.
     */
    if (fCloseApp)
        PostMessage(ThreadParam.hWnd, WM_CLOSE, 0, 0);
    
    return TRUE;

} /* end of Thread entry point function NotificationUpdate */


/******************************************************************************

  FUNCTION: ActiveUpdateThread( void )

  PURPOSE:  Test to see if a thread is currently running.

  COMMENTS:
            g_hTerminateEvent is created initially signaled and it is left
            signaled whenver a thread exits. It is not signaled only when a 
            thread is running.

******************************************************************************/

BOOL ActiveUpdateThread(void)
{
    /* let the caller know if a thread is running */
    return !(WaitForSingleObject(g_hTerminateEvent, 0) == WAIT_OBJECT_0);

} /* end of ActiveUpdateThread */


/******************************************************************************

  FUNCTION: StopUpdateThread( HANDLE, BOOL )

  PURPOSE:  Signals the current update thread to shutdown.

  COMMENTS:
            If BOOL is TRUE it is a signal to the thread that is shutting
            down that it also needs to shutdown the application with WM_CLOSE.

******************************************************************************/

BOOL StopUpdateThread(HANDLE hThread, BOOL fCloseAppNow)
{
    /* No thread running? */
    if (!hThread)
        return FALSE;

    /* Should we close the application too? */
    fCloseApp = fCloseAppNow;

    /* tell thread to quit */
    SetEvent(g_hTerminateEvent);

    return TRUE;
        
} /* end of StopNotifications function */


/******************************************************************************

  FUNCTION: TriggerUpdateThreadRefresh( void )

  PURPOSE:  Tells an update thread to refresh the printer queue contents.

  COMMENTS:
            The g_hForceFrefreshEvent is signaled which triggers the update
            thread into refreshing the contents of the entire queue.

******************************************************************************/

BOOL TriggerUpdateThreadRefresh(void)
{
    /* Signal the event that forces a refresh of the display /*/
    return SetEvent(g_hForceRefreshEvent);

} /* end of TriggerUpdateThreadRefresh function */

/* end of source file Threads.C */