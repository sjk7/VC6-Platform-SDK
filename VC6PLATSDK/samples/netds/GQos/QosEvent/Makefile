TARGETOS=BOTH

#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
comobj=$(OUTDIR)\chkqos.obj $(OUTDIR)\findsp.obj $(OUTDIR)\getqos.obj $(OUTDIR)\setqos.obj $(OUTDIR)\printqos.obj
mainobjs=$(OUTDIR)\qosevent.obj $(OUTDIR)\sender.obj $(OUTDIR)\receiver.obj

all: $(OUTDIR)\qosevent.exe

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Update the resource if necessary

# Update the object file if necessary

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

#--------------------- EXE ---------------------------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Linker options WIN32.MAK provides

# Build rule for EXE
$(OUTDIR)\qosevent.exe: $(OUTDIR) $(mainobjs) $(comobj) $(common_objs) 
    $(link) $(linkdebug) $(conlflags) -out:$(OUTDIR)\qosevent.exe $(mainobjs) $(comobj) $(conlibsmt) ws2_32.lib

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
	if exist "$(OUTDIR)/$(NULL)" rd /s /q $(OUTDIR)
