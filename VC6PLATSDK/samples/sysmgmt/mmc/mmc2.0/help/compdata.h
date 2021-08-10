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


#ifndef _CLASS_CCOMPONENTDATA_
#define _CLASS_CCOMPONENTDATA_


#include "Globals.h"
#include "BaseNode.h"

class  CStaticNode;           // References

//---------------------------------------------------------------------------
class CComponentData : public IComponentData2,
                              IExtendContextMenu,
                              ISnapinHelp2
{
  private:
    ULONG		             m_cRef;
    LPCONSOLE3		       m_ipConsole;           
    LPCONSOLENAMESPACE2  m_ipConsoleNameSpace2;  
    LPIMAGELIST          m_ipScopeImage;     // Caching the image list
    CStaticNode*         m_pStaticNode;
    HSCOPEITEM           m_hStaticNode;
    HBITMAP              m_hImageStrip16;
    HBITMAP              m_hImageStrip32;
    LPOLESTR             m_pszwHelpPath;     //MMC_HELP: Cached help path

  public:
    CComponentData();
    ~CComponentData();
    
  ///////////////////////////////////////////////////////////////////////////
  // Interface IUnknown
  public:
    STDMETHODIMP QueryInterface( REFIID riid, LPVOID *ppv );
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    
  ///////////////////////////////////////////////////////////////////////////
  // Interface IComponentData2
  public:
    HRESULT STDMETHODCALLTYPE Initialize
            ( /*[in]*/ LPUNKNOWN pUnknown );
        
    HRESULT STDMETHODCALLTYPE CreateComponent
            ( /*[out]*/ LPCOMPONENT __RPC_FAR* ppComponent);
        
    HRESULT STDMETHODCALLTYPE Notify
            ( /*[in]*/ LPDATAOBJECT ipDataObject,
              /*[in]*/ MMC_NOTIFY_TYPE MmcEvent,
              /*[in]*/ LPARAM nArg,
              /*[in]*/ LPARAM nParam
            );
        
    HRESULT STDMETHODCALLTYPE Destroy( void);
    
    HRESULT STDMETHODCALLTYPE QueryDataObject
            ( /*[in]*/  MMC_COOKIE uCookie,
              /*[in]*/  DATA_OBJECT_TYPES nEnumType,
              /*[out]*/ LPDATAOBJECT __RPC_FAR* ppDataObject
            );
    
    HRESULT STDMETHODCALLTYPE GetDisplayInfo
            ( /*[out][in]*/ SCOPEDATAITEM __RPC_FAR* pScopeDataItem );
        
    HRESULT STDMETHODCALLTYPE CompareObjects
            ( /*[in]*/ LPDATAOBJECT ipDataObjectA,
              /*[in]*/ LPDATAOBJECT ipDataObjectB
            );

    HRESULT STDMETHODCALLTYPE QueryDispatch
            ( /*[in] */  MMC_COOKIE  nCookie,
              /*[in] */  DATA_OBJECT_TYPES eType,
              /*[out]*/  LPDISPATCH* pipDispatch
            );

  ///////////////////////////////////////////////////////////////////////////
  // Interface IExtendContextMenu
  public:
    HRESULT STDMETHODCALLTYPE AddMenuItems
            ( /*[in]*/ LPDATAOBJECT ipDataObject,
              /*[in]*/ LPCONTEXTMENUCALLBACK ipCallback,
              /*[out,in]*/ long __RPC_FAR* pInsertionAllowed
            );

    HRESULT STDMETHODCALLTYPE Command
            ( /*[in]*/ long lCommandID,
              /*[in]*/ LPDATAOBJECT piDataObject
            );

  ///////////////////////////////////////////////////////////////////////////
  // Interface ISnapinHelp
  public:
    HRESULT STDMETHODCALLTYPE GetHelpTopic( /*[in]*/ LPOLESTR* lpHelpFilePath );
    HRESULT STDMETHODCALLTYPE GetLinkedTopics( /*[in]*/ LPOLESTR* lpHelpFilePath )
                              { return E_NOTIMPL; }

  // Pulic helper methods
  public:
    CStaticNode* GetStaticNode() { return m_pStaticNode;  } 
    LPOLESTR     GetHelpPath(); 
    HRESULT      GetInterface( DWORD dwRequestedInterface,  LONG_PTR* ppInterface );

};

#endif //_CLASS_CCOMPONENTDATA_
