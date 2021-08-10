*********************************************************************
                     SimpleFaxSendForm Sample
*********************************************************************
       Copyright(c) Microsoft Corporation. All rights reserved.

The SimpleFaxSendForm sample is a Visual Basic program that 
demonstrates how to send a fax using the FaxDocument object. The fax 
can consist of a cover page alone, an attachment alone, or an
attachment and cover page.

Usage: Enter the necessary information in the text fields, then
click the Send button. To change the sender information, click Sender 
information. Sender information can be saved as the default, or used
for a single fax.

Some attachments, such as PowerPoint presentations, will cause an
error in that application. After a few minutes, the SimpleFaxSendForm
program will resume. 

In general, faxes cannot be sent from a remote fax server unless the 
server is installed as a network printer on the local computer.

Project files: The Visual Basic project contains two forms, 
QuickFax.frm, which contains the code for sending the fax, and 
formSenderInfo.frm, for modification of the sender information. The 
project also includes the SenderModule.bas module, which contains 
declarations needed for both forms.

To create the browse control, the program uses the Microsoft Common 
Dialog Control 6.0

