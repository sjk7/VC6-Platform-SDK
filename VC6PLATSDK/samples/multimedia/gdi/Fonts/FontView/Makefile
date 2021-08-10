PROJ = FONTVIEW
SRC = FONTVIEW.C TOOLS.C STATUS.C DIALOGS.C DISPLAY.C

#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\FONTVIEW.exe 

LINK32_OBJS= \
	$(OUTDIR)\FONTVIEW.obj \
	$(OUTDIR)\TOOLS.obj \
	$(OUTDIR)\STATUS.obj \
	$(OUTDIR)\DIALOGS.obj \
	$(OUTDIR)\DISPLAY.obj
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)
    
# Generic rule for building ALL C files and placing their OBJ's in the OUTDIR
.c{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Build rule for resource file
SOURCE=.\FONTVIEW.rc

$(OUTDIR)\FONTVIEW.res: $(SOURCE) $(OUTDIR)
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\FONTVIEW.res $(SOURCE)

# Update the help file if necessary
$(OUTDIR)\FONTVIEW.hlp : FONTVIEW.rtf FONTVIEW.hpj
    $(hc) -o .\$(OUTDIR)\FONTVIEW.hlp $(hcvars) FONTVIEW.hpj

# Build rule for EXE
$(OUTDIR)\FONTVIEW.exe:  $(OUTDIR) $(LINK32_OBJS) $(OUTDIR)\FONTVIEW.res $(OUTDIR)\FONTVIEW.hlp
    $(link) $(ldebug) $(guiflags) /PDB:$(OUTDIR)\FONTVIEW.pdb -out:$(OUTDIR)\FONTVIEW.exe $(LINK32_OBJS) $(OUTDIR)\FONTVIEW.res $(guilibs)

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)

