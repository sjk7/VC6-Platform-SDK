#
# Copyright Microsoft Corp, 1997-1999
# Windows Platform SDK
#
!include <Win32.mak>

#
# All VB Projects in the directory
#
ALL :  RasEnumConnections.exe

#
# Project RASENUMCONNECTIONS.VBP builds RASENUMCONNECTIONS.EXE
#
RasEnumConnections.exe :  \
    RasEnumConnections.frm \
    RasEnumConnections.bas \
    rasenumConnections.vbp
    $(bc) rasenumConnections.vbp $(bc_exe) /out comp.log
    @type comp.log
    @del comp.log
