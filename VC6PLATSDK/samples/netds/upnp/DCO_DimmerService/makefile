# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1997-1999  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

!if (("$(CPU)" != "IA64") && ("$(TARGETOS)" == "WINNT") && ("$(APPVER)" != "4.0")) 


PROJ = UPNPSampleDimmerDevice

all: $(OUTDIR) $(PROJ).dll

MIDL_FLAGS = /win32 /Oicf 
RC_FLAGS=/l 0x409 /d _DEBUG

# If $(OUTDIR) does not exist, then create
$(OUTDIR) :
   if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)


# These files are created by running the MIDL tool on the .IDL file
MIDL_OBJS = dimmerdevice.h dimmerdevice_i.c dimmerdevice.tlb

$(MIDL_OBJS) : dimmerdevice.idl
   midl.exe $(MIDL_FLAGS) /h dimmerdevice.h /iid dimmerdevice_i.c dimmerdevice.idl

$(OUTDIR)\$(PROJ).res : $(MIDL_OBJS) $(PROJ).rc
	rc.exe $(RC_FLAGS) /fo $(OUTDIR)\$(PROJ).res $(PROJ).rc


.cpp{$(OUTDIR)}.obj:
   $(cc) $(cflags) $(cdebug) /D_MT /D_DLL /MD /DWIN32 /D_WIN32 /DUNICODE /D_UNICODE /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**


# Define project specific macros
PROJ_OBJS  = $(OUTDIR)\$(PROJ).res $(OUTDIR)\devicedll.obj $(OUTDIR)\dimmerdevicedco.obj  $(OUTDIR)\dimmerservice.obj


EXTRA_LIBS = advapi32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib kernel32.lib user32.lib gdi32.lib



# Build rule for DLL
$(PROJ).dll: $(PROJ_OBJS)
	$(link) $(linkdebug)  /dll -out:$(OUTDIR)\$(PROJ).dll /def:DeviceDll.def /entry:_DllMainCRTStartup@12 $(PROJ_OBJS) $(conflags) $(EXTRA_LIBS)
	regsvr32 /s $(OUTDIR)\$(PROJ).dll

# Rules for cleaning out generated files
clean:
    $(CLEANUP)


!else
!message Sorry this sample is only supported on the 32 bit WinXP and above.
!endif