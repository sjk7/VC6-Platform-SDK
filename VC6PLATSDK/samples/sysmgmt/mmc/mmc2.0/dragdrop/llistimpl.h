/////////////////////////////////////////////////////////////////////////////
//  This is a part of the MMC SDK.
//  Copyright (C) 1999 - 2001 Microsoft Corporation.  All Rights Reserved.
//  All rights reserved.
//
//  This source code is only intended as a supplement to the
//  MMC SDK Reference and related
//  electronic documentation provided with the library.
//  See these sources for detailed information regarding the
//  MMC Library product.
//
//  LListImple.h:  Definition and implementation of CLListImpl.  This is a
//                 generic linked list class which emulates CList from MFC.
//


#ifndef __CLASS_CLLISTIMPL__
#define __CLASS_CLLISTIMPL__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CrtDbg.h> 
#include <Windows.h>
#include <new.h>


// Abstract iteration position
struct  __POSITION { };
typedef __POSITION*  POSITION;

/////////////////////////////////////////////////////////////////////////////
//  CPlex stuff for allocating nodes
//

//---------------------------------------------------------------------------
struct CPlex     // warning variable length structure
{
	CPlex* pNext;
//#if (_AFX_PACKING >= 8)
	DWORD dwReserved[1];    // align on 8 byte boundary
//#endif

	// BYTE data[maxNum*elementSize];

	void* data() { return this+1; }

	static CPlex* PASCAL Create(CPlex*& head, UINT nMax, UINT cbElement);
			// like 'calloc' but no zero fill
			// may throw memory exceptions

	void FreeDataChain();       // free this one and links
};


/////////////////////////////////////////////////////////////////////////////
//  Helpers
//

BOOL IsValidAddress( const void*  lp, UINT nBytes, BOOL bReadWrite = TRUE );


/////////////////////////////////////////////////////////////////////////////
// CLListImpl<TYPE, ARG_TYPE>

template<class TYPE, class ARG_TYPE>
class CLListImpl  
{
  public:
	  CLListImpl( int nBlockSize = 10 );  
	  ~CLListImpl();

  protected:
	  struct CNode
	  {
		  CNode* pNext;
		  CNode* pPrev;
		  TYPE   data;
	  };

  public:
                                         // Attributes (head and tail)
	 int       GetCount() const;
	 BOOL      IsEmpty() const;

   TYPE&     GetHead();                  // Peek at head and tail                      
	 TYPE      GetHead() const;
	 TYPE&     GetTail();
	 TYPE      GetTail() const;
                                         // Operations
	 TYPE      RemoveHead();
	 TYPE      RemoveTail();
	                                       // Add before head or after tail
   POSITION  AddHead( ARG_TYPE NewElement );
	 POSITION  AddTail( ARG_TYPE NewElement );

	 void      AddHead(CLListImpl* pNewList);  // Add another list
	 void      AddTail(CLListImpl* pNewList);
	
	 void      RemoveAll();                // Remove all elements

   POSITION  GetHeadPosition() const;
	 POSITION  GetTailPosition() const;
	 TYPE&     GetNext(POSITION& rPosition);       // return *Position++
	 TYPE      GetNext(POSITION& rPosition) const; // return *Position++
	 TYPE&     GetPrev(POSITION& rPosition);       // return *Position--
	 TYPE      GetPrev(POSITION& rPosition) const; // return *Position--

	 // Getting/modifying an element at a given position
	 TYPE&     GetAt(POSITION Position);
	 TYPE      GetAt(POSITION Position) const;
	 void      SetAt(POSITION Pos, ARG_TYPE NewElement);
	 void      RemoveAt(POSITION Position);

	 // inserting before or after a given position
	 POSITION InsertBefore(POSITION position, ARG_TYPE newElement);
	 POSITION InsertAfter(POSITION position, ARG_TYPE newElement);

	 // Helper functions (note: O(n) speed)

	 // Defaults to starting at the HEAD, return NULL if not found
	 POSITION Find(ARG_TYPE SearchValue, POSITION StartAfter = NULL) const;

	 // Get the 'nIndex'th element (may return NULL)
   POSITION FindIndex(int nIndex) const;
		
  // Implementation
  protected:
	  CNode*   m_pNodeHead;
	  CNode*   m_pNodeTail;
	  int      m_nCount;
	  CNode*   m_pNodeFree;
	  struct   CPlex* m_pBlocks;
	  int m_nBlockSize;

	  CNode*   NewNode(CNode*, CNode*);
	  void     FreeNode(CNode*);

#ifdef _DEBUG

  void AssertValid() const;

#endif //_DEBUG

}; //end class CLListImpl

/////////////////////////////////////////////////////////////////////////////
// CLListImpl<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
inline int CLListImpl<TYPE, ARG_TYPE>::GetCount() const
	{ return m_nCount; }

template<class TYPE, class ARG_TYPE>
inline BOOL CLListImpl<TYPE, ARG_TYPE>::IsEmpty() const
	{ return m_nCount == 0; }

template<class TYPE, class ARG_TYPE>
inline TYPE& CLListImpl<TYPE, ARG_TYPE>::GetHead()
	{ 
    _ASSERT( NULL != m_pNodeHead );
		return m_pNodeHead->data;
  }

template<class TYPE, class ARG_TYPE>
inline TYPE CLListImpl<TYPE, ARG_TYPE>::GetHead() const
	{ 
    _ASSERT( NULL != m_pNodeHead );
		return m_pNodeHead->data; 
  }

template<class TYPE, class ARG_TYPE>
inline TYPE& CLListImpl<TYPE, ARG_TYPE>::GetTail()
	{ 
    _ASSERT( NULL != m_pNodeTail );
		return m_pNodeTail->data; 
  }

template<class TYPE, class ARG_TYPE>
inline TYPE CLListImpl<TYPE, ARG_TYPE>::GetTail() const
	{ 
    _ASSERT( NULL != m_pNodeTail );
		return m_pNodeTail->data; 
  }

template<class TYPE, class ARG_TYPE>
inline POSITION CLListImpl<TYPE, ARG_TYPE>::GetHeadPosition() const
	{ return (POSITION)m_pNodeHead; }

template<class TYPE, class ARG_TYPE>
inline POSITION CLListImpl<TYPE, ARG_TYPE>::GetTailPosition() const
	{ return (POSITION)m_pNodeTail; }

template<class TYPE, class ARG_TYPE>
inline TYPE& CLListImpl<TYPE, ARG_TYPE>::GetNext(POSITION& rPosition) // return *Position++
	{ 
    CNode* pNode = (CNode*) rPosition;
		_ASSERT(IsValidAddress(pNode, sizeof(CNode)));
		rPosition = (POSITION) pNode->pNext;
		return pNode->data;
  }

template<class TYPE, class ARG_TYPE>
inline TYPE CLListImpl<TYPE, ARG_TYPE>::GetNext(POSITION& rPosition) const // return *Position++
	{ 
    CNode* pNode = (CNode*) rPosition;
		_ASSERT(IsValidAddress(pNode, sizeof(CNode)));
		rPosition = (POSITION) pNode->pNext;
		return pNode->data;
  }

template<class TYPE, class ARG_TYPE>
inline TYPE& CLListImpl<TYPE, ARG_TYPE>::GetPrev(POSITION& rPosition) // return *Position--
	{ 
    CNode* pNode = (CNode*) rPosition;
		_ASSERT( IsValidAddress(pNode, sizeof(CNode)) );
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data;
  }

template<class TYPE, class ARG_TYPE>
inline TYPE CLListImpl<TYPE, ARG_TYPE>::GetPrev(POSITION& rPosition) const // return *Position--
	{ 
    CNode* pNode = (CNode*) rPosition;
		ASSERT( IsValidAddress(pNode, sizeof(CNode)) );
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data;
  }

template<class TYPE, class ARG_TYPE>
inline TYPE& CLListImpl<TYPE, ARG_TYPE>::GetAt(POSITION Position)
	{ 
    CNode* pNode = (CNode*)Position;
		_ASSERT( IsValidAddress(pNode, sizeof(CNode)) );
		return pNode->data;
  }

template<class TYPE, class ARG_TYPE>
inline TYPE CLListImpl<TYPE, ARG_TYPE>::GetAt(POSITION Position) const
	{ 
    CNode* pNode = (CNode*) Position;
		_ASSERT( IsValidAddress(pNode, sizeof(CNode)) );
		return pNode->data;
  }

template<class TYPE, class ARG_TYPE>
inline void CLListImpl<TYPE, ARG_TYPE>::SetAt(POSITION Pos, ARG_TYPE NewElement)
	{ 
    CNode* pNode = (CNode*)Pos;
		_ASSERT( IsValidAddress(pNode, sizeof(CNode)) );
		pNode->data = newElement;
  }


template<class TYPE, class ARG_TYPE>
CLListImpl<TYPE, ARG_TYPE>::CLListImpl( int nBlockSize )
{
	_ASSERT( nBlockSize > 0 );

	m_nCount     = 0;
	m_pNodeHead  = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks    = NULL;
	m_nBlockSize = nBlockSize;
}

template<class TYPE, class ARG_TYPE>
void CLListImpl<TYPE, ARG_TYPE>::RemoveAll()
{
	// destroy elements
	CNode* pNode;
	for( pNode = m_pNodeHead; pNode != NULL; pNode = pNode->pNext )
		(pNode->data).~TYPE();

	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

template<class TYPE, class ARG_TYPE>
CLListImpl<TYPE, ARG_TYPE>::~CLListImpl()
{
	RemoveAll();
	_ASSERT(m_nCount == 0);
}


/////////////////////////////////////////////////////////////////////////////
// Node helpers
//
//  Implementation note: CNode's are stored in CPlex blocks and
//  chained together. Free blocks are maintained in a singly linked list
//  using the 'pNext' member of CNode with 'm_pNodeFree' as the head.
//  Used blocks are maintained in a doubly linked list using both 'pNext'
//  and 'pPrev' as links and 'm_pNodeHead' and 'm_pNodeTail'
//  as the head/tail.
//
//  We never free a CPlex block unless the List is destroyed or RemoveAll()
//  is used - so the total number of CPlex blocks may grow large depending
//  on the maximum past size of the list.
//


template<class TYPE, class ARG_TYPE>
CLListImpl<TYPE, ARG_TYPE>::CNode*
CLListImpl<TYPE, ARG_TYPE>::NewNode(CLListImpl::CNode* pPrev, CLListImpl::CNode* pNext)
{
	if( NULL == m_pNodeFree )
	{
		// add another block
		CPlex* pNewBlock = CPlex::Create( m_pBlocks, m_nBlockSize, sizeof(CNode) );

		// chain them into free list
		CNode* pNode = (CNode*) pNewBlock->data();
		// free in reverse order to make it easier to debug
		pNode += m_nBlockSize - 1;
		for( int i = m_nBlockSize-1; i >= 0; i--, pNode-- )
		{
			pNode->pNext = m_pNodeFree;
			m_pNodeFree = pNode;
		}
	}
	_ASSERT( NULL != m_pNodeFree );  // we must have something

	CLListImpl::CNode* pNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNode->pPrev = pPrev;
	pNode->pNext = pNext;
	m_nCount++;
	_ASSERT(m_nCount > 0);  // make sure we don't overflow

	new (&pNode->data) TYPE; // Placement new 

	return pNode;
}


template<class TYPE, class ARG_TYPE>
void CLListImpl<TYPE, ARG_TYPE>::FreeNode(CLListImpl::CNode* pNode)
{
	(pNode->data).~TYPE();
	pNode->pNext = m_pNodeFree;
	m_pNodeFree = pNode;
	m_nCount--;
	_ASSERT(m_nCount >= 0);  // make sure we don't underflow

	// if no more elements, cleanup completely
	if( 0 == m_nCount )
		RemoveAll();
}

template<class TYPE, class ARG_TYPE>
POSITION CLListImpl<TYPE, ARG_TYPE>::AddHead( ARG_TYPE NewElement )
{
  _ASSERT( NULL != NewElement );

	CNode* pNewNode = NewNode( NULL, m_pNodeHead );
	pNewNode->data = NewElement;
	if( NULL != m_pNodeHead )
		m_pNodeHead->pPrev = pNewNode;
	else
		m_pNodeTail = pNewNode;

	m_pNodeHead = pNewNode;
	return (POSITION)pNewNode;
}


template<class TYPE, class ARG_TYPE>
POSITION CLListImpl<TYPE, ARG_TYPE>::AddTail(ARG_TYPE NewElement)
{
	_ASSERT( NULL != NewElement );

	CNode* pNewNode = NewNode( m_pNodeTail, NULL );
	pNewNode->data = NewElement;
	if( NULL != m_pNodeTail )
		m_pNodeTail->pNext = pNewNode;
	else
		m_pNodeHead = pNewNode;

	m_pNodeTail = pNewNode;
	return (POSITION)pNewNode;
}


template<class TYPE, class ARG_TYPE>
void CLListImpl<TYPE, ARG_TYPE>::AddHead( CLListImpl* pNewList )
{
	_ASSERT( NULL != pNewList );

	// Add a list of same elements to head (maintain order)
	POSITION Pos = pNewList->GetTailPosition();
	while( NULL != Pos )
		AddHead(pNewList->GetPrev( Pos ));
}


template<class TYPE, class ARG_TYPE>
void CLListImpl<TYPE, ARG_TYPE>::AddTail(CLListImpl* pNewList)
{
	_ASSERT( NULL != pNewList );

	// Add a list of same elements
	POSITION Pos = pNewList->GetHeadPosition();
	while( NULL != Pos )
		AddTail(pNewList->GetNext( Pos ));
}


template<class TYPE, class ARG_TYPE>
TYPE CLListImpl<TYPE, ARG_TYPE>::RemoveHead()
{
	_ASSERT( NULL != m_pNodeHead );  // don't call on empty list !!!
	_ASSERT( IsValidAddress( m_pNodeHead, sizeof(CNode)) );

	CNode* pOldNode = m_pNodeHead;
	TYPE returnValue = pOldNode->data;

	m_pNodeHead = pOldNode->pNext;
	if( NULL != m_pNodeHead )
		m_pNodeHead->pPrev = NULL;
	else
		m_pNodeTail = NULL;

	FreeNode(pOldNode);
	return returnValue;
}


template<class TYPE, class ARG_TYPE>
TYPE CLListImpl<TYPE, ARG_TYPE>::RemoveTail()
{
	_ASSERT( NULL != m_pNodeTail );  // don't call on empty list !!!
	_ASSERT( IsValidAddress( m_pNodeTail, sizeof(CNode)) );

	CNode* pOldNode = m_pNodeTail;
	TYPE returnValue = pOldNode->data;

	m_pNodeTail = pOldNode->pPrev;
	if( NULL != m_pNodeTail )
		m_pNodeTail->pNext = NULL;
	else
		m_pNodeHead = NULL;

	FreeNode(pOldNode);
	return returnValue;
}


template<class TYPE, class ARG_TYPE>
POSITION CLListImpl<TYPE, ARG_TYPE>::InsertBefore(POSITION Position, ARG_TYPE NewElement)
{
	_ASSERT( NULL != NewElement );

	if( NULL == Position )
		return AddHead( NewElement ); // insert before nothing -> head of the list

	// Insert it before position
	CNode* pOldNode = (CNode*)Position;
	CNode* pNewNode = NewNode( pOldNode->pPrev, pOldNode );
	pNewNode->data  = NewElement;

	if( NULL != pOldNode->pPrev )
	{
		_ASSERT( IsValidAddress( pOldNode->pPrev, sizeof(CNode)) );
		pOldNode->pPrev->pNext = pNewNode;
	}
	else
	{
		_ASSERT( pOldNode == m_pNodeHead );
		m_pNodeHead = pNewNode;
	}
	pOldNode->pPrev = pNewNode;
	return (POSITION)pNewNode;
}


template<class TYPE, class ARG_TYPE>
POSITION CLListImpl<TYPE, ARG_TYPE>::InsertAfter(POSITION Position, ARG_TYPE NewElement)
{
	ASSERT( NULL != NewElement );

	if( NULL == Position )
		return AddTail( NewElement ); // insert after nothing -> tail of the list

	// Insert it before position
	CNode* pOldNode = (CNode*)Position;
	_ASSERT( IsValidAddress( pOldNode, sizeof(CNode) ) );
	CNode* pNewNode = NewNode( pOldNode, pOldNode->pNext );
	pNewNode->data = NewElement;

	if( NULL != pOldNode->pNext )
	{
		_ASSERT( IsValidAddress( pOldNode->pNext, sizeof(CNode)) );
		pOldNode->pNext->pPrev = pNewNode;
	}
	else
	{
		_ASSERT( pOldNode == m_pNodeTail );
		m_pNodeTail = pNewNode;
	}
	pOldNode->pNext = pNewNode;
	return (POSITION)pNewNode;
}


template<class TYPE, class ARG_TYPE>
void CLListImpl<TYPE, ARG_TYPE>::RemoveAt( POSITION Position )
{
  _ASSERT( NULL != Position );

	CNode* pOldNode = (CNode*)Position;
	_ASSERT( IsValidAddress( pOldNode, sizeof(CNode)) );

	// Remove pOldNode from list
	if( pOldNode == m_pNodeHead )
	{
		m_pNodeHead = pOldNode->pNext;
	}
	else
	{
		_ASSERT( IsValidAddress( pOldNode->pPrev, sizeof(CNode)) );
		pOldNode->pPrev->pNext = pOldNode->pNext;
	}
	if( pOldNode == m_pNodeTail )
	{
		m_pNodeTail = pOldNode->pPrev;
	}
	else
	{
		_ASSERT( IsValidAddress( pOldNode->pNext, sizeof(CNode)) );
		pOldNode->pNext->pPrev = pOldNode->pPrev;
	}
	FreeNode( pOldNode );
}


template<class TYPE, class ARG_TYPE>
POSITION CLListImpl<TYPE, ARG_TYPE>::FindIndex(int nIndex) const
{
	if( nIndex >= m_nCount || nIndex < 0 )
		return NULL;  // went too far

	CNode* pNode = m_pNodeHead;
	while (nIndex--)
	{
		_ASSERT( IsValidAddress( pNode, sizeof(CNode)) );
		pNode = pNode->pNext;
	}
	return (POSITION)pNode;
}


template<class TYPE, class ARG_TYPE>
POSITION CLListImpl<TYPE, ARG_TYPE>::Find(ARG_TYPE SearchValue, POSITION StartAfter) const
{
	_ASSERT( NULL != SearchValue );

	CNode* pNode = (CNode*)StartAfter;
	if( NULL == pNode )
	{
		pNode = m_pNodeHead;  // start at head
	}
	else
	{
		_ASSERT( IsValidAddress( pNode, sizeof(CNode)) );
		pNode = pNode->pNext;  // start after the one specified
	}

	for (; pNode != NULL; pNode = pNode->pNext)
		if (CompareElements<TYPE>(&pNode->data, &searchValue))
			return (POSITION)pNode;

	return NULL;
}

#ifdef _DEBUG 

template<class TYPE, class ARG_TYPE>
void CLListImpl<TYPE, ARG_TYPE>::AssertValid() const
{
	if( 0 == m_nCount )
	{
		// empty list
		_ASSERT( NULL == m_pNodeHead );
		_ASSERT( NULL == m_pNodeTail );
	}
	else
	{
		// non-empty list
		_ASSERT( IsValidAddress(m_pNodeHead, sizeof(CNode)) );
		_ASSERT( IsValidAddress(m_pNodeTail, sizeof(CNode)) );
	}
}
#endif //_DEBUG

#endif //__CLASS_CLLISTIMPL__
