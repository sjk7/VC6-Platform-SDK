!if "$(CPU)" == "IA64"
!message Sorry building this sample for 64bit is not currently supported.
!else
#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>


all:	$(OUTDIR) $(OUTDIR)\LogWriter.tlb $(OUTDIR)\LogWriter.h $(OUTDIR)\LogWriter.dll

$(OUTDIR)\LogWriter.dll:	 $(OUTDIR) $(OUTDIR)\dlldatax.obj $(OUTDIR)\LogFile.obj $(OUTDIR)\LogWriter.obj $(OUTDIR)\StdAfx.obj $(OUTDIR)\LogWriter.res  
	$(link) $(ldebug) /OUT:$(OUTDIR)\LogWriter.dll $(guilflags) $(dlllflags) /PDB:$(OUTDIR)\LogWriter.pdb /MACHINE:$(CPU) /def:LogWriter.def /implib:$(OUTDIR)\LogWriter.lib $(OUTDIR)\dlldatax.obj $(OUTDIR)\LogFile.obj $(OUTDIR)\LogWriter.obj $(OUTDIR)\StdAfx.obj $(OUTDIR)\LogWriter.res kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 

$(OUTDIR)\LogWriter.h $(OUTDIR)\LogWriter_i.c $(OUTDIR)\LogWriter.tlb : LogWriter.idl
	midl.exe /h $(OUTDIR)\LogWriter.h /iid $(OUTDIR)\LogWriter_i.c /tlb $(OUTDIR)\LogWriter.tlb LogWriter.idl

$(OUTDIR)\dlldatax.obj:	dlldatax.c
	$(cc) $(cflags) $(cdebug) $(cvarsmt) /GX /Fp$(OUTDIR)\dlldata.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) /D "_UNICODE" /D "_ATL_DLL" dlldatax.c

$(OUTDIR)\LogFile.obj:	LogFile.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsmt) /GX /Fp$(OUTDIR)\LogFile.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) /D "_UNICODE" /D "_ATL_DLL" LogFile.cpp

$(OUTDIR)\LogWriter.obj:	LogWriter.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsmt) /GX /Fp$(OUTDIR)\LogWriter.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) /D "_UNICODE" /D "_ATL_DLL" LogWriter.cpp

$(OUTDIR)\StdAfx.obj:	StdAfx.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsmt) /GX /Fp$(OUTDIR)\StdAfx.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) /D "_UNICODE" /D "_ATL_DLL" StdAfx.cpp

$(OUTDIR)\LogWriter.res:	
	$(rc) $(rcvars) $(rcflags) /Fo$(OUTDIR)\LogWriter.res LogWriter.rc 


#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)

!endif
