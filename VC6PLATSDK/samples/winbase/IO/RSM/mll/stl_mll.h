/*
 *  This is a part of the Microsoft Source Code Samples.
 *  Copyright 1996 - 1998 Microsoft Corporation.
 *  All rights reserved.
 *
 *	This sample code shows the useage of some portions
 *	of the RSM API and MLL structure.
 *	
 *
 */


#include <ntmsmli.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define RSM_APPSAMPLE_LABEL_EXPORT __declspec(dllexport)

RSM_APPSAMPLE_LABEL_EXPORT DWORD WINAPI ClaimMediaLabel(const BYTE * const pBuffer,
		 			    const DWORD nBufferSize,
					    MediaLabelInfo * const pLabelInfo) ;

RSM_APPSAMPLE_LABEL_EXPORT DWORD WINAPI MaxMediaLabel(DWORD * const pMaxSize) ;

#ifdef __cplusplus
}
#endif

