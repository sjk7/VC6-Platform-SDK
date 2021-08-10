//+---------------------------------------------------------------------------
//
//  Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//  File:       ClntLst.h
//
//  Contents:   class to implement a simple Linked list of clients
//
//  Notes:
//
//----------------------------------------------------------------------------
#include <shlwapi.h>
#include "rqs.h"

class ClientList
{
    private:
        typedef struct _tag_LIST_NODE
        {
          struct _tag_LIST_NODE* pNext;
          RqsClient* pClient; 
        } LISTNODE;

        LISTNODE* m_pHead;
        LISTNODE* m_pTail;
        int m_iCount;

    public:

    class Iterator
    {
    friend ClientList;

    public:
        Iterator() : m_pHead(NULL), m_pTail(NULL), m_pCurrent(NULL){};
        ~Iterator() {};
		
        BOOL Next()
        {
            BOOL bReturn = TRUE;

            if (m_pCurrent)
            {
                m_pCurrent = m_pCurrent->pNext;
            }
            else
            {
                bReturn = FALSE;
            }

            return bReturn;
        }

        BOOL AtEnd() const
        {
            return (m_pCurrent == NULL);
        }

        RqsClient* GetItem() const
        {
            if (m_pCurrent)
            {
                return m_pCurrent->pClient;
            }
            else
            {
                return NULL;
            }
        } 


    private:
        LISTNODE* m_pHead;
        LISTNODE* m_pTail;
        LISTNODE* m_pCurrent;
    };

    ClientList()
    {
        m_pHead = m_pTail = NULL;
        m_iCount = 0;
    }

    ~ClientList()
    {
        while (NULL != m_pHead)
        {
            LISTNODE* pTemp = m_pHead->pNext;
            RuFree(m_pHead);
            m_pHead = pTemp;
        }
    }

    HRESULT InsertBack(RqsClient* pClient)
    {
        HRESULT hr = S_OK;

        if (m_pTail)
        {
            m_pTail->pNext = (LISTNODE*)RuAlloc(sizeof(LISTNODE), TRUE);
            if(m_pTail->pNext)
            {
                m_pTail->pNext->pClient = pClient;
                m_pTail->pNext->pNext = NULL;
                m_pTail = m_pTail->pNext;
                m_iCount++;
            }
            else
            {
                hr = E_OUTOFMEMORY;
            }
        }
        else
        {
            m_pHead = m_pTail = (LISTNODE*)RuAlloc(sizeof(LISTNODE), TRUE);
            if (m_pHead)
            {
                m_pHead->pClient = pClient;
                m_pHead->pNext = NULL;
                m_iCount = 1;
            }
            else
            {
                hr = E_OUTOFMEMORY;
            }
        }

        return hr;
    }

    VOID GetIterator(OUT ClientList::Iterator& It) const
    {         
        if (m_pHead)
        {
            It.m_pHead = m_pHead;
            It.m_pTail = m_pTail;
        }   
        else
        {
            It.m_pHead = NULL;
            It.m_pTail = NULL;
        }

        It.m_pCurrent = m_pHead;
    }

    HRESULT RemoveItem(RqsClient* pClient)
    {
        HRESULT hr = S_FALSE;
        //
        //  Remove the first node with the given Client pointer.
        //
        if (m_pHead)
        {
            LISTNODE* pCurrent = m_pHead;
            LISTNODE* pFollower = NULL;

			while (pCurrent)
			{
				if (pCurrent->pClient == pClient)
				{
					//
					//  We have an item to remove
					//
					if (pFollower)
					{
						pFollower->pNext = pCurrent->pNext;
						if (pCurrent == m_pTail)
						{
							m_pTail = pFollower; 
						}
					}
					else
					{
						m_pHead = pCurrent->pNext;
						if(pCurrent == m_pTail)
						{
							m_pTail = m_pHead;
						}
					}

					RuFree(pCurrent);
					pCurrent = NULL;
					m_iCount--;
					hr = S_OK;
				}
				else
				{
					pFollower = pCurrent;
					pCurrent = pCurrent->pNext;
				}
			}
        }

        return hr;
    }
};