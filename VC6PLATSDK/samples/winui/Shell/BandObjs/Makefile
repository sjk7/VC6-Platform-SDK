# Copyright Microsoft Corporation.  All Rights Reserved.

#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\BandObjs.dll 

LINK32_OBJS= \
	$(OUTDIR)\BandObjs.Obj  \
    $(OUTDIR)\ClsFact.Obj  \
    $(OUTDIR)\CommBand.Obj \
    $(OUTDIR)\DeskBand.Obj \
    $(OUTDIR)\ExplrBar.Obj \
    $(OUTDIR)\ToolBand.Obj
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Generic rule for building ALL CPP files and placing their OBJ's in the OUTDIR
.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**
    
# Build rule for DLL
$(OUTDIR)\BandObjs.dll: $(OUTDIR) $(LINK32_OBJS) 
    $(link) $(ldebug) $(dlllflags) \
    $(LINK32_OBJS)  $(olelibs) \
    -out:$(OUTDIR)\BandObjs.dll \
    -def:BandObjs.def

# Rules for cleaning out those old files
clean:
        $(CLEANUP)

