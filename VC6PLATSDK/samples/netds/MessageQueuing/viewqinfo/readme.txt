------------------------------------------------------------------------------

	Copyright (C) Microsoft Corporation. All rights reserved.

------------------------------------------------------------------------------

View Queue Info Example

Purpose:
This application demonstrates how to use some of the properties and methods of the MSMQApplication COM object to obtain lists of the private and active queues on a specific computer as well as to obtain and reset the network connectivity status of the computer.

Requirements:
Message Queuing 3.0 and Microsoft visual Basic 6.0 must be installed.

Overview:
The user can enter the name of a computer on which he wants to obtain queue information. This name is then set by the MSMQApplication.Machine method. If no computer name is entered, the local computer is set as the default. After clicking the refresh button, the program displays information in three different pages of the dialog box. The “Private Queues” page displays a list of the path names of all the private queues on the computer. This list is provided by the MSMQApplication.PrivateQueues property. The “Active Queues” page displays a list of the format names of all the active queues on the computer, which is provided by the MSMQApplication.ActiveQueues property. Finally, in the “Computer Status” pane, the user can view the Message Queuing network connectivity status and toggle it as desired. The connectivity status is obtained from the MSMQApplication.IsConnected property and reset by the MSMQApplication.Connect and MSMQApplication.Disconnect methods.
