#ifndef _PLUG_UTILS_H_
#define _PLUG_UTILS_H_

#define ASSERT assert

//****************************************************************************
//
// CLASS RefCount
//
//****************************************************************************

class RefCount
{
private:
   LONG m_cRef;

public:
   RefCount();
   // Virtual destructor defers destruction to destructor of derived class.
   virtual ~RefCount();

   ULONG STDMETHODCALLTYPE AddRef(void);
   ULONG STDMETHODCALLTYPE Release(void);
};



//****************************************************************************
//
// CLASS CNotify
//
// Notification sink
//
//****************************************************************************

class CNotify
{
private:
    DWORD  m_dwCookie;
	IUnknown * m_pUnk;
    IConnectionPoint           * m_pcnp;
    IConnectionPointContainer  * m_pcnpcnt;
public:
    CNotify(void);
    ~CNotify();

    HRESULT Connect(IUnknown *pUnk, REFIID riid, IUnknown *pUnkN);
    HRESULT Disconnect(void);

    IUnknown * GetPunk() {return m_pUnk;}
};

#endif  // _PLUG_UTILS_H_

