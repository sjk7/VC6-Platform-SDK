
FreeObjectps.dll: dlldata.obj FreeObject_p.obj FreeObject_i.obj
	link /dll /out:FreeObjectps.dll /def:FreeObjectps.def /entry:DllMain dlldata.obj FreeObject_p.obj FreeObject_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del FreeObjectps.dll
	@del FreeObjectps.lib
	@del FreeObjectps.exp
	@del dlldata.obj
	@del FreeObject_p.obj
	@del FreeObject_i.obj
