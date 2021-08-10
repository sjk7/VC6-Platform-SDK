APPVER = 5.2
TARGETOS = WINNT
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\rasutil.lib $(OUTDIR)\rqsmsg.dll $(OUTDIR)\Rqs.exe

RASUTIL_OBJS= \
	$(OUTDIR)\RuMem.obj	\
	$(OUTDIR)\RuReg.obj	\
	$(OUTDIR)\RuString.obj	\
	$(OUTDIR)\RuSocket.obj	\
	$(OUTDIR)\RcuSync.obj	\

RQSMSG_OBJS=\
	$(OUTDIR)\rqsmsg.obj	\

RQS_OBJS=\
	$(OUTDIR)\rqs_main.obj	\
	$(OUTDIR)\RqsConfig.obj	\
	$(OUTDIR)\RqsEngine.obj	\
	$(OUTDIR)\RqsClient.obj	\
        
#--------------------- Destination Directory --------------------------------------------- 
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

#--------------------- RASUTIL LIB ---------------------------------------------------------------
$(OUTDIR)\Rasutil.lib: $(OUTDIR) $(RASUTIL_OBJS)
    $(implib) -out:$(OUTDIR)\Rasutil.lib -machine:$(CPU) $(RASUTIL_OBJS)

#--------------------- RQSMSG DLL ---------------------------------------------------------------
$(OUTDIR)\rqsmsg.dll: $(OUTDIR) $(RQSMSG_OBJS) $(OUTDIR)\messages.res
    $(link) $(ldebug) $(dllllflags) \
    $(RQSMSG_OBJS) $(OUTDIR)\messages.res $(dlllibs) $(guilibs) \
    -out:$(OUTDIR)\rqsmsg.dll \
    -def:..\rqsmsg\rqsmsg.def

#--------------------- RQS EXE ---------------------------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Linker options WIN32.MAK provides

# Build rule for EXE
$(OUTDIR)\Rqs.exe:  $(OUTDIR) $(RQS_OBJS) $(OUTDIR)\rasutil.lib
    $(link) $(ldebug) $(conflags) /PDB:$(OUTDIR)\Rqs.pdb -out:$(OUTDIR)\Rqs.exe $(RQS_OBJS) $(OUTDIR)\rasutil.lib mprapi.lib shlwapi.lib rtutils.lib iphlpapi.lib $(conlibs)


#--------------------- Compiling C/CPP Files ---------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Compiler options WIN32.MAK provides

projIncludes = /I ..\inc /I .
unicode = -DUNICODE

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

$(OUTDIR)\RqsMsg.obj : ..\RqsMsg\RqsMsg.cpp $(OUTDIR)
    $(cc) $(projIncludes) $(cdebug) $(unicode) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ..\RqsMsg\RqsMsg.cpp

$(OUTDIR)\rqs_main.obj : main.cpp $(OUTDIR)
    $(cc) $(projIncludes) $(cdebug) $(unicode) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\rqs_main.obj" /Fd"$(OUTDIR)\\rqs_main.pdb" main.cpp

$(OUTDIR)\RqsConfig.obj : RqsConfig.cpp $(OUTDIR)
    $(cc) $(projIncludes) $(cdebug) $(unicode) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" RqsConfig.cpp

$(OUTDIR)\RqsEngine.obj : RqsEngine.cpp $(OUTDIR)
    $(cc) $(projIncludes) $(cdebug) $(unicode) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" RqsEngine.cpp

$(OUTDIR)\RqsClient.obj : RqsClient.cpp $(OUTDIR)
    $(cc) $(projIncludes) $(cdebug) $(unicode) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" RqsClient.cpp


#--------------------- Compiling Resource Files ------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Resource Compiler options WIN32.MAK provides

# Build rule for resource file

$(OUTDIR)\rqmsg.res: ..\rqsmsg\rqmsg.rc $(OUTDIR)
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\rqsmsg.res ..\rqsmsg\rqsmsg.rc

#--------------------- Compiling Message Files ------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Resource Compiler options WIN32.MAK provides

# Build rule for message file
SOURCE=..\RqsMsg\rqsmsg.mc

$(OUTDIR)\rqsmsg.h $(OUTDIR)\rqsmsg.rc $(OUTDIR)\msg0001.bin: $(SOURCE) $(OUTDIR)
   $(mc) -r $(OUTDIR) -h $(OUTDIR) -v $(SOURCE)
   copy $(OUTDIR)\rqsmsg.h $(OUTDIR)\..\rqsmsg.h

# for resource files utilizing the mc files
SOURCE=..\RqsMsg\messages.rc

$(OUTDIR)\messages.res: $(SOURCE) $(OUTDIR) $(OUTDIR)\rqsmsg.rc $(OUTDIR)\msg00001.bin
    $(rc) $(rcflags) $(rcvars) /i $(OUTDIR) /fo $(OUTDIR)\messages.res $(SOURCE)


#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
