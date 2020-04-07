
TxEnlisterps.dll: dlldata.obj TxEnlister_p.obj TxEnlister_i.obj
	link /dll /out:TxEnlisterps.dll /def:TxEnlisterps.def /entry:DllMain dlldata.obj TxEnlister_p.obj TxEnlister_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TxEnlisterps.dll
	@del TxEnlisterps.lib
	@del TxEnlisterps.exp
	@del dlldata.obj
	@del TxEnlister_p.obj
	@del TxEnlister_i.obj
