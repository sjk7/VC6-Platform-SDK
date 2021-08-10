THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998  Microsoft Corporation.  All Rights Reserved.


Abstract:

This applications prints out a list (-l) of the names of predefined Qos 
templates using WSAGetQosByName.  The program also allows a new QoS 
template to be added to the system (-a), either service provider specific 
or global to all providers (-g).  Finally, the program allows the added 
QoS template to be removed.  

To ensure that system-defined templates do not get inadvertantly removed, 
only the "special" QoS template that is added by this program can be 
removed.


Usage:

  List all QoS templates
    qoslist
    qoslist -l
  Add a global QoS template
    qoslist -a -g
  Delete a global QoS template 
    qoslist -d -g

 
Build:

To compile/link this sample type nmake and use the supplied makefile or
build a project with VC++.  Please remember to use the headers and libs from 
the Platform SDK assocatied with NT5 Beta 2 or later.  Also, please link with 
ws2_32.lib and qosname.lib
      
