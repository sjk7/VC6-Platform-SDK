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


#ifndef _VIEWEXTENSION_PROJECT_GUIDS_
#define _VIEWEXTENSION_PROJECT_GUIDS_

// {3bbefb8e-8122-4b0a-b54e-05dd4d6aa02c}
DEFINE_GUID( CLSID_CComponentData, 
             0x3bbefb8e, 0x8122, 0x4b0a, 0xb5, 0x4e, 0x05, 0xdd, 0x4d, 0x6a, 0xa0, 0x2c);


// {96dd4604-48f2-402d-8255-f7423dec1990}
DEFINE_GUID( CLSID_CSnapinAbout, 
             0x96dd4604, 0x48f2, 0x402d, 0x82, 0x55, 0xf7, 0x42, 0x3d, 0xec, 0x19, 0x90);


// {520F23F9-775D-4015-B437-98A24B9D085E}
DEFINE_GUID( CLSID_DeviceNode, 
             0x520F23f9, 0x775D, 0x4015, 0xB4, 0x37, 0x98, 0xA2, 0x4B, 0x9D, 0x8, 0x5E);


// {520F23FA-775D-4015-B437-98A24B9D085E}
DEFINE_GUID( CLSID_CFolderNode, 
             0x520F23fA, 0x775D, 0x4015, 0xb4, 0x37, 0x98, 0xA2, 0x4B, 0x9D, 0x8, 0x5E);

// {f0091c49-c869-4941-a81c-c719ad8174cc}
DEFINE_GUID( CLSID_CVirtualFile,
             0xf0091c49, 0xc869, 0x4941, 0xa8, 0x1c, 0xc7, 0x19, 0xad, 0x81, 0x74, 0xcc);


#endif //_VIEWEXTENSION_PROJECT_GUIDS_