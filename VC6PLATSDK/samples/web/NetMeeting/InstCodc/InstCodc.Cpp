//****************************************************************************
//  Module:      INSTCODC.EXE
//  File:        INSTCODC.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1999 - 2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include <stdio.h>
#include <stdarg.h>
#include <tchar.h>

#include <windows.h>
#include <windowsx.h>
#include <objbase.h>
#include <initguid.h>

#include "resource.h"
#include "codecs.h"


typedef enum {AUDIOCODEC, NONE} CODECTYPE;

//*******************
//GLOBALS
//*******************
const int           MID_SZ      = 128;
CODECTYPE           gtCodec     = AUDIOCODEC;       // Global depicting type of codec being displayed, installed,
                                                    // removed, or reordered.

HINSTANCE           ghInstance  = NULL;

WAVEFORMATEX*       gpWFmt      = NULL;             //Structures used for adding and removing codecs
AUDCAP_INFO         gWInfo;

//CAP_INFO lists 
AUDCAP_INFO_LIST*   gpsAudCapInfoList       = NULL; // Contains a list of the installed
                                                    // audio codecs and their properties.
int*                gpnAudCapOrderedIndex   = NULL; // Contains, in installed order, indexes
                                                    // of the structures in the AUDCAP_INFO_LIST.

 
//*******************
//GLOBAL Interfaces
//*******************
static IInstallAudioCodecs* pAudio          = NULL;
 
//*******************
//MAIN UI FUNCTIONS
//*******************

LRESULT CALLBACK MainUIProc (HWND hwnd, UINT message, UINT wParam, LONG lParam);
LRESULT CALLBACK ReorderUIProc (HWND hwnd, UINT message, UINT wParam, LONG lParam);
BOOL InitAppInstance (HINSTANCE hInstance);
void DeinitAppInstance(HINSTANCE hInstance);

//*******************
//Misc. Functions
//*******************

void LoadInstalledCodecs(void);
void IndexInstalledCodecs(void);
void UpdateCapInfoListsFromIndex(void);
void DlgDisplayInstalledCodecs(HWND);
void DebugTextOut(TCHAR* ptszFormat, ... );


//*******************
//helper function  converts HRESULT to error message
//*******************

TCHAR gszHRError[MID_SZ];
inline void HRErrorToString(HRESULT hr)
{
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,(DWORD)hr,LANG_SYSTEM_DEFAULT,gszHRError,MID_SZ,NULL);
}




//****************************************************************************
//
//    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
//
//    PURPOSE: calls initialization function
//
//    COMMENTS:
//
//        Windows recognizes this function by name as the initial entry point 
//        for the program.  This function calls the application initialization 
//        routine.  
//
//****************************************************************************


int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{ 
    BOOL fProcessed = FALSE;
    
    fProcessed = InitAppInstance(hInstance);
    if (fProcessed == FALSE)
    {
        DebugTextOut(TEXT("InitAppInstance failed\n"));
    }
    
    DeinitAppInstance(hInstance);
    return fProcessed;
}

//****************************************************************************
//
// BOOL InitAppInstance (HINSTANCE hInstance)
//
// This function initializes this instance of the application.
//
//****************************************************************************

BOOL InitAppInstance (HINSTANCE hInstance)
{
    WNDCLASS    wc;
    BYTE        gWFmtEx[] = {0x40,0x01};

    ghInstance = hInstance;

    //Register WNDCLASS for the app.

    //This class enables the main dialog box to have additional properties 
    //such as an icon.
    wc.style            = CS_DBLCLKS | CS_SAVEBITS | CS_BYTEALIGNWINDOW;
    wc.lpfnWndProc      = DefDlgProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = DLGWINDOWEXTRA;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INSTCODC));
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = TEXT("CodecInstClass");

    if (!RegisterClass(&wc))
    {
        DebugTextOut(TEXT("Register class failed!\n"));
        return FALSE;
    }

    
    //Setup audio codec structures
    //This particular codec is: GSM 6.10, 8,000 Hz, Mono
    gpWFmt = (WAVEFORMATEX *)LocalAlloc(LPTR,sizeof(WAVEFORMATEX)+sizeof(gWFmtEx));
    if (NULL == gpWFmt)
    {
        DebugTextOut(TEXT("Out of memory\n"));
        return FALSE;
    }

    gpWFmt->wFormatTag      = 49;
    gpWFmt->nChannels       = 1;
    gpWFmt->nSamplesPerSec  = 8000;
    gpWFmt->nAvgBytesPerSec = 1625;
    gpWFmt->nBlockAlign     = 65;
    gpWFmt->wBitsPerSample  = 0;
    gpWFmt->cbSize          = sizeof(gWFmtEx);

    CopyMemory((gpWFmt + 1), gWFmtEx, gpWFmt->cbSize);

    ZeroMemory(&gWInfo,sizeof(AUDCAP_INFO));
    gWInfo.wFormatTag = 49;
    gWInfo.uAvgBitrate = 13000;
    gWInfo.wCPUUtilizationEncode = 50; //arbitrary
    gWInfo.wCPUUtilizationDecode = 20; //artitrary
    gWInfo.bSendEnabled = 1;
    gWInfo.bRecvEnabled = 1;
    
    //Setup COM support
    if (FAILED(CoInitialize(NULL)))
    {
        DebugTextOut(TEXT("CoInitialize failed\n"));
        return FALSE;
    }

    //Application is a Modal Dialog.  
    return DialogBox(hInstance,MAKEINTRESOURCE(IDD_MAINUI),0,(DLGPROC)MainUIProc);
}

//****************************************************************************
//
// void DeinitAppInstance (HINSTANCE hInstance)
//
// This function initializes this instance of the application.
//
//****************************************************************************

void DeinitAppInstance(HINSTANCE hInstance)
{
    //End COM support
    CoUninitialize();
    
    //free the allocated memory
    LocalFree(gpWFmt);
    gpWFmt = NULL;
}

//****************************************************************************
//
// BOOL MainUI_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
//
// This function is called when the Main Dialog initializes.  It sets up 
// the initial interface pointers and updates the dialog accordingly
//
//****************************************************************************

BOOL MainUI_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    HRESULT hr  = S_OK;
    TCHAR   szString[MID_SZ];

    gtCodec = NONE;

    //Get an interface to the audio codec methods
    hr = CoCreateInstance(  CLSID_InstallCodecs,
                            NULL,
                            CLSCTX_INPROC_SERVER,
                            IID_IInstallAudioCodecs,
                            (void **) &pAudio);
    if (FAILED(hr))
    {
        pAudio = NULL;
        HRErrorToString(hr);
        LoadString(ghInstance,IDS_GETIAUDIO,szString,MID_SZ);
        MessageBox(NULL,gszHRError,szString,MB_OK);
    }
    else
    {
        gtCodec = AUDIOCODEC;
    }


    // If no interfaces were available, disable everything.
    if (gtCodec == NONE)
    {
        EnableWindow(GetDlgItem(hwnd,IDC_INSTALL),FALSE);
        EnableWindow(GetDlgItem(hwnd,IDC_UNINSTALL),FALSE);
        EnableWindow(GetDlgItem(hwnd,IDC_REORDER),FALSE);
        EnableMenuItem(GetMenu(hwnd),0,MF_BYPOSITION|MF_GRAYED);
        return TRUE;
    }

    //Load installed codec formats
    LoadInstalledCodecs();

    //display codecs
    DlgDisplayInstalledCodecs(hwnd);
    return TRUE;
}

//****************************************************************************
//
// void MainUI_OnDestroy(HWND hwnd)
//
//****************************************************************************

void MainUI_OnDestroy(HWND hwnd)
{
    HRESULT hr = S_OK;

    if (NULL == pAudio)
    {
        DebugTextOut(TEXT("Application not initialized!\n"));
        return;
    }
    
    // Free CapInfo structures
    if (NULL != gpsAudCapInfoList)
    {
        hr = pAudio->FreeBuffer(gpsAudCapInfoList);
        if (FAILED(hr))
        {
            // Simply log the failure, and continue. We want to continue and clean up
            DebugTextOut(TEXT("pAudio->FreeBuffer failed, hr = 0x%08p"), hr);
        }
    }

    // Release the interfaces
    if (NULL != pAudio)
    {
        pAudio->Release();
        pAudio = NULL;
    }

    // Free CapInfoIndexs
    LocalFree(gpnAudCapOrderedIndex);
    gpnAudCapOrderedIndex = NULL;
}

//****************************************************************************
//
// void MainUI_OnClose(HWND hwnd)
//
//****************************************************************************

void MainUI_OnClose(HWND hwnd)
{
    EndDialog(hwnd,0);
}

//****************************************************************************
//
// void MainUI_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
//
//****************************************************************************

void MainUI_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    TCHAR szString[MID_SZ];
    TCHAR szString2[MID_SZ];

    if (NULL == pAudio)
    {
        DebugTextOut(TEXT("Application not initialized!\n"));
        return;
    }

    switch(id)
    {
        //Install the codec
        case IDC_INSTALL:
        {
            if (gtCodec==AUDIOCODEC)
            {
                if (FAILED(pAudio->AddACMFormat(gpWFmt,&gWInfo)))
                {
                    LoadString(ghInstance,IDS_IAFMT,szString,MID_SZ);
                    LoadString(ghInstance,IDS_AAFMT,szString2,MID_SZ);
                    MessageBox(hwnd,szString,szString2,MB_OK|MB_ICONEXCLAMATION);
                }
            }
            LoadInstalledCodecs();
            break;
        }
        
        // Uninstall the codec
        case IDC_UNINSTALL:
        {
            if (gtCodec==AUDIOCODEC)
            {
                if (FAILED(pAudio->RemoveACMFormat(gpWFmt)))
                {
                    LoadString(ghInstance,IDS_UAFMT,szString,MID_SZ);
                    LoadString(ghInstance,IDS_RAFMT,szString2,MID_SZ);
                    MessageBox(hwnd,szString,szString2,MB_OK|MB_ICONEXCLAMATION);
                }
            }
        
            LoadInstalledCodecs();
            break;
        }

        // Reorder the codecs
        case IDC_REORDER:
        {
            DialogBox(ghInstance,MAKEINTRESOURCE(IDD_REORDER),hwnd,(DLGPROC)ReorderUIProc);
            break;
        } 
    }

    DlgDisplayInstalledCodecs(hwnd);
}

//****************************************************************************
//
// LRESULT CALLBACK MainUIProc (HWND hwnd, UINT message, UINT wParam, LONG lParam)
//
//****************************************************************************

LRESULT CALLBACK MainUIProc (HWND hwnd, UINT message, UINT wParam, LONG lParam)
{

    LRESULT fProcessed=TRUE;

    switch(message)
    {
        HANDLE_MSG(hwnd,WM_INITDIALOG,MainUI_OnInitDialog);
        HANDLE_MSG(hwnd,WM_CLOSE,MainUI_OnClose);
        HANDLE_MSG(hwnd,WM_DESTROY,MainUI_OnDestroy);
        HANDLE_MSG(hwnd,WM_COMMAND,MainUI_OnCommand);
        
    default:
        fProcessed=FALSE;
        break;
    }
    return (fProcessed);
}

//****************************************************************************
//
// BOOL ReorderUI_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
//
//****************************************************************************

BOOL ReorderUI_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    DlgDisplayInstalledCodecs(hwnd);
    return TRUE;
}

//****************************************************************************
//
// void ReorderUI_OnDestroy(HWND hwnd)
//
//****************************************************************************

void ReorderUI_OnDestroy(HWND hwnd)
{
    EndDialog(hwnd,TRUE);
}

//****************************************************************************
//
// void ReorderUI_OnClose(HWND hwnd)
//
//****************************************************************************

void ReorderUI_OnClose(HWND hwnd)
{
    IndexInstalledCodecs();
    ReorderUI_OnDestroy(hwnd);
}

//****************************************************************************
//
// void ReorderUI_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
//
//****************************************************************************

void ReorderUI_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    HWND    hListBox    = NULL;
    HRESULT hr          = S_OK;
    int     tmp         = 0;
    int     index       = 0;

    switch(id)
    {
        // Move the selected codec up in the list box, and update the CapInfoIndex
        case IDC_UP:
        {
            if (NULL == gpsAudCapInfoList)
            {
                DebugTextOut(TEXT("gpsAudCapInfoList not initialized.\n"));
                return;
            }

            if (NULL == gpnAudCapOrderedIndex)
            {
                DebugTextOut(TEXT("gpnAudCapOrderedIndex not initialized.\n"));
                return;
            }
            
            hListBox = GetDlgItem(hwnd,IDC_LBINSTALLEDCODECS);
            if (NULL == hListBox)
            {
                DebugTextOut(TEXT("GetDlgItem failed! Error = 0x%08p.\n"), HRESULT_FROM_WIN32(GetLastError()));
                return;
            }

            //get text of current selection
            index = SendMessage(hListBox,LB_GETCURSEL,0,0);

            //if wasn't able to get selection
            if (index==0 || index==LB_ERR)
                return;

            SendMessage(hListBox,LB_DELETESTRING,index,0);
            SendMessage(hListBox,LB_INSERTSTRING,index-1,(LPARAM)(LPCSTR)gpsAudCapInfoList->aFormats[gpnAudCapOrderedIndex[index]].szFormat);

            tmp = gpnAudCapOrderedIndex[index-1];
            gpnAudCapOrderedIndex[index-1] = gpnAudCapOrderedIndex[index];
            gpnAudCapOrderedIndex[index] = tmp;
            
            SendMessage(hListBox,LB_SETCURSEL,index-1,0);
            break;
        }

        // Move the selected codec down in the list box, and update the CapInfoIndex
        case IDC_DOWN:
        {
            if (NULL == gpsAudCapInfoList)
            {
                DebugTextOut(TEXT("gpsAudCapInfoList not initialized.\n"));
                return;
            }

            hListBox = GetDlgItem(hwnd,IDC_LBINSTALLEDCODECS);
            if (NULL == hListBox)
            {
                DebugTextOut(TEXT("GetDlgItem failed! Error = 0x%08p.\n"), HRESULT_FROM_WIN32(GetLastError()));
                return;
            }

            //get text of current selection
            index = SendMessage(hListBox,LB_GETCURSEL,0,0);

            if (    (index == (int)(gpsAudCapInfoList->cFormats - 1)) ||
                    (index == (int)LB_ERR))
                return;

            SendMessage(hListBox,LB_DELETESTRING,index,0);
            SendMessage(hListBox,LB_INSERTSTRING,index+1,(LPARAM)(LPCSTR)gpsAudCapInfoList->aFormats[gpnAudCapOrderedIndex[index]].szFormat);

            tmp = gpnAudCapOrderedIndex[index+1];
            gpnAudCapOrderedIndex[index+1] = gpnAudCapOrderedIndex[index];
            gpnAudCapOrderedIndex[index] = tmp;

            SendMessage(hListBox,LB_SETCURSEL,index+1,0);
            break;
        }


        // Update the CapInfoList from the CapInfoIndex
        // Call ReorderFormats to reorder the codecs in NetMtg
        // Reload the CapInfoList w/ the new info.
        case IDC_OK:
        {
            UpdateCapInfoListsFromIndex();

            if (NULL == pAudio)
            {
                DebugTextOut(TEXT("pAudio is NULL\n"));
                return;
            }

            hr = pAudio->ReorderFormats(gpsAudCapInfoList);
            if (FAILED(hr))
            {
                DebugTextOut(TEXT("pAudio->ReorderFormats failed. hr = 0x%08p\n"), hr);
                return;
            }

            //refresh display
            LoadInstalledCodecs();
            EndDialog(hwnd,TRUE);
            break;
        }

        // Cancel changes by reinitializing the CapInfoIndexs from the 
        // CapInfoLists and ending the dialog.
        case IDC_CANCEL:
        {
            IndexInstalledCodecs();
            EndDialog(hwnd,TRUE);
            break;
        }
    }
}

//****************************************************************************
//
// LRESULT CALLBACK ReorderUIProc (HWND hwnd, UINT message, UINT wParam, LONG lParam)
//
//****************************************************************************

LRESULT CALLBACK ReorderUIProc (HWND hwnd, UINT message, UINT wParam, LONG lParam)
{
    LRESULT fProcessed=TRUE;
    
    switch(message)
    {
        HANDLE_MSG(hwnd,WM_INITDIALOG,ReorderUI_OnInitDialog);
        HANDLE_MSG(hwnd,WM_CLOSE,ReorderUI_OnClose);
        HANDLE_MSG(hwnd,WM_DESTROY,ReorderUI_OnDestroy);
        HANDLE_MSG(hwnd,WM_COMMAND,ReorderUI_OnCommand);

    default:
        fProcessed=FALSE;
        break;
    }
    return (fProcessed);
}

//****************************************************************************
//
// void LoadInstalledCodecs(void)
//
// Loads a list of the installed codecs w/ their properties.
//
//****************************************************************************

void LoadInstalledCodecs(void)
{
    HRESULT hr = S_OK;

    // Make sure that we have an IInstallAudioCodecs*
    if (NULL == pAudio)
    {
        DebugTextOut(TEXT("pAudio is NULL\n"));
        return;
    }
    
    //free any existing info
    if (gtCodec==AUDIOCODEC)
    {
        if (NULL != gpsAudCapInfoList)
        {
            hr = pAudio->FreeBuffer(gpsAudCapInfoList);
            if (FAILED(hr))
            {
                DebugTextOut(TEXT("pAudio->FreeBuffer failed. hr = 0x%08p\n"), hr);
                return;
            }
        }
    
        //Get Installed Audio Codecs
        hr = pAudio->EnumFormats(&gpsAudCapInfoList);
        if (FAILED(hr))
        {
            DebugTextOut(TEXT("pAudio->EnumFormats failed. hr = 0x%08p\n"), hr);
            gpsAudCapInfoList=NULL;
        }
        else
        {
            LocalFree(gpnAudCapOrderedIndex);
            
            gpnAudCapOrderedIndex = (int *)LocalAlloc(LPTR,sizeof(int) * gpsAudCapInfoList->cFormats);
            if (NULL == gpnAudCapOrderedIndex)
            {
                DebugTextOut(TEXT("Out of memory\n"));
            }
        }
    }

    //Structures returned by EnumFormats not guarenteed to be inorder.
    IndexInstalledCodecs(); 
}

//****************************************************************************
//
// void IndexInstalledCodecs(void)
//
// Updates the CapOrderedIndexes to contain lists of indexes to the codecs 
// represented in the CapInfoLists in installed order.
//
//****************************************************************************

void IndexInstalledCodecs(void)
{
    unsigned int i;

    if (NULL == gpsAudCapInfoList)
    {
        DebugTextOut(TEXT("gpsAudCapInfoList is NULL\n"));
        return;
    }

    if (NULL == gpnAudCapOrderedIndex)
    {
        DebugTextOut(TEXT("gpnAudCapOrderedIndex is NULL\n"));
        return;
    }
    
    if (gtCodec==AUDIOCODEC)
    {
        for (i=0;i<gpsAudCapInfoList->cFormats;i++)
        {
            gpnAudCapOrderedIndex[gpsAudCapInfoList->aFormats[i].wSortIndex]=i;
        }
    }

}

//****************************************************************************
//
// void UpdateCapInfoListsFromIndex(void)
//
// Updates the CapInfoLists with the installed order represended in the CapOrderedIndexes
//
//****************************************************************************

void UpdateCapInfoListsFromIndex(void)
{
    unsigned int i;

    if (NULL == gpsAudCapInfoList)
    {
        DebugTextOut(TEXT("gpsAudCapInfoList is NULL\n"));
        return;
    }

    if (NULL == gpnAudCapOrderedIndex)
    {
        DebugTextOut(TEXT("gpnAudCapOrderedIndex is NULL\n"));
        return;
    }

    if (gtCodec==AUDIOCODEC)
    {
        for (i=0;i<gpsAudCapInfoList->cFormats;i++)
        {
            gpsAudCapInfoList->aFormats[gpnAudCapOrderedIndex[i]].wSortIndex=i;
        }
    }
    
}

//****************************************************************************
//
// void DlgDisplayInstalledCodecs(HWND hwnd)
//
// Displays the installed codecs in the order specified by the CapOrderedIndexes.
//
//****************************************************************************

void DlgDisplayInstalledCodecs(HWND hwnd)
{
    unsigned int    i;
    HWND            hListBox = NULL;
    
    if (NULL == gpsAudCapInfoList)
    {
        DebugTextOut(TEXT("gpsAudCapInfoList is NULL\n"));
        return;
    }

    if (NULL == gpnAudCapOrderedIndex)
    {
        DebugTextOut(TEXT("gpnAudCapOrderedIndex is NULL\n"));
        return;
    }
    
    //Display Installed Codecs
    hListBox = GetDlgItem(hwnd,IDC_LBINSTALLEDCODECS);
    SendMessage(hListBox,LB_RESETCONTENT,0,0);
    
    if (gtCodec==AUDIOCODEC)
    {
        for (i=0;i<gpsAudCapInfoList->cFormats;i++)
        {
            SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)(LPCSTR)gpsAudCapInfoList->aFormats[gpnAudCapOrderedIndex[i]].szFormat);
        }
    }

}


//****************************************************************************
//
// void DebugTextOut(TCHAR* ptszFormat, ... )
//
// 
//
//****************************************************************************

void DebugTextOut(TCHAR* ptszFormat, ... )
{
    TCHAR       ptszBuffer[1048];
    va_list     pArgList;

    va_start(pArgList, ptszFormat);
    _vsntprintf(ptszBuffer, sizeof(ptszBuffer)/sizeof(ptszBuffer[0]), ptszFormat, pArgList);
    va_end(pArgList);

    OutputDebugString(ptszBuffer);
}


//*****************************************************************************
