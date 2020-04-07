/*+==========================================================================

File: ComSyncTest.cpp

Summary: Implementation of CComSyncTest

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
#include "ComSyncObject.h"
#include "ComSyncTest.h"
#define LOOPCOUNT 10000

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: CComSyncTest

CComSyncTest is a simply object that does nothing but is marked as FREE threaded,
and marked in COM+ as requring syncronization but doesn't have any by itself.
It's purpose is just so our client has a free threaded COM syncronized object to call

C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Exercise

Summary: Exercise simply loops for a while doing some math on the stack.
		 This version does not utilize a CritSec. This is because this 
		 object will be marked as requires syncronization in COM+

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

STDMETHODIMP CComSyncTest::Exercise(void)
{

	DWORD	dwCount, dwValue = 0;

	for (dwCount = 0; dwCount < LOOPCOUNT; dwCount++)
		dwValue += dwCount;

	return S_OK;
}
