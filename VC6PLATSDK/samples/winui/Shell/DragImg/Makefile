# These are "extra" libs

libs = shell32.lib comctl32.lib urlmon.lib

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

_WIN32_IE = 0x0500

#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\DragImg.exe 

LINK32_OBJS= \
	$(OUTDIR)\DataObj.obj \
	$(OUTDIR)\DragSrc.obj \
	$(OUTDIR)\DropTgt.obj \
	$(OUTDIR)\EnumFE.obj \
	$(OUTDIR)\Render.obj \
	$(OUTDIR)\DragImg.obj \
	$(OUTDIR)\DragImg.res
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Build rule for resource file
SOURCE=.\DragImg.rc

$(OUTDIR)\DragImg.res: $(SOURCE) $(OUTDIR) resource.h mainicon.ico DragImg.bmp
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\DragImg.res $(SOURCE)

# Generic rule for building ALL CPP files and placing their OBJ's in the OUTDIR
.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Build rule for EXE
$(OUTDIR)\DragImg.exe:  $(OUTDIR) $(LINK32_OBJS) 
    $(link) $(ldebug) $(guiflags) /PDB:$(OUTDIR)\DragImg.pdb -out:$(OUTDIR)\DragImg.exe $(LINK32_OBJS) $(libs) $(olelibs)

# Rules for cleaning out those old files
clean:
        $(CLEANUP)
