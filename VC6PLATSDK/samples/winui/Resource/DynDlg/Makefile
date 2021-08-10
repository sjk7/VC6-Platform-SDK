# Nmake macros for building Windows 32/64 Bit apps

!include <Win32.Mak>

all: $(OUTDIR) $(OUTDIR)\dyndlg.exe $(OUTDIR)\dyndlg.hlp

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Update the resource if necessary

$(OUTDIR)\dyndlg.res: dyndlg.rc dyndlg.h
    $(rc) $(rcvars) -r -fo $(OUTDIR)\dyndlg.res dyndlg.rc

# Update the online help file if necessary.

$(OUTDIR)\dyndlg.hlp: dyndlg.hpj dyndlg.rtf
    $(hc) -o .\$(OUTDIR)\dyndlg.hlp $(hcvars) dyndlg.hpj 

# Update the object file if necessary

$(OUTDIR)\dyndlg.obj: dyndlg.c dyndlg.h
    $(cc) $(cdebug) $(cflags) $(cvars) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" dyndlg.c

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\dyndlg.exe: $(OUTDIR)\dyndlg.obj $(OUTDIR)\dyndlg.res
    $(link) $(linkdebug) $(guiflags) -out:$(OUTDIR)\dyndlg.exe $(OUTDIR)\dyndlg.obj $(OUTDIR)\dyndlg.res $(guilibs)

clean:
        $(CLEANUP)
