# ADO_PATH_SET=1

!ifndef ADO_PATH_SET
!message This sample imports a library using an importlib statement in the 
!message file 'data.idl'. This line needs to be manualy modified so the path 
!message to the library is correct before the sample can be built.
!message
!message Then the line: "ADO_PATH_SET=1" can be uncommented in the makefile 
!message after this change is made and the sample can be built with nmake.
!else

All:
!IFDEF NODEBUG
   nmake /f Data.mak CFG="Data - Win32 Release MinSize" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f Data.mak CFG="Data - Win32 Debug" -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF



!endif
