//============================================================================
//  FILE: BLRPLATE.h
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

#ifndef _BLRPLATE_H_
#define _BLRPLATE_H_

#include <windows.h>
#include <netmon.h>
#include <stdlib.h>
#include <string.h>

// structure for decoding the header -----------------------------------------
typedef struct _BLRPLATE 
{
    DWORD Signature;
    WORD  Opcode;
    BYTE  Flags;

} BLRPLATEHDR;
typedef BLRPLATEHDR UNALIGNED *PBLRPLATEHDR;

// property ordinals ---------------------------------------------------------
// (These must be kept in sync with the contents of BLRPLATEPropertyTable)
typedef enum
{
    BLRPLATE_SUMMARY = 0,
    BLRPLATE_SIGNATURE,
    BLRPLATE_OPCODE,
    BLRPLATE_FLAGS_SUMMARY,
    BLRPLATE_FLAGS_FLAGS
};

#endif // _BLRPLATE_H_