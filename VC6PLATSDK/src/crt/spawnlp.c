/***
*spawnlp.c - spawn a file; search along PATH
*
*       Copyright (c) 1985-2001, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _spawnlp() - spawn a file with search along PATH
*
*******************************************************************************/

#include <cruntime.h>
#include <stddef.h>
#include <process.h>
#include <stdarg.h>
#include <internal.h>
#include <malloc.h>
#include <tchar.h>
#include <dbgint.h>

/***
*_spawnlp(modeflag, filename, arglist) - spawn file and search along PATH
*
*Purpose:
*       Spawns a child process.
*       formats the parameters and calls _spawnvp to do the work of searching
*       the PATH environment variable and calling _spawnve.  The NULL
*       environment pointer indicates that the new process will inherit the
*       parents process's environment.  NOTE - at least one argument must be
*       present.  This argument is always, by convention, the name of the file
*       being spawned.
*
*Entry:
*       int modeflag   - mode of spawn (WAIT, NOWAIT, OVERLAY)
*                        only WAIT, OVERLAY currently implemented
*       _TSCHAR *pathname - file to spawn
*       _TSCHAR *arglist  - argument list
*       call as _spawnlp(modeflag, path, arg0, arg1, ..., argn, NULL);
*
*Exit:
*       returns exit code of child process
*       returns -1 if fails
*
*Exceptions:
*
*******************************************************************************/

intptr_t __cdecl _tspawnlp (
        int modeflag,
        const _TSCHAR *filename,
        const _TSCHAR *arglist,
        ...
        )
{
#ifdef _M_IX86

        _ASSERTE(filename != NULL);
        _ASSERTE(*filename != _T('\0'));
        _ASSERTE(arglist != NULL);
        _ASSERTE(*arglist != _T('\0'));

        return(_tspawnvp(modeflag,filename,&arglist));

#else  /* _M_IX86 */

        va_list vargs;
        _TSCHAR * argbuf[64];
        _TSCHAR ** argv;
        intptr_t result;

        _ASSERTE(filename != NULL);
        _ASSERTE(*filename != _T('\0'));
        _ASSERTE(arglist != NULL);
        _ASSERTE(*arglist != _T('\0'));

        va_start(vargs, arglist);
#ifdef WPRFLAG
        argv = _wcapture_argv(&vargs, arglist, argbuf, 64);
#else  /* WPRFLAG */
        argv = _capture_argv(&vargs, arglist, argbuf, 64);
#endif  /* WPRFLAG */
        va_end(vargs);

        result = _tspawnvp(modeflag,filename,argv);
        if (argv && argv != argbuf)
            _free_crt(argv);
        return result;

#endif  /* _M_IX86 */
}
