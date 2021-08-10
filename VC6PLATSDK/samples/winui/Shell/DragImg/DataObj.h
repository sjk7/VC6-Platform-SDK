/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1999 - 2000 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DataObj.h

   Description:   

**************************************************************************/

#ifndef DATAOBJ_H
#define DATAOBJ_H

/**************************************************************************
   #include statements
**************************************************************************/

#include <windows.h>
#include <ole2.h>

/**************************************************************************
   global variables and definitions
**************************************************************************/

#define MAX_NUM_FORMAT 5

/**************************************************************************
   class definitions
**************************************************************************/

class CDataObject: public IDataObject
{
private:
   DWORD m_cRefCount;
   LPFORMATETC m_pFormatEtc;
   LPSTGMEDIUM m_pStgMedium;
   DWORD m_cDataCount;

public:
   CDataObject();
   ~CDataObject();

   //IUnknown members that delegate to m_pUnkOuter.
   STDMETHOD(QueryInterface)(REFIID, LPVOID*);
   STDMETHOD_(ULONG, AddRef)(void);
   STDMETHOD_(ULONG, Release)(void);

   /* IDataObject methods */    
   STDMETHOD(GetData)(LPFORMATETC,  LPSTGMEDIUM);
   STDMETHOD(GetDataHere)(LPFORMATETC, LPSTGMEDIUM);
   STDMETHOD(QueryGetData)(LPFORMATETC);
   STDMETHOD(GetCanonicalFormatEtc)(LPFORMATETC, LPFORMATETC);
   STDMETHOD(SetData)(LPFORMATETC, LPSTGMEDIUM, BOOL);
   STDMETHOD(EnumFormatEtc)(DWORD, LPENUMFORMATETC*);
   STDMETHOD(DAdvise)(FORMATETC*, DWORD, LPADVISESINK, LPDWORD);
   STDMETHOD(DUnadvise)(DWORD);
   STDMETHOD(EnumDAdvise)(LPENUMSTATDATA*);
};

#endif   //DATAOBJ_H
