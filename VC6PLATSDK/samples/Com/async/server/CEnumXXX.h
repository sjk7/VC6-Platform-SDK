// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------

#if !defined(__CEnumXXX__)
#define __CEnumXXX__

template<class T, class ELT_T, class IFACE>
class CEnumXXX : public IFACE
{
//private:
public:  //TODO: set back to private after testing
        ULONG           m_cRef;         // Object reference count
        ULONG           m_iCur;         // Current element.
        ULONG           m_cELT;         // Number of element in container
        ELT_T*          m_prgELT;       // array of elements
		LPUNKNOWN		m_lpunk;		// Back pointer enumeratee
		REFIID			m_iid;

/*
 * The element list passed to this function will used directly by this class do not ever
 * free the list once it's been passed in
 */
protected:
	virtual bool __stdcall Init(ELT_T *elemlist);
	CEnumXXX(LPUNKNOWN lpUnk, REFIID iid, DWORD nCount);

public:
	virtual ~CEnumXXX();
	static T* __stdcall Create(LPUNKNOWN lpUnk, DWORD nCount, ELT_T* elemlist);

private:
	CEnumXXX() :m_iid(CLSID_NULL) {};

public:

		// IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID iid, PVOID *ppv);
    virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();
	virtual void __stdcall FinalRelease();

        //IEnumFORMATETC members
	virtual HRESULT __stdcall Next(ULONG celt, ELT_T* rgelt, PULONG pceltFetched);
	virtual HRESULT __stdcall Skip(ULONG celt);
	virtual HRESULT __stdcall Reset(void);
	virtual HRESULT __stdcall Clone(IFACE **ppenum);
};


#include "CEnumXXX.cpp"
#endif //__CEnumXXX__
