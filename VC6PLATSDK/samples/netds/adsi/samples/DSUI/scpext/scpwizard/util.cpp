//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       util.cpp
//
//--------------------------------------------------------------------------

#include "stdafx.h"
#include "util.h"

HRESULT SetStringAttribute(IADs* pIADs, LPCWSTR lpszAttr, LPCWSTR lpszValue)
{
  ASSERT(pIADs != NULL);
  ASSERT(lpszAttr != NULL);

  // Allocate the string
  BSTR bstrAttr = ::SysAllocString(lpszAttr);

  // Imbed the value in a VARIANT
  HRESULT hr = S_OK;
  CComVariant varValue;
  varValue.vt = VT_BSTR;
  varValue.bstrVal = ::SysAllocString(lpszValue);

  // Set the value in the temporary object
  hr = pIADs->Put(bstrAttr, varValue);

  // Clean up memory
  ::SysFreeString(bstrAttr);
  return hr;
}

HRESULT SetStringListAttribute(IADs* pIADs, LPCWSTR lpszAttr, CStringList& szValueList)
{
  CComVariant var;
  HRESULT hr = S_OK;

  hr = StringListToVariant(var, szValueList);
  if (SUCCEEDED(hr))
  {
    BSTR bstrAttr = ::SysAllocString(lpszAttr);
    hr = pIADs->Put(bstrAttr, var);
    ::SysFreeString(bstrAttr);
  }
  return hr;
}

HRESULT StringListToVariant( VARIANT& refvar, const CStringList& refstringlist)
{
  HRESULT hr = S_OK;
  int cCount = refstringlist.GetCount();

  SAFEARRAYBOUND rgsabound[1];
  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = cCount;

  SAFEARRAY* psa = SafeArrayCreate(VT_VARIANT, 1, rgsabound);
  if (NULL == psa)
    return E_OUTOFMEMORY;

  VariantClear( &refvar );
  V_VT(&refvar) = VT_VARIANT|VT_ARRAY;
  V_ARRAY(&refvar) = psa;

  VARIANT SingleResult;
  VariantInit( &SingleResult );
  V_VT(&SingleResult) = VT_BSTR;
  POSITION pos = refstringlist.GetHeadPosition();
  long i;
  for (i = 0; i < cCount, pos != NULL; i++)
  {
    V_BSTR(&SingleResult) = T2BSTR((LPCTSTR)refstringlist.GetNext(pos));
    hr = SafeArrayPutElement(psa, &i, &SingleResult);
    if( FAILED(hr) )
      return hr;
  }
  if (i != cCount || pos != NULL)
    return E_UNEXPECTED;

  return hr;
} // StringListToVariant()


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CAttributeValueEditor, CEdit)
  ON_CONTROL_REFLECT_EX(EN_CHANGE, OnChange)
END_MESSAGE_MAP()

BOOL CAttributeValueEditor::OnChange()
{
  m_pEditor->OnEditChange();
  return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMultiValuedListBox, CListBox)
  ON_CONTROL_REFLECT_EX(LBN_SELCHANGE, OnSelChange)
END_MESSAGE_MAP()

BOOL CMultiValuedListBox::OnSelChange()
{
  m_pEditor->OnValueSelChange();
  return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CAttributeValueAddButton, CButton)
  ON_CONTROL_REFLECT_EX(BN_CLICKED, OnAdd)
END_MESSAGE_MAP()

BOOL CAttributeValueAddButton::OnAdd()
{
  m_pEditor->OnAddValue();
  return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CAttributeValueDeleteButton, CButton)
  ON_CONTROL_REFLECT_EX(BN_CLICKED, OnDelete)
END_MESSAGE_MAP()

BOOL CAttributeValueDeleteButton::OnDelete()
{
  m_pEditor->OnDeleteValue();
  return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////

CMultiValuedAttributeEditor::CMultiValuedAttributeEditor(CStringList& strrefAttributeList) :
  m_ValueEditor(this),
  m_ValueList(this),
  m_AddButton(this),
  m_DeleteButton(this),
  m_strrefAttributeList(strrefAttributeList)

{
}

BOOL CMultiValuedAttributeEditor::Initialize(UINT nEditBox, 
                                              UINT nListBox, 
                                              UINT nAddButton, 
                                              UINT nDeleteButton, 
                                              CWnd* pParentWnd)
{
  BOOL bRes = TRUE;

  //
  // Subclass controls
  //
  bRes = m_ValueEditor.SubclassDlgItem(nEditBox, pParentWnd);
  ASSERT(bRes);
  if (!bRes) return FALSE;

  bRes = m_ValueList.SubclassDlgItem(nListBox, pParentWnd);
  ASSERT(bRes);
  if (!bRes) return FALSE;

  bRes = m_AddButton.SubclassDlgItem(nAddButton, pParentWnd);
  ASSERT(bRes);
  if (!bRes) return FALSE;

  bRes = m_DeleteButton.SubclassDlgItem(nDeleteButton, pParentWnd);
  ASSERT(bRes);
  if (!bRes) return FALSE;

  //
  // Add strings to list box
  //
  POSITION pos = m_strrefAttributeList.GetHeadPosition();
  while (pos != NULL)
  {
    CString szAddString = m_strrefAttributeList.GetNext(pos);
    m_ValueList.AddString(szAddString);
  }
  return bRes;
}

void CMultiValuedAttributeEditor::OnEditChange()
{
  CString szNewValue;
  m_ValueEditor.GetWindowText(szNewValue);

  m_AddButton.EnableWindow(!szNewValue.IsEmpty());
}

void CMultiValuedAttributeEditor::OnValueSelChange()
{
  int nSelection = m_ValueList.GetCurSel();
  m_DeleteButton.EnableWindow(nSelection != LB_ERR);
}

void CMultiValuedAttributeEditor::OnAddValue()
{
  CString szNewValue;
  m_ValueEditor.GetWindowText(szNewValue);

  m_strrefAttributeList.AddTail(szNewValue);
  if (m_ValueList.AddString(szNewValue) != LB_ERR)
  {
    m_ValueEditor.SetWindowText(_T(""));
  }
}

void CMultiValuedAttributeEditor::OnDeleteValue()
{
  int nSelection = m_ValueList.GetCurSel();
  if (nSelection != LB_ERR)
  {
    m_ValueList.DeleteString(nSelection);

    POSITION pos = m_strrefAttributeList.FindIndex(nSelection);
    if (pos != NULL)
    {
      m_strrefAttributeList.RemoveAt(pos);
    }
  }
}

