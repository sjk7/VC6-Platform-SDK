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
#if !defined(__CEVENT__)
#define __CEVENT__

#include <objidl.h>
#include "..\Server\unk.h"
#include "..\Server\debug.h"
#include "proxy.h"

class CEvent : public AppEvents
{
public:

	DWORD m_cRef;

	CEvent() : m_cRef(0)
	{
		DEBUGTRACE(_T("In CEvent ctor"));
	}


	~CEvent()
	{
		DEBUGTRACE(_T("In CEvent dtor"));
	}

	DECLARE_UNKNOWN

	HRESULT __stdcall Beep(short alert)
	{
		Sleep(1500);
		MessageBeep(alert);
		MessageBox(NULL, "Beep!", "DCOM Test Client", MB_OK);
		return S_OK;
	}
};

HRESULT __stdcall CEvent::QueryInterface(REFIID iid, PVOID *ppObj)
	{
#if defined(_DEBUG)
		LPWSTR lpstrIID;
		StringFromIID(iid, &lpstrIID);
		DEBUGTRACE(_TEXT("CEvent::QueryInterface has been asked for %S"), lpstrIID);
		CoTaskMemFree(lpstrIID);
#endif

		if (iid == IID_IUnknown || iid == IID_AppEvents)
			*ppObj = (AppEvents*)this;
		else
		{
			*ppObj = NULL;
			return E_NOINTERFACE;
		}

		if (*ppObj) 
			reinterpret_cast<LPUNKNOWN>(*ppObj)->AddRef();
		
		return S_OK;
	}

void __stdcall CEvent::FinalRelease()
	{
		DEBUGTRACE(_T("CEvent::FinalRelease called"));
		return;
	}

#endif // __CEVENT__

