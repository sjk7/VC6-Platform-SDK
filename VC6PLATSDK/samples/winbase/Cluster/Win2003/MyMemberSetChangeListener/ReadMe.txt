MyMemberSetChangeListener - Register for Cluster Member Set Change Notifications


SUMMARY
=======

This sample demonstrates how you can build a program that automatically gets
called whenever a member set change occurs in an MSCS cluster.

This is done by registering a COM class that implements the category
CATID_ClusCfgMemberSetChangeListeners.

REQUIREMENTS
============

This sample will only work on Windows Server 2003 and later.


MORE INFORMATION
================

How to build this sample
------------------------

Use one of the following:

1. Use nmake.exe from the command line to build MyMemberSetChangeListener.dll.
2. Use Visual C++ 6.0 or Visual C++ .NET to open the MyMemberSetChangeListener.dsw 
workspace and build MyMemberSetChangeListener.dll.


Usage
-----

When you build this sample, you will generate a DLL file that
you can register using 

RegSvr32.exe MyMemberSetChangeListener.dll

After this DLL is registered, whenever a node is added to or removed from the 
cluster, a message will be logged to the cluster configuration log file (%windir%\
system32\LogFiles\Cluster\ClCfgSrv.log). The same message will also be
displayed in UI in the reanalysis page of the Cluster Configuration Wizard.

Unregistering with

RegSvr32.exe /u MyMemberSetChangeListener.dll

stops Cluster Server from calling this dll on member set change.



