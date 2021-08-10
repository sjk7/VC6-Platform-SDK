! include <win32.mak>

LIBS = kernel32.lib libcmt.lib wsock32.lib iphlpapi.lib

.cpp.obj:
	$(cc) $(cdebug) $(cflags) $(cvarsmt) $*.cpp
all:ipchange.exe 

ipchange.exe:ipchange.obj
	$(link) $(ldebug) $(conlflags)  -out:$*.exe $*.obj user32.lib $(conlibsmt) $(LIBS)


clean:
	-del *.obj

cleanall:clean
	-del *.exe
