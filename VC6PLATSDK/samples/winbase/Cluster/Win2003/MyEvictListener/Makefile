!include <disable.mak>

!include <win32.mak>

WARNING_LEVEL=/W4

all: $(OUTDIR) $(OUTDIR)\MyEvictListener.dll

CPP_PROJ=$(WARNING_LEVEL) /WX /I"$(OUTDIR)" /Fo"$(OUTDIR)\\" /Fp"$(OUTDIR)\MyEvictListener.pch" /Fd"$(OUTDIR)\\" /FD /c
CPP_ALL=$(cc) $(cflags) $(cvarsdll) $(cdebug) $(CPP_PROJ)
MIDL_ALL=MIDL /robust /nologo /error all /D "MIDL_PASS" /out $(OUTDIR) /win32

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\StdAfx.obj : StdAfx.cpp
    $(CPP_ALL) StdAfx.cpp

$(OUTDIR)\Dll.obj : Dll.cpp
    $(CPP_ALL) Dll.cpp

$(OUTDIR)\MyEvictListener.obj : MyEvictListener.cpp
    $(CPP_ALL) MyEvictListener.cpp

$(OUTDIR)\MyEvictListener.res : MyEvictListener.rc
    rc -r -fo $(OUTDIR)\MyEvictListener.res /i $(OUTDIR) MyEvictListener.rc 

$(OUTDIR)\MyEvictListener.dll : \
                                $(OUTDIR)\StdAfx.obj            \
                                $(OUTDIR)\Dll.obj               \
                                $(OUTDIR)\MyEvictListener.obj   \
                                MyEvictListener.def              \
                                $(OUTDIR)\MyEvictListener.res
   $(link) $(linkdebug) $(dlllflags) \
   $(OUTDIR)\MyEvictListener.obj     \
   $(OUTDIR)\Dll.obj                 \
   $(OUTDIR)\MyEvictListener.res     \
   -def:MyEvictListener.def          \
   -out:$(OUTDIR)\MyEvictListener.dll

clean:
   $(CLEANUP)

