------------------------------------------------------------------------------

	Copyright (C) Microsoft Corporation. All rights reserved.

------------------------------------------------------------------------------

Sample: MULTI_DEST_DRAW

Purpose: 
This application demonstrates how to use MSMQ COM objects from VB.  The application basically allows the user to send/receive drawings to/from other drawing applications.  Note that there are other implementations of this "line drawing" protocol in C and VB that interoperate with this sample.

A private text format is used to encode line-drawing information.  VB event handling is used to implement asynchronous message arrival.


Requirements:
Microsoft Visual Basic 5.0 is required (specifically, the WithEvents keyword is used).

Message Queuing 3.0 or later must be installed.  Specifically, mqoa.dll must be registered and must be located on the path.


Overview:
When a MULTI_DEST_DRAW application is started, the user is prompted to specify the name of a local queue.

A user working on a DS-enabled computer will be asked to choose whether the local queue should be created as a private or a public queue.  If the computer is DS-disabled, then only a private local queue can be created.


After (creating and) opening the local queue, an asynchronous message handler is invoked to monitor that queue: messages that arrive are interpreted as line drawings and displayed on the form.

Then, the user will be asked to add queue names for other Draw family applications. If the computer is DS-enabled, the user can add names of both private and public queues.  If the computer is DS-disabled, the user will be able to add only names of private queue.

When the name of a private queue is added, the name of the computer with which to connect must be entered along with the name of a remote queue. 
When the name of a public queue is added, the user is asked to enter just the queue name, and the directory service is queried to ascertain the computer name. We call this standard mode.
On a DS-disabled computer, there is no possibility of working in standard mode, and therefore no such option is offered. The connection will always be direct.

The computer will keep the names of the queues until the "Start Sending" button is pressed.  After the "Start Sending" button is clicked and an MSMQdestination object with the added queue names is created and opened, the picture control allows the user to draw lines in its client area by dragging and clicking the left mouse button. Clicking the right button erases the screen. These mouse movements are captured and translated into a series of line coordinates that are included in MSMQ messages.
The coordinates are echoed on the form using standard VB Line commands and are also sent to the queues added to the destination. Text can also be entered, and the characters typed are included in messages. Both local and remote drawings/text can appear on the same form.


