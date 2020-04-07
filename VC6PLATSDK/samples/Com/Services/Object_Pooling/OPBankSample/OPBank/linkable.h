/*+==========================================================================
  File:      Linkable.h
  Summary:   Header for linked list helper class
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

#ifndef _LINKABLE_H_
#define _LINKABLE_H_

#include <windows.h>

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:	CLinkable
		Base class for objects that can be placed onto cheap circular
		doubly-linked lists.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 
class CLinkable
{
public:

	// Constructor
	CLinkable() { m_pNext = m_pPrev = this; }

	// Destructor
	~CLinkable() { Remove(); }

	// return TRUE iff on a list
	BOOL			IsLinked() { return ( m_pNext != this ); }

	// return next element on list
	CLinkable*		Next() { return m_pNext; }

	// return previous element on list
	CLinkable*		Previous() { return m_pPrev; }

	// insert parameter onto list after this, removing it first if necessary
	void			InsertAfter( CLinkable* other );

	// insert parameter onto list before this, removing it first if necessary
	void			InsertBefore( CLinkable* other );

	// remove us from list, if any
	void			Remove();

private:
	CLinkable*		m_pNext;		// next element on list
	CLinkable*		m_pPrev;		// previous element on list
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:	CListHeader
		List header for list of CLinkable's. This is merely a CLinkable with
		some methods renamed for better readability.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 
class CListHeader : public CLinkable
{

public:

	// Constructor
	CListHeader() {}

	// Destructor
	~CListHeader() {};

	// return TRUE iff list is empty
	BOOL			IsEmpty()	{ return !IsLinked(); }

	// return first element on list
	CLinkable*		First()		{ return Next(); }

	// return last element on list
	CLinkable*		Last()		{ return Previous(); }

	// insert parameter at head of list
	void			InsertFirst ( CLinkable* other )	{ InsertAfter( other ); }

	// insert parameter at tail of list
	void			InsertLast ( CLinkable* other )		{ InsertBefore( other ); }
};

#endif _LINKABLE_H_
