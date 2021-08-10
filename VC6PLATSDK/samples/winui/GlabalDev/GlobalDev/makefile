#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

DIRS = \
    GRES409\~   \

PROJ = Global
all:    $(DIRS) $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(DIRS):
!include <sdkbld.mak>

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = comctl32.lib odbccp32.lib odbc32.lib shell32.lib advapi32.lib

LINK32_OBJS = $(OUTDIR)\textapi.obj \
              $(OUTDIR)\nlsapi.obj \
              $(OUTDIR)\global.obj \
              $(OUTDIR)\gentab.obj \
              $(OUTDIR)\global.res

.c{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /GX /D_UNICODE /DUNICODE /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\global.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\global.res global.rc

$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
     $(link) $(ldebug) $(guilflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

clean:
     $(CLEANUP)
