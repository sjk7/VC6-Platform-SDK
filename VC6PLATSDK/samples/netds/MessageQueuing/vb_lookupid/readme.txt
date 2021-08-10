------------------------------------------------------------------------------

	Copyright (C) Microsoft Corporation. All rights reserved.

------------------------------------------------------------------------------

Sample: vb_LookupId

Purpose:
This application uses the LookupId property of the MSMQMessage object to peek at messages 
in a specified queue.
The application peeks at messages in the queue specified and displays them as a table. By walking through the pages of messages, the user sees all the messages in the queue.  

Requirements:

Microsoft Visual Basic 6.0 is required.
MSMQ 3.0 or later must be installed.


Overview:
When vb_LookupId is started, the user is prompted to specify a queue name.
This can be any string and is used to open a local queue by that name or to create one, if it does not exist. 

If the user's computer uses a directory service (DS), he will be asked to choose whether he
would like to open a local public queue or a local private queue.
If the user's computer does not use a DS, only a local private queue can be opened.

After clicking the "Connect" button, a window displaying the first 20 messages in the queue is opened. The remaining messages in the queue can be browsed by pressing the "First Page," "Last Page," "Next Page," and "Previous Page" buttons.





 