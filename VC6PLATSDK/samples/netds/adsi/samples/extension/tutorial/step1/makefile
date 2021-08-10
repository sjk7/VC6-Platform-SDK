!if "$(CPU)" == "IA64"
!message Sorry building this sample for 64bit is not currently supported.
!else

DIRS =        \
    client\~    \

SDKPROJ=NetDs\ADSI\Samples\Extension\Tutorial\step1

#
# This is a Platform SDK non-leaf-node makefile.  It is used to allow NMAKE,
#  or a similar tool, to recursively build all of the samples in a directory
#  tree.  To add or remove a directory from the build process, modify the
#  DIRS list above.
#
# The SDKPROJ macro (above) is defined solely for the purpose of echoing
#  the current directory location to the screen.
#
# Do not modify this makefile except for the DIRS and SDKPROJ macros above.
#

#
# Include SDKPropBld.Mak in order to get standard build options, environment
#  variables, and macros.  The sdkpropbld.mak file is installed with the SDK
#  in the include directory.
#

!include <SDKPropBld.Mak>

#
# In order to build "all," process each of the entries in the DIRS list.
#

all: $(DIRS)

#
# In order to build each of the entries in the DIRS list, change dir into the
#  directory in question, echo the current location, run nmake recursively,
#  and change dir back to the original directory level.  This four step process
#  is encapsulated in SDKBld.Mak which is installed with the SDK in the include
#  directory.
#

$(DIRS): ADsFirstExtps.dll
!include <SDKBld.Mak>


ADsFirstExtps.dll: dlldata.obj ADsFirstExt_p.obj ADsFirstExt_i.obj
	link /dll /out:ADsFirstExtps.dll /def:ADsFirstExtps.def /entry:DllMain dlldata.obj ADsFirstExt_p.obj ADsFirstExt_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ADsFirstExtps.dll
	@del ADsFirstExtps.lib
	@del ADsFirstExtps.exp
	@del dlldata.obj
	@del ADsFirstExt_p.obj
	@del ADsFirstExt_i.obj

!endif
