
Disp1ps.dll: dlldata.obj Disp1_p.obj Disp1_i.obj
	link /dll /out:Disp1ps.dll /def:Disp1ps.def /entry:DllMain dlldata.obj Disp1_p.obj Disp1_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del Disp1ps.dll
	@del Disp1ps.lib
	@del Disp1ps.exp
	@del dlldata.obj
	@del Disp1_p.obj
	@del Disp1_i.obj
