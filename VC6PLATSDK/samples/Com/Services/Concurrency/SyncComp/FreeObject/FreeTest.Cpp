/*+==========================================================================

File: FreeTest.cpp 

Summary: Implementation of CFreeTest

----------------------------------------------------------------------------
This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995 - 2000 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
==========================================================================+*/

#include "stdafx.h"
#include "FreeObject.h"
#include "FreeTest.h"

#define LOOPCOUNT 10000

extern CRITICAL_SECTION g_csSync;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: CFreeTest

CFreeTest is a simply object that does nothing but is marked as FREE threaded. 
It's purpose is just so our client has a free threaded object to call

C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Exercise

Summary: Exercise simply loops for a while doing some math on the stack.
		 Utilize a CritSec here just so we are doing some syncronization since
		 this sample compares syncronization methods

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

STDMETHODIMP CFreeTest::Exercise(void)
{

	DWORD	dwCount, dwValue = 0;

	// we only use a CriticalSection for time comparisons with the other clases.
	// There is nothing in this function that would require a critsec

	// get into our critical section
	EnterCriticalSection(&g_csSync);

	for (dwCount = 0; dwCount < LOOPCOUNT; dwCount++)
		dwValue += dwCount;

	LeaveCriticalSection(&g_csSync);

	return S_OK;
}
