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

// {0cadd2fc-5463-47bc-9187-b40ae2dc14f7}
DEFINE_GUID( CLSID_CComponentData, 
             0x0cadd2fc, 0x5463, 0x47bc, 0x91, 0x87, 0xb4, 0x0a, 0xe2, 0xdc, 0x14, 0xf7);

// {e72383ab-ae80-43c5-8f83-f85864a4f6ea}
DEFINE_GUID( CLSID_CSnapinAbout, 
             0xe72383ab, 0xae80, 0x43c5, 0x8f, 0x83, 0xf8, 0x58, 0x64, 0xa4, 0xf6, 0xea);

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