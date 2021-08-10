!include <disable.mak>

!include <win32.mak>

MSC_WARNING_LEVEL=/W4

all: $(OUTDIR) "$(OUTDIR)\File Share Sample.dll"

CPP_PROJ=/W4 /WX /I"$(OUTDIR)" /Fo"$(OUTDIR)\\" /Fp"$(OUTDIR)\File Share Sample.pch" /Fd"$(OUTDIR)\\" /FD /c
CPP_ALL=$(cc) $(cflags) $(cvarsdll) $(cdebug) $(CPP_PROJ)
MIDL_ALL=MIDL /robust /nologo /error all /D "MIDL_PASS" /out $(OUTDIR)

$(OUTDIR) :
   if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

"$(OUTDIR)\ClRes.obj" : ClRes.cpp
   $(CPP_ALL) ClRes.cpp

"$(OUTDIR)\StringUtils.obj" : StringUtils.cpp
   $(CPP_ALL) StringUtils.cpp

"$(OUTDIR)\File Share Sample.obj" : "File Share Sample.cpp"
   $(CPP_ALL) "File Share Sample.cpp"

"$(OUTDIR)\File Share Sample.res" : "File Share Sample.rc"
    rc -r -fo "$(OUTDIR)\File Share Sample.res" /i $(OUTDIR) "File Share Sample.rc"

"$(OUTDIR)\File Share Sample.dll" : \
                                        $(OUTDIR)\ClRes.obj                 \
                                        $(OUTDIR)\StringUtils.obj           \
                                        "$(OUTDIR)\File Share Sample.obj"   \
                                        "File Share Sample.def"             \
                                        "$(OUTDIR)\File Share Sample.res"
   $(link) $(linkdebug) $(dlllflags) \
   $(OUTDIR)\ClRes.obj               \
   $(OUTDIR)\StringUtils.obj         \
   "$(OUTDIR)\File Share Sample.obj" \
   "$(OUTDIR)\File Share Sample.res" \
   Clusapi.lib                       \
   NetApi32.lib                      \
   OleAut32.lib                      \
   ResUtils.lib                      \
   "-def:File Share Sample.def"      \
   "-out:$(OUTDIR)\File Share Sample.dll"

clean:
   $(CLEANUP)

