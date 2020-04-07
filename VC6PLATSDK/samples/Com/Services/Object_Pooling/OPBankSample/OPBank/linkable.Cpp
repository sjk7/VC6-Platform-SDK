/*+==========================================================================
  File:      Linkable.cpp
  Summary:   CLinkable linked list helper class implementation used by
			 bank client
  Classes:   CLinkable
-----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/

//
// Includes
//
#include <stdafx.h>
#include "linkable.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CLinkable::InsertAfter
  Summary:  Insert 'that' onto the list after 'this'. Remove 'other' from 
			its current list, if necessary.
  Args:     CLinkable* that		element to insert
  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CLinkable::InsertAfter( CLinkable* that )
{
	CLinkable* prev = that->m_pPrev;
	CLinkable* next = that->m_pNext;

	prev->m_pNext = next;
	next->m_pPrev = prev;

	next = this->m_pNext;

	this->m_pNext = that;
	that->m_pPrev = this;
	that->m_pNext = next;
	next->m_pPrev = that;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CLinkable::InsertBefore
  Summary:  Insert 'that' onto the list before 'this'. Remove 'other' from 
			its current list, if necessary.
  Args:     CLinkable* that		item to insert
  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CLinkable::InsertBefore( CLinkable* that )
{
	CLinkable* prev = that->m_pPrev;
	CLinkable* next = that->m_pNext;

	prev->m_pNext = next;
	next->m_pPrev = prev;

	prev = this->m_pPrev;

	prev->m_pNext = that;
	that->m_pPrev = prev;
	that->m_pNext = this;
	this->m_pPrev = that;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CLinkable::Remove
  Summary:  Remove element from its current list, if any.
			its current list, if necessary.
  Args:     None
  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CLinkable::Remove()
{
	CLinkable* prev = m_pPrev;
	CLinkable* next = m_pNext;

	prev->m_pNext = next;
	next->m_pPrev = prev;

	m_pPrev = m_pNext = this;
}
