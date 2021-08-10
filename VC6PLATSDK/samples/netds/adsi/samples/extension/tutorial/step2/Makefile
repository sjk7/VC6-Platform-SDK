#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>


ALL : $(OUTDIR) $(OUTDIR)\ADsFirstExt.h $(OUTDIR)\ADsFirstExt_i.c $(OUTDIR)\ADsFirstExt.dll 

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)


# Define project specific macros

PROJ_OBJS  =	$(OUTDIR)\ADsFirstExt.obj \
				$(OUTDIR)\HelloWorld.obj \
				$(OUTDIR)\StdAfx.obj

EXTRA_LIBS = activeds.lib adsiid.lib 

DEFFILE = .\ADsFirstExt.def


$(OUTDIR)\ADsFirstExt.h $(OUTDIR)\ADsFirstExt_i.c : ADsFirstExt.idl
	midl.exe /h $(OUTDIR)\ADsFirstExt.h /iid $(OUTDIR)\ADsFirstExt_i.c ADsFirstExt.idl

# Inference rule for updating the object files
.cpp{$(OUTDIR)}.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsdll) /GX /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /I$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Build rule for resource file
$(OUTDIR)\ADsFirstExt.res: ADsFirstExt.rc 
    $(rc) $(rcflags) $(rcvarsdll) /fo $(OUTDIR)\ADsFirstExt.res ADsFirstExt.rc

# Build rule for DLL
$(OUTDIR)\ADsFirstExt.dll: $(PROJ_OBJS) $(OUTDIR)\ADsFirstExt.res
    $(link) $(dlllflags) $(linkdebug) /DEF:$(DEFFILE) /implib:"$(OUTDIR)\ADsFirstExt.lib" /pdb:"$(OUTDIR)\ADsFirstExt.pdb" $(guilflags) \
    $(PROJ_OBJS) $(OUTDIR)\ADsFirstExt.res $(EXTRA_LIBS) \
    -out:$(OUTDIR)\ADsFirstExt.dll
    

CLEAN :
	$(CLEANUP)
