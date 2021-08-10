/*
*	Copyright (c) Microsoft Corportation. All rights reserved.
*/

/*
 *	preprocessor section
 */
#ifndef	__WAVE_H__
#define	__WAVE_H__

#include "DlgSrc.h"

/*
 *	constants
 */
#define	WAVE_TOGGLE_DESTINATION	0
#define	WAVE_TOGGLE_DISABLE		0
#define	WAVE_TOGGLE_ALLOW		1

/*
 *	functions
 */

// 
//	open a wave file, validate format and extract parameters
//
HANDLE  WaveOpenFile( LPCSTR, WAVEFORMATEX**, PULONG );

// 
//	write the mixed wave file
//
BOOL    WaveSaveFile( LPCSTR, WAVEFORMATEX*, PVOID, ULONG );

// 
//	callback function for waveOut calls
//
void CALLBACK   WavePlayFileCB( HWAVEOUT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR );

//
//	toggle every dialog's playable state
//
void WaveTogglePlayback( CDlgSrc *, const BOOL );

//
//	traps an error code
//
BOOL TrapMMError( MMRESULT, LPCSTR );

/*
 *	globals
 */

extern HWAVEOUT     g_hwo;


#endif	//	__WAVE_H__