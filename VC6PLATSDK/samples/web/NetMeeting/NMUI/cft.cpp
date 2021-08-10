//****************************************************************************
//  Module:     NMUI.EXE
//  File:       CCFT.CPP
//  Content:    INmFt Routines
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

INmFt				* g_pFt					= NULL;
INmChannelFt		* g_pChannelFt			= NULL;
CFileTransferNotify	* g_pNotifyFileTransfer	= NULL;

//****************************************************************************
//
// HRESULT HookFileTransfer(INmChannel * pChannel)
//
// Hook into notification callback for the file transfer channel
// 
//****************************************************************************

HRESULT HookFileTransfer(INmChannel * pChannel)
{
	HRESULT				  hr		= NO_ERROR	;
	CFileTransferNotify	* pNotify	= NULL		;

	ASSERT(NULL != pChannel);
	if	(NULL == pChannel)
	{
		ERROR_MSG(TEXT("HookFileTransfer passed a Null Pointer"));
		return E_POINTER;
	}

	if	(NULL != g_pChannelFt)
	{
		ERROR_MSG(TEXT("HookFileTransfer: replacing existing g_pChannelFileTransfer"));
	}

	hr = pChannel->QueryInterface(IID_INmChannelFt, (void **)&g_pChannelFt);
	if	FAILED(hr)
	{
		ERROR_MSG(TEXT("HookFileTransfer:Unable to get File Transfer channel"));
		return hr;
	}

	if	(NULL == g_pChannelFt)
	{
		ERROR_MSG(TEXT("HookFileTransfer:QI returned a Null Pointer"));
		return E_FAIL;
	}

	// Connect to the Ft object
	pNotify = new CFileTransferNotify();
	if(NULL == pNotify)
	{
		hr = E_OUTOFMEMORY;
	}
	else
	{
		hr = pNotify->Connect(g_pChannelFt);
		if(FAILED(hr))
		{
			ERROR_MSG(TEXT("CFileTransferNotify Failed (%s)"), GetHrSz(hr));
			pNotify->Release();
		}
		else
		{
			OBJECT_MSG(TEXT("FileTransfer Connection point established successfully"));
			g_pNotifyFileTransfer = pNotify;
		}
	}

	if(FAILED(hr))
	{
		g_pChannelFt->Release();
		g_pChannelFt = NULL;
	}
		
	return hr;
}



//****************************************************************************
//
// CLASS CFileTransferNotify
//
//****************************************************************************

CFileTransferNotify::CFileTransferNotify() : RefCount(), CNotify()
{
	OBJECT_MSG(TEXT("CFileTransferNotify created"));
}

CFileTransferNotify::~CFileTransferNotify()
{
	OBJECT_MSG(TEXT("CFileTransferNotify destroyed"));
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CFileTransferNotify::AddRef(void)
{
	return RefCount::AddRef();
}


ULONG STDMETHODCALLTYPE CFileTransferNotify::Release(void)
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CFileTransferNotify::QueryInterface(REFIID riid, PVOID *ppvObject)
{
	if	(NULL == ppvObject)
		return E_POINTER;

	HRESULT hr = NO_ERROR;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
		OBJECT_MSG(TEXT("CFileTransferNotify::QueryInterface(): Returning IUnknown."));
	}
	else if (riid == IID_INmChannelFtNotify)
	{
		*ppvObject = (INmChannelNotify *)this;
		OBJECT_MSG(TEXT("CChannelFtNotify::QueryInterface(): Returning INmChannelFtNotify."));
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
		OBJECT_MSG(TEXT("CFileTransferNotify::QueryInterface(): Called on unknown interface."));
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

HRESULT STDMETHODCALLTYPE CFileTransferNotify::Connect(IUnknown *pUnk)
{
	return CNotify::Connect(pUnk, IID_INmChannelFtNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE CFileTransferNotify::Disconnect(void)
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// Methods from IConfNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CFileTransferNotify::NmUI(CONFN uNotify)
{
	NOTIFY_MSG(TEXT("CFileTransferNotify::NmUI uNotify=%08X, pChannel=%08X"), uNotify, CNotify::GetPunk());
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CFileTransferNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
{
	NOTIFY_MSG(TEXT("CFileTransferNotify::MemberChanged uNotify=%d pMember=%08X, pChannel=%08X"), uNotify, pMember, CNotify::GetPunk());

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CFileTransferNotify::FtUpdate(CONFN uNotify, INmFt *pFt)
{
	if	(NULL == pFt)
	{
		ERROR_MSG(TEXT("FtUpdate: NULL == pFt"));
		return E_POINTER;
	}

	ULONG		  ulBytes	= 0			;
	INmMember	* pMember	= NULL		;
	BSTR		  bstrName	= NULL		;
	LPTSTR		  psz		= NULL		;
	HRESULT		  hr		= NO_ERROR	;

	TCHAR sz[MAX_PATH + 1];
	
	hr = pFt->GetBytesTransferred(&ulBytes);
	if(FAILED(hr))
	{
		ERROR_MSG(TEXT("GetBytes Failed hr=%s"), GetHrSz(hr));
	}

	// get the Member object of the sender
	hr = pFt->GetMember(&pMember);
	if(FAILED(hr))
	{
		ERROR_MSG(TEXT("GetMember Failed hr=%s"), GetHrSz(hr));
		return hr;
	}
	
	NM_FT_STATE uState;
	pFt->GetState(&uState);

	if(NULL == pMember)
	{
		ZeroMemory(sz, (MAX_PATH + 1) * sizeof(TCHAR));

		// file being sent to all members of the conference
		_tcsncpy(sz, TEXT("BROADCAST\0"), MAX_PATH);
		
	NOTIFY_MSG(TEXT("CFileTransferNotify::FtUpdate uNotify=%s, State = %d, pFt=%08X, bytes=%d from %s\0"), 
			GetConfnSz(uNotify), uState, pFt, ulBytes, sz);

	}
	else
	{
		hr = pMember->GetName(&bstrName);
		if(FAILED(hr))
		{
			ERROR_MSG(TEXT("GetName Failed hr=%s"), GetHrSz(hr));
		}

		psz = PszFromBstr(bstrName);

		SysFreeString(bstrName);
		pMember->Release();

		if	(NULL == psz)
		{
			ERROR_MSG(TEXT("FtUpdate: NULL == psz"));
			return E_FAIL;
		}

	NOTIFY_MSG(TEXT("CFileTransferNotify::FtUpdate uNotify=%s, State = %d, pFt=%08X, bytes=%d from %s"), 
			GetConfnSz(uNotify), uState, pFt, ulBytes, psz);

		FreePlpv(&psz);

	}

	return S_OK;
}


//****************************************************************************
//
// VOID DoFtCancel(void)
//
//****************************************************************************

VOID DoFtCancel(void)
{
	if (NULL == g_pFt)
		return;

	HRESULT hr = g_pFt->Cancel();
}


//****************************************************************************
//
// VOID FreeFt(void)
//
//****************************************************************************

VOID FreeFt(void)
{
	if (NULL != g_pFt)
	{
		g_pFt->Release();
		g_pFt = NULL;
	}
}




//****************************************************************************
//
// VOID SendFile(INmMember * pINmMember)
//
//****************************************************************************

VOID SendFile(INmMember * pINmMember)
{
	PUSER pUser = PUserLocal();
	if (NULL == pUser)
	{
		return;
	}

	if (NULL == pUser->m_pChannelFt)
	{
		return;
	}

	BSTRING	  bstrFileName(gPref.pszFileName);
	if	((NULL == bstrFileName.GetLPBSTR()) && (NULL != gPref.pszFileName))
		return;

	INmFt	* pFt	= NULL;
	HRESULT	  hr	= pUser->m_pChannelFt->SendFile(&pFt, pINmMember, bstrFileName, 0);
	
	if (SUCCEEDED(hr))
	{
		if	(NULL == pFt)
		{
			ERROR_MSG(TEXT("SendFile: NULL == pFt"));
			return;
		}

		INmMember * pMember	= NULL;

		FreeFt();
		g_pFt = pFt;

		hr = pFt->GetMember( &pMember );
		if(SUCCEEDED(hr))
		{
			if(NULL == pMember)
			{
				// file was sent to everyone
			}
			else
			{
				BSTR bstrName	= NULL;
				
				// file was sent to this user
				hr = pMember->GetName(&bstrName);
				if	(NULL != bstrName)
				{
					::SysFreeString(bstrName);
				}

				pMember->Release();
			}
		}
	}
}

