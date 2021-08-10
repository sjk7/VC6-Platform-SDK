// CapMFC.h : main header file for the CAPMFC application
//

#if !defined(AFX_CAPMFC_H__AB8FEB98_3841_11D2_8512_00C04FA34A14__INCLUDED_)
#define AFX_CAPMFC_H__AB8FEB98_3841_11D2_8512_00C04FA34A14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCapMFCApp:
// See CapMFC.cpp for the implementation of this class
//

class CCapMFCApp : public CWinApp
{
public:
	CCapMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCapMFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCapMFCApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPMFC_H__AB8FEB98_3841_11D2_8512_00C04FA34A14__INCLUDED_)
