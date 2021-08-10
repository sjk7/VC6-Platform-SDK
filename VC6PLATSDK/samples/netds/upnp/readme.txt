This is the readme for the device host sample.

SUMMARY
======= 

The Dimmer sample demonstrates a minimal UPnP device implemented using UPnP Device Host API. The DCO_DimmerService directory contains the implementation for the device dll. The RegisterDevice directory contains the implementation for registering the device dll with the UPnP Registrar service on the machine. The StepByStep directory contains VC6.0 projects corresponding to the Step By Step Guide below for developers without prior ATL/COM experience.


BUILD THE SAMPLE
================

In the Platform SDK build environment, run "nmake" without quotes under the DimmerDevice directory. Please make sure you have installed both the Core SDK and the Internet SDK. The xmldom.idl and xmldso.idl required to build the sample are shipped only in the Internet SDK.


RUN THE SAMPLE
==============

The makefile for the device runs "regsvr32 UPNPSampleDimmerDevice.dll" command automatically. After building the sample, you could simply locate the RegDevice.exe under the RegisterDevice directory and run it. When the RegDevice.exe is running, you could use the Generic UCP sample to query the DimmerDevice. When done testing, hit "d" in the console window to exit the RegDevice program.


STEP BY STEP GUIDE
==================

The DimmerDevice sample is implemented as an ATL COM server as required by UPnP Device Host API. The following step-by-step guide is to help developers without prior ATL COM experience to quickly build an ATL COM server framework. However it's not a replacement of ATL COM training. It's highly recommended that the developers study ATL COM documentation in MSDN to fully understand and correctly implement ATL COM Server.

The step by step projects are created using VC++6.0 with SP5 installed. You may want to compare the complete sample DCO_DimmerService code with the code generated each step below to actually follow the instructions. 

1. Create the device description XML and service description XML. In this case, DimmerDevice-Desc.xml and DimmingService_SCPD.xml are already copied to the Step1 directory. Run "utl2idl.exe DimmingService_SCPD.xml" with quotes and the DimmingService_SCPD.idl file is generated. The Platform SDK utl2idl tool converts the service description xml to an idl file with interfaces that the device COM server needs to implement. Open the DimmingService_SCPD.idl file, change interface IUPnPService_DimmingService_SCPD to inherit from IUnknown to IDisptach like	 the following:

	interface IUPnPService_DimmingService_SCPD : IDispatch

2. In VC++6.0, choose menu File | New and select the Projects Tab. Under the Projects Tab, highlight the selection ATL COM AppWizard, enter your project name MyDevice and choose a location for your project. Select Ok. In the next ATL COM AppWizard dialog box, make sure Dynamic Link Library (DLL) is selected and click Finish button. Choose Menu Project | Settings, and choose C/C++ tab, Choose Category Preprocessor, add UNICODE and _UNICODE to the Prepocessor definitions.

2.1 Choose menu Insert | New ATL Object..., and in the ATL Object Wizard dialog box choose Simple Object, click Next. In the ATL Object Wizard Properties dialog box, In the Short Name text box enter Dimmer. Click Attributes tab, select Free threading model, and click Okay.

2.2 Repeat step 2.1 but this time enter DimmerService in the Short Name text box. Make sure you still choose the Free threading model.

2.3 Open DimmingService_SCPD.idl generated in step 1 in notepad and copy into clipboard. In VC++ MyDevice project, open MyDevice.idl, paste the clipboard right after the following line:

library MYDEVICELib
{
	importlib("stdole32.tlb");
	importlib("stdole2.tlb");

-->paste at this line-->

Click menu File | Save to save the modified MyDevice.idl

2.4 In the MyDevice project window, right button click on Source Files, click on popup menu "Add Files to Folder...", navigate to the PSDK include directory and add upnphost.idl to the  project. Right button click on upnphost.idl, and click on Compile upnphost.idl. As a result, upnphost.tlb is built.

2.5 In the MyDevice project window, click the ClassView tab at the left bottom of the project window. Right button click on the CDimmer class, and select popup menu Implement Interface ... Click OK if you see a warning dialog box saying the project's type library can not be found. In the next Browse Type Libraries dialog box, click Browse... button, and choose upnphost.tlb located in the project's debug directory. Lastly select the IUPnPDeviceControl interface and click OK. Basically this step makes CDimmer class implements the IUPnPDeviceControl interface.

2.6 In the MyDevice project window, click the ClassView tab at the left bottom of the project window. Right button click on the CDimmerService class, and select popup menu Implement Interface ... Click OK if you see a warning dialog box saying the project's type library can not be found. In the next Browse Type Libraries dialog box, click Browse... button, and choose upnphost.tlb for the project's debug directory. Lastly select the IUPnPEventSource interface and click OK. Basically this step makes CDimmerService class implements the IUPnPEventSource interface. At this point, your source code should be like those under Step2 directory.

 
3. The step 2 has generated all the interface supports you need to implement our sample UPnP device. However the wizard generated code has unused interfaces and code and it's good to clean them up.

3.1 In the MyDevice project window, click on the FileView Tab, and under Resource Files, delete DimmerService.rgs. And also physically delete the DimmerService.rgs file from the project directory. Then click to open MyDevice.rc file, an error dialog box pops up as the DimmerService.rgs is no longer on disk, select Edit Code, remove the following line from the MyDevice.rc file:

IDR_DIMMERSERVICE       REGISTRY DISCARDABLE    "DimmerService.rgs"

If you don't get the error, open the file in notepad, and remove the line mentioned above.

Close and save the MyDevice.rc file. Open DimmerService.h, comment out the following two lines:

	DECLARE_REGISTRY_RESOURCEID(IDR_DIMMERSERVICE)
	DECLARE_PROTECT_FINAL_CONSTRUCT()


3.2 Open MyDevice.cpp, comment out the following line from the ObjectMap

	OBJECT_ENTRY(CLSID_DimmerService, CDimmerService)

Basically you don't need COM coclass for the CDimmerService as it's only created internally from CDimmer code. You only need COM coclass for CDimmer as it needs to be created externally.

3.3 Open MyDevice.idl, comment out the following IDimmer and IDimmerService declaration (The GUIDs in your project will vary):

	[
		object,
		uuid(058B03E3-7E89-432F-B4A8-77628E134CC1),
		dual,
		helpstring("IDimmer Interface"),
		pointer_default(unique)
	]
	interface IDimmer : IDispatch
	{
	};
	[
		object,
		uuid(A42B1F93-5D65-4537-AC6E-46C3A00D70D8),
		dual,
		helpstring("IDimmerService Interface"),
		pointer_default(unique)
	]
	interface IDimmerService : IDispatch
	{
	};

	[
		uuid(4322DC5F-0080-418A-9C71-DC00694CDE3A),
		helpstring("DimmerService Class")
	]
	coclass DimmerService
	{
		[default] interface IDimmerService;
	};

And then, change the default interface of coclass Dimmer to IUnknown like below:

	coclass Dimmer
	{
		[default] interface IUnknown;
	};

Basically you just use the VC tools to generate COM framework but you don't really need to implement IDimmerService and IDimmer. Close and save MyDevice.idl. In the project window, right click MyDevice.idl and select popup menu Compile MyDevice.idl.


3.4 Open Dimmer.h and comment out the following line from the parent of CDimmer class:
	
	public IDispatchImpl<IDimmer, &IID_IDimmer, &LIBID_MYDEVICELib>,

Comment out the following two lines from the COM Map.

	COM_INTERFACE_ENTRY(IDimmer)
	COM_INTERFACE_ENTRY(IDispatch)


3.5 Open DimmerService.h and comment out the following two lines from the parent inherits of CDimmerService class:
	
	public CComCoClass<CDimmerService, &CLSID_DimmerService>,
	public IDispatchImpl<IDimmerService, &IID_IDimmerService, &LIBID_MYDEVICELib>,

Comment out the following line from the COM Map.

	COM_INTERFACE_ENTRY(IDimmerService)


3.7 In the MyDevice project window, click the ClassView tab at the left bottom of the project window. Right button click on the CDimmerService class, and select popup menu Implement Interface. Select the IUPnPService_DimmingService_SCPD interface and click OK. Basically this step makes CDimmerService class implements the IUPnPService_DimmingService_SCPD interface. Open DimmerService.h, change one of the parent inherits of CDimmerService from IUPnPService_DimmingService_SCPD to the following:

	public IDispatchImpl<IUPnPService_DimmingService_SCPD, &IID_IUPnPService_DimmingService_SCPD, &LIBID_MYDEVICELib>
	//public IUPnPService_DimmingService_SCPD


3.8 In MyDevice Project window, open MyDevice.idl, change the GUID for coclass Dimmer to the following:

	[
		uuid(d31b8f49-367e-41b7-8fc4-50e23d36625d),
		helpstring("Dimmer Class")
	]
	coclass Dimmer
	{
		[default] interface IUnknown;
	};

Make sure you change the correspond CLSID entries in the Dimmer.rgs. This is because the RegisterDevice sample is hardcoded with above coclass GUID. With this change, you can use the RegisterDevice sample to test the device.

At this point, you are done building the COM framework required for the device. Your source code should be like those under Step3 directory.

4. Now the COM server framework is completed and you need to add device specific logic to the code. You could cut and paste member variables and methods from the complete sample DCO_DimmerService code to your own project. When you are done, your code should be like those under Step4 directory. And it should compile and work with the RegisterDevice sample.

4.1 Open Dimmer.h from the FilesView and the DimmerDeviceDCO.h from the DCO_DimmerService directory in the samples\upnp folder in the Platform SDK. Add the following two lines to the Dimmer.h:

#define NUM_TEMPLATE_UDNS_IN_DESCDOC 1	//This is equal to the number of devices (root or embedded) in the description doc
#define MAX_NOSERVICE_PER_DEVICE 1		//This  is equal to the maximum number of services in any device in the description doc

Copy and paste private members, and public functions from DimmerDeviceDCO.h to Dimmer.h.

4.2 Open Dimmer.cpp from the FilesView and the DimmerDeviceDCO.cpp from the DCO_DimmerService directory in the platform SDK. 

Copy and paste implementations of CDimmer from DimmerDeviceDCO.cpp to Dimmer.cpp. Global replace UPNPDimmerDevice to CDimmer. Add the following include:

#include "DimmerService.h"

4.3 Open our DimmerService.h from your sample's directory and the DimmerService.h from the DCO_DimmerService directory. 

Copy and paste private members, and public functions from DCO_DimmerService's DimmerService.h to yours.

4.4 Open the DimmerService.cpp from your sample directory and the DimmerService.cpp from the DCO_DimmerService directory. 

Copy and paste implementations. Global replace UPNPDimmerService to CDimmerService. 

4.5 Compile the project and test with the RegDevice sample.