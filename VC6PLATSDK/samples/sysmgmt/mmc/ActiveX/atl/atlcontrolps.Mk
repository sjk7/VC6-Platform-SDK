
ATLControlps.dll: dlldata.obj ATLControl_p.obj ATLControl_i.obj
	link /dll /out:ATLControlps.dll /def:ATLControlps.def /entry:DllMain dlldata.obj ATLControl_p.obj ATLControl_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ATLControlps.dll
	@del ATLControlps.lib
	@del ATLControlps.exp
	@del dlldata.obj
	@del ATLControl_p.obj
	@del ATLControl_i.obj
