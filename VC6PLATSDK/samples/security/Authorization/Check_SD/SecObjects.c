/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1997 - 2000.  Microsoft Corporation.  All rights reserved

Module Name:

    secobjects.c

Abstract:

    this module contains the variety of functions to obtain the security
    descriptor for a variety of securables objects.

    DumpFileKey()      - file or directory
    DumpKernelObject() - event, mutex, semaphore, process, process access
                         token, file mapping, named pipe, mailslot,
    DumpNetShare()     - network share
    DumpPrinter()      - printer
    DumpRegistryKey()  - registry key
    DumpService()      - service
    DumpUserObject()   - desktop, window station

--*/

#include "check_sd.h"
#include <lm.h>
#include <tchar.h>
#include <stdio.h>

void DumpFile(LPTSTR pszFile, TCHAR c)
{
     DWORD                dwSize = 0;
     PSECURITY_DESCRIPTOR psd = NULL;
     SECURITY_INFORMATION si  = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION;

     //
     // enable the privilege
     //
     Privilege(SE_SECURITY_NAME, TRUE);

     //
     // get the size
     //
     if (!GetFileSecurity(pszFile, si, psd, dwSize, &dwSize)){
          if (GetLastError() == ERROR_INSUFFICIENT_BUFFER){
               psd = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, dwSize);
               if (psd == NULL)
                    DisplayError(GetLastError(), TEXT("LocalAlloc"));

			    if (!GetFileSecurity(pszFile, si, psd, dwSize, &dwSize))
			         DisplayError(GetLastError(), TEXT("GetFileSecurity"));
          }
          else
               DisplayError(GetLastError(), TEXT("GetFileSecurity"));
     }
	 else{
          printf("GetFileSecurity succeeded when it was expected to fail.\n");
		  ExitProcess(0);
	 }

     //
     // enable the privilege
     //
     Privilege(SE_SECURITY_NAME, FALSE);

     //
     // dump security descriptor
     //
     DumpSD(psd, c);

     //
     // free the buffer
     //
	 if (NULL != psd)
	 {
          if (LocalFree((HLOCAL)psd))
               DisplayError(GetLastError(), TEXT("LocalFree"));
	 }
}

void DumpKernelObject(LPTSTR pszObject, TCHAR c)
{
     DWORD                dwPid;
     DWORD                dwSize = 0;
     HANDLE               hObject;
     HANDLE               hProcess;
     PSECURITY_DESCRIPTOR psd = NULL;
     SECURITY_INFORMATION si  = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION;

     //
     // enable the privilege
     //
     Privilege(SE_SECURITY_NAME, TRUE);

     //
     // obtain a handle
     //
     switch (c){
          case 'e':
               hObject = OpenEvent(READ_CONTROL | ACCESS_SYSTEM_SECURITY, FALSE, pszObject);
               if (hObject == NULL)
                    DisplayError(GetLastError(), TEXT("OpenEvent"));
               break;
          case 'm':
               hObject = OpenMutex(READ_CONTROL | ACCESS_SYSTEM_SECURITY, FALSE, pszObject);
               if (hObject == NULL)
                    DisplayError(GetLastError(), TEXT("OpenMutex"));
               break;
          case 's':
               hObject = OpenSemaphore(READ_CONTROL | ACCESS_SYSTEM_SECURITY, FALSE, pszObject);
               if (hObject == NULL)
                    DisplayError(GetLastError(), TEXT("OpenSemaphore"));
               break;
          case 'p':
               //
               // convert name to a pid
               //
               dwPid = _ttol(pszObject);

               hObject = OpenProcess(READ_CONTROL | ACCESS_SYSTEM_SECURITY, FALSE, dwPid);
               if (hObject == NULL)
                    DisplayError(GetLastError(), TEXT("OpenProcess"));
               break;

          case 'o':
               dwPid = _ttol(pszObject);

               //
               // SD in access token does not support SACLS
               //
               si  = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;

               hProcess= OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwPid);
               if (hProcess == NULL)
                    DisplayError(GetLastError(), TEXT("OpenProcess"));

               if (!OpenProcessToken(hProcess, READ_CONTROL, &hObject))
                    DisplayError(GetLastError(), TEXT("OpenProcessToken"));

               if (!CloseHandle(hProcess))
                    DisplayError(GetLastError(), TEXT("CloseHandle"));
               break;
          case 'i':
               hObject = OpenFileMapping(READ_CONTROL | ACCESS_SYSTEM_SECURITY, FALSE, pszObject);
               if (hObject == NULL)
                    DisplayError(GetLastError(), TEXT("OpenFileMapping"));
               break;
          case 'a':
          case 'n':
               hObject = CreateFile(pszObject, READ_CONTROL | ACCESS_SYSTEM_SECURITY, 0, NULL, OPEN_EXISTING, 0, NULL);
               if (hObject == INVALID_HANDLE_VALUE)
                    DisplayError(GetLastError(), TEXT("CreateFile"));
          default:
               break;
     }

     //
     // disable the privilege
     //
     Privilege(SE_SECURITY_NAME, FALSE);

     //
     // obtain the size
     //
     if (!GetKernelObjectSecurity(hObject, si, psd, dwSize, &dwSize)){
          if (GetLastError() == ERROR_INSUFFICIENT_BUFFER){
               psd = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, dwSize);
               if (psd == NULL)
                    DisplayError(GetLastError(), TEXT("LocalAlloc"));

               if (!GetKernelObjectSecurity(hObject, si, psd, dwSize, &dwSize))
                    DisplayError(GetLastError(), TEXT("GetKernelObjectSecurity"));
          }
          else
                DisplayError(GetLastError(), TEXT("GetKernelObjectSecurity"));
     }
	 else{
	      printf("GetFileSecurity succeeded when it was expected to fail.\n");
		  ExitProcess(0);
	 }

     //
     // dump security descriptor
     //
     DumpSD(psd, c);

     //
     // free the buffer
     //
	 if (NULL != psd)
          if (LocalFree((HLOCAL)psd))
               DisplayError(GetLastError(), TEXT("LocalFree"));

     if (!CloseHandle(hObject))
          DisplayError(GetLastError(), TEXT("CloseHandle"));
}

void DumpNetShare(LPTSTR pszShare)
{
     DWORD                dwSize = 0;
     LPTSTR               pszShareAdjusted;
     LPTSTR               pszShareName;
     NET_API_STATUS       nas;
     PSECURITY_DESCRIPTOR psd   = NULL;
     PSHARE_INFO_502      psi502;
     TCHAR                szServer[CNLEN] = TEXT("");

#ifndef UNICODE
     WCHAR                szWServer[CNLEN] = L"";
     WCHAR                szWShare[NNLEN]  = L"";
#endif

     //
     // remove \\ if exists
     //
     pszShareAdjusted = _tcsstr(pszShare, TEXT("\\\\"));
     if (pszShareAdjusted != NULL)
          pszShareAdjusted = pszShareAdjusted + 2;
     else
          pszShareAdjusted = pszShare;

     //
     // find the subkey
     //
     pszShareName = _tcschr(pszShareAdjusted, '\\');
     if (pszShareName == NULL)
          return;
     else
          pszShareName++;

     //
     // find the main key
     //
     if (!_tcsncpy(szServer, pszShareAdjusted, (UINT)(pszShareName - pszShareAdjusted - 1)))
          DisplayError(GetLastError(), TEXT("_tcsncpy"));


#ifndef UNICODE

     //
     // handle ANSI situation
     //
     if (!MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)szServer, -1, szWServer, sizeof(szWServer)))
          DisplayError(GetLastError(), TEXT("MultiByteToWideChar"));

     if(!MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)pszShareName, -1, szWShare, sizeof(szWShare)))
          DisplayError(GetLastError(), TEXT("MultiByteToWideChar"));

     nas = NetShareGetInfo(szWServer, szWShare, 502, (LPBYTE *)&psi502);

#else

     nas = NetShareGetInfo(szServer, pszShareName, 502, (LPBYTE *)&psi502);

#endif

     if (nas != NERR_Success)
          DisplayError(nas, TEXT("NetShareGetInfo"));

     //
     // obtain the SD
     //
     psd = psi502->shi502_security_descriptor;

     //
     // dump security descriptor
     //
     DumpSD(psd, 't');

     //
     // free the buffer
     //
     nas = NetApiBufferFree((LPVOID)psi502);
     if (nas != NERR_Success)
          DisplayError(nas, TEXT("NetApiBufferFree"));

}

void DumpPrinter(LPTSTR pszPrinter)
{
     DWORD                dwSize = 0;
     HANDLE               hPrinter;
     PRINTER_DEFAULTS     pd;
     PRINTER_INFO_3       *ppi3 = NULL;
     PSECURITY_DESCRIPTOR psd   = NULL;

     ZeroMemory(&pd, sizeof(PRINTER_DEFAULTS));
     pd.DesiredAccess = READ_CONTROL;

     //
     // obtain a handle to the printer
     //
     if (!OpenPrinter(pszPrinter, &hPrinter, &pd))
          DisplayError(GetLastError(), TEXT("OpenPrinter"));

     //
     // get the size
     //
     if (!GetPrinter(hPrinter, 3, (LPBYTE)ppi3, dwSize, &dwSize)){
          if (GetLastError() == ERROR_INSUFFICIENT_BUFFER){
               ppi3 = (PPRINTER_INFO_3)LocalAlloc(LPTR, dwSize);
               if (ppi3 == NULL)
                    DisplayError(GetLastError(), TEXT("LocalAlloc"));

               if (!GetPrinter(hPrinter, 3, (LPBYTE)ppi3, dwSize, &dwSize))
                    DisplayError(GetLastError(), TEXT("GetPrinter"));
          }
     }
	 else{
	      printf("GetPrinter succeeded when it was expected to fail.\n");
		  ExitProcess(0);
	 }


     //
     // cast buffer
     //
     psd = ppi3->pSecurityDescriptor;

     //
     // dump security descriptor information
     //
     DumpSDInfo(psd);

     //
     // dump the control bits
     //
     DumpControl(psd);

     //
     // get the owner
     //
     DumpOwnerGroup(psd, TRUE);

     //
     // get the group
     //
     DumpOwnerGroup(psd, FALSE);

     //
     // get the dacl
     //
     DumpDacl(psd, 'l', TRUE);

     //
     // printer object does not have a SACL
     //

     //
     // free the buffer
     //
     if (!ppi3)
		  if (LocalFree((HLOCAL)ppi3))
               DisplayError(GetLastError(), TEXT("LocalFree"));

     if (!ClosePrinter(hPrinter))
          DisplayError(GetLastError(), TEXT("ClosePrinter"));
}

void DumpRegistryKey(LPTSTR pszKey)
{
     DWORD                dwAccess = READ_CONTROL;
     DWORD                dwSize = 0;
     HKEY                 hKey;
     HKEY                 hMainKey;
     LONG                 lErrorCode;
     LPTSTR               pszSubKey = NULL;
     PSECURITY_DESCRIPTOR psd = NULL;
     SECURITY_INFORMATION si;
     TCHAR                szMainKey[256] = TEXT("");

     //
     // find the subkey
     //
     pszSubKey = _tcschr(pszKey, '\\');
     if (pszSubKey == NULL){
          if (!lstrcpy(szMainKey, pszKey))
		       DisplayError(GetLastError(), TEXT("lstrcpy"));

          si = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;
     }
     else{
          pszSubKey++;

          //
          // find the main key
          //
          if(!_tcsncpy(szMainKey, pszKey, (UINT)(pszSubKey - pszKey - 1)))
               DisplayError(GetLastError(), TEXT("_tcsncpy"));

          si = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION;
     }

     //
     // parse the main key
     //
     if (!lstrcmp(szMainKey, TEXT("HKEY_LOCAL_MACHINE"))){
          hMainKey = HKEY_LOCAL_MACHINE;
     }
     else if (!lstrcmp(szMainKey, TEXT("HKEY_CLASSES_ROOT"))){
          hMainKey = HKEY_CLASSES_ROOT;
     }
     else if (!lstrcmp(szMainKey, TEXT("HKEY_USERS"))){
          hMainKey = HKEY_USERS;
     }
     else if (!lstrcmp(szMainKey, TEXT("HKEY_CURRENT_USER"))){
          hMainKey = HKEY_CURRENT_USER;
     }
     else if (!lstrcmp(szMainKey, TEXT("HKEY_CLASSES_ROOT"))){
          hMainKey = HKEY_CLASSES_ROOT;
     }
     else
          hMainKey = 0;

     //
     // enable the privilege
     //
     if (pszSubKey != NULL){
          Privilege(SE_SECURITY_NAME, TRUE);
          dwAccess |= ACCESS_SYSTEM_SECURITY;
     }

     //
     // open the key
     //
     lErrorCode = RegOpenKeyEx(hMainKey, pszSubKey, 0, dwAccess, &hKey);
     if (lErrorCode != ERROR_SUCCESS)
          DisplayError(lErrorCode, TEXT("RegOpenKeyEx"));

     //
     // disable the privilege
     //
     if (pszSubKey != NULL)
          Privilege(SE_SECURITY_NAME, FALSE);

     //
     // get key security information
     //
     lErrorCode = RegGetKeySecurity(hKey, si, psd, &dwSize);
     if (lErrorCode == ERROR_INSUFFICIENT_BUFFER){
          //
          // allocate memory for psd
          //
          psd = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, dwSize);
          if (psd == NULL)
               DisplayError(GetLastError(), TEXT("LocalAlloc"));

          //
          // call the api again
          //
          lErrorCode = RegGetKeySecurity(hKey, si, psd, &dwSize);
          if (lErrorCode != ERROR_SUCCESS)
               DisplayError(lErrorCode, TEXT("RegGetKeySecurity"));
     }
     else
          DisplayError(lErrorCode, TEXT("RegGetKeySecurity"));

     //
     // dump security descriptor
     //
     DumpSD(psd, 'r');

     //
     // free the buffer
     //
     if (LocalFree((HLOCAL)psd))
          DisplayError(GetLastError(), TEXT("LocalFree"));

     //
     // close the key
     //
     lErrorCode = RegCloseKey(hKey);
     if (lErrorCode != ERROR_SUCCESS)
          DisplayError(lErrorCode, TEXT("RegCloseKey"));
}

void DumpService(LPTSTR pszServer, LPTSTR pszService)
{
     DWORD                dwSize = 0;
     PSECURITY_DESCRIPTOR psd = (PSECURITY_DESCRIPTOR)1;  // if initialized to NULL, QueryServiceObjectSecurity() returns error code 87
     SC_HANDLE            schService;
     SC_HANDLE            schManager;
     SECURITY_INFORMATION si  = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION;

     schManager = OpenSCManager(pszServer, NULL, SC_MANAGER_CONNECT);
     if (schManager == NULL)
          DisplayError(GetLastError(), TEXT("OpenSCManager"));

     //
     // enable the privilege
     //
     Privilege(SE_SECURITY_NAME, TRUE);

     schService = OpenService(schManager, pszService, READ_CONTROL | ACCESS_SYSTEM_SECURITY);
     if (schService == NULL)
          DisplayError(GetLastError(), TEXT("OpenService"));

     //
     // disable the privilege
     //
     Privilege(SE_SECURITY_NAME, FALSE);

     //
     // obtain the size
     //
     if (!QueryServiceObjectSecurity(schService, si, psd, dwSize, &dwSize)){
          if (GetLastError() == ERROR_INSUFFICIENT_BUFFER){
               psd = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, dwSize);
               if (psd == NULL)
                    DisplayError(GetLastError(), TEXT("LocalAlloc"));

          if (!QueryServiceObjectSecurity(schService, si, psd, dwSize, &dwSize))
               DisplayError(GetLastError(), TEXT("QueryServicelObjectSecurity"));
          }
          else
               DisplayError(GetLastError(), TEXT("QueryServiceObjectSecurity"));
     }
	 else{
	      printf("QueryServiceObjectSecurity succeeded when it was expected to fail.\n");
		  ExitProcess(0);
	 }



     //
     // dump security descriptor
     //
     DumpSD(psd, 'v');

     //
     // free the buffer
     //
     if(LocalFree((HLOCAL)psd))
	      DisplayError(GetLastError(), TEXT("LocalFree"));

     if (!CloseServiceHandle(schService))
          DisplayError(GetLastError(), TEXT("CloseServiceHandle"));

     if (!CloseServiceHandle(schManager))
          DisplayError(GetLastError(), TEXT("CloseServiceHandle"));
}

void DumpUserObject(LPTSTR pszObject, TCHAR c)
{
     DWORD                dwSize = 0;
     HANDLE               hObject;
     HWINSTA              hwinsta;
     HWINSTA              hwinstaCurrent;
     LPTSTR               pszDesktop;
     PSECURITY_DESCRIPTOR psd = NULL;
     SECURITY_INFORMATION si  = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION;
     TCHAR                szWinsta[256] = TEXT("");

     //
     // enable the privilege
     //
     Privilege(SE_SECURITY_NAME, TRUE);

     //
     // obtain a handle
     //
     switch (c){
          case 'w':
               hObject = OpenWindowStation(pszObject, FALSE, READ_CONTROL | ACCESS_SYSTEM_SECURITY);
               if (hObject == NULL)
                    DisplayError(GetLastError(), TEXT("OpenWindowStation"));
               break;

          case 'k':
               //
               // find the desktop
               //
               pszDesktop = _tcschr(pszObject, '\\');
               if (pszDesktop == NULL)
                    return;
               else
                    pszDesktop++;

               //
               // find the main key
               //
               if (!_tcsncpy(szWinsta, pszObject, (UINT)(pszDesktop - pszObject - 1)))
                    DisplayError(GetLastError(), TEXT("_tcsncpy"));

               //
               // obtain a handle to the window station
               //
               hwinsta = OpenWindowStation(szWinsta, FALSE, WINSTA_ENUMDESKTOPS);
               if (hwinsta == NULL)
                    DisplayError(GetLastError(), TEXT("OpenWindowStation"));

               hwinstaCurrent = GetProcessWindowStation();
               if (hwinstaCurrent == NULL)
                    DisplayError(GetLastError(), TEXT("GetProcessWindowStation"));

               if (!SetProcessWindowStation(hwinsta))
                    DisplayError(GetLastError(), TEXT("SetProcessWindowStation"));

               hObject = OpenDesktop(pszDesktop, 0, FALSE, READ_CONTROL | ACCESS_SYSTEM_SECURITY);
               if (hObject == NULL)
                    DisplayError(GetLastError(), TEXT("OpenDesktop"));

               if (!SetProcessWindowStation(hwinstaCurrent))
                    DisplayError(GetLastError(), TEXT("SetProcessWindowStation"));

               if (!CloseWindowStation(hwinsta))
                    DisplayError(GetLastError(), TEXT("CloseWindowStation"));
               break;
          default:
               break;
     }

     //
     // disable the privilege
     //
     Privilege(SE_SECURITY_NAME, FALSE);

     //
     // obtain the size
     //
     if (!GetUserObjectSecurity(hObject, &si, psd, dwSize, &dwSize)){
          if (GetLastError() == ERROR_INSUFFICIENT_BUFFER){
               psd = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, dwSize);
               if (psd == NULL)
                    DisplayError(GetLastError(), TEXT("LocalAlloc"));

               if (!GetUserObjectSecurity(hObject, &si, psd, dwSize, &dwSize))
                    DisplayError(GetLastError(), TEXT("GetUserObjectSecurity"));
           }
           else
                DisplayError(GetLastError(), TEXT("GetUserObjectSecurity"));
     }
	 else{
	      printf("GetUserObjectSecurity succeeded when it was expected to fail.\n");
		  ExitProcess(0);
	 }

     //
     // dump security descriptor
     //
     DumpSD(psd, c);

     //
     // free the buffer
     //
     if (LocalFree((HLOCAL)psd))
	      DisplayError(GetLastError(), TEXT("LocalFree"));

     if (!CloseHandle(hObject))
          DisplayError(GetLastError(), TEXT("CloseHandle"));
}


