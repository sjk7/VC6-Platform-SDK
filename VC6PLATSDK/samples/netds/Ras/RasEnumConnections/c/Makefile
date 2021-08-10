!include <win32.mak>

LIBS = kernel32.lib rasapi32.lib

RasEnumConnections.exe : RasEnumConnections.obj
	$(link) $(debug) $** $(LIBS) -out:$*.exe 

RasEnumConnections.obj: RasEnumConnections.c
	$(cc) $(cdebug) $(cflags) $(cvarsmt) RasEnumConnections.c

nmake cleanall :
	-del *.exe *.obj

nmake clean :
	-del *.exe *.obj