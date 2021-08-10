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
//  Abstract:     Defines the CDeviceNode class.  This node is a child of
//                CStaticNode.  It represents a Virtual Storage device
//                
//


#ifndef _CLASS_CDEVICENODE_
#define _CLASS_CDEVICENODE_

#include "Globals.h"
#include "FolderNode.h"      // Folders are children of this node
#include "LListImpl.h"


class CComponentData;        // References
class CStaticNode;

//---------------------------------------------------------------------------
class CDeviceNode : public CBaseNode  
{
  public:
    CDeviceNode();
    virtual ~CDeviceNode();
    
    HRESULT Initialize( LPNODEPROPS pNodeProps );
    VOID    ToggleStatus();

  // Virtual methods
  public:
    HRESULT GetProperties( LPNODEPROPS* ppNodeProps );
    ULONG   GetNodeType() { return NODETYPE_DEVICE; } 
    GUID&   GetNodeGUID() { return thisGUID; }

    HRESULT GetResultViewType2( MMC_COOKIE nCookie, PRESULT_VIEW_TYPE_INFO pRVTinfo );    
    HRESULT GetDisplayInfo( SCOPEDATAITEM* pSDI );
    HRESULT GetDisplayInfo( RESULTDATAITEM* pRDI );

  ///////////////////////////////////////////////////////////////////////////
  // Notification handlers   
  //
  public:
    HRESULT OnSelect( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnShow( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnRename( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnExpand( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData );            
    HRESULT OnRemoveChildren( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData );            

    // DRAGDROP:  Support for additional notifications
    HRESULT OnQueryPaste( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent ); 
    HRESULT OnPaste( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent ); 
    HRESULT OnCutOrMove( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );


  ///////////////////////////////////////////////////////////////////////////
  //  Context Menu methods
  //
  public:
    HRESULT AddMenuItems( LPCONTEXTMENUCALLBACK ipCallback, long __RPC_FAR* pInsertionAllowed );
    HRESULT Command( long lCommandID );

  ///////////////////////////////////////////////////////////////////////////
  // Public helpers
  public:
    VOID    RemoveChildNode( LONG_PTR pChildNode );

  ///////////////////////////////////////////////////////////////////////////
  // Private helpers
  private:
    HRESULT  DeleteChildItems( LPCONSOLENAMESPACE2 ipCNS );
    HRESULT  InsertChildItems( LPCONSOLENAMESPACE2 ipCNS );
    HRESULT  InitDefaultFolder();
    VOID     RemoveNodes();
 
  private:
    static GUID  thisGUID;
    DWORD        m_dwAttributes;
    HSCOPEITEM   m_hParentNode;  
    LPWSTR       m_wzStatus;
    BOOL         m_bOnlineStatus;

    CLListImpl<CBaseNode*,CBaseNode*>  m_NodeList;
    CComponentData*                    m_pCompData;
    CStaticNode*                       m_pParentNode;

};

#endif //_CLASS_CDEVICENODE_
