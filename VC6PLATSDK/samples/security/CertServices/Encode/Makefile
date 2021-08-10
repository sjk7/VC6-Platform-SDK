# Nmake macros for building Win32 & Win64 apps

!IF "$(TARGETOS)" == "WINNT"  && "$(CPU)" != "IA64"

!include <win32.mak>

IncDir=$(BKOFFICE)Include


PROJNAME = CertEnc
OBJFILES = adate.Obj along.Obj altname.Obj astring.Obj atl.Obj \
	bitstr.Obj ceError.Obj ceLib.Obj CertEnc.Obj crldist.Obj pch.Obj
EXTRA_LIBS = Certidl.Lib Crypt32.Lib


all: $(PROJNAME).Dll


CertEnc.Res: CertEnc.Rc CertEnc.Tlb
    $(rc) $(rcvars) -r -fo $*.Res $*.Rc


CertEnc.Tlb: "$(IncDir)\CertEnc.Idl"
    midl "$(IncDir)\CertEnc.Idl"


.Cpp.Obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) -I. -DUNICODE $*.Cpp


$(PROJNAME).Dll: $(OBJFILES) CertEnc.Res
    $(link) $(linkdebug) $(dlllflags)  -def:CertEnc.def -out:$*.Dll $** $(olelibsdll) $(EXTRA_LIBS)


clean:
    del *.Obj *.Res
!ELSE
!MESSAGE Sorry this sample only builds for the i386 Windows NT Platform
!ENDIF
