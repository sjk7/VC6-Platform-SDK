# Nmake macros for building Win32 & Win64 apps

!include <win32.mak>
cflags     = -DUSEWAPI $(cflags)

all: $(OUTDIR) $(OUTDIR)\IMEAppsm.Exe

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

LIBS=imm32.lib comctl32.lib
LINKFILES=$(OUTDIR)\Comp.Obj $(OUTDIR)\Data.Obj $(OUTDIR)\IMEApps.Obj $(OUTDIR)\IMEMenu.Obj $(OUTDIR)\Mode.Obj $(OUTDIR)\Paint.Obj $(OUTDIR)\SetComp.Obj \
          $(OUTDIR)\Status.Obj $(OUTDIR)\Subs.Obj $(OUTDIR)\Toolbar.Obj $(OUTDIR)\WSubs.Obj $(OUTDIR)\IMEApps.Res
# Update the resource if necessary

$(OUTDIR)\IMEApps.Res: ..\IMEApps.Rc ..\IMEApps.Rcv
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\IMEApps.Res   ..\IMEApps.Rc

# Update the object file if necessary
{..}.c{$(OUTDIR)}.Obj:
    $(cc) $(cdebug) $(cflags) $(cvars) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\IMEAppsm.Exe:   $(OUTDIR)\Comp.Obj    \
                $(OUTDIR)\Data.Obj    \
                $(OUTDIR)\IMEApps.Obj \
                $(OUTDIR)\IMEMenu.Obj \
                $(OUTDIR)\Mode.Obj    \
                $(OUTDIR)\Paint.Obj   \
                $(OUTDIR)\SetComp.Obj \
                $(OUTDIR)\Status.Obj  \
                $(OUTDIR)\Subs.Obj    \
                $(OUTDIR)\WSubs.Obj   \
                $(OUTDIR)\Toolbar.Obj \
                $(OUTDIR)\IMEApps.Res
    $(link) $(linkdebug) $(guiflags) -out:$(OUTDIR)\IMEAppsm.Exe $(LINKFILES) $(guilibs) $(LIBS)

clean:
        $(CLEANUP)
