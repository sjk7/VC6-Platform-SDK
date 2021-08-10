//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      MyMemberSetChangeListener.cpp
//
//  Description:
//      Implementation of CMyMemberSetChangeListener class.
//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyMemberSetChangeListener.h"

//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMyMemberSetChangeListener::CMyMemberSetChangeListener
//
//  Description:
//      Constructor of the CMyMemberSetChangeListener class. 
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CMyMemberSetChangeListener::CMyMemberSetChangeListener( void )
    : m_lcid( LOCALE_NEUTRAL )
    , m_piccCallback( NULL )
{
} //*** CMyMemberSetChangeListener::CMyMemberSetChangeListener

/////////////////////////////////////////////////////////////////////////////
//++
//
//  CMyMemberSetChangeListener::~CMyMemberSetChangeListener
//
//  Description:
//      Destructor of the CMyMemberSetChangeListener class.
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CMyMemberSetChangeListener::~CMyMemberSetChangeListener( void )
{
    // Release the callback interface
    if ( m_piccCallback != NULL )
    {
        m_piccCallback->Release();
    } // if: the callback interface pointer is not NULL 

} //*** CMyMemberSetChangeListener::~CMyMemberSetChangeListener


//***************************************************************************
//
//  IClusCfgMemberSetChangeListener interface
//
//***************************************************************************

//////////////////////////////////////////////////////////////////////////////
//++
//
//  [IClusCfgMemberSetChangeListener]
//  CMyMemberSetChangeListener::Notify
//
//  Description:
//      This function gets called just after a node is added/removed to/from the cluster.
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
CMyMemberSetChangeListener::Notify( IUnknown * punkIn )
{
     //
    // TODO: Modify this code to perform your tasks.
    //
 
    HRESULT                 hr = S_OK;
    WCHAR                   szMessage[] = L"MyMemberSetChangeListener Message: There has been a member set change in this cluster.";

    UNREFERENCED_PARAMETER( punkIn );
    
    if ( m_piccCallback != NULL )
    {
        //
        // Log a message to client and server log file informing that there has
        // been a member set change in this cluster.
        //
        hr = m_piccCallback->SendStatusReport(
                  NULL      // pcszNodeNameIn - Filled in by cluster config server.
                , TASKID_Major_Configure_Resources
                , TASKID_Minor_MyMemberSetChange_Info
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

} //*** CMyMemberSetChangeListener::Notify


//***************************************************************************
//
//  IClusCfgInitialize interface
//
//***************************************************************************

//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMyMemberSetChangeListener::Initialize
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
CMyMemberSetChangeListener::Initialize(
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

} //*** CMyMemberSetChangeListener::Initialize

