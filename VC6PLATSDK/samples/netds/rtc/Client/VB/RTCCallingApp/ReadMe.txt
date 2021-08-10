------------------------------------------------------------------------------

	Copyright (C) Microsoft Corporation. All rights reserved.

------------------------------------------------------------------------------


RTC Client API v1.0
RTCSampleVB Incoming/Outgoing SDK sample



Overview:
=========

RTCSampleVB is a Visual Basic sample application for RTC Client API v1.0.
It demonstrates PC-to-PC, PC-to-Phone and Phone-to-Phone audio/video
communication. This sample was developed using Visual Basic 6 (SP5).



Interfaces Demonstrated:
========================

This sample demonstrates methods from following five RTC Client interfaces:
* IRTCClient
* IRTCSession
* IRTCEventNotification
* IRTCSessionStateChangeEvent
* IRTCMediaEvent



Building the sample:
====================

Simply open the RTCSampleVB project (RTCSampleVB.vbp) in Visual Basic and
create RTCSampleVB.exe. Note that since RTC Client 1.0 is a new API being 
introduced in Windows XP, it can be compiled and executed only on Windows 
XP builds. This sample is not supported on Windows 2000, NT 4.0 etc.



Notes:
======

The user should create the necessary provisioning and ensure that proper
servers and gateways exist before making PC-to-Phone or Phone-to-Phone calls.

Furthermore, if two instances of this application are running at once, then
only the first instance will receive the incoming calls because it will be 
the one listening on port 5060.



How to use:
===========

A window will appear after starting the sample by running RTCSampleVB.exe.  
The bottom portion of window will display various information including 
status, errors, and other information.

ANSWERING CALLS:
This sample can be used to make and receive calls. There are two options to
receive a call:
* Check "Auto Answer": The sample will automatically answer an incoming call
  when checked.
* Click "Answer": An incoming call will alert (ring) once with the display 
  status showing "INCOMING". At this point, pressing the "Answer" button will
  connect the call and the displayed state will be changed to "CONNECTED".

CREATING A PC-to-PC CALL:
* Select the 'Session Type' and set it to "PC to PC".
* Enter an 'End URI' (which can be a machine name, IP address, or any other 
  correctly formatted SIP address).
* Press the 'Connect' button to initiate the call.

CREATING A PC-to-PHONE CALL:
In order to make PC-to-Phone calls, a SIP gateway is needed to convert the SIP
packets coming from the user agent to the appropriate Public Switch Telephone
Network (PSTN) signaling. Normally an Internet Telephony Service Provider (ITSP)
will provide this type of service, but any local SIP gateway is all that is 
needed. Before attempting to create a PC-to-phone call, the user must make sure
that the proper infrastructure (either via ITSP or gateway) is in place. Once 
this is available; a PC-to-phone call is made as follows:
* Select the 'Session Type' and set it to "PC to Phone".
* Enter an 'End URI' in the from of sip:telephonenumber 
  (full canonical form)@gateway address;user=phone 
  (e.g., sip:+13121234567@gateway.com;user=phone).
* Press the 'Connect' button to initiate the call.

CREATING A PHONE-to-PHONE CALL:
In order to make Phone-to-Phone calls, an ITSP that handles phone-to-phone calls
is required. Before attempting to create a Phone-to-Phone call, the user must 
make sure that the proper ITSP settings and configuration are in place. The user 
should also create a profile based on these settings and modify the sample code
to use this profile. Once this infrastructure is in place, a phone-to-phone call
is made as follows:
* Select the 'Session Type' and set it to "Phone to Phone".
* Enter a 'Local URI' which is the primary (calling) number in full canonical form.
* Enter an 'End URI' which is the secondary (called) number in full canonical form.
* Press the 'Connect' button to initiate the call.

TERMINATING A CALL:
* Click the 'Terminate' button to end a PC-to-PC, PC-to-Phone, or Phone-to-Phone call.

GENERATING DTMF TONES:
DTMF tones can only be generated while in the CONNECTED state (the status frame 
displays "CONNECTED") for PC-to-PC and PC-to-phone calls (i.e., Phone-to-Phone DTMF
is not supported).
* Press the desired DTMF digit to send a digit.

STARTING THE TUNING WIZARD:
* Pressing this button will start the tuning wizard.

NOTE: The tuning wizard can't be started while any type of call is active. Any active 
call must be terminated before using the tuning wizard functionality.


Sample Functionality:
====================

The sample demonstrates how to:

* Make outgoing calls.
* Receive incoming calls.
* Create any of the three session types (i.e., PC-to-PC, PC-to-Phone, or Phone-to-Phone)
* Start tuning wizard.
* Generate the DTMF tones.

It partially demonstrates the handling of RTC events and use of IVideoInterface
for managing video calls.


What this sample does not show:
===============================

The sample does not demonstrate how to:

* Create a session of type 'Instant Messaging' (IM).
* Provision the client.
* Handle Presence information.
* Watchers, buddies, and participant functionality (presence related).
* Application sharing.