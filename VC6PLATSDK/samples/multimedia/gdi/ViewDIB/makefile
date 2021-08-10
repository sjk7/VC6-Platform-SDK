# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

all: ViewDIB.exe


# Update the resource if necessary
ViewDIB.res: ViewDIB.rc resource.h
    rc -r -fo ViewDIB.res ViewDIB.rc

# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

# Update the executable file if necessary, and if so, add the resource back in.
ViewDIB.exe: ViewDIB.obj OpenDIB.obj DIBSECTN.obj ViewDIB.res
    $(link) $(linkdebug) $(guiflags) -out:ViewDIB.exe \
       ViewDIB.obj OpenDIB.obj DIBSECTN.obj ViewDIB.res  $(guilibs)


# Clean up everything except .exe
clean:
    del *.obj *.res
