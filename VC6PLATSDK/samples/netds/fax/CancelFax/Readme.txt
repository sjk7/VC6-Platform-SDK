*********************************************************************
                          CancelFax Sample
*********************************************************************
       Copyright(c) Microsoft Corporation. All rights reserved.

The CancelFax sample is a Visual Basic program that demonstrates
how to cancel a fax or a group of faxes.

Usage: When you run this program, you have to provide the name of a 
fax server and press Enter. The program connects to that server, and 
blocks and pauses its outgoing queue. This prevents the addition of
new faxes to the queue (blocked) and the sending of faxes from the
queue (paused). This allows you to manage the cancellation process
on a static outgoing queue. When you switch to another server, or if
you click Close, the queue is unblocked and unpaused. If you terminate
the program in any other way, the queue will remain blocked and paused.
These properties can also be managed through the Fax Service Manager.

When you click on a fax, its subject, submission time, sender and 
submission ID are shown in the corresponding text boxes. You can
choose to cancel the selected fax, all faxes with the same subject as 
the selected fax, all faxes from the same sender, or all faxes in the 
same broadcast. For details about a group of faxes, choose a 
cancelation option, then click the View list of faxes button. Click 
OK to complete the cancellation process.

When you cancel a group of faxes that includes an entire broadcast,
those faxes are deleted from the outgoing queue, and the Count 
property of the FaxOutgoingJobs object is updated. However, if you 
cancel an individual fax from a broadcast, that fax has the status
Canceled, but remains in the outgoing queue, and the Count property
is not modified.

Project files: The project contains threee files: CancelFaxForm1.frm,
BroadcastInfoForm.frm, and StatusStringModule1.bas.


CancelFaxForm1.frm contains the code for the operation of the main
program form.

BroadcastInfoForm.frm contains the code for displaying details of
a group of faxes.

StatusStringModule1.bas contains the strings to display for the fax 
job status, as listed in FAX_JOB_STATUS_ENUM. This module also 
contains declarations of public variables.

The ListView control is from Microsoft Windows Common Controls 6.0.

