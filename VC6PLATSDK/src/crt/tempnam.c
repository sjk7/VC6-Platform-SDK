/***
*tempnam.c - generate unique file name
*
*       Copyright (c) 1986-2001, Microsoft Corporation. All rights reserved.
*
*Purpose:
*
*******************************************************************************/


#include <cruntime.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>
#include <internal.h>
#include <mtdll.h>
#include <tchar.h>
#include <dbgint.h>

#ifdef _MBCS
#include <mbstring.h>
#endif  /* _MBCS */

/* local tchar */
#ifdef _UNICODE
#define _tP_tmpdir _wP_tmpdir
#else  /* _UNICODE */
#define _tP_tmpdir _P_tmpdir
#endif  /* _UNICODE */

#ifdef _UNICODE
static wchar_t * _wstripquote (wchar_t *);
#else  /* _UNICODE */
static char * _stripquote (char *);
#endif  /* _UNICODE */

/***
*_TSCHAR *_tempnam(dir, prefix) - create unique file name
*
*Purpose:
*       Create a file name that is unique in the specified directory.
*       The semantics of directory specification is as follows:
*       Use the directory specified by the TMP environment variable
*       if that exists, else use the dir argument if non-NULL, else
*       use _P_tmpdir if that directory exists, else use the current
*       working directory), else return NULL.
*
*Entry:
*       _TSCHAR *dir - directory to be used for temp file if TMP env var
*                   not set
*       _TSCHAR *prefix - user provided prefix for temp file name
*
*Exit:
*       returns ptr to constructed file name if successful
*       returns NULL if unsuccessful
*
*Exceptions:
*
*******************************************************************************/

_TSCHAR * __cdecl _ttempnam (
        const _TSCHAR *dir,
        const _TSCHAR *pfx
        )
{
        REG1 _TSCHAR *ptr;
        REG2 unsigned int pfxlength = 0;
        _TSCHAR *s;
        _TSCHAR *pfin;
        unsigned int first;
        unsigned int bufsz;
        _TSCHAR * qptr = NULL;  /* ptr to TMP path with quotes stripped out */

#ifdef _MT
        if ( !_mtinitlocknum( _TMPNAM_LOCK ))
                return NULL;
#endif  /* _MT */

        /* try TMP path */
        if ( ( ptr = _tgetenv( _T("TMP") ) ) && ( _taccess( ptr, 0 ) != -1 ) )
                dir = ptr;

        /* try stripping quotes out of TMP path */
#ifdef _UNICODE
        else if ( (ptr != NULL) && (qptr = _wstripquote(ptr)) &&
#else  /* _UNICODE */
        else if ( (ptr != NULL) && (qptr = _stripquote(ptr)) &&
#endif  /* _UNICODE */
                  (_taccess(qptr, 0) != -1 ) )
                dir = qptr;

        /* TMP path not available, use alternatives */
        else if (!( dir != NULL && ( _taccess( dir, 0 ) != -1 ) ) )
        /* do not "simplify" this depends on side effects!! */
        {
                if ( _taccess( _tP_tmpdir, 0 ) != -1 )
                    dir = _tP_tmpdir;
                else
                    dir = _T(".");
        }


        if (pfx)
                pfxlength = (unsigned)_tcslen(pfx);

        if ( ((bufsz = (unsigned)_tcslen(dir) + pfxlength + 12) > FILENAME_MAX) ||
             ((s = malloc(bufsz * sizeof(_TSCHAR))) == NULL) )
                /* the 12 above allows for a backslash, 10 char temp string and
                   a null terminator */
        {
                goto done2;
        }

        *s = _T('\0');
        _tcscat( s, dir );
        pfin = (_TSCHAR *)&(dir[ _tcslen( dir ) - 1 ]);

#ifdef _MBCS
        if (*pfin == '\\') {
                if (pfin != _mbsrchr(dir,'\\'))
                        /* *pfin is second byte of a double-byte char */
                        strcat( s, "\\" );
        }
        else if (*pfin != '/')
                strcat( s, "\\" );
#else  /* _MBCS */
        if ( ( *pfin != _T('\\') ) && ( *pfin != _T('/') ) )
        {
                _tcscat( s, _T("\\") );
        }
#endif  /* _MBCS */

        if ( pfx != NULL )
        {
                _tcscat( s, pfx );
        }
        ptr = &s[_tcslen( s )];

        /*
        Re-initialize _tempoff if necessary.  If we don't re-init _tempoff, we
        can get into an infinate loop (e.g., (a) _tempoff is a big number on
        entry, (b) prefix is a long string (e.g., 8 chars) and all tempfiles
        with that prefix exist, (c) _tempoff will never equal first and we'll
        loop forever).

        [NOTE: To avoid a conflict that causes the same bug as that discussed
        above, _tempnam() uses _tempoff; tmpnam() uses _tmpoff]
        */

#ifdef _MT
        _mlock(_TMPNAM_LOCK);   /* Lock access to _old_pfxlen and _tempoff */
        __try {
#endif  /* _MT */

        if (_old_pfxlen < pfxlength)
                _tempoff = 1;
        _old_pfxlen = pfxlength;

        first = _tempoff;

        do {
                if ( (++_tempoff - first) > TMP_MAX ) {
                        free(s);
                        s = NULL;
                        goto done1;
                }
                /* the maximum length string returned by _ultot is 10 chars
                   (assuming 32-bit unsigned long) so there is enough room in
                   the tail of s (pointed to by ptr) for it */
                _ultot( (unsigned long)_tempoff, ptr, 10 );
        }
        while ( (_taccess( s, 0 ) == 0 ) || (errno == EACCES) );


        /* Common return */
done1:

#ifdef _MT
        ; }
        __finally {
                _munlock(_TMPNAM_LOCK);     /* release tempnam lock */
        }
#endif  /* _MT */

done2:
        _free_crt(qptr);            /* free temp ptr, if non-NULL */
        return(s);
}



/***
*_stripquote() - Strip quotes out of a string
*
*Purpose:
*       This routine strips quotes out of a string.  This is necessary
*       in the case where a file/path name has embedded quotes (i.e.,
*       new file system.)
*
*       For example,
*                       c:\tmp\"a b c"\d --> c:\tmp\a b d\d
*
*       NOTE:  This routine makes a copy of the string since it may be
*       passed a pointer to an environment variable that shouldn't be
*       changed.  It is up to the caller to free up the memory (if the
*       return value is non-NULL).
*
*Entry:
*       _TSCHAR * ptr = pointer to string
*
*Exit:
*       _TSCHAR * ptr = pointer to copy of string with quotes gone.
*       NULL = no quotes in string.
*
*Exceptions:
*
*******************************************************************************/

#ifdef _UNICODE
static wchar_t * _wstripquote (
#else  /* _UNICODE */
static char * _stripquote (
#endif  /* _UNICODE */
        _TSCHAR * src
        )
{
        _TSCHAR * dst;
        _TSCHAR * ret;
        unsigned int q = 0;


        /* get a buffer for the new string */

        if ((dst = _malloc_crt((_tcslen(src)+1) * sizeof(_TSCHAR))) == NULL)
                return(NULL);

        /* copy the string stripping out the quotes */

        ret = dst;          /* save base ptr */

        while (*src) {

                if (*src == _T('\"')) {
                        src++; q++;
                }
                else
                        *dst++ =  *src++;
        }

        if (q) {
                *dst = _T('\0');        /* final nul */
                return(ret);
        }
        else {
                _free_crt(ret);
                return(NULL);
        }

}

