
File: README.TXT

UserWizard.DLL


This project contains samples showing how to implement a DS Admin 
secondary wizard extension.  This extension adds a page to set
a thumbnail photo and employee ID for a user.

FILES:
======

ReadMe.txt	ReadMe file for UserWizard.DLL
userwizard.dsw	Visual C++ workspace file
userwizard.dsp	Visual C++ project file
userwizard.def	Exported symbols for UserWizard.DLL
StdAfx.h	Pre-compiled header
StdAfx.cpp	Pre-compiled header
userwizard.rc	Resource file
resource.h	Resource header file
wizext.h	Source header file
wizext.cpp	Source C++ file
extpageuser.h	Source header file
extpageuser.cpp	Source C++ file
util.h		Source header file
util.cpp	Source C++ file



INSTALLATION NOTES for Windows 2000 (Windows 9x not supported):
===============================================================	

To install the extensions, you need to do the following:

1) Build the project to create UserWizard.DLL (Notice: The unicode MFC libraries are required for this.)
2) Register the DLL by using regsvr32.
3) Modify the display specifiers. If a display specifier named user-Display
   does not already exist one will need to be created.  Please refer to 
   the Active Directory Programmers guide for more information.

   Inside the <codepage> container, look for the object's display specifier
   (e.g. "user-Display"). Edit the "createWizardExt" multivalued property by 
   adding one (string) value "<number>,{C03793D3-A7C8-11d1-B940-00A0C9A06D2D}". 
   This value is the GUID of the secondary wizard extension installed.



RUNNING THE APPLICATION on Windows 2000:
========================================

1) Launch Active Directory Users and Computers snapin
2) Right click on a container or organizational unit.
3) Select New and then User from the context menu.
4) Proceed through the wizard as usual.  There will be an additional page
   for adding a thumbnail photo and employee ID for the user.
