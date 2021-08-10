THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998  Microsoft Corporation.  All Rights Reserved.



Abstract:

This code is used to produce a sample program that demonstrates how to 
GQOS-enable a simple Winsock application.  This application makes no attempt 
to do anything useful per se, but concentrates on illustrating key techniques 
to use when developing your GQOS-enabled application.  Additionally, this 
application demonstrates several Winsock2-specific APIs and techniques that 
are useful whether or not your main interest is GQOS-enabling your application.

Commandline parameters determine whether this application functions as 
either a sender (-n) or a receiver (default).  Use the -? commandline 
switch to determine available options.

This application simply sends a buffer of data when acting as the sender,
to an instance of itself acting as a receiver.  Any number of senders (up
to MAXCLIENTS) can be started to interact with one instance of a receiver.
The size of the data buffer (-b), its contents (-d), and the number of 
times to send (-l) this buffer are controllable via commandline switches. 
A repeat value of 0 implies continuous sending.  The (-c) commandline switch
allows enabling/disabling QOS on the socket every 5 sends and will cause any
repeat count entered to be overridden and set to continuous mode. A delay 
commandline switch (-s:#), measured in milliseconds can be specified for the 
sender to insure the total transfer spans a measured unit of time (this would 
be interesting for observing RSVP PATH/RESV message refresh using a network 
monitor).

This application can be enabled to support GQOS by specifying a specific GQOS
template to use (-q) for transfers.  Additionally, when to enable GQOS 
(i.e. when to inform the GQOS Service Provider) can be controlled via a 
commandline switch (-i). 

The sender and receiver can choose to use either UDP or TCP (default) for 
data transfers by using the -p commandline option.  The port number (endpoint) 
used by TCP and UDP is also controllable via commandline switch (-e).

The application is also multicast capable. A multicast receiver must specify
the multicast option (-m) and the multicast IP address to join or allow a
default to be used.  If the multicast option is not specified but the sender 
attempts to send data directly to that multicast address, the -m is implicitly
set by the program. When both -n and -m values are used (by a
multicast sender) any address specified in -n is overriden by the value used
in -m.



APIs of Interest:
    WSAEnumProtocols (findsp.cpp)
    WSASocket (sender.cpp, recevier.cpp)
    WSAConnect (sender.cpp)
    WSAJoinLeaf (sender.cpp, receiver.cpp)
    WSAAccept (receiver.cpp)
    WSAEventSelect (sender.cpp, receiver.cpp)
    WSAWaitForMultipleEvents (sender.cpp, receiver.cpp)
    WSASend (sender.cpp)
    WSAIoctl (getqos.cpp setqos.cpp)
    WSAAddressToString (printqos.cpp)


Build:

This sample uses the following .cpp and .h files contained in this directory.

    chkqos.cpp
    findsp.cpp
    getqos.cpp
    setqos.cpp
    printqos.cpp
    qosevent.h
    qosevent.cpp
    receiver.cpp
    sender.cpp


To compile/link this sample type nmake and use the supplied makefile or
build a project with VC++.  Please remember to use the headers and libs from 
the Platform SDK assocatied with NT5 Beta 3 or later.  Also, please
link with ws2_32.lib


Usage:

This application is targeted to run on either NT5 Beta 3 (or later) and 
Windows 98.  It is not targeted to run on NT4 or Windows 95.  To run on NT4 or 
Win95 with Winsock 2, but without QOS capability change APPVER to 4.0 in the 
supplied makefile.

    Act as a TCP receiver and enable QOS using g711 codec
        qosevent -q:g711

    Act as a TCP sender and enable QOS using g711 and send buffer 10 times
        qosevent -n:receiver_host -q:g711 -l:10

    Act as a UDP sender and enable QOS using g711, send 
    buffer 30 times with a 2 second delay between sends
        qosevent -p:udp -n:receiver_host -q:g711 -l:30 -s:2000

    Act as a TCP sender, no QOS, and send buffer once
        qosevent -n:receiver_host

    Act as a multicast receiver and enable QOS using g711
        qosevent -q:g711 -m:234.5.6.7

    Act as a multicast sender and enable QOS using g711
        qosevent -q:g711 -m:234.5.6.7 -n

