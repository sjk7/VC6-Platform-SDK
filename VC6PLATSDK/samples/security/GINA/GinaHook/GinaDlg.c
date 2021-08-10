/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

 Copyright (C) 1996 - 2000.  Microsoft Corporation.  All rights reserved.

 Module:   GinaDlg.c

 Abstract: See ReadMe.txt for more detail information about this sample.

 Revision: August 6, 1999.

-------------------------------------------------------------------------------*/

#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <winwlx.h>
#include <assert.h>
#include <lm.h>

#include "Ginahook.h"

//
// MSGINA dialog box IDs.
//
#define IDD_WLXDIAPLAYSASNOTICE_DIALOG    1400
#define IDD_WLXLOGGEDOUTSAS_DIALOG        1450
#define IDD_CHANGE_PASSWORD_DIALOG        1550
#define IDD_WLXLOGGEDONSAS_DIALOG         1650
#define IDD_WLXWKSTALOCKEDSAS_DIALOG      1850

//
// MSGINA control IDs
//
#define IDC_WLXLOGGEDOUTSAS_USERNAME      1453
#define IDC_WLXLOGGEDOUTSAS_PASSWORD      1454
#define IDC_WLXLOGGEDOUTSAS_DOMAIN        1455
#define IDC_WLXWKSTALOCKEDSAS_DOMAIN      1856

//
// Pointers to redirected functions.
//

static PWLX_DIALOG_BOX_PARAM pfWlxDialogBoxParam = NULL;

//
// Pointers to redirected dialog box.
//

static DLGPROC pfWlxLoggedOutSASDlgProc   = NULL;
static DLGPROC pfWlxWkstaLockedSASDlgProc = NULL;
static DLGPROC pfChangePasswordDlgProc    = NULL;

//
// Local functions.
//

int WINAPI MyWlxDialogBoxParam (HANDLE, HANDLE, LPWSTR, HWND, DLGPROC, LPARAM);

//
// Local variables.
//

static char g_szLocalMachineName[256] = "";


//
// Hook WlxDialogBoxParam() dispatch function.
//
void HookWlxDialogBoxParam (PVOID pWinlogonFunctions, DWORD dwWlxVersion)
{
   //
   // Hook WlxDialogBoxParam(). Note that we chould cheat here by always
   // casting to (PWLX_DISPATCH_VERSION_1_0) since WlxDialogBoxParam()
   // exists in all versions and is always in the same location of the
   // dispatch table. But, we will do it the hard way!
   //
   switch (dwWlxVersion)
   {
      case WLX_VERSION_1_0: 
      {
         pfWlxDialogBoxParam = 
            ((PWLX_DISPATCH_VERSION_1_0) pWinlogonFunctions)->WlxDialogBoxParam;
         ((PWLX_DISPATCH_VERSION_1_0) pWinlogonFunctions)->WlxDialogBoxParam = 
            MyWlxDialogBoxParam;
         break;
      }
  
      case WLX_VERSION_1_1:
      {
         pfWlxDialogBoxParam = 
            ((PWLX_DISPATCH_VERSION_1_1) pWinlogonFunctions)->WlxDialogBoxParam;
         ((PWLX_DISPATCH_VERSION_1_1) pWinlogonFunctions)->WlxDialogBoxParam = 
            MyWlxDialogBoxParam;
         break;
      }
   
      case WLX_VERSION_1_2:
      {
         pfWlxDialogBoxParam = 
            ((PWLX_DISPATCH_VERSION_1_2) pWinlogonFunctions)->WlxDialogBoxParam;
         ((PWLX_DISPATCH_VERSION_1_2) pWinlogonFunctions)->WlxDialogBoxParam = 
            MyWlxDialogBoxParam;
         break;
      }
   
      default:
      {
         pfWlxDialogBoxParam = 
            ((PWLX_DISPATCH_VERSION_1_3) pWinlogonFunctions)->WlxDialogBoxParam;
         ((PWLX_DISPATCH_VERSION_1_3) pWinlogonFunctions)->WlxDialogBoxParam = 
            MyWlxDialogBoxParam;
         break;
      }
   }
}


//
// Redirected WlxLoggedOutSASDlgProc().
//

BOOL 
CALLBACK 
MyWlxLoggedOutSASDlgProc (HWND   hwndDlg,  // handle to dialog box
                          UINT   uMsg,     // message  
                          WPARAM wParam,   // first message parameter
                          LPARAM lParam)   // second message parameter
{
   BOOL bResult;
   
   //
   // Sanity check.
   //
   assert(pfWlxLoggedOutSASDlgProc != NULL);
   
   //
   // Pass on to MSGINA first.
   //
   bResult = pfWlxLoggedOutSASDlgProc(hwndDlg, uMsg, wParam, lParam);

   //
   // We are only interested in WM_INITDIALOG message.
   //
   if (uMsg == WM_INITDIALOG)
   {
      DWORD dwIndex;
      HWND hwndDomain;
      NET_API_STATUS netstatus;
      LPWKSTA_INFO_100 lpWkstaInfo;

      //
      // Get local machine name.
      //
      netstatus = NetWkstaGetInfo(NULL, 100, (LPBYTE *) &lpWkstaInfo);
      if (netstatus != NERR_Success)
      {
         return bResult;
      }            

      //
      // Convert to ANSI.
      //
      wcstombs(g_szLocalMachineName, lpWkstaInfo->wki100_computername, 
               sizeof(g_szLocalMachineName));

      //
      // and free the buffer.
      //
      NetApiBufferFree((LPVOID) lpWkstaInfo);

      //
      // Manipulate the domain combo box so that only some predetermined
      // trusted domains are included in the list.
      //
      // In our case, we restrict logon to local machine only.
      //
      hwndDomain = GetDlgItem(hwndDlg, IDC_WLXLOGGEDOUTSAS_DOMAIN);
      if (hwndDomain == NULL)
      {
         return bResult;
      }

      dwIndex = (DWORD) SendMessage(hwndDomain, CB_FINDSTRING, 
                                    0, (LPARAM) g_szLocalMachineName);
      if (dwIndex != CB_ERR)
      {
         SendMessage(hwndDomain, CB_SETCURSEL, (WPARAM) dwIndex, 0);
         EnableWindow(hwndDomain, FALSE);
      }
   }

   return bResult;
}


//
// Redirected WlxWkstaLockedSASDlgProc().
//

BOOL 
CALLBACK 
MyWlxWkstaLockedSASDlgProc (HWND   hwndDlg,  // handle to dialog box
                            UINT   uMsg,     // message  
                            WPARAM wParam,   // first message parameter
                            LPARAM lParam)   // second message parameter
{
   BOOL bResult;
   
   //
   // Sanity check.
   //
   assert(pfWlxWkstaLockedSASDlgProc != NULL);
   
   //
   // Pass on to MSGINA first.
   //
   bResult = pfWlxWkstaLockedSASDlgProc(hwndDlg, uMsg, wParam, lParam);

   //
   // We are only interested in WM_INITDIALOG message.
   //
   if (uMsg == WM_INITDIALOG)
   {
      DWORD dwIndex;

      //
      // Make sure to cover this hole.
      //
      HWND hwndDomain = GetDlgItem(hwndDlg, IDC_WLXWKSTALOCKEDSAS_DOMAIN);
      if (hwndDomain == NULL)
      {
         return bResult;
      }

      dwIndex = (DWORD) SendMessage(hwndDomain, CB_FINDSTRING, 
                                    0, (LPARAM) g_szLocalMachineName);
      if (dwIndex != CB_ERR)
      {
         SendMessage(hwndDomain, CB_SETCURSEL, (WPARAM) dwIndex, 0);
         EnableWindow(hwndDomain, FALSE);
      }
   }

   return bResult;
}


//
// Redirected ChangePasswordDlgProc().
//

BOOL 
CALLBACK 
MyChangePasswordDlgProc (HWND   hwndDlg,  // handle to dialog box
                         UINT   uMsg,     // message  
                         WPARAM wParam,   // first message parameter
                         LPARAM lParam)   // second message parameter
{
   BOOL bResult;
   
   //
   // Sanity check.
   //
   assert(pfChangePasswordDlgProc != NULL);

   //
   // Pass on to MSGINA first.
   //
   bResult = pfChangePasswordDlgProc(hwndDlg, uMsg, wParam, lParam);

   //
   // We are only interested in WM_INITDIALOG message.
   //
   if (uMsg == WM_INITDIALOG)
   {
      //
      // Manipulate the dialog box to match your needs here. For example,
      // you can add a static control to the dialog box or display another
      // message to clearly explain the rules for composing a valid password.
      //
   }

   return bResult;
}


//
// Redirected WlxDialogBoxParam() function.
//

int 
WINAPI 
MyWlxDialogBoxParam (HANDLE  hWlx,
                     HANDLE  hInst,
                     LPWSTR  lpszTemplate,
                     HWND    hwndOwner,
                     DLGPROC dlgprc,
                     LPARAM  dwInitParam)
{
   //
   // Sanity check.
   //
   assert(pfWlxDialogBoxParam != NULL);

   //
   // We only know MSGINA dialogs by identifiers.
   //
   if (!HIWORD(lpszTemplate))
   {
      //
      // Hook appropriate dialog boxes as necessary.
      //
      switch ((DWORD) lpszTemplate)
      {
         case IDD_WLXLOGGEDOUTSAS_DIALOG:
         {
            pfWlxLoggedOutSASDlgProc = dlgprc;
            return pfWlxDialogBoxParam(hWlx, hInst, lpszTemplate, hwndOwner, 
                                       MyWlxLoggedOutSASDlgProc, dwInitParam);
         }

         case IDD_WLXWKSTALOCKEDSAS_DIALOG:
         {
            pfWlxWkstaLockedSASDlgProc = dlgprc;
            return pfWlxDialogBoxParam(hWlx, hInst, lpszTemplate, hwndOwner, 
                                       MyWlxWkstaLockedSASDlgProc, dwInitParam);
         }

         case IDD_CHANGE_PASSWORD_DIALOG:
         {
            pfChangePasswordDlgProc = dlgprc;
            return pfWlxDialogBoxParam(hWlx, hInst, lpszTemplate, hwndOwner, 
                                       MyChangePasswordDlgProc, dwInitParam);
         }
      }
   }

   //
   // The rest will not be redirected.
   //
   return pfWlxDialogBoxParam(hWlx, hInst, lpszTemplate, 
                              hwndOwner, dlgprc, dwInitParam);
}