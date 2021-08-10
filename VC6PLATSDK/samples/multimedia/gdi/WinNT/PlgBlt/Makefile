# Nmake macros for building Windows 32-Bit apps

!if "$(TARGETOS)" == "WINNT"

!include <Win32.Mak>

all: plgblt.exe

# Update the resource if necessary
plgblt.res: plgblt.rc plgblt.h
    rc $(rcvars) $(rcflags) -r -fo plgblt.res plgblt.rc

# Inference rule for updating the object files
.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $*.c

# Update the executable file if necessary, and if so, add the resource back in.
plgblt.exe: plgblt.obj track.obj bitmap.obj plgblt.res plgblt.def
    $(link) $(linkdebug) $(guiflags) -out:plgblt.exe plgblt.obj track.obj bitmap.obj plgblt.res $(guilibs)


# Clean up everything except .exe file
clean:
    del *.obj *.res
!ELSE
!MESSAGE Sorry, this sample only builds for the Windows NT Platform
!ENDIF
