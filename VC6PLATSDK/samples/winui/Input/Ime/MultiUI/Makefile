# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

all: $(OUTDIR) $(OUTDIR)\multiui.exe

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

LIBS=imm32.lib comctl32.lib

# Update the resource if necessary

$(OUTDIR)\multiui.res: multiui.rc
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\multiui.res multiui.rc


# Update the object file if necessary
.c{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\multiui.exe:    $(OUTDIR)\dlgs.obj    \
                          $(OUTDIR)\data.obj    \
                          $(OUTDIR)\multiui.obj \
                          $(OUTDIR)\multiwnd.obj    \
                          $(OUTDIR)\multiui.res
    $(link) $(linkdebug) $(guiflags) -out:$(OUTDIR)\multiui.exe $** $(guilibs) $(LIBS)

clean:
        $(CLEANUP)
