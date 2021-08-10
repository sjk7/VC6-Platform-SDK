/***
*noenv.c - stub out CRT's environment string processing
*
*       Copyright (c) 1997-2001, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Stub out the environment string processing normally carried out at
*       during startup. Note, getenv, _putenv and _environ are not supported
*       if this object is used. Nor is the third argument to main.
*
*******************************************************************************/

#include <stdlib.h>

int __cdecl _setenvp(void) { return 0; }

void * __cdecl __crtGetEnvironmentStringsA(void) { return NULL; }

int __cdecl _wsetenvp(void) { return 0; }

void * __cdecl __crtGetEnvironmentStringsW(void) { return NULL; }
