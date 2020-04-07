
ADOKBps.dll: dlldata.obj ADOKB_p.obj ADOKB_i.obj
	link /dll /out:ADOKBps.dll /def:ADOKBps.def /entry:DllMain dlldata.obj ADOKB_p.obj ADOKB_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del ADOKBps.dll
	@del ADOKBps.lib
	@del ADOKBps.exp
	@del dlldata.obj
	@del ADOKB_p.obj
	@del ADOKB_i.obj
