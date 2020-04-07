!if "$(CPU)" == "IA64"
!message Sorry, building this sample for 64bit is not currently supported.
!else
#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = VCAcct
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).dll

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = odbc32.lib shell32.lib advapi32.lib mtxguid.lib mtx.lib

LINK32_OBJS = $(OUTDIR)\stdafx.obj \
              $(OUTDIR)\caccount.obj \
              $(OUTDIR)\account.obj \
              $(OUTDIR)\account.res

$(OUTDIR)\account.h : account.idl
     $(midl) /h $(OUTDIR)\account.h /tlb $(OUTDIR)\account.tlb /iid $(OUTDIR)\account_i.c account.idl

$(OUTDIR)\stdafx.obj:     stdafx.cpp
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /GX /D_USRDLL /D_MBCS /D_WINDLL /I"..\..\include" /Yc"stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) stdafx.cpp

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /W3 /GX /D_USRDLL /D_MBCS /D_WINDLL /I"..\..\include" /Yu"stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I$(OUTDIR) $**

$(OUTDIR)\account.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\account.res /I$(OUTDIR) account.rc

$(OUTDIR)\$(PROJ).dll:   $(OUTDIR)\account.h $(LINK32_OBJS)
     $(link) $(ldebug) $(dlllflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).dll /DEF:account.def  $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

clean:
     $(CLEANUP)

!endif
