#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!if "$(CPU)" == "IA64"
!message Sorry, building this sample for the 64bit Windows Platform is not currently supported
!else
!include <win32.mak>

PROJ = nmui
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = comctl32.lib odbccp32.lib odbc32.lib shell32.lib advapi32.lib

LINK32_OBJS = $(OUTDIR)\util.obj \
              $(OUTDIR)\sbar.obj \
              $(OUTDIR)\rtns.obj \
              $(OUTDIR)\msg.obj \
              $(OUTDIR)\main.obj \
              $(OUTDIR)\init.obj \
              $(OUTDIR)\imsconf2_i.obj \
              $(OUTDIR)\dlg.obj \
              $(OUTDIR)\debug.obj \
              $(OUTDIR)\cshare.obj \
              $(OUTDIR)\cmgr.obj \
              $(OUTDIR)\cmemb.obj \
              $(OUTDIR)\cmd.obj \
              $(OUTDIR)\clutil.obj \
              $(OUTDIR)\cft.obj \
              $(OUTDIR)\cdata.obj \
              $(OUTDIR)\cconf.obj \
              $(OUTDIR)\cchan.obj \
              $(OUTDIR)\ccall.obj \
              $(OUTDIR)\res.res

$(OUTDIR)\imsconf2.h : imsconf2.idl
     $(midl) /h $(OUTDIR)\imsconf2.h /tlb $(OUTDIR)\imsconf2.tlb /iid $(OUTDIR)\imsconf2_i.c imsconf2.idl

.c{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /Gm /GX /DINIT_OFFICE /DSTRICT /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) $**

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /Gm /GX /DINIT_OFFICE /DSTRICT /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) $**

$(OUTDIR)\imsconf2_i.obj: $(OUTDIR)\imsconf2_i.c
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /Gm /GX /DINIT_OFFICE /DSTRICT /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) $(OUTDIR)\imsconf2_i.c

$(OUTDIR)\res.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\res.res /I$(OUTDIR) res.rc

$(OUTDIR)\$(PROJ).exe:   $(OUTDIR)\imsconf2.h $(LINK32_OBJS)
     $(link) $(ldebug) $(guilflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS) $(olelibs) $(baselibs) 

clean:
     $(CLEANUP)

!endif
