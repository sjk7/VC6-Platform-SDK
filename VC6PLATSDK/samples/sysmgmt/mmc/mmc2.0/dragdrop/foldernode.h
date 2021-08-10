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
#include "VirtualFile.h"     // Result item children of this node
#include "LListImpl.h"       // Linked list class


class CComponentData;        // References
class CDeviceNode;

//---------------------------------------------------------------------------
class CFolderNode : public CBaseNode  
{
  public:
    CFolderNode();
    virtual ~CFolderNode();
    
    HRESULT Initialize( LPNODEPROPS pNodeProps );

  ///////////////////////////////////////////////////////////////////////////
  // Virtual methods
  public:
    HRESULT GetProperties( LPNODEPROPS* ppNodeProps );
    ULONG   GetNodeType() { return NODETYPE_FOLDER; } 
    GUID&   GetNodeGUID() { return thisGUID; }

    HRESULT GetResultViewType2( MMC_COOKIE nCookie, PRESULT_VIEW_TYPE_INFO pRVTinfo );    
    HRESULT GetDisplayInfo( SCOPEDATAITEM* pSDI );
    HRESULT GetDisplayInfo( RESULTDATAITEM* pRDI );

  ///////////////////////////////////////////////////////////////////////////
  //  Notification handlers   
  //
  public:
    HRESULT OnSelect( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnShow( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnRename( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData );
    HRESULT OnExpand( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData );            
    HRESULT OnRemoveChildren( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData );            
    HRESULT OnViewChange( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );            

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
  // Private helpers
  private:
    HRESULT InitDefaultVFile();
    VOID    RemoveNodes();
    HRESULT EnumerateResultItems( LPRESULTDATA ipResultData );
    HRESULT AddVirtualFile( NODE_PROPERTIES* pProps = NULL );

  private:
    static GUID  thisGUID;
    DWORD        m_dwAttributes;

    CLListImpl<CVirtualFile*,CVirtualFile*>  m_NodeList;
    CComponentData* m_pCompData;
    HWND            m_hMessageWnd;     // Our message handler 
    CDeviceNode*    m_pParentNode;

  public:
    HWND   m_hAddVFileDlg;             // Instance of AddDeviceDlg

    static LRESULT CALLBACK FolderNodeWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
  
    VOID RemoveChildNode( LONG_PTR pChildNode );

};

#endif //_CLASS_CFOLDERNODE_
