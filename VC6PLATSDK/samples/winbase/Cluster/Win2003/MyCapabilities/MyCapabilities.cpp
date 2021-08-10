//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      MyCapabilities.cpp
//
//  Description:
//      Implementation of CMyCapabilities class.
//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyCapabilities.h"
#include <winerror.h>
#include <assert.h>

//
// If ALLOW_FAIL is defined, then we will not allow this node to be clustered
// if HrGetApplicationCompatibilityInfo() sets the output parameter to FALSE.
//
// If ALLOW_FAIL is not defined, then we will not prevent this node from being
// clustered if HrGetApplicationCompatibilityInfo() sets the output parameter to FALSE.
//

//
// Uncommenting the "#define ALLOW_FAIL" statement below will cause the Cluster
// Configuration Setup to display an error and fail, otherwise it will display
// a warning and allow to continue.
//

// #define ALLOW_FAIL


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMyCapabilities::CMyCapabilities
//
//  Description:
//      Constructor of the CMyCapabilities class. 
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CMyCapabilities::CMyCapabilities( void )
    : m_lcid( LOCALE_NEUTRAL )
    , m_piccCallback( NULL )
{
} //*** CMyCapabilities::CMyCapabilities

/////////////////////////////////////////////////////////////////////////////
//++
//
//  CMyCapabilities::~CMyCapabilities
//
//  Description:
//      Destructor of the CMyCapabilities class.
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CMyCapabilities::~CMyCapabilities( void )
{
    // Release the callback interface
    if ( m_piccCallback != NULL )
    {
        m_piccCallback->Release();
    } // if: the callback interface pointer is not NULL 

} //*** CMyCapabilities::~CMyCapabilities

//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMyCapabilities::HrGetApplicationCompatibilityInfo
//
//  Description:
//      Gets information about the application's compatibility with
//      clustering.
//
//  Arguments:
//      pfIsAppCompatible   - TRUE = Application is compatible with clustering.
//
//  Return Value:
//      S_OK   - Operation completed successfully.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CMyCapabilities::HrGetApplicationCompatibilityInfo( BOOL * pfIsAppCompatible )
{
    assert( pfIsAppCompatible != NULL );
    
    //
    // TODO: Add decision logic here
    //
    *pfIsAppCompatible = FALSE;

    return S_OK;

} //*** CMyCapabilities::HrGetApplicationCompatibilityInfo


//***************************************************************************
//
//  IClusCfgCapabilities interface
//
//***************************************************************************

//////////////////////////////////////////////////////////////////////////////
//++
//
//  [IClusCfgCapabilities]
//  CMyCapabilities::CanNodeBeClustered
//
//  Description:
//      Checks for application compatibility with clustering. This function 
//      will decide whether this node can be clustered or not.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Node can be clustered.
//
//      S_FALSE
//          Node cannot be clustered.
//
//      Other HRESULTs
//          An error occurred.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CMyCapabilities::CanNodeBeClustered( void )
{
    HRESULT hr = S_OK;
    HRESULT hrCompatibilityInfo = S_OK;
    BOOL    fIsAppCompatible = FALSE;

    //
    // Determine if application is compatible.
    //
    hrCompatibilityInfo = HrGetApplicationCompatibilityInfo( &fIsAppCompatible );
    if ( hrCompatibilityInfo == S_OK )
    {
        if ( fIsAppCompatible == FALSE )
        {
            //
            // The application is not compatible with clustering.
            // Display a warning message in the user interface
            // to alert the user to this condition.
            //
            hr = m_piccCallback->SendStatusReport(
                      NULL      // Sender's node name (filled in by server)
                    , TASKID_Major_Check_Cluster_Feasibility
                    , TASKID_Minor_MyApp_Compat_Info
                    , 0         // ulMinIn
                    , 1         // ulMaxIn
                    , 1         // ulCurrentIn
#if defined( ALLOW_FAIL )
                    , HRESULT_FROM_WIN32( ERROR_NODE_CANNOT_BE_CLUSTERED ) // generates an error (red "x")
#else
                    , S_FALSE   // S_FALSE generates only a warning in the wizard
#endif
                    , L"MyCapabilities message: My application is not compatible with the Cluster Service."
                    , NULL      // pftTimeIn (filled in by server)
                    , NULL      // pcszReferenceIn
                    );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

#if defined( ALLOW_FAIL )
            hr = S_FALSE; // if ALLOW_FAIL is defined we return S_FALSE to error out. 
            goto Cleanup;
#endif
        } // if: app is not compatible with clustering
    } // if: no error getting application compatibility info
    else
    {
        //
        // An error occurred getting application compatibility info.
        // Display an error message in the user interface to alert the
        // user to this condition.
        //

        hr = m_piccCallback->SendStatusReport(
                  NULL      // Sender's node name (filled in by server)
                , TASKID_Major_Check_Cluster_Feasibility
                , TASKID_Minor_MyApp_Compat_Info
                , 0         // ulMinIn
                , 1         // ulMaxIn
                , 1         // ulCurrentIn
                , hr
                , L"MyCapabilities message: Could not determine whether my application is compatible with the Cluster Service or not."
                , NULL      // pftTimeIn (filled in by server)
                , NULL      // pcszReferenceIn
                );

        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

    } // else: error getting application compatibility info.

Cleanup:

    //
    //  If we only want to warn the user, we can re-set hr to S_OK to allow
    //  this node to be clustered anyway, regardless of whether or not this
    //  application is cluster-aware. 
    //
#if ! defined( ALLOW_FAIL )
    hr = S_OK;
#endif

    return hr;

} //*** CMyCapabilities::CanNodeBeClustered


//***************************************************************************
//
//  IClusCfgInitialize interface
//
//***************************************************************************

//////////////////////////////////////////////////////////////////////////////
//++
//
//  [IClusCfgInitialize]
//  CMyCapabilities::Initialize
//
//  Description:
//      Initialize this component.
//
//  Arguments:
//    IN  IUknown * punkCallbackIn
//    IN  LCID      lcidIn
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
CMyCapabilities::Initialize(
    IUnknown *  punkCallbackIn,
    LCID        lcidIn
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

} //*** CMyCapabilities::Initialize

