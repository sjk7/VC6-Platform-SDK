// Filename: Computer.h
//
// Description:  Definition of CComputer
//
// This file is provided as part of the Microsoft Transaction Server Samples
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
// WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
// OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
// PURPOSE.
//
// Copyright (C) 1997 - 2000 Microsoft Corporation, All rights reserved

#if !defined(AFX_COMPUTER_H__AA22C9A7_FD72_11D0_B5DC_00C04FB957D8__INCLUDED_)
#define AFX_COMPUTER_H__AA22C9A7_FD72_11D0_B5DC_00C04FB957D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CComputer

class CComputer : 
	public CComDualImpl<IComputer, &IID_IComputer, &LIBID_TSERVERLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CComputer,&CLSID_Computer>
{
public:
	CComputer() {}

private:
	long plField [3][3];

	float CComputer::Evaluate (long lX, long lY);
	long CComputer::LineScan (long lPlayer, long& lX, long& lY);
	bool CComputer::IsWin (long lPlayer);
	long CComputer::HowManyTurns ();
	void CComputer::GetMove (long lGameID, VARIANT_BOOL bEasy, long& lX, long& lY);
	HRESULT CComputer::LoadArray (long lGameID);
	HRESULT CComputer::SaveArray (long lGameID); 
	void inline CComputer::InitArray () {
		for (int i = 0; i < 3; i ++)
			for (int j = 0; j < 3; j ++)
				plField[i][j] = 0;
	}

BEGIN_COM_MAP(CComputer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComputer)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CComputer) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_Computer)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IComputer
public:
	STDMETHODIMP AddNewGame (IN VARIANT_BOOL bEasy, OUT VARIANT* pvGameID, OUT VARIANT* pvOrder, OUT VARIANT* pvX, OUT VARIANT* pvY);
	STDMETHODIMP NewMove (IN long lGameID, IN VARIANT_BOOL bEasy, IN long lX, IN long lY, OUT VARIANT* pvMyX, OUT VARIANT* pvMyY, OUT VARIANT* pvWin);

};

#endif // !defined(AFX_COMPUTER_H__AA22C9A7_FD72_11D0_B5DC_00C04FB957D8__INCLUDED_)