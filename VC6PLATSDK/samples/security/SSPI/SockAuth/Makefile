# Copyright (c) Microsoft Corporation. All rights reserved.

!include <win32.mak>

CPP          = $(cc)
CPPFLAGS     = $(cflags) $(cvars) $(cdebug)
LINKFLAGS    = $(linkdebug) $(conflags) /subsystem:console 

            
all: server.exe client.exe


                     
# ----------------------------------------------------------------------------
#                      L I N K / R E S   C O M M A N D S
# ----------------------------------------------------------------------------

server.exe: server.obj comm.obj security.obj collect.obj
    @echo Linking ...
     $(link) $(LINKFLAGS) $** $(conlibs) wsock32.lib secur32.lib -out:$@

client.exe: client.obj comm.obj security.obj collect.obj
    @echo Linking ...
     $(link) $(LINKFLAGS) $** $(conlibs) secur32.lib -out:$@


# ----------------------------------------------------------------------------
#                           B U I L D   R U L E S
# ----------------------------------------------------------------------------

.c.obj:
    @echo Compiling $<...
    $(CPP) $(CPPFLAGS) /c -I..\include $<


# ----------------------------------------------------------------------------
#                       D E P E N D E N C Y   R U L E S
# ----------------------------------------------------------------------------

comm.obj : comm.cpp comm.h

security.obj : security.cpp security.h collect.h

server.obj : server.cpp security.h comm.h

client.obj : client.cpp security.h comm.h

collect.obj : collect.cpp collect.h
