#
# Copyright Microsoft Corp, 1997-1999
# Windows Platform SDK
#
!include <Win32.mak>

#
# All VB Projects in the directory
#
ALL :  RasEnumEntries.exe

#
# Project RASENUMENTRIES.VBP builds RASENUMENTRIES.EXE
#
RasEnumEntries.exe :  \
    RasEnumEntries.frm \
    RasEnumEntries.bas \
    rasenumentries.vbp
    $(bc) rasenumentries.vbp $(bc_exe) /out comp.log
    @type comp.log
    @del comp.log
