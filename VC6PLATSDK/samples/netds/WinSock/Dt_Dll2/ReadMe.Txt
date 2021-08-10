Microsoft Platform SDK Winsock DT_DLL++ Sample Readme
Jeffrey C. Venable, Sr.
(c) 1998 - 2001, Microsoft Corporation

Microsoft's Winsock 2.0 implementation has introduced a very powerful yet
little known debugging and diagnostic tool known as 'DT'.  Quite simply,
it's a debugging specification fully qualified with its own whitepaper
which is available with the default sample on the Microsoft Platform SDK
under 'samples\NetDS\Winsock\dt_dll'.  It allows any sockets-based
application which uses Microsoft's implementation to hook all Winsock
API calls into dt_dll.dll which one might implement themselves, tracing
any information needed to debug an application.

To implement DT, one first and foremost needs the debug (checked) build
of the ws2_32.dll installed on their system, appropriate to the OS.  When
any application loads the Winsock2 debug .dll module, it makes a call to
LoadLibrary("dt_dll"), and if successful continues with GetProcAddress()
on the various APIs exported from dt_dll.dll per the whitepaper
specification.  However that specification requires that the APIs
dt_dll.dll exports handle variable argument lists which contain all of
the various parameters to the Winsock API calls.  With over 160 Winsock
APIs, this can be a daunting task to implement.

This sample implements a C++ framework whereby all of the variable
argument list manipulations and type-casting are already done in an easy
to use class.  All the developer need do is overload any of the virtual
protected methods of the same name as the Winsock API in which tracing
is desired.  The method is nearly identical to the API, having the same
parameters and the ability to hook the return value, with the exception
of a standard, final template parameter containing generic information
about the hook. (APIHook<>)

All the developer really needs to worry about is the following files:
    Implement the .dll framework to use the DT framework:
        dt_dll.hpp
        dt_dll.cpp
    Base class for implementing dt_dll.dll hooks:
        APIHook.hpp
        DTHandler.hpp
        DTHandler.cpp

SocketMonitor is a child class inherited from DTHandler to implement
four API hooks for the purpose of demonstrating this sample.

For ease of use, several of the debug builds of ws2_32.dll are included on the
Platform SDK CD under the 'mssdk\bin\debug' directory for the various Microsoft
platforms on which Winsock2 and DT are implemented.  These files are not installed
automatically when the Platform SDK is installed.  While you can obtain
these same .dll's from other Microsoft sources, please use the NT4 SP3
ws2_32.dll provided as the original build of this .dll was missing some debug
information and most of the DT hooks are missing; this should be corrected by
SP4.  If you are working with Whistler betas, you will need the debug ws2_32.dll
appropriate with the beta number or build number.  Contact Microsoft Developer
Support if you need the checked ws2_32.dll for a valid product which you have
and cannot find.

It's easiest to install these from a dual-boot system in which ws2_32.dll
isn't loaded by any processes on the target OS by simply replacing the file.
Make sure before replacing any ws2_32.dll to back it up someplace.  If a
single boot system is the target, close all sockets applications and stop all
networking-related services.  Since it will take a few minutes to 'unlock' the
ws2_32.dll from use (and protection), deletion or replacement isn't best.
Instead rename the ws2_32.dll (this is a good opportunity to back it up) to
something like ws2_32.free (free as opposed to debug).  After that's done, copy
in the appropriate ws2_32.dll.
