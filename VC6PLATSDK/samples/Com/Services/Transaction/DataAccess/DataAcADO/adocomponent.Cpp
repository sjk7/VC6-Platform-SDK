//==============================================================================
// Filename: ADOComponent.cpp
//
// Description: Implementation of CADOComponent 
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
#include "ADOKB.h"
#include "ADOComponent.h"

//Add the directory that contains msado20.tlb to the include path 

#import "D:\Program Files\Common Files\System\ado\msado20.tlb" no_namespace rename("EOF", "adoEOF" )
/////////////////////////////////////////////////////////////////////////////
// CADOComponent

HRESULT CADOComponent::Activate()
{
	HRESULT hr = CoGetObjectContext(IID_IObjectContext, (void**)&m_spObjectContext);
	if (SUCCEEDED(hr))
		return S_OK;
	return hr;
} 

BOOL CADOComponent::CanBePooled()
{
	return TRUE;
} 

void CADOComponent::Deactivate()
{
	m_spObjectContext.Release();
} 


STDMETHODIMP CADOComponent::SimpleQuery(VARIANT * returnval)
{
   _RecordsetPtr adoRs;

   _bstr_t Source("select au_fname from authors where au_lname = 'White'");
   //NOTE: Secure database installations should never have a blank password
   // Trusted security is recommended for production systems - this avoids
   // having to store the password in the code
   _bstr_t Connect("DSN=pubs;Uid=sa;Pwd=;Database=pubs");

   try
   {
      _variant_t InVar;

      adoRs.CreateInstance(__uuidof(Recordset));
      adoRs->Open( Source,
                Connect, 
                adOpenForwardOnly, 
				adLockReadOnly, 
				adCmdText);
      InVar = adoRs->Fields->GetItem("au_fname")->Value;
      VariantClear(returnval);
      VariantCopy(returnval, &(InVar.Detach()));

      adoRs->Close();
   }
    
   catch(_com_error z)
   {
      if(adoRs)
		{
         adoRs->Close();
         adoRs = NULL;
		}
    
		if (m_spObjectContext)
			m_spObjectContext->SetAbort();
		return z.Error();
	}

   if (m_spObjectContext)
   {
		m_spObjectContext->SetComplete();
   }

   adoRs = NULL;
   return S_OK;
}
