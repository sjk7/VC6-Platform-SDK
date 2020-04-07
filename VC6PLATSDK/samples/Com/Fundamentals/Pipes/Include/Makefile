# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 1993 - 1998 Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

PROJ = proxy

all: $(OUTDIR) $(OUTDIR)\$(PROJ).dll

CUSTOM_FLAGS = /D_WIN32_DCOM /D_UNICODE /DUNICODE /DREGISTER_PROXY_DLL


!ifndef NO_DEBUG
CUSTOM_FLAGS = $(CUSTOM_FLAGS) /D_DEBUG /DDEBUG /D_DEBUGTRACE
!endif

.cpp.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.cxx.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.c.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<


# Define project specific macros

$(OUTDIR)\dlldata.c : pipesample.idl
	midl /h ISimpleInterface.h /iid guids.c /proxy proxy.c /char unsigned pipesample.idl  /out $(OUTDIR)

PROXYSTUB_OBJS = $(OUTDIR)\dlldata.obj $(OUTDIR)\proxy.obj $(OUTDIR)\guids.obj

PROXYSTUB_LIBS = kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib uuid.lib
 
# use default inference rule for compiling cpp file

EXTRA_LIBS = $(EXTRA_LIBS) uuid.lib ole32.lib oleaut32.lib

# Build rule for PROXYSTUBDLL
$(OUTDIR)\$(PROJ).dll: $(PROXYSTUB_OBJS) $(GLOBAL_OBJS)
    $(link) $(linkdebug) $(guilflags) -DLL -DEF:proxy.def\
    $(PROXYSTUB_OBJS) $(PROXYSTUB_LIBS) $(EXTRA_LIBS) \
    -out:$(OUTDIR)\$(PROJ).dll $(MAPFILE)


"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

#
# Pipe stuff
#
$(OUTDIR)\proxy.obj: $(OUTDIR)\dlldata.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(OUTDIR)\proxy.c

$(OUTDIR)\guids.obj: $(OUTDIR)\dlldata.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(OUTDIR)\guids.c

$(OUTDIR)\dlldata.obj: $(OUTDIR)\dlldata.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(OUTDIR)\dlldata.c


# Rules for cleaning out those old files

clean:
	del -f $(OUTDIR)\*.obj $(OUTDIR)\*.pdb $(OUTDIR)\*.dll $(OUTDIR)\*.exp $(OUTDIR)\*.lib $(OUTDIR)\*.tlb $(OUTDIR)\dlldata.c
