#
# Copyright Microsoft Corp, 1997-1999
# Windows Platform SDK
#
!include <Win32.mak>

#
# All VB Projects in the directory
#
ALL :  RasEntry.exe

#
# Project RasEntry.VBP builds RasEntry.EXE
#
RasEntry.exe :  \
    RasEntry.frm \
    RasEntry.bas \
    RasEnumDevices.bas \
    RasEnumEntries.bas \
    RasGetCountryInfo.bas \
    RasEntry.vbp
    $(bc) RasEntry.vbp $(bc_exe) /out comp.log
    @type comp.log
    @del comp.log
