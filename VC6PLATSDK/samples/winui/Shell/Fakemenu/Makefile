!include <win32.mak>

Proj = FakeMenu

LinkObjs = $(Proj).obj $(Proj).res

all: $(Proj).exe

$(Proj).res: $(Proj).rc $(Proj).h
    $(rc) $(rcflags) $(rcvars) $(Proj).rc

$(Proj).obj: $(Proj).c $(Proj).h
    $(cc) $(cflags) $(cvars) $(cdebug) $(Proj).c

$(Proj).exe: $(LinkObjs)
    $(link) $(linkdebug) $(guiflags) -out:$@ $(LinkObjs) $(guilibs)

clean:
    -if exist $(Proj).obj del $(Proj).obj
    -if exist $(Proj).res del $(Proj).res
    -if exist $(Proj).exe del $(Proj).exe
    -if exist $(Proj).pdb del $(Proj).pdb
    -if exist vc60.pdb del vc60.pdb
