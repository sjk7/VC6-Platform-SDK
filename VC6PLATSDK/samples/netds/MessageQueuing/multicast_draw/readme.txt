------------------------------------------------------------------------------

	Copyright (C) Microsoft Corporation. All rights reserved.

------------------------------------------------------------------------------

Sample: multi_draw

Purpose: 
This application demonstrates how to use MSMQ COM objects in VB.  The application basically allows the user to send/receive drawings to/from other drawing applications.  Note that there are other implementations of its "line drawing" protocol in C and VB that interoperate with this sample.
This application also demonstrates how to use the new "real-time multicast messaging" feature of MSMQ 3.0.

A private text format is used to encode line-drawing information.  VB event handling is used to implement asynchronous message arrival.


Requirements:
Microsoft Visual Basic 6.0 is required (specifically, the WithEvents keyword is used).

Message Queuing 3.0 or later must be installed.  Specifically, mqoa.dll must be registered and must be located on the path.


Overview:
When an instance of the multicast_draw application is started, the user is prompted to specify the name of a local queue. 

If the user is working on a DS enabled computer, she will be asked to choose whether she would like the local queue to be public or private. If the computer is DS disabled, then only a private local queue can be created.

The user is also asked to specify a multicast address for the local queue in the form of two separate values - an IP address and a port number.

After (creating and) opening the local queue, an asynchronous message handler is invoked to monitor that queue: messages that arrive are interpreted as line drawings and displayed on the form. 

The user then can specify a multicast address to which the messages are sent. After clicking the "Start Sending" button and opening an MSMQdestination object that represents the multicast address, the picture control on the form allows the user to draw lines in its client area by dragging and clicking the left mouse button. Clicking the right mouse button erases the screen. These mouse movements are captured and translated into a series of line coordinates.

The coordinates are echoed on the form using standard VB Line commands and are also sent to the multicast address specified by the "MultiCast IP address" and "Port Number." Text can also be entered.  Both local and remote drawings/text can appear on the same form.

