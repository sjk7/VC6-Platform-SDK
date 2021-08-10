#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
APPVER = 4.0
TARGETOS = BOTH
_WIN32_IE = 0x0300
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\rasutil.lib $(OUTDIR)\Rqc.exe

RQC_OBJS=\
	$(OUTDIR)\rqc_main.obj	\

RASUTIL_OBJS= \
	$(OUTDIR)\RuMem.obj	\
	$(OUTDIR)\RuReg.obj	\
	$(OUTDIR)\RuString.obj	\
	$(OUTDIR)\RuSocket.obj	\
	$(OUTDIR)\RcuSync.obj	\
      
#--------------------- Destination Directory --------------------------------------------- 
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

#--------------------- RASUTIL LIB ---------------------------------------------------------------
$(OUTDIR)\Rasutil.lib: $(OUTDIR) $(RASUTIL_OBJS)
    $(implib) -out:$(OUTDIR)\Rasutil.lib -machine:$(CPU) $(RASUTIL_OBJS)

#--------------------- RQC EXE ---------------------------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Linker options WIN32.MAK provides

# Build rule for EXE
$(OUTDIR)\Rqc.exe:  $(OUTDIR) $(RQC_OBJS) $(OUTDIR)\rasutil.lib
    $(link) $(ldebug) $(conflags) /PDB:$(OUTDIR)\Rqc.pdb -out:$(OUTDIR)\Rqc.exe $(RQC_OBJS) $(OUTDIR)\rasutil.lib $(conlibs)


#--------------------- Compiling C/CPP Files ---------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Compiler options WIN32.MAK provides

unicode = -DUNICODE
projIncludes = /I ..\inc

$(OUTDIR)\RuMem.obj : ..\common\RuMem.cpp $(OUTDIR)
    $(cc) $(projIncludes) $(cdebug) $(unicode) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ..\common\RuMem.cpp

$(OUTDIR)\RuReg.obj : ..\common\RuReg.cpp $(OUTDIR)
    $(cc) $(projIncludes) $(cdebug) $(unicode) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ..\common\RuReg.cpp

$(OUTDIR)\RuString.obj : ..\common\RuString.cpp $(OUTDIR)
    $(cc) $(projIncludes) $(cdebug) $(unicode) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ..\common\RuString.cpp

$(OUTDIR)\RuSocket.obj : ..\common\RuSocket.cpp $(OUTDIR)
    $(cc) $(projIncludes) $(cdebug) $(unicode) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ..\common\RuSocket.cpp

$(OUTDIR)\RcuSync.obj : ..\common\RcuSync.cpp $(OUTDIR)
    $(cc) $(projIncludes) $(cdebug) $(unicode) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ..\common\RcuSync.cpp

# Note that the client isn't built Unicode and is built with WinVer 4.0 Headers
$(OUTDIR)\rqc_main.obj : main.cpp $(OUTDIR)
    $(cc) $(projIncludes) $(cdebug) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\rqc_main.obj" /Fd"$(OUTDIR)\\rqc_main.pdb" main.cpp

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
