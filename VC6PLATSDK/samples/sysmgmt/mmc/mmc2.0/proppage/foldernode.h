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
  // Property Page methods.  This node does not support Property Pages
  public:  
    HRESULT QueryForPropertyPage() 
            { return E_NOTIMPL; }

    HRESULT CreatePropertyPages( LPPROPERTYSHEETCALLBACK lpCallback, LONG_PTR Handle )
            { return E_NOTIMPL; }

    HRESULT GetWatermarks( HBITMAP __RPC_FAR *lphWatermark,
                           HBITMAP __RPC_FAR *lphHeader,
                           HPALETTE __RPC_FAR *lphPalette,
                           BOOL __RPC_FAR *bStretch )
            { return E_NOTIMPL; }


  ///////////////////////////////////////////////////////////////////////////
  //  Notification handlers   
  public:
    HRESULT OnSelect( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent );
    HRESULT OnShow( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent );
    HRESULT OnExpand( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pCompData );            
    HRESULT OnRemoveChildren( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pCompData );            

    HRESULT OnViewChange( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent );            
    HRESULT OnDelete( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent )
            { return E_NOTIMPL; }     

  ///////////////////////////////////////////////////////////////////////////
  //  Context Menu methods
  public:
    HRESULT AddMenuItems( LPCONTEXTMENUCALLBACK ipCallback, long __RPC_FAR* pInsertionAllowed );
    HRESULT Command( long lCommandID );

  ///////////////////////////////////////////////////////////////////////////
  // Private helpers
  private:
    HRESULT RefreshNodeList();
    VOID    RemoveNodes();
    HRESULT EnumerateResultItems( LPRESULTDATA ipResultData );
    HRESULT AddVirtualFile( NODE_PROPERTIES* pProps = NULL );

  private:
    static GUID  thisGUID;
    DWORD        m_dwAttributes;

    CLListImpl<CVirtualFile*,CVirtualFile*>  m_NodeList;
    CComponentData* m_pCompData;
    HWND            m_hMessageWnd;     // Our message handler 

  public:
    HWND   m_hAddVFileDlg;             // Instance of AddDeviceDlg

    VOID   RemoveVirtualFile( CVirtualFile* pDeadNode );

    static LRESULT CALLBACK FolderNodeWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

  // XPROPPAGE: Support for attributes
  public:
    BOOL    IsAttributeSet( DWORD dwAttribute ) { return FALSE; }
    VOID    SetAttribute( DWORD dwAttribute ) {}
    VOID    RemoveAttribute( DWORD dwAttribute ) {}
    LPWSTR  GetAttributeString() { return m_pAttributeStr; }
    DWORD   GetAttributes() { return 0; }
    LPWSTR  GetObjectPath() { return NULL; }

};

#endif //_CLASS_CFOLDERNODE_
