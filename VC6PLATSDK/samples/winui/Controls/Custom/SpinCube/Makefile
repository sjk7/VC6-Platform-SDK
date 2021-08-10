#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\SpinTest.Exe $(OUTDIR)\SpinCube.Dll

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

SOURCE=.\spintest.c

$(OUTDIR)\SpinTest.Obj: $(OUTDIR) $(SOURCE)
	$(cc) $(cdebug) $(cflags) $(cvarsdll) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

SOURCE=.\spincube.c

$(OUTDIR)\SpinCube.Obj: $(OUTDIR) $(SOURCE) SpinCube.h
	$(cc) $(cdebug) $(cflags) $(cvarsdll) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

SOURCE=.\paint.c

$(OUTDIR)\Paint.Obj: $(OUTDIR) $(SOURCE) Paint.h SpinCube.h
	$(cc) $(cdebug) $(cflags) $(cvarsdll) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

# Build rule for resource files
$(OUTDIR)\SpinTest.Res: $(OUTDIR) SpinTest.Rc SpinTest.h SpinTest.Dlg
	$(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\SpinTest.res $(SOURCE)

$(OUTDIR)\SpinCube.Res: $(OUTDIR) SpinCube.Rc
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\SpinCube.res $(SOURCE)

#SpinCube.Lib: SpinCube.Obj Paint.Obj SpinCube.Def SpinCube.Res
#     $(implib) -machine:$(CPU) \
#     -def:SpinCube.Def   \
#!IF "$(CPU)" == "i386"
#     SpinCube.Obj Paint.Obj \
#!ENDIF
#     -out:SpinCube.Lib

#SpinCube.Dll: SpinCube.Obj Paint.Obj SpinCube.Def SpinCube.Res
#    $(link) $(linkdebug) $(dlllflags) \
##    -base:0x1C000000     \
#    -out:SpinCube.Dll    \
#    SpinCube.Obj SpinCube.Exp SpinCube.Res Paint.Obj $(guilibsdll)

# Build rule for DLL
$(OUTDIR)\SpinCube.dll: $(OUTDIR)\spincube.obj $(OUTDIR)\paint.obj spincube.def $(OUTDIR)\SpinCube.res
    $(link) $(ldebug) $(dllllflags) \
    $(OUTDIR)\spincube.obj $(OUTDIR)\paint.obj $(OUTDIR)\SpinCube.res $(dlllibs) $(guilibsdll) \
    -base:0x1C000000 \
    -out:$(OUTDIR)\SpinCube.dll \
    -def:SpinCube.def


#SpinTest.Exe: SpinTest.Obj SpinCube.Lib SpinTest.Res SpinTest.Def
#    $(link) $(linkdebug) $(guiflags) -out:SpinTest.Exe SpinTest.Obj SpinTest.Res SpinCube.Lib $(guilibsdll)

# Build rule for EXE
$(OUTDIR)\SpinTest.exe: $(OUTDIR) $(OUTDIR)\spincube.dll $(OUTDIR)\spintest.obj spintest.def $(OUTDIR)\SpinTest.res
    $(link) $(linkdebug) $(guiflags) /PDB:$(OUTDIR)\SpinTest.pdb -out:$(OUTDIR)\SpinTest.exe $(OUTDIR)\spintest.obj $(OUTDIR)\spincube.lib $(OUTDIR)\SpinTest.res $(guilibs)


#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
