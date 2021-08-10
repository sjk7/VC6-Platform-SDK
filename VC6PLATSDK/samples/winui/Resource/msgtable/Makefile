!include <Win32.Mak>

all: MsgTest.Exe

MsgTest.Exe: $*.c Messages.h Messages.Dll
  $(cc) $(cflags) $(cdebug) $(cvarsDll) $*.c
  $(link) $(ldebug) $(conlflags) -out:$*.Exe $*.Obj $(conlibsDll) \
      user32.lib

Messages.Dll: $*.Res
  $(link) $(lflags) -base:0x60000000 -machine:$(CPU) -Dll -noentry \
    -out:$*.Dll $*.Res

Messages.h: Messages.Rc

Messages.Rc: Messages.Mc
  mc $*.Mc

.Rc.Res:
    $(rc) -r -fo $*.Res $*.Rc
