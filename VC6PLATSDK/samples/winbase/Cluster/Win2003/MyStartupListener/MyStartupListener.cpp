//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      MyStartupListener.cpp
//
//  Description:
//      Implementation of CMyStartupListener class.
//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyStartupListener.h"

//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMyStartupListener::CMyStartupListener
//
//  Description:
//      Constructor of the CMyStartupListener class. 
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CMyStartupListener::CMyStartupListener( void )
    : m_lcid( LOCALE_NEUTRAL )
    , m_piccCallback( NULL )
{
} //*** CMyStartupListener::CMyStartupListener

/////////////////////////////////////////////////////////////////////////////
//++
//
//  CMyStartupListener::~CMyStartupListener
//
//  Description:
//      Destructor of the CMyStartupListener class.
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CMyStartupListener::~CMyStartupListener( void )
{
    // Release the callback interface
    if ( m_piccCallback != NULL )
    {
        m_piccCallback->Release();
    } // if: the callback interface pointer is not NULL 

} //*** CMyStartupListener::~CMyStartupListener


//***************************************************************************
//
//  IClusCfgStartupListener interface
//
//***************************************************************************

//////////////////////////////////////////////////////////////////////////////
//++
//
//  [IClusCfgStartupListener]
//  CMyStartupListener::Notify
//
//  Description:
//      This function gets called just after the cluster service has started.
//
//  Arguments:
//      punkIn
//          Pointer to a COM object that implements
//          IClusCfgResourceTypeCreate.
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
CMyStartupListener::Notify( IUnknown * punkIn )
{
    //
    // TODO: Modify this code to perform your tasks.
    //

    HRESULT         hr = S_OK;
    WCHAR           szMessage[] = L"MyStartupListener Message: The Cluster Service has started successfully.";

    UNREFERENCED_PARAMETER( punkIn );

    if ( m_piccCallback != NULL )
    {
        //
        // Log a message to client and server log file informing that the
        // cluster service has started on this machine.
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

} //*** CMyStartupListener::Notify


//***************************************************************************
//
//  IClusCfgInitialize interface
//
//***************************************************************************

//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMyStartupListener::Initialize
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
CMyStartupListener::Initialize(
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

} //*** CMyStartupListener::Initialize


