#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

!ifdef NODEBUG
NMFTCVARS=$(cvars)
NMFTLFLAGS=$(conlflags)
!else
NMFTCVARS=$(cvarsdll)
NMFTLFLAGS=$(guilflags)
!endif

PROJ = nmFt
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = comctl32.lib odbccp32.lib odbc32.lib shell32.lib advapi32.lib

LINK32_OBJS = $(OUTDIR)\util.obj \
              $(OUTDIR)\msg.obj \
              $(OUTDIR)\main.obj \
              $(OUTDIR)\imsconf2_i.obj \
              $(OUTDIR)\debug.obj \
              $(OUTDIR)\clutil.obj \
              $(OUTDIR)\cconf.obj \
              $(OUTDIR)\res.res

$(OUTDIR)\imsconf2.h : imsconf2.idl
     $(midl) /h $(OUTDIR)\imsconf2.h /tlb $(OUTDIR)\imsconf2.tlb /iid $(OUTDIR)\imsconf2_i.c imsconf2.idl

.c{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(NMFTCVARS) /Ob2 /GX /DSTRICT /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) $**

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(NMFTCVARS) /Ob2 /GX /DSTRICT /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) $**

$(OUTDIR)\imsconf2_i.obj: $(OUTDIR)\imsconf2_i.c
     $(cc) $(cflags) $(cdebug) $(cvars) /Ob2 /GX /DSTRICT /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) $(OUTDIR)\imsconf2_i.c

$(OUTDIR)\res.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\res.res /I$(OUTDIR) res.rc

$(OUTDIR)\$(PROJ).exe:   $(OUTDIR)\imsconf2.h $(LINK32_OBJS)
     $(link) $(ldebug) $(NMFTLFLAGS) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS) $(olelibs) $(baselibs) 

clean:
     $(CLEANUP)
