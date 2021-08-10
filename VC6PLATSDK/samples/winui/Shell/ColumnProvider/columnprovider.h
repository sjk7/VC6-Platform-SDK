// ColumnProvider.h: interface for the CColumnProvider class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLUMNPROVIDER_H__01039060_03F3_11D3_B1BF_00600893AD51__INCLUDED_)
#define AFX_COLUMNPROVIDER_H__01039060_03F3_11D3_B1BF_00600893AD51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CColumnProvider : public IColumnProvider  
{
public:
    CColumnProvider();
    virtual ~CColumnProvider();

    // IUnknown methods
    STDMETHODIMP QueryInterface (REFIID riid, LPVOID *ppvObject);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IColumnProvider methods
    STDMETHODIMP Initialize (LPCSHCOLUMNINIT psci);
    STDMETHODIMP GetColumnInfo (DWORD dwIndex, LPSHCOLUMNINFO psci);
    STDMETHODIMP GetItemData (LPCSHCOLUMNID pscid, LPCSHCOLUMNDATA pscd, VARIANT *pvartData);

private:
    ULONG m_nRefCount;
};

#endif // !defined(AFX_COLUMNPROVIDER_H__01039060_03F3_11D3_B1BF_00600893AD51__INCLUDED_)
