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
//  Abstract:     Defines the CStaticNode class.  This is the Snap-in's
//                top level node
//


#ifndef _CLASS_CSTATICNODE_
#define _CLASS_CSTATICNODE_

#include "Globals.h"
#include "BaseNode.h"          // For NODE_PROPERTIES
#include "LListImpl.h"

class CDeviceNode;             // References
class CComponentData;


//---------------------------------------------------------------------------
class CStaticNode : public CBaseNode  
{
  public:
    CStaticNode();
    virtual ~CStaticNode();
    
    HRESULT Initialize( LPNODEPROPS pNodeProps );


  // Virtual methods
  public:
    HRESULT GetProperties( LPNODEPROPS* ppNodeProps );
    ULONG   GetNodeType() { return NODETYPE_STATIC; } 
    GUID&   GetNodeGUID() { return thisGUID; }

    HRESULT GetResultViewType2( MMC_COOKIE nCookie, PRESULT_VIEW_TYPE_INFO pRVTinfo );    
    HRESULT GetDisplayInfo( SCOPEDATAITEM* pSDI );
    HRESULT GetDisplayInfo( RESULTDATAITEM* pRDI );

  ///////////////////////////////////////////////////////////////////////////
  // Notification handlers   
  public:
    HRESULT OnSelect( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnShow( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnRename( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent )
            { return E_NOTIMPL; }
 
    HRESULT OnExpand( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData );            
    HRESULT OnRemoveChildren( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData );            

    // DRAGDROP:  Support for additional notifications
    HRESULT OnQueryPaste( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent )
            { return S_FALSE; }
 
    HRESULT OnPaste( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent )
            { return E_NOTIMPL; }
 
    HRESULT OnCutOrMove( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent )
            { return E_NOTIMPL; }

  /////////////////////////////////////////////////////////////////////////
  //  Context Menu methods
  //
  public:
    HRESULT AddMenuItems( LPCONTEXTMENUCALLBACK ipCallback, long __RPC_FAR* pInsertionAllowed );
    HRESULT Command( long lCommandID );

  ///////////////////////////////////////////////////////////////////////////
  // Private helpers
  private:
    HRESULT  DeleteScopeItems( LPCONSOLENAMESPACE2 ipCNS );
    HRESULT  InsertScopeItems( LPCONSOLENAMESPACE2 ipCNS );
    HRESULT  InitDefaultDevices();
    VOID     RemoveNodes();

  ///////////////////////////////////////////////////////////////////////////
  // Public helpers
  public:
    HRESULT  AddDeviceNode( NODE_PROPERTIES* pProperties );
    VOID     ToggleStatus( LPDATAOBJECT ipDataObject );
    HWND     GetMessageWnd() { return m_hMessageWnd; } 

    static LRESULT CALLBACK StaticNodeWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

  private:
    static GUID      thisGUID;
    HSCOPEITEM       m_hStaticNode;  
    CComponentData*  m_pCompData;
    HWND             m_hMessageWnd;        // Our message handler 

    CLListImpl<CDeviceNode*,CDeviceNode*>  m_NodeList;
  
  public:
    HWND             m_hAddDeviceDlg;      // Instance of AddDeviceDlg

};

#endif //_CLASS_CSTATICNODE_
