# Microsoft Developer Studio Project File - Name="Account" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=Account - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "account.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "account.mak" CFG="Account - Win32 Alpha Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Account - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Account - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Account - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Account - Win32 Alpha Release" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Account - Win32 Alpha Debug" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Account - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0

!IF  "$(CFG)" == "Account - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /Ob2 /I "..\..\include" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /u
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 mtx.lib mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib uuid.lib /nologo /subsystem:windows /dll /pdb:"Release/Vcacct.pdb" /machine:I386 /nodefaultlib:"msvcrt.lib" /out:"Release/Vcacct.dll"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Unicode Release"
# PROP BASE Intermediate_Dir ".\Unicode Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\ReleaseU"
# PROP Intermediate_Dir ".\ReleaseU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_MBCS" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 mtx.lib mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib uuid.lib /nologo /subsystem:windows /dll /pdb:"ReleaseU/vcacct.pdb" /machine:I386 /nodefaultlib:"msvcrt.lib" /out:"ReleaseU/vcacct.dll"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Unicode Debug"
# PROP BASE Intermediate_Dir ".\Unicode Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\DebugU"
# PROP Intermediate_Dir ".\DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_MBCS" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib odbc32.lib uuid.lib /nologo /subsystem:windows /dll /pdb:"DebugU/vcacct.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /out:"DebugU/vcacct.dll"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Account_"
# PROP BASE Intermediate_Dir "Account_"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AlphaRelease"
# PROP Intermediate_Dir "AlphaRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /out:"vcacct.dll"
# ADD LINK32 mtxguid.lib mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /out:"AlphaRelease/Vcacct.dll"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Account0"
# PROP BASE Intermediate_Dir "Account0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AlphaDebug"
# PROP Intermediate_Dir "AlphaDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /MTd /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /MTd /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /out:"..\..\packages\i386\Checked\Vcacct.dll"
# ADD LINK32 mtxguid.lib mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /out:"AlphaDebug/Vcacct.dll"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib odbc32.lib uuid.lib /nologo /subsystem:windows /dll /pdb:"Debug/Vcacct.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /out:"Debug/Vcacct.dll"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Account - Win32 Release"
# Name "Account - Win32 Unicode Release"
# Name "Account - Win32 Unicode Debug"
# Name "Account - Win32 Alpha Release"
# Name "Account - Win32 Alpha Debug"
# Name "Account - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Account.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

DEP_CPP_ACCOU=\
	".\CACCOUNT.H"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	".\STDAFX.H"\
	".\UpdateReceipt.h"\
	
NODEP_CPP_ACCOU=\
	".\Account.h"\
	".\Account_i.c"\
	

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

DEP_CPP_ACCOU=\
	".\CACCOUNT.H"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	".\STDAFX.H"\
	".\UpdateReceipt.h"\
	
NODEP_CPP_ACCOU=\
	".\Account.h"\
	".\Account_i.c"\
	

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Account.def
# End Source File
# Begin Source File

SOURCE=.\Account.idl

!IF  "$(CFG)" == "Account - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Account.idl

BuildCmds= \
	midl Account.idl

"Account.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Account.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Account_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Account.idl

BuildCmds= \
	midl Account.idl

"Account.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Account.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Account_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Account.idl

BuildCmds= \
	midl Account.idl

"Account.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Account.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Account_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Account.idl

BuildCmds= \
	midl Account.idl

"Account.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Account.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Account_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Account.idl

BuildCmds= \
	midl Account.idl

"Account.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Account.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Account_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Account.idl

BuildCmds= \
	midl Account.idl

"Account.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Account.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Account_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Account.rc
# End Source File
# Begin Source File

SOURCE=.\CAccount.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

DEP_CPP_CACCO=\
	".\CACCOUNT.H"\
	".\STDAFX.H"\
	
NODEP_CPP_CACCO=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

DEP_CPP_CACCO=\
	".\CACCOUNT.H"\
	".\STDAFX.H"\
	
NODEP_CPP_CACCO=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GetReceipt.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

DEP_CPP_GETRE=\
	".\GetReceipt.h"\
	".\STDAFX.H"\
	".\UpdateReceipt.h"\
	
NODEP_CPP_GETRE=\
	".\Account.h"\
	

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

DEP_CPP_GETRE=\
	".\GetReceipt.h"\
	".\STDAFX.H"\
	".\UpdateReceipt.h"\
	
NODEP_CPP_GETRE=\
	".\Account.h"\
	

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MoveMoney.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

DEP_CPP_MOVEM=\
	".\GetReceipt.h"\
	".\movemoney.h"\
	".\STDAFX.H"\
	
NODEP_CPP_MOVEM=\
	".\Account.h"\
	

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

DEP_CPP_MOVEM=\
	".\GetReceipt.h"\
	".\movemoney.h"\
	".\STDAFX.H"\
	
NODEP_CPP_MOVEM=\
	".\Account.h"\
	

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

DEP_CPP_STDAF=\
	".\STDAFX.H"\
	
NODEP_CPP_STDAF=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

DEP_CPP_STDAF=\
	".\STDAFX.H"\
	
NODEP_CPP_STDAF=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\UpdateReceipt.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

DEP_CPP_UPDAT=\
	".\STDAFX.H"\
	".\UpdateReceipt.h"\
	
NODEP_CPP_UPDAT=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

DEP_CPP_UPDAT=\
	".\STDAFX.H"\
	".\UpdateReceipt.h"\
	
NODEP_CPP_UPDAT=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CACCOUNT.H
# End Source File
# Begin Source File

SOURCE=.\DLLDATAX.H
# End Source File
# Begin Source File

SOURCE=.\GetReceipt.h
# End Source File
# Begin Source File

SOURCE=.\movemoney.h
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\UpdateReceipt.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\CACCOUNT.RGS
# End Source File
# Begin Source File

SOURCE=.\GetReceipt.rgs
# End Source File
# Begin Source File

SOURCE=.\movemoney.rgs
# End Source File
# Begin Source File

SOURCE=.\UpdateReceipt.rgs
# End Source File
# End Target
# End Project
