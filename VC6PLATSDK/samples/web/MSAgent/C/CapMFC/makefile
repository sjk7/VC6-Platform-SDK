!include <win32.mak>
proj=Cap

all: $(OUTDIR) $(OUTDIR)\$(proj).exe

LINK32_OBJS= \
        $(OUTDIR)\acanim.obj \
        $(OUTDIR)\acaudio.obj   \
        $(OUTDIR)\acball.obj \
        $(OUTDIR)\acchar.obj \
        $(OUTDIR)\acchars.obj \
        $(OUTDIR)\accomm.obj \
        $(OUTDIR)\accomms.obj \
        $(OUTDIR)\acex.obj \
        $(OUTDIR)\acprop.obj \
        $(OUTDIR)\acreq.obj \
        $(OUTDIR)\acuser.obj \
        $(OUTDIR)\capmfc.obj \
        $(OUTDIR)\maindlg.obj \
        $(OUTDIR)\stdafx.obj  \
        $(OUTDIR)\capMFC.res

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) -GX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS $**

$(OUTDIR)\$(proj).exe:  $(LINK32_OBJS)
    $(link) $(ldebug) $(guilflags) /PDB:$(OUTDIR)\$(proj).pdb -out:$(OUTDIR)\$(proj).exe $(LINK32_OBJS) $(olelibs) version.lib shell32.lib


$(OUTDIR)\capMFC.res: $(OUTDIR)
    $(rc) $(rcflags) $(rcvars) /d_AFXDLL /fo $(OUTDIR)\capMFC.res capMFC.rc

clean:
        $(CLEANUP)

