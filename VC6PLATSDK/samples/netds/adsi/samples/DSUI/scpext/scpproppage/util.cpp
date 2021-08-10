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

  //
  // Allocate the string
  //
  BSTR bstrAttr = ::SysAllocString(lpszAttr);

  //
  // Imbed the value in a VARIANT
  //
  HRESULT hr = S_OK;
  CComVariant varValue;
  varValue.vt = VT_BSTR;
  varValue.bstrVal = ::SysAllocString(lpszValue);

  //
  // Set the value in the temporary object
  //
  hr = pIADs->Put(bstrAttr, varValue);

  //
  // Clean up memory
  //
  ::SysFreeString(bstrAttr);
  return hr;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

//
// Attribute value edit box
//
BEGIN_MESSAGE_MAP(CAttributeValueEditor, CEdit)
  ON_CONTROL_REFLECT_EX(EN_CHANGE, OnChange)
END_MESSAGE_MAP()

BOOL CAttributeValueEditor::OnChange()
{
  //
  // Let the editor handle the message
  //
  m_pEditor->OnEditChange();
  return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////

//
// Attribute value list box
//
BEGIN_MESSAGE_MAP(CMultiValuedListBox, CListBox)
  ON_CONTROL_REFLECT_EX(LBN_SELCHANGE, OnSelChange)
END_MESSAGE_MAP()

BOOL CMultiValuedListBox::OnSelChange()
{
  //
  // Let the editor handle the message
  //
  m_pEditor->OnValueSelChange();
  return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////

//
// Add button
//
BEGIN_MESSAGE_MAP(CAttributeValueAddButton, CButton)
  ON_CONTROL_REFLECT_EX(BN_CLICKED, OnAdd)
END_MESSAGE_MAP()

BOOL CAttributeValueAddButton::OnAdd()
{
  //
  // Let the editor handle the message
  //
  m_pEditor->OnAddValue();
  return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////

//
// Delete button
//
BEGIN_MESSAGE_MAP(CAttributeValueDeleteButton, CButton)
  ON_CONTROL_REFLECT_EX(BN_CLICKED, OnDelete)
END_MESSAGE_MAP()

BOOL CAttributeValueDeleteButton::OnDelete()
{
  //
  // Let the editor handle the message
  //
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

  //
  // Retrieve the new value and enable the add button if it's not empty
  //
  m_ValueEditor.GetWindowText(szNewValue);
  m_AddButton.EnableWindow(!szNewValue.IsEmpty());
}

void CMultiValuedAttributeEditor::OnValueSelChange()
{
  //
  // Enable the delete button if a value is selected in the list box
  //
  int nSelection = m_ValueList.GetCurSel();
  m_DeleteButton.EnableWindow(nSelection != LB_ERR);
}

void CMultiValuedAttributeEditor::OnAddValue()
{
  CString szNewValue;

  //
  // Retrieve the new value and add it to the data list and list box
  //
  m_ValueEditor.GetWindowText(szNewValue);
  m_strrefAttributeList.AddTail(szNewValue);
  if (m_ValueList.AddString(szNewValue) != LB_ERR)
  {
    m_ValueEditor.SetWindowText(_T(""));
  }

  if (m_ValueList.GetCount() !=0)
  {
    m_DeleteButton.EnableWindow(TRUE);
  }
}

void CMultiValuedAttributeEditor::OnDeleteValue()
{
  //
  // Remove the value from the list box and the data list
  //
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
  if (m_ValueList.GetCount() == 0)
  {
    m_DeleteButton.EnableWindow(FALSE);
  }
}
