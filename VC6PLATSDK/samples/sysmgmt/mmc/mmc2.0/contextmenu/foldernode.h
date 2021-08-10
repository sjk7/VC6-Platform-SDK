/////////////////////////////////////////////////////////////////////////////
//
//  This source code is only intended as a supplement to existing
//  Microsoft documentation. 
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1999 - 2001 Microsoft Corporation.  All Rights Reserved.
//
//  Abstract:     Defines the CFolderNode class.  This node is a child of
//                CDeviceNode.  It represents a Virtual Storage folder
//                
//


#ifndef _CLASS_CFOLDERNODE_
#define _CLASS_CFOLDERNODE_

#include "Globals.h"
#include "BaseNode.h"


class CComponentData;        // References

//---------------------------------------------------------------------------
class CFolderNode : public CBaseNode  
{
  public:
    CFolderNode();
    virtual ~CFolderNode();
    
    HRESULT Initialize( NODE_PROPERTIES* pNodeProps );

  ///////////////////////////////////////////////////////////////////////////
  // Virtual methods
  public:
    ULONG   GetNodeType() { return NODETYPE_FOLDER; } 
    GUID&   GetNodeGUID() { return thisGUID; }

    HRESULT GetResultViewType2( MMC_COOKIE nCookie, PRESULT_VIEW_TYPE_INFO pRVTinfo );    
    HRESULT GetDisplayInfo( SCOPEDATAITEM* pSDI );
    HRESULT GetDisplayInfo( RESULTDATAITEM* pRDI );

  ///////////////////////////////////////////////////////////////////////////
  //  Notification handlers   
  //
  public:
    HRESULT OnSelect( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent );
    HRESULT OnShow( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent );
    HRESULT OnExpand( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pCompData );            
    HRESULT OnRemoveChildren( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pCompData );            

  ///////////////////////////////////////////////////////////////////////////
  //  Context Menu methods
  //
  HRESULT AddMenuItems( LPCONTEXTMENUCALLBACK ipCallback, long __RPC_FAR* pInsertionAllowed );
  HRESULT Command( long lCommandID );

  private:
    static GUID      thisGUID;
    DWORD            m_dwAttributes;
    CComponentData*  m_pCompData;
};

#endif //_CLASS_CFOLDERNODE_
