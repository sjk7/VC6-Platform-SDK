
CascadeECps.dll: dlldata.obj CascadeEC_p.obj CascadeEC_i.obj
	link /dll /out:CascadeECps.dll /def:CascadeECps.def /entry:DllMain dlldata.obj CascadeEC_p.obj CascadeEC_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del CascadeECps.dll
	@del CascadeECps.lib
	@del CascadeECps.exp
	@del dlldata.obj
	@del CascadeEC_p.obj
	@del CascadeEC_i.obj
