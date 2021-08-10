#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\vlistvw.exe
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Build rule for resource file
SOURCE=.\VListVw.rc

$(OUTDIR)\VListVw.res: $(SOURCE) $(OUTDIR) resource.h VListVw.h
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\VListVw.res $(SOURCE)
    
SOURCE=.\VListVw.c

$(OUTDIR)\VListVw.obj : $(SOURCE) $(OUTDIR) VListVw.h resource.h
    $(cc) $(cdebug) $(cflags) $(cvars) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

# Build rule for EXE
$(OUTDIR)\VListVw.exe:  $(OUTDIR) $(OUTDIR)\VListVw.obj $(OUTDIR)\VListVw.res
    $(link) $(ldebug) $(guiflags) /PDB:$(OUTDIR)\VListVw.pdb -out:$(OUTDIR)\VListVw.exe $(OUTDIR)\VListVw.obj $(OUTDIR)\VListVw.res $(guilibs) ComCtl32.lib

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
