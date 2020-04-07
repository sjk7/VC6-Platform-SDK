!if "$(TARGETOS)" == "WIN95"
!message Sorry this sample builds only for the Windows NT, 2000 and XP platforms
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

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

PROJ = PingResp

all: $(PROJ).dll

CUSTOM_FLAGS = /D_DLL /D_USRDLL /D_WIN32_DCOM /D_MERGE_PROXYSTUB
MIDL_FLAGS = /Oicf
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
PROJ_OBJS  = PingResp.obj dlldatax.obj PingResp.res
# use default inference rule for compiling cpp file

EXTRA_LIBS = $(EXTRA_LIBS) $(MSVCRT) uuid.lib ole32.lib oleaut32.lib rpcrt4.lib advapi32.lib kernel32.lib user32.lib gdi32.lib

PingResp.obj : PingResp.cpp PingResp.h PingResp_i.c

PingResp.h PingResp_i.c PingResp.tlb : PingResp.idl
	midl.exe $(MIDL_FLAGS) /h PingResp.h /iid PingResp_i.c /tlb PingResp.tlb PingResp.idl

PingResp.res : PingResp.rc
	rc.exe $(RC_FLAGS) /fo PingResp.res PingResp.rc
	
# Build rule for DLL
$(PROJ).dll: $(PROJ_OBJS) $(GLOBAL_OBJS)
    $(link) $(linkdebug) $(dlllflags) -DLL -DEF:pingresp.def\
    $(PROJ_OBJS) $(EXTRA_LIBS) \
    -out:$(PROJ).dll $(MAPFILE)


# Rules for cleaning out those old files
clean:
    del *.obj *.dll *.exp *.lib *.res
    del PingResp.h PingResp.tlb PingResp_i.c dlldata.c



!endif
