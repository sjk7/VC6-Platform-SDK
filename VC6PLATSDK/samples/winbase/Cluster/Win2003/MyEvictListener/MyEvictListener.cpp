//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      MyEvictListener.cpp
//
//  Description:
//      Implementation of CMyEvictListener class.
//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyEvictListener.h"

//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMyEvictListener::CMyEvictListener
//
//  Description:
//      Constructor of the CMyEvictListener class. 
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CMyEvictListener::CMyEvictListener( void )
    : m_lcid( LOCALE_NEUTRAL )
    , m_piccCallback( NULL )
{
} //*** CMyEvictListener::CMyEvictListener

/////////////////////////////////////////////////////////////////////////////
//++
//
//  CMyEvictListener::~CMyEvictListener
//
//  Description:
//      Destructor of the CMyEvictListener class.
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CMyEvictListener::~CMyEvictListener( void )
{
    // Release the callback interface
    if ( m_piccCallback != NULL )
    {
        m_piccCallback->Release();
    } // if: the callback interface pointer is not NULL 

} //*** CMyEvictListener::~CMyEvictListener


//***************************************************************************
//
//  IClusCfgEvictListener interface
//
//***************************************************************************

//////////////////////////////////////////////////////////////////////////////
//++
//
//  [IClusCfgEvictListener]
//  CMyEvictListener::EvictNotify
//
//  Description:
//      This function gets called just after a cluster node has been evicted from the cluster.
//
//  Arguments:
//      pcszNodeNameIn 
//          [in] Pointer to the name of the node that was evicted.
//
//  Return Value:
//      S_OK
//          Operation completed successfully.
//
//      Other HRESULTs
//          An error occurred.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CMyEvictListener::EvictNotify( LPCWSTR pcszNodeNameIn )
{
    //
    // TODO: Modify this code to perform your tasks.
    //
 
    HRESULT         hr = S_OK;
    WCHAR           szMessage[256];

    hr = StringCchPrintfW( 
              szMessage
            , RTL_NUMBER_OF( szMessage )
            , L"MyEvictListener Message: Node '%ws' has been evicted from the cluster."
            , pcszNodeNameIn == NULL ? L"<null>" : pcszNodeNameIn 
            );

    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if: StringCchPrintW failed

    if ( m_piccCallback != NULL )
    {
        //
        // Log a message to client and server log file informing that a node
        // has been evicted from the cluster.
        //
        hr = m_piccCallback->SendStatusReport(
                  NULL      // pcszNodeNameIn - Filled in by cluster config server.
                , TASKID_Major_Client_And_Server_Log
                , IID_NULL
                , 0         // ulMinIn
                , 1         // ulMaxIn
                , 1         // ulCurrentIn
                , hr
                , szMessage
                , NULL      // pftTimeIn - Filled in by cluster config server.
                , NULL      // bstrReferenceIn
                );
        
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:
    } //if: the callback interface pointer is not NULL
    
 Cleanup:
 
    return hr;
 
} //*** CMyEvictListener::EvictNotify


//***************************************************************************
//
//  IClusCfgInitialize interface
//
//***************************************************************************

//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMyEvictListener::Initialize
//
//  Description:
//      Initialize this component.
//
//  Arguments:
//      punkCallbackIn
//          Pointer to the IUnknown interface of a component that implements
//          the IClusCfgCallback interface.
//
//      lcidIn
//          Locale id for this component.
//
//  Return Value:
//      S_OK
//          If the call succeeded.
//
//      E_POINTER
//          The punkCallbackIn param is NULL.
//
//      Other HRESULTs
//          An error occurred.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CMyEvictListener::Initialize(
      IUnknown *   punkCallbackIn
    , LCID         lcidIn
    )
{
    HRESULT hr = S_OK;

    m_lcid = lcidIn;

    if ( m_piccCallback != NULL )
    {
        //
        // Release the callback interface
        //
        m_piccCallback->Release();
        m_piccCallback = NULL;
    } // if: the callback interface pointer is not NULL

    if ( punkCallbackIn != NULL )
    {
        //
        // Query for the IClusCfgCallback interface.
        //
        hr = punkCallbackIn->QueryInterface( __uuidof( IClusCfgCallback ), reinterpret_cast< void ** > ( &m_piccCallback ) );
    } // if: the callback punk is not NULL.
    else
    {
        hr = E_POINTER;
    } // else: the callback punk is NULL.

    return hr;

} //*** CMyEvictListener::Initialize


