//============================================================================
//  MODULE: BLRPLATE.cpp
//
//  Description:
//
//  BLRPLATE expert module
//
//  Modification History:
//
//  Your Name Here      01/01/70    Created
//============================================================================
#define STRICT 1

#include "BLRPLATE.h"
#include "resrc1.h"

//////////////////////////////////////////////////////////////////////////////
// Global Variables
HINSTANCE g_hInstance;

char g_StatusString[MAX_PATH];
char g_Col0Name[MAX_PATH];
char g_Col1Name[MAX_PATH];
char g_ExpertName[MAX_PATH];
char g_EventName[MAX_PATH];
char g_Justification[MAX_PATH];


//////////////////////////////////////////////////////////////////////////////
// The DLL entry point
//
BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID pvReserved)
{
    switch( ulReason )
    {
        case DLL_PROCESS_ATTACH:
            g_hInstance = hInstance;
            break;

        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// The Expert Registration entry point
//
BOOL WINAPI Register( PEXPERTENUMINFO lpExpertInfo)
{
    // fill in the expert info data structure
    // TODO: Choose the proper flags
    lpExpertInfo->Flags = EXPERT_ENUM_FLAG_VIEWER_PRIVATE |
                          EXPERT_ENUM_FLAG_CONFIGURABLE;
    lpExpertInfo->Version = 1;
    LoadString( g_hInstance, IDS_EXPERTNAME, lpExpertInfo->szName, MAX_PATH);
    LoadString( g_hInstance, IDS_COMMENT, lpExpertInfo->szDescription, MAX_PATH);
    LoadString( g_hInstance, IDS_AUTHOR, lpExpertInfo->szVendor, MAX_PATH);
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// The Expert Configuration entry point
//
BOOL WINAPI Configure( HEXPERTKEY hExpertKey, 
                       PEXPERTCONFIG* ppConfig,
                       PEXPERTSTARTUPINFO pStartupInfo,
                       DWORD StartupFlags,
                       HWND hWnd )
{
    // is the startup info from a right mouse click?
    if( (pStartupInfo == NULL) &&
        (StartupFlags & EXPERT_STARTUP_FLAG_USE_STARTUP_DATA_OVER_CONFIG_DATA) )
    {
        // The user started this expert by right mouse clicking...

        // TODO: pull the relevant data out of the pStartupInfo
        // and put it in the (possibly resized) ppConfig
    }

    // call the dialog
    return ConfigBLRPLATEDlg_Do(hWnd, 
                                (PBLRPLATECONFIG *)ppConfig, 
                                hExpertKey);
}


//////////////////////////////////////////////////////////////////////////////
// The Expert Start entry point
//
BOOL WINAPI Run( HEXPERTKEY hExpertKey, 
                 PEXPERTCONFIG lpConfig, 
                 PEXPERTSTARTUPINFO pStartupInfo,
                 DWORD StartupFlags,
                 HWND hwnd)
{
    DWORD                   rc;
    EXPERTSTATUS            Status;

    HFILTER                 hFilter;
    FILTEROBJECT2            FilterObj;

    PBLRPLATECONFIG         pBLRPLATEConfig = (PBLRPLATECONFIG)lpConfig;

    PNMEVENTDATA            pEvent;

    DWORD                   TotalFrames;
    DWORD                   CurrentFrameNumber;
    BYTE                    CurrentPercentDone;
    BYTE                    ReportedPercentDone;

    EXPERTFRAMEDESCRIPTOR   FrameDescriptor;

    // -----------------------------------------------------------------------
    // Zero out all of our stack data structures
    memset( &Status, 0, sizeof(EXPERTSTATUS) );
    memset( &FilterObj, 0, sizeof(FILTEROBJECT) );
    memset( &FrameDescriptor, 0, sizeof(EXPERTFRAMEDESCRIPTOR) );


    // -----------------------------------------------------------------------
    // Set up our status structure and tell the world that we are initializing
    Status.Frame       = 0;
    Status.PercentDone = 0;
    Status.Status      = EXPERTSTATUS_STARTING;
    Status.SubStatus   = 0;    
    LoadString(g_hInstance, IDS_INITIALIZING, Status.szStatusText, MAX_PATH);
    rc = ExpertIndicateStatus(hExpertKey, 
                              Status.Status,
                              Status.SubStatus,
                              Status.szStatusText,
                              Status.PercentDone);
    if( rc == NMERR_EXPERT_TERMINATE )
    {
        // we have been asked to terminate
        return TRUE;
    }
    else if( rc != NMERR_SUCCESS )
    {
        // something bad happened
        return FALSE;
    }


    // -----------------------------------------------------------------------
    // prefill the event
    // TODO: the 2s below should be mondified to reflect the desired event
    // TODO: this code needs to be copied for any extra types of events
    pEvent = (PNMEVENTDATA)ExpertAllocMemory( hExpertKey,
                                              sizeof(NMEVENTDATA) +
                                              2 * sizeof(NMCOLUMNINFO),
                                              &rc);
    if( pEvent == NULL )
    {
        LoadString(g_hInstance, IDS_CANTALLOCMEM, g_StatusString, MAX_PATH);
        ExpertIndicateStatus( hExpertKey, 
                              EXPERTSTATUS_PROBLEM,
                              0,
                              g_StatusString,
                              0);
        return FALSE;
    }

    pEvent->Version      = 0;
    pEvent->EventIdent   = 1;
    pEvent->Flags        = NMEVENTFLAG_DO_NOT_DISPLAY_MACHINE;
    pEvent->Severity     = NMEVENT_SEVERITY_INFORMATIONAL;
    pEvent->NumColumns   = 2;
    memset( &(pEvent->SysTime), 0, sizeof(SYSTEMTIME));
    pEvent->Justification= g_Justification;
    LoadString(g_hInstance, IDS_EXPERTNAME, g_ExpertName, MAX_PATH);
    pEvent->szSourceName = g_ExpertName;
    LoadString(g_hInstance, IDS_EVENTNAME, g_EventName, MAX_PATH);
    pEvent->szEventName  = g_EventName;
//    pEvent->szUrl        = NULL;
    pEvent->szDescription= NULL;
    pEvent->szMachine    = NULL;

    LoadString(g_hInstance, IDS_COLZERO, g_Col0Name, MAX_PATH);
    pEvent->Column[0].szColumnName = g_Col0Name;
    pEvent->Column[0].VariantData.Type = NMCOLUMNTYPE_IPADDR;
    LoadString(g_hInstance, IDS_COLONE, g_Col1Name, MAX_PATH);
    pEvent->Column[1].szColumnName = g_Col1Name;
    pEvent->Column[1].VariantData.Type = NMCOLUMNTYPE_IPADDR;

    // ------------------------------------------------------------------------
    // create a filter which will only find frames which we are interested in
    hFilter = CreateFilter();
    if( hFilter == NULL )
    {
        // can't make filter
        LoadString(g_hInstance, IDS_CANTCREATEFILTER, g_StatusString, MAX_PATH);
        ExpertIndicateStatus( hExpertKey, 
                              EXPERTSTATUS_PROBLEM,
                              0,
                              g_StatusString,
                              0);
        return FALSE;
    }

    // TODO: Fill the filter
    // This example returns only frames which contain TCP
    FilterObj.Action = FILTERACTION_PROTOCOLEXIST;
    FilterObj.hProtocol = GetProtocolFromName( "TCP" );
    rc = FilterAddObject( hFilter, &FilterObj);
    if( rc != NMERR_SUCCESS )
    {
        // can't add to the filter
        LoadString(g_hInstance, IDS_CANTADDTOFILTER, g_StatusString, MAX_PATH);
        ExpertIndicateStatus( hExpertKey, 
                              EXPERTSTATUS_PROBLEM,
                              0,
                              g_StatusString,
                              0);
        DestroyFilter( hFilter);
        return FALSE;
    }

    // -----------------------------------------------------------------------
    // send the first status message which will indicate that we are now running
    rc = ExpertIndicateStatus( hExpertKey, 
                               EXPERTSTATUS_RUNNING,
                               0,
                               "",
                               0);
    if( rc == NMERR_EXPERT_TERMINATE )
    {
        // we were terminated
        DestroyFilter( hFilter );
        return FALSE;
    }

    // -----------------------------------------------------------------------
    // the main loop
    TotalFrames = GetCaptureTotalFrames( pStartupInfo->hCapture);
    CurrentFrameNumber = -1;
    do
    {
        // get the next frame which passes both the user's filter and ours
        rc = ExpertGetFrame( hExpertKey,
                             GET_FRAME_NEXT_FORWARD,
                             ( FLAGS_DEFER_TO_UI_FILTER | 
                               FLAGS_ATTACH_PROPERTIES ),
                             CurrentFrameNumber,
                             hFilter,
                             &FrameDescriptor);
        if( rc == NMERR_EXPERT_TERMINATE )
        {
            // we were terminated
            DestroyFilter( hFilter );
            return FALSE;
        }
        if( rc != NMERR_SUCCESS )
        {
            // we failed to get a frame, break out of the loop
            break;
        }

        // got a frame, which one?
        CurrentFrameNumber = FrameDescriptor.FrameNumber;

        // update our status if we need to
        CurrentPercentDone = (BYTE)((CurrentFrameNumber*100)
                                         /TotalFrames);
        if( CurrentPercentDone > ReportedPercentDone )
        {
            // new number
            rc = ExpertIndicateStatus( hExpertKey, 
                                         EXPERTSTATUS_RUNNING,
                                         0,
                                         "",
                                         CurrentPercentDone);
            ReportedPercentDone = CurrentPercentDone;
            if( rc == NMERR_EXPERT_TERMINATE )
            {
                // we were terminated
                DestroyFilter( hFilter );
                return FALSE;
            }
        }

        // TODO: This is were the expert actually uses the frame 
        // returned by either sending an event or recording information
        // for a summary type event later.

    } while( rc == NMERR_SUCCESS );

    // -----------------------------------------------------------------------
    // TODO: submit summary type events here

    // -----------------------------------------------------------------------
    // we are done
    DestroyFilter( hFilter );
    return rc;
}

    