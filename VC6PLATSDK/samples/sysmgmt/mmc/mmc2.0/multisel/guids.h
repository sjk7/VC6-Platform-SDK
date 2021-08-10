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


#ifndef _MULTISELECT_PROJECT_GUIDS_
#define _MULTISELECT_PROJECT_GUIDS_

// {17384dc8-ef90-4776-9307-70369f21e99b}
DEFINE_GUID( CLSID_CComponentData, 
             0x17384dc8, 0xef90, 0x4776, 0x93, 0x07, 0x70, 0x36, 0x9f, 0x21, 0xe9, 0x9b);

// {f54789ff-ad41-42d4-8f2e-a68089f625b1}
DEFINE_GUID( CLSID_CSnapinAbout, 
             0xf54789ff, 0xad41, 0x42d4, 0x8f, 0x2e, 0xa6, 0x80, 0x89, 0xf6, 0x25, 0xb1);

// {520F23F9-775D-4015-B437-98A24B9D085E}
DEFINE_GUID( CLSID_DeviceNode, 
             0x520F23f9, 0x775D, 0x4015, 0xB4, 0x37, 0x98, 0xA2, 0x4B, 0x9D, 0x8, 0x5E);

// {520F23FA-775D-4015-B437-98A24B9D085E}
DEFINE_GUID( CLSID_CFolderNode, 
             0x520F23fA, 0x775D, 0x4015, 0xb4, 0x37, 0x98, 0xA2, 0x4B, 0x9D, 0x8, 0x5E);

// {f0091c49-c869-4941-a81c-c719ad8174cc}
DEFINE_GUID( CLSID_CVirtualFile,
             0xf0091c49, 0xc869, 0x4941, 0xa8, 0x1c, 0xc7, 0x19, 0xad, 0x81, 0x74, 0xcc);


#endif //_MULTISELECT_PROJECT_GUIDS_
