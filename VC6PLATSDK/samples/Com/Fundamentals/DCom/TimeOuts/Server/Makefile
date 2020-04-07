!if "$(CPU)" == "IA64"
!message Sorry building this sample for 64bit is not currently supported.
!else

# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 1993 - 1999 Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile
APPVER = 5.0

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

PROJ = Server

all: $(PROJ).exe $(PROJ)ps.dll

CUSTOM_FLAGS = /D_WIN32_DCOM /I..\PingResp
MIDL_FLAGS = /win32 /Oicf
RC_FLAGS=/l 0x409
MSVCRT = msvcrt.lib

!ifndef NODEBUG
CUSTOM_FLAGS = $(CUSTOM_FLAGS) /D_DEBUG /DDEBUG /D_DEBUGTRACE
RC_FLAGS  = $(RC_FLAGS) /d _DEBUG
MSVCRT = msvcrtd.lib
!endif

.cpp.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.cxx.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.c.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

# Define project specific macros
PROJ_OBJS  = Server.obj MonitorServer.obj Server.res
# use default inference rule for compiling cpp file

EXTRA_LIBS = $(EXTRA_LIBS) $(MSVCRT) uuid.lib ole32.lib oleaut32.lib rpcrt4.lib advapi32.lib kernel32.lib user32.lib gdi32.lib

Server.obj : Server.cpp Server.h Server_i.c ..\PingResp\PingResp.h

MonitorServer.obj : MonitorServer.cpp MonitorServer.h ..\PingResp\PingResp.h

Server.h Server_i.c Server_p.c dlldata.c : Server.idl 
	midl.exe $(MIDL_FLAGS) /o NUL /h Server.h /iid Server_i.c /proxy Server_p.c Server.idl

Server.res : Server.rc
	rc.exe $(RC_FLAGS) /fo Server.res Server.rc

# Build rule for EXE
$(PROJ).exe: $(PROJ_OBJS) $(GLOBAL_OBJS)
    $(link) $(linkdebug) $(guilflags) \
    $(PROJ_OBJS) $(EXTRA_LIBS) \
    -out:$(PROJ).exe $(MAPFILE)

# Files for the Proxy/Stub DLL
dlldata.obj : dlldata.c
    $(CC) /c /Ox /DWIN32 /MD /D_DLL /D_WIN32_WINNT=0x500 /DREGISTER_PROXY_DLL /I..\PingResp /c dlldata.c

$(PROJ)_p.obj : $(PROJ)_p.c
    $(CC) /c /Ox /DWIN32 /MD /D_DLL /D_WIN32_WINNT=0x500 /DREGISTER_PROXY_DLL /I..\PingResp /c $(PROJ)_p.c
	
$(PROJ)_i.obj : $(PROJ)_i.c
    $(CC) /c /Ox /DWIN32 /MD /D_DLL /D_WIN32_WINNT=0x500 /DREGISTER_PROXY_DLL /I..\PingResp /c $(PROJ)_i.c

# Build rule for DLL
$(PROJ)ps.dll: dlldata.obj $(PROJ)_p.obj $(PROJ)_i.obj
	link /dll /out:$(PROJ)ps.dll /def:$(PROJ)ps.def /entry:DllMain dlldata.obj $(PROJ)_p.obj $(PROJ)_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib msvcrt.lib


# Rules for cleaning out generated files
clean:
    del *.obj *.dll *.exe *.exp *.lib *.res
    del Server.h Server.tlb Server_i.c Server_p.c dlldata.c


!endif
