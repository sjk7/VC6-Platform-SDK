/////////////////////////////////////////////////////////////////////////////
//  This is a part of the MMC SDK.
//  Copyright (C) 1999 - 2001 Microsoft Corporation.  All Rights Reserved.
//  All rights reserved.
//
//  This source code is only intended as a supplement to the MMC SDK
//  Reference and related electronic documentation provided with the
//  library.  See these sources for detailed information regarding the
//  MMC Library product.
//
//  LListImple.cpp: implementation of CLListImpl helper functions
//


#include "LListImpl.h"


//---------------------------------------------------------------------------
CPlex* PASCAL CPlex::Create(CPlex*& pHead, UINT nMax, UINT cbElement)
{
	_ASSERT( nMax > 0 && cbElement > 0 );
	CPlex* p = (CPlex*) new BYTE[sizeof(CPlex) + nMax * cbElement];
			// may throw exception
	p->pNext = pHead;
	pHead = p;  // change head (adds in reverse order for simplicity)
	return p;

} //end Create()

//---------------------------------------------------------------------------
// Free this one and links
//
void CPlex::FreeDataChain()     
{
	CPlex* p = this;
	while (p != NULL)
	{
		BYTE* bytes = (BYTE*) p;
		CPlex* pNext = p->pNext;
		delete[] bytes;
		p = pNext;
	}
} //end FreeDataChain()

//---------------------------------------------------------------------------
// IsValidAddress() returns TRUE if the passed parameter points
// to at least nBytes of accessible memory. If bReadWrite is TRUE,
// the memory must be writeable; if bReadWrite is FALSE, the memory
// may be const.
//
BOOL IsValidAddress
(
  const void*  lp,
  UINT         nBytes,
	BOOL         bReadWrite /* TRUE */
)
{
	// Simple version using Win-32 APIs for pointer validation.
	return (lp != NULL && !IsBadReadPtr(lp, nBytes) &&
		     (!bReadWrite || !IsBadWritePtr((LPVOID)lp, nBytes)));

} //end IsValidAddress()

