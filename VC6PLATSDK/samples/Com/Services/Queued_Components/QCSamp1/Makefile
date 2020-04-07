#Make Queued Components QCSamp1 and Driver
#Driver depends on QCSamp1, so nmake Driver.mak also makes QCSamp1.mak

All:
!IFDEF NODEBUG
   cd Driver
   nmake /f Driver.mak CFG="Driver - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
   cd ..
!ELSE
   cd Driver
   nmake /f Driver.mak CFG="Driver - Win32 Debug" -nologo /$(MAKEFLAGS) $(makeopts)
   cd ..
!ENDIF
