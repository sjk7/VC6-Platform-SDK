Proj = eap

!IF "$(TARGETOS)" == "WINNT"

!include <win32.mak>

cflags = $(cflags) -DUNICODE

LIBS=rtutils.lib     \
     user32.lib      \
     advapi32.lib    \
     kernel32.lib    \
     netapi32.lib    \
     ole32.lib       \
     oleaut32.lib    \
     uuid.lib        \
       
OBJS=$(Proj).obj ceapcfg.obj exports.obj $(Proj).res

all: $(Proj).dll

$(Proj).dll: $(OBJS)
    $(link) $(ldebug) $(dlllflags) $(LIBS) \
    /DEF:$(Proj).def /OUT:$(Proj).dll $**

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.cpp

$(Proj).res: $(Proj).rc
    rc -r $*.rc

!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT Platform
!ENDIF
