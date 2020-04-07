# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 1993 - 1998 Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Win32 apps
!include <win32.mak>

PROJ = GENERIC

all: $(OUTDIR) $(OUTDIR)\$(PROJ).exe $(OUTDIR)\$(PROJ).hlp

# Define project specific macros
PROJ_OBJS  = $(OUTDIR)\generic.obj 
BASE_OBJS  =
EXTRA_LIBS = version.lib
GLOBAL_DEP = generic.h resource.h
RC_DEP     = resource.h

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Inference rule for updating the object files
.c{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Build rule for resource file
$(OUTDIR)\$(PROJ).res: $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\$(PROJ).res $(PROJ).rc

# Build rule for EXE
$(OUTDIR)\$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS) $(OUTDIR)\$(PROJ).res
    $(link) $(linkdebug) $(guilflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(OUTDIR)\$(PROJ).res $(guilibs) $(EXTRA_LIBS) \
    -out:$(OUTDIR)\$(PROJ).exe $(MAPFILE)

# Build rule for help file
$(OUTDIR)\$(PROJ).hlp: $(PROJ).rtf $(PROJ).hpj
    $(hc) -o .\$(OUTDIR)\$(PROJ).hlp $(hcvars) $(PROJ).hpj 



# Rules for cleaning out those old files
clean:
        $(CLEANUP)
