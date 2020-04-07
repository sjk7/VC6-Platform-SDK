/*+==========================================================================

File: MonitorServer.cpp

Summary:  Implements CMonitorServer methods.


----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995 - 2000 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/
// MonitorServer.cpp : Implementation of CServerApp and DLL registration.

#include "stdafx.h"
#include "server.h"
#include "MonitorServer.h"

#include "PingResp_i.c"
/////////////////////////////////////////////////////////////////////////////
//

// Normal Distribution Median=2000, max = 4000, 10 buckets
int arDelay[10] = {0,1,5,91,635,2000,3365,3909,3995,4000};


HRESULT STDMETHODCALLTYPE CMonitorServer::GetData(LONG *pData){
	// Delay Call completion by randomizing response time
	int index = rand()*10/RAND_MAX;  // Range 0-9
	int iSleep = arDelay[index];
	*pData = iSleep;
	if (iSleep) Sleep(iSleep);
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CMonitorServer::GetPingResponder(IPingResponder **ppPing){
	return CoCreateInstance(CLSID_PingResponder,NULL,CLSCTX_INPROC_SERVER,IID_IPingResponder, (LPVOID*) ppPing);
}
