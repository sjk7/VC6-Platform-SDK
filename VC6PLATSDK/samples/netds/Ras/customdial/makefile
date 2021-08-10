#THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
#ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
#THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
#PARTICULAR PURPOSE.
#
#Copyright (C) 2000 Microsoft Corporation.  All Rights Reserved.

TARGETOS=BOTH
APPVER=5.0

include <win32.mak>

LIBS = kernel32.lib user32.lib advapi32.lib rasapi32.lib

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.cpp

all:customdial.dll

customdial.dll:Customdial.obj customdial.res
    $(link) $(ldebug) $(dlllflags) -def:customdial.def -out:$*.dll $** $(LIBS)

customdial.res: customdial.rc
    $(rc) $(rcflags) $(rcvars)  customdial.rc

clean:
	-del *.obj
        -del *.pdb
        -del *.ilk
 	-del *.res

cleanall:clean
	-del *.exp
	-del *.lib
	-del *.dll
