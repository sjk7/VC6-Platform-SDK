!include <sdkpropbld.mak>

All:
!IFDEF NODEBUG
   nmake /f ProxyStub.mak CFG="MtsSdkPs - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f ProxyStub.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF