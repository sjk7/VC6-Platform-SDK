// First.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "activeds.h"

int main(int argc, char* argv[])
{
	HRESULT hr;
	IADsContainer *pCont;

	CoInitialize(NULL);

	hr = ADsGetObject(L"WinNT://YOURDOMAIN", IID_IADsContainer, (void**) &pCont );
	
	if ( !SUCCEEDED(hr) )
	{
		return 0;
	}

	//----------------------------
	// Creating a user
	//-----------------------------
	IDispatch *pDisp=NULL;
	IADs *pUser;
	hr = pCont->Create( L"user", L"jsmith", &pDisp );
	pCont->Release();
	
	if ( !SUCCEEDED(hr) )
	{
		return 0;
	}

	hr = pDisp->QueryInterface( IID_IADs, (void**) &pUser );
    pDisp->Release();

	if ( !SUCCEEDED(hr) )
	{	
		return 0;
	}



	// Commit creation to the directory
	pUser->SetInfo();

	// Release the object
	pUser->Release();
	

	CoUninitialize();

	return 0;
}
