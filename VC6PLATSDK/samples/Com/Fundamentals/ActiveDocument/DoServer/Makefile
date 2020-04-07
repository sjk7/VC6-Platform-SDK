#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = DOServer
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = odbccp32.lib odbc32.lib shell32.lib advapi32.lib

LINK32_OBJS = $(OUTDIR)\utils.obj \
              $(OUTDIR)\perstor.obj \
              $(OUTDIR)\perfile.obj \
              $(OUTDIR)\oleobj.obj \
              $(OUTDIR)\oledocvw.obj \
              $(OUTDIR)\oledoc.obj \
              $(OUTDIR)\oipobj.obj \
              $(OUTDIR)\oipaobj.obj \
              $(OUTDIR)\doserver.obj \
              $(OUTDIR)\dataobj.obj \
              $(OUTDIR)\clsfact.obj \
              $(OUTDIR)\doserver.res

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvars) /Gm /Fr /GX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\doserver.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\doserver.res doserver.rc

$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
     $(link) $(ldebug) $(guilflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS) $(olelibs) 

clean:
     $(CLEANUP)
