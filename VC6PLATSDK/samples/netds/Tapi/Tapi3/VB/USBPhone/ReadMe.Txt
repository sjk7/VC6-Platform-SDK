-----------------------------------------------------------------------------

  Copyright (C) 1997-2000 Microsoft Corporation. All rights reserved.

-----------------------------------------------------------------------------


TAPI 3.1
USB Phone Sample Application



Overview:
=========

USBPhone Sample is a Visual Basic sample TAPI 3.1 application that makes and 
receives audio calls on a USB phone using H323 Line. This sample was developed
using Visual Basic 6.

This sample shows the use of USB phone in two states, when phone handling is
enabled and when it is disabled. In both states outgoing and incoming audio
calls can be handled. 



APIs Demonstrated:
==================

This sample demonstrates the use of following three TAPI interfaces:
1) ITPhone
2) ITAutomatedPhoneControl
3) ITPhoneEvent	

Note that these are new interfaces introduced on the Whistler platform. 
This means that this sample can be compiled and executed only on a Whistler build, 
it cannot be built nor executed on Windows 2000. 


Building the sample:
====================

Simply open the USBPhone project (USBPhone.vbp) in Visual Basic 6 and create
USBPhone.exe. In order for this to work, the sample must be built on the 
Whistler platform (because it makes use of interfaces that are not present on 
Windows 2000 or before). 

Before running the sample make sure that

1) USB phone is connected to the system and no other application is using it.
2) H323 gateway exists on the network for making telephone calls. This can be
   checked by opening 'Phone and Modem Options' from Control Panel. Go to 
   'Advanced' tab, select 'H.323 Telephony Service Provider' and click 
   'Configure'. 'Use H.323 gateway' should be checked and valid gateway name 
   should be in the adjacent text field.
   
Note: If gateway is not available this sample is able to only call Machine 
      names or IP addresses.



How to use:
===========

On running USBPhone.exe a window will appear. Top portion of window will
display some information about the phone and the addresses available on your 
machine.

PHONE HANDLING ENABLED OR DISABLED:
The sample can use the USB phone in two states, in Phone handling enabled 
and phone handling disabled state. These states can be selected by checking 
and un-checking 'Enable Phone Handling' check box. When phone handling is 
enabled certain functions happen automatically. For example, dial tone being
generated when handset is picked up, call being automatically dialed on 
pressing '#' after a phone number is entered etc. These things will not happen
if phone handling is disabled. Developer needs to write specific code to 
accomplish these things or can enable phone handling to do these things for 
them.

MAKING A CALL:
To make a call type in the destination address, select the Address type i.e. 
a 'Machine Name or Phone number' and click 'Place Call'. Another way a call
can be made is when phone handling is enabled. In this case pick up the 
phone handset, enter the phone number and either press '#' or wait for 
three seconds for call to be dialed.

DISCONNECTING A CALL:
The calls can be disconnected by using the 'Disconnect' button and if phone
handling is enabled then pressing the hook switch will disconnect the call.
The 'Status' field will also provide this information while the samples runs.

RECEIVING A CALL:
Once an incoming call comes 'Status' will show a message informing about an
incoming call. Furthermore 'Answer Call' button will be enabled and either 
this button can be used to answer the call or if phone handling is enabled 
then picking up the handset will automatically answer the call. Keep in mind 
that incoming call will be automatically ignored if phone is already in use 
for an outgoing or incoming call. 

The 'Manual Control' frame will be active if phone handling is disabled. 
Pressing these buttons will allow a user to explore various features of USB
phone that can be controlled through ITAutomatedPhoneControl interface.   



What functionality this sample does show:
=========================================

The USBPhone sample application demonstrates how to make and receive new
calls using a USB phone. It demonstrates lightly how to control phone using
ITAutomatedPhoneControl such as generating tones and rings.



What this sample does not show:
===============================

This sample does not let the user choose the TAPI address for the
application to use. The sample always uses H.323 line for making calls. 
It does not show in detail how to control, set properties, generated tones 
etc when phone handling is disabled. It doesn't show how connect to a 
conference using USB phone. 



Hints:
======

An H323 address will exist on your computer if H323 provider is 
installed, and if the computer is part of a network: the H323 provider
uses the machine's network card to actually implement the "H323 address".
Control Panel - Telephony applet should show if the H323 provider is 
currently installed; H323.tsp is installed by default by the operating 
system Window 2000.

In all cases, a sound card is also expected to be installed.
