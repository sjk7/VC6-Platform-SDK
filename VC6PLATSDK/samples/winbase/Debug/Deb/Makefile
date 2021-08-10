# -------------------------------------------------------------------------
#
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993-1999.  Microsoft Corporation.  All rights reserved.
#
#
# -------------------------------------------------------------------------
# MODULE  : MakeFile
# PURPOSE : Nmake macros for building the Windows 32-Bit Debug Event
#           Browser Application
# -------------------------------------------------------------------------

#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\deb.exe $(OUTDIR)\linklist.dll $(OUTDIR)\toolbar.dll $(OUTDIR)\deb.hlp
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

LINK32_OBJS= \
	$(OUTDIR)\DEBMain.obj \
	$(OUTDIR)\DEBDebug.obj \
	$(OUTDIR)\DEBMisc.obj 

# Generic rule for building ALL CPP files and placing their OBJ's in the OUTDIR
.c{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Build rule for resource file
SOURCE=.\deb.rc

$(OUTDIR)\deb.res: $(SOURCE) $(OUTDIR) deb.dlg
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\deb.res $(SOURCE)

# Build rule for DLL
$(OUTDIR)\linklist.dll: $(OUTDIR) $(OUTDIR)\linklist.obj linklist.h 
	$(link) $(ldebug) $(dlllflags) \
    $(OUTDIR)\linklist.obj $(dlllibs) $(guilibsmt) \
    -out:$(OUTDIR)\linklist.dll \
    -def:linklist.def

# Build rule for DLL
$(OUTDIR)\toolbar.dll: $(OUTDIR) $(OUTDIR)\toolbar.obj toolbar.h 
	$(link) $(ldebug) $(dlllflags) \
    $(OUTDIR)\toolbar.obj $(dlllibs) $(guilibsmt) \
    -out:$(OUTDIR)\toolbar.dll \
    -def:toolbar.def
    
# Build rule for EXE
$(OUTDIR)\deb.exe:  $(OUTDIR) $(OUTDIR)\linklist.dll $(OUTDIR)\toolbar.dll $(LINK32_OBJS) $(OUTDIR)\deb.res
    $(link) $(ldebug) $(guilflags) /PDB:$(OUTDIR)\deb.pdb -out:$(OUTDIR)\deb.exe $(LINK32_OBJS) $(OUTDIR)\deb.res $(OUTDIR)\linklist.lib $(OUTDIR)\toolbar.lib $(guilibsmt)

# Update the help file if necessary
$(OUTDIR)\deb.hlp : deb.rtf deb.hpj
    $(hc) -o .\$(OUTDIR)\deb.hlp $(hcvars) deb.hpj 

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
