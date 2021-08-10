/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1999 - 2000 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DragSrc.h

   Description:   

**************************************************************************/

#ifndef DRAGSRC_H
#define DRAGSRC_H

/**************************************************************************
   #include statements
**************************************************************************/

#include <windows.h>
#include <ole2.h>

/**************************************************************************
   class definitions
**************************************************************************/

class CDragSource : public IDropSource
{
private:
   DWORD m_cRefCount;

public:
   CDragSource();
   ~CDragSource();

   //IUnknown members
   STDMETHOD(QueryInterface)(REFIID, LPVOID*);
   STDMETHOD_(ULONG, AddRef)(void);
   STDMETHOD_(ULONG, Release)(void);

   //IDataObject members
   STDMETHOD(GiveFeedback)(DWORD);
   STDMETHOD(QueryContinueDrag)(BOOL, DWORD);
};

#endif   //DRAGSRC_H

