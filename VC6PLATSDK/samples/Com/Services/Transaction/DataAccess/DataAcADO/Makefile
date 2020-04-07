!MESSAGE Before you can compile DataAcADO you MUST make the following change
!MESSAGE 
!MESSAGE Modify Line 26 of ADOCOMPONENT.CPP 
!MESSAGE to point to the correct location of MSADO20.TLB
!MESSAGE 
!MESSAGE Then uncomment the last lines of the makefile and you are ready to build
!MESSAGE 
!MESSAGE 
# When mofications are complete uncomment the lines below here
#!IF "$(CPU)" != "IA64"
#
#All:
#!IFDEF NODEBUG
#   nmake /f ADOKB.MAK CFG="ADOKB - Win32 Release MinSize" -nologo /$(MAKEFLAGS) $(makeopts)
#!ELSE
#   nmake /f ADOKB.MAK -nologo /$(MAKEFLAGS) $(makeopts)
#!ENDIF
#
#
#
#
#!ELSE
#
#Win64:
#	@echo **************************************
#	@cd 
#	@echo does not yet build on 64-bit Windows
#	@echo **************************************
#!ENDIF
