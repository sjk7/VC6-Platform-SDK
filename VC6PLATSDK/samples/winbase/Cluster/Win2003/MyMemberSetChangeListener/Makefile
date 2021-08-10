!include <disable.mak>

!include <win32.mak>

WARNING_LEVEL=/W4

all: $(OUTDIR) $(OUTDIR)\MyMemberSetChangeListener.dll

CPP_PROJ=$(WARNING_LEVEL) /WX /I"$(OUTDIR)" /Fo"$(OUTDIR)\\" /Fp"$(OUTDIR)\MyMemberSetChangeListener.pch" /Fd"$(OUTDIR)\\" /FD /c
CPP_ALL=$(cc) $(cflags) $(cvarsdll) $(cdebug) $(CPP_PROJ)
MIDL_ALL=MIDL /robust /nologo /error all /D "MIDL_PASS" /out $(OUTDIR) /win32

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\StdAfx.obj : StdAfx.cpp
    $(CPP_ALL) StdAfx.cpp

$(OUTDIR)\Dll.obj : Dll.cpp
    $(CPP_ALL) Dll.cpp

$(OUTDIR)\MyMemberSetChangeListener.obj : MyMemberSetChangeListener.cpp
    $(CPP_ALL) MyMemberSetChangeListener.cpp

$(OUTDIR)\MyMemberSetChangeListener.res : MyMemberSetChangeListener.rc
    rc -r -fo $(OUTDIR)\MyMemberSetChangeListener.res /i $(OUTDIR) MyMemberSetChangeListener.rc 

$(OUTDIR)\MyMemberSetChangeListener.dll : \
                                $(OUTDIR)\StdAfx.obj            \
                                $(OUTDIR)\Dll.obj               \
                                $(OUTDIR)\MyMemberSetChangeListener.obj  \
                                MyMemberSetChangeListener.def            \
                                $(OUTDIR)\MyMemberSetChangeListener.res
   $(link) $(linkdebug) $(dlllflags) \
   $(OUTDIR)\MyMemberSetChangeListener.obj     \
   $(OUTDIR)\Dll.obj                 \
   $(OUTDIR)\MyMemberSetChangeListener.res     \
   -def:MyMemberSetChangeListener.def          \
   -out:$(OUTDIR)\MyMemberSetChangeListener.dll

clean:
   $(CLEANUP)

