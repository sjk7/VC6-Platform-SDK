/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2003 <company name>
//
//  Module Name:
//      Guids.h
//
//  Description:
//      File for definition of CLSIDs, GUIDs, and logging GUIDs.
//
//  Author:
//      <name> (<e-mail name>) Mmmm DD, 2003
//
//  Revision History:
//
//  Notes:
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#pragma warning( push )
#include <initguid.h>
#pragma warning( pop )

//////////////////////////////////////////////////////////////////////////////
//
// Registration GUIDs
//
//////////////////////////////////////////////////////////////////////////////

//
// The Resource Type's GUID
//
// {E83C5122-8C18-42FA-99E7-221B51E16505}
DEFINE_GUID( RESTYPE_ClipBookServer,
0xE83C5122, 0x8C18, 0x42FA, 0x99, 0xE7, 0x22, 0x1B, 0x51, 0xE1, 0x65, 0x05 );

//
// This is the Cluster Administrator Extension dll CLSID to register for the type.
// This has to match the UUID of the extension class in ExtObjID.idl.
//
// {9E747617-E5D1-42D7-A8C3-0FC1D418B76B}
DEFINE_GUID(CLSID_CoClipBookServerEx,
0x9E747617, 0xE5D1, 0x42D7, 0xA8, 0xC3, 0x0F, 0xC1, 0xD4, 0x18, 0xB7, 0x6B );

//////////////////////////////////////////////////////////////////////////////
//
// Reporting GUIDs
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// CMgdClusCfgInit
//////////////////////////////////////////////////////////////////////////////

// {308A300C-2A40-4818-B5D2-7B65E39FB4FA}
DEFINE_GUID( TASKID_Minor_ClipBookServer_Initialize,
0x308A300C, 0x2A40, 0x4818, 0xB5, 0xD2, 0x7B, 0x65, 0xE3, 0x9F, 0xB4, 0xFA );

//////////////////////////////////////////////////////////////////////////////
// CMgdResType
//////////////////////////////////////////////////////////////////////////////

// {E4F7A345-EF7C-45F1-95FE-D6BF9C034FEE}
DEFINE_GUID( TASKID_Minor_ClipBookServer_ResType_CommitChanges,
0xE4F7A345, 0xEF7C, 0x45F1, 0x95, 0xFE, 0xD6, 0xBF, 0x9C, 0x03, 0x4F, 0xEE );
