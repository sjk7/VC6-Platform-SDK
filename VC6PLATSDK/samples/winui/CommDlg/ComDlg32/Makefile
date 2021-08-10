# Nmake macros for building Windows 32-Bit apps

!IF "$(TARGETOS)" == "WIN95"

!include <win32.mak>

all: $(OUTDIR) $(OUTDIR)\comdlg32.exe

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Update the resource if necessary

$(OUTDIR)\comdlg32.res: $(OUTDIR) comdlg32.rc comdlg32.h resource.h
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\comdlg32.res comdlg32.rc

# Update the object file if necessary

$(OUTDIR)\comdlg32.obj: $(OUTDIR) comdlg32.c comdlg32.h
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" comdlg32.c

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\comdlg32.exe: $(OUTDIR) $(OUTDIR)\comdlg32.obj $(OUTDIR)\comdlg32.res
    $(link) $(linkdebug) $(guiflags) /PDB:$(OUTDIR)\comdlg32.pdb -out:$(OUTDIR)\comdlg32.exe $(OUTDIR)\comdlg32.obj $(OUTDIR)\comdlg32.res $(guilibs)

clean:
        $(CLEANUP)

!ELSE
!MESSAGE Sorry this sample only builds for the Windows 9x Platforms
!ENDIF
