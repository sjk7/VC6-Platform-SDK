/* Copyright 1992 - 2000 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
*/

#include "pipe.hxx"

/******************************************
* Helper functions for pipes
******************************************/

STDMETHODIMP GenericPull(IPipeLong *pPipe, LONG *buff, ULONG *pPulled, ULONG lElements)
{
   HRESULT hr = S_OK;
   ULONG lcount = 0;
   ULONG lRemain = 0;
   ULONG lTransfer = 0;

   if (0 == lElements) { lRemain = 1; }
   else { lRemain = lElements; }
   
   do
   {
      if (1 == lRemain) { lTransfer = OPTIMUM_SIZE; }
      else { lTransfer = lRemain; } 

      lcount=0;
      hr = pPipe->Pull(buff, lTransfer, &lcount);
      if (FAILED(hr)) { return hr; }

      // Verify the data was pulled properly
      hr = DrainBuffer(buff, lcount, *pPulled);
      if (FAILED(hr)) { return hr; }
      *pPulled = *pPulled + lcount;
      if ( 1 != lRemain )
      { lRemain = lRemain - lcount; }

   } while ( lRemain > 0 && lcount > 0);
   return S_OK;
}

STDMETHODIMP GenericPush(IPipeLong *pPipe, LONG *buff, ULONG lElements)
{
   HRESULT hr = S_OK;
   ULONG lTransfer = 0;

   lTransfer = lElements;
   hr = PopulateBuffer(buff, lTransfer, 0);
   if (FAILED(hr)) { return hr; }

   hr = pPipe->Push(buff, lTransfer);
   if (FAILED(hr)) { return hr; }

   return S_OK;
}



STDMETHODIMP PopulateBuffer(long *buff, DWORD dwElementsCount,
                          DWORD dwStartIdx)
{
   ULONG i;
   
   for(i = dwStartIdx; i < dwElementsCount + dwStartIdx; i++)
   {
      // Can do something fancy here.
      *buff++ = i;   
   }
      
   return S_OK;
};

STDMETHODIMP DrainBuffer(long *buff, 
                            DWORD dwElementsCount,
                            DWORD dwStartIdx)
{
   ULONG i;
   
   for(i = dwStartIdx; i < dwElementsCount + dwStartIdx; i++)
   {
      // TODO: Need to output data to a file
      if( ULONG(*buff) != i ) 
      {
         return E_FAIL;
      }      
      buff++;
   }
   return S_OK;
};



/******************************************
* Class CSamplePipe Implementation
******************************************/

CSamplePipe::CSamplePipe() :
   m_cRef(1), m_nPushSeq(0), m_nPullSeq(0),
   m_pBuffer(NULL), 
   m_dwOutPipeRcvd(0), m_dwInPipeSent(0)
{
};

CSamplePipe::~CSamplePipe()
{
   delete m_pBuffer;
};

STDMETHODIMP CSamplePipe::QueryInterface(REFIID riid, void** ppv)
{
   
    *ppv = NULL;

    if (IsEqualIID(IID_IPipeLong, riid))
    {
        *ppv = static_cast<IPipeLong *>(this);
    }
    else if (IsEqualIID(IID_IUnknown, riid))
    {
        *ppv = static_cast<IPipeLong *>(this);
    }
    else
    {
      return E_NOINTERFACE;
    }

   reinterpret_cast<IUnknown*>(*ppv)->AddRef();
   return S_OK;
};

STDMETHODIMP_(ULONG) CSamplePipe::AddRef()
{
    InterlockedIncrement((LONG *)&m_cRef);
    return m_cRef;
};

STDMETHODIMP_(ULONG) CSamplePipe::Release()
{
    ULONG cLockedRefs = InterlockedDecrement((LONG *)&m_cRef);
    if( cLockedRefs == 0 )
    {
       delete this;
    }
    return cLockedRefs;
};

STDMETHODIMP CSamplePipe::Pull(long *buf, ULONG cRequest, ULONG *pcReturned)
{
   HRESULT     hr=S_OK;
   DWORD       dwElementsAvailable = BUF_SIZE; // Should really be a member variable
   ULONG        lElements;
   

   //cout << "Pull being called on the pipe" << endl;
   
   *pcReturned = 0;

   // Adjust the number of elements we actually return
   lElements = dwElementsAvailable - m_dwInPipeSent;
   if( lElements < 0 )
       lElements = 0;
       
   if( lElements > cRequest )
       lElements = cRequest;

   // Fill the buffer                                       
   hr = PopulateBuffer(buf, (DWORD) lElements, m_dwInPipeSent);
   if( FAILED(hr) )
   {
        //cout << "Populate buffer failed" << endl;
	return hr;
   }
   
   // Set elements count
   *pcReturned = (DWORD) lElements;
   m_dwInPipeSent += lElements;
   
   //cout << "cRequested = " << cRequest << " and Returned = " << lElements 
   //   << endl << endl ;
   
   if ( 0 == lElements)
   {
      m_dwInPipeSent = 0;
      //cout << "!WARNING! The pipe is drained .. Returning 0 count.."
      //    << " Pull sequence #" << m_nPullSeq << " is over" << endl << endl;
      m_nPullSeq++;
   }

   return S_OK;
}

STDMETHODIMP CSamplePipe::Push(long *buf, ULONG cSent)
{
   HRESULT hr=S_OK;
      
   //cout << "Push being called on the pipe" << endl;
   //cout << "cSent = " << cSent << " and Received before this = " << m_dwOutPipeRcvd 
   //     << endl << endl;

   hr = DrainBuffer(buf, cSent, m_dwOutPipeRcvd);
   if( FAILED(hr) )
   {
       //cout << "Unable to push the data received to the buffer !!" << endl;
       return hr;
   }
       
   if ( 0 == cSent )
   {
       m_dwOutPipeRcvd = 0;
       //cout << "!WARNING! 0 count received at the push side.."
       //     << " Push sequence #" << m_nPushSeq << " is over."
       //     << endl << endl;
       m_nPushSeq++;
   }
   else
   {
       // Inc count for number of elems received.
       m_dwOutPipeRcvd += cSent;
   }
           
   return hr;
}
