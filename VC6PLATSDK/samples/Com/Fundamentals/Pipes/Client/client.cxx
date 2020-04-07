/* Copyright 1992 - 2000 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
*/

#include <objbase.h>
#include <conio.h>
#include <tchar.h>
#include <iostream.h>
#include "ISimpleInterface.h"

#include "..\include\pipe.hxx"

LPTSTR   g_szMessage;

typedef enum _options { PIPE_AS_IN_PARAMETER=1, PIPE_AS_OUT_PARAMETER,
                PIPE_AS_IN_OUT_PARAMETER, PIPES_AS_IN_IN_OUT_PARAMETERS
              } clOption;

void usage()
{
   cout << endl << "Usage: client <OPTION>" << endl << endl
           << "OPTION : PIPE_AS_IN_PARAMETER | PIPE_AS_OUT_PARAMETER | "
           << " PIPE_AS_IN_OUT_PARAMETER | PIPES_AS_IN_IN_OUT_PARAMETERS "
           << endl << endl;
   return;
}

int map(char *szOption)
{
   int option=0;
   if (!strcmp(szOption, "PIPE_AS_IN_PARAMETER")) { option=1; }
   else if (!strcmp(szOption,"PIPE_AS_OUT_PARAMETER")) { option=2; }
   else if (!strcmp(szOption,"PIPE_AS_IN_OUT_PARAMETER")) { option=3; }
   else if (!strcmp(szOption,"PIPES_AS_IN_IN_OUT_PARAMETERS")) { option=4; }
   else { option=0; }
   return option;
}

void Message(HRESULT hr)
{
    if (HRESULT_FACILITY(hr) == FACILITY_WINDOWS)
        hr = HRESULT_CODE(hr);
 
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
        (LPTSTR)&g_szMessage,
        0,
        NULL);
}

int CreateInstance(ISimpleInterface **ppSI)
{
   HRESULT hr = S_OK;
   hr=CoInitializeEx(NULL, COINIT_MULTITHREADED);
   hr=CoCreateInstance(CLSID_SimpleClass,0,CLSCTX_LOCAL_SERVER,IID_ISimpleInterface, (void**)&(*ppSI));
   if (FAILED(hr)) {
      Message(hr);
      MessageBox(NULL, g_szMessage, TEXT("CLIENT : COCREATEINSTANCE ERROR"), MB_SETFOREGROUND);
      CoUninitialize();
      return 0;
   }
   return 1;
}

inline void cleanup()
{
   //CoFreeUnusedLibraries();
   CoUninitialize();
}

/**********************************************************
* PIPE_AS_IN_PARAMETER option
**********************************************************/

void pipe_in()
{
   HRESULT hr = S_OK;
   cout << endl << "***** Running [In] Pipe Example *****" << endl << endl;
   
   // Create an instance of the simple class
   ISimpleInterface* pSI=NULL;
   if (!CreateInstance(&pSI)) { return; }

   // The client needs to Create a pipe
   CSamplePipe* pInPipe = new CSamplePipe();
   pInPipe->AddRef();
   // Pass the pipe to the server as an 'in' parameter.
   // Since the client implements both Pull and Push operations,
   // the server can use these callbacks.
   hr=pSI->InPipeSample(pInPipe);
   if (FAILED(hr)) {
      MessageBox(NULL, TEXT("InPipe couldn't be used by the server/callee"), TEXT("CLIENT: ERROR"), MB_SETFOREGROUND);
   }
   else
   {
      cout << endl << "InPipe was successfully used by the server/callee." << endl;
   }

   // Resource management 
   hr=pInPipe->Release();
   hr=pSI->Release();
   pInPipe=NULL;
   pSI=NULL;
   cleanup();
   return;
}

/************************************************************
* PIPE_AS_OUT_PARAMETER option
************************************************************/

void pipe_out()
{ 
   HRESULT hr = S_OK;
   cout << endl << "***** Running [Out] Pipe Example *****" << endl << endl;

   // Create an instance of the simple class
   ISimpleInterface* pSI=NULL;
   if (!CreateInstance(&pSI)) { return; }

   // The server will create the pipe
   IPipeLong *pOutPipe=NULL;

   // Get the pipe from the server as an 'out' parameter.
   // Since the server implements both Pull and Push operations,
   // the client can use these callbacks.
   hr=pSI->OutPipeSample(&pOutPipe);
   if (FAILED(hr)) {
      MessageBox(NULL, TEXT("Invalid OutPipe returned by the server"), TEXT("CLIENT: ERROR"), MB_SETFOREGROUND);
      cleanup(); return;
   }
   
   /*
   ** Drain in (PULL) the pipe. 
   */

   cout << "OPERATION: PULLing one sequence from the OutPipe" << endl;
   ULONG lPulled=0;
   LONG *buffer1 = new LONG[2000 + 1];

   hr=GenericPull(pOutPipe, buffer1, &lPulled, 0);
   if (FAILED(hr)) { 
      MessageBox(NULL, TEXT("PULL FAILED ON OUTPIPE"), TEXT("CLIENT: ERROR"), MB_SETFOREGROUND); 
      cleanup(); return;
   }
   else {
      cout << "RESULT: success !"
           << endl << endl;
   }

   /*
   ** PUSH 500 elements to the pipe.
   */
   cout << "OPERATION: PUSHing one sequence to the OutPipe" << endl;

   LONG *buffer2 = new LONG[2000 + 1];

   hr=GenericPush(pOutPipe, buffer2, 500);
   if (FAILED(hr)) { 
      MessageBox(NULL, TEXT("PUSH FAILED ON OUTPIPE"), TEXT("CLIENT: ERROR"), MB_SETFOREGROUND); 
      cleanup(); return;
   }
   
   /*
   ** Push 0 to close this sequence
   */

   hr=GenericPush(pOutPipe, buffer2, 0);
   if (FAILED(hr)) {
      MessageBox(NULL, TEXT("PUSH FAILED ON OUTPIPE"), TEXT("CLIENT: ERROR"), MB_SETFOREGROUND);
      cleanup(); return;
   }
   else {
      cout << "RESULT: success !"
           << endl << endl;
   }

   // Resource management
   pOutPipe->Release();
   hr=pSI->Release();
   cleanup();
   return;  
}

/******************************************************************
* PIPE_AS_IN_OUT_PARAMETER option
*****************************************************************/

void pipe_in_out()
{ 
   cout << endl << "***** Running [In,Out] Pipe Example *****" << endl << endl;
   HRESULT hr = S_OK;

   // Create an instance of the simple class
   ISimpleInterface* pSI;
   if (!CreateInstance(&pSI)) { return; }

   // The client needs to Create a pipe
   IPipeLong* pInOutPipe;
   
   pInOutPipe = new CSamplePipe();
   
   // Pass the pipe to the server as an 'in,out' parameter.
   // Since the client implements both Pull and Push operations,
   // the server can use these callbacks.
   pInOutPipe->AddRef();
   hr=pSI->InOutPipeSample(&pInOutPipe);
   if (FAILED(hr)) {
      MessageBox(NULL, TEXT("InOutPipe invalid on return from server"), TEXT("CLIENT: ERROR"), MB_SETFOREGROUND);
      hr=pSI->Release(); 
      cleanup(); return;
   }

   // Use the returned Pipe now

   /*
   ** Drain in (PULL) the pipe. 
   */
   cout << "OPERATION: PULLing one sequence from the InOutPipe" << endl;
   ULONG lPulled=0;
   LONG *buffer1 = new LONG[2000 + 1];

   hr=GenericPull(pInOutPipe, buffer1, &lPulled, 0);
   if (FAILED(hr)) { 
      MessageBox(NULL, TEXT("PULL FAILED ON INOUTPIPE"), TEXT("CLIENT: ERROR"), MB_SETFOREGROUND); 
      cleanup(); return;
   }
   else {
      cout << "RESULT: success !"
           << endl << endl;
   }
   
   // Resource management 
   pInOutPipe->Release();
   hr=pSI->Release();
   cleanup();
   return; 
}

/******************************************************************
* PIPES_AS_IN_IN_OUT_PARAMETERS option
*****************************************************************/

void pipes_in_in_out()
{ 
   cout << endl << "***** Running [In] [In] [Out] Example *****" << endl;

   HRESULT hr = S_OK;
   
   // Create an instance of the simple class
   ISimpleInterface* pSI;
   if (!CreateInstance(&pSI)) { return; }

   // The client needs to Create In pipes
   IPipeLong* pInPipe1=NULL;
   IPipeLong* pInPipe2=NULL;
   IPipeLong* pOutPipe=NULL;

   // The client needs to Create In pipes
   pInPipe1 = new CSamplePipe();
   pInPipe2 = new CSamplePipe();

   // Pass the pipes to the server as an 'in' parameter.
   // Since the client implements both Pull and Push operations,
   // the server can use these callbacks.
   hr=pSI->InInOutPipesSample(pInPipe1,pInPipe2,&pOutPipe);
   if (FAILED(hr)) {
	MessageBox(NULL, TEXT("Pipes couldn't be used by the server/callee"), TEXT("CLIENT: ERROR"), MB_SETFOREGROUND);
   }
   else
   {
      cout << endl << "Pipes were successfully used by the server/callee." << endl;
   }

   // Resource management
   pInPipe1->Release();
   pInPipe1 = NULL;
   pInPipe2->Release();
   pInPipe2 = NULL;
   pOutPipe->Release();
   pOutPipe=NULL;
   hr=pSI->Release();
   pSI = NULL;
   cleanup();

   return; 
}


/********************************************************
** Main function for the client
*********************************************************/

int main(int argc, char *argv[])
{
   if (argc != 2) { usage(); return -1; }

   int option;
   char* szOption=new char[strlen(argv[1])+1];
   strcpy(szOption, argv[1]);

   // Map input option to desired switch value
   option=map(szOption);
   
   // Execute the appropriate function
   switch (option)
   {
      case PIPE_AS_IN_PARAMETER:          pipe_in();
				          break;
      case PIPE_AS_OUT_PARAMETER:         pipe_out();
				          break;
      case PIPE_AS_IN_OUT_PARAMETER:      pipe_in_out();
				          break;
      case PIPES_AS_IN_IN_OUT_PARAMETERS: pipes_in_in_out();
					  break;
      default:                            usage();
		                          break;
   };
   return 0;
};
