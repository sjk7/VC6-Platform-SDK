//==============================================================;
//
//      This source code is only intended as a supplement to
//  existing Microsoft documentation.
//
//
//
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1999 - 2001 Microsoft Corporation.  All Rights Reserved.
//
//
//
//==============================================================;

#ifndef _SNAPINBASE_H
#define _SNAPINBASE_H

#include "DeleBase.h"

class CStaticNode : public CDelegationBase {
public:
    CStaticNode();

    virtual ~CStaticNode();

    virtual const _TCHAR *GetDisplayName(int nCol = 0) {
        static _TCHAR szDisplayName[256];
        LoadString(g_hinst, IDS_SNAPINNAME, szDisplayName, (sizeof szDisplayName)/(sizeof szDisplayName[0]));
        return szDisplayName;
    }
    virtual const GUID & getNodeType() { return thisGuid; }
    virtual const int GetBitmapIndex() { return INDEX_NONE; }
    virtual void SetScopeItemValue(HSCOPEITEM hscopeitem) { m_hParentHScopeItem = hscopeitem; }
    virtual HSCOPEITEM GetParentScopeItem() { return m_hParentHScopeItem; }

public:
    // virtual functions go here (for MMCN_*)
    virtual HRESULT OnExpand(IConsoleNameSpace *pConsoleNameSpace, IConsole *pConsole, HSCOPEITEM parent);

private:
    enum { NUMBER_OF_CHILDREN = 4 };
    CDelegationBase *children[NUMBER_OF_CHILDREN];

    HSCOPEITEM m_hParentHScopeItem;

    // {C094012C-6BE7-11d3-9156-00C04F65B3F9}
    static const GUID thisGuid;
};



#endif // _SNAPINBASE_H