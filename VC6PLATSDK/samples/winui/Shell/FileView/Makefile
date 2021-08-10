#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\fvtext.dll 

LINK32_OBJS= \
	$(OUTDIR)\CSTATHLP.obj \
    $(OUTDIR)\CSTRTABL.obj \
    $(OUTDIR)\FILEVIEW.obj \
    $(OUTDIR)\FVINIT.obj   \
    $(OUTDIR)\FVPROC.obj   \
    $(OUTDIR)\FVTEXT.obj   \
    $(OUTDIR)\IFILEVW.obj  \
    $(OUTDIR)\IPERFILE.obj 
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Build rule for DLL
$(OUTDIR)\fvtext.dll: $(OUTDIR) $(LINK32_OBJS) $(OUTDIR)\fvtext.res
	$(implib) -machine:$(CPU) -def:fvtext.def $(LINK32_OBJS) -out:$(OUTDIR)\fvtext.lib
    $(link) $(ldebug) $(dllllflags) \
    $(LINK32_OBJS) $(OUTDIR)\fvtext.res $(dlllibs) $(olelibsdll) $(guilibs) shell32.lib $(OUTDIR)\fvtext.lib comctl32.lib $(OUTDIR)\fvtext.exp \
    -base:0x1C000000 \
    -out:$(OUTDIR)\fvtext.dll 
#    -def:fvtext.def

  
#  $(link) $(linkdebug) $(dlllflags) -base:0x1C000000 -out:$*.dll $** $(olelibsdll) shell32.lib fvtext.lib comctl32.lib fvtext.exp

# Generic rule for building ALL CPP files and placing their OBJ's in the OUTDIR
.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Build rule for resource file
SOURCE=.\fvtext.rc

$(OUTDIR)\fvtext.res: $(SOURCE) $(OUTDIR)
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\fvtext.res $(SOURCE)

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
