#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\property.exe 

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Build rule for resource file
SOURCE=.\Property.rc

$(OUTDIR)\Property.res: $(SOURCE) $(OUTDIR) resource.h property.h
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\Property.res $(SOURCE)

# Update the object file if necessary

SOURCE=.\property.c

$(OUTDIR)\property.obj : $(SOURCE) $(OUTDIR) resource.h property.h
    $(cc) $(cdebug) $(cflags) $(cvars) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

# Update the executable if necessary

Property.Exe: Property.Obj Property.Res
    $(link) $(linkdebug) $(guiflags) -out:Property.Exe Property.Obj Property.Res $(guilibs) ComCtl32.Lib

# Build rule for EXE
$(OUTDIR)\Property.exe:  $(OUTDIR) $(OUTDIR)\property.obj $(OUTDIR)\Property.res
	$(link) $(ldebug) $(guiflags) /PDB:$(OUTDIR)\Property.pdb -out:$(OUTDIR)\Property.exe $(OUTDIR)\property.obj $(OUTDIR)\Property.res $(guilibs) comctl32.lib

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)

