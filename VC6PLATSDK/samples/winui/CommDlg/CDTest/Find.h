/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright 1993 - 2000 Microsoft Corp.
*       All rights not expressly granted in the SDK license are reserved.
\******************************************************************************/
BOOL bDoFindDlg ;

HHOOK hHook ;

LRESULT CALLBACK lpfnFilterProc(int, WPARAM, LPARAM) ;


void DoFindDialog(HWND) ;
INT_PTR APIENTRY FindProc(HWND, UINT, WPARAM, LPARAM) ;



#define ID_STRUCTSIZEFT             111
#define ID_HWNDOWNERFT              112
#define ID_FLAGSFT                  113
#define ID_FINDWHATFT               114
#define ID_REPLACEWITHFT            115
#define ID_FINDWHATLENFT            116
#define ID_REPLACEWITHLENFT         117
#define ID_CUSTDATAFT               118
#define ID_HOOKFT                   119
#define ID_TEMPLATEFT               120
#define ID_ERRORFT                  123
#define ID_RETURNFT                 124


#define ID_FINDDIALOG               600
#define ID_HINSTANCEFT              125
#define ID_RESETFIND                127
#define ID_FLAGSMSG                 128
#define ID_FRNULLSTRUCT             601
#define ID_PRELOADEDFIND            602
#define ID_MULTITHREADFINDREP       603


#define ID_FINDLEFT                 604
#define ID_FINDRIGHT                605
#define ID_DEFSTRINGS               101
