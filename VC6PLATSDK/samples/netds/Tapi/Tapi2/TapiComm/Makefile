!IF "$(TARGETOS)" == "WIN95"

#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\tapicomm.exe $(OUTDIR)\tapicomm.hlp

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)
    
LINK32_OBJS= \
	$(OUTDIR)\tapicomm.obj \
	$(OUTDIR)\ABOUT.obj    \
    $(OUTDIR)\COMMCODE.obj \
    $(OUTDIR)\DISPATCH.obj \
    $(OUTDIR)\EDITCTLS.obj \
    $(OUTDIR)\INIT.obj     \
    $(OUTDIR)\MISC.obj     \
    $(OUTDIR)\STATBAR.obj  \
    $(OUTDIR)\TAPICODE.obj \
    $(OUTDIR)\TAPIINFO.obj \
    $(OUTDIR)\TOOLBAR.obj  \
    $(OUTDIR)\WINMAIN.obj
	
# Build rule for resource file
SOURCE=.\tapicomm.rc

$(OUTDIR)\tapicomm.res: $(SOURCE) $(OUTDIR)
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\tapicomm.res $(SOURCE)

# Update the help file if necessary
$(OUTDIR)\tapicomm.hlp : tapicomm.rtf tapicomm.hpj
    $(hc) -o .\$(OUTDIR)\tapicomm.hlp $(hcvars) tapicomm.hpj 

# Generic rule for building ALL CPP files and placing their OBJ's in the OUTDIR
.c{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**


# Build rule for EXE
$(OUTDIR)\tapicomm.exe:  $(OUTDIR) $(LINK32_OBJS) $(OUTDIR)\tapicomm.res
    $(link) $(ldebug) $(guiflags) /PDB:$(OUTDIR)\tapicomm.pdb -out:$(OUTDIR)\tapicomm.exe $(LINK32_OBJS) $(OUTDIR)\tapicomm.res $(guilibs) advapi32.lib comctl32.lib tapi32.lib version.lib

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
        
!ELSE
!MESSAGE Sorry this sample only builds for the Windows 9x Platform
!ENDIF
