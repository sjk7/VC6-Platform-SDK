
LogWriterps.dll: dlldata.obj LogWriter_p.obj LogWriter_i.obj
	link /dll /out:LogWriterps.dll /def:LogWriterps.def /entry:DllMain dlldata.obj LogWriter_p.obj LogWriter_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del LogWriterps.dll
	@del LogWriterps.lib
	@del LogWriterps.exp
	@del dlldata.obj
	@del LogWriter_p.obj
	@del LogWriter_i.obj
