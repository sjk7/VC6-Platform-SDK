#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\Cleanup.dll

LINK32_OBJS= \
	$(OUTDIR)\ClassFactory.obj \
	$(OUTDIR)\EmptyVolumeCache.obj \
	$(OUTDIR)\RegisterServer.obj \
	$(OUTDIR)\UnregisterServer.obj \
	$(OUTDIR)\Dacl.obj \
	$(OUTDIR)\Cleanup.obj
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)
    
# Build rule for resource file
SOURCE=.\cleanup.rc

$(OUTDIR)\cleanup.res: $(SOURCE) $(OUTDIR)
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\cleanup.res $(SOURCE)
    
# Generic rule for building ALL CPP files and placing their OBJ's in the OUTDIR
.cpp{$(OUTDIR)}.obj: 
    $(cc) $(cdebug) $(cflags) $(cvarsdll) -DWIN32_LEAN_AND_MEAN /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**
    
# Build rule for DLL
$(OUTDIR)\Cleanup.dll: $(OUTDIR) $(LINK32_OBJS) $(OUTDIR)\Cleanup.res
    $(link) $(ldebug) $(dllllflags) \
    $(LINK32_OBJS) $(OUTDIR)\Cleanup.res $(dlllibs) $(olelibsmt) shell32.lib shlwapi.lib \
    -out:$(OUTDIR)\Cleanup.dll \
    -def:Cleanup.def

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
