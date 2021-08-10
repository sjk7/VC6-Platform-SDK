In order for you to build the DataServices sample, you must modify the DATA.IDL
and the STDAFX.H files.  Line 24 of DATA.IDL and line 32 of STDAFX.H must point 
to the correct location of MSADO15.DLL

The path usually looks like the following:
"c:\program files\common files\system\ado\msado15.dll

Once you make the two modifications, you can type
nmake /F data.mak

OR uncomment the last two lines in the makefile and just type 'nmake'
