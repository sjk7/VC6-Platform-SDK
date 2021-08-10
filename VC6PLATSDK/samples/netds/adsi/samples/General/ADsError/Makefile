#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>


all:	$(OUTDIR) $(OUTDIR)\ADsError.h $(OUTDIR)\ADsError_i.c $(OUTDIR)\ADsError.tlb $(OUTDIR)\ADsError.dll

$(OUTDIR)\ADsError.dll:	 $(OUTDIR) $(OUTDIR)\ADsError.obj $(OUTDIR)\IADsError.obj $(OUTDIR)\StdAfx.obj $(OUTDIR)\ADsError.res  
	$(link) $(ldebug) /OUT:$(OUTDIR)\ADsError.dll $(guilflags) $(dlllflags) /PDB:$(OUTDIR)\ADsError.pdb /MACHINE:$(CPU) /def:ADsError.def /implib:$(OUTDIR)\ADsError.lib $(OUTDIR)\ADsError.obj $(OUTDIR)\IADsError.obj $(OUTDIR)\StdAfx.obj $(OUTDIR)\ADsError.res kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib activeds.lib 
	
$(OUTDIR)\ADsError.h $(OUTDIR)\ADsError_i.c $(OUTDIR)\ADsError.tlb : ADsError.idl
	midl.exe /h $(OUTDIR)\ADsError.h /iid $(OUTDIR)\ADsError_i.c /tlb $(OUTDIR)\ADsError.tlb ADsError.idl


$(OUTDIR)\ADsError.obj:	ADsError.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fp$(OUTDIR)\ADsError.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) ADsError.cpp

$(OUTDIR)\IADsError.obj:	IADsError.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fp$(OUTDIR)\IADsError.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) IADsError.cpp

$(OUTDIR)\StdAfx.obj:	StdAfx.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fp$(OUTDIR)\StdAfx.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) StdAfx.cpp

$(OUTDIR)\ADsError.res:	
	$(rc) $(rcvars) $(rcflags) /Fo$(OUTDIR)\ADsError.res /I$(OUTDIR) ADsError.rc 


#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
