!if "$(CPU)" == "IA64"
!message Sorry building this sample for 64bit is not currently supported.
!else
!include <$(MSTOOLS)\samples\com\fundamentals\include\olesampl.mak>

all: simpsvr.exe

simpsvr.exe:  app.obj         \
            doc.obj         \
            icf.obj         \
            ido.obj        \
            iec.obj        \
            ioipao.obj        \
            ioipo.obj        \
            ioo.obj        \
            ips.obj        \
            obj.obj         \
            simpsvr.obj     \
            simpsvr.res
  $(link) $(linkdebug) $(guiflags) -machine:$(CPU) -out:$*.exe $** $(olelibs) $(guilibs) ..\lib\olestd.lib oledlg.lib

.cpp.obj:
    $(cc) /D_DEBUG $(cdebug) $(cflags) $(cvars) $*.cpp

simpsvr.res: simpsvr.rc simpsvr.h
    $(rc) -r simpsvr.rc

# Rules for cleaning out those old files
clean:
    del *.exe *.obj *.res 

!endif
