#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>



all:	$(OUTDIR) $(OUTDIR)\adscmd.exe 

$(OUTDIR)\adscmd.exe:	 $(OUTDIR) $(OUTDIR)\dump.obj $(OUTDIR)\enum.obj $(OUTDIR)\main.obj $(OUTDIR)\util.obj 
	$(link) $(ldebug) /OUT:$(OUTDIR)\adscmd.exe $(conlflags) /PDB:$(OUTDIR)\adscmd.pdb /MACHINE:$(CPU) $(OUTDIR)\dump.obj $(OUTDIR)\enum.obj $(OUTDIR)\main.obj $(OUTDIR)\util.obj shell32.lib $(ole2libs) odbc32.lib odbccp32.lib activeds.lib adsiid.lib 

$(OUTDIR)\dump.obj:	dump.cxx
	$(cc) $(cflags) $(cdebug) $(cvars) /GX /Fp$(OUTDIR)\adscmd.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_CONSOLE" /D"_MBCS" dump.cxx

$(OUTDIR)\enum.obj:	enum.cxx
	$(cc) $(cflags) $(cdebug) $(cvars) /GX /Fp$(OUTDIR)\adscmd.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_CONSOLE" /D"_MBCS" enum.cxx

$(OUTDIR)\main.obj:	main.cxx
	$(cc) $(cflags) $(cdebug) $(cvars) /GX /Fp$(OUTDIR)\adscmd.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_CONSOLE" /D"_MBCS" main.cxx

$(OUTDIR)\util.obj:	util.cxx
	$(cc) $(cflags) $(cdebug) $(cvars) /GX /Fp$(OUTDIR)\adscmd.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_CONSOLE" /D"_MBCS" util.cxx

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
