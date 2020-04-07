//==============================================================================
// Filename: OLEDBComponent.cpp
//
// Description: Implementation of COLEDBComponent
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


//#define DBINITCONSTANTS // Initialize OLE constants...


#include "stdafx.h"
#include "Oledbkb.h"
#include "OLEDBComponent.h"

//TODO: You will have to adjust the following #include statements
//to have correct paths to your oledb header files.
#include "oledb.h"
#include "oledberr.h"
#include "msdaguid.h"
#include "msdasql.h"
//END TODO


#include <windows.h>
#include <stdio.h>


HRESULT SetInitProps(IDBInitialize *);

/////////////////////////////////////////////////////////////////////////////
// COLEDBComponent

HRESULT COLEDBComponent::Activate()
{
	HRESULT hr = CoGetObjectContext(IID_IObjectContext, (void**)&m_spObjectContext);
	if (SUCCEEDED(hr))
		return S_OK;
	return hr;
} 

BOOL COLEDBComponent::CanBePooled()
{
	return TRUE;
} 

void COLEDBComponent::Deactivate()
{
	m_spObjectContext.Release();
} 


STDMETHODIMP COLEDBComponent::SimpleQuery(BSTR * returnval)
{

	IDBInitialize*		pIDBInitialize		= NULL;
   IMultipleResults*	pIMultipleResults	= NULL;
   IDBCreateSession* pIDBCreateSession	= NULL;
   IDBCreateCommand* pIDBCreateCommand	= NULL;
   ICommandText*     pICommandText		= NULL;
   ICommand*         pICommand			= NULL;
   IAccessor*			pIAccessor			= NULL;
   IRowset*				pIRowset			= NULL;

	LPCOLESTR         wSQLString 
		= OLESTR("select au_fname from authors where au_lname = 'White'");
   LONG              cRowsAffected;
   HRESULT           retcode;
   ULONG					cRowsObtained;
   HROW					hRow;
   HROW*					pRows = &hRow;
   HACCESSOR			hAccessor;
   DBBINDSTATUS		DBBindStatus;
   DBBINDING			DBBindings = 		
			{1, 0, 0, 0, NULL, NULL, NULL, DBPART_VALUE, 
			DBMEMOWNER_CLIENTOWNED, DBPARAMIO_NOTPARAM, 20,
			0, 129, 255, 255};
	char					RowValue[20];
	
//	Helper				myHelper;

	CoInitialize(NULL);

	if(FAILED(CoCreateInstance(CLSID_MSDASQL, NULL, CLSCTX_INPROC_SERVER,
        IID_IDBInitialize, (void**)&pIDBInitialize)))
        goto error;
	
   if(FAILED(SetInitProps(pIDBInitialize)))
        goto error;

	if(FAILED(pIDBInitialize->Initialize()))
		goto error;

	if(FAILED(pIDBInitialize->QueryInterface(IID_IDBCreateSession, (void**) &pIDBCreateSession)))
      goto error;

   if(FAILED(pIDBCreateSession->CreateSession(NULL, IID_IDBCreateCommand,
       (IUnknown**) &pIDBCreateCommand)))
		goto error;

   if(FAILED(pIDBCreateCommand->CreateCommand(NULL, IID_ICommand,
       (IUnknown**) &pICommand)))
		goto error;

   if(FAILED(retcode=pICommand->QueryInterface(IID_ICommandText, 
		(void**) &pICommandText)))
		goto error;

   //if(FAILED(pICommandText->SetCommandText(DBGUID_DBSQL, wSQLString))))
   if(FAILED(pICommandText->SetCommandText(DBGUID_DEFAULT, OLESTR("select au_fname from authors where au_lname = 'White'"))))
		goto error;

	if(FAILED(pICommand->Execute(NULL, IID_IMultipleResults, NULL, 
		&cRowsAffected,(IUnknown**) &pIMultipleResults)))
		goto error;

	if(FAILED(pIMultipleResults->GetResult(NULL, 0, IID_IRowset,
		&cRowsAffected,(IUnknown**) &pIRowset)))
		goto error;

   if(FAILED(pIRowset->QueryInterface(IID_IAccessor, 
		(void**) &pIAccessor)))
		goto error;

   if(FAILED(pIAccessor->CreateAccessor(DBACCESSOR_ROWDATA, 1,
		&DBBindings,0,&hAccessor,&DBBindStatus)))
		goto error;

	if(DBBINDSTATUS_OK != DBBindStatus)
		goto error;

   if(FAILED(pIRowset->GetNextRows(0,0,1,&cRowsObtained,&pRows )))
		goto error;

	if(cRowsObtained == 0)
        goto error;

   if(FAILED(pIRowset->GetData(hRow, hAccessor, RowValue)))
		goto error;

	OLECHAR svalue[20];
   if(0 == MultiByteToWideChar(CP_ACP, 0, (const char *)RowValue, 
		20, svalue, 20))
		goto error;
	*returnval = SysAllocString(svalue);

	if (m_spObjectContext)
		m_spObjectContext->SetComplete();
	
	retcode = S_OK;
	
	goto cleanup;


error:
	if (m_spObjectContext)
		m_spObjectContext->SetAbort();
	retcode = E_FAIL;
	goto cleanup;

cleanup:
	if(pIDBCreateSession)
	    pIDBCreateSession->Release();

   if(pIDBCreateCommand)
		pIDBCreateCommand->Release();

	if(pICommand)
	    pICommand->Release();

   if(pICommandText)
		pICommandText->Release();

	if(pIRowset)
	{
		pIRowset->ReleaseRows(cRowsObtained, &hRow, NULL, NULL, NULL);
		pIRowset->Release();
	}

	if(pIAccessor)
	{
		pIAccessor->ReleaseAccessor(hAccessor, NULL);
		pIAccessor->Release();
	}

	if(pIMultipleResults)
		pIMultipleResults->Release();

	if(pIDBInitialize)
	{
		pIDBInitialize->Uninitialize();
		pIDBInitialize->Release();
	}

    CoUninitialize();

    return retcode;
}

HRESULT SetInitProps(IDBInitialize * pIDBInitialize)
{
	IDBProperties* pIDBProperties;
   DBPROP         InitProperties[4];
   DBPROPSET      rgInitPropSet;
	HRESULT			retcode;

   for (ULONG i = 0; i < 4; i++ )
	{
		VariantInit(&InitProperties[i].vValue);
      InitProperties[i].dwOptions = DBPROPOPTIONS_REQUIRED;
      InitProperties[i].colid = DB_NULLID;
   }

   InitProperties[0].dwPropertyID = DBPROP_INIT_PROMPT;
   InitProperties[0].vValue.vt = VT_I2;
   InitProperties[0].vValue.iVal = DBPROMPT_NOPROMPT; 	

   InitProperties[1].dwPropertyID = DBPROP_INIT_DATASOURCE;	
   InitProperties[1].vValue.vt = VT_BSTR;
   InitProperties[1].vValue.bstrVal = SysAllocString(OLESTR("pubs"));
	
   InitProperties[2].dwPropertyID = DBPROP_AUTH_USERID;
   InitProperties[2].vValue.vt = VT_BSTR;
   InitProperties[2].vValue.bstrVal = SysAllocString(OLESTR("sa"));

   InitProperties[3].dwPropertyID = DBPROP_AUTH_PASSWORD;
   InitProperties[3].vValue.vt = VT_BSTR;
   InitProperties[3].vValue.bstrVal = SysAllocString(OLESTR(""));

   rgInitPropSet.guidPropertySet = DBPROPSET_DBINIT;
   rgInitPropSet.cProperties = 4;
   rgInitPropSet.rgProperties = InitProperties;

   if(FAILED(pIDBInitialize->QueryInterface(IID_IDBProperties, (void**) &pIDBProperties)))
		goto error;
   if(FAILED(pIDBProperties->SetProperties(1, &rgInitPropSet)))
		goto error;
	
	retcode = S_OK;
	goto cleanup;

error:
	retcode = E_FAIL;
	goto cleanup;

cleanup:
	if(pIDBProperties)
		pIDBProperties->Release();

	SysFreeString(InitProperties[1].vValue.bstrVal);
   SysFreeString(InitProperties[2].vValue.bstrVal);
   SysFreeString(InitProperties[3].vValue.bstrVal);
	
	return retcode;
}
