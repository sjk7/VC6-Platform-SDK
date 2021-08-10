------------------------------------------------------------------
           Windows NetMeeting 3 SDK Readme File
                         May 2002
------------------------------------------------------------------

             (c) Copyright Microsoft Corporation, 2002


HOW TO USE THIS DOCUMENT
========================

To view Readme.txt on screen in Windows Notepad, maximize the Notepad window, and turn on Word Wrap under the Edit menu.

To print Readme.txt, open the file in Notepad or another word processor, and then on the File menu, click Print.


CONTENTS
========

ABOUT THIS RELEASE OF THE NETMEETING SDK
INSTALLING AND USING THE NETMEETING SDK
OVERVIEW OF THE NETMEETING SDK SAMPLES
KNOWN ISSUES


ABOUT THIS RELEASE OF THE NETMEETING SDK
========================================
This release includes documentation and sample code for the following:

· A new NetMeeting UI ActiveX control that enables developers to embed the NetMeeting user interface in a web page or application and a simple scripting interface that provides access to NetMeeting functionality

· A set of objects based on the OLE Component Object Model (COM) that enable developers to access the functionality of the Windows NetMeeting platform from within COM applications.

· A set of COM objects that allow developers to access the functionality of LDAP directories, including the one used by Windows NetMeeting.   Use these objects to add directory capabilities to your NetMeeting application.

· A set of COM objects that allow developers to install and uninstall audio and video codecs.  Use these objects in a setup program for your codec so that NetMeeting users can install your codecs. 



INSTALLING AND USING THE NETMEETING SDK
=======================================
To install, or re-install, the NetMeeting SDK, execute the NM3SDK.EXE self-extracting installation program.   This .EXE was created for Windows NT 4.0, Windows 2000 Windows 98 and Windows 95.  It  will copy the SDK to a directory you specify and place shortcuts to the NetMeeting SDK documentation, readme, and folder, in the Start, Programs menu on your task bar.

The NetMeeting 3 SDK documentation requires the use of Internet Explorer 4.01 or greater.

It is strongly recommended that you uninstall previous versions of the NetMeeting SDK before installing the NetMeeting 3 SDK.

Note that if you install on NT 4.0 and you do not have administrator privilege, no items will be installed on the Start, Programs Menu for the NetMeeting 3 SDK.

To use this SDK you will need NetMeeting 3.
This version of the NetMeeting is available at http://www.microsoft.com/netmeeting.

OVERVIEW OF THE NETMEETING SDK DOCUMENTATION
============================================

This release contains documentation for newly added interfaces.  The NetMeeting 2.1 references, included with this release should be used as a reference for interfaces that existed in NetMeeting 2.1. 


OVERVIEW OF THE NETMEETING SDK SAMPLES
======================================

The Samples directory contains the following sample code:

· One Visual C++ application, NMUI, that uses the INm* COM objects to leverage enhanced NetMeeting 3 platform capabilities.

· One Visual C++ application, INSTCODC, that uses codec installation COM objects to demonstrate the installation, deinstallation, and reordering of codec priorities.

· A Visual C++ application, AVPHONE, that demonstrates the manipulation of   the audio & video API in Windows NetMeeting and using the NetMeeting UI ActiveX Control to embed video in an application.

· Several Visual C++ applications that demonstrate how to allow users to communicate using NetMeeting COM interfaces (each sample in this list has NetMeeting running on each system):  
     NMCHAT demonstrates how to allow a user to communicate through a chat window to another user.
     NMCHAT2 similarly demonstrates chat using the NetMeeting 3 T.120 COM applet interfaces.
     NMSHARE demonstrates an application that allows a user to share application windows with another user.
     PLUGTRANSPORT demonstrates how to use the NetMeeting 3 transport replacement COM interfaces.

·  A Visual C++ Windows application, NMFT,  that allows the user to 
send files via an existing NetMeeting connection.  NMFT can be added
to the system pop-up menu by placing the executable in the Windows
SendTo directory.
 

· Several HTML Web pages with VBScript that use the NetMeeting UI ActiveX Control to embed the NetMeeting UI ActiveX Control. These Web pages are in the TEAMPAGE and VIEWMODES directories.

NOTE: Earlier releases of the NetMeeting 3 SDK included SKIPPY!, a Visual C++ application that allowed a user to query an ILS server for users and user information. Because such functionality has become obsolete, the SKIPPY! sample code has been removed from the NetMeeting 3 SDK.

For more information on the samples, see the Samples.txt file in the root directory of the SDK. This file contains information on all of the samples in the SDK. In addition, some of the samples have specific readme files located in their respective directories.


KNOWN ISSUES
==============
Use *.mak files with NMAKE to build samples from DOS prompt (Example: Nmake nmui.mak), but before doing this one must set the VC environment using VCVARS32.BAT which is installed along with VC.

