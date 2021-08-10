!ifdef VBINstalled
#
# Copyright Microsoft Corp, 1997-2001
# Windows Platform SDK
#
!include <Win32.mak>

#
# All VB Projects in the directory
#
ALL :  TestExt.exe

#
# Project TestExt.VBP builds TestExt.EXE
#
TestExt.exe :  \
    TestExt.frm \
    TestExt.vbp
    $(bc) $(bc_exe) TestExt.vbp /out comp.log
    @type comp.log
    @del comp.log

clean:
	@del ..\TestExt.exe

!else
!message This sample need to be built with Microsoft Visual Basic
!endif
