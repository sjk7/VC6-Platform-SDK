#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\accserv.exe $(OUTDIR)\testacc.exe

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

LIBS = user32.lib ws2_32.lib

testacc_OBJS= $(OUTDIR)\testaccept.obj 
accserv_OBJS= $(OUTDIR)\common.obj $(OUTDIR)\nbaccept.obj $(OUTDIR)\asaccept.obj $(OUTDIR)\sockinfo.obj $(OUTDIR)\main.obj

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

#--------------------- EXE ---------------------------------------------------------------
#PLEASE REFER TO WIN32.MAK for the different Linker options WIN32.MAK provides

# Build rule for EXE
$(OUTDIR)\accserv.exe:  $(OUTDIR) $(accserv_OBJS) 
	$(link) $(ldebug) $(conflags) /PDB:$(OUTDIR)\accserv.pdb -out:$(OUTDIR)\accserv.exe $(accserv_OBJS) $(conlibs) $(LIBS)

$(OUTDIR)\testacc.exe:  $(OUTDIR) $(testacc_OBJS) 
	$(link) $(ldebug) $(conflags) /PDB:$(OUTDIR)\testacc.pdb -out:$(OUTDIR)\testacc.exe $(testacc_OBJS) $(conlibs) $(LIBS)

clean:
	$(CLEANUP)
