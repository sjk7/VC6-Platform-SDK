!include <win32.mak>

LIBS = kernel32.lib user32.lib gdi32.lib comctl32.lib rasapi32.lib 

PhoneEntry.exe : PhoneEntry.obj PhoneEntry.res
    $(link) $(debug) $** $(LIBS) -out:$*.exe 

PhoneEntry.obj: PhoneEntry.c
    $(cc) $(cdebug) $(cflags) $(cvarsmt) PhoneEntry.c

PhoneEntry.res : PhoneEntry.rc
    $(rc) $(rcvars) PhoneEntry.rc

cleanall :
    -del *.obj *.res *.exe

clean :
    -del *.obj *.res *.exe