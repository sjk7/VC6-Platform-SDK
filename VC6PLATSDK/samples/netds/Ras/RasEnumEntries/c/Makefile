!include <win32.mak>

LIBS = kernel32.lib rasapi32.lib

RasEnumEntries.exe : RasEnumEntries.obj
	$(link) $(debug) $** $(LIBS) -out:$*.exe 

RasEnumEntries.obj: RasEnumEntries.c
	$(cc) $(cdebug) $(cflags) $(cvarsmt) RasEnumEntries.c

nmake cleanall :
	-del *.exe *.obj

nmake clean :
	-del *.exe *.obj