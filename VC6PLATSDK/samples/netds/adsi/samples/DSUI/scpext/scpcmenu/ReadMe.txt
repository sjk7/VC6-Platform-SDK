
File: README.TXT

SCPCMenu.DLL


This project contains samples showing how to implement a DS Admin 
context menu handler shell extension.  This context menu handler 
displays the clipboard format information in a dialog box.

FILES:
======

ReadMe.txt	ReadMe file for SCPCMenu.DLL
SCPCMenu.dsw	Visual C++ workspace file
SCPCMenu.dsp	Visual C++ project file
SCPCMenu.def	Exported symbols for SCPCMenu.DLL
StdAfx.h	Pre-compiled header
StdAfx.cpp	Pre-compiled header
SCPCMenu.rc	Resource file
resource.h	Resource header file
SCPCMenu.h	Source header file
SCPCMenu.cpp	Source C++ file
dsmenu.h	Source header file
dsmenu.cpp	Source C++ file
scpcmenuui.h	Source header file
scpcmenuui.cpp	Source C++ file



INSTALLATION NOTES for Windows 2000 (Windows 9x not supported):
===============================================================	

To install the extensions, you need to do the following:

1) Build the project to create SCPCMenu.DLL (Notice: The unicode MFC libraries are required for this.)
2) Register the DLL by using regsvr32.
3) Modify the display specifiers. If a display specifier named serviceConnectionPoint-Display
   does not already exist one will need to be created.  Please refer to 
   the Active Directory Programmers guide for more information.

   Inside the <codepage> container, look for the object's display specifier
   (e.g. "serviceConnectionPoint-Display").  Edit the "adminContextMenu" 
   multivalued property by adding one (string) value 
   "<number>,{2CE182CC-DD9D-11d2-AB28-01C04F68FA4A}". This
   value is the GUID of the context menu handlers installed.

4) Modify the schema object.  This requires SchemaAdmin privileges and the schema must be set to
   allow updates.  To do this use Active Directory Schema Manager to select 'Operations Master' 
   menu and check 'Schema may be modified on this Domain Controller' checkbox.
   Then the defaultHidingValue of the serviceConnectionPoint schemaClass object must be set to 
   FALSE using ADSI Edit or programmatic means.



RUNNING THE APPLICATION on Windows 2000:
========================================

1) Launch Active Directory Users and Computers snapin and create a service connection point
2) Right click on the new service connection point.
3) A menu item, "Show Clipboard Information", will be displayed in the context menu.
4) Select this menu item.
5) A dialog box will appear with information extracted from the clipboard format.

     

