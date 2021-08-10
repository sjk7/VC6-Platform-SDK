/***
*isatty.c - check if file handle refers to a device
*
*       Copyright (c) 1989-2001, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _isatty() - check if file handle refers to a device
*
*******************************************************************************/

#include <cruntime.h>
#include <msdos.h>
#include <internal.h>
#include <io.h>

/***
*int _isatty(handle) - check if handle is a device
*
*Purpose:
*       Checks if the given handle is associated with a character device
*       (terminal, console, printer, serial port)
*
*Entry:
*       int handle - handle of file to be tested
*
*Exit:
*       returns non-0 if handle refers to character device,
*       returns 0 otherwise
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _isatty (
        int fh
        )
{
        /* see if file handle is valid, otherwise return FALSE */
        if ( (unsigned)fh >= (unsigned)_nhandle )
                return 0;

        /* check file handle database to see if device bit set */
        return (int)(_osfile(fh) & FDEV);
}
