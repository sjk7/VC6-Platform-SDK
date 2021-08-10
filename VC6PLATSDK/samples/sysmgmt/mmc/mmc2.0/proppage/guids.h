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


#ifndef _PROPPAGE_PROJECT_GUIDS_
#define _PROPPAGE_PROJECT_GUIDS_

// {f321bdf7-b850-427d-8062-5df89c1bb688}
DEFINE_GUID( CLSID_CComponentData, 
             0xf321bdf7, 0xb850, 0x427d, 0x80, 0x62, 0x5d, 0xf8, 0x9c, 0x1b, 0xb6, 0x88);

// {64de9ae8-f74b-48c5-9874-0308c1add5d7}
DEFINE_GUID( CLSID_CSnapinAbout, 
             0x64de9ae8, 0xf74b, 0x48c5, 0x98, 0x74, 0x03, 0x08, 0xc1, 0xad, 0xd5, 0xd7);

// {520F23F9-775D-4015-B437-98A24B9D085E}
DEFINE_GUID( CLSID_DeviceNode, 
             0x520F23f9, 0x775D, 0x4015, 0xB4, 0x37, 0x98, 0xA2, 0x4B, 0x9D, 0x8, 0x5E);

// {520F23FA-775D-4015-B437-98A24B9D085E}
DEFINE_GUID( CLSID_CFolderNode, 
             0x520F23fA, 0x775D, 0x4015, 0xb4, 0x37, 0x98, 0xA2, 0x4B, 0x9D, 0x8, 0x5E);

// {f0091c49-c869-4941-a81c-c719ad8174cc}
DEFINE_GUID( CLSID_CVirtualFile,
             0xf0091c49, 0xc869, 0x4941, 0xa8, 0x1c, 0xc7, 0x19, 0xad, 0x81, 0x74, 0xcc);



#endif //_PROPPAGE_PROJECT_GUIDS_