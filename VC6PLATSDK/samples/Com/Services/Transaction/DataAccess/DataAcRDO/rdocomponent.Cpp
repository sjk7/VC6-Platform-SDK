//==============================================================================
// Filename: RDOComponent.cpp 
//
// Description: Implementation of CRDOComponent
//
// This file is part of the Microsoft COM+ Samples
//
// Copyright (C) 1995 - 2000 Microsoft Corporation. All rights reserved
//
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation.  See these other
// materials for detailed information reagrding Microsoft code samples.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
//==============================================================================


#include "stdafx.h"
#include "RDOKB.h"
#include "RDOComponent.h"
#import "msrdo20.dll" no_namespace  rename("EOF", "rdoEOF") rename("UserNameA", "rdoUserNameA")
/////////////////////////////////////////////////////////////////////////////
// CRDOComponent

HRESULT CRDOComponent::Activate()
{
	HRESULT hr = CoGetObjectContext(IID_IObjectContext, (void**)&m_spObjectContext);
	if (SUCCEEDED(hr))
		return S_OK;
	return hr;
} 

BOOL CRDOComponent::CanBePooled()
{
	return TRUE;
} 

void CRDOComponent::Deactivate()
{
	m_spObjectContext.Release();
} 


STDMETHODIMP CRDOComponent::SimpleQuery(VARIANT * returnval)
{

	_rdoEnginePtr rdoEngine1;
	_rdoConnectionPtr rdoCon;
	_rdoResultsetPtr rdoRs;
	_variant_t InVar;

   _bstr_t Source("select au_fname from authors where au_lname = 'White'");
   //NOTE: Secure database installations should never have a blank password
   // Trusted security is recommended for production systems - this avoids
   // having to store the password in the code
   _bstr_t Connect("DSN=pubs;Uid=sa;Pwd=;Database=pubs");

	HRESULT hr = rdoEngine1.CreateInstance(__uuidof(rdoEngine));
   if (FAILED(hr)) return hr;
	
	try
	{
		rdoEngine1->rdoEnvironments->GetItem(0L)->CursorDriver = rdUseNone;
		rdoCon =rdoEngine1->rdoEnvironments->GetItem(0L)->OpenConnection("", 
			(long)rdDriverNoPrompt, 0L, Connect);
		
		rdoRs = rdoCon->OpenResultset(Source);
		InVar = rdoRs->rdoColumns->GetItem("au_fname")->Value;
		
		VariantClear(returnval);
		VariantCopy(returnval, &(InVar.Detach()));

		rdoRs->Close();
		rdoRs=NULL;
		rdoCon->Close();
		rdoCon = NULL;
		rdoEngine1 = NULL;
	}

	catch(_com_error z)
	{
		if(rdoRs)
		{
			rdoRs->Close();
			rdoRs = NULL;
		}
		if(rdoCon)
		{
			rdoCon->Close();
			rdoCon = NULL;
		}
		if(rdoEngine1)
			rdoEngine1 = NULL;

		if(m_spObjectContext)
			m_spObjectContext->SetAbort();
		return z.Error();
	}

	if (m_spObjectContext)
		m_spObjectContext->SetComplete();
	return S_OK;
}
