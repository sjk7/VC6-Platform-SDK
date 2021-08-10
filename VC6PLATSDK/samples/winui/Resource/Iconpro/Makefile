!include <Win32.Mak>

all: $(OUTDIR) $(OUTDIR)\iconpro.exe $(OUTDIR)\iconpro.hlp

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Update the object file if necessary

$(OUTDIR)\iconpro.obj: iconpro.c iconpro.h resource.h icons.h mdichild.h
    $(cc) $(cdebug) $(cflags) $(cvars) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" iconpro.c

$(OUTDIR)\dib.obj: dib.c dib.h
    $(cc) $(cdebug) $(cflags) $(cvars) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" dib.c

$(OUTDIR)\icons.obj: icons.c iconpro.h resource.h icons.h dib.h
    $(cc) $(cdebug) $(cflags) $(cvars) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" icons.c

$(OUTDIR)\mdichild.obj: mdichild.c iconpro.h resource.h icons.h mdichild.h
    $(cc) $(cdebug) $(cflags) $(cvars) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" mdichild.c

# Update the resources if necessary

$(OUTDIR)\iconpro.res: iconpro.rc iconpro.h resource.h
    rc -r -fo $(OUTDIR)\iconpro.res iconpro.rc

# Build the help file if necessary

$(OUTDIR)\iconpro.hlp: iconpro.hpj iconpro.rtf
    $(hc) -o .\$(OUTDIR)\iconpro.hlp $(hcvars) iconpro.hpj 

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\iconpro.exe: $(OUTDIR)\iconpro.obj \
	$(OUTDIR)\mdichild.obj \
	$(OUTDIR)\icons.obj \
	$(OUTDIR)\dib.obj \
	$(OUTDIR)\iconpro.res
    $(link) $(linkdebug) $(guiflags) -out:$(OUTDIR)\iconpro.exe	 \
    $(OUTDIR)\iconpro.obj \
    $(OUTDIR)\mdichild.obj \
    $(OUTDIR)\icons.obj \
    $(OUTDIR)\dib.obj \
    $(OUTDIR)\iconpro.res $(guilibs) shell32.lib

clean:
        $(CLEANUP)
