!include <Win32.Mak>

all: $(OUTDIR) $(OUTDIR)\dibapi32.dll $(OUTDIR)\wincap32.exe

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Update DIBAPI32.DLL
# Update the resources for DIBAPI32.DLL if necessary

OBJS = $(OUTDIR)\copy.obj $(OUTDIR)\dibutil.obj $(OUTDIR)\dllinit.obj $(OUTDIR)\errors.obj $(OUTDIR)\file.obj $(OUTDIR)\hook.obj $(OUTDIR)\print.obj

$(OUTDIR)\copy.obj: copy.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $(scall) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" copy.c

$(OUTDIR)\dibuitl.obj: dibuitl.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $(scall) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" dibuitl.c

$(OUTDIR)\dllinit.obj: dllinit.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $(scall) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" dllinit.c

$(OUTDIR)\errors.obj: errors.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $(scall) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" errors.c

$(OUTDIR)\file.obj: file.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $(scall) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" file.c

$(OUTDIR)\hook.obj: hook.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $(scall) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" hook.c

$(OUTDIR)\print.obj: print.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $(scall) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" print.c

$(OUTDIR)\dialogs.obj: dialogs.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $(scall) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" dialogs.c

$(OUTDIR)\dlgopen.obj: dlgopen.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $(scall) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" dlgopen.c

$(OUTDIR)\wincap.obj: wincap.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $(scall) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" wincap.c

 
$(OUTDIR)\dibapi.res: dibapi.rc
    rc $(rcvars) $(rcflags) /fo $(OUTDIR)\dibapi.res  -r dibapi.rc

$(OUTDIR)\dibapi32.lib: $(OBJS) dibapi.def
        $(implib)  -MACHINE:$(CPU) \
        -def:dibapi.def \
        $(OBJS) \
        -out:$(OUTDIR)\dibapi32.lib

$(OUTDIR)\dibapi32.dll: $(OBJS) dibapi.def $(OUTDIR)\dibapi.Res $(OUTDIR)\dibapi32.lib
    $(link) $(linkdebug) $(dlllflags) -MACHINE:$(CPU) \
    -base:0x1c000000 \
    -out:$(OUTDIR)\dibapi32.dll \
    $(OUTDIR)\dibapi.Res $(OUTDIR)\dibapi32.exp $(OBJS) $(guilibsdll)

# Update WINCAP32.EXE
# Update the resources for WINCAP32.EXE if necessary

WINOBJS = $(OUTDIR)\dialogs.obj $(OUTDIR)\dlgopen.obj $(OUTDIR)\wincap.obj

$(OUTDIR)\wincap.res: wincap.rc wincap.h wincap.ico
    rc $(rcvars) $(rcflags) /fo $(OUTDIR)\wincap.res -r wincap.rc

$(OUTDIR)\wincap32.exe: $(WINOBJS)  $(OUTDIR)\wincap.Res $(OUTDIR)\dibapi32.lib
  $(link) $(linkdebug) $(guiflags) -out:$*.exe $(WINOBJS) $(OUTDIR)\dibapi32.lib $(OUTDIR)\wincap.Res $(guilibsdll)

.c{$(OUTDIR)}.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $(scall) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

clean:
        $(CLEANUP)
