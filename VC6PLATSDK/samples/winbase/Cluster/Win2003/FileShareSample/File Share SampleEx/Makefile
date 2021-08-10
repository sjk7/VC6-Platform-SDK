!include <disable.mak>

!include <win32.mak>

MSC_WARNING_LEVEL=/W4

all: $(OUTDIR) "$(OUTDIR)\File Share SampleEx.dll"

CPP_PROJ=/W4 /WX /I"$(OUTDIR)" /GX /D "_AFXDLL" /Fo"$(OUTDIR)\\" /Fp"$(OUTDIR)\File Share SampleEx.pch" /Fd"$(OUTDIR)\\" /FD /c
CPP_ALL=$(cc) $(cflags) $(cvarsdll) $(cdebug) $(CPP_PROJ)
MIDL_ALL=MIDL /robust /nologo /error all /D "MIDL_PASS" /mktyplib203 /win32 /out $(OUTDIR)

$(OUTDIR) :
   if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

ExtObjID.h : ExtObjID.idl
   $(MIDL_ALL) /tlb ExtObjID.tlb /h ExtObjID.h /win32 ExtObjID.idl

"$(OUTDIR)\BasePage.obj" : BasePage.cpp
   $(CPP_ALL) BasePage.cpp

"$(OUTDIR)\File Share SampleEx.obj" : "File Share SampleEx.cpp"
   $(CPP_ALL) "File Share SampleEx.cpp"

"$(OUTDIR)\DDxDDV.obj" : DDxDDV.cpp
   $(CPP_ALL) DDxDDV.cpp

"$(OUTDIR)\ExtObj.obj" : ExtObj.cpp
   $(CPP_ALL) ExtObj.cpp

"$(OUTDIR)\ExtObjData.obj" : ExtObjData.cpp
   $(CPP_ALL) ExtObjData.cpp

"$(OUTDIR)\PropList.obj" : PropList.cpp
   $(CPP_ALL) PropList.cpp

"$(OUTDIR)\RegExt.obj" : RegExt.cpp
   $(CPP_ALL) RegExt.cpp

"$(OUTDIR)\ResProp.obj" : ResProp.cpp
   $(CPP_ALL) ResProp.cpp

"$(OUTDIR)\StdAfx.obj" : StdAfx.cpp ExtObjID.h
   $(CPP_ALL) StdAfx.cpp

"$(OUTDIR)\File Share SampleEx.res" : "File Share SampleEx.rc" ExtObjID.h
    rc -r -d "_AFXDLL" -fo "$(OUTDIR)\File Share SampleEx.res" /i $(OUTDIR) "File Share SampleEx.rc" 

"$(OUTDIR)\File Share SampleEx.dll" :                                       \
                                        $(OUTDIR)\StdAfx.obj                \
                                        $(OUTDIR)\BasePage.obj              \
                                        "$(OUTDIR)\File Share SampleEx.obj" \
                                        $(OUTDIR)\DDxDDV.obj                \
                                        $(OUTDIR)\ExtObj.obj                \
                                        $(OUTDIR)\ExtObjData.obj            \
                                        $(OUTDIR)\PropList.obj              \
                                        $(OUTDIR)\RegExt.obj                \
                                        $(OUTDIR)\ResProp.obj               \
                                        "File Share SampleEx.def"           \
                                        "$(OUTDIR)\File Share SampleEx.res"
   $(link) $(linkdebug) $(dlllflags) \
   $(OUTDIR)\StdAfx.obj             \
   $(OUTDIR)\BasePage.obj           \
   $(OUTDIR)\DDxDDV.obj             \
   $(OUTDIR)\ExtObj.obj             \
   $(OUTDIR)\ExtObjData.obj         \
   "$(OUTDIR)\File Share SampleEx.obj" \
   "$(OUTDIR)\File Share SampleEx.res" \
   $(OUTDIR)\PropList.obj           \
   $(OUTDIR)\RegExt.obj             \
   $(OUTDIR)\ResProp.obj            \
   Clusapi.lib                      \
   "-def:File Share SampleEx.def"     \
   "-out:$(OUTDIR)\File Share SampleEx.dll"

clean:
   $(CLEANUP)

