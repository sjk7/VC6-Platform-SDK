!include <disable.mak>

!include <win32.mak>

MSC_WARNING_LEVEL=/W4

all: $(OUTDIR) "$(OUTDIR)\ClipBook ServerEx.dll"

CPP_PROJ=/W4 /WX /I"$(OUTDIR)" /GX /D "_AFXDLL" /Fo"$(OUTDIR)\\" /Fp"$(OUTDIR)\ClipBook ServerEx.pch" /Fd"$(OUTDIR)\\" /FD /c
CPP_ALL=$(cc) $(cflags) $(cvarsdll) $(cdebug) $(CPP_PROJ)
MIDL_ALL=MIDL /robust /nologo /error all /D "MIDL_PASS" /mktyplib203 /win32 /out $(OUTDIR)

$(OUTDIR) :
   if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

ExtObjID.h : ExtObjID.idl
   $(MIDL_ALL) /tlb ExtObjID.tlb /h ExtObjID.h /win32 ExtObjID.idl

"$(OUTDIR)\BasePage.obj" : BasePage.cpp
   $(CPP_ALL) BasePage.cpp

"$(OUTDIR)\ClipBook ServerEx.obj" : "ClipBook ServerEx.cpp"
   $(CPP_ALL) "ClipBook ServerEx.cpp"

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

"$(OUTDIR)\ClipBook ServerEx.res" : "ClipBook ServerEx.rc" ExtObjID.h
    rc -r -d "_AFXDLL" -fo "$(OUTDIR)\ClipBook ServerEx.res" /i $(OUTDIR) "ClipBook ServerEx.rc" 

"$(OUTDIR)\ClipBook ServerEx.dll" :                                         \
                                        $(OUTDIR)\StdAfx.obj                \
                                        $(OUTDIR)\BasePage.obj              \
                                        "$(OUTDIR)\ClipBook ServerEx.obj"   \
                                        $(OUTDIR)\DDxDDV.obj                \
                                        $(OUTDIR)\ExtObj.obj                \
                                        $(OUTDIR)\ExtObjData.obj            \
                                        $(OUTDIR)\PropList.obj              \
                                        $(OUTDIR)\RegExt.obj                \
                                        $(OUTDIR)\ResProp.obj               \
                                        "ClipBook ServerEx.def"             \
                                        "$(OUTDIR)\ClipBook ServerEx.res"
   $(link) $(linkdebug) $(dlllflags) \
   $(OUTDIR)\StdAfx.obj             \
   $(OUTDIR)\BasePage.obj           \
   "$(OUTDIR)\ClipBook ServerEx.obj" \
   "$(OUTDIR)\ClipBook ServerEx.res" \
   $(OUTDIR)\DDxDDV.obj             \
   $(OUTDIR)\ExtObj.obj             \
   $(OUTDIR)\ExtObjData.obj         \
   $(OUTDIR)\PropList.obj           \
   $(OUTDIR)\RegExt.obj             \
   $(OUTDIR)\ResProp.obj            \
   Clusapi.lib                      \
   "-def:ClipBook ServerEx.def"     \
   "-out:$(OUTDIR)\ClipBook ServerEx.dll"

clean:
   $(CLEANUP)

