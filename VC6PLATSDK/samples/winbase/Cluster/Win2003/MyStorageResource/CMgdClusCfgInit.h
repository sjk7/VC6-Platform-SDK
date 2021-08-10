//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      CMgdClusCfgInit.h
//
//  Description:
//      Header file for the CMgdClusCfgInit class
//
//  Implementation Files:
//      CMgdClusCfgInit.cpp
//
//  Description:
//      Header file for the CMgdClusCfgInit class
//
//////////////////////////////////////////////////////////////////////////////

#pragma once


//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"


//////////////////////////////////////////////////////////////////////////////
//++
//
//  class CMgdClusCfgInit
//
//  Description:
//      The CMgdClusCfgInit class is a base class implementation of the
//      IClusCfgInitialize interface.
//
//--
//////////////////////////////////////////////////////////////////////////////
class CMgdClusCfgInit
    : public IClusCfgInitialize
    , public CComObjectRoot
{
public:

    CMgdClusCfgInit( void );
    virtual ~CMgdClusCfgInit( void );

    //
    // IClusCfgInitialize interface
    //

    STDMETHOD( Initialize )( IUnknown * punkCallbackIn, LCID lcidIn );

    //
    // Public member functions.
    //

    IClusCfgCallback *  GetCallback( void )     { return m_picccCallback; }
    LCID                GetLCID( void )         { return m_lcid; }
    BSTR                GetNodeName( void )     { return m_bstrNodeName; }
    BSTR                GetDllName( void )      { return m_bstrDllName; }
    BSTR                GetResTypeName( void )  { return m_bstrResTypeName; }
    BSTR                GetDisplayName( void )  { return m_bstrDisplayName; }

    STDMETHOD( HrSendStatusReport )(
          CLSID      clsidTaskMajorIn
        , CLSID      clsidTaskMinorIn
        , ULONG      ulMinIn
        , ULONG      ulMaxIn
        , ULONG      ulCurrentIn
        , HRESULT    hrStatusIn
        , LPCWSTR    pcszDescriptionIn
        , LPCWSTR    pcszReferenceIn
        ...
        );

    STDMETHOD( HrSendStatusReport )(
          CLSID      clsidTaskMajorIn
        , CLSID      clsidTaskMinorIn
        , ULONG      ulMinIn
        , ULONG      ulMaxIn
        , ULONG      ulCurrentIn
        , HRESULT    hrStatusIn
        , LPCWSTR    pcszDescriptionIn
        , UINT       idsReferenceIn
        ...
        );

    STDMETHOD( HrSendStatusReport )(
          CLSID     clsidTaskMajorIn
        , CLSID     clsidTaskMinorIn
        , ULONG     ulMinIn
        , ULONG     ulMaxIn
        , ULONG     ulCurrentIn
        , HRESULT   hrStatusIn
        , UINT      idsDescriptionIn
        , UINT      idsReferenceIn
        ...
        );

private:

    //
    // Private member functions.
    //

    STDMETHOD( SendStatusReport )(
          CLSID     clsidTaskMajorIn
        , CLSID     clsidTaskMinorIn
        , ULONG     ulMinIn
        , ULONG     ulMaxIn
        , ULONG     ulCurrentIn
        , HRESULT   hrStatusIn
        , LPCWSTR   pcszDescriptionIn
        , LPCWSTR   pcszReferenceIn
        );

    //
    // Private copy constructor to avoid copying.
    //

    CMgdClusCfgInit( const CMgdClusCfgInit & rSrcIn );

    //
    // Private assignment operator to avoid copying.
    //

    const CMgdClusCfgInit & operator = ( const CMgdClusCfgInit & rSrcIn );

    //
    // IClusCfgCallback info.
    //

    LCID                m_lcid;
    IClusCfgCallback *  m_picccCallback;
    BSTR                m_bstrNodeName;

    //
    // Resource dll, resource type, and resource type display names.
    //

    BSTR    m_bstrDllName;
    BSTR    m_bstrResTypeName;
    BSTR    m_bstrDisplayName;

}; //*** class CMgdClusCfgInit
