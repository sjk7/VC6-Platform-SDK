!include <win32.mak>

LIBS = kernel32.lib rasapi32.lib

RasDial.exe : RasDial.obj
	$(link) $(debug) $** $(LIBS) -out:sdkrasdial.exe 

RasDial.obj: RasDial.c
	$(cc) $(cdebug) $(cflags) $(cvarsmt) RasDial.c

nmake cleanall :
	-del *.exe *.obj

nmake clean :
	-del *.exe *.obj