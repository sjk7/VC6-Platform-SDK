!include <disable.mak>

!include <win32.mak>

WARNING_LEVEL=/W4

all: $(OUTDIR) $(OUTDIR)\MyCapabilities.dll

CPP_PROJ=$(WARNING_LEVEL) /WX /I"$(OUTDIR)" /Fo"$(OUTDIR)\\" /Fp"$(OUTDIR)\MyCapabilities.pch" /Fd"$(OUTDIR)\\" /FD /c
CPP_ALL=$(cc) $(cflags) $(cvarsdll) $(cdebug) $(CPP_PROJ)
MIDL_ALL=MIDL /robust /nologo /error all /D "MIDL_PASS" /out $(OUTDIR) /win32

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\StdAfx.obj : StdAfx.cpp
    $(CPP_ALL) StdAfx.cpp

$(OUTDIR)\Dll.obj : Dll.cpp
    $(CPP_ALL) Dll.cpp

$(OUTDIR)\MyCapabilities.obj : MyCapabilities.cpp
    $(CPP_ALL) MyCapabilities.cpp

$(OUTDIR)\MyCapabilities.res : MyCapabilities.rc
    rc -r -fo $(OUTDIR)\MyCapabilities.res /i $(OUTDIR) MyCapabilities.rc 

$(OUTDIR)\MyCapabilities.dll : \
                                $(OUTDIR)\StdAfx.obj            \
                                $(OUTDIR)\Dll.obj               \
                                $(OUTDIR)\MyCapabilities.obj    \
                                MyCapabilities.def              \
                                $(OUTDIR)\MyCapabilities.res
   $(link) $(linkdebug) $(dlllflags) \
   $(OUTDIR)\MyCapabilities.obj      \
   $(OUTDIR)\Dll.obj                 \
   $(OUTDIR)\MyCapabilities.res      \
   -def:MyCapabilities.def           \
   -out:$(OUTDIR)\MyCapabilities.dll

clean:
   $(CLEANUP)

