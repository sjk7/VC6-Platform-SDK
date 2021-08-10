--------------------------------------------------------------------------

  Copyright (C) Microsoft Corporation. All rights reserved.

--------------------------------------------------------------------------

UPnP
GenericUCP Sample Application in Visual Basic


Overview:

GenericUCP is a Visual Basic sample UPnP application that discovers and controls 
UPnP devices found on the network.This sample was developed using Visual Basic 6.

The sample application uses the UPnP Control Point API provided by upnp.dll. More
description about the application can be found in the documentation. 

The application first starts by discovering devices on the network through one of 
the three types of searches available, FindByType, FindByUDN and AsyncFind. 

The devices found are instantiated in the device list. One of the devices can be 
selected and the service objects for the selected device are listed in the service
list. One of the services can be selected and controlled by invoking actions against
it. The events relevant to the service are displayed in the events field. 

Also the service description of the service can be viewed by entering the url in the
service description field and browsing through the xml tree of the service description
document. 


How to use:

To run the GenericUCP sample application, simply build and run GenericUCP.exe,
using Visual Basic 6. The application needs UPnP to be installed in the operating system. 
This application runs only in WinMe and WinXP operating system. For using the presentation 
functionality of the application, IE needs to be installed.

Limitations:

The following files need to be present in the same directory as the application.
1. cbklib.tlb 2. devType.txt 3. udn.txt. 


What functionality this sample does show:

The sample uses most of the UPnP control point APIs. The comments give more detail on
usage of APIs.

What this sample does not show:

This sample does not use some of the APIs like IUPnPDescriptionDocument interface APIs, 
IUPnPDeviceDocumentAccess interface APIs, etc. 


Notes for building the sample application:

To build the app, use VB6. When loading the project, you need to point the 
references for tlbtypes.olb and VboostTypes.olb supplied in the Platform SDK. 
Once you loaded the project, build the app by going to the menu and 
choosing File - Make exe.

