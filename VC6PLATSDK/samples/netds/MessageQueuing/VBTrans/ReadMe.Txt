------------------------------------------------------------------------------

	Copyright (C) Microsoft Corporation. All rights reserved.

------------------------------------------------------------------------------

Sample: VBTrans

Purpose: 
This sample uses MSMQ COM objects from VB and demonstrates how to use the transactional boundary feature introduced in Message Queuing 2.0.

The application opens a local transactional queue and sends messages to that queue. The messages in the queue appear in a treeview, gathered in the transactions to which they belong. The user can then receive the messages from the queue as a single transaction.

Requirements:
Microsoft Visual Basic 5.0 or later.
Message Queuing 2.0 or later.

Overview:
When the VBTrans application is started, the user is prompted to specify a queue name. The application then creates a local queue by that name. A public queue is created on a DS-enabled computer, while a private queue is created on a DS-disabled computer.

If a queue by that name already exists, it is opened only if it is a transactional queue. In this case, the application updates the treeview by peeking at all queue messages. The transactions are identified by inspecting each message's sFirstInTransaction property. If the existing queue is not transactional, the user will be prompted to specify another queue name.

Once the queue has been opened with both send and receive access and the treeview has been updated, the DNS pathname of the queue will be displayed. It is obtained from the PathNameDNS property of the instance of MSMQQueueInfo.

If the queue is not empty, the user can receive messages by clicking the Receive button. Note that all messages belonging to a single transaction will be received.

After specifying the number of messages to be sent, the Send button can be clicked to send the messages to the queue. These messages will be sent as a single local transaction. The message labels can be viewed by clicking the transaction icon.
