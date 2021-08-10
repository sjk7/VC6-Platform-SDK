!include <win32.mak>

LIBS = kernel32.lib user32.lib mprapi.lib 

LoadProtocol.exe : LoadProtocol.obj
	$(link) $(debug) $** $(LIBS) -out:$*.exe 

LoadProtocol.obj: LoadProtocol.c
	$(cc) $(cdebug) $(cflags) $(cvarsmt) LoadProtocol.c

nmake cleanall :
	-del *.exe *.obj