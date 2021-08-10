MyEvictListener - Register for Cluster Evict Notifications


SUMMARY
=======

This sample demonstrates how you can build a program that automatically gets
called whenever a node gets evicted from an MSCS Cluster. 

This is done by registering a COM class that implements the category
CATID_ClusCfgEvictListeners.

REQUIREMENTS
============

This sample will only work on Windows Server 2003 and later.


MORE INFORMATION
================

How to build this sample
------------------------

Use one of the following:

1. Use nmake.exe from the command line to build MyEvictListener.dll.
2. Use Visual C++ 6.0 or Visual C++ .NET to open the MyEvictListener.dsw 
workspace and build MyEvictListener.dll.


Usage
-----

When you build this sample, you will generate a DLL file that
you must register using 

RegSvr32.exe MyEvictListener.dll

After this DLL is registered, whenever a node is evicted from the cluster,
a message will be logged to the cluster configuration log file (%windir%\
system32\LogFiles\Cluster\ClCfgSrv.log). Note that a cluster evict notification
is NOT sent if the last node of a cluster is being evicted.

Unregistering with

RegSvr32.exe /u MyEvictListener.dll

stops Cluster Server from calling this dll on eviction.

