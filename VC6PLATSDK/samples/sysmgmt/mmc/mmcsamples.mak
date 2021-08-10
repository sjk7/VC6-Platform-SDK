

!include <disable.mak>

SDKPROJ =SysMgmt\MMC\$(samplename)

!include <sdkpropbld.mak>

#--------------------------------------------------------------
# see if we are asked for a cleanup or build
#
!if "$(CLEAN)" == "1"
$(SDKPROJ): Clean
!else
$(SDKPROJ): All
!endif


#--------------------------------------------------------------
# check for supported platforms
#
!if "$(CPU)" != "i386"
!error "Sample is not supported for this platform"
!endif

#--------------------------------------------------------------
# use ansi for WinMe platform
ansi=$(ANSI)
!if "$(TARGETOS)" == "WIN95"
ansi=1
!endif


#--------------------------------------------------------------
# pick a proper configuration
#

PlatformModifier=Win32

!if "$(ansi)" == "1"
PlatformModifier=Win32 Ansi
!endif

!if "$(NODEBUG)" == "1"
CFG="$(samplename) - $(PlatformModifier) Release"
!else
CFG="$(samplename) - $(PlatformModifier) Debug"
!endif


makeopts = $(makeopts) CFG=$(CFG) 

#--------------------------------------------------------------
# build the project
#
All::
	$(MAKE) -nologo /$(MAKEFLAGS) $(makeopts) -f"$(samplename).mak" 

#--------------------------------------------------------------
# cleanup directory
#
Clean::
	@echo *** cleanup ***
	-del /q .\Ansi_debug\.
	-del /q .\Ansi_release\.
	-del /q .\Debug\.
	-del /q .\Release\.

