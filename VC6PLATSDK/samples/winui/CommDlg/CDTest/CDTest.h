/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright 1993 - 2000 Microsoft Corp.
*       All rights not expressly granted in the SDK license are reserved.
\******************************************************************************/
#define UMSG_DECREMENTDLGCOUNT (WM_USER+1)



HINSTANCE hInst;

BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
LRESULT APIENTRY MainWndProc(HWND, UINT, WPARAM, LPARAM);
void HandleTheCommand(HWND, WPARAM, LPARAM) ;
INT_PTR APIENTRY AboutProc(HWND, UINT, WPARAM, LPARAM) ;

#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))

TCHAR szTemp[100] ;

TCHAR szShortFilter[5] ;
TCHAR szLongFilter[5] ;
TCHAR szPointerFilter[5] ;

#define IDM_COLOR   100
#define IDM_FONT    101
#define IDM_FIND    102
#define IDM_TITLE   103
#define IDM_OPEN    104
#define IDM_SAVE    105
#define IDM_PRINT   106
#define IDM_REPLACE 107
#define IDM_EXIT    108
#define IDM_HEXMODE 200
#define IDM_DECIMALMODE 201
#define IDM_MULTITHREAD2 300
#define IDM_ABOUT   301


UINT nFindMsg ;
UINT nOpenShareVMsg ;
UINT nHelpMessage ;
