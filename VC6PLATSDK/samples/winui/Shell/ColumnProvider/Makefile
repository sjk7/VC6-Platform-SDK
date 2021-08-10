# Nmake macros for building Win32 apps

!IF "$(TARGETOS)" == "WINNT"

#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\ShortName.dll

LINK32_OBJS= \
	$(OUTDIR)\ClassFactory.obj \
	$(OUTDIR)\ColumnProvider.obj \
	$(OUTDIR)\Clsid.obj \
	$(OUTDIR)\RegisterServer.obj \
	$(OUTDIR)\UnregisterServer.obj \
	$(OUTDIR)\ShortName.obj
	
      
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Build rule for resource file
SOURCE=.\ShortName.rc

$(OUTDIR)\ShortName.res: $(SOURCE) $(OUTDIR) resource.h ShortName.h
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\ShortName.res $(SOURCE)
    
# Update the object file if necessary

# Generic rule for building ALL CPP files and placing their OBJ's in the OUTDIR
.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) -DWIN32_LEAN_AND_MEAN -DUNICODE -D_UNICODE /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Update the executable if necessary

# Build rule for DLL
$(OUTDIR)\ShortName.dll: $(OUTDIR) $(LINK32_OBJS) $(OUTDIR)\ShortName.res
    $(link) $(ldebug) $(dllllflags) \
    $(LINK32_OBJS) $(OUTDIR)\ShortName.res  $(olelibsmt) shell32.lib shlwapi.lib \
    /BASE:0x66810000 \
    -out:$(OUTDIR)\ShortName.dll \
    -def:ShortName.def

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
        
!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT Platform
!ENDIF
