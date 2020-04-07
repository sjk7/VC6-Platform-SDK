/*+==========================================================================

File: STATest.cpp

Summary: Implementation of CSTATest

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
#include "STAObject.h"
#include "STATest.h"

#define LOOPCOUNT 10000

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: CSTATest

CSTATest is a simply object that does nothing but is marked as Apartment threaded.
It's purpose is just so our client has an apartment threaded object to call

C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Exercise

Summary: Exercise simply loops for a while doing some math on the stack


M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

STDMETHODIMP CSTATest::Exercise(void)
{

	DWORD	dwCount, dwValue = 0;

	for (dwCount = 0; dwCount < LOOPCOUNT; dwCount++)
		dwValue += dwCount;

	return S_OK;
}
