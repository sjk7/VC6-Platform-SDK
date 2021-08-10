//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       DEBUG.CPP
//  Content:    
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
#include <atlconv.h>


#define STRING_CASE(val)               case val: pcsz = TEXT(#val); break

//****************************************************************************
//
// LPCTSTR GetHrSz(HRESULT hr)
//
//****************************************************************************

LPCTSTR GetHrSz(HRESULT hr)
{
	LPCTSTR pcsz	= NULL;
	static TCHAR _szHRESULT[128];

	switch (hr)
		{
	STRING_CASE(S_OK);
	STRING_CASE(S_FALSE);

	STRING_CASE(NM_E_NOT_INITIALIZED);
	STRING_CASE(NM_E_CHANNEL_ALREADY_EXISTS);
	STRING_CASE(NM_E_NO_T120_CONFERENCE);
	STRING_CASE(NM_E_NOT_ACTIVE);

	STRING_CASE(DRAGDROP_S_CANCEL);
	STRING_CASE(DRAGDROP_S_DROP);
	STRING_CASE(DRAGDROP_S_USEDEFAULTCURSORS);

	STRING_CASE(E_UNEXPECTED);
	STRING_CASE(E_NOTIMPL);
	STRING_CASE(E_OUTOFMEMORY);
	STRING_CASE(E_INVALIDARG);
	STRING_CASE(E_NOINTERFACE);
	STRING_CASE(E_POINTER);
	STRING_CASE(E_HANDLE);
	STRING_CASE(E_ABORT);
	STRING_CASE(E_FAIL);
	STRING_CASE(E_ACCESSDENIED);

	STRING_CASE(CLASS_E_NOAGGREGATION);

	STRING_CASE(CO_E_NOTINITIALIZED);
	STRING_CASE(CO_E_ALREADYINITIALIZED);
	STRING_CASE(CO_E_INIT_ONLY_SINGLE_THREADED);

	STRING_CASE(REGDB_E_INVALIDVALUE);
	STRING_CASE(REGDB_E_CLASSNOTREG);
	STRING_CASE(REGDB_E_IIDNOTREG);

	STRING_CASE(DV_E_DVASPECT);
	STRING_CASE(DV_E_LINDEX);
	STRING_CASE(DV_E_TYMED);
	STRING_CASE(DV_E_FORMATETC);

	default:
		ZeroMemory(_szHRESULT, 128 * sizeof(TCHAR));
		_sntprintf(_szHRESULT, 127, TEXT("%#lx\0"), hr);
		pcsz = _szHRESULT;
		break;
		}

	return pcsz;
}


//****************************************************************************
//
// LPCTSTR GetConfnSz(CONFN confn)
//
//****************************************************************************

LPCTSTR GetConfnSz(CONFN confn)
{
	LPCTSTR pcsz	= NULL;
	static TCHAR _szMsg[256];

	switch (confn)
		{
	STRING_CASE(CONFN_FT_UI);
	STRING_CASE(CONFN_FT_OFFERED);
	STRING_CASE(CONFN_FT_STARTED);
	STRING_CASE(CONFN_FT_PROGRESS);
	STRING_CASE(CONFN_FT_COMPLETE);
	STRING_CASE(CONFN_FT_CANCELED);
	
	STRING_CASE(CONFN_CALL_INCOMPATIBLE);
	STRING_CASE(CONFN_CALL_OLDER);
	STRING_CASE(CONFN_CALL_NEWER);
	STRING_CASE(CONFN_CALL_IGNORED);
	STRING_CASE(CONFN_CALL_FAILED);
	STRING_CASE(CONFN_CALL_IN_CONFERENCE);

	STRING_CASE(CONFN_NM_STARTED);
	STRING_CASE(CONFN_NM_STOPPED);

	default:
		ZeroMemory(_szMsg, 256 * sizeof(TCHAR));
		_sntprintf(_szMsg, 255, TEXT("CONFN_%08X\0"), confn);
		pcsz = _szMsg;
		break;
		}
	return pcsz;
}


//****************************************************************************
//
// LPCTSTR GetNmchSz(ULONG uch)
//
//****************************************************************************

LPCTSTR GetNmchSz(ULONG uch)
{
	LPCTSTR pcsz	= NULL;
	static TCHAR _szMsg[256];

	switch (uch)
		{
	case NMCH_DATA:  pcsz = TEXT("Data");  break;
	case NMCH_AUDIO: pcsz = TEXT("Audio"); break;
	case NMCH_VIDEO: pcsz = TEXT("Video"); break;
	case NMCH_SHARE: pcsz = TEXT("Share"); break;
	case NMCH_FT:    pcsz = TEXT("Ft");    break;
	
	case NMCH_ALL:
	case NMCH_NONE:
	default:
		ZeroMemory(_szMsg, 256 * sizeof(TCHAR));
		_sntprintf(_szMsg, 255, TEXT("%04X\0"), uch);
		pcsz = _szMsg;
		break;
		}
	return pcsz;
}


//****************************************************************************
//
// LPCTSTR GetCallStateSz(NM_CALL_STATE uState)
//
//****************************************************************************

LPCTSTR GetCallStateSz(NM_CALL_STATE uState)
{
	LPCTSTR pcsz	= NULL;
	static TCHAR _szMsg[256];

	switch (uState)
		{
	STRING_CASE(NM_CALL_INVALID);
	STRING_CASE(NM_CALL_INIT);
	STRING_CASE(NM_CALL_RING);
	STRING_CASE(NM_CALL_SEARCH);
	STRING_CASE(NM_CALL_WAIT);
	STRING_CASE(NM_CALL_ACCEPTED);
	STRING_CASE(NM_CALL_REJECTED);
	STRING_CASE(NM_CALL_CANCELED);

	default:
		ZeroMemory(_szMsg, 256 * sizeof(TCHAR));
		_sntprintf(_szMsg, 255, TEXT("NM_CALL_%04X\0"), uState);
		pcsz = _szMsg;
		break;
		}
	return pcsz;
}


//****************************************************************************
//
// LPCTSTR GetConferenceStateSz(NM_CONFERENCE_STATE uState)
//
//****************************************************************************

LPCTSTR GetConferenceStateSz(NM_CONFERENCE_STATE uState)
{
	LPCTSTR pcsz	= NULL;
	static TCHAR _szMsg[256];

	switch (uState)
		{
	STRING_CASE(NM_CONFERENCE_IDLE);
	STRING_CASE(NM_CONFERENCE_WAITING);
	STRING_CASE(NM_CONFERENCE_INITIALIZING);
	STRING_CASE(NM_CONFERENCE_ACTIVE);

	default:
		ZeroMemory(_szMsg, 256 * sizeof(TCHAR));
		_sntprintf(_szMsg, 255, TEXT("NM_CONFERENCE_%04X\0"), uState);
		pcsz = _szMsg;
		break;
		}
	return pcsz;
}

//****************************************************************************
//
// LPCTSTR GetCollaborationStateSz(NM_SHARE_STATE uState)
//
//****************************************************************************

LPCTSTR GetCollaborationStateSz(NM_SHARE_STATE uState)
{
	LPCTSTR pcsz	= NULL;
	static TCHAR _szMsg[256];

	switch (uState)
		{
	STRING_CASE(NM_SHARE_COLLABORATING);
	STRING_CASE(NM_SHARE_UNKNOWN);
	STRING_CASE(NM_SHARE_IN_CONTROL);
	STRING_CASE(NM_SHARE_WORKING_ALONE);

	default:
		ZeroMemory(_szMsg, 256 * sizeof(TCHAR));
		_sntprintf(_szMsg, 255, TEXT("NM_SHARE_%04X\0"), uState);
		pcsz = _szMsg;
		break;
		}
	return pcsz;
}
//****************************************************************************
//
// VOID FAR PASCAL AssertProc(LPTSTR lpszMsg, LPTSTR lpszAssert, LPTSTR lpszFile, UINT line)
//
//****************************************************************************

VOID FAR PASCAL AssertProc(LPTSTR lpszMsg, LPTSTR lpszAssert, LPTSTR lpszFile, UINT line)
{
	int  id	= 0;
	TCHAR szBuffer[1024]; // a big buffer
	ZeroMemory(szBuffer, 1024 * sizeof(TCHAR));

	_sntprintf(szBuffer, 1023, TEXT("Assert: %s\nFile %s, Line %d"),
		(lpszMsg && *lpszMsg) ? lpszMsg : lpszAssert,
		lpszFile ? lpszFile : TEXT(""), line);

#ifdef DEBUG
	OutputDebugString(szBuffer);
#endif

	do {
		id = MessageBox(NULL, szBuffer, TEXT("NmUi Assert"),
					MB_ICONHAND | MB_ABORTRETRYIGNORE | MB_SYSTEMMODAL);

		switch (id)
		{
		case IDRETRY:
			DebugBreak();
			break;
		case IDABORT:
			FatalAppExit(0, szBuffer);
			break;
		case IDIGNORE:
		default:
			break;
		}
	} while (id == IDRETRY);
}


//****************************************************************************
//
// VOID Log(COLORREF cv, LPTSTR pszMsg)
//
//****************************************************************************

VOID Log(COLORREF cv, LPTSTR pszMsg)
{
	int iItem	= SendMessage(ghwndMsg, LB_ADDSTRING, 0, (LPARAM) pszMsg);

	SendMessage(ghwndMsg, LB_SETITEMDATA, (WPARAM)iItem, (LPARAM) cv);

	PostMessage(ghwndMsg, WM_VSCROLL, SB_BOTTOM, 0);
}

//****************************************************************************
//
// VOID ClearLog(void)
//
//****************************************************************************

VOID ClearLog(void)
{
	SendMessage(ghwndMsg, LB_RESETCONTENT, 0, 0);
}


//****************************************************************************
//
// VOID TraceMsg(PSTR pszFormat,...)
//
//****************************************************************************

VOID TraceMsg(LPTSTR ptszFormat,...)
{

	TCHAR szMsg[1024];
	va_list v1;
	
	ZeroMemory(szMsg, 1024 * sizeof(TCHAR));

	va_start(v1, ptszFormat);
	_vsntprintf(szMsg, 1023, ptszFormat, v1);
	va_end(v1);

	Log(RGB(0, 0, 0), szMsg);

#ifdef DEBUG
	OutputDebugString(szMsg);
	OutputDebugString(TEXT("\r\n"));
#endif
}


//****************************************************************************
//
// VOID WarnMsg(PSTR pszFormat,...)
//
//****************************************************************************

VOID WarnMsg(LPTSTR ptszFormat,...)
{
	TCHAR szMsg[1024];
	va_list v1;

	ZeroMemory(szMsg, 1024 * sizeof(TCHAR));
	
	va_start(v1, ptszFormat);
	_vsntprintf(szMsg, 1023, ptszFormat, v1);
	va_end(v1);

	Log(RGB(0, 0, 255), szMsg);

#ifdef DEBUG
	OutputDebugString(szMsg);
	OutputDebugString(TEXT("\r\n"));
#endif
}


//****************************************************************************
//
// VOID ErrorMsg(PSTR pszFormat,...)
//
//****************************************************************************

VOID ErrorMsg(LPTSTR ptszFormat,...)
{
	TCHAR szMsg[1024];
	va_list v1;
	
	ZeroMemory(szMsg, 1024 * sizeof(TCHAR));

	va_start(v1, ptszFormat);
	_vsntprintf(szMsg, 1023, ptszFormat, v1);
	va_end(v1);

	Log(RGB(255, 0, 0), szMsg);

#ifdef DEBUG
	OutputDebugString(szMsg);
	OutputDebugString(TEXT("\r\n"));
#endif
}


//****************************************************************************
//
// VOID LogMsg(COLORREF cv, PSTR pszFormat,...)
//
//****************************************************************************

VOID LogMsg(COLORREF cv, LPTSTR tszFormat,...)
{
	TCHAR tszMsg[1024];
	va_list v1;

	ZeroMemory(tszMsg, 1024 * sizeof(TCHAR));
	
	va_start(v1, tszFormat);
	_vsntprintf(tszMsg, 1023, tszFormat, v1);
	va_end(v1);

	Log(cv, tszMsg);

#ifdef DEBUG
	OutputDebugString(tszMsg);
	OutputDebugString(TEXT("\r\n"));
#endif
}


//****************************************************************************
//
// VOID DumpCallInfo(INmCall * pCall)
//
//****************************************************************************

VOID DumpCallInfo(INmCall * pCall)
{
	HRESULT			  hr			= NO_ERROR	;
	BSTR			  bstrName		= NULL		;
	BSTR			  bstrAddr		= NULL		;
	NM_ADDR_TYPE	  uType						;
	NM_CALL_STATE	  uState					;
	INmConference	* pConference	= NULL		;

	OBJECT_MSG(TEXT("[%08X] - dump call info"), pCall);
	if (NULL == pCall)
	{
		ERROR_MSG(TEXT("DumpCallInfo: Invalid Call"));
		return;
	}

	hr = pCall->GetName(&bstrName);
	if (FAILED(hr))
	{
		bstrName = NULL;
    	ERROR_MSG(TEXT("DumpCallInfo: GetName failed"));
	}

	hr = pCall->GetAddr(&bstrAddr, &uType);
	if (FAILED(hr))
	{
		bstrAddr = NULL;
		uType = NM_ADDR_UNKNOWN; 
    	ERROR_MSG(TEXT("DumpCallInfo: GetAddr failed"));
	}

    if (FAILED(pCall->GetState(&uState)))
    {
		uState = NM_CALL_INVALID; 
    	ERROR_MSG(TEXT("DumpCallInfo: GetState failed"));
    }

	hr = pCall->GetConference(&pConference);
	if (FAILED(hr))
	{
    	WARN_MSG(TEXT("DumpCallInfo: GetConference failed %s"), GetHrSz(hr));
	}
	else if (NULL == pConference)
	{
		WARN_MSG(TEXT("DumpCallInfo: GetConference returned a null ptr"));
	}

	TRACE_MSG(TEXT("Call=[%s] Addr=[%s], Type=%d, State=%s %s conf=%08X"),
		(LPTSTR) BTSTR(bstrName), (LPTSTR) BTSTR(bstrAddr),
		uType, GetCallStateSz(uState),
		(S_OK == pCall->IsIncoming()) ? TEXT("(Incoming)") : TEXT(""), pConference);

	if (NULL != pConference)
	{
		pConference->Release();
		pConference = NULL;
	}

	SysFreeString(bstrName);
	SysFreeString(bstrAddr);
}


//****************************************************************************
//
// VOID DumpAllCalls(void)
//
//****************************************************************************

VOID DumpAllCalls(void)
{
	if (NULL == g_pListCall)
		return;

	for (POSITION pos = g_pListCall->GetHeadPosition(); NULL != pos; )
	{
		INmCall * pCall = (INmCall *) g_pListCall->GetNext(pos);
		DumpCallInfo(pCall);
	}
}


//****************************************************************************
//
// VOID DumpConferenceInfo(INmConference * pConference)
//
//****************************************************************************

VOID DumpConferenceInfo(INmConference * pConference)
{
	HRESULT				hr			= NO_ERROR	;
	BSTR				bstr		= NULL		;
	ULONG				cMember		= 0			;
	ULONG				cChannel	= 0			;
	NM_CONFERENCE_STATE	uState					;

	if (NULL == pConference)
	{
		ERROR_MSG(TEXT("DumpConferenceInfo: Invalid conference"));
		return;
	}

	hr = pConference->GetName(&bstr);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("GetName failed"));
		bstr = NULL;
	}
	
	hr = pConference->GetState(&uState);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("GetState failed?"));
	}
	
	hr = pConference->GetMemberCount(&cMember);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("GetMemberCount failed"));
		cMember = 0;
	}
	
	hr = pConference->GetChannelCount(&cChannel);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("GetChannelCount failed"));
		cChannel = 0;
	}
	
	TRACE_MSG(TEXT("[%08X] - Conference=[%s] state=%s"), pConference,
		(LPTSTR) BTSTR(bstr), GetConferenceStateSz(uState));
	TRACE_MSG(TEXT("  MemberCount=%d, ChannelCount=%d"), cMember, cChannel);

	SysFreeString(bstr);
}


//****************************************************************************
//
// VOID DumpMemberInfo(INmMember * pMember)
//
//****************************************************************************

VOID DumpMemberInfo(INmMember * pMember)
{
	HRESULT			hr			= NO_ERROR	;
	BSTR			bstr		= NULL		;
	BOOL			fLocal		= FALSE		;
	BOOL			fMcu		= FALSE		;
	BOOL			fTop		= FALSE		;
	ULONG			uchCaps		= 0			;
	ULONG			uVer		= 0			;
	INmConference *	pConference	= NULL		;

	if	(NULL == pMember)
	{
		ERROR_MSG(TEXT("DumpMemberInfo: NULL == pMember"));
		return;
	}

	hr = pMember->GetName(&bstr);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("Problem with GetName"));
	}

	hr = pMember->GetNmchCaps(&uchCaps);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("Problem with GetNmchCaps"));
		uchCaps = 0;
	}

	hr = pMember->GetNmVersion(&uVer);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("Problem with GetNmVersion"));
		uVer = 0;
	}

	fLocal = S_OK == pMember->IsSelf();
	fMcu = S_OK == pMember->IsMCU();

	fTop = FALSE;
	hr = pMember->GetConference(&pConference);
	if (FAILED(hr) || (NULL == pConference))
	{
		TRACE_MSG(TEXT("Problem with GetConference"));
	}
	else
	{
		INmMember * pMemberTop	= NULL;
		if (SUCCEEDED(pConference->GetTopProvider(&pMemberTop)) && (NULL != pMemberTop))
		{
			fTop = (pMember == pMemberTop);

			pMemberTop->Release();
			pMemberTop = NULL;
		}

		pConference->Release();
		pConference = NULL;
	}

	TRACE_MSG(TEXT("[%08X] Member=[%s] "), pMember, (LPTSTR) BTSTR(bstr));
	TRACE_MSG(TEXT("Local=%d, MCU=%d, Top=%d, uch=%08X, version=%d"), fLocal, fMcu, fTop, uchCaps, uVer);

	SysFreeString(bstr);
}


//****************************************************************************
//
// VOID DumpChannelInfo(INmChannel * pChannel)
//
//****************************************************************************

VOID DumpChannelInfo(INmChannel * pChannel)
{
	HRESULT	hr		= NO_ERROR;
	ULONG	uch		= 0;
	ULONG	cMember	= 0;

	if	(NULL == pChannel)
	{
		ERROR_MSG(TEXT("DumpChannelInfo: NULL == pChannel"));
		return;
	}

	hr = pChannel->GetNmch(&uch);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("GetNmch failed"));
		uch = 0;
	}
	
	hr = pChannel->GetMemberCount(&cMember);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("GetMemberCount failed"));
		cMember = 0;
	}

	TRACE_MSG(TEXT("[%08X] - Channel=[%s] MemberCount=%d"), pChannel, GetNmchSz(uch), cMember);
	switch (uch)
		{
	case NMCH_AUDIO:
	{
		INmChannelAudio * pChannelAudio	= NULL;
		hr = pChannel->QueryInterface(IID_INmChannelAudio, (void **)&pChannelAudio);
		if (FAILED(hr))
		{
			ERROR_MSG(TEXT("Not an audio channel?"));
		}
		else if (NULL == pChannelAudio)
		{
			ERROR_MSG(TEXT("DumpChannelInfo: NULL == pChannelAudio"));
		}
		else
		{
			NM_AUDIO_STATE uState	;
			pChannelAudio->GetState(&uState);
			TRACE_MSG(TEXT("Audio State: %d"), uState);
			pChannelAudio->Release();
			pChannelAudio = NULL;
		}
		break;
	}

	case NMCH_VIDEO:
		break;

	case NMCH_DATA:
	{
		INmChannelData * pChannelData	= NULL;
		hr = pChannel->QueryInterface(IID_INmChannelData, (void **)&pChannelData);
		if (FAILED(hr) || (NULL == pChannelData))
		{
			ERROR_MSG(TEXT("Not a data channel?"));
		}
		else
		{
			TRACE_MSG(TEXT("Data channel is %s"),
				(S_OK == pChannelData->IsActive()) ? TEXT("Active") : TEXT("Inactive"));
			pChannelData->Release();
			pChannelData = NULL;
		}
		break;
	}
	default:
		break;
		}
}

//****************************************************************************
//
// VOID DoEnumChannelMember(INmChannel * pChannel)
//
//****************************************************************************

VOID DoEnumChannelMember(INmChannel * pChannel)
{
	HRESULT			  hr		= NO_ERROR;
	IEnumNmMember	* pEnum		= NULL;
	ULONG			  cFetched	= 0;
	ULONG			  cMember	= 0;

	ASSERT(NULL != pChannel);
	if	(NULL == pChannel)
	{
		ERROR_MSG(TEXT("DoEnumChannelMember: NULL == pChannel"));
		return;
	}

	hr = pChannel->GetMemberCount(&cMember);
	if (FAILED(hr))
	{
    	ERROR_MSG(TEXT("GetMemberCount Failed (%s)"), GetHrSz(hr));
    	return;
	}
	TRACE_MSG(TEXT("%d members in channel (%08X)"), cMember, pChannel);

	if (0 == cMember)
		return;

	if (cMember > 10)
		cMember = 10;

	hr = pChannel->EnumMember(&pEnum);
	if (FAILED(hr))
	{
    	ERROR_MSG(TEXT("EnumMember Failed (%s)"), GetHrSz(hr));
    	return;
	}
	else if (NULL == pEnum)
	{
		ERROR_MSG(TEXT("EnumMember returned a Null ptr"));
		return;
	}

	INmMember * rgpMember[10];
	for	(int i = 0; i < 10; i++)
		rgpMember[i] = NULL;


	hr = pEnum->Next(cMember, rgpMember, &cFetched);
	if (FAILED(hr))
	{
    	ERROR_MSG(TEXT("EnumMember Failed (%s)"), GetHrSz(hr));
	}
	else
	{
		for (UINT iMember = 0; iMember < cFetched; iMember++)
		{
			DumpMemberInfo(rgpMember[iMember]);
			
			if	(NULL != rgpMember[iMember])
			{
				rgpMember[iMember]->Release();
				rgpMember[iMember] = NULL;
			}
		}
	}

	pEnum->Release();
	pEnum = NULL;
}


//****************************************************************************
//
// VOID DoEnumConferenceMember(INmConference * pConference)
//
//****************************************************************************

VOID DoEnumConferenceMember(INmConference * pConference)
{
	HRESULT			  hr		= NO_ERROR;
	IEnumNmMember	* pEnum		= NULL;
	ULONG			  cFetched	= 0;
	ULONG			  cMember	= 0;

	ASSERT(NULL != pConference);
	if	(NULL == pConference)
	{
		ERROR_MSG(TEXT("DoEnumConferenceMember: NULL == pConference"));
		return;
	}

	hr = pConference->GetMemberCount(&cMember);
	if (FAILED(hr))
	{
    	ERROR_MSG(TEXT("GetMemberCount Failed (%s)"), GetHrSz(hr));
    	return;
	}
	TRACE_MSG(TEXT("%d members in conference (%08X)"), cMember, pConference);

	if (cMember > 10)
		cMember = 10;

	hr = pConference->EnumMember(&pEnum);
	if (FAILED(hr))
	{
    	ERROR_MSG(TEXT("EnumMember Failed (%s)"), GetHrSz(hr));
    	return;
	}

	if	(NULL == pEnum)
	{
		ERROR_MSG(TEXT("EnumMember returned Null ptr"));
		return;
	}

	INmMember	* rgpMember[10];
	BSTR		  bstrAddr	= NULL;
	NM_ADDR_TYPE  uType;

	for	(int i = 0; i < 10; i++)
		rgpMember[i] = NULL;

	hr = pEnum->Next(cMember, rgpMember, &cFetched);
	if (FAILED(hr))
	{
    	ERROR_MSG(TEXT("EnumMember Failed (%s)"), GetHrSz(hr));
	}
	else
	{
		for (UINT iMember = 0; iMember < cFetched; iMember++)
		{
			if	(NULL != rgpMember[iMember])
			{
				hr = rgpMember[iMember] ->GetAddr(&bstrAddr, &uType);
				DumpMemberInfo(rgpMember[iMember]);
				rgpMember[iMember]->Release();
				rgpMember[iMember] = NULL;
			}
			else
				ERROR_MSG(TEXT("rgpMember[iMember] == NULL"));
		}
	}

	pEnum->Release();
	pEnum = NULL;
}


//****************************************************************************
//
// VOID DoEnumAll(void)
//
//****************************************************************************

VOID DoEnumAll(void)
{
	HRESULT			  hr		= NO_ERROR;
	IEnumNmChannel	* pEnum		= NULL;
	ULONG			  cFetched	= 0;
	ULONG			  cChannel	= 0;
	INmConference	* pConference = GetCurrentConference();

	if (NULL == pConference)
	{
		TRACE_MSG(TEXT("No current conference"));
		return;
	}

	DumpConferenceInfo(pConference);

	DoEnumConferenceMember(pConference);

	hr = pConference->GetChannelCount(&cChannel);
	if (FAILED(hr))
	{
    	ERROR_MSG(TEXT("GetChannelCount Failed (%s)"), GetHrSz(hr));
    	return;
	}
	TRACE_MSG(TEXT("%d channels in conference"), cChannel);

	if (cChannel > 10)
		cChannel = 10;

	hr = pConference->EnumChannel(&pEnum);
	if (FAILED(hr))
	{
    	ERROR_MSG(TEXT("EnumChannel Failed (%s)"), GetHrSz(hr));
    	return;
	}

	if	(NULL == pEnum)
	{
		ERROR_MSG(TEXT("EnumChannel returned NULL ptr"));
		return;
	}

	INmChannel * rgpChannel[10];
	for (int i = 0; i < 10; i++)
		rgpChannel[i] = NULL;

	hr = pEnum->Next(cChannel, rgpChannel, &cFetched);
	if (FAILED(hr))
	{
    	ERROR_MSG(TEXT("EnumMember Failed (%s)"), GetHrSz(hr));
	}
	else
	{
		for (UINT iChannel = 0; iChannel < cFetched; iChannel++)
		{
			if	(NULL != rgpChannel[iChannel])
			{
				DumpChannelInfo(rgpChannel[iChannel]);
				DoEnumChannelMember(rgpChannel[iChannel]);
				rgpChannel[iChannel]->Release();
				rgpChannel[iChannel] = NULL;
			}
			else
			{
				ERROR_MSG(TEXT("DoEnumAll: rgpChannel[iChannel] == NULL"));
			}
		}
	}

	pEnum->Release();
}

//****************************************************************************
//
// VOID DoEnumMemberLeak(void)
//
//****************************************************************************

VOID DoEnumMemberLeak(void)
{

	HRESULT			  hr		= NO_ERROR;
	IEnumNmMember	* pEnum		= NULL;
	INmMember		* pm		= NULL;
	INmConference	* pConference = GetCurrentConference();
	UINT i;

	if (NULL == pConference)
	{
		TRACE_MSG(TEXT("No current conference"));
		return;
	}

	for(i=0; i < 10; i++)
	{
		hr = pConference->EnumMember(&pEnum);
		if	(SUCCEEDED(hr) && (NULL != pEnum))
		{
			while(pEnum->Next(1, &pm, NULL) == NO_ERROR)
			{
				if	(NULL != pm)
				{
					pm->Release();
					pm = NULL;
				}
			}

			pEnum->Release();
			pEnum = NULL;
		}
		else
		{
			ERROR_MSG(TEXT("DoEnumMemberLeak: Error INmMember::EnumMember"));
		}
	}

}
//****************************************************************************
//
// VOID DoSharableAppLeak(void)
//
//****************************************************************************

VOID DoSharableAppLeak(void)
{

	HRESULT				  hr	= NO_ERROR	;	
	IEnumNmSharableApp	* pEnum	= NULL		;
	INmSharableApp		* pa	= NULL		;

	if	(NULL == g_pChannelAppShare)
	{
		ERROR_MSG(TEXT("DoSharableAppLeak: NULL == g_pChannelAppShare"));
		return;
	}

	for(UINT i=0; i < 1000; i++)
	{
		hr = g_pChannelAppShare->EnumSharableApp(&pEnum);
		if	(SUCCEEDED(hr) && (NULL != pEnum))
		{
			while(pEnum->Next(1, &pa, NULL) == NO_ERROR)
			{
				if	(NULL != pa)
				{
					pa->Release();
					pa = NULL;
				}
			}

			pEnum->Release();
			pEnum = NULL;
		}
		else
		{
			ERROR_MSG(TEXT("DoSharableAppLeak: NULL == pEnum"));
		}
	}

}
