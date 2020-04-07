/* Copyright 1992 - 2000 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
*/

#include "component.hxx"
#include "..\include\pipe.hxx"
#include <conio.h>
#include <stdio.h>
#include <tchar.h>

#define PIPE_SIZE 1000;


/******************************************  
* Class CSimpleClass Implementation
*******************************************/

CSimpleClass::CSimpleClass()
   : m_cRef(1)
{
   CoAddRefServerProcess();
};

CSimpleClass::~CSimpleClass()
{
   if (0==CoReleaseServerProcess())
       PostQuitMessage(0);
};

// IUnknown implementation

STDMETHODIMP CSimpleClass::QueryInterface(REFIID riid, void** ppv)
{
   *ppv = NULL;

   if (IsEqualIID(IID_IUnknown, riid)) {
      *ppv = static_cast<ISimpleInterface*>(this);
   }
   else if (IsEqualIID(IID_ISimpleInterface, riid)) {
         *ppv = static_cast<ISimpleInterface*>(this);
   }
   else
   {
      return E_NOINTERFACE;
   }

   reinterpret_cast<IUnknown*>(*ppv)->AddRef();
   return S_OK;

};

STDMETHODIMP_(ULONG) CSimpleClass::AddRef()
{
   InterlockedIncrement((LONG *)&m_cRef);
   return m_cRef;
};

STDMETHODIMP_(ULONG) CSimpleClass::Release()
{
   ULONG cLockedRefs = InterlockedDecrement((LONG *)&m_cRef);
   if( cLockedRefs == 0 )
   {
      delete this;
      return 0;
   }
   else return cLockedRefs;
};

/**********************************************************
* InPipeSample implementation : PIPE_AS_IN_PARAMETER option
**********************************************************/

STDMETHODIMP CSimpleClass::InPipeSample(IPipeLong *pInPipe)
{
   HRESULT hr=S_OK;
   LONG* buffer1=NULL;
   LONG* buffer2=NULL;
   ULONG lPulled=0;

   AllocConsole();
   HANDLE hConsoleOutput;
   hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
   const TCHAR* lpMessage = __TEXT("\n***** SERVER SIDE CONSOLE *****\n \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   /*******************************************
   ** DEMONSTRATING MULTIPLE SEQUENCES OF PULLS
   *******************************************/

   lpMessage = __TEXT("DEMONSTRATING MULTIPLE SEQUENCES OF PULLS \n\n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   /*
   ** PULL one sequence from the InPipe 
   */

   lpMessage = __TEXT("\tOPERATION: PULLing one sequence from the InPipe  \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   buffer1 = new LONG[2000 + 1];
   lPulled=0;
   hr=GenericPull(pInPipe, buffer1, &lPulled, 0);
   if (FAILED(hr) || (2000 != lPulled))
   { 
      MessageBox(NULL, TEXT("PULL FAILED ON INPIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND); 
      return E_FAIL;
   }
   else
   {
      lpMessage = __TEXT("\tRESULT: success ! \n \n");
      WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   }

   /*
   ** PULL another sequence from the InPipe 
   */

   lpMessage = __TEXT("\tOPERATION: PULLing second sequence from the InPipe  \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   lPulled=0;
   hr=GenericPull(pInPipe, buffer1, &lPulled, 0);
   if (FAILED(hr) || (2000 != lPulled))
   { 
      MessageBox(NULL, TEXT("PULL FAILED ON INPIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND);  
      return E_FAIL;
   }
   else
   {
      lpMessage = __TEXT("\tRESULT: success ! \n \n");
      WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   }

   lpMessage = __TEXT("NOTE: Multiple sequences of PULLs are allowed using DCOM Pipes, each separated by a zero count PULL. \n \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   lpMessage = __TEXT("Press any key to continue..\n\n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   _getch();

   /********************************************
   ** DEMONSTRATING MULTIPLE SEQUENCES OF PUSHES
   ********************************************/

   lpMessage = __TEXT("DEMONSTRATING MULTIPLE SEQUENCES OF PUSHES \n\n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   /*
   ** PUSH 500 elements to the pipe.
   */

   lpMessage = __TEXT("\tOPERATION: PUSHing 500 elements to the InPipe  \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   buffer2 = new LONG[2000 + 1];

   hr=GenericPush(pInPipe, buffer2, 500);
   if (FAILED(hr))
   { 
      MessageBox(NULL, TEXT("PUSH FAILED ON INPIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND); 
      return E_FAIL;
   }
   else
   {
      lpMessage = __TEXT("\tRESULT: success !\n \n");
      WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   }

   /*
   ** Push 0 count to close this sequence
   */
   hr=GenericPush(pInPipe, buffer2, 0);
   if (FAILED(hr)) { return E_FAIL; }

   /*
   ** PUSH another 500 elements to the pipe.
   */
   lpMessage = __TEXT("\tOPERATION: PUSHing another sequence of 500 elements to the InPipe  \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   hr=GenericPush(pInPipe, buffer2, 500);
   if (FAILED(hr))
   { 
      MessageBox(NULL, TEXT("PUSH FAILED ON INPIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND); 
      return E_FAIL;
   }
   else
   {
      lpMessage = __TEXT("\tRESULT: success !\n \n");
      WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   }

   /*
   ** Push 0 count to close this second sequence
   */

   hr=GenericPush(pInPipe, buffer2, 0);
   if (FAILED(hr)) { return E_FAIL; }

   lpMessage = __TEXT("NOTE: Multiple sequences of PUSHes are allowed using DCOM Pipes, each separated by a zero count PUSH. \n \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   lpMessage = __TEXT("Press any key to continue..\n \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   _getch();

   /*******************************************
   ** DEMONSTRATING MIX OF PULL AND PUSH
   *******************************************/

   lpMessage = __TEXT("DEMONSTRATING MIXING OF PULL AND PUSH \n\n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   /*
   ** Pull 1000 elements from the InPipe.
   */

   lpMessage = __TEXT("\tOPERATION: PULLing 1000 elements from the InPipe  \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   lPulled=0;
   hr=GenericPull(pInPipe, buffer1, &lPulled, 1000);
   if (FAILED(hr))
   { 
      MessageBox(NULL, TEXT("PULL FAILED ON INPIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND);   
      return E_FAIL;
   }
   else
   {
      lpMessage = __TEXT("\tRESULT: success ! \n \n");
      WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   }
   

   /*
   ** PUSH 500 elements to the pipe. Notice how Pull and Push
   ** operations can be mixed on the same pipe.
   */

   lpMessage = __TEXT("\tOPERATION: PUSHing 500 elements to the InPipe  \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
  
   hr=GenericPush(pInPipe, buffer2, 500);
   if (FAILED(hr))
   { 
      MessageBox(NULL, TEXT("PUSH FAILED ON INPIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND); 
      return E_FAIL;
   }
   else
   {
      lpMessage = __TEXT("\tRESULT: success !\n \n");
      WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   }

   /*
   ** Push 0 count to close this sequence
   */
   hr=GenericPush(pInPipe, buffer2, 0);
   if (FAILED(hr)) { return E_FAIL; }


   /*
   ** Drain in the rest of the InPipe.
   */ 
   lpMessage = __TEXT("\tOPERATION: PULLing all the remaining elements from the InPipe  \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   hr=GenericPull(pInPipe, buffer1, &lPulled, 2000);
   if (FAILED(hr))
   { 
      MessageBox(NULL, TEXT("PULL FAILED ON INPIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND);  
      return E_FAIL;
   }
   else
   {
      lpMessage = __TEXT("\tRESULT: success ! \n \n");
      WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   }

   lpMessage = __TEXT("NOTE: PULLs and PUSHes can be mixed on the same DCOM Pipe. \n \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   lpMessage = __TEXT("Press any key to terminate the server console.. \n\n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   _getch();
   FreeConsole();
   return S_OK; 
};


/************************************************************
* OutPipeSample implementation : PIPE_AS_OUT_PARAMETER option
************************************************************/

STDMETHODIMP CSimpleClass::OutPipeSample(IPipeLong **ppOutPipe)
{
   // Create a pipe on the server side
   *ppOutPipe=new CSamplePipe();
   if (NULL == *ppOutPipe)
   return E_OUTOFMEMORY;
   (*ppOutPipe)->AddRef();
   return S_OK;
};

/******************************************************************
* InOutPipeSample implementation : PIPE_AS_IN_OUT_PARAMETER option
*****************************************************************/

STDMETHODIMP CSimpleClass::InOutPipeSample(IPipeLong **ppInOutPipe)
{ 
   HRESULT hr=S_OK;
   ULONG lPulled=0;

   AllocConsole();
   HANDLE hConsoleOutput;
   hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
   const TCHAR* lpMessage = __TEXT("\n***** SERVER SIDE CONSOLE *****\n \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   /*******************************************
   ** DEMONSTRATING USE OF INOUTPIPE
   *******************************************/

   lpMessage = __TEXT("DEMONSTRATING USE OF [IN,OUT] PIPE \n\n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   /*
   ** PULL one sequence from the InPipe 
   */

   lpMessage = __TEXT("\tOPERATION: PULLing one sequence from the InOutPipe  \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   LONG *buffer1 = new LONG[2000 + 1];

   hr=GenericPull(*ppInOutPipe, buffer1, &lPulled, 0);
   if (FAILED(hr) || (2000 != lPulled))
   { 
      MessageBox(NULL, TEXT("PULL FAILED ON INOUTPIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND); 
      return E_FAIL;
   }
   else
   {
      lpMessage = __TEXT("\tRESULT: success ! \n \n");
      WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   }
   
   (*ppInOutPipe)->Release();

   // Create a pipe on the server side

   lpMessage = __TEXT("\tOPERATION: Creating a pipe on the server  \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   *ppInOutPipe = new CSamplePipe();
   if (NULL == *ppInOutPipe)
   { 
      MessageBox(NULL, TEXT("UNABLE TO CREATE PIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND); 
      return E_OUTOFMEMORY;
   }
   else
   {
      lpMessage = __TEXT("\tRESULT: success ! \n \n");
      WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   }
   (*ppInOutPipe)->AddRef();

    lpMessage = __TEXT("Press any key to return to the client..");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   _getch();
   FreeConsole();
   return S_OK;   
};

/******************************************************************
* InInOutPipesSample implementation : PIPES_AS_IN_IN_OUT_PARAMETERS
*****************************************************************/

STDMETHODIMP CSimpleClass::InInOutPipesSample(IPipeLong *pInPipe1, IPipeLong *pInPipe2,
                                   IPipeLong **ppOutPipe)
{
   HRESULT hr=S_OK;
   ULONG lPulled=0;

   AllocConsole();
   HANDLE hConsoleOutput;
   hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
   const TCHAR* lpMessage = __TEXT("\n***** SERVER SIDE CONSOLE *****\n \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   /*
   ** PROCESS THE SECOND [IN] PARAMETER FIRST
   ** DCE Model wouldn't allow to use second 'in' pipe without
   ** using the first 'in' pipe.
   */

   lpMessage = __TEXT("DEMONSTRATING HOW ORDER OF PROCESSING DCOM PIPES IS NOT IMPORTANT \n\n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   lpMessage = __TEXT("\tOPERATION: PULLing one sequence from the second InPipe  \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   LONG *buffer1 = new LONG[2000 + 1];
   lPulled=0;
   hr=GenericPull(pInPipe2, buffer1, &lPulled, 0);
   if (FAILED(hr) || (2000 != lPulled))
   { 
      MessageBox(NULL, TEXT("PULL FAILED ON SECOND INPIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND); 
      return E_FAIL;
   }
   else
   {
      lpMessage = __TEXT("\tRESULT: success ! \n \n");
      WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   }

   /*
   ** PUSH 500 elements to the 'out' pipe.
   */

   lpMessage = __TEXT("\tOPERATION: PUSHing one sequence to the OutPipe  \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   // Create an Out pipe on the server side
   *ppOutPipe=new CSamplePipe();
   (*ppOutPipe)->AddRef();

   LONG *buffer2 = new LONG[2000 + 1];

   hr=GenericPush(*ppOutPipe, buffer2, 500);
   if (FAILED(hr))
   { 
      MessageBox(NULL, TEXT("PUSH FAILED ON OUTPIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND); 
      return E_FAIL;
   }
   hr=GenericPush(*ppOutPipe, buffer2, 0);
   if (FAILED(hr))
   { 
      MessageBox(NULL, TEXT("PUSH FAILED ON OUTPIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND); 
      return E_FAIL;
   }
   else
   {
      lpMessage = __TEXT("\tRESULT: success !\n \n");
      WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   }


   /*
   ** Drain in (PULL) the first 'in' parameter. 
   */

   lpMessage = __TEXT("\tOPERATION: PULLing one sequence from the first InPipe  \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   lPulled=0;
   hr=GenericPull(pInPipe1, buffer1, &lPulled, 0);
   if (FAILED(hr) || (2000 != lPulled))
   { 
      MessageBox(NULL, TEXT("PULL FAILED ON FIRST INPIPE"), TEXT("SERVER: ERROR"), MB_SETFOREGROUND); 
      return E_FAIL;
   }
   else
   {
      lpMessage = __TEXT("\tRESULT: success ! \n \n");
      WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   }
   
   lpMessage = __TEXT("NOTE: Using DCOM Pipes, it possible to process the parameters in any order. \n \n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);

   lpMessage = __TEXT("Press any key to return to the client..\n\n");
   WriteConsole(hConsoleOutput, lpMessage, _tcslen(lpMessage), 0, NULL);
   _getch();
   FreeConsole();
   return S_OK;
}


/***********************************
* Class Factory Implementation
***********************************/

CFactory::CFactory()
   : m_cRef(1)
{
};

CFactory::~CFactory()
{
};

STDMETHODIMP CFactory::QueryInterface(REFIID riid, void** ppv)
{
   *ppv = NULL;

   if (riid == IID_IUnknown) {
      *ppv = static_cast<IClassFactory*>(this);
   }
   else if (riid == IID_IClassFactory) {
         *ppv = static_cast<IClassFactory*>(this);
   }
   else
   {
      return E_NOINTERFACE;
   }

   reinterpret_cast<IUnknown*>(*ppv)->AddRef();
   return S_OK;

};

STDMETHODIMP_(ULONG) CFactory::AddRef()
{
   InterlockedIncrement((LONG *)&m_cRef);
   return m_cRef;
};

STDMETHODIMP_(ULONG) CFactory::Release()
{
   ULONG cLockedRefs = InterlockedDecrement((LONG *)&m_cRef);

   if( cLockedRefs == 0 )
   {
      delete this;
      return 0;
   }
   return cLockedRefs;
};

STDMETHODIMP CFactory::CreateInstance(IUnknown* pUnkwnOuter, REFIID riid, void** ppv)
{
   HRESULT hr;
   CSimpleClass* pObject = new CSimpleClass();

   hr=pObject->QueryInterface(riid, ppv);
   if (FAILED(hr)) {
      delete pObject;
      return hr;
   }
   pObject->Release();
   return S_OK;
};

STDMETHODIMP CFactory::LockServer(BOOL bLock)
{

   if (bLock) 
	CoAddRefServerProcess();
   else
   {
        if (0==CoReleaseServerProcess())
	{
	    //PostThreadMessage(GetCurrentThreadId(), WM_QUIT, 0, 0);
	    PostQuitMessage(0);
	}
   }
   return S_OK;
};
