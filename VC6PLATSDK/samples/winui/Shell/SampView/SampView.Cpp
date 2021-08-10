/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1998 - 2000 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          SampView.cpp
   
   Description:   Contains DLLMain and standard OLE COM object creation stuff.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "ShlView.h"
#include "ClsFact.h"
#include "ViewList.h"
#include "Utility.h"
#include <olectl.h>

/**************************************************************************
   GUID stuff
**************************************************************************/

//this part is only done once
//if you need to use the GUID in another file, just include Guid.h
#define INITGUID
#include <initguid.h>
#include <shlguid.h>
#include "Guid.h"

/**************************************************************************
   private function prototypes
**************************************************************************/

extern "C" BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID);
BOOL DeleteEntireKey(HKEY, LPTSTR);

/**************************************************************************
   global variables
**************************************************************************/

HINSTANCE   g_hInst;
UINT        g_DllRefCount;
HIMAGELIST  g_himlLarge = NULL;
HIMAGELIST  g_himlSmall = NULL;
TCHAR       g_szStoragePath[MAX_PATH];
TCHAR       g_szExtTitle[TITLE_SIZE];
const TCHAR c_szDataFile[] = TEXT("items.ini\0");
const TCHAR c_szSection[] = TEXT("Items\0");
int         g_nColumn = INITIAL_COLUMN_SIZE;
CViewList   *g_pViewList;

/**************************************************************************

   DllMain

**************************************************************************/

extern "C" BOOL WINAPI DllMain(  HINSTANCE hInstance, 
                                 DWORD dwReason, 
                                 LPVOID lpReserved)
{
switch(dwReason)
   {
   case DLL_PROCESS_ATTACH:
      g_hInst = hInstance;
      g_DllRefCount = 0;

      GetGlobalSettings();
      
      //create the global image lists
      CreateImageLists();

      g_pViewList = new CViewList();
      break;

   case DLL_PROCESS_DETACH:
      SaveGlobalSettings();

      //destroy the global image lists
      DestroyImageLists();

      if(g_pViewList)
         delete g_pViewList;
      break;
   }
   
return TRUE;
}                                 

/**************************************************************************

   DllCanUnloadNow

**************************************************************************/

STDAPI DllCanUnloadNow(VOID)
{
return (g_DllRefCount ? S_FALSE : S_OK);
}

/**************************************************************************

   DllGetClassObject

**************************************************************************/

STDAPI DllGetClassObject(  REFCLSID rclsid, 
                           REFIID riid, 
                           LPVOID *ppReturn)
{
*ppReturn = NULL;

//if we don't support this classid, return the proper error code
if(!IsEqualCLSID(rclsid, CLSID_SampleNameSpace))
   return CLASS_E_CLASSNOTAVAILABLE;
   
//create a CClassFactory object and check it for validity
CClassFactory *pClassFactory = new CClassFactory();
if(NULL == pClassFactory)
   return E_OUTOFMEMORY;
   
//get the QueryInterface return for our return value
HRESULT hResult = pClassFactory->QueryInterface(riid, ppReturn);

//call Release to decrement the ref count - creating the object set it to one 
//and QueryInterface incremented it - since its being used externally (not by 
//us), we only want the ref count to be 1
pClassFactory->Release();

//return the result from QueryInterface
return hResult;
}

/**************************************************************************

   DllRegisterServer

**************************************************************************/

typedef struct{
   HKEY  hRootKey;
   LPTSTR lpszSubKey;
   LPTSTR lpszValueName;
   LPTSTR lpszData;
}REGSTRUCT, *LPREGSTRUCT;

STDAPI DllRegisterServer(VOID)
{
int      i;
HKEY     hKey;
LRESULT  lResult;
DWORD    dwDisp;
TCHAR    szSubKey[MAX_PATH];
TCHAR    szCLSID[MAX_PATH];
TCHAR    szModule[MAX_PATH];
LPWSTR   pwsz;

//get the CLSID in string form
StringFromIID(CLSID_SampleNameSpace, &pwsz);

if(pwsz)
   {
   WideCharToLocal(szCLSID, pwsz, ARRAYSIZE(szCLSID));

   //free the string
   LPMALLOC pMalloc;
   CoGetMalloc(1, &pMalloc);
   if(pMalloc)
      {
      pMalloc->Free(pwsz);
      pMalloc->Release();
      }
   }

//get this DLL's path and file name
GetModuleFileName(g_hInst, szModule, ARRAYSIZE(szModule));

//register the CLSID entries
REGSTRUCT ClsidEntries[] = {  HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s"),                  NULL,                   g_szExtTitle,
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocServer32"),  NULL,                   TEXT("%s"),
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocServer32"),  TEXT("ThreadingModel"), TEXT("Apartment"),
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\DefaultIcon"),     NULL,                   TEXT("%s,0"),
                              NULL,                NULL,                               NULL,                   NULL};

for(i = 0; ClsidEntries[i].hRootKey; i++)
   {
   //Create the sub key string.
   wsprintf(szSubKey, ClsidEntries[i].lpszSubKey, szCLSID);

   lResult = RegCreateKeyEx(  ClsidEntries[i].hRootKey,
                              szSubKey,
                              0,
                              NULL,
                              REG_OPTION_NON_VOLATILE,
                              KEY_WRITE,
                              NULL,
                              &hKey,
                              &dwDisp);
   
   if(NOERROR == lResult)
      {
      TCHAR szData[MAX_PATH];

      //if necessary, create the value string
      wsprintf(szData, ClsidEntries[i].lpszData, szModule);
   
      lResult = RegSetValueEx(   hKey,
                                 ClsidEntries[i].lpszValueName,
                                 0,
                                 REG_SZ,
                                 (LPBYTE)szData,
                                 (lstrlen(szData) + 1) * sizeof(TCHAR));
      
      RegCloseKey(hKey);
      }
   else
      return SELFREG_E_CLASS;
   }

//Register the default flags for the folder.

wsprintf(   szSubKey, 
            TEXT("CLSID\\%s\\ShellFolder"), 
            szCLSID);

lResult = RegCreateKeyEx(  HKEY_CLASSES_ROOT,
                           szSubKey,
                           0,
                           NULL,
                           REG_OPTION_NON_VOLATILE,
                           KEY_WRITE,
                           NULL,
                           &hKey,
                           &dwDisp);

if(NOERROR == lResult)
   {
   DWORD dwData = SFGAO_FOLDER | SFGAO_HASSUBFOLDER | SFGAO_BROWSABLE | SFGAO_DROPTARGET;

   lResult = RegSetValueEx(   hKey,
                              TEXT("Attributes"),
                              0,
                              REG_BINARY,
                              (LPBYTE)&dwData,
                              sizeof(dwData));
   
   RegCloseKey(hKey);
   }
else
   return SELFREG_E_CLASS;

//Register the name space extension

/*
Create the sub key string. Change this from "...MyComputer..." to 
"...Desktop..." if desired.
*/
//#define INSTALL_ON_DESKTOP
wsprintf(   szSubKey, 
#ifdef INSTALL_ON_DESKTOP
            TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\%s"), 
#else
            TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MyComputer\\NameSpace\\%s"), 
#endif
            szCLSID);

lResult = RegCreateKeyEx(  HKEY_LOCAL_MACHINE,
                           szSubKey,
                           0,
                           NULL,
                           REG_OPTION_NON_VOLATILE,
                           KEY_WRITE,
                           NULL,
                           &hKey,
                           &dwDisp);

if(NOERROR == lResult)
   {
   TCHAR szData[MAX_PATH];

   //Create the value string.
   lstrcpyn(szData, g_szExtTitle, ARRAYSIZE(szData));

   lResult = RegSetValueEx(   hKey,
                              NULL,
                              0,
                              REG_SZ,
                              (LPBYTE)szData,
                              (lstrlen(szData) + 1) * sizeof(TCHAR));
   
   RegCloseKey(hKey);
   }
else
   return SELFREG_E_CLASS;

//If running on NT, register the extension as approved.
OSVERSIONINFO  osvi;

osvi.dwOSVersionInfoSize = sizeof(osvi);
GetVersionEx(&osvi);

if(VER_PLATFORM_WIN32_NT == osvi.dwPlatformId)
   {
   lstrcpyn( szSubKey, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"), ARRAYSIZE(szSubKey));

   lResult = RegCreateKeyEx(  HKEY_LOCAL_MACHINE,
                              szSubKey,
                              0,
                              NULL,
                              REG_OPTION_NON_VOLATILE,
                              KEY_WRITE,
                              NULL,
                              &hKey,
                              &dwDisp);

   if(NOERROR == lResult)
      {
      TCHAR szData[MAX_PATH];

      //Create the value string.
      lstrcpyn(szData, g_szExtTitle, ARRAYSIZE(szData));

      lResult = RegSetValueEx(   hKey,
                                 szCLSID,
                                 0,
                                 REG_SZ,
                                 (LPBYTE)szData,
                                 (lstrlen(szData) + 1) * sizeof(TCHAR));
      
      RegCloseKey(hKey);
      }
   else
      return SELFREG_E_CLASS;
   }

//tell the shell that the folder has been added.
LPITEMIDLIST   pidlDesktop,
               pidlMyComputer;

SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidlDesktop);
SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &pidlMyComputer);
SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlDesktop, 0);
SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlMyComputer, 0);

IMalloc  *pMalloc;
if(S_OK == SHGetMalloc(&pMalloc))
   {
   pMalloc->Free(pidlDesktop);
   pMalloc->Free(pidlMyComputer);
   pMalloc->Release();
   }

return S_OK;
}

/**************************************************************************

   DllUnregisterServer()

**************************************************************************/

STDAPI DllUnregisterServer(VOID)
{
LPWSTR   pwsz;
TCHAR    szCLSID[MAX_PATH];
TCHAR    szSubKey[MAX_PATH];

//get the CLSID in string form
StringFromIID(CLSID_SampleNameSpace, &pwsz);

if(pwsz)
   {
   WideCharToLocal(szCLSID, pwsz, ARRAYSIZE(szCLSID));

   //free the string
   LPMALLOC pMalloc;
   CoGetMalloc(1, &pMalloc);
   if(pMalloc)
      {
      pMalloc->Free(pwsz);
      pMalloc->Release();
      }
   }
else
   {
   return E_FAIL;
   }

//delete the namespace extension entries
wsprintf(   szSubKey, 
            TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MyComputer\\NameSpace\\%s"), 
            szCLSID);
DeleteEntireKey(HKEY_LOCAL_MACHINE, szSubKey);
wsprintf(   szSubKey, 
            TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\%s"), 
            szCLSID);
DeleteEntireKey(HKEY_LOCAL_MACHINE, szSubKey);

//delete the object's registry entries
wsprintf(szSubKey, TEXT("CLSID\\%s"), szCLSID);
DeleteEntireKey(HKEY_CLASSES_ROOT, szSubKey);

//delete the approved extensions on NT
OSVERSIONINFO  osvi;

osvi.dwOSVersionInfoSize = sizeof(osvi);
GetVersionEx(&osvi);

if(VER_PLATFORM_WIN32_NT == osvi.dwPlatformId)
   {
   LRESULT  lResult;
   HKEY     hKey;

   lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                           TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"),
                           0,
                           KEY_SET_VALUE,
                           &hKey);

   if(NOERROR == lResult)
      {
      TCHAR szData[MAX_PATH];

      //Create the value string.
      lstrcpyn(szData, g_szExtTitle, ARRAYSIZE(szData));

      lResult = RegDeleteValue(  hKey,
                                 szCLSID);
      
      RegCloseKey(hKey);
      }
   else
      return SELFREG_E_CLASS;
   }

//tell the shell that the folder has been removed.
LPITEMIDLIST   pidlDesktop,
               pidlMyComputer;

SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidlDesktop);
SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &pidlMyComputer);
SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlDesktop, 0);
SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlMyComputer, 0);

IMalloc  *pMalloc;
if(S_OK == SHGetMalloc(&pMalloc))
   {
   pMalloc->Free(pidlDesktop);
   pMalloc->Free(pidlMyComputer);
   pMalloc->Release();
   }

return S_OK;
}

/**************************************************************************

   DeleteEntireKey()

**************************************************************************/

BOOL DeleteEntireKey(HKEY hKey, LPTSTR pszSubKey)
{
LRESULT  lResult;
HKEY     hEnumKey;

lResult = RegOpenKeyEx( hKey,
                        pszSubKey,
                        0,
                        KEY_ENUMERATE_SUB_KEYS,
                        &hEnumKey);

if(NOERROR == lResult)
   {
   TCHAR szKey[MAX_PATH];
   DWORD dwSize = MAX_PATH;

   while(ERROR_SUCCESS == RegEnumKeyEx(hEnumKey, 0, szKey, &dwSize, NULL, NULL, NULL, NULL))
      {
      DeleteEntireKey(hEnumKey, szKey);

      dwSize = MAX_PATH;
      }
   
   RegCloseKey(hEnumKey);
   }
else
   {
   return FALSE;
   }

RegDeleteKey(hKey, pszSubKey);

return TRUE;
}

