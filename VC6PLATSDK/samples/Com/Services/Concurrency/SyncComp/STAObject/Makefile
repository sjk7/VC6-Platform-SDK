!include <win32.mak>

PROJ=STAObject
ALL : $(OUTDIR) $(OUTDIR)\$(PROJ).dll

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

LINK32_OBJS= \
        $(OUTDIR)\STAObject.obj \
        $(OUTDIR)\STATest.obj \
        $(OUTDIR)\StdAfx.obj \
        $(OUTDIR)\$(PROJ).res

CLEAN :
        $(CLEANUP)

SOURCE=.\$(PROJ).idl


$(OUTDIR)\$(PROJ).tlb  $(OUTDIR)\$(PROJ).h  $(OUTDIR)\$(PROJ)_i.c: 
        midl /tlb $(PROJ).tlb /h $(PROJ).h /iid $(PROJ)_i.c /Oicf /out $(OUTDIR) $(PROJ).idl 

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /D_USRDLL /D_ATL_DLL /D_ATL_MIN_CRT /I$(OUTDIR) $**

$(OUTDIR)\$(PROJ).dll: $(OUTDIR)\$(PROJ).tlb $(LINK32_OBJS)
    $(link) $(ldebug) $(dlllflags) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).dll /def:$(PROJ).def $(LINK32_OBJS) $(olelibs)

$(OUTDIR)\$(PROJ).res:  $(PROJ).rc 
		rc $(rcflags) $(rcvars) -Fo $(OUTDIR)\$(PROJ).res /I$(OUTDIR) $(PROJ).rc

