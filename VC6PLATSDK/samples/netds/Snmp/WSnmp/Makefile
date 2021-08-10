!include <win32.mak>

LIBS = kernel32.lib user32.lib gdi32.lib ws2_32.lib snmpapi.lib wsnmp32.lib mgmtapi.lib oldnames.lib

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

all:$(OUTDIR) $(OUTDIR)\wsnmputil.exe

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\wsnmputil.exe: $(OUTDIR)\wsnmputil.obj $(OUTDIR)\helper.obj
    $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(LIBS)

clean:   
        $(CLEANUP)
	-del *.obj *.pdb *.ilk

cleanall:clean
	-del *.exe
