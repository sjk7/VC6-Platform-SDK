THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999  Microsoft Corporation.  All rights reserved.

Cleanup Sample

The Cleanup sample implements a Disk Cleanup Handler shell extension. The 
sample implements the IEmptyVolumeCache interface, which is used by the 
Disk Cleanup Manager (CLEANMGR.EXE) on Windows 98 and Windows 2000.

The sample can be registered by using the REGSVR32.EXE utility:

    REGSVR32.EXE <DLL PATH>\CLEANUP.DLL

or unregistered:

    REGSVR32.EXE /U <DLL PATH>\CLEANUP.DLL

Once the extension is registered, it can be accessed by starting
CLEANMGR.EXE or by clicking the "Disk Cleanup" button on a drive's
Properties dialog in Explorer. The Properties dialog can be accessed
by right-clicking on a drive in Explorer and selecting "Properties"
from the context menu or by clicking on a drive in Explorer and
selecting File | Properties.