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


class  CBaseNode;            // References

//---------------------------------------------------------------------------
//  DRAGDROP:  Two new data members have been added to facilitate cut/paste
//             operations between two different console processes.
//             See CDataObject
//
//    pChildProps  - An array of CHILD_PROPERTIES structs.  Each struct
//                   represents one child object.
//
//    dwChildCount - The number of CHILD_PROPERTIES structs in the array. 
//
//

struct CHILD_PROPERTIES
{
  WCHAR            szNodeName[MAX_NAME_LEN];
  DWORD            dwAttributes;         
};

struct NODE_PROPERTIES
{
  WCHAR              szNodeName[MAX_NAME_LEN];
  LONG_PTR           pComponentData;
  LONG_PTR           pParentObject;
  DWORD              dwAttributes;         
  LONG               nChildCount;
  LONG               nBlockSize;                
  CHILD_PROPERTIES   pChildProps;
};   

typedef NODE_PROPERTIES    NODEPROPS;
typedef NODE_PROPERTIES*   LPNODEPROPS;
typedef CHILD_PROPERTIES   CHILDPROPS;
typedef CHILD_PROPERTIES*  LPCHILDPROPS;
typedef CBaseNode*         LPBASENODE;


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
    LPWSTR   GetNodeName()     { return m_pwszNodeName;  };

    virtual  HRESULT Initialize( LPNODEPROPS pNodeProps ) = 0;
    virtual  HRESULT GetProperties( LPNODEPROPS* ppNodeProps ) = 0;  
    virtual  ULONG   GetNodeType() = 0;
    virtual  GUID&   GetNodeGUID() = 0;

  /////////////////////////////////////////////////////////////////////////// 
  // These virtual methods handle calls from the console
  //
  public:
    virtual  HRESULT GetDisplayInfo( SCOPEDATAITEM* pSDI ) = 0;
    virtual  HRESULT GetDisplayInfo( RESULTDATAITEM* pRDI ) = 0;
    virtual  HRESULT GetResultViewType2( MMC_COOKIE nCookie, PRESULT_VIEW_TYPE_INFO pRVTinfo ) = 0;    

  /////////////////////////////////////////////////////////////////////////// 
  // Context Menu methods
  //
  public:
    virtual  HRESULT AddMenuItems( LPCONTEXTMENUCALLBACK ipCallback, long __RPC_FAR* pInsertionAllowed ) = 0;
    virtual  HRESULT Command( long lCommandID ) = 0;

  /////////////////////////////////////////////////////////////////////////// 
  // These virtual methods handle notifications
  //
  public:  
    virtual  HRESULT OnSelect( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent ) = 0;
    virtual  HRESULT OnShow( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent ) = 0;
    virtual  HRESULT OnRename( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent ) = 0;
    virtual  HRESULT OnExpand( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData ) = 0;
    virtual  HRESULT OnRemoveChildren( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData ) = 0;


    virtual  HRESULT OnViewChange( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent )
                     { return E_NOTIMPL; };

    // DRAGDROP:  Support for additional notifications
    virtual  HRESULT OnQueryPaste( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent ) = 0;
    virtual  HRESULT OnPaste( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent ) = 0;
    virtual  HRESULT OnCutOrMove( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent ) = 0;

  public:
    SCOPEDATAITEM    m_SDI;
    RESULTDATAITEM   m_RDI;

  protected:
    LPWSTR     m_pwszNodeName;

}; //end class CBaseNode

#endif //_CLASS_CBASENODE_