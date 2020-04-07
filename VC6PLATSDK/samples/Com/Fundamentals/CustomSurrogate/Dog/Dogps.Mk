
dogps.dll: dlldata.obj idog_p.obj idog_i.obj
	link /dll /out:dogps.dll /def:dogps.def /entry:DllMain dlldata.obj idog_p.obj idog_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_DEBUG /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del dogps.dll
	@del dogps.lib
	@del dogps.exp
	@del dlldata.obj
	@del idog_p.obj
	@del idog_i.obj
