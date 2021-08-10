#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\simples.exe $(OUTDIR)\simplec.exe $(OUTDIR)\ioctl.exe

LIBS = kernel32.lib oldnames.lib libcmt.lib ws2_32.lib

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)
    
#--------------------- EXE ---------------------------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Linker options WIN32.MAK provides

# Build rule for EXE
$(OUTDIR)\simplec.exe:  $(OUTDIR) $(OUTDIR)\simplec.obj
    $(link) $(ldebug) $(conflags) /PDB:$(OUTDIR)\simplec.pdb -out:$(OUTDIR)\simplec.exe $(OUTDIR)\simplec.obj $(conlibs) user32.lib

$(OUTDIR)\simples.exe:  $(OUTDIR) $(OUTDIR)\simples.obj
    $(link) $(ldebug) $(conflags) /PDB:$(OUTDIR)\simples.pdb -out:$(OUTDIR)\simples.exe $(OUTDIR)\simples.obj $(conlibs)

$(OUTDIR)\ioctl.exe:  $(OUTDIR) $(OUTDIR)\ioctl.obj
    $(link) $(ldebug) $(conflags) /PDB:$(OUTDIR)\ioctl.pdb -out:$(OUTDIR)\ioctl.exe $(OUTDIR)\ioctl.obj $(conlibs) user32.lib

#--------------------- Compiling C/CPP Files ---------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Compiler options WIN32.MAK provides
SOURCE=.\simplec.c

$(OUTDIR)\simplec.obj : $(SOURCE) $(OUTDIR)
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)


SOURCE=.\simples.c

$(OUTDIR)\simples.obj : $(SOURCE) $(OUTDIR)
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

SOURCE=.\ioctl.c

$(OUTDIR)\ioctl.obj : $(SOURCE) $(OUTDIR)
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
