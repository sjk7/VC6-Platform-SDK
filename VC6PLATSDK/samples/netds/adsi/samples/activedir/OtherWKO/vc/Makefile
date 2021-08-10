#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>



all:	$(OUTDIR) $(OUTDIR)\otherwko.exe 

$(OUTDIR)\otherwko.exe:	 $(OUTDIR) $(OUTDIR)\otherwko1.obj 
	$(link) $(ldebug) /OUT:$(OUTDIR)\otherwko.exe $(conlflags) /PDB:$(OUTDIR)\otherwko.pdb /MACHINE:$(CPU) $(OUTDIR)\otherwko1.obj shell32.lib $(ole2libs) odbc32.lib odbccp32.lib wldap32.lib activeds.lib adsiid.lib 

$(OUTDIR)\otherwko1.obj:	otherwko1.cpp
	$(cc) $(cflags) $(cdebug) $(cvars) /GX /FR /Fp$(OUTDIR)\otherwko.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_CONSOLE" /D"_MBCS" /D"UNICODE" /D"_UNICODE" otherwko1.cpp

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
