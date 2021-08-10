# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

all: $(OUTDIR) $(OUTDIR)\fullime.exe

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

LIBS=imm32.lib

# Update the resource if necessary

$(OUTDIR)\fullime.res: fullime.rc
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\fullime.res fullime.rc

# Update the object file if necessary

.c{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\fullime.exe:    $(OUTDIR)\candui.obj \
                $(OUTDIR)\global.obj \
                $(OUTDIR)\imeui.obj  \
                $(OUTDIR)\main.obj   \
                $(OUTDIR)\fullime.res
    $(link) $(linkdebug) $(guiflags) -out:$(OUTDIR)\fullime.exe $** $(guilibs) $(LIBS)

clean:
        $(CLEANUP)
