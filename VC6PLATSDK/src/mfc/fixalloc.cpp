// fixalloc.cpp - implementation of fixed block allocator

#include "stdafx.h"
#include "fixalloc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// CFixedAlloc

CFixedAlloc::CFixedAlloc(UINT nAllocSize, UINT nBlockSize)
{
	ASSERT(nAllocSize >= sizeof(CNode));
	ASSERT(nBlockSize > 1);

	if (nAllocSize < sizeof(CNode))
		nAllocSize = sizeof(CNode);
	if (nBlockSize <= 1)
		nBlockSize = 64;

	m_nAllocSize = nAllocSize;
	m_nBlockSize = nBlockSize;
	m_pNodeFree = NULL;
	m_pBlocks = NULL;
    __try {
		InitializeCriticalSection(&m_protect);
    } __except (GetExceptionCode() == STATUS_NO_MEMORY ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
        AfxThrowMemoryException();
    }
}

CFixedAlloc::~CFixedAlloc()
{
	FreeAll();
	DeleteCriticalSection(&m_protect);
}

void CFixedAlloc::FreeAll()
{
	EnterCriticalSection(&m_protect);
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
	m_pNodeFree = NULL;
	LeaveCriticalSection(&m_protect);
}

void* CFixedAlloc::Alloc()
{
	EnterCriticalSection(&m_protect);
	if (m_pNodeFree == NULL)
	{
		CPlex* pNewBlock = NULL;
		TRY
		{
			// add another block
			pNewBlock = CPlex::Create(m_pBlocks, m_nBlockSize, m_nAllocSize);
		}
		CATCH_ALL(e)
		{
			LeaveCriticalSection(&m_protect);
			THROW_LAST();
		}
		END_CATCH_ALL

		// chain them into free list
		CNode* pNode = (CNode*)pNewBlock->data();
		// free in reverse order to make it easier to debug
		(BYTE*&)pNode += (m_nAllocSize * m_nBlockSize) - m_nAllocSize;
		for (int i = m_nBlockSize-1; i >= 0; i--, (BYTE*&)pNode -= m_nAllocSize)
		{
			pNode->pNext = m_pNodeFree;
			m_pNodeFree = pNode;
		}
	}
	ASSERT(m_pNodeFree != NULL);  // we must have something

	// remove the first available node from the free list
	void* pNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;

	LeaveCriticalSection(&m_protect);
	return pNode;
}

void CFixedAlloc::Free(void* p)
{
	if (p != NULL)
	{
		EnterCriticalSection(&m_protect);

		// simply return the node to the free list
		CNode* pNode = (CNode*)p;
		pNode->pNext = m_pNodeFree;
		m_pNodeFree = pNode;
		LeaveCriticalSection(&m_protect);
	}
}
