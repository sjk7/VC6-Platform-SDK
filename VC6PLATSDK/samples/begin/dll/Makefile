# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

all: $(OUTDIR) $(OUTDIR)\demo.exe $(OUTDIR)\select.dll

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Update the object files if necessary

$(OUTDIR)\demo.obj: demo.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" demo.c

$(OUTDIR)\select.obj: select.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" select.c

# Update the resources if necessary

$(OUTDIR)\demo.res: demo.rc demo.h
    $(rc) $(rcvars) /fo $(OUTDIR)\demo.res demo.c

# Update the import library

$(OUTDIR)\select.lib: $(OUTDIR)\select.obj select.def
    $(implib) -machine:$(CPU)     \
    -def:select.def	    \
    $(OUTDIR)\select.obj	 	    \
    -out:$(OUTDIR)\select.lib

# Update the dynamic link library

$(OUTDIR)\select.dll: $(OUTDIR)\select.obj select.def
    $(link) $(linkdebug) $(dlllflags)     \
    -base:0x1C000000  \
    -out:$(OUTDIR)\select.dll   \
    $(OUTDIR)\select.exp $(OUTDIR)\select.obj $(guilibsdll)


# Update the executable file if necessary.
# If so, add the resource back in.

$(OUTDIR)\demo.exe: $(OUTDIR)\demo.obj $(OUTDIR)\select.lib $(OUTDIR)\demo.res demo.def
    $(link) $(linkdebug) $(guiflags) -out:$(OUTDIR)\demo.exe $(OUTDIR)\demo.obj $(OUTDIR)\select.lib $(OUTDIR)\demo.res $(guilibsdll)

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
