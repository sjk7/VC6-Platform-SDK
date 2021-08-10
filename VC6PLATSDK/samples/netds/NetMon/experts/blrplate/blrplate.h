//============================================================================
//  MODULE: BLRPLATE.h
//
//  Description:
//
//  BLRPLATE expert module
//
//  Modification History:
//
//  Your Name Here      01/01/70    Created
//============================================================================

#ifndef _BLRPLATE_H_
#define _BLRPLATE_H_

#include <windows.h>
#include <netmon.h>

#pragma warning(disable:4200)

//////////////////////////////////////////////////////////////////////////////
// Global Variables
extern HINSTANCE g_hInstance;
extern char g_StatusString[];

//////////////////////////////////////////////////////////////////////////////
// Data Structures

// BLRPLATECONFIG
typedef struct _BLRPLATECONFIG
{
    DWORD nTotalLength;

    // TODO: put interesting Info here.

} BLRPLATECONFIG;
typedef BLRPLATECONFIG *PBLRPLATECONFIG;


//////////////////////////////////////////////////////////////////////////////
// Function Prototypes

// In BLRPLATE.cpp
BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID pvReserved);
BOOL WINAPI Register( PEXPERTENUMINFO lpExpertInfo);
BOOL WINAPI Configure( HEXPERTKEY hExpertKey, 
                       PEXPERTCONFIG* ppConfig,
                       PEXPERTSTARTUPINFO pStartupInfo,
                       DWORD StartupFlags,
                       HWND hWnd );
BOOL WINAPI Run( HEXPERTKEY hExpertKey, PEXPERTCONFIG lpConfig, HWND hwnd);

// In Config.cpp
BOOL ConfigBLRPLATEDlg_Do(HWND hwnd, 
                          PBLRPLATECONFIG * ppBLRPLATEConfig, 
                          HEXPERTKEY hExpertKey);


#pragma warning(default:4200)

#endif // _BLRPLATE_H_