//****************************************************************************
//  Module:     PLUGTRANSPORT.EXE     
//  File:       PLUGXPRT.H
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1995-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************



#ifndef _PLUG_XPRT_H_
#define _PLUG_XPRT_H_

#define CONNIDMAXLENGTH   64

class CPluggableTransport
{
private:
 IPluggableTransport *m_pIPlugTrans;
 BOOL m_bInConnection;
 HANDLE m_hEvtRead;
 HANDLE m_hEvtWrite;
 HANDLE m_hEvtClose;
 char m_szConnID[CONNIDMAXLENGTH];

public:
 CX224 *m_pX224;
 CPSTN *m_pPSTN;

 CPluggableTransport(void);
 ~CPluggableTransport(void);
 HRESULT Initialize(INmManager *pINmManager);
 HRESULT Uninitialize();
 BOOL InConnection();
 HRESULT CreateConnection();  // for X224
 HRESULT CreateConnection(LPTSTR pszComPort);  // for PSTN
 HRESULT AcceptConnection(HWND hWnd);  // for X224
 HRESULT AcceptConnection(LPTSTR pszComPort);  // for PSTN
 HRESULT CloseConnection(PLUGXPRT_FRAMING eFraming);  // for both
 HRESULT EnableWinsock();
 HRESULT DisableWinsock();
 LPSTR GetConnectionID();
 HANDLE GetReadEventHandle();
 HANDLE GetWriteEventHandle();
 HANDLE GetCloseEventHandle();
};

#endif // _PLUG_XPRT_H_
