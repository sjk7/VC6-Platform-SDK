
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
