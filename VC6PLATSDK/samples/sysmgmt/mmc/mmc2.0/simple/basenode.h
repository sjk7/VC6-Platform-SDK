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
//


#ifndef _CLASS_BASENODE_
#define _CLASS_BASENODE_

#include "Globals.h"
#include "Resource.h"


#define DEFAULT_SDI_MASK  (SDI_STR | SDI_PARAM | SDI_IMAGE | SDI_OPENIMAGE | SDI_PARENT | SDI_CHILDREN)
#define DEFAULT_RDI_MASK  (RDI_STR | RDI_PARAM | RDI_IMAGE)

#define MAX_NAME_LEN     64


//---------------------------------------------------------------------------
//  Data types specific to this object
//
typedef struct tag_BASENODE_PROPERTIES
{
  WCHAR      szNodeName[MAX_NAME_LEN];
  LONG_PTR   pComponentData;

}NODE_PROPERTIES;   

typedef NODE_PROPERTIES*  LPNODE_PROPERTIES;


//---------------------------------------------------------------------------
class CBaseNode
{
  public:
    CBaseNode()
    {
      m_pwszNodeName      = NULL;

      ZeroMemory( &m_SDI, sizeof(SCOPEDATAITEM) );
      ZeroMemory( &m_RDI, sizeof(RESULTDATAITEM) );
    };

    virtual ~CBaseNode()
    {
      if( NULL != m_pwszNodeName )
        CoTaskMemFree( m_pwszNodeName );
    };

  public:
    LPWSTR   GetNodeName()     { return m_pwszNodeName;  }

    virtual  HRESULT Initialize( NODE_PROPERTIES* pProperties ) = 0;
    virtual  ULONG   GetNodeType() = 0;
    virtual  GUID*   GetNodeGUID() = 0;

  ///////////////////////////////////////////////////////////////////////// 
  // These virtual methods handle calls from the console
  //
  public:
    virtual  HRESULT GetDisplayInfo( SCOPEDATAITEM* pSDI ) = 0;
    virtual  HRESULT GetDisplayInfo( RESULTDATAITEM* pRDI ) = 0;
    virtual  HRESULT GetResultViewType2( MMC_COOKIE nCookie, PRESULT_VIEW_TYPE_INFO pRVTinfo ) = 0;    

  /////////////////////////////////////////////////////////////////////////// 
  // These virtual methods handle notifications
  //
  public:
    virtual  HRESULT OnSelect( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent ) = 0;
    virtual  HRESULT OnShow( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam, LONG_PTR pComponent ) = 0;

  public:
    SCOPEDATAITEM    m_SDI;
    RESULTDATAITEM   m_RDI;

  protected:
    LPWSTR     m_pwszNodeName;

}; //end class CBaseNode

#endif //_CLASS_BASENODE_