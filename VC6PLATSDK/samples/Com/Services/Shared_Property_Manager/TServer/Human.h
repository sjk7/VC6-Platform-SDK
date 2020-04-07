// Filename: Human.h
//
// Description:  Definition of CHuman
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

#if !defined(AFX_HUMAN_H__CAAD7FA2_F22D_11D0_B5CB_00C04FB957D8__INCLUDED_)
#define AFX_HUMAN_H__CAAD7FA2_F22D_11D0_B5CB_00C04FB957D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHuman

class CHuman : 
	public CComDualImpl<IHuman, &IID_IHuman, &LIBID_TSERVERLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CHuman,&CLSID_Human>
{
public:
	CHuman() {}

private:
	long plField [3][3];
	
	void inline CHuman::InitArray () {
		for (int i = 0; i < 3; i ++)
			for (int j = 0; j < 3; j ++)
				plField[i][j] = 0;
	}

	HRESULT CHuman::LoadArray (long lGameID);
	HRESULT CHuman::SaveArray (long lGameID);
	long CHuman::HowManyTurns ();
	bool CHuman::IsWin (long lPlayer);

BEGIN_COM_MAP(CHuman)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IHuman)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CHuman) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_Human)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IHuman

public:
	STDMETHODIMP EnterNewGame (IN BSTR bstrLocalName, OUT VARIANT* pvGameID, OUT VARIANT* pvName, OUT VARIANT* pvOrder);
	STDMETHODIMP NewMove (IN long lGameID, IN long lOrder, IN long lX, IN long lY, OUT VARIANT* pvWin);
	STDMETHODIMP GetNewMove (IN long lGameID, IN long lOrder, OUT VARIANT* pvName, OUT VARIANT* pvFoeX, OUT VARIANT* pvFoeY, OUT VARIANT* pvWin, OUT VARIANT* pvUpdate);
};

#endif // !defined(AFX_HUMAN_H__CAAD7FA2_F22D_11D0_B5CB_00C04FB957D8__INCLUDED_)
