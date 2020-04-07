
NewsEventClassps.dll: dlldata.obj NewsEventClass_p.obj NewsEventClass_i.obj
	link /dll /out:NewsEventClassps.dll /def:NewsEventClassps.def /entry:DllMain dlldata.obj NewsEventClass_p.obj NewsEventClass_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del NewsEventClassps.dll
	@del NewsEventClassps.lib
	@del NewsEventClassps.exp
	@del dlldata.obj
	@del NewsEventClass_p.obj
	@del NewsEventClass_i.obj
