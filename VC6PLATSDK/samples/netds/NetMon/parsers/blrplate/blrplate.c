//============================================================================
//  FILE: BLRPLATE.c
//
//  Description: BLRPLATE (BLRPLATE) Parser
//
//  Note: info for this parser was gleaned from:
//  rfcXXXX (BLRPLATE)
//
//  Modification History
//
//  Your Name Here      01/01/70    Created
//============================================================================

#include "BLRPLATE.h"

// Globals -------------------------------------------------------------------
HPROTOCOL hBLRPLATE = NULL;
DWORD     Attached = 0;

// Functions -----------------------------------------------------------------
extern VOID   WINAPI BLRPLATE_Register( HPROTOCOL hBLRPLATE);
extern VOID   WINAPI BLRPLATE_Deregister( HPROTOCOL hBLRPLATE);
extern LPBYTE WINAPI BLRPLATE_RecognizeFrame( HFRAME hFrame, 
                                              LPBYTE pMacFrame, 
                                              LPBYTE pBLRPLATEFrame, 
                                              DWORD MacType, 
                                              DWORD BytesLeft, 
                                              HPROTOCOL hPrevProtocol, 
                                              DWORD nPrevProtOffset,
                                              LPDWORD pProtocolStatus,
                                              LPHPROTOCOL phNextProtocol, 
                                              LPDWORD InstData);
extern LPBYTE WINAPI BLRPLATE_AttachProperties( HFRAME hFrame, 
                                                LPBYTE pMacFrame, 
                                                LPBYTE pBLRPLATEFrame, 
                                                DWORD MacType, 
                                                DWORD BytesLeft, 
                                                HPROTOCOL hPrevProtocol, 
                                                DWORD nPrevProtOffset,
                                                DWORD InstData);
extern DWORD  WINAPI BLRPLATE_FormatProperties( HFRAME hFrame, 
                                                LPBYTE pMacFrame, 
                                                LPBYTE pBLRPLATEFrame, 
                                                DWORD nPropertyInsts, 
                                                LPPROPERTYINST p);

VOID WINAPIV BLRPLATE_FormatSummary( LPPROPERTYINST pPropertyInst);

// Define the entry points that we will pass back at dll entry time ----------
ENTRYPOINTS BLRPLATEEntryPoints =
{
    // BLRPLATE Entry Points
    BLRPLATE_Register,
    BLRPLATE_Deregister,
    BLRPLATE_RecognizeFrame,
    BLRPLATE_AttachProperties,
    BLRPLATE_FormatProperties
};


// Property Value Labels -----------------------------------------------------

// OpCodes
LABELED_WORD BLRPLATEOpCodes[] = 
{
    { 1, "Premiere" },
    { 2, "Secondary" },
};
SET BLRPLATEOpCodesSET = {(sizeof(BLRPLATEOpCodes)/sizeof(LABELED_WORD)), 
                          BLRPLATEOpCodes };


// Flags
LABELED_BIT BLRPLATEFlags[] =
{
    // bit 0 = Are aardvarks allowed
    {   0,
	    "No aardvarks",
	    "Aardvarks welcome",
    },

    // bit 1 = Does it include batteries
    {   1,
	    "Batteries not included",
	    "Batteries included",
    },

    // bit 4 = Is this a subsidiary of ACME Spaceworks?
    {   4,
	    "Not a subsidiary of ACME Spaceworks",
	    "ACME Spaceworks subsidiary",
    },

};
SET BLRPLATEFlagsSET = {sizeof(BLRPLATEFlags)/sizeof(LABELED_BIT),
                        BLRPLATEFlags};



// Properties ----------------------------------------------------------------
PROPERTYINFO  BLRPLATEPropertyTable[] = 
{
    // BLRPLATE_SUMMARY (0)
    { 0, 0,
      "Summary",
      "Summary of the BLRPLATE Packet",
      PROP_TYPE_SUMMARY,
      PROP_QUAL_NONE,
      NULL,
      80,
      BLRPLATE_FormatSummary
    },

    // BLRPLATE_SIGNATURE (1)
    { 0, 0,
      "Signature",
      "BLRPLATE Signature",
      PROP_TYPE_STRING,
      PROP_QUAL_NONE,
      NULL,
      80,
      FormatPropertyInstance
    },
    
    // BLRPLATE_OPCODE (2)
    { 0, 0,
      "Opcode",
      "BLRPLATE Packet Type",
      PROP_TYPE_WORD,
      PROP_QUAL_LABELED_SET,
      &BLRPLATEOpCodesSET,
      80,
      FormatPropertyInstance
    },

    // BLRPLATE_FLAGS_SUMMARY (3)
    { 0, 0,
      "Flags Summary",
      "BLRPLATE Flags Summary",
      PROP_TYPE_BYTE,
      PROP_QUAL_NONE,
      NULL,
      80,
      FormatPropertyInstance
    },

    // BLRPLATE_FLAGS_FLAGS (4)
    { 0, 0,
      "Flags",
      "BLRPLATE Flags",
      PROP_TYPE_BYTE,
      PROP_QUAL_FLAGS,
      &BLRPLATEFlagsSET,
      3 * 80,
      FormatPropertyInstance
    },


};
DWORD nNumBLRPLATEProps = (sizeof(BLRPLATEPropertyTable)/sizeof(PROPERTYINFO));

//============================================================================
// 
//  AutoInstall - return all of the information neede to install us
//
//  Modification history:
//                                                                            
//============================================================================
PPF_PARSERDLLINFO WINAPI ParserAutoInstallInfo() 
{
    PPF_PARSERDLLINFO pParserDllInfo; 
    PPF_PARSERINFO    pParserInfo;
    DWORD NumProtocols;
    /*
    DWORD NumHandoffs;
    PPF_HANDOFFSET    pHandoffSet;
    PPF_HANDOFFENTRY  pHandoffEntry;
    */

    /*
    DWORD NumFollows;
    PPF_FOLLOWSET     pFollowSet;
    PPF_FOLLOWENTRY   pFollowEntry;
    */

    // Base structure ========================================================

    // Allocate memory for parser info:
    NumProtocols = 1;
    pParserDllInfo = (PPF_PARSERDLLINFO)HeapAlloc( GetProcessHeap(),
                                                   HEAP_ZERO_MEMORY,
                                                   sizeof( PF_PARSERDLLINFO ) +
                                                   NumProtocols * sizeof( PF_PARSERINFO) );
    if( pParserDllInfo == NULL)
    {
        return NULL;
    }       
    
    // fill in the parser DLL info
    pParserDllInfo->nParsers = NumProtocols;

    // fill in the individual parser infos...

    // BLRPLATE ==============================================================
    pParserInfo = &(pParserDllInfo->ParserInfo[0]);
    wsprintf( pParserInfo->szProtocolName, "BLRPLATE" );
    wsprintf( pParserInfo->szComment,      "Boilerplate Protocol" );
    wsprintf( pParserInfo->szHelpFile,     "");

    /*
    // the incoming handoff set ----------------------------------------------
    // allocate
    NumHandoffs = 1;
    pHandoffSet = (PPF_HANDOFFSET)HeapAlloc( GetProcessHeap(),
                                             HEAP_ZERO_MEMORY,
                                             sizeof( PF_HANDOFFSET ) +
                                             NumHandoffs * sizeof( PF_HANDOFFENTRY) );
    if( pHandoffSet == NULL )
    {
        // just return early
        return pParserDllInfo;
    }

    // fill in the incoming handoff set
    pParserInfo->pWhoHandsOffToMe = pHandoffSet;
    pHandoffSet->nEntries = NumHandoffs;

    // TCP PORT FFFF
    pHandoffEntry = &(pHandoffSet->Entry[0]);
    wsprintf( pHandoffEntry->szIniFile,    "TCPIP.INI" );
    wsprintf( pHandoffEntry->szIniSection, "TCP_HandoffSet" );
    wsprintf( pHandoffEntry->szProtocol,   "BLRPLATE" );
    pHandoffEntry->dwHandOffValue =        0xFFFF;
    pHandoffEntry->ValueFormatBase =       HANDOFF_VALUE_FORMAT_BASE_DECIMAL;    
    */

    /*
    // the outgoing follow set -----------------------------------------------
    // allocate
    NumFollows = 1;
    pFollowSet = (PPF_FOLLOWSET)HeapAlloc( GetProcessHeap(),
                                           HEAP_ZERO_MEMORY,
                                           sizeof( PF_FOLLOWSET ) +
                                           NumFollows * sizeof( PF_FOLLOWENTRY) );
    if( pFollowSet == NULL )
    {
        // just return early
        return pParserDllInfo;
    }

    // fill in the outgoing follow set
    pParserInfo->pWhoCanFollowMe = pFollowSet;
    pFollowSet->nEntries = NumFollows;

    // SMB
    pFollowEntry = &(pFollowSet->Entry[0]);
    wsprintf( pFollowEntry->szProtocol,   "SMB" );
    */

    return pParserDllInfo;
}


//============================================================================
//  Function: DllMain
// 
//  Description: (Called by the OS) Tell the kernel about our entry points.
//
//  Modification History
//
//  Your Name Here      01/01/70    Created
//=============================================================================
BOOL WINAPI DllMain( HANDLE hInstance, ULONG Command, LPVOID Reserved)
{

    // what type of call is this
    switch( Command )
    {
        case DLL_PROCESS_ATTACH:
            // are we loading for the first time?
            if( Attached == 0 )
            {
                // the first time in we need to tell the kernel 
                // about ourselves
                hBLRPLATE = CreateProtocol( "BLRPLATE", 
                                            &BLRPLATEEntryPoints, 
                                            ENTRYPOINTS_SIZE);
            }
            Attached++;
            break;

        case DLL_PROCESS_DETACH:
            // are we detaching our last instance?
            Attached--;
            if( Attached == 0 )
            {
                // last guy out needs to clean up
                DestroyProtocol( hBLRPLATE);
            }
            break;
    }

    // Netmon parsers ALWAYS return TRUE.
    return TRUE;
}

//============================================================================
//  Function: BLRPLATE_Register
// 
//  Description: Create our property database and handoff sets.
//
//  Modification History
//
//  Your Name Here      01/01/70    Created
//============================================================================
void BHAPI BLRPLATE_Register( HPROTOCOL hBLRPLATE)
{
    WORD  i;

    // tell the kernel to make reserve some space for our property table
    CreatePropertyDatabase( hBLRPLATE, nNumBLRPLATEProps);

    // add our properties to the kernel's database
    for( i = 0; i < nNumBLRPLATEProps; i++)
    {
        AddProperty( hBLRPLATE, &BLRPLATEPropertyTable[i]);
    }
}


//============================================================================
//  Function: BLRPLATE_Deregister
// 
//  Description: Destroy our property database and handoff set
//
//  Modification History
//
//  Your Name Here      01/01/70    Created
//============================================================================
VOID WINAPI BLRPLATE_Deregister( HPROTOCOL hBLRPLATE)
{
    // tell the kernel that it may now free our database
    DestroyPropertyDatabase( hBLRPLATE);
}


//============================================================================
//  Function: BLRPLATE_RecognizeFrame
// 
//  Description: Determine whether we exist in the frame at the spot 
//               indicated. We also indicate who (if anyone) follows us
//               and how much of the frame we claim.
//
//  Modification History
//
//  Your Name Here      01/01/70    Created
//============================================================================
LPBYTE BHAPI BLRPLATE_RecognizeFrame( HFRAME      hFrame,         
                                      LPBYTE      pMacFrame,      
                                      LPBYTE      pBLRPLATEFrame, 
                                      DWORD       MacType,        
                                      DWORD       BytesLeft,      
                                      HPROTOCOL   hPrevProtocol,  
                                      DWORD       nPrevProtOffset,
                                      LPDWORD     pProtocolStatus,
                                      LPHPROTOCOL phNextProtocol,
                                      LPDWORD     InstData)       
{
    // For now, just assume that if we got called,
    // then the packet does contain us and we go to the end of the frame
    *pProtocolStatus = PROTOCOL_STATUS_CLAIMED;
    return NULL;
}


//============================================================================
//  Function: BLRPLATE_AttachProperties
// 
//  Description: Indicate where in the frame each of our properties live.
//
//  Modification History
//
//  Your Name Here      01/01/70    Created
//============================================================================
LPBYTE BHAPI BLRPLATE_AttachProperties( HFRAME      hFrame,         
                                        LPBYTE      pMacFrame,     
                                        LPBYTE      pBLRPLATEFrame,   
                                        DWORD       MacType,        
                                        DWORD       BytesLeft,      
                                        HPROTOCOL   hPrevProtocol,  
                                        DWORD       nPrevProtOffset,
                                        DWORD       InstData)       

{
    // apply the header overlay in order to decode the protocol
    PBLRPLATEHDR pBLRPLATEHdr = (PBLRPLATEHDR)pBLRPLATEFrame;

    //
    // Attach Properties...
    //

    // summary line
    AttachPropertyInstance( hFrame,
                            BLRPLATEPropertyTable[BLRPLATE_SUMMARY].hProperty,
                            (WORD)BytesLeft,
                            (LPBYTE)pBLRPLATEFrame,
                            0, 0, 0);

    // signature
    AttachPropertyInstance( hFrame,
                            BLRPLATEPropertyTable[BLRPLATE_SIGNATURE].hProperty,
                            sizeof(DWORD),
                            &(pBLRPLATEHdr->Signature),
                            0, 1, 0);

    // opcode
    AttachPropertyInstance( hFrame,
                            BLRPLATEPropertyTable[BLRPLATE_OPCODE].hProperty,
                            sizeof(WORD),
                            &(pBLRPLATEHdr->Opcode),
                            0, 1, 0);

    // flags summary
    AttachPropertyInstance( hFrame,
                            BLRPLATEPropertyTable[BLRPLATE_FLAGS_SUMMARY].hProperty,
                            sizeof(BYTE),
                            &(pBLRPLATEHdr->Flags),
                            0, 1, 0);

    // flags decode
    AttachPropertyInstance( hFrame,
                            BLRPLATEPropertyTable[BLRPLATE_FLAGS_FLAGS].hProperty,
                            sizeof(BYTE),
                            &(pBLRPLATEHdr->Flags),
                            0, 2, 0);

    return NULL;
}


//============================================================================
//  Function: BLRPLATE_FormatProperties
// 
//  Description: Format the given properties on the given frame.
//
//  Modification History
//
//  Your Name Here      01/01/70    Created
//============================================================================
DWORD BHAPI BLRPLATE_FormatProperties( HFRAME          hFrame,
                                       LPBYTE          pMacFrame,
                                       LPBYTE          pBLRPLATEFrame,
                                       DWORD           nPropertyInsts,
                                       LPPROPERTYINST  p)
{
    // loop through the property instances
    while( nPropertyInsts-- > 0)
    {
        // and call the formatter for each
        ( (FORMAT)(p->lpPropertyInfo->InstanceData) )( p);
        p++;
    }

    return NMERR_SUCCESS;
}


//============================================================================
//  Function: BLRPLATE_FormatSummary
// 
//  Description: The custom formatter for the summary property
//
//  Modification History
//
//  Your Name Here      01/01/70    Created
//============================================================================
VOID WINAPIV BLRPLATE_FormatSummary( LPPROPERTYINST pPropertyInst)
{
    LPBYTE       pReturnedString = pPropertyInst->szPropertyText;
    PBLRPLATEHDR pBLRPLATE = (PBLRPLATEHDR)(pPropertyInst->lpData);
    char*        szTempString;

    // fetch the Opcode name
    szTempString = LookupWordSetString( &BLRPLATEOpCodesSET,
                                        pBLRPLATE->Opcode );
    if( szTempString == NULL )
    {
        szTempString = "Unknown";
    }

    // print "Opcode: <Opcode Name> (<Opcode number>)"
    wsprintf ( pReturnedString, 
               "Opcode: %s (%d)", 
               szTempString,
               pBLRPLATE->Opcode);
}
