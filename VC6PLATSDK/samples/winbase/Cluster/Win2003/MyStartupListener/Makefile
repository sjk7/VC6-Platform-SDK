!include <disable.mak>

!include <win32.mak>

WARNING_LEVEL=/W4

all: $(OUTDIR) $(OUTDIR)\MyStartupListener.dll

CPP_PROJ=$(WARNING_LEVEL) /WX /I"$(OUTDIR)" /Fo"$(OUTDIR)\\" /Fp"$(OUTDIR)\MyStartupListener.pch" /Fd"$(OUTDIR)\\" /FD /c
CPP_ALL=$(cc) $(cflags) $(cvarsdll) $(cdebug) $(CPP_PROJ)
MIDL_ALL=MIDL /robust /nologo /error all /D "MIDL_PASS" /out $(OUTDIR) /win32

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\StdAfx.obj : StdAfx.cpp
    $(CPP_ALL) StdAfx.cpp

$(OUTDIR)\Dll.obj : Dll.cpp
    $(CPP_ALL) Dll.cpp

$(OUTDIR)\MyStartupListener.obj : MyStartupListener.cpp
    $(CPP_ALL) MyStartupListener.cpp

$(OUTDIR)\MyStartupListener.res : MyStartupListener.rc
    rc -r -fo $(OUTDIR)\MyStartupListener.res /i $(OUTDIR) MyStartupListener.rc 

$(OUTDIR)\MyStartupListener.dll : \
                                $(OUTDIR)\StdAfx.obj            \
                                $(OUTDIR)\Dll.obj               \
                                $(OUTDIR)\MyStartupListener.obj   \
                                MyStartupListener.def              \
                                $(OUTDIR)\MyStartupListener.res
   $(link) $(linkdebug) $(dlllflags) \
   $(OUTDIR)\MyStartupListener.obj     \
   $(OUTDIR)\Dll.obj                 \
   $(OUTDIR)\MyStartupListener.res     \
   -def:MyStartupListener.def          \
   -out:$(OUTDIR)\MyStartupListener.dll

clean:
   $(CLEANUP)

