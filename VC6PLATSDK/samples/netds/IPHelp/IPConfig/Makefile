! include <ntwin32.mak>

# define these if you want a debug version
#PDB = ipconfig.pdb
#CDEBUG= -Zi -Fd"$(PDB)"
#LDEBUG = -debug:full

LIBS = kernel32.lib libcmt.lib wsock32.lib iphlpapi.lib

.cpp.obj:
	$(cc) $(cdebug) $(cflags) $(cvarsmt) $*.cpp

all:ipconfig.exe 

ipconfig.exe:ipconfig.obj
	$(link) $(ldebug) $(conlflags) -out:$*.exe $*.obj user32.lib $(conlibsmt) $(LIBS)

#
# uncomment the line below for a debug build
#	-pdb:$(PDB)  \
	
clean:
	-del *.obj

cleanall:clean
	-del *.exe
