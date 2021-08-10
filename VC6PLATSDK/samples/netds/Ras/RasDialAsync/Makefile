!include <win32.mak>

LIBS = kernel32.lib rasapi32.lib

RasDialAsync.exe : RasDialAsync.obj
	$(link) $(debug) $** $(LIBS) -out:$*.exe 

RasDialAsync.obj: RasDialAsync.c
	$(cc) $(cdebug) $(cflags) $(cvarsmt) RasDialAsync.c

nmake cleanall :
	-del *.exe *.obj

nmake clean :
	-del *.exe *.obj