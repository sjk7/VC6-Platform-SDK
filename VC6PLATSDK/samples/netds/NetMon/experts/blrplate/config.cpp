//============================================================================
//  MODULE: Config.cpp
//
//  Description:
//
//  Handles the dialog for configuring the BLRPLATE Expert
//
//  Modification History:
//
//  Your Name Here      01/01/70    Created
//============================================================================
#define STRICT 1
#include <windows.h>
#include <windowsx.h>
#include <netmon.h>
#include "Resrc1.h"
#include "BLRPLATE.h"

//////////////////////////////////////////////////////////////////////////////
// Global Variables

HEXPERTKEY        g_hExpertKey;
PBLRPLATECONFIG * g_ppBLRPLATEConfig;

//////////////////////////////////////////////////////////////////////////////
// Forward Declarations
BOOL CALLBACK ConfigBLRPLATEDlg_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// input handlers
BOOL ConfigBLRPLATEDlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void ConfigBLRPLATEDlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void ConfigBLRPLATEDlg_OnOKButton( HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void ConfigBLRPLATEDlg_OnCancelButton( HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void ConfigBLRPLATEDlg_OnHelpButton( HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

//////////////////////////////////////////////////////////////////////////////
// ConfigBLRPLATEDlg_Do
BOOL ConfigBLRPLATEDlg_Do(HWND hwnd, 
                          PBLRPLATECONFIG * ppBLRPLATEConfig, 
                          HEXPERTKEY hExpertKey)
{
    // save the current struture
    g_hExpertKey = hExpertKey;
    g_ppBLRPLATEConfig = ppBLRPLATEConfig;

    // create the dialog box...
    return DialogBox( g_hInstance, 
                      MAKEINTRESOURCE(IDD_BLRPLATE_CONFIG_DIALOG), 
                      hwnd, 
                      (DLGPROC)ConfigBLRPLATEDlg_DlgProc);
}

//////////////////////////////////////////////////////////////////////////////
// ConfigBLRPLATEDlg_DlgProc
BOOL CALLBACK ConfigBLRPLATEDlg_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG, ConfigBLRPLATEDlg_OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND,    ConfigBLRPLATEDlg_OnCommand);

        // this makes the F1 key act like the Help key
        case WM_HELP:
            ConfigBLRPLATEDlg_OnHelpButton(hwnd, IDM_HELP, NULL, 0);
            break;
    }
    return(FALSE);
}

//////////////////////////////////////////////////////////////////////////////
// ConfigBLRPLATEDlg_OnInitDialog
BOOL ConfigBLRPLATEDlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    // TODO: Add initialization code

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// ConfigBLRPLATEDlg_OnCommand
void ConfigBLRPLATEDlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch(id)
    {
        // OK Button has been hit...
        case IDOK:
            ConfigBLRPLATEDlg_OnOKButton(hwnd, id, hwndCtl, codeNotify);
            break;

        // Cancel button has been hit
        case IDCANCEL:
            ConfigBLRPLATEDlg_OnCancelButton(hwnd, id, hwndCtl, codeNotify);
            break;

        case IDM_HELP:
            ConfigBLRPLATEDlg_OnHelpButton(hwnd, id, hwndCtl, codeNotify);
            break;
    }
}

//////////////////////////////////////////////////////////////////////////////
// ConfigBLRPLATEDlg_OnOKButton
void ConfigBLRPLATEDlg_OnOKButton( HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    DWORD BufferSize;
    DWORD rc;

    // TODO: Validate dialog contents ----------------------------------------
    BufferSize = 1;

    // TODO: Size the buffer -------------------------------------------------
    // do we have a config buffer?
    if( *g_ppBLRPLATEConfig == NULL )
    {
        // no, allocate one
        *g_ppBLRPLATEConfig = (PBLRPLATECONFIG)ExpertAllocMemory( 
                                    g_hExpertKey,
                                    BufferSize,
                                    &rc);
        if( *g_ppBLRPLATEConfig == NULL )
        {
            return;
        }
    }
    else
    {
        // is the given buffer big enough
        if( (*g_ppBLRPLATEConfig)->nTotalLength < BufferSize )
        {
            PBLRPLATECONFIG TempConfig;

            // no, we must grow it
            TempConfig = (PBLRPLATECONFIG)ExpertReallocMemory( 
                                    g_hExpertKey,
                                    *g_ppBLRPLATEConfig,
                                    BufferSize,
                                    &rc);
            if( TempConfig == NULL )
            {
                return;
            }

            // it worked
            *g_ppBLRPLATEConfig = TempConfig;
        }
    }

    // TODO: Fill in the Config ----------------------------------------------

    // we are done
    EndDialog(hwnd, TRUE);
}

//////////////////////////////////////////////////////////////////////////////
// ConfigBLRPLATEDlg_OnCancelButton
void ConfigBLRPLATEDlg_OnCancelButton( HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{   
    // TODO: Release any memory that you have allocated

    // we are done
    EndDialog(hwnd, FALSE);
}

//////////////////////////////////////////////////////////////////////////////
// ConfigBLRPLATEDlg_OnHelpButton()
void ConfigBLRPLATEDlg_OnHelpButton( HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    // TODO: bring up help
}

