// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------
#define _WIN32_WINNT 0x0400
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <WindowsX.h>

#include <initguid.h>

// {37824810-ADBA-11d1-B6FB-00A024A85A1F}
DEFINE_GUID(CLSID_NoneCancelObject, 0x37824810, 0xadba, 0x11d1, 0xb6, 0xfb, 0x0, 0xa0, 0x24, 0xa8, 0x5a, 0x1f);

// {37824811-ADBA-11d1-B6FB-00A024A85A1F}
DEFINE_GUID(CLSID_STACancelObject, 0x37824811, 0xadba, 0x11d1, 0xb6, 0xfb, 0x0, 0xa0, 0x24, 0xa8, 0x5a, 0x1f);

// {37824812-ADBA-11d1-B6FB-00A024A85A1F}
DEFINE_GUID(CLSID_MTACancelObject, 0x37824812, 0xadba, 0x11d1, 0xb6, 0xfb, 0x0, 0xa0, 0x24, 0xa8, 0x5a, 0x1f);

long	g_Count;
typedef struct tagCONSOLEDATA
{
	int x;
	int y;
} CONSOLEDATA;

CRITICAL_SECTION g_cs;
CONSOLEDATA g_ConsoleData;

// %%Classes: ----------------------------------------------------------------

// simple class-factory: only knows how to create CSimpleObject instances
class CClassFactory : public IClassFactory 
{
  public:
    // IUnknown
    STDMETHODIMP    QueryInterface (REFIID riid, void** ppv);
    STDMETHODIMP_(ULONG) AddRef(void)  { return 2; };
    STDMETHODIMP_(ULONG) Release(void) { return 1; }

    // IClassFactory
    STDMETHODIMP    CreateInstance (LPUNKNOWN punkOuter, REFIID iid, void **ppv);
    STDMETHODIMP    LockServer (BOOL fLock) { fLock ? InterlockedIncrement(&g_Count): InterlockedDecrement(&g_Count); return S_OK;}

    CClassFactory()  { }

  private:
    };

class CSimpleObject : public IPersist
{
  public:
    // IUnknown
    STDMETHODIMP    QueryInterface (REFIID iid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void)  {InterlockedIncrement(&m_cRef);return m_cRef;}
    STDMETHODIMP_(ULONG) Release(void) { 
		if (InterlockedDecrement(&m_cRef) == 0) 
		{ delete this; return 0;}
		else
			return m_cRef;
	}

    // IPersist
    STDMETHODIMP    GetClassID(CLSID *pClsID);
	
    // constructors/destructors
    CSimpleObject()     { 
		m_cRef = 1; 
		xy.X = 0; 
		xy.Y = (short)g_ConsoleData.y;
		InterlockedIncrement(&g_Count);
		hConsole = CreateFile(TEXT("CONOUT$"), GENERIC_READ|GENERIC_WRITE, 
			FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (INVALID_HANDLE_VALUE == hConsole)
			hConsole = 0;	
	}
    ~CSimpleObject()    { InterlockedDecrement(&g_Count); if (hConsole) CloseHandle(hConsole);}
    STDMETHODIMP    WasteTime(TCHAR *szMessage);

  private:
    LONG        m_cRef;
	COORD       xy;
	HANDLE hConsole;

    };

// %%Globals: ----------------------------------------------------------------

CClassFactory   g_ClassFactory;
HINSTANCE		g_hInstance;

BOOL WINAPI DllMain(HINSTANCE hDLLInst, DWORD fdwReason, LPVOID lpvReserved)
{
	UNREFERENCED_PARAMETER(lpvReserved);
	switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
			 g_hInstance = hDLLInst;
			 InitializeCriticalSection(&g_cs);
			 break;
        case DLL_THREAD_ATTACH:
			break;
        case DLL_THREAD_DETACH:
			break;
        case DLL_PROCESS_DETACH:
			 DeleteCriticalSection(&g_cs);
			 _tprintf(TEXT("\n going..going..gone\n"));
			 break;
		default:
			break;
	}
    return TRUE;
}

// ---------------------------------------------------------------------------
// %%Function: Message
// 
//  Formats and displays a message to the console.
// ---------------------------------------------------------------------------
void
Message(LPTSTR szPrefix, HRESULT hr)
{
    LPTSTR   szMessage;
	TCHAR szDisplay[1000];

    if (hr == S_OK)
        {
		_stprintf(szDisplay, TEXT("%s"), szPrefix);
		MessageBox(0, szDisplay, TEXT("Msg"),MB_SERVICE_NOTIFICATION);    
        return;
        }
 
    if (HRESULT_FACILITY(hr) == FACILITY_WIN32)
        hr = HRESULT_CODE(hr);

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
        (LPTSTR)&szMessage,
        0,
        NULL );

    _stprintf(szDisplay, TEXT("%s: %s(%lx)"), szPrefix, szMessage, hr);
	MessageBox(0, szDisplay, TEXT("Service:Msg"),MB_SERVICE_NOTIFICATION);    
    LocalFree(szMessage);
}  // Message


// ---------------------------------------------------------------------------
// %%Function: CSimpleObject::QueryInterface
// ---------------------------------------------------------------------------
 STDMETHODIMP
CSimpleObject::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == NULL)
        return E_INVALIDARG;
    *ppv = NULL;
    if (riid == IID_IUnknown || riid == IID_IPersist)
    {
        *ppv =  this;
        ((IUnknown*)*ppv)->AddRef();
        return S_OK;
	}

    return E_NOINTERFACE;
}  // CSimpleObject::QueryInterface

STDMETHODIMP Busy(HANDLE hConsole, COORD& xy, int nIter)
{
	HRESULT hr = S_OK;
	SetConsoleCursorPosition(hConsole, xy);
	TCHAR *szMessage = TEXT("!!!Call cancelled!!!");
	TCHAR *szBuf[4]={TEXT("|"), TEXT("/"), TEXT("-"), TEXT("\\")};
	for (int i = 0; i < nIter; i++)
	{
		WriteConsole(hConsole, szBuf[0], 1, NULL, NULL);
		SetConsoleCursorPosition(hConsole, xy);
		WriteConsole(hConsole, szBuf[1], 1, NULL, NULL);
		SetConsoleCursorPosition(hConsole, xy);
		WriteConsole(hConsole, szBuf[2], 1, NULL, NULL);
		SetConsoleCursorPosition(hConsole, xy);
		WriteConsole(hConsole, szBuf[3], 1, NULL, NULL);
		SetConsoleCursorPosition(hConsole, xy);
		if (RPC_E_CALL_CANCELED == CoTestCancel())
		{
			hr = RPC_E_CALL_CANCELED;
			WriteConsole(hConsole, szMessage, lstrlen(szMessage), NULL, NULL);
			break;
		}
	}
	return hr;
}
 
STDMETHODIMP
CSimpleObject::WasteTime(TCHAR *szMessage)
{
	if (hConsole)
	{
		SetConsoleCursorPosition(hConsole, xy);
		WriteConsole(hConsole, szMessage, lstrlen(szMessage), NULL, NULL);
		xy.X += 50;
		return Busy(hConsole, xy, 5000);
	}
	return S_OK;
}


STDMETHODIMP
CSimpleObject::GetClassID(CLSID *pClsID)
{
	UNREFERENCED_PARAMETER(pClsID);
	MessageBeep(0);
	xy.X = 0;
	return WasteTime(TEXT("In Call                               "));
}
 
// ---------------------------------------------------------------------------
// %%Function: CClassFactory::QueryInterface
// ---------------------------------------------------------------------------
 STDMETHODIMP
CClassFactory::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == NULL)
        return E_INVALIDARG;
    if (riid == IID_IClassFactory || riid == IID_IUnknown)
        {
        *ppv = (IClassFactory *) this;
        AddRef();
        return S_OK;
        }
    *ppv = NULL;
    return E_NOINTERFACE;
}  // CClassFactory::QueryInterface

// ---------------------------------------------------------------------------
// %%Function: CClassFactory::CreateInstance
// ---------------------------------------------------------------------------

 STDMETHODIMP
CClassFactory::CreateInstance(LPUNKNOWN punkOuter, REFIID riid, void** ppv)
{
	HRESULT hr = S_OK;
    *ppv = NULL;
	CSimpleObject *p;

    if (punkOuter != NULL)
        return CLASS_E_NOAGGREGATION;
	EnterCriticalSection(&g_cs);
	g_ConsoleData.y++;
	p = new CSimpleObject;
	LeaveCriticalSection(&g_cs);
    if (p == NULL)
        return E_OUTOFMEMORY;
	if (RPC_E_CALL_CANCELED == p->WasteTime(TEXT("Creating Object")))
	{
		p->Release();
		return hr;
	}
    hr = p->QueryInterface(riid, ppv);
	p->Release();
	return hr;
}  // CClassFactory::CreateInstance


STDAPI DllCanUnloadNow()
{
	if (g_Count == 0)
	{
		return S_OK ;
	}
	else
	{
		return S_FALSE ;
	}
}

STDAPI DllGetClassObject(const CLSID& clsid,
                         const IID& iid,
                         void** ppv)
{

	// Can we create this component?
	if ( (clsid != CLSID_NoneCancelObject) && (clsid != CLSID_STACancelObject) &&
		 (clsid != CLSID_MTACancelObject)) 
	{
		return CLASS_E_CLASSNOTAVAILABLE ;
	}
	HRESULT hr =  g_ClassFactory.QueryInterface(iid, ppv) ;
	return hr ;
}

