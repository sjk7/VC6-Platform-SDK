/*
 *  This is a part of the Microsoft Source Code Samples.
 *  Copyright 1996 - 1998 Microsoft Corporation.
 *  All rights reserved.
 *
 *	This sample code shows the usage of some portions
 *	of the NTMS API.
 *	
 *	Return codes are, for the most part, not checked in
 *	this code. See the Programmer's reference for error
 *	return information.
 *
 *  DLL must be built with standard calling convention (/Gz)
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Copyright 1997 - 1998 Microsoft Corporation.  All Rights Reserved. *
 */
#include <windows.h>
#include "..\inc\stl.h"
#include "STL_mll.h"

static DWORD GetMediaGuid(wchar_t *pDescription, WORD size, GUID &gMediaGuid);


RSM_APPSAMPLE_LABEL_EXPORT DWORD WINAPI ClaimMediaLabel(const BYTE * const pBuffer, const DWORD nBufferSize,
		      MediaLabelInfo * const pLabelInfo)
{
	DWORD nError = NO_ERROR;
	STL_LABEL *pLabel;
	GUID gMediaGuid;


	// Go through the label and look at each field.  If something is seen that isn't STL, then bail
	// If this MLL is to recognize all instances of STL, then perhaps it should only check the first
	// two fields, since multiple applications and vendors could write STL.  If the intent is to 
	// only recognize STL written by a particular app then the vendor and app fields are checked. That's
	// the way this sample is done.
	pLabel = (STL_LABEL *) pBuffer;
	if (wcsncmp ((wchar_t *)pLabel->LabelType, STL_LABEL_LabelType, STL_LABEL_LabelTypeSize/sizeof(WCHAR)))
		return ERROR_BAD_FORMAT;

	if(wcsncmp((wchar_t *)pLabel->LabelVersion, STL_LABEL_Version, STL_LABEL_VersionSize/sizeof(WCHAR)))
		return ERROR_BAD_FORMAT;

	if(wcsncmp((wchar_t *)pLabel->Vendor, STL_LABEL_Vendor, STL_LABEL_VendorSize/sizeof(WCHAR)))
		return ERROR_BAD_FORMAT;

	if(wcsncmp((wchar_t *)pLabel->Application, STL_LABEL_Application, STL_LABEL_ApplicationSize/sizeof(WCHAR)))
		return ERROR_BAD_FORMAT;


	// OK, found an instance of STL, now populate the MediaLabelInfo structure to pass back to RSM
	memset(pLabelInfo, 0, sizeof(MediaLabelInfo));
	wcsncpy(pLabelInfo->LabelType, (wchar_t *) pLabel->LabelType, (STL_LABEL_LabelTypeSize/sizeof(WCHAR))-1);

	if(GetMediaGuid((wchar_t *)pLabel->MediaID, STL_LABEL_MediaIDSize, gMediaGuid) == NO_ERROR)
	{
		pLabelInfo->LabelIDSize = sizeof(gMediaGuid);
		memcpy(pLabelInfo->LabelID, &gMediaGuid, sizeof(gMediaGuid));
	}
	else
		// Whoops, we got a valid STL instance, but the app screwed up the GUID
		// A real MLL could try to recover, or just bail.  Here we bail.
		return ERROR_BAD_FORMAT;

	wcsncpy(pLabelInfo->LabelAppDescr, (wchar_t *) pLabel->TapeName, (STL_LABEL_TapeNameSize/sizeof(WCHAR))-1); 

	return NO_ERROR;
}


RSM_APPSAMPLE_LABEL_EXPORT DWORD WINAPI MaxMediaLabel (DWORD * const pMaxSize)
{
	// local variables 
	DWORD nError = NO_ERROR ;

	// set the max size for the sample label in terms of 512 blocks
	*pMaxSize = 512 * ((sizeof(STL_LABEL) / 512)+1);

	return nError ;
}

#define HEX_0 L'0'
#define HEX_9 L'9'
#define HEX_A L'A'
#define HEX_F L'F'
#define OUR_STRING wchar_t*
#define OUR_BAR L'|'
#define OUR_BRACE L'{'

static DWORD ConvertHex(const wchar_t * str, const int length)
{
	DWORD value = 0;
	for(int i=0;i<length;i++){
		value = value << 4;
		if(str[i] >= HEX_A && str[i] <= HEX_F){
			value += str[i]-'A'+10;
		} else if(str[i] >= HEX_0 && str[i] <= HEX_9){
			value += str[i]-HEX_0;
		}
	}
	return value;
}

static DWORD GetMediaGuid(wchar_t * pDescription, WORD size, GUID &gMediaGuid)
{

    int numChars = size / sizeof(wchar_t);

	wchar_t * pId = pDescription;

	// check all the "syntactic sugar" characters as a check to insure this
	// is a valid GUID
	if((pId[0] != '{') ||
		(pId[9] != '-') ||
		(pId[14] != '-') ||
		(pId[19] != '-') ||
		(pId[24] != '-') ||
		(pId[37] != '}'))
		return ERROR_BAD_FORMAT;
		
	// now pick the GUID fields out of the string		
	gMediaGuid.Data1 = ConvertHex(pId,8);
	pId += 9;
	gMediaGuid.Data2 = (WORD)ConvertHex(pId,4);
	pId += 5;
	gMediaGuid.Data3 = (WORD)ConvertHex(pId,4);
	pId += 5;
	int i;
	for(i=0;i<2;i++){
		gMediaGuid.Data4[i] = (BYTE)ConvertHex(pId,2);
		pId += 2;
	}
	pId++;
	for(i=2;i<8;i++){
		gMediaGuid.Data4[i] = (BYTE)ConvertHex(pId,2);
		pId += 2;
	}
	pId++;

    return NO_ERROR;
}

