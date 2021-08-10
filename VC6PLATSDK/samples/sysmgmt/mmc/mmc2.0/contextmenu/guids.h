/////////////////////////////////////////////////////////////////////////////
//
//  This source code is only intended as a supplement to existing
//  Microsoft documentation. 
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1999 - 2001 Microsoft Corporation.  All Rights Reserved.
//
//  Note that the GUIDs for CComponentData and CSnapinAbout are different 
//  from the ScopeNode project.  The Node GUIDs can stay the same since
//  they are not really COM objects.


#ifndef _CONTEXTMENU_PROJECT_GUIDS_
#define _CONTEXTMENU_PROJECT_GUIDS_

// {6812e2cf-47dd-4294-a155-5ff2bec2fea2}
DEFINE_GUID( CLSID_CComponentData, 
             0x6812e2cf, 0x47dd, 0x4294, 0xa1, 0x55, 0x5f, 0xf2, 0xbe, 0xc2, 0xfe, 0xa2);

// {9eee41e0-e990-4160-8fde-271514eb2240}
DEFINE_GUID( CLSID_CSnapinAbout, 
             0x9eee41e0, 0xe990, 0x4160, 0x8f, 0xde, 0x27, 0x15, 0x14, 0xeb, 0x22, 0x40);

// {520F23F9-775D-4015-B437-98A24B9D085E}
DEFINE_GUID( CLSID_DeviceNode, 
             0x520F23f9, 0x775D, 0x4015, 0xB4, 0x37, 0x98, 0xA2, 0x4B, 0x9D, 0x8, 0x5E);

// {520F23FA-775D-4015-B437-98A24B9D085E}
DEFINE_GUID( CLSID_CFolderNode, 
             0x520F23fA, 0x775D, 0x4015, 0xb4, 0x37, 0x98, 0xA2, 0x4B, 0x9D, 0x8, 0x5E);




#endif //_CONTEXTMENU_PROJECT_GUIDS_