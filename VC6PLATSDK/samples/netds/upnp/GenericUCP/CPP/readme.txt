--------------------------------------------------------------------------

  Copyright (C) Microsoft Corporation. All rights reserved.

--------------------------------------------------------------------------

UPnP
GenericUCP Sample Application in C++


Overview:

GenericUCP is a C++ sample UPnP application that discovers and controls 
UPnP devices found on the network.This sample was developed using Visual C++.

The sample application uses the UPnP Control Point API provided by upnp.dll. More
description about the application can be found in the documentation. 

The application first starts by discovering devices on the network through one of 
the three types of searches available, FindByType, FindByUDN and AsyncFind. 

The devices found are instantiated in the device list. One of the devices can be 
selected and the service objects for the selected device are listed in the service
list. One of the services can be selected and controlled by invoking actions against
it. The events relevant to the service are displayed in the events field. 


How to use:

To run the GenericUCP sample application, simply build and run GenericUCP.exe using 
the Platform SDK environment. The application needs UPnP to be installed in the operating system. 
This application runs only in WinMe and WinXP operating system. 

Limitations:

The following files need to be present in the same directory as the application.
1. cbklib.tlb 2. devType.txt 3. udn.txt. 
The ViewSDD and presentation functionality are not implemented in C++ version.

What functionality this sample does show:

The sample uses most of the UPnP control point APIs. The comments give more detail on
usage of APIs.

What this sample does not show:

This sample does not use some of the APIs like IUPnPDescriptionDocument interface APIs, 
IUPnPDeviceDocumentAccess interface APIs, etc. 


Notes for building the sample application:

 How to build the samples with VC6 or VC5:
-	IMPORTANT: start a new command prompt (cmd.exe), 
	or start a new "Set Win32 Environment" cmd window 
	from Programs - Microsoft Platform SDK .
-	go to the path where you installed VC6 
	(e.g. C:\ Program Files\Microsoft Visual Studio\VC98\Bin) 
	and type VCVARS32.BAT.
-	go to the path where you installed SDK 
	(e.g. C:\Program Files\Microsoft Platform SDK) 
	and type SetEnv.Bat.
-	check the following environment variables: 
	PATH, LIB, INCLUDE. You can see their current 
	values by typing "SET" at the command prompt. 
	You should see that they contain first the SDK 
	paths and then the VC6 paths.
-	go to the path where the UPNP sample 
	(GenericUCP) is installed and type NMAKE. 