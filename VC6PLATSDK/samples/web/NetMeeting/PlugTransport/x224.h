//****************************************************************************
//  Module:     PLUGTRANSPORT.EXE     
//  File:       X224.H
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



#ifndef _X224_H_
#define _X224_H_

#define MAXHOSTNAMELENGTH   64

class CX224
{
private:
  SOCKET 	m_hListenSocket;
  TCHAR		m_szHostName[MAXHOSTNAMELENGTH];
  SOCKET 	m_hSocket;
public:
  CX224::CX224(void);
  CX224::~CX224(void);
  HRESULT CreateListenSocket(HWND hwnd);
  HRESULT CreateConnectSocket(HWND hwnd, LPSTR pszHostName);
  HRESULT CX224::CreateAcceptSocket(HWND hWnd);
  LPSTR   SetAndGetHostName();
  HRESULT CloseSocket();
  HRESULT CloseListenSocket();
  SOCKET  GetSocket();
};

#endif  // _X224_H_
