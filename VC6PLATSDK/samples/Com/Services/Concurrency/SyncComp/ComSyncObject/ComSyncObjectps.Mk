
ComSyncObjectps.dll: dlldata.obj ComSyncObject_p.obj ComSyncObject_i.obj
	link /dll /out:ComSyncObjectps.dll /def:ComSyncObjectps.def /entry:DllMain dlldata.obj ComSyncObject_p.obj ComSyncObject_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ComSyncObjectps.dll
	@del ComSyncObjectps.lib
	@del ComSyncObjectps.exp
	@del dlldata.obj
	@del ComSyncObject_p.obj
	@del ComSyncObject_i.obj
