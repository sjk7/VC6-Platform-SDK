/////////////////////////////////////////////////////////////////////////////
//
//	This source code is only intended as a supplement to 
//  existing Microsoft documentation. 
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1999 - 2001 Microsoft Corporation.  All Rights Reserved.
//
//  StaticNode.h: interface for the CStaticNode class.
//

#ifndef _CLASS_CSTATICNODE_
#define _CLASS_CSTATICNODE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Globals.h"
#include "BaseNode.h"


class CComponentData;        // References


//---------------------------------------------------------------------------
class CStaticNode : public CBaseNode  
{
  public:
    CStaticNode();
    virtual ~CStaticNode();
    
    HRESULT Initialize( NODE_PROPERTIES* pNodeProps );


  // Virtual methods
  public:
    ULONG   GetNodeType() { return NODETYPE_STATIC; }; 
    GUID*   GetNodeGUID() { return &thisGUID; };

    HRESULT GetResultViewType2( MMC_COOKIE nCookie, PRESULT_VIEW_TYPE_INFO pRVTinfo );    
    HRESULT GetDisplayInfo( SCOPEDATAITEM* pSDI );
    HRESULT GetDisplayInfo( RESULTDATAITEM* pRDI );


  // Notification handlers   
  public:
    HRESULT OnSelect( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent )
            { return E_NOTIMPL; }

    HRESULT OnShow( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent )
            { return E_NOTIMPL; }

  private:
    static GUID      thisGUID;
    CComponentData*  m_pCompData;

};

#endif //_CLASS_CSTATICNODE_
