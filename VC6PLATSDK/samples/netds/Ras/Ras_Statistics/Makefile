!include <win32.mak>

LIBS = kernel32.lib rasapi32.lib

RasGetConnectionStatistics.exe : RasGetConnectionStatistics.obj
	$(link) $(debug) $** $(LIBS) -out:$*.exe 

RasGetConnectionStatistics.obj: RasGetConnectionStatistics.c
	$(cc) $(cdebug) $(cflags) $(cvarsmt) RasGetConnectionStatistics.c

nmake cleanall :
	-del *.exe *.obj *.pdb

nmake clean :
	-del *.exe *.obj *.pdb