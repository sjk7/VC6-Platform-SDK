!include <win32.mak>

LIBS = kernel32.lib rasapi32.lib

RasEnumDevices.exe : RasEnumDevices.obj
	$(link) $(debug) $** $(LIBS) -out:$*.exe 

RasEnumDevices.obj: RasEnumDevices.c
	$(cc) $(cdebug) $(cflags) $(cvarsmt) RasEnumDevices.c

nmake cleanall :
	-del *.exe *.obj

nmake clean :
	-del *.exe *.obj