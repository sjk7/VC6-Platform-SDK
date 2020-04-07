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
#ifndef _ADMINWRAP_H_
#define _ADMINWRAP_H_

#include <comadmin.h>

typedef enum
{
	APPLICATION=0,
	COMPONENT,
	SUBSCRIPTION,
	TRANSIENTSUB,
	PUBPROP,
	TRANSIENTPUBPROP,
} ADMINTYPE, *PADMINTYPE;


HRESULT AddTransientSubscription(ICOMAdminCatalog* pICat, WCHAR* pwzSubName, WCHAR* pwzECID, WCHAR* pwzPubID, WCHAR* pwzIID, IUnknown *punk,
			                         WCHAR* pwzMethod, WCHAR* pwzCriteria, WCHAR* pwzPubProp, WCHAR* pwzPubVal);
HRESULT RemoveTransientSubscription(ICOMAdminCatalog* pICat, WCHAR* pwzName);

// Catalogue access functions
HRESULT RemoveNamedObjectFromCollection(ICatalogCollection* pICol, BSTR szObjectName, ADMINTYPE type);
HRESULT GetNamedObjectFromCollection(ICatalogCollection* pICol, BSTR szObjName, ICatalogObject** ppICatObj, LONG* plIndex, ADMINTYPE type, BSTR bstrName=NULL);
HRESULT GetCollection(ICOMAdminCatalog* pICat, BSTR szCollName, ICatalogCollection** ppICol);
HRESULT GetCollection(ICatalogCollection* pIParentColl, ICatalogObject* pICatObj, BSTR szCollName, ICatalogCollection** ppICol);
HRESULT GetObjectNameProperty(ADMINTYPE type, BSTR* pbstr);
HRESULT SetStringProperty(ICatalogObject *pcat, BSTR bPROP, WCHAR* pval);
HRESULT SetIUnknownProperty(ICatalogObject *pcat, BSTR bPROP, IUnknown* punk);



#endif
