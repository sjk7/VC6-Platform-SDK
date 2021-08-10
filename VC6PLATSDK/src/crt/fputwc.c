/***
*fputwc.c - write a wide character to an output stream
*
*       Copyright (c) 1993-2001, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines fputwc() - writes a wide character to a stream
*
*******************************************************************************/


#include <cruntime.h>
#include <stdio.h>
#include <stdlib.h>
#include <dbgint.h>
#include <file2.h>
#include <internal.h>
#include <mtdll.h>
#include <msdos.h>
#include <errno.h>
#include <wchar.h>
#include <tchar.h>
#include <setlocal.h>

#ifdef _MT

/***
*wint_t fputwc(ch, stream) - write a wide character to a stream
*
*Purpose:
*       Writes a wide character to a stream.  Function version of putwc().
*
*Entry:
*       wchar_t ch - wide character to write
*       FILE *stream - stream to write to
*
*Exit:
*       returns the wide character if successful
*       returns WEOF if fails
*
*Exceptions:
*
*******************************************************************************/

wint_t __cdecl fputwc (
        wchar_t ch,
        FILE *str
        )
{
        REG1 FILE *stream;
        REG2 wint_t retval;

        _ASSERTE(str != NULL);

        /* Init stream pointer */
        stream = str;

#ifdef _MT
        _lock_str(stream);
        __try {
#endif  /* _MT */

        retval = _putwc_lk(ch,stream);

#ifdef _MT
        }
        __finally {
                _unlock_str(stream);
        }
#endif  /* _MT */

        return(retval);
}

/***
*_putwc_lk() -  putwc() core routine (locked version)
*
*Purpose:
*       Core putwc() routine; assumes stream is already locked.
*
*       [See putwc() above for more info.]
*
*Entry: [See putwc()]
*
*Exit:  [See putwc()]
*
*Exceptions:
*
*******************************************************************************/

wint_t __cdecl _putwc_lk (
        wchar_t ch,
        FILE *str
        )
{

#else  /* _MT */

wint_t __cdecl fputwc (
        wchar_t ch,
        FILE *str
        )
{

#endif  /* _MT */

        if (!(str->_flag & _IOSTRG) && (_osfile_safe(_fileno(str)) & FTEXT))
        {
                int size, i;
                char mbc[MB_LEN_MAX];

                /* text (multi-byte) mode */
                if ((size = wctomb(mbc, ch)) == -1)
                {
                        /*
                         * Conversion failed! Set errno and return
                         * failure.
                         */
                        errno = EILSEQ;
                        return WEOF;
                }
                for ( i = 0; i < size; i++)
                {
                        if (_putc_lk(mbc[i], str) == EOF)
                                return WEOF;
                }
                return (wint_t)(0xffff & ch);
        }
        /* binary (Unicode) mode */
        if ( (str->_cnt -= sizeof(wchar_t)) >= 0 )
                return (wint_t) (0xffff & (*((wchar_t *)(str->_ptr))++ = (wchar_t)ch));
        else
                return (wint_t) _flswbuf(ch, str);
}

#undef putwc

wint_t __cdecl putwc (
        wchar_t ch,
        FILE *str
        )
{
        return fputwc(ch, str);
}

