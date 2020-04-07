!include <win32.mak>

PROJ=ComSyncObject
ALL : $(OUTDIR) $(OUTDIR)\$(PROJ).dll

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

LINK32_OBJS= \
        $(OUTDIR)\ComSyncObject.obj \
        $(OUTDIR)\ComSyncTest.obj \
        $(OUTDIR)\StdAfx.obj \
        $(OUTDIR)\ComSyncObject.res

CLEAN :
        $(CLEANUP)

SOURCE=.\ComSyncObject.idl


$(OUTDIR)\ComSyncObject.tlb  $(OUTDIR)\ComSyncObject.h  $(OUTDIR)\ComSyncObject_i.c: 
        midl /tlb ComSyncObject.tlb /h ComSyncObject.h /iid ComSyncObject_i.c /Oicf /out $(OUTDIR) $(PROJ).idl 

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /D_USRDLL /D_ATL_DLL /D_ATL_MIN_CRT /I$(OUTDIR) $**

$(OUTDIR)\$(PROJ).dll: $(OUTDIR)\ComSyncObject.tlb $(LINK32_OBJS)
    $(link) $(ldebug) $(dlllflags) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).dll /def:$(PROJ).def $(LINK32_OBJS) $(olelibs)

$(OUTDIR)\$(PROJ).res:  $(PROJ).rc 
		rc $(rcflags) $(rcvars) -Fo $(OUTDIR)\$(PROJ).res /I$(OUTDIR) $(PROJ).rc


