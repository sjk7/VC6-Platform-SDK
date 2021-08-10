--------------------------------------------------------------------------

  Copyright (C) 1997-1999 Microsoft Corporation. All rights reserved.

--------------------------------------------------------------------------

TAPI 3.0
INCOMING Sample Application


Overview:

INCOMING is a Visual Basic sample TAPI 3.0 application that waits for 
and answers incoming calls: phone calls or H323 audio calls.
This sample was developed using Visual Basic 6.

In order to receive incoming call notifications, as well as the related call
state event notifications, the application must call RegisterCallNotifications
specifying the media types for which it wants to be notified (therefore
not all incoming calls will be offered to the app, but only those that
have the desired media types). This sample registers for receiving audio
calls (it registers for the "audio" media type).

The application must also declare a TAPI object "with events", and 
implement for it the event procedure that processes the events - this 
procedure is called "Event". This is actually the function that will get 
called by Tapi3.dll each time when a new call is offered, and also when 
the call changes its state.

In order for Tapi3.dll to know about this event procedure, the object 
"tapi with events" must be assigned the value of a real tapi object 
(for which also the method Initialize has been called - this is a 
TAPI 3.0 requirement) - search in the sample code "gobjTapiWithEvents".
This is equivalent with "registering an outgoing interface" from C/C++.
For more information about declaring and using objects with events, see
Visual Basic 5's Books Online or, if you are using Visual Basic 6, check
the MSDN.

INCOMING shows how to use a "TAPI object with events" in order to 
receive notifications about incoming calls, and how to answer and 
eventually disconnect the incoming call.


How to use:

To run the INCOMING sample application, simply build and run incoming.exe,
using Visual Basic 6.
A small dialog box will appear, and the user is supposed to select the 
desired call type and press "Register". After that, the status will be 
"Waiting for a call."
The 2 possible call types (for this application) are: phone calls and 
H323 calls. In order to succesfully register for receiving "audio" phone 
calls, a "voice modem" must be currently installed on the computer. 

In both cases, H323 calls or phone calls, the application counts on 
the existence of a sound card (full duplex). The app selects on the call 
the default terminals for "capturing" and "rendering" the media type 
"audio"  - these are "microphone" and "speakers";
therefore, after the call is answered, you should be able to use 
the microphone and the speakers currently existing on the computer
to talk to the person from the other end of the call. 
However, in the case of phone calls, only the microphone might work, 
because most of the voice modems are half duplex. If you have a 
full duplex voice modem, then both audio terminals should work, the 
microphone as well as the speakers.


Limitations:

The way this sample was implemented, in the case of phone calls it 
will allow only "automated voice" calls, which means that the sound 
card is used for talking (the microphone and eventually the speakers 
too, if the voice modem is full duplex). But Tapi 3.0 actually allows 
also two other types of phone calls: "interactive voice" calls, 
and "datamodem" calls.
In order to support those too, the application should be changed in
the following way:
- for "interactive voice" calls: "audio" is still the media type that 
must be used when calling RegisterCallNotifications, but in this case 
the app must select no terminals on the streams. In fact, the app 
should not use the ITStream[Control] interfaces at all.
In this case, once the call is answered and becomes "connected", 
the phone set plugged into the modem must be used to actually talk 
to the person from the other end of the call.
- for "data" calls: "data modem" is the media type that should be 
registered instead of "audio"; then after the call is answered it will
go to connected state. 
Further, if the programmer wants to transfer data on the call, a special 
interface must be queried from the call object: ITLegacyCallMediaControl. 
This interface exposes (for C/C++ only) a method called GetID which 
can be further used; it corresponds to lineGetID from tapi2.x.


What functionality this sample does show:

The incoming sample application demostrates how to receive new call
notification and call state event notifications.  It also demonstrates
the basic TAPI 3.0 functions involved in answering a call.


What this sample does not show:

This sample does not let the user choose the TAPI address for the
application to use (in case there are several addresses that meet the 
same criteria, the sample will always use the first one). It does not 
allow the user to decide what media types to listen for, and it does 
not allow the user to decide what terminals to use: the sample always
uses the media type "audio" and its default terminals for "rendering" 
and "capturing".


Hints:

An H323 address will exist on your computer if H323 provider is 
installed, and if the computer is part of a network: the H323 provider
uses the machine's network card to actually implement the "H323 address".
Control Panel - Telephony applet should show if the H323 provider is 
currently installed; H323.tsp is installed by default by the operating 
system Window 2000.

In case you want to use the sample for receiving phone calls, a voice
modem should be installed; the data modems will not work with this sample
because they don't support registering for receving "audio" 
calls (which is the only case illustrated by this sample).

In all cases, a sound card is also expected to be installed.



Notes for building the sample application:

To build the app, you can use either VB6 or VB5. When loading the project 
(incoming.vbp) with VB5, you might get an error. In that case, delete from 
incoming.vbp the line that causes the error, then try loading it again. 
That line is VB6 specific and therefore not recognized by VB5.
Once you loaded the project, build the app by going to the menu and 
choosing File - Make.

