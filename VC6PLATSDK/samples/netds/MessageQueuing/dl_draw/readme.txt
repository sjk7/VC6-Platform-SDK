------------------------------------------------------------------------------

	Copyright (C) Microsoft Corporation. All rights reserved.

------------------------------------------------------------------------------

Sample: DL_DRAW

Purpose: 
This application demonstrates how to use MSMQ COM objects from VB.  The application basically allows the user to send/receive drawings to/from other drawing applications using a distribution list in the form of an Active Directory distribution group as the remote destination.  Note that there are other implementations of this "line drawing" protocol in C and VB that interoperate with this sample. 
The application also demonstrates how to send to a distribution list and how to get a list of all the distribution lists in the local domain.

A private text format is used to encode line-drawing information.  VB event handling is used to implement asynchronous message arrival.


Requirements:
Microsoft Visual Basic 6.0 is required (specifically, the WithEvents keyword is used).

Message Queuing 3.0 or later must be installed. Specifically, mqoa.dll must be registered and must be located on the path.

The computer on which the demonstration is executed should be DS-enabled. If it is not, the program will exit.

Overview:
When the VB DL_DRAW application is started, the user is prompted to specify a name, which can be any string and is used to create a local queue by that name.

If the user is working on a DS-disabled computer, the program exits.
A user working on a DS-enabled computer will be asked to choose whether the incoming queue will be private (not published in Active Directory) or public (published in Active Directory).
In the former case, a local private queue is created. In the latter case, a public queue is created.

After the local queue is (created and) opened, an asynchronous message handler is invoked to monitor that queue: messages that arrive are interpreted as line drawings and displayed on the form.

In order to send messages to a distribution list (an Active Directory distribution group), its ADs path must be entered. Although the program was written with distribution lists in mind, a queue ADs path can also be entered.

When the user clicks the "Get DL List" button, a list of the ADs paths of all the distribution lists in the local domain will be presented, and the user can choose one of the ADs paths listed.

After the user clicks the "Start Sending" button and connects to the DL (or queue), the picture control on the form allows the user to draw lines on its client area by dragging and clicking the left mouse button. Clicking the right button erases the screen. These mouse movements are captured and translated into a series of line coordinates. The coordinates are echoed on the form using standard VB Line commands and are also sent to the distribution list specified by the "ADsPath" string. Text can be entered in a similar manner. Both local and remote drawings/text will appear on the same form.
