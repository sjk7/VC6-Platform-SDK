!if "$(CPU)" == "IA64"
!message Sorry building this sample for 64bit is not currently supported.
!else
All:
!IFDEF NODEBUG
   nmake /f tServer.mak CFG="tServer - Win32 Release MinDependency" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f tServer.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF

!endif
