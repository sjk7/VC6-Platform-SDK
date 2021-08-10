#
# Copyright Microsoft Corp, 1997-1999
# Windows Platform SDK
#
!include <Win32.mak>

#
# All VB Projects in the directory
#
ALL :  sdkrasdial.exe

#
# Project RASDIAL.VBP builds SDKRASDIAL.EXE
#
sdkrasdial.exe :  \
    RasDial.frm \
    RasDial.bas \
    rasdial.vbp
    $(bc) rasdial.vbp $(bc_exe) /out comp.log
    @type comp.log
    @del comp.log
