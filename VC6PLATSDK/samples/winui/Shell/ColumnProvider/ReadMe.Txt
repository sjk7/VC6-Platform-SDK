THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999  Microsoft Corporation.  All rights reserved.

ShortName Sample

The ShortName sample implements a Column Provider shell extension
for Windows 2000. The shell extension is available in the Windows
Explorer when browsing into file system folders and can be 
displayed by right-clicking on the column header and selecting a
column to display.

The sample provides two columns: the short filename for files and the
short pathname for files and folders.

The sample can be registered by using the REGSVR32.EXE utility:

    REGSVR32.EXE <DLL PATH>\SHORTNAME.DLL

or unregistered:

    REGSVR32.EXE /U <DLL PATH>\SHORTNAME.DLL

Once the Column Provider is registered, the "Short Name" and "Short
Path" colums can be added by right-clicking on the header of any
Explorer view in Details mode and selecting "More..." from the 
context menu. 

NOTE: The new columns may not immediately appear in the
list of available columns. Perform the following steps to until the
new columns appear in the list:

    1. Change the current folder to another folder, then back to the
       initial folder.
    2. Close the current instance of the Explorer window and start a
       new instance.
    3. Restart the shell.
    4. Reboot.

In most cases, only the first step is needed to have the shell
reinitialize the list of available columns. 