#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\rebar.exe 

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

#--------------------- Compiling C/CPP Files ---------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Compiler options WIN32.MAK provides

SOURCE=.\rebar.c

$(OUTDIR)\rebar.obj : $(SOURCE) $(OUTDIR) resource.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)
    
#--------------------- Compiling Resource Files ------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Resource Compiler options WIN32.MAK provides

# Build rule for resource file
SOURCE=.\rebar.rc

$(OUTDIR)\rebar.res: $(SOURCE) $(OUTDIR) resource.h
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\rebar.res $(SOURCE)

#--------------------- EXE ---------------------------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Linker options WIN32.MAK provides

# Build rule for EXE
$(OUTDIR)\rebar.exe:  $(OUTDIR) $(OUTDIR)\rebar.obj $(OUTDIR)\rebar.res
    $(link) $(ldebug) $(guiflags) /PDB:$(OUTDIR)\rebar.pdb -out:$(OUTDIR)\rebar.exe $(OUTDIR)\rebar.obj $(OUTDIR)\rebar.res $(guilibs) ComCtl32.lib

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)

