/***
*fputs.c - write a string to a stream
*
*       Copyright (c) 1985-2001, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines fputs() - writes a string to a stream
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <dbgint.h>
#include <file2.h>
#include <string.h>
#include <internal.h>
#include <mtdll.h>

/***
*int fputs(string, stream) - write a string to a file
*
*Purpose:
*       Output the given string to the stream, don't write the '\0' or
*       supply a '\n'.  Uses _stbuf and _ftbuf for efficiency reasons.
*
*Entry:
*       char *string - string to write
*       FILE *stream - stream to write to.
*
*Exit:
*       Good return   = 0
*       Error return  = EOF
*
*Exceptions:
*
*******************************************************************************/

int __cdecl fputs (
        const char *string,
        FILE *stream
        )
{
        REG2 int buffing;
        REG1 size_t length;
        REG3 size_t ndone;

        _ASSERTE(string != NULL);
        _ASSERTE(stream != NULL);

        length = strlen(string);

#ifdef _MT
        _lock_str(stream);
        __try {
#endif  /* _MT */

        buffing = _stbuf(stream);
        ndone = _fwrite_lk(string,1,length,stream);
        _ftbuf(buffing, stream);

#ifdef _MT
        }
        __finally {
            _unlock_str(stream);
        }
#endif  /* _MT */

        return(ndone == length ? 0 : EOF);
}
