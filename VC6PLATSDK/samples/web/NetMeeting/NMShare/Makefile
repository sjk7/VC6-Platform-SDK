# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1997-2002  Microsoft Corporation.  All Rights Reserved.
#
!if "$(CPU)" == "IA64"
!message Sorry, building this sample for the 64bit Windows Platform is not currently supported
!else

!IF "$(nodebug)" == ""
CFG=nmShare - Win32 Debug
!MESSAGE Building DEBUG version of NMSHARE
!ELSE
CFG=nmShare - Win32 Release
!MESSAGE Building RELEASE version of NMSHARE
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "nmShare - Win32 Release"

OUTDIR=.\Release

ALL : "$(OUTDIR)\nmShare.exe"

CLEAN :
	-@erase "$(OUTDIR)\cConf.obj"
	-@erase "$(OUTDIR)\cHwnd.obj"
	-@erase "$(OUTDIR)\clUtil.obj"
	-@erase "$(OUTDIR)\cmd.obj"
	-@erase "$(OUTDIR)\cMemb.obj"
	-@erase "$(OUTDIR)\cShare.obj"
	-@erase "$(OUTDIR)\debug.obj"
	-@erase "$(OUTDIR)\imsconf2.obj"
	-@erase "$(OUTDIR)\main.obj"
	-@erase "$(OUTDIR)\msg.obj"
	-@erase "$(OUTDIR)\res.res"
	-@erase "$(OUTDIR)\util.obj"
	-@erase "$(OUTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\nmShare.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "STRICT" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(OUTDIR)\nmShare.pch" /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Release/
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(OUTDIR)\res.res" /d "NDEBUG" 
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\nmShare.pdb" /machine:I386\
 /out:"$(OUTDIR)\nmShare.exe" 
LINK32_OBJS= \
	"$(OUTDIR)\cConf.obj" \
	"$(OUTDIR)\cHwnd.obj" \
	"$(OUTDIR)\clUtil.obj" \
	"$(OUTDIR)\cmd.obj" \
	"$(OUTDIR)\cMemb.obj" \
	"$(OUTDIR)\cShare.obj" \
	"$(OUTDIR)\debug.obj" \
	"$(OUTDIR)\imsconf2.obj" \
	"$(OUTDIR)\main.obj" \
	"$(OUTDIR)\msg.obj" \
	"$(OUTDIR)\res.res" \
	"$(OUTDIR)\util.obj"

"$(OUTDIR)\nmShare.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

OUTDIR=.\Debug


ALL : "$(OUTDIR)\nmShare.exe"


CLEAN :
	-@erase "$(OUTDIR)\cConf.obj"
	-@erase "$(OUTDIR)\cHwnd.obj"
	-@erase "$(OUTDIR)\clUtil.obj"
	-@erase "$(OUTDIR)\cmd.obj"
	-@erase "$(OUTDIR)\cMemb.obj"
	-@erase "$(OUTDIR)\cShare.obj"
	-@erase "$(OUTDIR)\debug.obj"
	-@erase "$(OUTDIR)\imsconf2.obj"
	-@erase "$(OUTDIR)\main.obj"
	-@erase "$(OUTDIR)\msg.obj"
	-@erase "$(OUTDIR)\res.res"
	-@erase "$(OUTDIR)\util.obj"
	-@erase "$(OUTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\nmShare.exe"
	-@erase "$(OUTDIR)\nmShare.ilk"
	-@erase "$(OUTDIR)\nmShare.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "STRICT" /D "DEBUG" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(OUTDIR)\nmShare.pch" /YX /Fo"$(OUTDIR)\\"\
 /Fd"$(OUTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(OUTDIR)\res.res" /d "_DEBUG" 
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\nmShare.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)\nmShare.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(OUTDIR)\cConf.obj" \
	"$(OUTDIR)\cHwnd.obj" \
	"$(OUTDIR)\clUtil.obj" \
	"$(OUTDIR)\cmd.obj" \
	"$(OUTDIR)\cMemb.obj" \
	"$(OUTDIR)\cShare.obj" \
	"$(OUTDIR)\debug.obj" \
	"$(OUTDIR)\imsconf2.obj" \
	"$(OUTDIR)\main.obj" \
	"$(OUTDIR)\msg.obj" \
	"$(OUTDIR)\res.res" \
	"$(OUTDIR)\util.obj"

"$(OUTDIR)\nmShare.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<



imsconf2.h : imsconf2.idl "$(OUTDIR)" "$(OUTDIR)"
	midl /client none /server none /ms_ext /c_ext /env win32 /Os  /dlldata\
         $(OUTDIR)\dlldata.rpc /proxy $(OUTDIR)\imsconf2.rpc /header\
         imsconf2.h /iid imsconf2.c imsconf2.idl

"$(OUTDIR)\imsconf2.obj" : imsconf2.c $(OUTDIR)

"$(OUTDIR)\res.res" : res.rc main.ico $(OUTDIR)
	$(RSC) $(RSC_PROJ) res.rc

"$(OUTDIR)\cConf.obj" : cConf.cpp cconf.h clUtil.h cmemb.h cShare.h global.h imsconf2.h precomp.h $(OUTDIR)

"$(OUTDIR)\cHwnd.obj" : cHwnd.cpp cconf.h clUtil.h cmemb.h cShare.h global.h imsconf2.h precomp.h $(OUTDIR)

"$(OUTDIR)\clUtil.obj" : clUtil.cpp cconf.h clUtil.h cmemb.h cShare.h global.h imsconf2.h precomp.h $(OUTDIR)

"$(OUTDIR)\cmd.obj" : cmd.cpp cconf.h clUtil.h cmemb.h cShare.h global.h imsconf2.h precomp.h $(OUTDIR)

"$(OUTDIR)\cMemb.obj" : cMemb.cpp cconf.h clUtil.h cmemb.h cShare.h global.h imsconf2.h precomp.h $(OUTDIR)

"$(OUTDIR)\cShare.obj" : cShare.cpp cconf.h clUtil.h cmemb.h cShare.h global.h imsconf2.h precomp.h $(OUTDIR)

"$(OUTDIR)\debug.obj" : debug.cpp cconf.h clUtil.h cmemb.h cShare.h global.h imsconf2.h precomp.h $(OUTDIR)

"$(OUTDIR)\main.obj" : main.cpp cconf.h clUtil.h cmemb.h cShare.h global.h imsconf2.h precomp.h $(OUTDIR)

"$(OUTDIR)\msg.obj" : msg.cpp cconf.h clUtil.h cmemb.h cShare.h global.h imsconf2.h precomp.h $(OUTDIR)

"$(OUTDIR)\util.obj" : util.cpp cconf.h clUtil.h cmemb.h cShare.h global.h imsconf2.h precomp.h $(OUTDIR)

!endif
