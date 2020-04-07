/*+==========================================================================
  File:      processFlags.h
  Summary:   Declaration of flags for Process() method

  Origin:    Implementation of case study in Queued Components specification
----------------------------------------------------------------------------
  Copyright 1992 - 2000 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE
==========================================================================+*/ 

#ifndef __PROCESSFLAGS_H_
#define __PROCESSFLAGS_H_

// Constants for Process() lFlag

const long processFlagWriteDB = 1;			// Write to order and ship tables
const long processFlagLateBound = 2;		// Latebound (IDispatch) invocation
const long processFlagQueuedComponents = 4;	// invoke Ship & Notify Queued Components

#endif	//__PROCESSFLAGS_H_