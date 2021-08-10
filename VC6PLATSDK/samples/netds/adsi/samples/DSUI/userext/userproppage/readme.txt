
File: README.TXT

UserProppage.DLL


This project contains samples showing how to implement a DS Admin 
property page extension.  This property page displays
a thumbnail photo and employee ID for a user object.

FILES:
======

ReadMe.txt		ReadMe file for UserProppage.DLL
userproppage.dsw	Visual C++ workspace file
userproppage.dsp	Visual C++ project file
userproppage.def	Exported symbols for UserProppage.DLL
StdAfx.h		Pre-compiled header
StdAfx.cpp		Pre-compiled header
userproppage.rc		Resource file
resource.h		Resource header file
proppageuser.h		Source header file
proppageuser.cpp	Source C++ file
proppageuserui.h	Source header file
proppageuserui.cpp	Source C++ file
util.h			Source header file
util.cpp		Source C++ file



INSTALLATION NOTES for Windows 2000 (Windows 9x not supported):
===============================================================	

To install the extensions, you need to do the following:

1) Build the project to create UserProppage.DLL (Notice: The unicode MFC libraries are required for this.)
2) Register the DLL by using regsvr32.
3) Modify the display specifiers. If a display specifier named user-Display
   does not already exist one will need to be created.  Please refer to 
   the Active Directory Programmers Guide for more information.

   Inside the <codepage> container, look for the object's display specifier
   (e.g. "user-Display"). Edit the "adminPropertyPages" multivalued property 
   by adding one (string) value "<number>,{69D967C6-AB39-47b7-8F00-410185C80F89}". 
   This value is the GUID of the property page extension installed.



RUNNING THE APPLICATION on Windows 2000:
========================================

1) Launch Active Directory Users and Computers snapin and select a user object
2) Right click on the user object and select properties.
3) All the original property pages will be shown and an additional page that
   displays the user's thumbnail photo and employee ID will also be shown.
