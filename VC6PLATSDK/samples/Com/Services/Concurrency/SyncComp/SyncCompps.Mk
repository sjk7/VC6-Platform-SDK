
SyncCompps.dll: dlldata.obj SyncComp_p.obj SyncComp_i.obj
	link /dll /out:SyncCompps.dll /def:SyncCompps.def /entry:DllMain dlldata.obj SyncComp_p.obj SyncComp_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del SyncCompps.dll
	@del SyncCompps.lib
	@del SyncCompps.exp
	@del dlldata.obj
	@del SyncComp_p.obj
	@del SyncComp_i.obj
