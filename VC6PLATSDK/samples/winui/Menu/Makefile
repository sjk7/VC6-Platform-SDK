# Nmake macros for building Win32 & Win64 apps

!include <Win32.Mak>

all: $(OUTDIR) $(OUTDIR)\Menu.Exe

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Update the resource if necessary

$(OUTDIR)\Menu.Res: Menu.Rc Menu.h Menu.Dlg checkon.Bmp checkoff.Bmp Menu.Ico
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\Menu.res Menu.Rc

# Update the object file if necessary

$(OUTDIR)\Menu.Obj: Menu.c Menu.h
    $(cc) $(cflags) $(cvars) $(cdebug) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" Menu.c

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\Menu.Exe: $(OUTDIR)\Menu.Obj $(OUTDIR)\Menu.Res Menu.Def
    $(link) $(linkdebug) $(guiflags) -out:$(OUTDIR)\Menu.Exe $(OUTDIR)\Menu.Obj $(OUTDIR)\Menu.Res $(guilibs)

clean:
        $(CLEANUP)
