TARGETOS=BOTH
!include <win32.mak>

objs=qoslist.obj

all: qoslist.exe

# Update the resource if necessary

# Update the object file if necessary

.cpp.obj: 
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.cpp

# Update the executable file if necessary, and if so, add the resource back in.

qoslist.exe: $(objs)  
    $(link) $(linkdebug) $(conlflags) -out:qoslist.exe $(objs) $(conlibsmt) ws2_32.lib qosname.lib


clean:
	del *.obj
	del *.exe
