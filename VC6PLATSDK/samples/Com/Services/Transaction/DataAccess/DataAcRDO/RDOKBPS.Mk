
RDOKBps.dll: dlldata.obj RDOKB_p.obj RDOKB_i.obj
	link /dll /out:RDOKBps.dll /def:RDOKBps.def /entry:DllMain dlldata.obj RDOKB_p.obj RDOKB_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del RDOKBps.dll
	@del RDOKBps.lib
	@del RDOKBps.exp
	@del dlldata.obj
	@del RDOKB_p.obj
	@del RDOKB_i.obj
