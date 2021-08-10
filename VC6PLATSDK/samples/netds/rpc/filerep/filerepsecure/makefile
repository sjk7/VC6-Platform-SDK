#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**             Simple File Replication Service             **#
#**         Copyright(c) Microsoft Corp. 1992-2001          **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

# Let the compiler know what version we are running.
cflags = $(cflags) /W3 -D_WIN32_WINNT=0x500 -D_WIN32_IE=0x0500

# Compile with UNICODE support
cflags = $(cflags) -D_UNICODE -DUNICODE
midlflags = $(midlflags) -D_UNICODE

!if "$(DEBUG)" == "1"
linkflags = $(linkflags) $(linkdebug)
cflags = $(cflags) $(cdebug)
MSVCRT = msvcrtd.lib
LIBC = libcd.lib
!else
MSVCRT = msvcrt.lib
LIBC = libc.lib
!endif

!if "$(PROF)" == "1"
cflags = $(cflags) -DPROF
PROF_DEPS = Prof.obj
PROF_LIBS = Prof.obj
!else
!endif

!if "$(STRESS)" == "1"
cflags = $(cflags) -DRETRY_EXCEPTION
!else
!endif

all : FileRep FileRepService

# Make the file replication utility
FileRep : FileRep.obj common.obj FileRepClient_c.obj
	$(link) $(linkflags) -out:FileRep.exe \
	FileRep.obj common.obj FileRepClient_c.obj \
	rpcrt4.lib shell32.lib Ntdsapi.lib Advapi32.lib \
	$(LIBC) /NODEFAULTLIB:libc

FileRep.obj : FileRep.cpp FileRepClient.h
   $(cc) $(cflags) $*.cpp

# Make the services
FileRepService : FileRepService.obj common.obj Service.obj \
                 FileRepClientProc.obj FileRepServerProc.obj \
		 FileRepClient_s.obj \
		 FileRepServer_c.obj FileRepServer_s.obj $(PROF_DEPS)
	$(link) $(linkflags) -out:FileRepService.exe \
        FileRepService.obj common.obj Service.obj \
        FileRepClientProc.obj FileRepServerProc.obj \
	FileRepClient_s.obj \
        FileRepServer_c.obj FileRepServer_s.obj $(PROF_LIBS) \
	rpcrt4.lib advapi32.lib kernel32.lib shell32.lib Secur32.lib \
	Ntdsapi.lib Netapi32.lib $(MSVCRT) /NODEFAULTLIB:libc

FileRepService.obj : FileRepService.cpp common.h \
                     FileRepServer.h FileRepClient.h FileRepServer.h
	$(cc) $(cflags) $*.cpp

FileRepClientProc.obj : FileRepClientProc.cpp FileRepClient.h common.h
	$(cc) $(cflags) $*.cpp

FileRepServerProc.obj : FileRepServerProc.cpp FileRepServer.h common.h
	$(cc) $(cflags) $*.cpp

Service.obj : Service.cpp Service.h
	$(cc) $(cflags) $*.cpp

common.obj : common.cpp common.h
        $(cc) $(cflags) $*.cpp

Prof.obj : Prof.cpp Prof.h
	$(cc) $(cflags) $*.cpp

FileRepServer_c.obj : FileRepServer_c.c FileRepServer.h
	$(cc) $(cflags) $*.c

FileRepServer_s.obj : FileRepServer_s.c FileRepServer.h
	$(cc) $(cflags) $*.c

FileRepClient_c.obj : FileRepClient_c.c FileRepClient.h
	$(cc) $(cflags) $*.c

FileRepClient_s.obj : FileRepClient_s.c FileRepClient.h
	$(cc) $(cflags) $*.c

# Make stubs and header files from the IDL files
FileRepClient.h FileRepClient_c.c FileRepClient_s.c : FileRepClient.idl
	midl $(midlflags) -robust FileRepClient.idl

FileRepServer.h FileRepServer_c.c FileRepServer_s.c : FileRepServer.idl
	midl $(midlflags) -robust -prefix client "c_" server "s_" FileRepServer.idl

# Clean up everything
cleanall : clean
	-del *.exe
	-del *.pdb
	-del *~

# Clean up everything but the .EXEs
clean :
	-del *.obj
	-del FileRepServer_c.c
	-del FileRepServer_s.c
	-del FileRepServer.h
	-del FileRepClient_c.c
	-del FileRepClient_s.c
	-del FileRepClient.h

