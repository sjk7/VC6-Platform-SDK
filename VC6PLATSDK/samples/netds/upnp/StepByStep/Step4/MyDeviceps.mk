
MyDeviceps.dll: dlldata.obj MyDevice_p.obj MyDevice_i.obj
	link /dll /out:MyDeviceps.dll /def:MyDeviceps.def /entry:DllMain dlldata.obj MyDevice_p.obj MyDevice_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del MyDeviceps.dll
	@del MyDeviceps.lib
	@del MyDeviceps.exp
	@del dlldata.obj
	@del MyDevice_p.obj
	@del MyDevice_i.obj
