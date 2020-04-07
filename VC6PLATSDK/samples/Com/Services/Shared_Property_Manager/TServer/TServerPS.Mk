
tServerps.dll: dlldata.obj tServer_p.obj tServer_i.obj
	link /dll /out:tServerps.dll /def:tServerps.def /entry:DllMain dlldata.obj tServer_p.obj tServer_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del tServerps.dll
	@del tServerps.lib
	@del tServerps.exp
	@del dlldata.obj
	@del tServer_p.obj
	@del tServer_i.obj
