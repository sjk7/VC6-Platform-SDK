
ADsErrorps.dll: dlldata.obj ADsError_p.obj ADsError_i.obj
	link /dll /out:ADsErrorps.dll /def:ADsErrorps.def /entry:DllMain dlldata.obj ADsError_p.obj ADsError_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ADsErrorps.dll
	@del ADsErrorps.lib
	@del ADsErrorps.exp
	@del dlldata.obj
	@del ADsError_p.obj
	@del ADsError_i.obj
