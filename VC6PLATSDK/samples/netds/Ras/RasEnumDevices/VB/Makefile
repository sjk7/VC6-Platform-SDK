#
# Copyright Microsoft Corp, 1997-1999
# Windows Platform SDK
#
!include <Win32.mak>

#
# All VB Projects in the directory
#
ALL :  RasEnumDevices.exe

#
# Project RASENUMDEVICES.VBP builds RASENUMDEVICES.EXE
#
RasEnumDevices.exe :  \
    RasEnumDevices.frm \
    RasEnumDevices.bas \
    rasenumdevices.vbp
    $(bc) rasenumdevices.vbp $(bc_exe) /out comp.log
    @type comp.log
    @del comp.log
