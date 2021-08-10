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

//---------------------------------------------------------------------------
class CVirtualFile : public CBaseNode  
{
  public:
    CVirtualFile();
    virtual ~CVirtualFile();
    
    HRESULT Initialize( NODE_PROPERTIES* pNodeProps );

  ///////////////////////////////////////////////////////////////////////////
  // Virtual methods
  public:
    ULONG   GetNodeType() { return NODETYPE_VFILE; } 
    GUID&   GetNodeGUID() { return thisGUID; }

    HRESULT GetResultViewType2( MMC_COOKIE nCookie, PRESULT_VIEW_TYPE_INFO pRVTinfo )
            { return E_NOTIMPL; }
    
    HRESULT GetDisplayInfo( SCOPEDATAITEM* pSDI )
            { return E_NOTIMPL; }                  

    HRESULT GetDisplayInfo( RESULTDATAITEM* pRDI );

  ///////////////////////////////////////////////////////////////////////////
  // Property Page methods
  public:
    HRESULT QueryForPropertyPage(); 
    HRESULT CreatePropertyPages( LPPROPERTYSHEETCALLBACK lpCallback, LONG_PTR Handle );
    HRESULT GetWatermarks( HBITMAP __RPC_FAR *lphWatermark,
                           HBITMAP __RPC_FAR *lphHeader,
                           HPALETTE __RPC_FAR *lphPalette,
                           BOOL __RPC_FAR *bStretch );


  /////////////////////////////////////////////////////////////////////////
  //  Notification handlers   
  public:
    HRESULT OnSelect( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnShow( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnDelete( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnContextHelp( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );

    HRESULT OnExpand( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData )            
            { return E_NOTIMPL; }

    HRESULT OnRemoveChildren( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData )
            { return E_NOTIMPL; }              

  ///////////////////////////////////////////////////////////////////////////
  //  Context Menu methods
  public:  
    HRESULT AddMenuItems( LPCONTEXTMENUCALLBACK ipCallback, long __RPC_FAR* pInsertionAllowed );
    HRESULT Command( long lCommandID );

  private:
    static GUID      thisGUID;
    DWORD            m_dwAttributes;
    CFolderNode*     m_pParentFolder;
    CComponentData*  m_pCompData;
    WCHAR            m_pAttributeStr[16];  // Attribute string 

  private:
    static BOOL CALLBACK PPageWndProc0( HWND hPage, UINT uMsg, WPARAM wParam, LPARAM lParam );
     
    BOOL   OnInitPropPage( HWND hPage, WPARAM wParam, LPARAM lParam );
    BOOL   OnApplyChanges( HWND hPage, WPARAM wParam, LPARAM lParam );

  public:
    LONG_PTR     m_nNotifyHandle;

  public:
    BOOL    IsAttributeSet( DWORD dwAttribute );
    VOID    SetAttribute( DWORD dwAttribute );
    VOID    RemoveAttribute( DWORD dwAttribute );
    LPWSTR  GetAttributeString();

};

#endif //_CLASS_VIRTUALFILE_