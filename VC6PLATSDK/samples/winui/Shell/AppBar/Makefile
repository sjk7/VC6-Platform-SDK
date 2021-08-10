# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993 - 1995  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\appbar.exe 

LINK32_OBJS= \
	$(OUTDIR)\main.obj \
	$(OUTDIR)\wndproc.obj \
	$(OUTDIR)\appbar.obj \
	$(OUTDIR)\propsht.obj \
	$(OUTDIR)\util.obj
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)
    
# Generic rule for building ALL CPP files and placing their OBJ's in the OUTDIR
.c{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Build rule for resource file
SOURCE=.\appbar.rc

$(OUTDIR)\appbar.res: $(SOURCE) $(OUTDIR) resource.h appbar.ico appbar.bmp base.bmp window.bmp
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\appbar.res $(SOURCE)

# Build rule for EXE
$(PROJ).EXE: $(PROJ_OBJS) $(PROJ).res
    $(link) $(linkdebug) $(guilflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res $(guilibs) $(EXTRA_LIBS) \
    -out:$(PROJ).exe $(MAPFILE)

# Build rule for EXE
$(OUTDIR)\appbar.exe:  $(OUTDIR) $(LINK32_OBJS) $(OUTDIR)\appbar.res
    $(link) $(ldebug) $(guiflags) /PDB:$(OUTDIR)\appbar.pdb -out:$(OUTDIR)\appbar.exe $(LINK32_OBJS) $(OUTDIR)\appbar.res $(guilibs) version.lib comctl32.lib shell32.lib


#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
