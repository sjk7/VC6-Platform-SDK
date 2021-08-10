------------------------------------------------------------------------------

	Copyright (C) Microsoft Corporation. All rights reserved.

------------------------------------------------------------------------------

Manage Queue Example

Purpose:
This application demonstrates how to use various management properties of the MSMQApplication, MSMQManagement, MSMQQueueManagement and MSMQOutgoingQueueManagement objects.

Requirements:
Message Queuing 3.0 and Microsoft visual Basic 6.0 must be installed.

Overview:
The application asks the user to enter a path name or a format name of a queue. The user can also enter a computer name. If no computer name is entered, the local computer is set as the default. After entering the information requested, the user can click the “Refresh” button and then view information regarding the queue selected. The number of messages in the queue, the queue type, whether the queue is a destination queue or an outgoing queue are displayed on the “General Info” page. If the queue is an outgoing queue, the user can view the current state of the queue and the address for routing messages to the destination computer in the next hop on the “Outgoing Queue” page. The user can also select to pause the queue or resume the transmission of messages from it by pressing the applicable buttons. If the queue is a destination queue local to the computer selected, the user can view the journal message count, the amount of message data in the queue journal, and the amount of message data in the queue on the “Local Queue” page.
