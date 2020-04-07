#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = VCExplore
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

LINK32_OBJS = $(OUTDIR)\stdafx.obj \
              $(OUTDIR)\vcexploredlg.obj \
              $(OUTDIR)\vcexplore.obj \
              $(OUTDIR)\utilitiesdlg.obj \
              $(OUTDIR)\connectdlg.obj \
              $(OUTDIR)\compinstalldlg.obj \
              $(OUTDIR)\compimportdlg.obj \
              $(OUTDIR)\apputildlg.obj \
              $(OUTDIR)\appinstalldlg.obj \
              $(OUTDIR)\appexportdlg.obj \
              $(OUTDIR)\vcexplore.res

$(OUTDIR)\stdafx.obj:     stdafx.cpp
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /Gm /GX /D_MBCS /D_AFXDLL /Yc"stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" stdafx.cpp

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /Gm /GX /D_MBCS /D_AFXDLL /Yu"stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\vcexplore.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\vcexplore.res vcexplore.rc

$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
     $(link) $(ldebug) $(guilflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) 

clean:
     $(CLEANUP)
