/*+==========================================================================
  File:      processFlags.h
  Summary:   Declaration of flags for Process() method
  Classes:   None
-----------------------------------------------------------------------------

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

#ifndef __PROCESSFLAGS_H_
#define __PROCESSFLAGS_H_

// Constants for Process() lFlag

const long processFlagWriteDB = 1;			// Write to order and ship tables
const long processFlagLateBound = 2;		// Latebound (IDispatch) invocation
const long processFlagQueuedComponents = 4;	// invoke Ship & Notify Queued Components

#endif	//__PROCESSFLAGS_H_