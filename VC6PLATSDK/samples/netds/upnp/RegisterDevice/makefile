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

!if (("$(CPU)" != "IA64") && ("$(TARGETOS)" == "WINNT") && ("$(APPVER)" != "4.0")) || (("$(TARGETOS)" == "WIN95") && ("$(APPVER)" != "5.0"))

PROJ = RegDevice

all: $(OUTDIR) $(PROJ).exe 

# Define project specific macros
PROJ_OBJS  = $(OUTDIR)\RegDevice.obj 


CFLG=$(cflags)


link=$(link)

# If $(OUTDIR) does not exist, then create
$(OUTDIR) :
  if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR) 

# Inference rule for updating the object files
.cpp{$(OUTDIR)}.obj:
   $(cc) $(cflags) $(cdebug) /D_MT /D_DLL /MD /D_AFXDLL /D_MBCS /DUNICODE /D_UNICODE /I"..\DCO_DimmerService" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Build rule for EXE
$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS)
    $(link) $(linkdebug) $(guilflags) \
    $(PROJ_OBJS) $(conflags)  $(EXTRA_LIBS) \
    -out:$(OUTDIR)\$(PROJ).exe $(MAPFILE) /NODEFAULTLIB:libcd.lib /NODEFAULTLIB:libc.lib 
    copy *.xml $(OUTDIR)\

# Rules for cleaning out those old files
clean:
    $(CLEANUP)
!else
!message This sample only supports 32 bit WinXP and above.
!endif