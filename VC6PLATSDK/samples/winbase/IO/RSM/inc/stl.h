/*
 *  This is a part of the Microsoft Source Code Samples.
 
 *
 *	This sample code shows the usage of some portions
 *	of the RSM API.
 *	
 *	Return codes are, for the most part, not checked in
 *	this code. See the Programmer's reference for error
 *	return information.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Copyright 1997 - 1998 Microsoft Corporation.  All Rights Reserved. 
 */

/*
 *  Definition of the "Simple Tape Label"
 *
 */
#ifndef _STL_DEFS_H
#define _STL_DEFS_H


// make sure we are byte aligned ... 
#pragma pack(1) 

#define STL_LABEL_LabelType L"Simple Tape Label (STL)"
#define STL_LABEL_LabelTypeSize sizeof (STL_LABEL_LabelType)

#define STL_LABEL_Version L"2.60"
#define STL_LABEL_VersionSize sizeof(STL_LABEL_Version)

#define STL_LABEL_Vendor L"Microsoft Corporation"
#define STL_LABEL_VendorSize sizeof(STL_LABEL_Vendor)

#define STL_LABEL_TimeStampSize 40 // Must be even to hold UNICODE string

#define STL_LABEL_Application L"RSM Sample App"
#define STL_LABEL_ApplicationSize sizeof(STL_LABEL_Application)

#define STL_LABEL_TapeNameSize 256 // Must be even to hold UNICODE string

#define STL_LABEL_MediaIDBlank L"{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}"
#define STL_LABEL_MediaIDSize sizeof(STL_LABEL_MediaIDBlank)

typedef struct
{
	BYTE	LabelType[STL_LABEL_LabelTypeSize];
	BYTE	LabelVersion[STL_LABEL_VersionSize];
	BYTE	Vendor[STL_LABEL_VendorSize];
	BYTE	TimeStamp[STL_LABEL_TimeStampSize];
	BYTE	Application[STL_LABEL_ApplicationSize];
	BYTE	TapeName[STL_LABEL_TapeNameSize];
	BYTE	MediaID[STL_LABEL_MediaIDSize];
} STL_LABEL;

#endif