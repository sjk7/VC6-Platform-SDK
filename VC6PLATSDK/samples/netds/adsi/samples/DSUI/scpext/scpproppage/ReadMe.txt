
File: README.TXT

SCPProppage.DLL


This project contains samples showing how to implement a DS Admin 
primary property page extension.  This property page displays
information for service connection point objects.

FILES:
======

ReadMe.txt	ReadMe file for SCPProppage.DLL
SCPProppage.dsw	Visual C++ workspace file
SCPProppage.dsp	Visual C++ project file
SCPProppage.def	Exported symbols for SCPProppage.DLL
StdAfx.h	Pre-compiled header
StdAfx.cpp	Pre-compiled header
SCPProppage.rc	Resource file
resource.h	Resource header file
SCP.h		Source header file
SCP.cpp		Source C++ file
SCPUI.h		Source header file
SCPUI.cpp	Source C++ file
util.h		Source header file
util.cpp	Source C++ file



INSTALLATION NOTES for Windows 2000 (Windows 9x not supported):
===============================================================

To install the extensions, you need to do the following:

1) Build the project to create SCPProppage.DLL (Notice: The unicode MFC libraries are required for this.)
2) Register the DLL by using regsvr32.
3) Modify the display specifiers. If a display specifier named serviceConnectionPoint-Display
   does not already exist one will need to be created.  Please refer to 
   the Active Directory Programmers guide for more information.

   Inside the <codepage> container, look for the object's display specifier
   (e.g. "serviceConnectionPoint-Display"). Edit the "adminPropertyPages" 
   multivalued property by adding one (string) value 
   "<number>,{69D967C6-AB39-47b7-9F00-410185C80F89}". This
   value is the GUID of the property page extension installed.

4) Modify the schema object.  This requires SchemaAdmin privileges and the schema must be set to
   allow updates.  To do this use Active Directory Schema Manager to select 'Operations Master' 
   menu and check 'Schema may be modified on this Domain Controller' checkbox.
   Then the defaultHidingValue of the serviceConnectionPoint schemaClass object must be set to 
   FALSE using ADSI Edit or programmatic means.
	



RUNNING THE APPLICATION on Windows 2000:
========================================

1) Launch Active Directory Users and Computers snapin and create a service connection point
2) Right click on the new service connection point.
3) Select properties from the context menu.
4) Property pages for the service connection point object will be displayed.

