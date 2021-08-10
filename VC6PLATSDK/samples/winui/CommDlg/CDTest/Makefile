# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: $(OUTDIR) $(OUTDIR)\cdtest.exe

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

OBJS=$(OUTDIR)\cdtest.obj $(OUTDIR)\open.obj $(OUTDIR)\save.obj $(OUTDIR)\print.obj $(OUTDIR)\font.obj $(OUTDIR)\colors.obj $(OUTDIR)\find.obj $(OUTDIR)\replace.obj $(OUTDIR)\title.obj

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN

# Update the resource if necessary

$(OUTDIR)\cdtest.res: res.rc cdtest.h
    $(rc) -r $(OTHERRCOPTS) -fo $(OUTDIR)\cdtest.res res.rc

# Update the object file if necessary

$(OUTDIR)\cdtest.obj: cdtest.c cdtest.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) /WX /Fo"$(OUTDIR)\\" cdtest.c

$(OUTDIR)\open.obj: open.c open.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) /WX /Fo"$(OUTDIR)\\" open.c

$(OUTDIR)\save.obj: save.c save.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) /WX /Fo"$(OUTDIR)\\" save.c

$(OUTDIR)\print.obj: print.c print.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) /WX /Fo"$(OUTDIR)\\" print.c

$(OUTDIR)\font.obj: font.c font.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) /WX /Fo"$(OUTDIR)\\" font.c

$(OUTDIR)\colors.obj: colors.c colors.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) /WX /Fo"$(OUTDIR)\\" colors.c

$(OUTDIR)\find.obj: find.c find.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) /WX /Fo"$(OUTDIR)\\" find.c

$(OUTDIR)\replace.obj: replace.c replace.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) /WX /Fo"$(OUTDIR)\\" replace.c

$(OUTDIR)\title.obj: title.c title.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) /WX /Fo"$(OUTDIR)\\" title.c

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\cdtest.exe:  $(OBJS) $(OUTDIR)\cdtest.res
    $(link) $(linkdebug) $(guiflags) -out:$(OUTDIR)\cdtest.exe $(OBJS) $(OUTDIR)\cdtest.res $(guilibs) shlwapi.lib
