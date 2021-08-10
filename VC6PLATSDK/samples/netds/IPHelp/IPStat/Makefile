!include <win32.mak>

# define these if you want a debug version
#PDB = IpStat.pdb
#CDEBUG= -Zi -Fd"$(PDB)"
#LDEBUG = -debug:full

PROJ = IpStat
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

LIBS = kernel32.lib wsock32.lib iphlpapi.lib

.cpp.obj:
	$(cc) $(cdebug) $(cflags) $(cvarsmt) $*.cpp

$(OUTDIR)\$(PROJ).exe:IpStat.obj
     $(link) $(ldebug) $(conlflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe  IpStat.obj $(LIBS)
	
clean:
	$(CLEANUP)
