! include <win32.mak>

# define these if you want a debug version

LIBS =  wsock32.lib iphlpapi.lib

.cpp.obj:
	 $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.cpp

all:IpArp.exe 

IpArp.exe:IpArp.obj
	$(link) $(ldebug) $(conlflags) -out:$*.exe $*.obj $(conlibsmt)  $(LIBS)


clean:
	-del *.obj

cleanall:clean
	-del *.exe
