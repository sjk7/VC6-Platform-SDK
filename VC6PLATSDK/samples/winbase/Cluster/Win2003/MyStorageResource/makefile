!include <disable.mak>

!include <win32.mak>

INCLUDE=$(INCLUDE);$(OUTDIR)

all: $(OUTDIR) $(OUTDIR)\MyStorageResource.dll

CPP_PROJ=/W4 /WX /I"$(OUTDIR)" /Fo"$(OUTDIR)\\" /Fp"$(OUTDIR)\MyStorageResource.pch" /Fd"$(OUTDIR)\\" /FD /c
CPP_ALL=$(cc) $(cflags) $(cvarsdll) $(cdebug) $(CPP_PROJ)
MIDL_ALL=MIDL /robust /nologo /error all /D "MIDL_PASS" /out $(OUTDIR) /win32

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

MyStorageResource.h : MyStorageResource.idl
    $(MIDL_ALL) /tlb MyStorageResource.tlb /h MyStorageResource.h MyStorageResource.idl

MyStorageResource_i.c : MyStorageResource.h

$(OUTDIR)\stdafx.obj : stdafx.cpp MyStorageResource.h MyStorageResource_i.c
    $(CPP_ALL) StdAfx.cpp

$(OUTDIR)\CClusterUtils.obj : CClusterUtils.cpp
    $(CPP_ALL) CClusterUtils.cpp

$(OUTDIR)\CEnumStorageResource.obj : CEnumStorageResource.cpp
    $(CPP_ALL) CEnumStorageResource.cpp

$(OUTDIR)\CPartitionInfo.obj : CPartitionInfo.cpp
    $(CPP_ALL) CPartitionInfo.cpp

$(OUTDIR)\CMgdClusCfgInit.obj : CMgdClusCfgInit.cpp
    $(CPP_ALL) CMgdClusCfgInit.cpp

$(OUTDIR)\CStorageResource.obj : CStorageResource.cpp
    $(CPP_ALL) CStorageResource.cpp

$(OUTDIR)\CStorageResType.obj : CStorageResType.cpp
    $(CPP_ALL) CStorageResType.cpp

$(OUTDIR)\MyStorageResource.obj : MyStorageResource.cpp
    $(CPP_ALL) MyStorageResource.cpp

$(OUTDIR)\PropList.obj : PropList.cpp
    $(CPP_ALL) PropList.cpp

$(OUTDIR)\StringUtils.obj : StringUtils.cpp
    $(CPP_ALL) StringUtils.cpp

$(OUTDIR)\WMIHelpers.obj : WMIHelpers.cpp 
    $(CPP_ALL) WMIHelpers.cpp

$(OUTDIR)\SIndexedDisk.obj : SIndexedDisk.cpp
    $(CPP_ALL) SIndexedDisk.cpp

$(OUTDIR)\MyStorageResource.res : MyStorageResource.rc
    rc -r -fo $(OUTDIR)\MyStorageResource.res /i $(OUTDIR) MyStorageResource.rc 

$(OUTDIR)\MyStorageResource.dll : \
                                        $(OUTDIR)\StdAfx.obj                    \
                                        $(OUTDIR)\CClusterUtils.obj             \
                                        $(OUTDIR)\CEnumStorageResource.obj      \
                                        $(OUTDIR)\CPartitionInfo.obj            \
                                        $(OUTDIR)\CMgdClusCfgInit.obj           \
                                        $(OUTDIR)\CStorageResource.obj          \
                                        $(OUTDIR)\CStorageResType.obj           \
                                        $(OUTDIR)\MyStorageResource.obj         \
                                        $(OUTDIR)\PropList.obj                  \
                                        $(OUTDIR)\StringUtils.obj               \
                                        $(OUTDIR)\WMIHelpers.obj                \
                                        $(OUTDIR)\MyStorageResource.res         \
                                        $(OUTDIR)\SIndexedDisk.obj              \
                                        MyStorageResource.def
    $(link) $(linkdebug) $(dlllflags)   \
    $(OUTDIR)\CClusterUtils.obj         \
    $(OUTDIR)\CEnumStorageResource.obj  \
    $(OUTDIR)\CMgdClusCfgInit.obj       \
    $(OUTDIR)\CPartitionInfo.obj        \
    $(OUTDIR)\CStorageResource.obj      \
    $(OUTDIR)\CStorageResType.obj       \
    $(OUTDIR)\MyStorageResource.obj     \
    $(OUTDIR)\PropList.obj              \
    $(OUTDIR)\StringUtils.obj           \
    $(OUTDIR)\StdAfx.obj                \
    $(OUTDIR)\WMIHelpers.obj            \
    $(OUTDIR)\MyStorageResource.res     \
    $(OUTDIR)\SIndexedDisk.obj          \
    uuid.lib                            \
    Clusapi.lib                         \
    WbemUUID.lib                        \
    ResUtils.lib                        \
    -def:MyStorageResource.def          \
    -out:$(OUTDIR)\MyStorageResource.dll

clean:
   $(CLEANUP)

