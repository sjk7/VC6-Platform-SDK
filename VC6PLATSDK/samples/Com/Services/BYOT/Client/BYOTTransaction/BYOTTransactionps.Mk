
ByotTransactionps.dll: dlldata.obj ByotTransaction_p.obj ByotTransaction_i.obj
	link /dll /out:ByotTransactionps.dll /def:ByotTransactionps.def /entry:DllMain dlldata.obj ByotTransaction_p.obj ByotTransaction_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ByotTransactionps.dll
	@del ByotTransactionps.lib
	@del ByotTransactionps.exp
	@del dlldata.obj
	@del ByotTransaction_p.obj
	@del ByotTransaction_i.obj
