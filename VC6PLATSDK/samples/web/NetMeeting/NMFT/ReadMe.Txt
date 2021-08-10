------------------------------------------------------------------
         Microsoft NetMeeting SDK 3 NMFT Readme File
                           April 1999
------------------------------------------------------------------

             (c) Copyright Microsoft Corporation, 1999

CONTENTS
========

OVERVIEW OF THE NMFT SAMPLE
BUILDING THE NMFT SAMPLE


OVERVIEW OF THE NMFT SAMPLE
===========================

NMFT is a Windows utility application that allows the user to 
send files via an existing NetMeeting connection.  NMFT can be added
to the system pop-up menu by placing the executable in the Windows
SendTo directory.


BUILDING THE NMFT SAMPLE
========================

Building the sample application requires VC++ Version 6.0 or later.

To build the sample under VC++, open the project makefile (nmft.mak) 
as a Microsoft VC++ project, and build as usual.  The NetMeeting SDK 
directories must be added to your VC++ environment.

If your DOS environment is correctly configured, you can build the sample
from the command line by typing "nmake".  The DOS path, include and lib
environment variables must point to the VC installation and the 
NetMeeting SDK directories.


Notes: 

1) The NMFT sample is designed to be placed in the Windows SendTo 
   directory.  This will make it available on the user's right-click
   menu in the Explorer.  

2) Launching NMFT will cause NetMeeting to launched if it is not already
   running.  However, no files will be transferred unless you are in 
   a conference when NMFT is executed.

3) The transferred file will be sent to all conference members.
