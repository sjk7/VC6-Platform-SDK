
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1993 - 2000 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#include <stdio.h>

main()

{
#ifdef JAPAN
        printf ("�v�����R�Q�A����͎������I");
#else
        printf ("Win32, it's happenin'!");
#endif

        return(0);
}
