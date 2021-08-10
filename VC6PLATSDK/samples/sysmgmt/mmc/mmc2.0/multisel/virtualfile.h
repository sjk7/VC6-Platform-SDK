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
//  Abstract:  Defines a virtual file class derived from CBaseNode.  This
//             class will represent our result items
//


#ifndef _CLASS_VIRTUALFILE_
#define _CLASS_VIRTUALFILE_

#include "Globals.h"
#include "BaseNode.h"


class CFolderNode;           // References
class CComponentData;
class CComponent;

//---------------------------------------------------------------------------
class CVirtualFile : public CBaseNode  
{
  public:
    CVirtualFile();
    virtual ~CVirtualFile();
    
    HRESULT Initialize( LPNODEPROPS pNodeProps );

  ///////////////////////////////////////////////////////////////////////////
  // Virtual methods
  public:
    ULONG   GetNodeType() { return NODETYPE_VFILE; } 
    GUID&   GetNodeGUID() { return m_thisGUID; }

    HRESULT GetResultViewType2( MMC_COOKIE nCookie, PRESULT_VIEW_TYPE_INFO pRVTinfo )
            { return E_NOTIMPL; }
    
    HRESULT GetDisplayInfo( SCOPEDATAITEM* pSDI )
            { return E_NOTIMPL; }                  

    HRESULT GetDisplayInfo( RESULTDATAITEM* pRDI );

  ///////////////////////////////////////////////////////////////////////////
  //  Notification handlers   
  public:
    HRESULT OnSelect( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnShow( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnRename( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );

    HRESULT OnExpand( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData )            
            { return E_NOTIMPL; }

    HRESULT OnRemoveChildren( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData )
            { return E_NOTIMPL; }              

    HRESULT OnViewChange( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent )
            { return E_NOTIMPL; }

  ///////////////////////////////////////////////////////////////////////////
  //  Context Menu methods
  public:
    HRESULT AddMenuItems( LPCONTEXTMENUCALLBACK ipCallback, long __RPC_FAR* pInsertionAllowed );
    HRESULT Command( long lCommandID );

  /////////////////////////////////////////////////////////////////////////
  //  IExtendControlbar methods
  //
  public:
    HRESULT ControlbarNotify( LPARAM nArg, LPARAM lParam, LONG_PTR pComp );

  ///////////////////////////////////////////////////////////////////////////
  //  Helpers
  public:
    DWORD      GetAttributes() { return m_dwAttributes; } 
    BOOL       IsAttributeSet( DWORD dwAttribute );
    VOID       SetAttribute( DWORD dwAttribute );
    VOID       RemoveAttribute( DWORD dwAttribute );
    LPWSTR     GetAttributeString();
    LONG_PTR   GetParent() { return (LONG_PTR)m_pParentFolder; }


  private:
    static GUID      m_thisGUID;
    DWORD            m_dwAttributes;
    WCHAR            m_pAttributeStr[16];
    CFolderNode*     m_pParentFolder;
    CComponentData*  m_pCompData;
    CComponent*      m_pComponent;
};

#endif //_CLASS_VIRTUALFILE_