# Nmake macros for building Windows 32-Bit apps

!IF "$(TARGETOS)" == "WINNT"

!include <Win32.Mak>

all: wxform.exe

# Update the resource if necessary

wxform.res: wxform.rc wxform.h
    rc $(rcvars) $(rcflags) -r -fo wxform.res wxform.rc

# Update the object file if necessary

wxform.obj: wxform.c wxform.h
    $(cc) $(cdebug) $(cflags) $(cvars) wxform.c

# Update the executable file if necessary, and if so, add the resource back in.

wxform.exe: wxform.obj wxform.res wxform.def
    $(link) $(linkdebug) $(guiflags) -out:wxform.exe wxform.obj wxform.res $(guilibs)
!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT Platform
!ENDIF
