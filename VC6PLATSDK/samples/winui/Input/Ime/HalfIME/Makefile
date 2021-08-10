# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

all: $(OUTDIR) $(OUTDIR)\halfime.exe

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

LIBS=imm32.lib

# Update the resource if necessary

$(OUTDIR)\halfime.res: halfime.rc
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\halfime.res halfime.rc

# Update the object file if necessary

.c{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\halfime.exe:    $(OUTDIR)\main.obj   \
                $(OUTDIR)\halfime.res
    $(link) $(linkdebug) $(guiflags) -out:$(OUTDIR)\halfime.exe $** $(guilibs) $(LIBS)

clean:
        $(CLEANUP)
