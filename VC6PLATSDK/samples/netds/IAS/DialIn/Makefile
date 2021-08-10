APPVER=5.01

!include <win32.mak>

proj=dialin

all: $(proj).dll

$(proj).obj: $(proj).c
        $(cc) $(cflags) $(cvarsdll) $(cdebug) $(proj).c

$(proj).dll: $(proj).obj
        $(link) -dll -def:$(proj).def -out:$@ $** rassapi.lib

clean:
        del $(proj).dll
        del $(proj).lib
        del $(proj).exp
        del $(proj).obj
