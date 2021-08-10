/******************************************************************************
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
*  PARTICULAR PURPOSE.
* 
*  Copyright (C) 1999 - 2000  Microsoft Corporation.  All Rights Reserved.
* 
*   FILE:   PrintJob.c
* 

        PROGRAM: PrintJob

        PURPOSE: Demonstrates the Win32 Spooler API for retrieving printer 
                 and print job status.

                 This sample also demonstrates:

                    Simple use of the ListView common control.
                    Multithreaded programming techniques.

        FUNCTIONS:

        WinMain() - Calls initialization function, processes message loop

        InitApplication() - Initializes window data and registers window.

        InitInstance() - Saves instance handle, creates thread synchornization 
                         objects, and creates main window.
        
        CloseInstance() - Destroys thread synchronizatoin objects and general 
                          cleanup.
        WndProc() - Processes messages and creates threads in response to menu
                    items.

        CenterWindow() - Used to center the "About" box over application window.

        Refresh() - Performs a complete replacement of the applications copy of the 
                    Printer Queue.

        RefreshFromNotification() - Updates the application's copy of the Printer 
                                    Queue data from Printer Change Notifications.

        UpdateWindowTitle() - Sets the Application's Window caption with the name and
                              state of the printer.

        MakeJobStatusStr() - Compounds the status bits of a DWORD into a string.

        MakePrinterStatusStr() - Creats a descriptive string of a printers DWORD status.

        UpdateQueue() - Update's the printer queue data structure with data from Printer
                        Change Notifications.

        GetQueue() - Uses Spooler API's to build a printer queue data structure copy of a
                     Printer Queue's current state.

        OnSelectPrinter() - Process's a user's printer selection command and starts the 
                            process of monitoring a new printer queue.

        OnPrinterNotificationOption() - Toggles the applications use of Printer Change 
                                        Notifications.

        COMMENTS:

                The PrintJob Application Example is a sample application
                that uses Win32 Spooler API's to monitor Printer Queues in Windows 95
                or Windows NT. This sample demonstrates Multithreading and the Print 
                Spooler functions available in the Win32 SDK. Multithreading is used to
                block on system objects that provide timing for or notification of 
                system events in the print spooler while maintianing a responsive user 
                interface for the user.

                The program uses the following Spooler API's and structures:

                FindFirstPrinterChangeNotification()
                FindNextPrinterChangeNotification()
                FreePrinterNotifyInfo()
                OpenPrinter()
                ClosePrinter()
                GetPrinter()
                EnumJobs()


                PRINTER_NOTIFY_INFO
                PRINTER_NOTIFY_OPTIONS_TYPE
                PRINTER_NOTIFY_OPTIONS
                JOB_INFO_2
                PRINTER_INFO_2


                The following Kernel/Base API's and structures are used for Multithreading:

                CreateThread()
                CreateEvent()
                CloseHandle()
                WaitForSingleObject()
                WaitForMultipleObjects()
                ResetEvent()
                SetEvent()
                PostMessage()

                HANDLE

               
                This application is compatible with Windows 95 and
                Windows NT. The application customize's its capabilities based on what
                Operating System is in use.

****************************************************************************/


#define STRICT
#include <windows.h>   /* required for all Windows applications             */
#include "resource.h"  /* Windows resource IDs for this application         */
#include "Queue.h"     /* Custom Printer Queue data structure               */
#include "QueList.h"   /* Module containing the list view common control    */
#include "Dialogs.h"   /* Module with the Windows Dialog code               */
#include "Threads.h"   /* Module of threading code for this sample          */
#include "PrintJob.h"  /* declarations specific to this program             */
#include "QueCore.h"   /* declarations for operations on printer queue data */

/* 
 * Application globals 
 */
HINSTANCE g_hInst;     /* current application instance */

char g_szAppName[] = "PrintJob";   // The name of this application
char g_szTitle[]   = "Print Job Viewer"; // The title bar text

static HWND     g_hWndJobList;  /* Window handle of list view control */
static BOOL     g_fUsePrinterChanges = FALSE;   /* Toggle for NT feature, polling by default */

/* 
 * Macro definitions 
 */
#define IS_NT           (BOOL)(GetVersion() < 0x80000000)
#define PrinterNameSize 200


/************ Local Function declarations *************/

/* 
 * application management 
 */
BOOL    InitApplication(HANDLE);
BOOL    InitInstance(HANDLE, int);
BOOL    CloseInstance(HANDLE);

/* access to Printer Ques */
void    MakePrinterStatusStr(char *pBuffer, short nChars, DWORD dwStatus);
BOOL    GetQueue(QUEUEDATA *pQueueData);

/* Utility */
BOOL IsPrinterHandle( HANDLE hPrinter );

/* message processing */
BOOL OnSelectPrinter(HWND hWnd, char *pszPrinterName, unsigned short cbNameSize, HANDLE *pThreadHandle);
BOOL OnPrinterNotificationOption(HWND hWnd, char *pszPrinterName, HANDLE *pThreadHandle);

/*
 * Windows Application Functions
 */

/****************************************************************************

        FUNCTION: WinMain(HINSTANCE, HINSTANCE, LPSTR, int)

        PURPOSE: calls initialization function, processes message loop

        COMMENTS:

                Windows recognizes this function by name as the initial entry point
                for the program.  This function calls the application initialization
                routine, if no other instance of the program is running, and always
                calls the instance initialization routine.  It then executes a message
                retrieval and dispatch loop that is the top-level control structure
                for the remainder of execution.  The loop is terminated when a WM_QUIT
                message is received, at which time this function exits the application
                instance by returning the value passed by PostQuitMessage().

                If this function must abort before entering the message loop, it
                returns the conventional value NULL.

****************************************************************************/
int CALLBACK WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow)
{

        MSG msg;
        HANDLE hAccelTable;

        if (!hPrevInstance) {       // Other instances of app running?
            if (!InitApplication(hInstance)) { // Initialize shared things
                return (FALSE);     // Exits if unable to initialize
            }
        }

        /* Perform initializations that apply to a specific instance */

        if (!InitInstance(hInstance, nCmdShow)) {
            return (FALSE);
        }

        hAccelTable = LoadAccelerators (hInstance, MAKEINTRESOURCE(IDR_PRINTJOB));

        /* Acquire and dispatch messages until a WM_QUIT message is received. */

        while (GetMessage(&msg, // message structure
            NULL,   // handle of window receiving the message
            0,      // lowest message to examine
            0))     // highest message to examine
        {
            if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg)) 
            {
                TranslateMessage(&msg);// Translates virtual key codes
                DispatchMessage(&msg); // Dispatches message to window
            }
        }

        CloseInstance(hInstance);

        return (int)(msg.wParam); // Returns the value from PostQuitMessage

        lpCmdLine; // This will prevent 'unused formal parameter' warnings

} /* end of function WinMain */


/****************************************************************************

        FUNCTION: InitApplication(HINSTANCE)

        PURPOSE: Initializes window data and registers window class

        COMMENTS:

                This function is called at initialization time only if no other
                instances of the application are running.  This function performs
                initialization tasks that can be done once for any number of running
                instances.

                In this case, we initialize a window class by filling out a data
                structure of type WNDCLASS and calling the Windows RegisterClass()
                function.  Since all instances of this application use the same window
                class, we only need to do this when the first instance is initialized.


****************************************************************************/

BOOL InitApplication(HINSTANCE hInstance)
{
        WNDCLASS  wc;

        // Fill in window class structure with parameters that describe the
        // main window.

        wc.style         = 0;                      // Class style(s).
        wc.lpfnWndProc   = (WNDPROC)WndProc;       // Window Procedure
        wc.cbClsExtra    = 0;                      // No per-class extra data.
        wc.cbWndExtra    = 0;                      // No per-window extra data.
        wc.hInstance     = hInstance;              // Owner of this class
        wc.hIcon         = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_APP)); // Icon name from .RC
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);// Cursor
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);// Default color
        wc.lpszMenuName  = MAKEINTRESOURCE(IDR_PRINTJOB); // Menu from .RC
        wc.lpszClassName = g_szAppName;              // Name to register as

        // Register the window class and return success/failure code.
        return (RegisterClass(&wc));
} /* end of function InitApplication */


/****************************************************************************

        FUNCTION:  InitInstance(HINSTANCE, int)

        PURPOSE:  Saves instance handle and creates main window

        COMMENTS:

                This function is called at initialization time for every instance of
                this application.  This function performs initialization tasks that
                cannot be shared by multiple instances.

                In this case, we save the instance handle in a static variable and
                create and display the main program window.

****************************************************************************/

BOOL InitInstance(
        HINSTANCE       hInstance,
        int             nCmdShow)
{
        HWND            hWnd; /* Main window handle. */

        // Save the instance handle in static variable, which will be used in
        // many subsequent calls from this application to Windows.

        g_hInst = hInstance; // Store instance handle in our global variable

        // This application uses common controls, make sure they are ready
        InitCommonControls();
        
        // Create synchronization objects, if not, return "failure"
        if (!CreateThreadSyncResources())
        {
            return (FALSE);
        }

        // Create a main window for this application instance.
        hWnd = CreateWindow(
                g_szAppName,           // See RegisterClass() call.
                g_szTitle,             // Text for window title bar.
                WS_OVERLAPPEDWINDOW, // Window style.
                CW_USEDEFAULT, 0, 
                CW_USEDEFAULT, 0,    // Use default positioning but adjusted for size
                NULL,                // Overlapped windows have no parent.
                NULL,                // Use the window class menu.
                hInstance,           // This instance owns this window.
                NULL                 // We don't use any data in our WM_CREATE
        );

        // If window could not be created, return "failure"
        if (!hWnd) 
        {
            DestroyThreadSyncResources();
            return (FALSE);
        }


        // Make the window visible; update its client area; and return "success"
        ShowWindow(hWnd, nCmdShow); // Show the window
        UpdateWindow(hWnd);         // Sends WM_PAINT message

        return (TRUE);              // We succeeded...

} /* end of function InitInstance */

/****************************************************************************

        FUNCTION:  CloseInstance(HINSTANCE)

        PURPOSE:  Orderly shutdown of this instance of the application

        COMMENTS:

                This function is called when the application is shutting down
                after it has exited the message processing loop.

                It is used to destroy application global resources used during
                execution of this instance.

****************************************************************************/

BOOL CloseInstance(HANDLE hInst)
{
    
    DestroyThreadSyncResources();
    
    return TRUE;

} /* end of function CloseInstance */



/****************************************************************************

        FUNCTION:  IsPrinterHandle(HANDLE)

        PURPOSE:  Determines if a handle to a printer is to a real printer.

        COMMENTS:

                If the handle is bogus or it is a handle to a printer server
                the function will return FALSE.

****************************************************************************/

BOOL IsPrinterHandle( HANDLE hPrinter )
{
    DWORD       cbNeeded;
    DWORD       Error;
    BOOL        fRet = TRUE;

    // Test if the handle is to a printer by asking how big
    // a buffer is needed to describe it.
    if( !GetPrinter(hPrinter, 2, (LPBYTE)NULL, 0, &cbNeeded ))
    {
        // The function failed so the handle might not be a printer
        Error = GetLastError( );
        fRet = FALSE;

        if( Error == ERROR_INSUFFICIENT_BUFFER )
        {
            // Apparently the handle was a printer, but as expected
            // We didn't give it a buffer
            fRet = TRUE;
        }
        // Else, the handle is not to a valid printer
    }
    return fRet;

} /* end of function IsPrinterHandle */


/****************************************************************************

        FUNCTION:  OnSelectPrinter(HWND, char *, unsigned short, HANDLE *)

        PURPOSE:  Processes user command to select a printer to watch

        COMMENTS:

                This function is called by the Window Procedure's command 
                processing in response to a user's selection of the 
                Printer | Select menu.

                It is used validate the user's entry and start a seperate 
                thread which monitors the selected printer's print queue.

****************************************************************************/

BOOL OnSelectPrinter(HWND hWnd, char *pszPrinterName, unsigned short cbNameSize, HANDLE *pThreadHandle)
{
    HANDLE hNewPrinter = NULL;
    HANDLE hThread;

    /* 
     * Present the user with Printer Selection Dialog until success or cancel 
     */
    
    // Loop unless dialog canceled
    while (GetPrinterPath(hWnd, pszPrinterName, cbNameSize))
    {
        // OK button pressed, see if the printer name is recognized.
        if (OpenPrinter(pszPrinterName, &hNewPrinter, NULL) && IsPrinterHandle ( hNewPrinter ))
        {
            /*  
             * On NT, a valid printer name is the Printer Name or 
             * a UNC share name. Note that for printer connections, the Printer 
             * name appears in the printer folder in a parsed form:
             * "[PrinterName] on [Server]" corresponds to an actual pPrinterName of
             * "\\[Server]\[PrinterName]" - where [PrinterName] is the pPrinterName
             * on the Server.
             * 
             * On Windows 95 a valid printer name is the port(e.g. LPTX:), 
             * Printer name, or UNC share name. Printer Name and share name are
             * unambigous, but if a port is given, OpenPrinter returns a handle to 
             * the first Printer it encounters using that port.
             */

            if (!g_fUsePrinterChanges)
            /* if application not using Printer Change Notification's, use polling */
            {
                /* 
                 * Start a new polling thread to refresh the 
                 * Job list.
                 */
                hThread = StartPolling(hWnd, hNewPrinter, *pThreadHandle);
            }
            else
            {
                /* 
                 * On Windows NT, the application can use 
                 * Printer Change Notifications which are more
                 * efficient.
                 */
                hThread = StartNotifications(hWnd, hNewPrinter, *pThreadHandle);
            }

            *pThreadHandle = hThread;
            return TRUE;
        }
        else // nope, user typed in something that was wrong
        {
            if (hNewPrinter)
                ClosePrinter ( hNewPrinter );
            /*
             * Tell the user we do not recognize their selection.
             */
            if (MessageBox(hWnd, 
                "The printer name you specified cannot be found.",
                "Printer Selection Error", MB_OKCANCEL | MB_ICONSTOP) 
                == IDCANCEL)
                // User asked to leave, break out of loop
                break;
        }

    }

    return FALSE;

} /* end of function OnSelecPrinter */


/****************************************************************************

        FUNCTION:  OnPrinterNotificationOption(HWND , char *, HANDLE *)

        PURPOSE:  Processes user command to switch between polling and Printer
                  Change notifications.

        COMMENTS:

                This function is called by the Window Procedure's command 
                processing in response to a user's selection of the 
                "Options | Use Printer Notifications" menu itme.

                This function toggles the menu and application state for using
                polling or Printer Change Notifications as the trigger for
                updating the internal data structures and the displayed ListView
                of the selected printer's print queue.

                If the application was monitoring a printer queue it restarts
                a monitoring thread using the new polling or notification
                method.

                Otherwise it merely toggles the state of the option.

                Notifications and the menu item are disabled by default in the 
                resources and are only enabled if the application startup code 
                determines that the application is running on Windows NT.

****************************************************************************/

BOOL OnPrinterNotificationOption(HWND hWnd, char *pszPrinterName, HANDLE *pThreadHandle)
{
    HMENU   hOptionsMenu;
    HANDLE  hNewPrinter;
    HANDLE  hThread = NULL;

    hOptionsMenu = GetSubMenu(GetMenu(hWnd), 1);
    hNewPrinter = NULL;

    /*
     * If we are currently running a thread,
     * get a new printer handle since the thread owns
     * the one we passed it and we are going to start
     * a new thread with the same printer.
     */
    if (ActiveUpdateThread())
    {
        if (!OpenPrinter(pszPrinterName, &hNewPrinter, NULL))
        {
            /* Bogus printer name */
            hNewPrinter = NULL;
            
            /* Bail */
            return FALSE;
        }
    
    }

    if (g_fUsePrinterChanges)
    {
        /* Switch back to polling */
        g_fUsePrinterChanges = FALSE;
        CheckMenuItem(hOptionsMenu, IDM_PRINTERNOTIFICATION, MF_UNCHECKED | MF_BYCOMMAND);
        if (hNewPrinter)
        {
            hThread = StartPolling(hWnd, hNewPrinter, *pThreadHandle);
        }

    }
    else
    {
        /* Switch to using Printer Change Notifictions on NT */
        g_fUsePrinterChanges = TRUE;
        CheckMenuItem(hOptionsMenu, IDM_PRINTERNOTIFICATION, MF_CHECKED | MF_BYCOMMAND);
        if (hNewPrinter)
        {
            hThread = StartNotifications(hWnd, hNewPrinter, *pThreadHandle);
        }
    }

    *pThreadHandle = hThread;
    return TRUE;

} /* end of function OnPrinterNotificationOption */


/****************************************************************************

        FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)

        PURPOSE:  Processes messages

        MESSAGES:

        WM_COMMAND    - application menu: About; Select Printer;
                        Toggle Printer Notifications; Exit; Refresh
        WM_DESTROY    - destroy window
        WM_CREATE     - Creates Child Window ListView control,
                        Initializes local variables,
                        and Enables OS dependent features.
        WM_SIZE       - Processed to resize Child ListView control.
        WM_ERASEBKGND - Processed to prevent background painting over the
                        child ListView Control.
        WM_NOTIFY     - Processed as an example.
        WM_CLOSE      - Checks for any running worker threads and shuts
                        them down before closing the application.
        WM_CREATE     - Sets defaults, createst the list child window, and
                        enables notifications if running on NT.

        COMMENTS:


****************************************************************************/

LRESULT CALLBACK WndProc(
                HWND hWnd,         // window handle
                UINT message,      // type of message
                WPARAM uParam,     // additional information
                LPARAM lParam)     // additional information
{
        int     wmId, wmEvent;
static  char    PrinterName[PrinterNameSize]; // Name of Printer Selected, kept as a convenience to the user
static  HANDLE  hListUpdateThread = NULL;   // handle to thread which updates the job list


        switch (message) 
        {
            case WM_CREATE:
            {
                HMENU   hOptionsMenu = GetSubMenu(GetMenu(hWnd), 1);

                /* Variable initialization */
                lstrcpyn(PrinterName, "", PrinterNameSize);
                
                /* Create the control to display printer info */
                g_hWndJobList = CreateQueList(hWnd);

                /* 
                 * Enable use of the Printer Notifications Option on NT,
                 * the option is disabled by default in the resources.
                 */
                if (IS_NT)
                {
                    EnableMenuItem(hOptionsMenu, IDM_PRINTERNOTIFICATION, MF_ENABLED | MF_BYCOMMAND);
                }

                break;
            }

            case WM_SIZE:
            {
                /* resize list box windows to match main window */
                ResizeQueList(g_hWndJobList, hWnd);
                break;
            }
            case WM_ERASEBKGND:
            {
                /* 
                 * Don't let the client area be painted since our
                 * list view control covers it entirely.
                 * This prevents disco flicker.
                 */
                break;
            }

            case WM_COMMAND:  // message: command from application menu
            {
                wmId    = LOWORD(uParam);
                wmEvent = HIWORD(uParam);

                switch (wmId) 
                {
                    case IDM_ABOUT:
                    {
                        DialogBox(g_hInst,                      // current instance
                                MAKEINTRESOURCE(IDD_ABOUTBOX),  // dlg resource to use
                                hWnd,                           // parent handle
                                (DLGPROC)About);                // About() instance address
                        break;
                    }

                    case IDM_SELECTPRINTER:
                    {
                        OnSelectPrinter(hWnd, PrinterName, sizeof(PrinterName), &hListUpdateThread);
                        break;
                    }

                    case IDM_PRINTERNOTIFICATION:
                    {
                        if (IS_NT)
                        {
                            OnPrinterNotificationOption(hWnd, PrinterName, &hListUpdateThread);
                        }
                        break;
                    }

                    case IDM_EXIT:
                    {
                        PostMessage(hWnd, WM_CLOSE, 0, 0);
                        break;
                    }

                    case ID_FILE_REFRESH:
                    {
                        TriggerUpdateThreadRefresh();
                        break;
                    }

                    default:
                        return (DefWindowProc(hWnd, message, uParam, lParam));
                }
                break;
            }

            case WM_CLOSE:
            {
                /* Close any thread and free its resources */
                if (ActiveUpdateThread())
                {
                    /* 
                     * Can't close down yet because a thread is running, 
                     * ask the thread to terminate and close the app down 
                     * when it is done.
                     */
                    StopUpdateThread(hListUpdateThread, TRUE);
                    break;
                }
                
                /* 
                 * Otherwise, no thread running
                 */
                CloseHandle(hListUpdateThread);
                hListUpdateThread = NULL;
                DestroyWindow (hWnd);
                break;
            }

            case WM_DESTROY:  // message: window being destroyed
            { 
                /* Quit the Message Loop */
                PostQuitMessage(0);
                break;
            }

            default:          // Passes it on if unproccessed
                return (DefWindowProc(hWnd, message, uParam, lParam));
        }
        return (0);

} /* end of function WndProc */


/****************************************************************************

    FUNCTION: CenterWindow (HWND, HWND)

    PURPOSE:  Center one window over another

    COMMENTS:

        Dialog boxes take on the screen position that they were designed at,
        which is not always appropriate. Centering the dialog over a particular
        window usually results in a better position.

****************************************************************************/

BOOL CenterWindow (HWND hwndChild, HWND hwndParent)
{
        RECT    rChild, rParent;
        int     wChild, hChild, wParent, hParent;
        int     wScreen, hScreen, xNew, yNew;
        HDC     hdc;

        // Get the Height and Width of the child window
        GetWindowRect (hwndChild, &rChild);
        wChild = rChild.right - rChild.left;
        hChild = rChild.bottom - rChild.top;

        // Get the Height and Width of the parent window
        GetWindowRect (hwndParent, &rParent);
        wParent = rParent.right - rParent.left;
        hParent = rParent.bottom - rParent.top;

        // Get the display limits
        hdc = GetDC (hwndChild);
        wScreen = GetDeviceCaps (hdc, HORZRES);
        hScreen = GetDeviceCaps (hdc, VERTRES);
        ReleaseDC (hwndChild, hdc);

        // Calculate new X position, then adjust for screen
        xNew = rParent.left + ((wParent - wChild) /2);
        if (xNew < 0) 
        {
            xNew = 0;
        } else if ((xNew+wChild) > wScreen) 
        {
            xNew = wScreen - wChild;
        }

        // Calculate new Y position, then adjust for screen
        yNew = rParent.top  + ((hParent - hChild) /2);
        if (yNew < 0) 
        {
            yNew = 0;
        } 
        else if ((yNew+hChild) > hScreen) 
        {
            yNew = hScreen - hChild;
        }

        // Set it, and return
        return SetWindowPos (hwndChild, 
                             NULL,
                             xNew, 
                             yNew, 
                             0, 
                             0, 
                             SWP_NOSIZE | SWP_NOZORDER);

} /* end of function CenterWindow */





/***************************************************************************
 *
 * Core Application Printer Queue Processing Functions
 *
 **************************************************************************/

/****************************************************************************

    FUNCTION:  Refresh(HWND, QUEUEDATA *)

    PURPOSE:   Replaces the contents of the application's custom printer queue
               data structure and then updates the ListView control that 
               displays the contents of the printer queue.
                
    COMMENTS:

            This function is called whenever the entire contents of the list 
            view should be updated.

****************************************************************************/

void Refresh(HWND hWnd, QUEUEDATA *pQueue)
{
    /* retrieve job info from the printer */
    if (GetQueue(pQueue))
    {       
        /* update the list boxes */
        SetQueListContents(g_hWndJobList, pQueue);

        /* update queue status in window caption */
        UpdateWindowTitle(hWnd, pQueue);
    }

} /* end of function Refresh */


/****************************************************************************

    FUNCTION:  MakeJobStatusStr(char *, short, DWORD)

    PURPOSE:   Creates a descriptive string in the char * buffer which is of
               size short from the Print Job status bits contained in DWORD.
                
    COMMENTS:

            One, none, or more than one Status bit can be set in the JOB_INFO_2
            structure. This function processes all of the status bits that are 
            set in the DWORD. 

            The meanings of the bits in the Status DWORD are documented in
            the JOB_INFO_2 documentation in the Win32 SDK. The most recent
            status bits are always located in winspool.h.

****************************************************************************/

void MakeJobStatusStr(char *szBuffer, short cchChars, DWORD dwStatus)
{
    DWORD   dwClearBits = 0;
    char    szTmp[MAX_PATH];
    

    szTmp[0] = 0;

    /*
     * Accumulate a status string from the set bits.
     * Terminate when we have processed all of the bits.
     */
    while (dwStatus)
    {
        /* Seperate multiple status phrases with a hyphen */
        if (dwClearBits)
            strncat(szTmp, " - ", MAX_PATH - strlen(szTmp));

        if (JOB_STATUS_SPOOLING & dwStatus)
        {
            strncat(szTmp, "Spooling", MAX_PATH - strlen(szTmp));
            dwClearBits |= JOB_STATUS_SPOOLING;
        }
        else if (JOB_STATUS_PRINTING & dwStatus)
        {
            strncat(szTmp, "Printing", MAX_PATH - strlen(szTmp));
            dwClearBits |= JOB_STATUS_PRINTING;
        }
        else if (JOB_STATUS_DELETING & dwStatus)
        {
            strncat(szTmp, "Deleting", MAX_PATH - strlen(szTmp));
            dwClearBits |= JOB_STATUS_DELETING;
        }
        else if (JOB_STATUS_PAUSED & dwStatus)
        {
            strncat(szTmp, "Paused", MAX_PATH - strlen(szTmp));
            dwClearBits |= JOB_STATUS_PAUSED;
        }
        else if (JOB_STATUS_PRINTED & dwStatus)
        {
            strncat(szTmp, "Printed", MAX_PATH - strlen(szTmp));
            dwClearBits |= JOB_STATUS_PRINTED;
        }
        else if (JOB_STATUS_DELETED & dwStatus)
        {
            strncat(szTmp, "Deleted", MAX_PATH - strlen(szTmp));
            dwClearBits |= JOB_STATUS_DELETED;
        }
        else if (JOB_STATUS_ERROR & dwStatus)
        {
            strncat(szTmp, "Error", MAX_PATH - strlen(szTmp));
            dwClearBits |= JOB_STATUS_ERROR;
        }
        else if (JOB_STATUS_OFFLINE & dwStatus)
        {
            strncat(szTmp, "Offline", MAX_PATH - strlen(szTmp));
            dwClearBits |= JOB_STATUS_OFFLINE;
        }
        else if (JOB_STATUS_PAPEROUT & dwStatus)
        {
            strncat(szTmp, "Paper Out", MAX_PATH - strlen(szTmp));
            dwClearBits |= JOB_STATUS_PAPEROUT;
        }
        else if (JOB_STATUS_BLOCKED_DEVQ & dwStatus)
        {
            strncat(szTmp, "Blocked Device", MAX_PATH - strlen(szTmp));
            dwClearBits |= JOB_STATUS_BLOCKED_DEVQ;
        }
        else if (JOB_STATUS_USER_INTERVENTION & dwStatus)
        {
            strncat(szTmp, "Intervention Required", MAX_PATH - strlen(szTmp));
            dwClearBits |= JOB_STATUS_USER_INTERVENTION;
        }
        else if (JOB_STATUS_RESTART & dwStatus)
        {
            strncat(szTmp, "Restarting", MAX_PATH - strlen(szTmp));
            dwClearBits |= JOB_STATUS_RESTART;
        }
        else 
        {
            /* if we get here, the OS knows more than us. */
            strncat(szTmp, "Unkown", MAX_PATH - strlen(szTmp));
            dwClearBits = dwStatus;
        }

        /* Clear whatever bit we just processed */
        dwStatus = dwStatus & ~dwClearBits;
    }

    lstrcpyn(szBuffer, szTmp, cchChars);
    szBuffer[cchChars-1] = 0;

} /* end of function MakeJobStatus */


/****************************************************************************

    FUNCTION:  MakePrinterStatusStr(char *, short,  DWORD)

    PURPOSE:   Forms a character string description of the status contained
               in the DWORD.
                
    COMMENTS:

            This function prioritizes the status bits of the DWORD and assigns
            only one status string to the pszStr parameter. Note that the 
            bits of the DWORD Status are documented in the PRINTER_INFO_2  
            structure in the Platform SDK(Win32 SDK). The most current status
            bits are always in the Winspool.h header file.

****************************************************************************/

void MakePrinterStatusStr(char *pBuffer, short cchChars, DWORD dwStatus)
{
    char *  pszStr = NULL;
    
    /* Pick which string to use */
    switch(dwStatus)
    {
        case PRINTER_STATUS_PAUSED:
            pszStr = "Paused";
            break;
        case PRINTER_STATUS_OFFLINE:
            pszStr = "Offline";
            break;
        case PRINTER_STATUS_PAPER_OUT:
            pszStr = "Paper Out";
            break;
        case PRINTER_STATUS_PAPER_JAM:
            pszStr = "Paper Jam";
            break;
        case PRINTER_STATUS_PAPER_PROBLEM:
            pszStr = "Paper Problem";
            break;
        case PRINTER_STATUS_ERROR:
            pszStr = "Error";
            break;
        case PRINTER_STATUS_PRINTING:
            pszStr = "Printing";
            break;
        case PRINTER_STATUS_OUTPUT_BIN_FULL:
            pszStr = "Output Bin Full";
            break;
        case PRINTER_STATUS_USER_INTERVENTION:
            pszStr = "User Intervention Required";
            break;
        case PRINTER_STATUS_MANUAL_FEED:
            pszStr = "Manual Feed";
            break;
        case PRINTER_STATUS_IO_ACTIVE:
            pszStr = "IO Active";
            break;
        case PRINTER_STATUS_BUSY:
            pszStr = "Busy";
            break;
        case PRINTER_STATUS_NOT_AVAILABLE:
            pszStr = "Not Available";
            break;
        case PRINTER_STATUS_PENDING_DELETION:
            pszStr = "Deleting";
            break;
        case PRINTER_STATUS_WAITING:
            pszStr = "Waiting";
            break;
        case PRINTER_STATUS_PROCESSING:
            pszStr = "Processing";
            break;
        case PRINTER_STATUS_INITIALIZING:
            pszStr = "Initializing";
            break;
        case PRINTER_STATUS_WARMING_UP:
            pszStr = "Warming Up";
            break;
        case PRINTER_STATUS_TONER_LOW:
            pszStr = "Low Toner";
            break;
        case PRINTER_STATUS_NO_TONER:
            pszStr = "No Toner";
            break;
        case PRINTER_STATUS_PAGE_PUNT:
            pszStr = "Page Punt";
            break;
        case PRINTER_STATUS_OUT_OF_MEMORY:
            pszStr = "Out of Memory";
            break;
        case PRINTER_STATUS_DOOR_OPEN:
            pszStr = "Door Open";
            break;
        case PRINTER_STATUS_SERVER_UNKNOWN:
            pszStr = "Unknown Server";
            break;
        case PRINTER_STATUS_POWER_SAVE:
            pszStr = "Power Save";
            break;
        default:
            /* The OS knows more than us */
            pszStr = "Unkown Status";
            break;
    }

    /* Copy the string into the buffer */
    lstrcpyn(pBuffer, pszStr, cchChars);
    pBuffer[cchChars-1] = 0;

} /* end of function MakePrinterStatusStr */


/****************************************************************************

    FUNCTION:  RefreshFromNotification(HWND, QUEUEDATA *, PRINTER_NOTIFY_INFO*)

    PURPOSE:   Updates the data in the Printer Queue data structure by applying
               the changes to specific fields of the data structures as 
               specified in the PRINT_NOTIFY_INFO data structure.
                
    COMMENTS:

            PRINTER_NOTIFY_INFO contains changes on a per structure field
            basis for both the JOB_INFO_* structures and the PRINTER_INFO_*
            structures. UpdateQueue uses this list of changes to update the 
            data saved by the applications custom printer queue structure. 
            SetQueListContents uses the updated data structure to propagate the
            changes to the ListView control. UpdateWindowTitle rewrites the 
            entire Window caption with data from the updated data structure.

****************************************************************************/

BOOL RefreshFromNotification(HWND hWnd, QUEUEDATA *pQueue, PRINTER_NOTIFY_INFO *pNotification)
{

    if (pNotification)
    {       
        /* Update Our Data */
        UpdateQueue(pQueue, pNotification);
        
        /* update the list boxes */
        SetQueListContents(g_hWndJobList, pQueue);
        
        /* Always Update the Window Title */
        UpdateWindowTitle(hWnd, pQueue);

    }
    
    return TRUE;

} /* end of function RefreshFromNotification */



/****************************************************************************

    FUNCTION:  UpdateWindowTitle(HWND , QUEUEDATA *)

    PURPOSE:   Forms a new Window Caption containing the status of the print
               queue and sets the Window Caption.
                
    COMMENTS:

            This function concatenates the title of the application with the
            name of the printer and the current state of the printer and sets
            the resulting string as the new caption in the Window's Title bar.


****************************************************************************/

void UpdateWindowTitle(HWND hWnd, QUEUEDATA *pQueue)
{
    char        WindowTitle[200];
    PRINTERDATA *pPd = &pQueue->Printer;

    /* Start with application title */
    lstrcpyn(WindowTitle, g_szTitle, 200);
    
    /* Append printer queue information */
    strncat(WindowTitle, ": ", 200-strlen(WindowTitle));
    
    if (pPd->pszPrinterName && lstrlen(pPd->pszPrinterName) > 0)
    {
        lstrcat(WindowTitle, pPd->pszPrinterName);
    }
    else if (pPd->pszServerName && pPd->pszShareName)
    {
        strncat(WindowTitle, pPd->pszServerName, 200-strlen(WindowTitle));
        strncat(WindowTitle, "\\", 200-strlen(WindowTitle));
        strncat(WindowTitle, pPd->pszShareName, 200-strlen(WindowTitle));
    }
    else
    {
        strncat(WindowTitle, "Unknown", 200-strlen(WindowTitle));
    }
    
    /* append status of the printer queue */
    if (pPd->dwStatus)
    {
        strncat(WindowTitle, " - ", 200-strlen(WindowTitle));
        
        /* insert the printer status after the "-" */
        MakePrinterStatusStr(&WindowTitle[lstrlen(WindowTitle)], 
            (short)(sizeof(WindowTitle) - lstrlen(WindowTitle)),
            pPd->dwStatus);
    }
    
    SetWindowText(hWnd, WindowTitle);
            

} /* end of function UpdateWindowTitle */


/****************************************************************************

    FUNCTION:  UpdateQueue(QUEUEDATA *, PRINTER_NOTIFY_INFO *)

    PURPOSE:   Loops over the changes to printer queue data contained in the
               PRINTER_NOTIFY_INFO pointer and applies them to the accumulated
               queue data contained in the QUEUEDATA pointer.

    COMMENTS:

            A change contained in the notification list can be either Job data
            or Printer data. UpdateQueue first tries to find the change in the
            Job data. If it fails it then tries to apply it to the Printer data.
            This approach was taken because we are far more likely to receive 
            more frequent changes to job data then printer data.

****************************************************************************/

BOOL UpdateQueue(QUEUEDATA *pQueueData, PRINTER_NOTIFY_INFO *pPNI)
{
    unsigned int        i;

    for (i=0; i < pPNI->Count; i++)
    {
        if (!UpdateJobData(pQueueData, &pPNI->aData[i]))
            UpdatePrinterData(pQueueData, &pPNI->aData[i]);
    }

    return TRUE;
}


/****************************************************************************

    FUNCTION:  GetQueue(QUEUEDATA *)

    PURPOSE:   Used to initially, periodically, or upon user request, 
               completely fill in the data for the printer queue. 

    COMMENTS:

            If Printer Change Notifications are not used this function is 
            called by the polling thread each time it wakes up to refresh the
            data for the Printer Queue.

****************************************************************************/

BOOL GetQueue(QUEUEDATA *pQueueData)
{
    DWORD               cByteNeeded, 
                        cByteUsed, 
                        i;
    int                 nReturned=0;
    JOB_INFO_2          *pJobStorage = NULL;
    PRINTER_INFO_2      *pPrinterInfo = NULL;
    HANDLE              hPrinter = pQueueData->Printer.hPrinter;


    if (hPrinter)
    {
        /* Get the buffer size needed */
        if (!GetPrinter(hPrinter, 2, NULL, 0, &cByteNeeded))
        {
            if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
                goto Fail;
        }

        pPrinterInfo = (PRINTER_INFO_2 *)malloc(cByteNeeded);
        if (!(pPrinterInfo))
            /* failure to allocate memory */
            goto Fail;
        
        /* get the printer info */
        if (!GetPrinter(hPrinter, 2, (LPBYTE)pPrinterInfo, cByteNeeded, &cByteUsed))
        {
            /* failure to access the printer */
            free(pPrinterInfo);
            pPrinterInfo = NULL;
            goto Fail;
        } 
        
        /* Get job storage space */
        if (!EnumJobs(hPrinter, 
                 0, 
                 (pPrinterInfo)->cJobs, 
                 2, 
                 NULL, 
                 0,
                 (LPDWORD)&cByteNeeded,
                 (LPDWORD)&nReturned))
        {
            if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
                goto Fail;
        }

        pJobStorage = (JOB_INFO_2 *)malloc(cByteNeeded);
        if (!pJobStorage)
            /* failure to allocate Job storage space */
            goto Fail;
        
        ZeroMemory(pJobStorage, cByteNeeded);

        /* get the list of jobs */
        if (!EnumJobs(hPrinter, 
                 0, 
                 (pPrinterInfo)->cJobs, 
                 2, 
                 (LPBYTE)pJobStorage, 
                 cByteNeeded,
                 (LPDWORD)&cByteUsed,
                 (LPDWORD)&nReturned))
        {
            goto Fail;
        }

        /* Update the count of jobs
         * It is possible for cJobs != nReturned after this sequence so
         * we reset the printer data structure to only reflect what we
         * actually retrieved this time around
         */
        (pPrinterInfo)->cJobs = nReturned;

    }
    else
        goto Fail;

    SetPrinterQueueData(pQueueData, pPrinterInfo);

    /* Dump the existing data */
    FreeJobs(pQueueData);
    
    /* Fill in the Printer Queue with the jobs we retrieved */
    for (i = 0; i < pPrinterInfo->cJobs; i++)
        AddJobData(pQueueData, &pJobStorage[i]);
    
    free(pJobStorage);
    free(pPrinterInfo);
    
    return TRUE;

Fail:

    free(pJobStorage);
    free(pPrinterInfo);
    return FALSE;

} /* end of function GetQueue */

/* end of source file PrintJob.c */

