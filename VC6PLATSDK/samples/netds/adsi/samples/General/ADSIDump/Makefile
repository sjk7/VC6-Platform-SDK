#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>



all:	$(OUTDIR) $(OUTDIR)\AdsiDump.exe 

$(OUTDIR)\AdsiDump.exe:	 $(OUTDIR) $(OUTDIR)\StdAfx.obj $(OUTDIR)\AdsiDump.obj  
	$(link) $(ldebug) /OUT:$(OUTDIR)\AdsiDump.exe $(conlflags) /PDB:$(OUTDIR)\AdsiDump.pdb /MACHINE:$(CPU) $(OUTDIR)\StdAfx.obj $(OUTDIR)\AdsiDump.obj shell32.lib $(ole2libs) odbc32.lib odbccp32.lib activeds.lib adsiid.lib 

$(OUTDIR)\StdAfx.obj:	StdAfx.cpp
	$(cc) $(cflags) $(cdebug) $(cvars) /GX /FR /Yc"stdafx.h" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_CONSOLE" /D"_MBCS" /D"_UNICODE" /D"UNICODE" /D"_NO_STRING_TABLE" /I..\Common StdAfx.cpp

$(OUTDIR)\AdsiDump.obj:	AdsiDump.cpp
	$(cc) $(cflags) $(cdebug) $(cvars) /GX /FR /Yu"stdafx.h" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_CONSOLE" /D"_MBCS" /D"_UNICODE" /D"UNICODE" /D"_NO_STRING_TABLE" /I..\Common AdsiDump.cpp

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
