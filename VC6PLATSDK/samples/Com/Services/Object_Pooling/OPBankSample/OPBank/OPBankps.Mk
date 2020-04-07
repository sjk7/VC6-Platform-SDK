
OPBankps.dll: dlldata.obj OPBank_p.obj OPBank_i.obj
	link /dll /out:OPBankps.dll /def:OPBankps.def /entry:DllMain dlldata.obj OPBank_p.obj OPBank_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del OPBankps.dll
	@del OPBankps.lib
	@del OPBankps.exp
	@del dlldata.obj
	@del OPBank_p.obj
	@del OPBank_i.obj
