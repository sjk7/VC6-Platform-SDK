/***
*strcoll.c - Collate locale strings
*
*       Copyright (c) 1988-2001, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Compare two strings using the locale LC_COLLATE information.
*
*******************************************************************************/

#include <cruntime.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <setlocal.h>
#include <mtdll.h>
#include <errno.h>
#include <awint.h>

/***
*int strcoll() - Collate locale strings
*
*Purpose:
*       Compare two strings using the locale LC_COLLATE information.
*       [ANSI].
*
*       Non-C locale support available under _INTL switch.
*       In the C locale, strcoll() simply resolves to strcmp().
*Entry:
*       const char *s1 = pointer to the first string
*       const char *s2 = pointer to the second string
*
*Exit:
*       Less than 0    = first string less than second string
*       0              = strings are equal
*       Greater than 0 = first string greater than second string
*
*Exceptions:
*       _NLSCMPERROR    = error
*       errno = EINVAL
*
*******************************************************************************/

int __cdecl strcoll (
        const char *_string1,
        const char *_string2
        )
{

    int ret;
#ifdef _MT
    _ptiddata ptd = _getptd();
    pthreadlocinfo ptloci = ptd->ptlocinfo;

    __UPDATE_LOCALE(ptd, ptloci);
#endif  /* _MT */
    if ( __LC_HANDLE(ptloci)[LC_COLLATE] == _CLOCALEHANDLE )
            return strcmp(_string1, _string2);

    if ( 0 == (ret = __crtCompareStringA( __LC_HANDLE(ptloci)[LC_COLLATE],
                                          SORT_STRINGSORT,
                                          _string1,
                                          -1,
                                          _string2,
                                          -1,
                                          __LC_COLLATE_CP(ptloci) )) )
    {
        errno = EINVAL;
        return _NLSCMPERROR;
    }

    return (ret - 2);

}
