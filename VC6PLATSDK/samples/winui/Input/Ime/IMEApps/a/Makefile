# Nmake macros for building Win32 & Win64 apps

# Requires Windows 2000

!include <win32.mak>

all: $(OUTDIR) $(OUTDIR)\IMEApps.Exe

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

LIBS=imm32.Lib comctl32.Lib
LINKFILES=$(OUTDIR)\Comp.Obj $(OUTDIR)\Data.Obj $(OUTDIR)\IMEApps.Obj $(OUTDIR)\IMEMenu.Obj $(OUTDIR)\Mode.Obj $(OUTDIR)\Paint.Obj $(OUTDIR)\SetComp.Obj \
          $(OUTDIR)\Status.Obj $(OUTDIR)\Subs.Obj $(OUTDIR)\Toolbar.Obj $(OUTDIR)\WSubs.Obj $(OUTDIR)\IMEApps.Res

# Update the resource if necessary

$(OUTDIR)\IMEApps.Res: ..\IMEApps.Rc ..\IMEApps.Rcv
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\IMEApps.Res   ..\IMEApps.Rc

# Update the object file if necessary

{..}.c{$(OUTDIR)}.Obj:
    $(cc) $(cdebug) $(cflags) $(cvars) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\IMEApps.Exe:    $(OUTDIR)\Comp.Obj    \
                $(OUTDIR)\Data.Obj    \
                $(OUTDIR)\IMEApps.Obj \
                $(OUTDIR)\IMEMenu.Obj \
                $(OUTDIR)\Mode.Obj    \
                $(OUTDIR)\Paint.Obj   \
                $(OUTDIR)\SetComp.Obj \
                $(OUTDIR)\Status.Obj  \
                $(OUTDIR)\Subs.Obj    \
                $(OUTDIR)\Toolbar.Obj \
                $(OUTDIR)\WSubs.Obj   \
                $(OUTDIR)\IMEApps.Res
    $(link) $(linkdebug) $(guiflags) -out:$(OUTDIR)\IMEApps.Exe $(LINKFILES) $(guilibs) $(LIBS)

clean:
        $(CLEANUP)
