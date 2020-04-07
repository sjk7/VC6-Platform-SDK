/* Copyright 1992 - 2000 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
*/

#include <windows.h>
#include <winbase.h>
#include <tchar.h>
#include <conio.h>
#include <iostream.h>
#include "component.hxx"

DWORD g_dwRegisterClass;
HANDLE g_hEvent;

const char *g_RegTable[][3] = {
    { "CLSID\\{84f2059a-d9ae-11d2-86a3-00c04f8ef940}",0, "PipeSample" },
    { "CLSID\\{84f2059a-d9ae-11d2-86a3-00c04f8ef940}\\LocalServer32",0,
      (const char*)-1}
    };
    

STDAPI UnRegisterServer()
{
    HRESULT hr = S_OK;

    int nEntries = sizeof(g_RegTable)/sizeof(*g_RegTable);
    for (int i=nEntries -1; i >=0; i--) {
        long err = RegDeleteKeyA(HKEY_CLASSES_ROOT, g_RegTable[i][0]);
        if ( ERROR_SUCCESS != err ) hr=S_FALSE;
    }
    return hr;
}

STDAPI RegisterServer()
{
    HRESULT hr = S_OK;
    HINSTANCE hInstance = 0;
    char szFileName[1000];
    GetModuleFileNameA(hInstance, szFileName, 1000);
    
    int nEntries = sizeof(g_RegTable)/sizeof(*g_RegTable);
    for (int i=0; SUCCEEDED(hr) && i < nEntries; i++) {
        const char *pszKeyName = g_RegTable[i][0];
        const char *pszValueName = g_RegTable[i][1];
        const char *pszValue = g_RegTable[i][2];

        if (pszValue == (const char*)-1) pszValue = szFileName;
        HKEY hKey;
        long err = RegCreateKeyA(HKEY_CLASSES_ROOT, pszKeyName, &hKey);
        if ( ERROR_SUCCESS == err ) {
           err = RegSetValueExA(hKey, pszValueName, 0, REG_SZ, (const BYTE*)pszValue, (strlen(pszValue) + 1));
           RegCloseKey(hKey);
        }
        if ( ERROR_SUCCESS != err ) {
           UnRegisterServer();
           hr = E_FAIL;  // Need to be specific here
        }
     }
     return hr;
}

/*************************************************************************
* WinMain
*
* Program Entry point
*************************************************************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE nPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HRESULT hr;
    MSG msg;

    hr=CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
       return hr;

    // Creating a console...

    //AllocConsole();
    //HANDLE hConsoleOutput;
    //hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    //const TCHAR* lpBuffer1 = __TEXT("First Output for console \n");
    //const TCHAR* lpBuffer2 = __TEXT("Second Output for console \n");

    //WriteConsole(hConsoleOutput, lpBuffer1, strlen(lpBuffer1), 0, NULL);
    //WriteConsole(hConsoleOutput, lpBuffer2, strlen(lpBuffer2), 0, NULL);

    //FreeConsole();


    if ( 0 != strstr(lpCmdLine, "/RegServer") ||
         0 != strstr(lpCmdLine, "-RegServer")  ) {
       hr = RegisterServer();
       MessageBox(NULL, NULL, TEXT("PIPE SAMPLE SERVER REGISTERED"), MB_SETFOREGROUND);
       CoUninitialize();
       return 0;
    }
    else if ( 0 != strstr(lpCmdLine, "/UnRegServer") ||
              0 != strstr(lpCmdLine, "-UnRegServer")  ) {
            hr = UnRegisterServer();
            MessageBox(NULL, NULL, TEXT("PIPE SAMPLE SERVER UN-REGISTERED"), MB_SETFOREGROUND);
            CoUninitialize();
            return 0;
    }

    CFactory* pCFactory = new CFactory();

    hr=CoRegisterClassObject(CLSID_SimpleClass, pCFactory, CLSCTX_LOCAL_SERVER, REGCLS_SUSPENDED, &g_dwRegisterClass);
    hr=CoResumeClassObjects();
    
    if (FAILED(hr)) {
       MessageBox(NULL, TEXT("Failed to register the class object with the SCM"), TEXT("ERROR"), MB_SETFOREGROUND);
    }
    else
    {
       while (GetMessage(&msg, NULL, 0, 0)) {
          DispatchMessage(&msg);
       } 
       CoRevokeClassObject(g_dwRegisterClass);
    }
    delete pCFactory;

    CoUninitialize();
    return 0;
}