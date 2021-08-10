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


#ifndef _DRAGDROP_PROJECT_GUIDS_
#define _DRAGDROP_PROJECT_GUIDS_

// {c6f2200f-7e99-4313-8c30-69555ff913de}
DEFINE_GUID( CLSID_CComponentData, 
             0xc6f2200f, 0x7e99, 0x4313, 0x8c, 0x30, 0x69, 0x55, 0x5f, 0xf9, 0x13, 0xde);

// {8abe0b8c-bf73-4065-bbd0-afb8a617ac23}
DEFINE_GUID( CLSID_CSnapinAbout, 
             0x8abe0b8c, 0xbf73, 0x4065, 0xbb, 0xd0, 0xaf, 0xb8, 0xa6, 0x17, 0xac, 0x23);

// {520F23F9-775D-4015-B437-98A24B9D085E}
DEFINE_GUID( CLSID_DeviceNode, 
             0x520F23f9, 0x775D, 0x4015, 0xB4, 0x37, 0x98, 0xA2, 0x4B, 0x9D, 0x8, 0x5E);


// {520F23FA-775D-4015-B437-98A24B9D085E}
DEFINE_GUID( CLSID_CFolderNode, 
             0x520F23fA, 0x775D, 0x4015, 0xb4, 0x37, 0x98, 0xA2, 0x4B, 0x9D, 0x8, 0x5E);

// {f0091c49-c869-4941-a81c-c719ad8174cc}
DEFINE_GUID( CLSID_CVirtualFile,
             0xf0091c49, 0xc869, 0x4941, 0xa8, 0x1c, 0xc7, 0x19, 0xad, 0x81, 0x74, 0xcc);


#endif //_DRAGDROP_PROJECT_GUIDS_