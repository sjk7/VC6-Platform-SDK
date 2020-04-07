
PersistATLps.dll: dlldata.obj PersistATL_p.obj PersistATL_i.obj
	link /dll /out:PersistATLps.dll /def:PersistATLps.def /entry:DllMain dlldata.obj PersistATL_p.obj PersistATL_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del PersistATLps.dll
	@del PersistATLps.lib
	@del PersistATLps.exp
	@del dlldata.obj
	@del PersistATL_p.obj
	@del PersistATL_i.obj
