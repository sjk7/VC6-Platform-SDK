!if "$(CPU)" == "IA64"
!message Sorry building this sample for 64bit is not currently supported.
!else
All:
!IFDEF NODEBUG
   nmake /f PoolTest.mak CFG="PoolTest - Win32 Unicode Release MinSize" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f PoolTest.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF

!endif
