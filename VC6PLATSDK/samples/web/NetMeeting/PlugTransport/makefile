!include <win32.mak>
proj=PlugTransport

all: $(OUTDIR) $(OUTDIR)\$(proj).exe

LINK32_OBJS= \
        $(OUTDIR)\PlugTransport.obj \
        $(OUTDIR)\nmsession.obj \
        $(OUTDIR)\nullmdm.obj   \
        $(OUTDIR)\plugxprt.obj \
        $(OUTDIR)\ui.obj \
        $(OUTDIR)\utils.obj \
        $(OUTDIR)\x224.obj  \
        $(OUTDIR)\ui.res

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\PlugTransport.h $(OUTDIR)\PlugTransport.c:
	midl /client none /server none /ms_ext /W1 /c_ext /Oicf /out $(OUTDIR) /iid PlugTransport.c /I . PLugTransport.idl

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /I$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\PlugTransport.obj: $(OUTDIR)\PlugTransport.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /I$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(OUTDIR)\PlugTransport.c

$(OUTDIR)\$(proj).exe:  $(OUTDIR)\PlugTransport.h $(LINK32_OBJS)
    $(link) $(ldebug) $(guilflags) /PDB:$(OUTDIR)\$(proj).pdb -out:$(OUTDIR)\$(proj).exe $(LINK32_OBJS) $(olelibs) shell32.lib comctl32.lib odbc32.lib odbccp32.lib


$(OUTDIR)\ui.res: $(OUTDIR)
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\ui.res ui.rc

clean:
        $(CLEANUP)
