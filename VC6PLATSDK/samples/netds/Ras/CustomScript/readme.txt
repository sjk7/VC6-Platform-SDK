THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 2002  Microsoft Corporation.  All Rights Reserved.

PURPOSE :
=========

The purpose of this sample is to demonstrate the use the CustomScripting Ras Api
available on the RasClients and how it can be used with the other 3rd party
security apis on ther server side.

This Sample will work only on Windows 2000 and Windows XP.


REQUIREMENTS TO RUN THE SAMPLE :
================================

1) Windows 2000 Wks/Srv or Windows XP (Home/Pro)
2) Modems on each machine with phone line.
3) Optional custom Dial .DLL (see and build <Platform SDK Root>\Samples\NetDs\RAS\CustomDial sample)


WHAT DOES THE SAMPLE DO :
=========================

There are three directories under this sample.

1) customentry :  Customentry sample creates an .exe "customentry.exe". 
   This exe can create a customentry which has 
   the RASEO_CustomScript Flag set. In addition to 
   creating the proper registry entries, the DLL will create a 
   sample phonebook entry named "SDKSample" in the default  
   phonebook file. This entry will be set to use the first 
   modem found in the system. If a phonebook entry of that 
   name already exists, it will get recreated.
   Optionally if you include a path to the custom dial .dll this path will 
   be added to the phone entry as well as added to the registry:

       \\HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Rasman\Parameters\ 
       REG_EXPAND_SZ: CustomDll


2) customclient : This creates a dll customcli.dll.  This dll needs to be registered
   at following place in the registry.

   (a) Make sure that the path to the customscripting dll is set in 

       \\HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Rasman\Parameters\
       REG_EXPAND_SZ: CustomScriptDllPath

   (b) The CustomScriptDll should export the entrypoint as below - RasCustomScriptExecute.


3) customsrv : This uses the 3rd party security dll mechanism provided by the
   RasServer. See step 3) under STEPS TO RUN THE SAMPLE section.


HOW DOES THE SAMPLE WORK ?
==========================

On the server side register the dll "customsrv.dll" using the ini file provided
in the sample or by manually editing the registry. Stop remoteaccess service and
restart it. ( net stop remoteaccess and then net start remoteaccess). 
Now the control will be passed to this dll before PPP kicks in for any modem
connection made to this server. 

The client needs to creates a phone entry ( one in which the RASEO_CustomScript flag is
set). When we dial out from the client the RasCustomScriptExecute Entry Point in the
dll registered at the above registry location gets called. 

The RASDIALPARAMS get passed to the RasCustomScript Api also. 
The application internally modifies the username to "Administrator" and
password to "", to demonstrate that the RasDialParams can be changed
by this RasCustomScript Api as needed.

The Client Sends a string "Some client message" to the server. 
The Server Responds back saying "A server message".



STEPS TO RUN THE SAMPLE :
=========================


1) Build the customentry.exe and run:
   customentry.exe <phoneNumberTobeDialed> <optional_customdial_dll_path>

   Usage:
   1st Parameter: phone number to dial
   2nd Parameter: 0 - no custom script, 1 - sets RASEO_CustomScript 
   3rd Parameter: (optional) path to a ras custom dial .dll

  Example:
     customentry.exe ######### 0 "drive:\path\customdll.dll"

2) If you include the custom dial .dll path, when you dial using 
   this phone entry 'SDKSample' it will use you custom dial .dll if you specified
   a path to it. A sample of a custom dial .dll is located in 
   <Platform SDK Root>\Samples\NetDs\RAS\CustomDial directory


3) On the server side register the customsrv.dll in the registry at the following 
   reg location.

  - Edit the registry on the server:

  - Go to  HKLM\SOFTWARE\Microsoft\RAS.
  - Add a key SecurityHost
  - To that key, add a value named DLLPath of type REG_SZ and give full path
    to the security dll.  (example:  d:\customsrv\customsrv.dll)

    Example regini script:

    \\HKEY_LOCAL_MACHINE\Software\Microsoft\RAS\SecurityHost
    REG_SZ:
      DLLPath  
       (your location of customsrv.dll. Example: d:\customsrv\customsrv.dll)


    Stop the remote access service and restart it.
    (Or just reboot the machine).

4) On the Client Side register the customcli.dll at the location specified above.

   \\HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Rasman\Parameters\
    REG_EXPAND_SZ: CustomScriptDllPath

    Give the full path where the custom dll can be found.

5) Dial out using the entry created in one.


   You will see that client is sending the string "Some client message" and the
   server replying with "A server message".

   If you attach a ntsd to the svchost running remoteaccess service on the
   server side then you will see that server actually receives the above mentioned
   string. This all happens before the PPP kicks in.

6) On the Client Side the RasCustomScriptExecute changes the password and
   username to   "" and Administrator resepectively.  
    So to dial with a different username and password you will have to change
    the code in "customcli.dll".




