!IF "$(TARGETOS)" == "WINNT"
!include <win32.mak>

LIBS = kernel32.lib rasapi32.lib Advapi32.lib

customentry.exe : customentry.obj
	$(link) $(debug) $** $(LIBS) -out:$*.exe 

customentry.obj: customentry.c
	$(cc) $(cdebug) $(cflags) $(cvarsmt) customentry.c

nmake cleanall :
	-del *.exe *.obj

nmake clean :
	-del *.exe *.obj

!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT Platform
!ENDIF
