Telephony API (TAPI) Sample


The TapiComm sample uses both the Telephony API and the Win32 Communications 
API to demonstrate one way to implement a very simple TTY application. While 
the user interface and TTY emulation are very rudimentary, the TAPI and comm 
modules are fairly complete.

For more information, see the tapicomm.doc or tapicomm.rtf file included in 
the TapiComm sample directory.


Additional Notes on how to build the sample: 

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
-	go to the path where the TAPI sample 
	(TAPI2 and TAPI3) is installed and type NMAKE. 


