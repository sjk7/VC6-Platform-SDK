TARGETOS=BOTH
#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\dt_dll.dll 

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) : 
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Build rule for DLL
$(OUTDIR)\dt_dll.dll: $(OUTDIR) $(OUTDIR)\dt_dll.obj $(OUTDIR)\dthandler.obj $(OUTDIR)\socketmon.obj
	$(link) $(ldebug) $(dlllflags) \
    $(dlllibs) $(guilibsdll) \
    -export:WSAPreApiNotify -export:WSAPostApiNotify \
    -out:$(OUTDIR)\dt_dll.dll \
    $(OUTDIR)\dt_dll.obj $(OUTDIR)\dthandler.obj $(OUTDIR)\socketmon.obj
    	
# Generic rule for building ALL CPP files and placing their OBJ's in the OUTDIR
.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) -DSTRICT $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
