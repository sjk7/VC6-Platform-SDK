!if "$(CPU)" == "IA64"
!message Sorry building this sample for 64bit is not currently supported.
!else
!include <$(MSTOOLS)\samples\com\fundamentals\include\olesampl.mak>

all: simpdnd.exe

simpdnd.exe:  app.obj         \
            doc.obj         \
            dxferobj.obj    \
            ias.obj         \
            ids.obj         \
            idt.obj         \
            iocs.obj        \
            simpdnd.obj     \
            simpdnd.res     \
            site.obj
  $(link) $(linkdebug) $(guiflags) -machine:$(CPU) -out:$*.exe $** $(olelibs) $(guilibs) ..\lib\olestd.lib oledlg.lib

.cpp.obj:
    $(cc) /D_DEBUG $(cdebug) $(cflags) $(cvars) $*.cpp

simpdnd.res: simpdnd.rc simpdnd.h
    $(rc) -r simpdnd.rc

# Rules for cleaning out those old files
clean:
    del *.exe *.obj *.res 


!endif
