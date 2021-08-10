# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (c) Microsoft Corporation. All rights reserved.
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

PROJ = htmlprop

all: $(OUTDIR) $(OUTDIR)\$(PROJ).dll

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Define project specific macros

PROJ_OBJS  = $(OUTDIR)\htmlprop.obj
BASE_OBJS  =
EXTRA_LIBS = ntquery.lib 

# Inference rule for updating the object files

.cxx{$(OUTDIR)}.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Update the dynamic link library

$(OUTDIR)\$(PROJ).dll: $(OUTDIR)\$(PROJ).obj $(PROJ).def
    $(link) $(linkdebug) $(dlllflags)     \
    -base:0x1C000000  \
    -out:$(OUTDIR)\$(PROJ).dll   \
    /def:$(PROJ).def $(OUTDIR)\$(PROJ).obj $(conlibsdll) $(EXTRA_LIBS) $(olelibs)

# Rules for cleaning out those old files
clean:
        $(CLEANUP)

