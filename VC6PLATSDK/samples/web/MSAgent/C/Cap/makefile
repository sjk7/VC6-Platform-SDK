!include <win32.mak>
proj=Cap

all: $(OUTDIR) $(OUTDIR)\$(proj).exe

LINK32_OBJS= \
        $(OUTDIR)\about.obj \
        $(OUTDIR)\cap.obj   \
        $(OUTDIR)\error.obj \
        $(OUTDIR)\maindlg.obj \
        $(OUTDIR)\notify.obj \
        $(OUTDIR)\stdafx.obj  \
        $(OUTDIR)\cap.res

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\$(proj).exe:  $(LINK32_OBJS)
    $(link) $(ldebug) $(guilflags) /PDB:$(OUTDIR)\$(proj).pdb -out:$(OUTDIR)\$(proj).exe $(LINK32_OBJS) $(olelibs) version.lib shell32.lib


$(OUTDIR)\cap.res: $(OUTDIR)
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\cap.res cap.rc

clean:
        $(CLEANUP)

