
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

PROJ = GenericUCP

all: $(OUTDIR) $(PROJ).exe 

# Define project specific macros
PROJ_OBJS  = $(OUTDIR)\GenericUCP.obj \
             $(OUTDIR)\GenericUCPDlg.obj \
             $(OUTDIR)\deviceprop.obj \
             $(OUTDIR)\util.obj \
             $(OUTDIR)\stdafx.obj 


CFLG=$(cflags)


link=$(link)

# If $(OUTDIR) does not exist, then create
$(OUTDIR) :
  if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Inference rule for updating the object files
.cpp{$(OUTDIR)}.obj:
   $(cc) $(cflags) $(cdebug) $(cvarsdll) /D_AFXDLL /D_MBCS  /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Build rule for resource file
$(OUTDIR)\$(PROJ).res: GenericUCP.rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\$(PROJ).res GenericUCP.rc

# Build rule for EXE
$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS) $(OUTDIR)\$(PROJ).res
    $(link) $(linkdebug) $(guilflags) \
    $(PROJ_OBJS) $(OUTDIR)\$(PROJ).res $(guilibs)  $(EXTRA_LIBS) \
    -out:$(PROJ).exe $(MAPFILE) /NODEFAULTLIB:libcd.lib /NODEFAULTLIB:libc.lib



# Rules for cleaning out those old files
clean:
    $(CLEANUP)
!else
!message Sorry this sample is only supported on the WinMe and 32 bit WinXP and above.
!endif