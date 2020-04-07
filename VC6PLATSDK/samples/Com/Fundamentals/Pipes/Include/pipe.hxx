#ifndef __PIPE_HXX__
#define __PIPE_HXX__

#include "objbase.h"
#include "iostream.h"

#define BUF_SIZE 2000;
#define OPTIMUM_SIZE 800;

/***** Helper functions ********************/

STDMETHODIMP GenericPull(IPipeLong *pPipe, LONG *buff, ULONG *pPulled, ULONG lElements);

STDMETHODIMP GenericPush(IPipeLong *pPipe, LONG *buff, ULONG lElements);

STDMETHODIMP PopulateBuffer(long *buff, DWORD dwElementsCount,
                          DWORD dwStartIdx);
STDMETHODIMP DrainBuffer(long *buff, 
                            DWORD dwElementsCount,
                            DWORD dwStartIdx);

/********** Sample Pipe ***************************/

class CSamplePipe : public IPipeLong
{
protected:
   LONG    m_cRef;
   ULONG   m_nPushSeq, m_nPullSeq;
   LONG   *m_pBuffer;
   DWORD   m_dwOutPipeRcvd;
   DWORD   m_dwInPipeSent;

public:
   CSamplePipe();
   ~CSamplePipe();

   // IUnknown
   STDMETHODIMP QueryInterface (REFIID iid, void **ppv);
   STDMETHODIMP_(ULONG) AddRef(void);
   STDMETHODIMP_(ULONG) Release(void);

   // IPipeLong
   STDMETHODIMP Pull(long *buf, ULONG cRequest, ULONG *pcReturned);
   STDMETHODIMP Push(long *buf, ULONG cSent);
};

#endif // __PIPE_HXX__
