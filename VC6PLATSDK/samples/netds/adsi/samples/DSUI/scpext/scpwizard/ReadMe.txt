
File: README.TXT

SCPWizard.DLL


This project contains samples showing how to implement a DS Admin 
primary creation wizard extension.  This wizard creates a service
connection point object.

FILES:
======

ReadMe.txt	ReadMe file for SCPWizard.DLL
SCPWizard.dsw	Visual C++ workspace file
SCPWizard.dsp	Visual C++ project file
SCPWizard.def	Exported symbols for SCPWizard.DLL
StdAfx.h	Pre-compiled header
StdAfx.cpp	Pre-compiled header
SCPWizard.rc	Resource file
resource.h	Resource header file
SCPWiz.h	Source header file
SCPWiz.cpp	Source C++ file
SCPPageUI.h	Source header file
SCPPageUI.cpp	Source C++ file
util.h		Source header file
util.cpp	Source C++ file



INSTALLATION NOTES for Windows 2000 (Windows 9x not supported):
===============================================================	

To install the extensions, you need to do the following:

1) Build the project to create SCPWizard.DLL (Notice: The unicode MFC libraries are required for this.)
2) Register the DLL by using regsvr32.
3) Modify the display specifiers.  If a display specifier named serviceConnectionPoint-Display
   does not already exist one will need to be created.  Please refer to 
   the Active Directory Programmers guide for more information.

   Inside the <codepage> container, look for the object's display 
   specifier (e.g. "serviceConnectionPoint-Display"). Edit the 
   "creationWizard" single-valued property by setting one 
   (string) value "{C03793D3-A7C8-11d1-B942-00A0C9A06D2D}". This
   value is the GUID of the creation wizard installed.

4) Modify the schema object.  This requires SchemaAdmin privileges and the schema must be set to
   allow updates.  To do this use Active Directory Schema Manager to select 'Operations Master' 
   menu and check 'Schema may be modified on this Domain Controller' checkbox.
   Then the defaultHidingValue of the serviceConnectionPoint schemaClass object must be set to 
   FALSE using ADSI Edit or programmatic means.

RUNNING THE APPLICATION on Windows 2000:
========================================

1) Launch Active Directory Users and Computers snapin
2) In the view menu select Advanced Features and Users, Groups, and Computers as containers.
3) Right click on a computer object.
4) Select New and then Service Connection Point from the context menu.
5) A service connection point wizard will be shown that will create the service connection point object.

