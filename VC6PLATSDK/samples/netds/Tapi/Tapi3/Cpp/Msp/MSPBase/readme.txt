THIS IS NOT SUPPORTED BY MICROSOFT CORPORATION. IT IS PROVIDED "AS IS" BECAUSE WE BELIEVE IT MAY BE USEFUL TO YOU


	TAPI 3.0 Rendezvous Controls Sample Program


What the sample does?
~~~~~~~~~~~~~~~~~~~~~

RendSam is a simple program demonstrates how to use TAPI 3.0 Rendezvous Controls COM interfaces to 

. open an ILS directory, 
. configure a conference, 
. add a conference,
. enumerate conferences, 
. delete a conference,
. configure a user,
. add a user,
. enumerate users, and
. delete a user,

A few methods in TAPI 3.0 SDPBLB COM interfaces are also used in configuring a conference.


How do I build the sample program?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Set the SDK build environment (see SDK readme file.), then type "nmake" in this "Rend" directory. RendSam.exe will be built.


How do I use the sample program?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

After RendSam.exe is built, run 
	RendSam <ils>
where <ils> is the name or IP address of an ILS server. Note that credentials of the currently logged on user's will be used to bind to the ILS server.


What does this sample not show?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This sample does not query NTDS to find all available ILS servers, instead an ILS server is specified in command line. Conference and user configurations were minimal. One can use other methods in Rendezvous Control or SDP BLOB COM interfaces to do more complex configurations. 


 
Additional Notes on how to build the sample: 

 How to build the samples with VS.Net or VC6 or VC5:
-	install the DirectX9 SDK
-	go to the path where you installed the platform SDK 
	(e.g. C:\Program Files\Microsoft SDK) 
	and type SetEnv.Bat.
-	check the following environment variables: 
	PATH, LIB, INCLUDE. You can see their current 
	values by typing "SET" at the command prompt. 
	You should see that they contain first the SDK 
	paths and then the VC6 paths.
-	Set the enviroment variable DXSDKROOT to point to the 
	root directory of the DirectX9 SDK
	(e.g. set DXSDKROOT=C:\DXSDK )
	You can add this to the setenv.bat so DXSDKROOT will be set 
	whenever you run setenv.bat.  A good place to add this 
	line is right after the set MSSDK= line
-	go to the path where the Rend sample is installed
	(Samples\NetDS\Tapi\Tapi3\cpp\Rend) and type NMAKE. 
