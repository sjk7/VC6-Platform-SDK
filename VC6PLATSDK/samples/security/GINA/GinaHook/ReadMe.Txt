Abstract
========

This sample illustrates a pass-thru "stub" GINA with hook to some MSGINA
dialog boxes which can be used in some cases to simplify GINA development.

In this sample, the WlxLoggedOutSAS() and WlxWkstaLockedSAS() dialog boxes
are hooked so that UI can be manipulated as such only logon to local machine
is allowed.

Please see the GINASTUB sample for more detail on pass-thru GINA.

Files included in this sample
=============================

1) ReadMe.txt   - This file
2) GinaHook.c   - C source file
2) GinaDlg.c    - C source file
3) GinaHook.h   - C header file
3) GinaDlg.h    - C header file
4) GinaHook.def - Definition file
5) MAKEFILE     - Makefile for NMAKE utility

Winlogon Versions supported
===========================

This sample can support WINLOGON versions from 1.0 up to 1.3.

Version 1.0 = NT 3.5x
Version 1.1 = NT 4.0, SP1, SP2, and SP3
Version 1.2 = NT 4.0 SP4 and SP5
Version 1.3 = Windows 2000

How to compile
==============

1) Make sure MSSDK and your C compiler environment are properly setup.
2) From the GinaHook directory, run NMAKE to make GinaHook.dll.

How to install GINAHOOK
=======================

1) Copy GinaHook.dll to %SystemRoot%\System32 directory.
2) Run RegEdit
3) Create the following value under
   HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\Winlogon.
   Value Name: GinaDLL
   Value Type: REG_SZ
   Value Data: "GinaHook.dll"
4) Exit RegEdit.
5) Reboot.

Remarks
=======

Make sure to create an Emergency Repair Disk before deploying GINAHOOK.DLL,
since any mishap may cause your system unuseable. It is recommended that you
test your GINA under a FAT system. This way you can always boot to DOS, copy
over MSGINA.DLL to GINAHOOK.DLL, and reboot to restore your system.
