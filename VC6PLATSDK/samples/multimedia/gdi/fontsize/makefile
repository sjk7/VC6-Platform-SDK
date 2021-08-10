!include <win32.mak>

Proj = Fontsize

LinkObjs = $(Proj).obj

all: $(Proj).exe

$(Proj).obj: $(Proj).c
    $(cc) $(cflags) $(cvars) $(cdebug) $(Proj).c

$(Proj).exe: $(LinkObjs)
    $(link) $(linkdebug) $(guiflags) -out:$@ $(LinkObjs) $(guilibs)

clean:
    -del $(Proj).exe
    -del $(Proj).obj
