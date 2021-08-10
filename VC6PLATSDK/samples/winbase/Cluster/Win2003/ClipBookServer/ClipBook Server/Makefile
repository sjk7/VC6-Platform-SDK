!include <disable.mak>

!include <win32.mak>

MSC_WARNING_LEVEL=/W4

all: $(OUTDIR) "$(OUTDIR)\ClipBook Server.dll"

CPP_PROJ=/W4 /WX /I"$(OUTDIR)" /Fo"$(OUTDIR)\\" /Fp"$(OUTDIR)\ClipBook Server.pch" /Fd"$(OUTDIR)\\" /FD /c
CPP_ALL=$(cc) $(cflags) $(cvarsdll) $(cdebug) $(CPP_PROJ)
MIDL_ALL=MIDL /robust /nologo /error all /D "MIDL_PASS" /out $(OUTDIR) /win32

$(OUTDIR) :
   if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

MgdResource.h : MgdResource.idl
   $(MIDL_ALL) /tlb MgdResource.tlb /h MgdResource.h MgdResource.idl

MgdResource_i.c: MgdResource.h

"$(OUTDIR)\ClRes.obj" : ClRes.cpp MgdResource.h MgdResource_i.c
   $(CPP_ALL) ClRes.cpp

"$(OUTDIR)\StringUtils.obj" : StringUtils.cpp
   $(CPP_ALL) StringUtils.cpp

"$(OUTDIR)\ClipBook Server.obj" : "ClipBook Server.cpp"
   $(CPP_ALL) "ClipBook Server.cpp"

$(OUTDIR)\CMgdClusCfgInit.obj : CMgdClusCfgInit.cpp CMgdClusCfgInit.h
   $(CPP_ALL) CMgdClusCfgInit.cpp

$(OUTDIR)\CMgdResType.obj : CMgdResType.cpp CMgdResType.h
   $(CPP_ALL) CMgdResType.cpp

"$(OUTDIR)\ClipBook Server.res" : "ClipBook Server.rc" MgdResource.h
    rc -r -fo "$(OUTDIR)\ClipBook Server.res" /i $(OUTDIR) "ClipBook Server.rc"

"$(OUTDIR)\ClipBook Server.dll" : \
                                    $(OUTDIR)\ClRes.obj                 \
                                    $(OUTDIR)\StringUtils.obj           \
                                    "$(OUTDIR)\ClipBook Server.obj"     \
                                    $(OUTDIR)\CMgdClusCfgInit.obj       \
                                    $(OUTDIR)\CMgdResType.obj           \
                                    "ClipBook Server.def"               \
                                    "$(OUTDIR)\ClipBook Server.res"
   $(link) $(linkdebug) $(dlllflags) \
   $(OUTDIR)\ClRes.obj               \
   $(OUTDIR)\StringUtils.obj         \
   "$(OUTDIR)\ClipBook Server.obj"   \
   $(OUTDIR)\CMgdClusCfgInit.obj     \
   $(OUTDIR)\CMgdResType.obj         \
   "$(OUTDIR)\ClipBook Server.res"   \
   Clusapi.lib                       \
   ResUtils.lib                      \
   "-def:ClipBook Server.def"        \
   "-out:$(OUTDIR)\ClipBook Server.dll"

clean:
   $(CLEANUP)

