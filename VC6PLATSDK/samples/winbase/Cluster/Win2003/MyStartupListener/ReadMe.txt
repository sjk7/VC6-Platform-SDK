MyStartupListener - Register for Cluster Startup Notifications


SUMMARY
=======

This sample demonstrates how you can build a program that automatically gets
called whenever the Microsoft Cluster Service (MSCS) starts on a machine.

This is done by registering a COM class that implements the category
CATID_ClusCfgStartupListeners.

REQUIREMENTS
============

This sample will only work on Windows Server 2003 and later.


MORE INFORMATION
================

How to build this sample
------------------------

Use one of the following:

1. Use nmake.exe from the command line to build MyStartupListener.dll.
2. Use Visual C++ 6.0 or Visual C++ .NET to open the MyStartupListener.dsw 
workspace and build MyStartupListener.dll.


Usage
-----

When you build this sample, you will generate a DLL file that
you must register using 

RegSvr32.exe MyStartupListener.dll

After this DLL is registered, on every start of the cluster service on a 
node, a message will be logged to the cluster configuration log file 
(%windir%\system32\LogFiles\Cluster\ClCfgSrv.log).

Unregistering with

RegSvr32.exe /u MyStartupListener.dll

stops Cluster Server from calling this dll when the service starts.


