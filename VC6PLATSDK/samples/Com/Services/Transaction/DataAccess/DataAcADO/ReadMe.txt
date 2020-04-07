In order for you to build the DataAcADO sample, you must modify the ADOCOMPONENT.CPP
file.  Line 26 of ADOCOMPONENT.CPP must point 
to the correct location of MSADO20.TLB

The path usually looks like the following:
"c:\program files\common files\system\ado\msado20.tlb

Once you make the necessary modification, uncomment the lines below the messages 
in the makefile and just type 'nmake'
