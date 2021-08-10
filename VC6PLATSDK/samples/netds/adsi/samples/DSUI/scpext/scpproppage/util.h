//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       util.h
//
//--------------------------------------------------------------------------

#ifndef _UTIL_H
#define _UTIL_H

#define BYTE_OFFSET(base, offset) (((LPBYTE)base)+offset)

HRESULT SetStringAttribute(IADs* pIADs, LPCWSTR lpszAttr, LPCWSTR lpszValue);


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//
// Forward Declaration
//
class CMultiValuedAttributeEditor;


class CAttributeValueEditor : public CEdit
{
public:
  CAttributeValueEditor(CMultiValuedAttributeEditor* pEditor)
  {
    ASSERT(pEditor != NULL);
    m_pEditor = pEditor;
  }

  ~CAttributeValueEditor() {}

  afx_msg BOOL OnChange();

protected:
  CMultiValuedAttributeEditor* m_pEditor;

  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////////

class CMultiValuedListBox : public CListBox
{
public:
  CMultiValuedListBox(CMultiValuedAttributeEditor* pEditor)
  {
    ASSERT(pEditor != NULL);
    m_pEditor = pEditor;
  }

  ~CMultiValuedListBox() {}

  afx_msg BOOL OnSelChange();

protected:
  CMultiValuedAttributeEditor* m_pEditor;

  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////////

class CAttributeValueAddButton : public CButton
{
public:
  CAttributeValueAddButton(CMultiValuedAttributeEditor* pEditor)
  {
    ASSERT(pEditor != NULL);
    m_pEditor = pEditor;
  }

  ~CAttributeValueAddButton() {}

  afx_msg BOOL OnAdd();

protected:
  CMultiValuedAttributeEditor* m_pEditor;

  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////////

class CAttributeValueDeleteButton : public CButton
{
public:
  CAttributeValueDeleteButton(CMultiValuedAttributeEditor* pEditor)
  {
    ASSERT(pEditor != NULL);
    m_pEditor = pEditor;
  }

  ~CAttributeValueDeleteButton() {}

  afx_msg BOOL OnDelete();

protected:
  CMultiValuedAttributeEditor* m_pEditor;

  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////////

class CAttributeValueEditButton : public CButton
{
public:
  CAttributeValueEditButton(CMultiValuedAttributeEditor* pEditor)
  {
    ASSERT(pEditor != NULL);
    m_pEditor = pEditor;
  }

  ~CAttributeValueEditButton() {}

  afx_msg BOOL OnEdit();

protected:
  CMultiValuedAttributeEditor* m_pEditor;

  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////////

class CMultiValuedAttributeEditor
{
public:
  CMultiValuedAttributeEditor(CStringList& strrefAttributeList);
  ~CMultiValuedAttributeEditor() {}

  BOOL Initialize(UINT nEditBox, 
                  UINT nListBox, 
                  UINT nAddButton, 
                  UINT nDeleteButton, 
                  CWnd* pParentWnd);

  //
  // Redirected message handlers from subclassed controls
  //
  void OnEditChange();
  void OnValueSelChange();
  void OnAddValue();
  void OnDeleteValue();

private:
  CStringList& m_strrefAttributeList;

  //
  // Controls to be subclassed
  //
  CAttributeValueEditor       m_ValueEditor;
  CMultiValuedListBox         m_ValueList;
  CAttributeValueAddButton    m_AddButton;
  CAttributeValueDeleteButton m_DeleteButton;
};
#endif // _UTIL_H