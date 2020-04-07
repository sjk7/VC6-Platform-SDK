#include "ISimpleInterface.h"
#include <objbase.h>
#include <iostream.h>


class CSimpleClass: ISimpleInterface
{  
   private:
   
      ULONG m_cRef;
   
   public:

   CSimpleClass();
   ~CSimpleClass();

   STDMETHODIMP QueryInterface(REFIID riid, void** ppv);
   STDMETHODIMP_(ULONG) AddRef(void);
   STDMETHODIMP_(ULONG) Release(void);

   STDMETHODIMP InPipeSample(IPipeLong *pInPipe);
   STDMETHODIMP OutPipeSample(IPipeLong **pOutPipe);
   STDMETHODIMP InOutPipeSample(IPipeLong **ppInOutPipe);
   STDMETHODIMP InInOutPipesSample(IPipeLong *pInPipe1, IPipeLong *pInPipe2,
                                   IPipeLong **ppOutPipe);
};


class CFactory: public IClassFactory
{  
   private:
   
      ULONG m_cRef;
   
   public:

   CFactory();
   ~CFactory();

   STDMETHODIMP QueryInterface(REFIID riid, void** ppv);
   STDMETHODIMP_(ULONG) AddRef(void);
   STDMETHODIMP_(ULONG) Release(void);

   STDMETHODIMP CreateInstance(IUnknown* pUnkwnOuter, REFIID riid, void** ppv);
   STDMETHODIMP LockServer(BOOL bLock);

};
