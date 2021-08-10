# Nmake macros for building Windows 32-Bit apps

!include <Win32.Mak>

all: HalfTone.exe

LIBS=comctl32.lib

# Update the resource if necessary

HalfTone.res: HalfTone.rc resource.h
    rc -r HalfTone.rc

# Update the object file if necessary

HalfTone.obj: HalfTone.c resource.h
    $(cc) $(cflags) $(cvars) $(cdebug) HalfTone.c

# Update the executable file if necessary, and if so, add the resource back in.

HalfTone.exe: HalfTone.obj HalfTone.res
    $(link) $(linkdebug) $(guiflags) -out:HalfTone.exe HalfTone.obj HalfTone.res $(guilibs) $(LIBS)
