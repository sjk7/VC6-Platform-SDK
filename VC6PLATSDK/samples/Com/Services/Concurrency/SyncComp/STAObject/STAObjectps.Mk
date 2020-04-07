
STAObjectps.dll: dlldata.obj STAObject_p.obj STAObject_i.obj
	link /dll /out:STAObjectps.dll /def:STAObjectps.def /entry:DllMain dlldata.obj STAObject_p.obj STAObject_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del STAObjectps.dll
	@del STAObjectps.lib
	@del STAObjectps.exp
	@del dlldata.obj
	@del STAObject_p.obj
	@del STAObject_i.obj
