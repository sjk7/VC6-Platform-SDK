--------------------------------------------------------------------------

  Copyright (C) 1997-1999 Microsoft Corporation. All rights reserved.

--------------------------------------------------------------------------


TAPI 3.0
CALLHUB Monitoring Sample Application

CALLHUB is a sample TAPI 3.0 application that monitors call and callhub events
on all tapi addresses present on the machine, for all media modes.
It was developped using Visual Basic 6.


How to use:

To run the CALLHUB sample application, simply build and run CALLHUB.exe, using
Visual Basic 6.
After having started CALLHUB.exe, start some TAPI activity on the same machine:
use another TAPI application to make outgoing calls, or to receive incoming calls.
The application CALLHUB will show all these calls and their call states, 
and their related callhub and participant calls and events.

What functionality this sample does show:

The CALLHUB sample application shows how to monitor TAPI 3.0 addresses in order 
to see all new calls that appear on them, as well as the related call and callhub 
events.


What this sample does not show:

This sample does not perform any call control, it doesn't make nor receive calls,
and it can't control the monitored calls either. 


Note about events:

Different TSP-s (Telephony Service Providers) implement callhub feature differently.
Therefore don't expect them all to fire all defined callhub events, or even to 
show all the participant calls from a specific callhub. Most of the TSP-s will only 
show the local participant and they would have no information about the participant 
from the other end of the call.

Notes for building the sample application:

To build the app, you can use either VB6 or VB5. When loading the project 
(callhub.vbp) with VB5, you might get an error. In that case, delete from 
callhub.vbp the line that causes the error, then try loading it again. 
That line is VB6 specific and therefore not recognized by VB5.
Once you loaded the project, build the app by going to the menu and 
choosing File - Make.

