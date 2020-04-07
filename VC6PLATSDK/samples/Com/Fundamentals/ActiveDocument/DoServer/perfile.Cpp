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

/**************************************************************************

  File:          PerFile.cpp
  
	Description:   CPersistFile implementation.
	
**************************************************************************/

/**************************************************************************
#include statements
**************************************************************************/

#include "PerFile.h"

/**************************************************************************

  CPersistFile::CPersistFile()
  
**************************************************************************/

CPersistFile::CPersistFile(COleDocument *pOleDoc, CPersistStorage *pPersistStorage)
{
	OutputDebugString(TEXT("CPersistFile's constructor\n"));
	
	m_pOleDoc = pOleDoc;
	
	m_pPersistStorage = pPersistStorage;
	
	m_pStorage = NULL;
	
	m_pwszFile = new OLECHAR[MAX_PATH];
}

/**************************************************************************

  CPersistFile::~CPersistFile()
  
**************************************************************************/

CPersistFile::~CPersistFile() 
{
	OutputDebugString(TEXT("CPersistFile's destructor\n"));
	
	if(m_pStorage)
		m_pStorage->Release();
	
	delete m_pwszFile;
}

/**************************************************************************

  CPersistFile::QueryInterface()
  
**************************************************************************/

STDMETHODIMP CPersistFile::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
	OutputDebugString(TEXT("CPersistFile::QueryInterface\n"));
	
	return m_pOleDoc->QueryInterface(riid, ppReturn);
}

/**************************************************************************

  CPersistFile::AddRef()
  
**************************************************************************/

STDMETHODIMP_(ULONG) CPersistFile::AddRef()
{
	OutputDebugString(TEXT("CPersistFile::AddRef\n"));
	
	return m_pOleDoc->AddRef();
}

/**************************************************************************

  CPersistFile::Release()
  
**************************************************************************/

STDMETHODIMP_(ULONG) CPersistFile::Release()
{
	OutputDebugString(TEXT("CPersistFile::Release\n"));
	
	return m_pOleDoc->Release();
}

/**************************************************************************

  CPersistFile::GetClassID()
  
**************************************************************************/

STDMETHODIMP CPersistFile::GetClassID(LPCLSID pClassID)
{
	OutputDebugString(TEXT("CPersistFile::GetClassID\n"));
	
	return m_pPersistStorage->GetClassID(pClassID);
}

/**************************************************************************

  CPersistFile::Save()
  
**************************************************************************/

STDMETHODIMP CPersistFile::Save(LPCOLESTR pwszFile, BOOL fRemember)
{
	OutputDebugString(TEXT("CPersistFile::Save\n"));
	
	if(!pwszFile)
		return E_INVALIDARG;
	
	HRESULT     hr = E_FAIL;	// Assume failure
	
								/*
								Only create a new storage if we don't already have a storage or the file name 
								has changed.
	*/
	if(!m_pStorage || (0 != lstrcmpiW(pwszFile, m_pwszFile)))
	{
		//if we have a storage, release it
		if(m_pStorage)
		{
			m_pPersistStorage->ReleaseStreamsAndStorage();
			m_pStorage->Release();
			m_pStorage = NULL;
			*m_pwszFile = 0;
		}
		
		//open the file as storage
		hr = StgCreateDocfile(  pwszFile,
			STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
			0,
			&m_pStorage);
		
	}
	
	
	
	if(m_pStorage)
	{
		hr = m_pPersistStorage->Save(m_pStorage, FALSE);
	}
	
	
	if(fRemember)
	{
		lstrcpynW(m_pwszFile, pwszFile, MAX_PATH);
	}
	else
	{
		m_pPersistStorage->ReleaseStreamsAndStorage();
		m_pStorage->Release();
		m_pStorage = NULL;
		*m_pwszFile = 0;
	}
	
	return hr;
}

/**************************************************************************

  CPersistFile::SaveCompleted()
  
**************************************************************************/

STDMETHODIMP CPersistFile::SaveCompleted(LPCOLESTR pwszFile)
{
	UNREFERENCED_PARAMETER(pwszFile);
	OutputDebugString(TEXT("CPersistFile::SaveCompleted\n"));
	
	return m_pPersistStorage->SaveCompleted(NULL);
}

/**************************************************************************

  CPersistFile::Load()
  
**************************************************************************/

STDMETHODIMP CPersistFile::Load(LPCOLESTR pwszFile, DWORD dwMode)
{
	OutputDebugString(TEXT("CPersistFile::Load\n"));
	
	HRESULT     hr;
	
	if(!pwszFile)
		return E_INVALIDARG;
	
	//close any existing storage we might have
	if(m_pStorage)
	{
		m_pPersistStorage->ReleaseStreamsAndStorage();
		m_pStorage->Release();
		m_pStorage = NULL;
		*m_pwszFile = 0;
	}
	
	//open the file as storage and load it
	hr = StgOpenStorage(    pwszFile,
		NULL,
		dwMode | STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
		NULL,
		0,
		&m_pStorage);
	
	if(m_pStorage)
	{
		hr = m_pPersistStorage->Load(m_pStorage);
	}
	else
	{
		hr = E_FAIL;
	}
	
	if(SUCCEEDED(hr))
		lstrcpynW(m_pwszFile, pwszFile, MAX_PATH);
	
	return hr;
}

/**************************************************************************

  CPersistFile::IsDirty()
  
**************************************************************************/

STDMETHODIMP CPersistFile::IsDirty()
{
	OutputDebugString(TEXT("CPersistFile::IsDirty\n"));
	
	return m_pPersistStorage->IsDirty();
}

/**************************************************************************

  CPersistFile::GetCurFile()
  
**************************************************************************/

STDMETHODIMP CPersistFile::GetCurFile(LPOLESTR *ppwszOut)
{
	OutputDebugString(TEXT("CPersistFile::GetCurFile\n"));
	
	HRESULT  hr = E_FAIL;
	
	*ppwszOut = NULL;
	
	LPMALLOC pMalloc;
	CoGetMalloc(1, &pMalloc);
	if(pMalloc)
	{
		if(*m_pwszFile)
		{
			*ppwszOut = (LPOLESTR)pMalloc->Alloc(lstrlenW(m_pwszFile) + sizeof(OLECHAR));
			if(*ppwszOut)
			{
				lstrcpynW(*ppwszOut, m_pwszFile, (lstrlenW(m_pwszFile) + sizeof(OLECHAR))/
          sizeof(OLECHAR));
				hr = S_OK;
			}
		}
		else
		{
			*ppwszOut = (LPOLESTR)pMalloc->Alloc(lstrlenW(DEFAULT_PROMPT) + sizeof(OLECHAR));
			if(*ppwszOut)
			{
				lstrcpynW(*ppwszOut, DEFAULT_PROMPT, (lstrlenW(DEFAULT_PROMPT) + sizeof(OLECHAR))/
          sizeof(OLECHAR));
				hr = S_FALSE;
			}
		}
		
		pMalloc->Release();
	}
	
	return hr;
}

