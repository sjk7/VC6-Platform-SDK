/***
*wcslen.c - contains wcslen() routine
*
*       Copyright (c) 1985-2001, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       wcslen returns the length of a null-terminated wide-character string,
*       not including the null wchar_t itself.
*
*******************************************************************************/


#include <cruntime.h>
#include <string.h>

#if defined(_M_IA64) && _MSC_FULL_VER >= 13102125
#pragma warning(disable:4163)
#pragma function(wcslen)
#endif  /* defined(_M_IA64) && _MSC_FULL_VER >= 13102125 */

/***
*wcslen - return the length of a null-terminated wide-character string
*
*Purpose:
*       Finds the length in wchar_t's of the given string, not including
*       the final null wchar_t (wide-characters).
*
*Entry:
*       const wchar_t * wcs - string whose length is to be computed
*
*Exit:
*       length of the string "wcs", exclusive of the final null wchar_t
*
*Exceptions:
*
*******************************************************************************/

size_t __cdecl wcslen (
        const wchar_t * wcs
        )
{
        const wchar_t *eos = wcs;

        while( *eos++ ) ;

        return( (size_t)(eos - wcs - 1) );
}

