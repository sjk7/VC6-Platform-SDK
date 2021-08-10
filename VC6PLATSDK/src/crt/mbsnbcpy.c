/***
*mbsnbcpy.c - Copy one string to another, n bytes only (MBCS)
*
*       Copyright (c) 1985-2001, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Copy one string to another, n bytes only (MBCS)
*
*******************************************************************************/

#ifdef _MBCS

#include <mtdll.h>
#include <cruntime.h>
#include <string.h>
#include <mbdata.h>
#include <mbctype.h>
#include <mbstring.h>

/***
* _mbsnbcpy - Copy one string to another, n bytes only (MBCS)
*
*Purpose:
*       Copies exactly cnt bytes from src to dst.  If strlen(src) < cnt, the
*       remaining character are padded with null bytes.  If strlen >= cnt, no
*       terminating null byte is added.  2-byte MBCS characters are handled
*       correctly.
*
*Entry:
*       unsigned char *dst = destination for copy
*       unsigned char *src = source for copy
*       int cnt = number of characters to copy
*
*Exit:
*       returns dst = destination of copy
*
*Exceptions:
*
*******************************************************************************/

unsigned char * __cdecl _mbsnbcpy(
        unsigned char *dst,
        const unsigned char *src,
        size_t cnt
        )
{

        unsigned char *start = dst;
#ifdef _MT
        pthreadmbcinfo ptmbci = _getptd()->ptmbcinfo;

        if ( ptmbci != __ptmbcinfo )
            ptmbci = __updatetmbcinfo();

        if ( _ISNOTMBCP_MT(ptmbci) )
#else  /* _MT */
        if ( _ISNOTMBCP )
#endif  /* _MT */
            return strncpy(dst, src, cnt);

        while (cnt) {

            cnt--;
#ifdef _MT
            if ( __ismbblead_mt(ptmbci, *src) ) {
#else  /* _MT */
            if ( _ismbblead(*src) ) {
#endif  /* _MT */
                *dst++ = *src++;
                if (!cnt) {
                    dst[-1] = '\0';
                    break;
                }
                cnt--;
                if ((*dst++ = *src++) == '\0') {
                    dst[-2] = '\0';
                    break;
                }
            }

            else
                if ((*dst++ = *src++) == '\0')
                    break;

        }

        /* pad with nulls as needed */

        while (cnt--)
            *dst++ = '\0';

        return start;
}

#endif  /* _MBCS */
