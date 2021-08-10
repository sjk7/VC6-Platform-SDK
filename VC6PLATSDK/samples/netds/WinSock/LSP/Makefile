!include <win32.mak>

all: $(OUTDIR) $(OUTDIR)\lsp.dll $(OUTDIR)\instlsp.exe

$(OUTDIR):
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

DLL_OBJS=  $(OUTDIR)\spi.obj        \
           $(OUTDIR)\extension.obj  \
           $(OUTDIR)\overlap.obj    \
           $(OUTDIR)\provider.obj   \
           $(OUTDIR)\sockinfo.obj   \
           $(OUTDIR)\lspguid.obj    \
           $(OUTDIR)\asyncselect.obj

INSTALL_OBJS= $(OUTDIR)\instlsp.obj     \
              $(OUTDIR)\lspguid.obj     \
              $(OUTDIR)\prnpinfo.obj    \
              $(OUTDIR)\provider.obj

LIBS= ws2_32.lib ole32.lib rpcrt4.lib

.cpp{$(OUTDIR)}.obj:
	$(cc) $(cdebug) $(cflags) $(cvarsmt) -DSTRICT -DFD_SETSIZE=1024 $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\lsp.dll: $(DLL_OBJS)
	$(link) $(linkdebug) $(dlllflags) -def:lsp.def \
	-out:$*.dll -pdb:$*.pdb $(guilibsdll) $** $(LIBS)
        copy $*.dll %SYSTEMROOT%\System32

$(OUTDIR)\instlsp.exe: $(INSTALL_OBJS)
    $(link) $(linkdebug) $(conlflags) -out:$*.exe $** $(LIBS)

clean:
    rmdir /s /q $(OUTDIR)
