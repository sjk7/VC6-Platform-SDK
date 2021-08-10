//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       CMGR.CPP
//  Content:    Conference Manager Routines
//              
//
//  Copyright (c) Microsoft Corporation 1995-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include "precomp.h"
#include <atlbase.h>

// There should be only one conference manager
INmManager * g_pMgr  = NULL;

CMgrNotify * g_pMgrNotify = NULL;


// {D29A8C50-774F-11d0-8B1D-00A0C91BC90E}
const GUID g_guid = 
{ 0xd29a8c51, 0x774f, 0x11d0, { 0x8b, 0x1d, 0x0, 0xa0, 0xc9, 0x1b, 0xc9, 0xe} };

const GUID g_guidNMUIChat =
// {9F7F48B5-4A97-11d3-A12D-00C04F79C1D9}
{ 0x9f7f48b5, 0x4a97, 0x11d3, { 0xa1, 0x2d, 0x0, 0xc0, 0x4f, 0x79, 0xc1, 0xd9 } };

HRESULT InitializeNm(void)
{
	HRESULT hr			= NO_ERROR;
	ULONG	uchCaps		= 0;
	ULONG	uOptions	= (ULONG) gPref.iInit;

	hr = g_pMgr->Initialize(&uOptions, &uchCaps);
	TRACE_MSG(TEXT("CConfMgr result=%s uOptions=%08X"), GetHrSz(hr), uOptions);

	return hr;
}


//****************************************************************************
//
// HRESULT InitConfMgr(void)
//
//****************************************************************************

HRESULT InitConfMgr(void)
{
	HRESULT			hr	= NO_ERROR;
	LPCLASSFACTORY	pcf	= NULL;

    // Notify the system we want to use the conferencing services
    // by creating a conference manager object
    hr = CoGetClassObject(CLSID_NmManager,
                          CLSCTX_INPROC,
                          NULL,
                          IID_IClassFactory,
                          (void**)&pcf);
    if (FAILED(hr))
    {
    	ERROR_MSG(TEXT("CoGetClassObject Failed (%s)"), GetHrSz(hr));
    }
	else if (NULL == pcf)
	{
		ERROR_MSG(TEXT("CoGetClassObject Succeeded but returned a Null Ptr"));
		hr	= E_POINTER;
	}
    else
    {
        // Get the conference manager object
        hr = pcf->CreateInstance(NULL, IID_INmManager, (void**)&g_pMgr);
        if (FAILED(hr))
        {
	    	ERROR_MSG(TEXT("CreateInstance Failed (%s)"), GetHrSz(hr));
        }
        else if (NULL == g_pMgr)
		{
			ERROR_MSG(TEXT("CreateInstance Succeeded but returned a Null Ptr"));
			hr	= E_POINTER;
		}
		else
        {
            // Connect to the conference manager object
            g_pMgrNotify = new CMgrNotify();
            if (g_pMgrNotify == NULL)
            {
                hr = E_OUTOFMEMORY;
		    	ERROR_MSG(TEXT("CConfMgrNotify: out of memory!"));
            }
            else
            {
                hr = g_pMgrNotify->Connect(g_pMgr);
                if (FAILED(hr))
                {
			    	ERROR_MSG(TEXT("CConfMgrNotify Failed (%s)"), GetHrSz(hr));
                    g_pMgrNotify->Release();
                    g_pMgrNotify = NULL;
                }
                else
                {
					DumpSysInfo();
                	hr = InitializeNm();
                	DumpLaunchInfo();
				}
            }
        }

        pcf->Release();
    }

	if	FAILED(hr)
	{
		FreeConfMgr();
	}

	return hr;
}

//****************************************************************************
//
// VOID FreeConfMgr(void)
//
//****************************************************************************

VOID FreeConfMgr(void)
{
	// Release conference manager notify
	if (NULL != g_pMgrNotify)
	{
		OBJECT_MSG(TEXT("Freeing g_pMgrNotify"));
		g_pMgrNotify->Disconnect();
		g_pMgrNotify->Release();
		g_pMgrNotify = NULL;
	}

	// Release conference manager
	if (NULL != g_pMgr)
	{
		OBJECT_MSG(TEXT("Freeing g_pMgr"));
		g_pMgr->Release();
		g_pMgr = NULL;
	}
}

//****************************************************************************
//
// CLASS CMgrNotify
//
//****************************************************************************

CMgrNotify::CMgrNotify() : RefCount(), CNotify()
{
	OBJECT_MSG(TEXT("CMgrNotify created"));
}

CMgrNotify::~CMgrNotify()
{
	OBJECT_MSG(TEXT("CMgrNotify destroyed"));
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CMgrNotify::AddRef(void)
{
	return RefCount::AddRef();
}


ULONG STDMETHODCALLTYPE CMgrNotify::Release(void)
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CMgrNotify::QueryInterface(REFIID riid, PVOID *ppvObject)
{
	if	(NULL == ppvObject)
		return E_POINTER;

	HRESULT hr = S_OK;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
		OBJECT_MSG(TEXT("CMgrNotify::QueryInterface(): Returning IUnknown."));
	}
	else if (riid == IID_INmManagerNotify)
	{
		*ppvObject = (INmManagerNotify *)this;
		OBJECT_MSG(TEXT("CMgrNotify::QueryInterface(): Returning INmManagerNotify."));
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
		OBJECT_MSG(TEXT("CMgrNotify::QueryInterface(): Called on unknown interface."));
	}

	if SUCCEEDED(hr)
	{
		AddRef();
	}

	return hr;
}



//****************************************************************************
//
// Methods from ICNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CMgrNotify::Connect(IUnknown *pUnk)
{
	return CNotify::Connect(pUnk, IID_INmManagerNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE CMgrNotify::Disconnect(void)
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// Methods from INmManagerNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CMgrNotify::NmUI(CONFN confn)
{
	NOTIFY_MSG(TEXT("CMgrNotify::NmUI"));
	TRACE_MSG(TEXT("CONFN=%s"), GetConfnSz(confn));
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMgrNotify::CallCreated(INmCall *pCall)
{
	if	(NULL == pCall)
	{
		ERROR_MSG(TEXT("CMgrNotify::CallCreated: NULL == pCall"));
		return E_POINTER;
	}

	BYTE	* ppb	= NULL;
	ULONG	  pcb	= 0;

	const GUID guid = { 0x068b0780, 0x718c, 0x11d0,{ 0x8b, 0x1a, 0x0, 0xa0, 0xc9, 0x1b, 0xc9, 0x0e}};	 
	
	NOTIFY_MSG(TEXT("CMgrNotify::CallCreated"));
	
	pCall->GetUserData(GUID_NULL, (BYTE**) &ppb, &pcb);

	DumpCallInfo(pCall);
	HookCall(pCall);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMgrNotify::ConferenceCreated(INmConference *pConference)
{
	if	(NULL == pConference)
	{
		ERROR_MSG(TEXT("CMgrNotify::ConferenceCreated: Null == pConference"));
		return E_POINTER;
	}

	NOTIFY_MSG(TEXT("CMgrNotify::ConferenceCreated"));
	
	DumpConferenceInfo(pConference);
	HookConference(pConference);

	return S_OK;
}


DWSTR _rgSysInfo[] = {
	{NM_SYSPROP_EMAIL_NAME,    TEXT("Email     ")},
	{NM_SYSPROP_SERVER_NAME,   TEXT("Server    ")},
	{NM_SYSPROP_RESOLVE_NAME,  TEXT("Resolve   ")},
	{NM_SYSPROP_FIRST_NAME,    TEXT("First Name")},
	{NM_SYSPROP_LAST_NAME,     TEXT("Last Name ")},
	{NM_SYSPROP_USER_NAME,     TEXT("Name      ")},
	{NM_SYSPROP_USER_CITY,     TEXT("City      ")},
	{NM_SYSPROP_USER_COUNTRY,  TEXT("Country   ")},
	{NM_SYSPROP_USER_COMMENTS, TEXT("Comments  ")},
	{NM_SYSPROP_USER_CATEGORY, TEXT("Category  ")},
	{NM_SYSPROP_INSTALL_DIRECTORY, TEXT("Directory ")},
	{NM_SYSPROP_APP_NAME,      TEXT("App Name  ")},
	{NM_SYSPROP_IS_RUNNING,    TEXT("Is Running")},
	{NM_SYSPROP_IN_CONFERENCE, TEXT("In Conference")},
	{NM_SYSPROP_H323_GATEWAY,  TEXT("H323 Gateway ")},
	{NM_SYSPROP_H323_GATEWAY_ENABLE, TEXT("H323 Enable  ")},
	{NM_SYSPROP_LOGGED_ON,     TEXT("Logged on    ")},
	{200,					   TEXT("Build Ver   ")},
};


//****************************************************************************
//
// VOID DumpSysInfo(void)
//
//****************************************************************************

VOID DumpSysInfo(void)
{
	HRESULT		  hr		= NO_ERROR;
	INmSysInfo	* pSysInfo	= 0;

	if (NULL == g_pMgr)
		return;

	if (FAILED(g_pMgr->GetSysInfo(&pSysInfo)))
	{
		return;
	}

	hr = pSysInfo->IsInstalled();

	TRACE_MSG(TEXT("NetMeeting IsInstalled (%s)"), GetHrSz(hr));

	TRACE_MSG(TEXT("--- NetMeeting System Information ---"));

	for (int i = 0; i < ARRAY_ELEMENTS(_rgSysInfo); i++)
	{
		BSTR bstr	= NULL;
		hr = pSysInfo->GetProperty((NM_SYSPROP)_rgSysInfo[i].dw, &bstr);
		if FAILED(hr)
		{
			TRACE_MSG(TEXT("%s: HRESULT = %s"), _rgSysInfo[i].psz, GetHrSz(hr));
		}
		else
		{
			LPTSTR psz = PszFromBstr(bstr);
			TRACE_MSG(TEXT("%s = [%s]"), _rgSysInfo[i].psz, psz);
			FreePlpv(&psz);
			SysFreeString(bstr);
		}
	}
	TRACE_MSG(TEXT("--- NetMeeting System Information ---"));

	ULONG nmch	= 0;
	hr = pSysInfo->GetNmchCaps(&nmch);

	HRESULT hrInstalled = pSysInfo->IsInstalled();
	TRACE_MSG(TEXT("Installed=%s, Caps=%08X  hr=%s"), GetHrSz(hrInstalled), nmch, GetHrSz(hr));

	BSTRING bstr(TEXT("1"));
	if	(NULL == bstr.GetLPBSTR())
	{
		ERROR_MSG(TEXT("DumpSysInfo: NULL == bstr"));
	}
	else
	{
		hr = pSysInfo->SetProperty(NM_SYSPROP_DISABLE_INITIAL_ILS_LOGON, bstr);
	}

	pSysInfo->Release();

	DumpAllCalls();
}


//****************************************************************************
//
// VOID DumpLaunchInfo(void)
//
//****************************************************************************

VOID DumpLaunchInfo(void)
{
	HRESULT			  hr			= NO_ERROR	;
	INmSysInfo		* pSysInfo		= NULL		;
	INmConference	* pConference	= NULL		;
	INmMember		* pMember		= NULL		;

	if (NULL == g_pMgr)
		return;

	if (FAILED(g_pMgr->GetSysInfo(&pSysInfo)))
	{
		return;
	}

	GUID g = IID_INmSysInfo;

	hr = pSysInfo->SetUserData(g, reinterpret_cast<byte*>(&g), sizeof(g));
	if(SUCCEEDED(hr))
	{

		BYTE* pb	= 0;
		ULONG ul	= 0;
		if	SUCCEEDED(hr = pSysInfo->GetUserData(g, &pb, &ul))
		{
			ASSERT(ul == sizeof(g));
			ASSERT(0 == memcmp(pb, &g, ul));

			CoTaskMemFree(pb);
		}
		else
		{
			ERROR_MSG(TEXT("DumpLaunchInfo: pSysInfo->GetUserData returned 0x%08X"), hr);
		}
	}

	hr = pSysInfo->GetLaunchInfo(&pConference, &pMember);
	TRACE_MSG(TEXT("GetLaunchInfo: (%s) Conference=%08X Member=%08X"), GetHrSz(hr), pConference, pMember);

	if (NULL != pConference)
		pConference->Release();

	if (NULL != pMember)
		pMember->Release();
	
	pSysInfo->Release();
}


//****************************************************************************
//
// VOID SysLogOnOff(int iDirection)
//
//****************************************************************************

VOID SysLogOnOff(int iDirection)
{
	HRESULT		  hr			= NO_ERROR	;
	INmSysInfo	* pSysInfo		= NULL		;
	BSTRING		  bstrDirection				;
	BSTR		  bstrServer	= NULL		;

	if (NULL == g_pMgr)
		return;

	if (FAILED(g_pMgr->GetSysInfo(&pSysInfo)))
	{
		TRACE_MSG(TEXT("NetMeeting GetSysInfo failed"));
		return;
	}

	hr = pSysInfo->GetProperty(NM_SYSPROP_IS_RUNNING, &bstrServer);
	if(FAILED(hr))
		TRACE_MSG(TEXT("NetMeeting GetProperty [Is Running] (%s) "), GetHrSz(hr));

	if	(NULL != bstrServer)
	{
		::SysFreeString(bstrServer);
		bstrServer = NULL;
	}


	hr = pSysInfo->GetProperty(NM_SYSPROP_SERVER_NAME, &bstrServer);
	if(FAILED(hr))
		TRACE_MSG(TEXT("NetMeeting GetProperty [ServerName] (%s) "), GetHrSz(hr));
	else
		TRACE_MSG(TEXT("Server is %s"), PszFromBstr(bstrServer));

	if	(NULL != bstrServer)
	{
		::SysFreeString(bstrServer);
		bstrServer = NULL;
	}

	bstrDirection = (iDirection==LOGON ? BSTRING(TEXT("1")) : BSTRING(TEXT("0")));

	hr = pSysInfo->SetProperty(NM_SYSPROP_LOGGED_ON, bstrDirection);

	TRACE_MSG(TEXT("NetMeeting SetProperty [Logon/Logoff] (%s)"), GetHrSz(hr));

	pSysInfo->Release();
}



