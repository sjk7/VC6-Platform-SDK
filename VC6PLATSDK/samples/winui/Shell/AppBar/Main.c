//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993 - 2000  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     main.c
//
//  PURPOSE:    Startup functions and error handling
//
//  PLATFORMS:  Windows 95, Windows 98, Windows 2000, Windows NT 4.0
//
//  FUNCTIONS:
//      WinMain()           - Entry point function
//      DoMain()            - Main message loop
//      InitApplication()   - Register window classes
//      InitInstance()      - Create and display main windows
//      ErrorHandlerEx()    - Generic error handler code
//      DebugMsg()          - Prints formatted output to the debugger
//
//  COMMENTS:
//
//

#include <windows.h>
#include <stdio.h>
#include "globals.h"
#include "resource.h"


//////////////////////////////////////////////////////////////////////////////
// Prototypes

int DoMain(void);
VERSION DetermineVersion(void);

//////////////////////////////////////////////////////////////////////////////
// Global Variables

VERSION version;
HINSTANCE g_hInstance = NULL;


//
//  FUNCTION:   WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//
//  PURPOSE:    Entry point function, initializes the application, instance,
//              and then launches the message loop.
//
//  PARAMETERS:
//      hInstance     - handle that uniquely identifies this instance of the
//                      application
//      hPrevInstance - always zero in Win32
//      lpszCmdLine   - any command line arguements pass to the program
//      nCmdShow      - the state which the application shows itself on
//                      startup
//
//  RETURN VALUE:
//      (int) Returns the value from PostQuitMessage().
//
//  COMMENTS:
//

int PASCAL WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine,
                     int nCmdShow)
{
    int iResult;

    // Find out what OS we're running on in case we have to call any platform
    // specific code.
    version = DetermineVersion();

    if (InitApplication(hInstance))
       if (InitInstance(hInstance, SW_SHOWDEFAULT))
           iResult = DoMain();

    return iResult;
}


//
//  FUNCTION:   DoMain(void) 
//
//  PURPOSE:    This is the main message loop for the application.  It
//              retrieves messages from the application's message queue and
//              dispatches the messages to the appropriate window procedure.
//
//  PARAMETERS:
//      none
//
//  RETURN VALUE:
//      (int) Returns the value passed to PostQuitMessage().
//
//  COMMENTS:
//

int DoMain( void )
{
    MSG msg;
    
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);   // Translates virtual key codes
        DispatchMessage(&msg);    // Dispatches message to window procedure 
    }

    return ((int) msg.wParam);
}


//
//  FUNCTION:   InitApplication(HINSTANCE)
//
//  PURPOSE:    Registers the application's window class(es).
//
//  PARAMETERS: 
//      hInstance   - handle that uniquely identifies this application instance
//
//  RETURN VALUE:
//      (BOOL) Returns TRUE if the window classes are registered successfully
//             Returns FALSE otherwise
//
//  COMMENTS:
//

#define DEFBKGDCOLOR (COLOR_WINDOW + 1)
BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASSEX  wcx;

    // The window class is not registered yet, so we have to fill a
    // window class structure with parameters that describe the
    // window class.
    wcx.cbSize        = sizeof(WNDCLASSEX);
    wcx.style         = 0;
    wcx.lpfnWndProc   = MainWndProc;     
    wcx.cbClsExtra    = 0;             
    wcx.cbWndExtra    = sizeof(LPVOID);             
    wcx.hInstance     = hInstance;     
    wcx.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
    wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)DEFBKGDCOLOR;
    wcx.lpszMenuName  = NULL;
    wcx.lpszClassName = TEXT("MSSampleAppbar");  
    wcx.hIconSm       = LoadImage(hInstance,        
                                  MAKEINTRESOURCE(IDI_APPICON),
                                  IMAGE_ICON,
                                  16, 16,
                                  0);

    // Attempt to register the class first with the WNDCLASSEX structure
    // and if that doesn't work try just the WNDCLASS for NT and Win32s.
    if (!RegisterClassEx(&wcx))
    {   
        if (!RegisterClass((LPWNDCLASS)&wcx.style))
        {
            ErrorHandler();
            return (FALSE);
        }
    }        

    return (TRUE);
}


//
//  FUNCTION:   InitInstance(HINSTANCE, int)
//
//  PURPOSE:    Creates and displays the application's initial window(s).
//
//  PARAMETERS:
//      hInstance   - handle which uniquely identifies this instance
//      nCmdShow    - determines the state which the window should be initially
//                    shown in
//
//  RETURN VALUE:
//      (BOOL) Returns TRUE if the window(s) are created successfully.
//             Returns FALSE otherwise.
//
//  COMMENTS:
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hwnd;                       // temporary window handle
    BOOL bStatus = FALSE;            // holds return status for function

    // Save the instance handle in global variable, which will be used in
    // many subsequent calls from this application to Windows
    g_hInstance = hInstance;

    // Create a main window for this application instance
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_TOOLWINDOW,
                          TEXT("MSSampleAppbar"),                 
                          TEXT("Win32 Sample AppBar"),    
                          WS_POPUP | WS_THICKFRAME | WS_CLIPCHILDREN,
                          CW_USEDEFAULT,                  
                          CW_USEDEFAULT,                  
                          400,                  
                          200,                  
                          NULL,                           
                          NULL,                           
                          hInstance,                      
                          NULL                            
                         );

    // If the window was successfully created, make the window visible,
    // update its client area, and return "success".  If the window
    // was not created, return "failure"
    if (hwnd)
    {
        ShowWindow(hwnd, nCmdShow); // Set to visible & paint non-client area
        UpdateWindow(hwnd);         // Tell window to paint client area

        bStatus = TRUE;             // Indicate success, default is failure
    }
    else
    {
        ErrorHandler();
    }

    return bStatus;                  // Return status code
}


//
//  FUNCTION:   ErrorHandlerEx(WORD, LPSTR)
//
//  PURPOSE:    Calls GetLastError() and uses FormatMessage() to display the
//              textual information of the error code along with the file 
//              and line number.
//
//  PARAMETERS:
//      wLine    - line number where the error occured   
//      lpszFile - file where the error occured
//
//  RETURN VALUE:
//      none
//
//  COMMENTS:
//      This function has a macro ErrorHandler() which handles filling in
//      the line number and file name where the error occured.  ErrorHandler()
//      is always used instead of calling this function directly.
//

void ErrorHandlerEx( INT wLine, LPSTR lpszFile )
{
    LPVOID lpvMessage;
    DWORD  dwError;
    TCHAR  szBuffer[256];

    // The the text of the error message
    dwError = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                            FORMAT_MESSAGE_FROM_SYSTEM, 
                            NULL, 
                            GetLastError(), 
                            MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), 
                            (LPTSTR)&lpvMessage, 
                            0, 
                            NULL);

    // Check to see if an error occured calling FormatMessage()
    if (0 == dwError)
    {
        wsprintf(szBuffer, TEXT("An error occured calling FormatMessage().")
                 TEXT("Error Code %d"), GetLastError());
        MessageBox(NULL, szBuffer, TEXT("Generic"), MB_ICONSTOP | 
                   MB_ICONEXCLAMATION);
        return;
    }

    // Display the error message
    wsprintf(szBuffer, TEXT("Generic, Line=%d, File=%s"), wLine, lpszFile);
    MessageBox(NULL, lpvMessage, szBuffer, MB_ICONEXCLAMATION | MB_OK);

    return;
}



//
//  FUNCTION:   DetermineVersion()
//
//  PURPOSE:    Returns whether the program is running on WinNT, Win32s,
//              or Win95.
//
//  PARAMETERS:
//      none
//
//  RETURN VALUE:
//      (VERSION) Returns WINNT, WIN32S, or WIN95
//
//  COMMENTS:
//

VERSION DetermineVersion(void)
{
    DWORD dwVersion;

    dwVersion = GetVersion();
    if (dwVersion < 0x80000000)
        return (WINNT);
    else
        if (LOBYTE(LOWORD(dwVersion)) < 4)
            return (WIN32S);
        else
            return (WIN95);
}


//
//  FUNCTION:   DebugMsg(const TCHAR, ...) 
//
//  PURPOSE:    Prints formatted output to the debugger ala printf.
//
//  PARAMETERS:
//      *pFmt   - string with the necessary formatting codes
//      ...     - arguments being embedded in the pFmt string.
//
//  RETURN VALUE:
//      Returns number of bytes written or -1 if buffer is too small
//
//  COMMENTS:
//      Calling this function should be just like calling printf.  The only
//      difference is this function outputs to the debugger instead of STDOUT.
//

int DebugMsg( const TCHAR *pFmt, ...)
{
    int i;
    const int iMsgSize = 512;
    va_list pArgs;
    char szMsg[512];

    // outputs formatted string to debugger
    // returns count of bytes written or -1 if buffer size is too small

    va_start( pArgs, pFmt );

    #ifdef UNICODE
        i = _vsnwprintf(szMsg, iMsgSize+1, pFmt, pArgs);
    #else
        i = _vsnprintf(szMsg, iMsgSize+1, pFmt, pArgs);
    #endif

    va_end( pArgs );

    OutputDebugString( szMsg );

    return( i );
}
