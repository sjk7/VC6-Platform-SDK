------------------------------------------------------------------------------

	Copyright (C) Microsoft Corporation. All rights reserved.

------------------------------------------------------------------------------

Sample: VB_DRAW

Purpose: 
This application demonstrates how to use the MSMQ COM objects from VB.  The application basically allows the user to send/receive line drawings to/from other drawing applications.  Note that there are other implementations of this "line drawing" protocol in C and VB that interoperate with this sample.

A private text format is used to encode line-drawing information.  VB event handling is used to implement asynchronous message arrival.


Requirements:
Microsoft Visual Basic 5.0 is required (specifically, the WithEvents keyword is used).

Message Queuing 2.0 or later must be installed. Specifically, mqoa.dll must be registered and must be located on the path.


Overview:
When a VB_DRAW application is started, the user is prompted to specify a name, which can be any string and is used to create a local queue by that name.

A user working on a DS-enabled computer will be asked to choose whether to connect to a DS-disabled or a DS-enabled client. 
In the former case, a local private queue is created. Then the name of the remote computer with which to connect as well as the remote queue name must be supplied. 
This means that the connection will be direct.
In the latter case, a public queue is created. Afterwards, the user is asked to enter only the remote queue name, and the directory service is queried to ascertain the computer name. We call this standard mode.
On a DS-disabled computer there is no possibility of working in standard mode, and therefore no such option is offered. The connection will always be direct.

After (creating and) opening the local queue, an asynchronous message handler is invoked to monitor that queue: messages that arrive are interpreted as line drawings and are displayed on the form. After the "Start Sending" button is clicked and a connection with the remote queue is established, the picture control allows the user to draw lines in its client area by dragging and clicking the left mouse button. Clicking the right button erases the screen. These mouse movements are captured and translated into a series of line coordinates that are included in MSMQ messages.
The coordinates are echoed on the form using standard VB Line commands and are also sent to the queue specified by the "remote queue name" string. Text can also be entered, and the characters typed are included in messages. Both local and remote drawings/text can appear on the same form.


