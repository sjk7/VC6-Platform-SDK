
Oledbkbps.dll: dlldata.obj Oledbkb_p.obj Oledbkb_i.obj
	link /dll /out:Oledbkbps.dll /def:Oledbkbps.def /entry:DllMain dlldata.obj Oledbkb_p.obj Oledbkb_i.obj mtxih.lib kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib ole32.lib advapi32.lib

.c.obj:
	cl /c /MD /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del Oledbkbps.dll
	@del Oledbkbps.lib
	@del Oledbkbps.exp
	@del dlldata.obj
	@del Oledbkb_p.obj
	@del Oledbkb_i.obj
