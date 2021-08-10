===============================================
 Shell Common Controls - CustomDrawButtonDlg
================================================
Last Updated: OCT. 18,  2001              

DESCRIPTION
============
CustomDrawButtonDlg is a sample application that displays the drawing stages that are associated 
with a button's control states. When you run CustomDrawButtonDlg and move the cursor so that the control's 
state changes, for example from hot to disabled, the application shows the states and drawing stages.

The ReadMe.txt file contained in the down loaded files is a summary of the files that make up the 
CustomDrawButtonDlg application.

CustomDrawButtonDlg.cpp - This is the main application source file.

CustomDrawButtonDlg.dsp - This file (the project file) contains information at the project level and builds a single project or subproject. Other users can share the project (.dsp) file, but they should export the make files locally.


BROWSER/PLATFORM COMPATIBILITY
===============================
CustomDrawButtonDlg.exe is a browser-independent executable file.
CustomDrawButtonDlg.exe operates with Microsoft® Windows® XP. This sample application will not 
run on any operating system except Windows XP because it requires ComCtl32.dll version 6. 
CustomDrawButtonDlg in turn requires a manifest to ensure that ComCtl32.dll version 6 is available.
This sample application includes a manifest named CustomDrawButtonDlg.exe.manifest. ComCtl32.dll 
version 6 is not redistributable therefore you must have Windows XP installed which contains this particular dynamic link library. 

The header and library files that are required are:

Commctrl.h
WinUser.h (newer version than the one I had in Visual Studio 6)
Tvout.h
Comctl32.lib

All the above header and library files are available in the Platform SDK.


USAGE
=====
To build the sample, use Microsoft® Visual C++® 6 with the latest header 
and library files from Platform SDK. To run CustomDrawButtonDlg.exe, the manifest file, 
CustomDrawButtonDlg.exe.manifest must reside in the same directory. 

CustomDrawButtonDlg.exe is a Unicode application. 


SOURCE FILES
=============
CustomDrawButtonDlg.exe
CustomDrawButtonDlg.cpp
CustomDrawButtonDlg.dsp
StdAfx.cpp


OTHER FILES
============
StdAfx.h
Readme.txt

========================
© Microsoft Corporation

  





