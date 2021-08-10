!if "$(CPU)" == "IA64"
!message Sorry building this sample for 64bit is not currently supported
!else
# Nmake macros for building Windows 32-Bit apps

Proj=sa

all:SA.exe

!include <inetsdk.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!endif

sa.obj: sa.cpp
    $(cc) $(cflags) $(cvars) $(cdebug) sa.cpp

sa.exe: sa.obj
    $(link) $(lflags) $(ldebug) -out:sa.exe sa.obj $(olelibs) 

!endif
