# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: $(OUTDIR) $(OUTDIR)\cliptext.exe

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Update the resource if necessary

$(OUTDIR)\cliptext.res: cliptext.rc cliptext.h
    rc -r /fo $(OUTDIR)\cliptext.res cliptext.rc

# Update the object file if necessary

$(OUTDIR)\cliptext.obj: cliptext.c cliptext.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" cliptext.c

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\cliptext.exe: $(OUTDIR)\cliptext.obj $(OUTDIR)\cliptext.res cliptext.def
    $(link) $(linkdebug) $(guiflags) -out:$(OUTDIR)\cliptext.exe $(OUTDIR)\cliptext.obj $(OUTDIR)\cliptext.res $(guilibs)

clean:
        $(CLEANUP)
