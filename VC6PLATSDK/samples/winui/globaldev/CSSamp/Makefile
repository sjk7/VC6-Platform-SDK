# Makefile for CSSAMP 
#
# Nmake macros for building Win32 & Win64 apps
!include <Win32.Mak>

LINK_OBJS=\
	$(OUTDIR)\cssamp.obj\
	$(OUTDIR)\dspformt.obj\
	$(OUTDIR)\dsplogcl.obj\
	$(OUTDIR)\dspplain.obj\
	$(OUTDIR)\settings.obj\
	$(OUTDIR)\text.obj\
	$(OUTDIR)\style.obj\
	$(OUTDIR)\textwnd.obj\
	$(OUTDIR)\edit.obj\
	$(OUTDIR)\debug.obj\
	$(OUTDIR)\cssamp.res

all: $(OUTDIR) $(OUTDIR)\cssamp.exe 

$(OUTDIR) :
	if not exist "$(OUTDIR)" mkdir "$(OUTDIR)"

# Compile the resource files if necessary
$(OUTDIR)\cssamp.res: cssamp.rc resource.h initial.txt
    $(rc) $(rcflags) $(rcvars) /fo"$(OUTDIR)\cssamp.res" cssamp.rc 


#Generic compiler command line
.cpp{$(OUTDIR)}.obj::
   $(cc) @<<
   $(cflags) /Fo"$(OUTDIR)\\" $(cvars) $(cdebug)  $< 
<<

# Update modules if necessary

#main exe
$(OUTDIR)\cssamp.exe: $(LINK_OBJS) 
    $(link) $(linkdebug) $(guiflags) -out:"$(OUTDIR)\cssamp.exe" $(guilibs) USP10.LIB shlwapi.lib $(LINK_OBJS)

CLEAN :
        $(CLEANUP)
