--------------------------------------------------------------------------

  Copyright (C) 1997-1999 Microsoft Corporation. All rights reserved.

--------------------------------------------------------------------------


TAPI 3.0
OUTGOING Sample Application


Overview:

OUTGOING is a sample TAPI 3.0 application that makes outgoing asynchronous 
audio (and eventually video) calls. 
It was developed using Visual Basic 6.

This sample shows the most basic TAPI 3.0 functionality - finding an
appropriate address object and creating a call on it.
It also shows some more advanced TAPI 3.0 functionality - how to use the 
stream interfaces to make video calls.


How to use:

To run the OUTGOING sample application, simply build and run OUTGOING.exe, using
Visual Basic 6.
A dialog box will appear, and the user can type in a destination address
to dial. The user also must specify the address type (phone number, machine
name, etc). So the destination address must match the selected address type.
Simply select an address type (e.g. "phone number"), type in a destination 
address (e.g. a phone number) and press the Dial button.


What functionality this sample does show:

The OUTGOING sample application shows how to make an asynchronous outgoing 
call with TAPI 3.0 from VB.
It will make an audio call and, if present, video will also be selected
on the call. If no audio capabilities are detected, no call is made at all.


What this sample does not show:

This sample does not allow the user to select the media types or terminals 
that the user is interested in. 

It also selects an address by picking up the first one that matches the 
selected address type and that supports at least the audio media types. So if 
there are more addresses that meet this same criteria, only the first address 
will be selected, the user cannot choose among them.

The sample does not show how to receive incoming calls.
 

Hints:

1. In order for this sample to run for making phone calls, a voice modem 
must be installed on the machine. 

2. If you want the sample to work with data modems too, you'll need to change
the sample to not use any terminals at all (just don't use the interfaces 
ITTerminalSupport and ITStreamControl). When calling CreateCall still specify 
the "audio" media type. When the call is connected, pick up the phone and talk. 
(A phone must be plugged in the local data modem).
In the case of using a data modem, a sound card is not required to be installed 
on the machine.

3. The sample will work if a full duplex sound card is installed on the system
(or a sound card with a full duplex driver) so that both audio terminals 
("audio capture" and "audio render" - microphone and speakers) can be selected 
on the call in the same time. 
However, if the user makes a phone call over a voice modem which is only 
half duplex (as most of the external voice modems are) then, although both 
terminals are selected on the call (microphone and speakers), only one 
of them will actually work (usually the microphone).

4. The addresses of type "machine name", and "ip address" support the video 
media type too. The media type "video render" should always be available for 
these addresses even if the machine does not have any special hardware 
(but the network card, which is used to implement the address object itself).
However, the "video capture" media type can be used only if a video card with a 
camera are installed on the computer. 
If video "render" or "capture" capabilities are detected, the sample application 
will use them. If no video capabilities are present, the call will be audio only.

5. You can enhance the sample to make calls using "email name" or "conference name"
addresses. The code will not change, but you will need to add code that uses the 
interfaces exposed by Rend.DLL to "translate" these addresses into something else 
before passing them to CreateCall: the email name must be transformed into an IP 
address, the conference name must be transformed into an SDP blob. In order to see 
the Rend.DLL interfaces in VB's Object Browser, you need to add rend.dll in the 
Project References: in VB6, select the menu options Project - References - Available 
References; in this list box, check the component called 
	"Microsoft Rendezvous control 1.0 Type Library".
For more info about Rendezvous control see the samples that come with this component
and the SDK help.

6. The sample will be able to make H323 (point to point IP calls) or conference calls 
(multicast) only if the machine is connected in a network. Also, for resolving the 
addresses of type "conference name" and "email name", an ILS server must exist on the 
network, and must list the Conference/Email Name you are looking for. 



Notes for building the sample application:

To build the app, you can use either VB6 or VB5. When loading the project 
(outgoing.vbp) with VB5, you might get an error. In that case, delete from 
outgoing.vbp the line that causes the error, then try loading it again. 
That line is VB6 specific and therefore not recognized by VB5.
Once you loaded the project, build the app by going to the menu and 
choosing File - Make.

