------------------------------------------------------------------------------

	Copyright (C) Microsoft Corporation. All rights reserved.

------------------------------------------------------------------------------

Sample: DistCreate

Purpose:
This application demonstrates how to create public and private queues, how to create a queue alias to a private queue, and how to create a distribution list in the form of an Active Directory distribution group, as well as how to add public queues and a queue alias to a distribution list.
The application also demonstrates how to create a distribution list and queues in a general solution - without having the computer name and the domain name hard-coded into the source.

Requirements:
Microsoft Visual Basic 6.0 is required.

Message Queuing 3.0 or later must be installed. Specifically, mqoa.dll must be registered and must be located on the path.

The computer on which the demo is executed must be DS-enabled.

Overview:
An IADsGroup object is created and set to be a distribution list. Then, two public queues and a private queue are created. A queue alias is created and given the private queue's format name as the queue to which the alias refers. The two public queues and the queue alias are added to the distribution list, and then a simple message is sent.

Copyright (c) Microsoft Corporation.  All rights reserved.
