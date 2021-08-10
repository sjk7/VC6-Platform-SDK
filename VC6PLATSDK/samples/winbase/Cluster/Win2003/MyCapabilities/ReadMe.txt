MyCapabilities - Register for Cluster Feasibility Test


SUMMARY
=======

This sample demonstrates how you can build a program that automatically gets
called by the Cluster Configuration Wizard to decide whether or not a computer 
can be made a member of an MSCS Cluster.

This is done by registering a COM class that implements the category
CATID_ClusCfgCapabilities.


REQUIREMENTS
============

This sample will only work on Windows Server 2003 and later.


MORE INFORMATION
================

Special considerations before building
--------------------------------------

This sample can either generate a warning or it can actually prevent 
the computer from becoming a member of a Cluster.

By default, ALLOW_FAIL is not defined in MyCapabilities.cpp. This will only
generate a warning to the user if the function HrGetApplicationCompatibilityInfo()
declares this computer not to be cluster-safe.

If you uncomment the ALLOW_FAIL definition, then the CMyCapabilities class
will prevent this computer from becoming a cluster node.

Also, by default, HrGetApplicationCompatibilityInfo() always sets the output 
parameter to FALSE, indicating that this application is not compatible with 
clustering.

So as is, this sample will only generate a warning in the UI on the analysis 
page of the Cluster Configuration Wizard. In either case a message 
will be logged to the cluster configuration log file (%windir%\system32\
LogFiles\Cluster\ClCfgSrv.log).


How to build this sample
------------------------

Use one of the following:

1. Use nmake.exe from the command line to build MyCapabilities.dll.
2. Use Visual C++ 6.0 or Visual C++ .NET to open the MyCapabilities.dsw 
workspace and build MyCapabilities.dll.


Usage
-----

When you build this sample, you will generate a DLL file that
you must register using 

RegSvr32.exe MyCapabilities.dll

After this DLL is registered, every time the Cluster Configuration Wizard
attempts to make this computer a Cluster node, you will receive either a
warning (if ALLOW_FAIL is not defined) or an error (if ALLOW_FAIL is defined).
In the latter case, this node will be prevented from being clustered.

Unregistering with

RegSvr32.exe /u MyCapabilities.dll

stops the Cluster Configuration Wizard from calling this dll.

