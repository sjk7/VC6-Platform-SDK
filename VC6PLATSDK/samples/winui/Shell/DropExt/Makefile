# Nmake macros for building Win32 & Win64 components

# Copyright 1994 - 1999 Microsoft Corporation

#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\DropExt.dll
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Update the object files if necessary

SOURCE=.\DefClsf.c

$(OUTDIR)\DefClsf.obj : $(SOURCE) $(OUTDIR)
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

SOURCE=.\DropExt.c

$(OUTDIR)\DropExt.obj : $(SOURCE) $(OUTDIR)
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

# Build rule for resource file
SOURCE=.\DropExt.rc

$(OUTDIR)\DropExt.res: $(SOURCE) $(OUTDIR) DropExt.h
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\DropExt.res $(SOURCE)
    
# Update the import library

$(OUTDIR)\DropExt.Lib: $(OUTDIR)\DropExt.Obj DropExt.Def
    $(implib) -machine:$(CPU) -def:DropExt.Def $(OUTDIR)\DropExt.Obj -out:$(OUTDIR)\DropExt.Lib

# Update the dynamic link library

# Build rule for DLL
$(OUTDIR)\DropExt.dll: $(OUTDIR) $(OUTDIR)\DropExt.Lib $(OUTDIR)\DropExt.Obj $(OUTDIR)\DefClsf.Obj DropExt.Def $(OUTDIR)\DropExt.res
    $(link) $(ldebug) $(dllllflags) \
    $(OUTDIR)\DropExt.Obj $(OUTDIR)\DefClsf.Obj $(OUTDIR)\dropext.exp $(OUTDIR)\DropExt.res $(dlllibs) $(guilibsdll) Shell32.Lib uuid.Lib Ole32.Lib \
    -out:$(OUTDIR)\DropExt.dll \
    -base:0x1C000000

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
