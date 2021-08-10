*********************************************************************
                          QueueMonitor Sample
*********************************************************************
       Copyright(c) Microsoft Corporation. All rights reserved.

The QueueMonitor sample is a Visual Basic program that demonstrates
how to register for fax server events. The sample monitors the
outgoing fax queue, and refreshes the display when an
OnOutgoingJobAdded, OnOutgoingJobChanged or OnOutgoingJobRemoved 
event is received.

Note that access to the outgoing queue includes access to private
information regarding the faxes in the queue.

Though canceled and completed faxes from broadcasts are not removed 
from the queue until the entire broadcast is competed or canceled, 
this program removes them from the list individually. This is done
by means of a call to the OnOutgoingJobRemoved event, which would 
not be called automatically for the cancellation or completion of a
single fax from a broadcast.

When a job is added to the queue, it is also added to the bottom
of the list.

When the status or extended status of a job changes, that job is 
located on the list, and the status information is updated.

When a job is canceled or completed, that job is located and removed
from the list.

Usage: Type the name of a server in the space provided. The program 
connects to that server, and displays the faxes in the outgoing
queue.

Project files: The Visual Basic project includes one form, 
QueueMonitorForm.frm, which contains the code for operation of the 
monitor form.

The ListView control is from Microsoft Windows Common Controls 6.0.
