#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\traynot.exe
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Build rule for resource file
SOURCE=.\app32.rc

$(OUTDIR)\app32.res: $(SOURCE) $(OUTDIR) app32.h resource.h
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\app32.res $(SOURCE)

# Update the object file if necessary

SOURCE=.\app32.c

$(OUTDIR)\app32.obj : $(SOURCE) $(OUTDIR) app32.h
    $(cc) $(cdebug) $(cflags) $(cvars) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

# Update the executable file if necessary, and if so, add the resource back in.

# Build rule for EXE
$(OUTDIR)\traynot.exe: $(OUTDIR) $(OUTDIR)\app32.obj $(OUTDIR)\app32.res
    $(link) $(ldebug) $(guiflags) /PDB:$(OUTDIR)\traynot.pdb -out:$(OUTDIR)\traynot.exe $(OUTDIR)\app32.obj $(OUTDIR)\app32.res $(guilibs) shell32.lib


#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
        
