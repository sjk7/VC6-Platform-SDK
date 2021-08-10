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
//  Abstract:  Generic base node class.  All nodes are derived from this.


#ifndef _CLASS_CBASENODE_
#define _CLASS_CBASENODE_

#include "Globals.h"
#include "Resource.h"


#define DEFAULT_SDI_MASK  (SDI_STR | SDI_PARAM | SDI_IMAGE | SDI_OPENIMAGE | SDI_PARENT | SDI_CHILDREN)
#define DEFAULT_RDI_MASK  (RDI_STR | RDI_PARAM | RDI_IMAGE)

#define MAX_NAME_LEN     64


class CBaseNode;


//---------------------------------------------------------------------------
//  Data types specific to this object
//
typedef struct tag_BASENODE_PROPERTIES
{
  WCHAR      szNodeName[MAX_NAME_LEN];
  LONG_PTR   pComponentData;
  LONG_PTR   pParentObject;
  DWORD      dwAttributes;         
                                   
}NODE_PROPERTIES;   


typedef NODE_PROPERTIES*  LPNODE_PROPERTIES;
typedef CBaseNode*        LPBASENODE;


//---------------------------------------------------------------------------
class CBaseNode
{
  public:
    CBaseNode()
    {
      m_pwszNodeName   = NULL;
      m_nPropPageCount = 0;
      m_dwAttributes   = 0;
      *m_pAttributeStr = NULL;

      ZeroMemory( &m_SDI, sizeof(SCOPEDATAITEM) );
      ZeroMemory( &m_RDI, sizeof(RESULTDATAITEM) );
    };

    virtual ~CBaseNode()
    {
      if( NULL != m_pwszNodeName )
        CoTaskMemFree( m_pwszNodeName );
    };

  public:
    LPWSTR   GetNodeName()     { return m_pwszNodeName;  };

    virtual  HRESULT Initialize( NODE_PROPERTIES* pProperties ) = 0;
    virtual  ULONG   GetNodeType() = 0;
    virtual  GUID&   GetNodeGUID() = 0;

  ///////////////////////////////////////////////////////////////////////////
  //  IExtendPropertySheet2 methods
  public:
    virtual  HRESULT QueryForPropertyPage() = 0; 
    virtual  HRESULT CreatePropertyPages( LPPROPERTYSHEETCALLBACK lpCallback, LONG_PTR Handle ) = 0;
    virtual  HRESULT GetWatermarks( HBITMAP __RPC_FAR *lphWatermark,
                                    HBITMAP __RPC_FAR *lphHeader,
                                    HPALETTE __RPC_FAR *lphPalette,
                                    BOOL __RPC_FAR *bStretch ) = 0;

  /////////////////////////////////////////////////////////////////////////// 
  // These virtual methods handle calls from the console
  public:
    virtual  HRESULT GetDisplayInfo( SCOPEDATAITEM* pSDI ) = 0;
    virtual  HRESULT GetDisplayInfo( RESULTDATAITEM* pRDI ) = 0;
    virtual  HRESULT GetResultViewType2( MMC_COOKIE nCookie, PRESULT_VIEW_TYPE_INFO pRVTinfo ) = 0;    

  /////////////////////////////////////////////////////////////////////////// 
  // Context menu methods
  public:
    virtual  HRESULT AddMenuItems( LPCONTEXTMENUCALLBACK ipCallback, long __RPC_FAR* pInsertionAllowed ) = 0;
    virtual  HRESULT Command( long lCommandID ) = 0;

  /////////////////////////////////////////////////////////////////////////// 
  // Notification handlers
  public:
    virtual  HRESULT OnSelect( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent ) = 0;
    virtual  HRESULT OnShow( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent ) = 0;
    virtual  HRESULT OnExpand( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pCompData ) = 0;
    virtual  HRESULT OnRemoveChildren( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pCompData ) = 0;
    virtual  HRESULT OnDelete( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent ) = 0;

    virtual  HRESULT OnViewChange( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent )
                     { return E_NOTIMPL; };

  public:
    SCOPEDATAITEM    m_SDI;
    RESULTDATAITEM   m_RDI;

  protected:
    LPWSTR     m_pwszNodeName;
    LONG       m_nPropPageCount;       // Added to support Property Pages

  /////////////////////////////////////////////////////////////////////////// 
  // XPROPPAGE:  Data and methods to support node attributes

  public:
    DWORD      m_dwAttributes;         // Attribute flags
    WCHAR      m_pAttributeStr[16];    // Attribute string 

    virtual BOOL    IsAttributeSet( DWORD dwAttribute ) = 0;
    virtual VOID    SetAttribute( DWORD dwAttribute ) = 0;
    virtual VOID    RemoveAttribute( DWORD dwAttribute ) = 0;
    virtual LPWSTR  GetAttributeString() = 0;
    virtual DWORD   GetAttributes() = 0;
    virtual LPWSTR  GetObjectPath() = 0;

}; //end class CBaseNode

#endif //_CLASS_CBASENODE_