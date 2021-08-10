------------------------------------------------------------------
         Microsoft NetMeeting SDK 3 NMCHAT Readme File
                           1999-2002
------------------------------------------------------------------

             (c) Copyright Microsoft Corporation, 1999-2002

CONTENTS
========

OVERVIEW OF THE NMCHAT SAMPLE
BUILDING THE NMCHAT SAMPLE


OVERVIEW OF THE NMCHAT SAMPLE
=============================

NMCHAT is a Windows utility application that allows the user to 
send text messages to other NmChat users existing NetMeeting connection.  


BUILDING THE NMCHAT SAMPLE
==========================

Building the sample application requires VC++ Version 6.0 or later.

To build the sample from Visual C++, open the project makefile (nmchat.mak) 
as a Microsoft VC++ project, and build as usual.  The NetMeeting SDK 
directories must be added to your VC++ environment.

If your DOS environment is correctly configured, you can build the sample
from the command line by typing "nmake".  The DOS path, include and lib
environment variables must point to the VC installation and the 
NetMeeting SDK directories.


Notes: 
The chat sample uses an existing NetMeeting connection.  There is no way
to launch NetMeeting from the NmChat UI.

NmChat displays three windows.  The upper left displays the call roster and
allows the user to specify the recipient of a message.  The upper right
displays the status messages and time stamps.  Across the bottom is the
text entry area for composing your messages.

NmChat can only exchange data with another instance of NmChat.  This sample
should be running on all machines in the conference.

