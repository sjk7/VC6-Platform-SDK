--------------------------------------------------------------------------

  Copyright (C) 1997-1999 Microsoft Corporation. All rights reserved.

--------------------------------------------------------------------------


TAPI 3.0
DTMF Sample Application


Overview:

DTMF is a sample TAPI 3.0 application that is able to generate and detect 
DTMF tones over an outgoing call made on an address that supports DTMF 
(e.g. a voice modem address).
It was developed using Visual Basic 6.


How to use:

To run the DTMF sample application, simply build and run DTMF.exe, using
Visual Basic 6.
A form will appear in which the user can type in a destination address
to dial. The user also must indicate the address on which the call is to 
be made.
Select the address on which to make the call (select a voice modem address),
enter the destination address (enter a phone number) and press Dial.
At the other end of the call, pick up the phone - this will put the call 
in connected state.

After the call is connected, generate DTMF tones by entering the digits 
to be generated and pressing "Generate".

In order to detect tones, you must specify the Digit Mode by checking 
one or more "Digit Mode" checkboxes, then press StartDetect. (You should 
probably check only DTMF or DTMF and DTMFEND, but depending on the system
you are using, "Pulse" detection might also be possible).
After performing these steps, use the phone from the other end of the call 
to generate tones by pressing its keys - and watch the DTMF app 
to see the events printed in the "Status" edit box.
Pressing "StopDetect" should prevent the app from receving any DTMF events.


What functionality this sample does show:

The DTMF sample application shows how to generate and detect tones over 
a connected outgoing call, with TAPI 3.0, from VB.
It will let the user make an outgoing async call and then generate or 
detect tones by pressing the corresponding buttons.


What this sample does not show:

The sample does not show how to receive incoming calls.
 

Hints:

In order for this sample to work, the machine must have at least one 
TAPI 3.0 address that supports DTMF generation/detection. The buttons 
"Generate", "StartDetect" and "StopDetect" will be enabled for all addresses,
but for those addresses that don't support DTMF they pressing them will 
simply cause an error to be printed.

Usually, voice modems support DTMF generation/detection - so if you 
have such a modem installed on the machine, you should be able to 
successfully use the sample.

Notes for building the sample application:

To build the app, you can use either VB6 or VB5. When loading the project 
(dtmf.vbp) with VB5, you might get an error. In that case, delete from 
dtmf.vbp the line that causes the error, then try loading it again. 
That line is VB6 specific and therefore not recognized by VB5.
Once you loaded the project, build the app by going to the menu and 
choosing File - Make.

