// bindtoparent.cpp : Defines the entry point for the console application.
//
#include <wchar.h>
#include <objbase.h>
#include <activeds.h>

HRESULT GetParentObject(IADs *pObject, //Pointer the object whose parent to bind to.
						IADs **ppParent //Return a pointer to the parent object.
						);

HRESULT FindUserByName(IDirectorySearch *pSearchBase, //Container to search
					   LPOLESTR szFindUser, //Name of user to find.
					   IADs **ppUser); //Return a pointer to the user


void wmain( int argc, wchar_t *argv[ ])
{

//Handle the command line arguments.
LPOLESTR pszBuffer = new OLECHAR[MAX_PATH*2];
if (argv[1] == NULL)
{
	wprintf(L"This program finds a user in the current Window 2000 domain\n");
	wprintf(L"and displays its parent container's ADsPath and binds to that container.\n");	
	wprintf(L"Enter Common Name of the user to find:");
	_getws(pszBuffer);
}
else
   wcscpy(pszBuffer, argv[1]);
//if empty string, exit.
if (0==wcscmp(L"", pszBuffer))
{
   delete pszBuffer;
   return; 
}
	
wprintf(L"\nFinding user: %s...\n",pszBuffer);
	
//Intialize COM
CoInitialize(NULL);
HRESULT hr = S_OK;
//Get rootDSE and the domain container's DN.
IADs *pObject = NULL;
IADs *pParent = NULL;
IDirectorySearch *pDS = NULL;
LPOLESTR szPath = new OLECHAR[MAX_PATH]; //[seyitb] delete at the end
VARIANT var;
hr = ADsOpenObject(L"LDAP://rootDSE",
				 NULL,
				 NULL,
				 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
				 IID_IADs,
				 (void**)&pObject);
if (FAILED(hr))
{
   wprintf(L"Not Found. Could not bind to the domain.\n");
   if (pObject)
     pObject->Release();
    delete pszBuffer;
    delete szPath;
   return;
}

hr = pObject->Get(L"defaultNamingContext",&var);
if (SUCCEEDED(hr))
{
	wcscpy(szPath,L"LDAP://"); // If you're running on NT 4.0 or Win9.x machine, you need to 
	                           // add the server name e.g L"LDAP://myServer"
	wcscat(szPath,var.bstrVal);
	VariantClear(&var);
	if (pObject)
	{
	   pObject->Release();
	   pObject = NULL;
	}
	//Bind to the root of the current domain.
	hr = ADsOpenObject(szPath,
					 NULL,
					 NULL,
					 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
					 IID_IDirectorySearch,
					 (void**)&pDS);
	if (SUCCEEDED(hr))
	{
		hr =  FindUserByName(pDS, //Container to search
						   pszBuffer, //Name of user to find.
						   &pObject); //Return a pointer to the user
		if (pDS)  pDS->Release();
		
		if (SUCCEEDED(hr))
		{
			BSTR bstr, bstrC;
            		hr = GetParentObject(pObject, //Pointer the object whose parent to bind to.
						&pParent //Return a pointer to the parent object.
						);
			if (SUCCEEDED(hr))
			{
				   wprintf(L"Successfully bound to parent container\n");
				   //Get ADsPath
				   hr = pParent->get_ADsPath(&bstr);
	   			   //Get the distinguishedName property
			          hr = pParent->Get(L"distinguishedName", &var);
				   //Get class
				   hr = pParent->get_Class(&bstrC);
			       if (SUCCEEDED(hr))
				   {
				         wprintf(L"ADsPath: %s\n",bstr);
					  wprintf(L"DN: %s\n",var.bstrVal);
					  wprintf(L"Class: %s\n",bstrC);
				   }
				   else
				  	  wprintf(L"Get method failed with hr: %x\n",hr);
				   VariantClear(&var);
				   //Free the BSTR.
		               FreeADsStr(bstr);
		               FreeADsStr(bstrC);
			}
			else
				wprintf(L"GetParentObject failed with hr: %x\n",hr);
			if (pParent)
				pParent->Release();
		}
		else
		{
            		wprintf(L"User \"%s\" not Found.\n",pszBuffer);
			wprintf (L"FindUserByName failed with the following HR: %x\n", hr);
		}
		if (pObject)
			pObject->Release();
	}	
}


delete pszBuffer;
delete szPath;

//Uninitalize COM
CoUninitialize();

return;
}

HRESULT GetParentObject(IADs *pObject, //Pointer the object whose parent to bind to.
						IADs **ppParent //Return a pointer to the parent object.
						)
{
	if ((!pObject)||(!ppParent))
		return E_INVALIDARG;

	HRESULT hr = E_FAIL;
	BSTR bstr;
	hr = pObject->get_Parent(&bstr);
	if (SUCCEEDED(hr))
	{
		//Bind to the parent container.
		*ppParent = NULL;
	    	hr = ADsOpenObject(bstr,
			 NULL,
			 NULL,
			 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
			 IID_IADs,
			 (void**)ppParent);
		if(FAILED(hr))
		{
			if ((*ppParent))
			{
			  	(*ppParent)->Release();
		      		(*ppParent) = NULL;
			}
		}
	}
       FreeADsStr(bstr);
	return hr;
}





HRESULT FindUserByName(IDirectorySearch *pSearchBase, //Container to search
					   LPOLESTR szFindUser, //Name of user to find.
					   IADs **ppUser) //Return a pointer to the user
{
	HRESULT hr = S_OK;
	
	if ((!pSearchBase)||(!szFindUser))
		return E_INVALIDARG;

	//Create search filter
	LPOLESTR pszSearchFilter = new OLECHAR[MAX_PATH];
	LPOLESTR szADsPath = new OLECHAR[MAX_PATH];
	wcscpy(pszSearchFilter, L"(&(objectCategory=person)(objectClass=user)(cn=");
	wcscat(pszSearchFilter, szFindUser);
	wcscat(pszSearchFilter,	L"))");

	//Search entire subtree from root.
	ADS_SEARCHPREF_INFO SearchPrefs;
	SearchPrefs.dwSearchPref = ADS_SEARCHPREF_SEARCH_SCOPE;
	SearchPrefs.vValue.dwType = ADSTYPE_INTEGER;
	SearchPrefs.vValue.Integer = ADS_SCOPE_SUBTREE;
	DWORD dwNumPrefs = 1;

	// COL for iterations
	ADS_SEARCH_COLUMN col;
	// Handle used for searching
	ADS_SEARCH_HANDLE hSearch;
	// Set the search preference

	hr = pSearchBase->SetSearchPreference( &SearchPrefs, dwNumPrefs);
	if (FAILED(hr))
	{
		delete pszSearchFilter;
		delete szADsPath;
		return hr;
	}

	// Set attributes to return
	LPOLESTR pszAttribute[1] = {L"ADsPath"};

	// Execute the search
	hr = pSearchBase->ExecuteSearch(pszSearchFilter,
	                          			  pszAttribute,
							  1,
							  &hSearch
							  );

	DWORD noUsersFound = 0; 
	if (SUCCEEDED(hr))
	{    

		// Call IDirectorySearch::GetNextRow() to retrieve the next row 
		//of data
		while( pSearchBase->GetNextRow( hSearch) != S_ADS_NOMORE_ROWS )
		{	

			if(noUsersFound>0 && ((*ppUser) != NULL))(*ppUser)->Release();
			wprintf(L"Found User %s.\n",szFindUser); 
			// Get the data for this column
			hr = pSearchBase->GetColumn( hSearch, pszAttribute[0], &col );
			if ( SUCCEEDED(hr) )
			{
				// Print the data for the column and free the column
				// Note the attribute we asked for is type CaseIgnoreString.
				wcscpy(szADsPath, col.pADsValues->CaseIgnoreString); 					
				wprintf(L"%s: %s\r\n",pszAttribute[0],col.pADsValues->CaseIgnoreString); 
				hr = ADsOpenObject(szADsPath,
								 NULL,
								 NULL,
								 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
								 IID_IADs,
								 (void**)ppUser);
				if(SUCCEEDED(hr)) noUsersFound ++;
				
				pSearchBase->FreeColumn( &col );
			}
		}
		// Close the search handle to clean up
        	pSearchBase->CloseSearchHandle(hSearch);
	}

	
	
	if (noUsersFound>1)
	{
		VARIANT var;
		wprintf(L"---------------------------------------------------\n"); 
		wprintf(L"More than one user with CN %s was found.\n",szFindUser); 
		(*ppUser)->Get(L"distinguishedName", &var);
		wprintf(L"Returning pointer to User (DN): %s\n",var.bstrVal); 
		wprintf(L"---------------------------------------------------\n"); 
		VariantClear(&var);
	}

	if(noUsersFound == 0) hr = E_FAIL;

	delete pszSearchFilter;
	delete szADsPath;
	return hr;
}
