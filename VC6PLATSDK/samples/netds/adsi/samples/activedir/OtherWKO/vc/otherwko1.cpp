// otherwko.cpp : Defines the entry point for the console application.
//
#include <wchar.h>
#include <objbase.h>
#include <activeds.h>
#include <stdio.h>
//Make sure you define UNICODE
//Need to define version 5 for Windows 2000
#define _WIN32_WINNT 0x0500
//FOR LDAP API...Required for Beta 3 only.
#include <winldap.h>
//Need to link against the following LIBs:
//wldap32.lib


static GUID MyWKOTestObjectGUID = { /* df447b5e-aa5b-11d2-8d53-00c04f79ab81 */
    0xdf447b5e,
    0xaa5b,
    0x11d2,
    {0x8d, 0x53, 0x00, 0xc0, 0x4f, 0x79, 0xab, 0x81}
  };


int IS_BUFFER_ENOUGH(UINT maxAlloc, LPWSTR pszTarget, LPCWSTR pszSource, int toCopy=-1);
bool SAFE_APPEND(int targetSize, LPWSTR szTarget, LPCWSTR szSource);


HRESULT GUIDtoBindableString (LPGUID pGUID, LPOLESTR *ppGUIDString);

HRESULT AddValueToOtherWKOProperty(LPOLESTR szContainerDN, //DN for container whose otherWellKnownObjects property to modify
								   LPGUID pWKOGUID, //WKO GUID for the well-known object.
								   LPOLESTR szWKOObjectDN //DN of the well-known object.
								   );




void wmain( int argc, wchar_t *argv[ ])
{

int allocBuffer = MAX_PATH*2;
LPOLESTR pszBuffer = new OLECHAR[allocBuffer];
	wprintf(L"This program does the following:\n");
	wprintf(L"1. Creates a container (MyWKOTestContainer) in the current Window 2000 domain.\n");
	wprintf(L"2. Creates a container object (MyWKOTestObject) within the container.\n");
	wprintf(L"3. Adds a value for the container object on the otherWellKnownObject property of the container.\n");
	wprintf(L"4. Binds to the container object using WKGUID binding string.\n");
	wprintf(L"5. Renames the container object using WKGUID binding string.\n");
	wprintf(L"6. Binds to the container object using WKGUID binding string.\n");
	wprintf(L"7. Optionally, cleans up by removing the container and container object.\n\n");
	
	
//Intialize COM
CoInitialize(NULL);

HRESULT hr = S_OK;
IADs *pObject = NULL;
IADsContainer *pDomain = NULL;
IDispatch *pDisp = NULL;
IDispatch *pDispNewObject = NULL;
IADsContainer *pNewContainer = NULL;
IADs *pIADsObject = NULL;
IADs *pNewObject = NULL;
IADs *pTestWKO1 = NULL;
IADs *pTestWKO2 = NULL;
VARIANT vartest;
BSTR bstr;

LPOLESTR szNewContainerDN = new OLECHAR[MAX_PATH];
LPOLESTR szPath = new OLECHAR[MAX_PATH];
LPOLESTR szRelPath = new OLECHAR[MAX_PATH];
LPOLESTR szGUIDString = NULL;

//Names of the container and child object.
LPOLESTR szContainer = L"MyWKOTestContainer";
LPOLESTR szNewObject = L"MyWKOTestObject";

LPOLESTR szNewObjectRenameRDN = L"cn=ObjectwithNEWNAME";

//Get rootDSE and the domain container's DN.
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
   return;
}

hr = pObject->Get(L"defaultNamingContext",&var);
if (SUCCEEDED(hr))
{
	//Build the ADsPath to the domain
	wcscpy(szPath,L"LDAP://");
	if (!SAFE_APPEND(MAX_PATH, szPath, var.bstrVal) )
	{
		pObject->Release();
		VariantClear(&var);
		wprintf(L"Buffer is to small, operation is aborting...");
		return;
	}
	VariantClear(&var);
	//Bind to the current domain.
	hr = ADsOpenObject(szPath,
					 NULL,
					 NULL,
					 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
					 IID_IADsContainer,
					 (void**)&pDomain);
	if (SUCCEEDED(hr))
	{
	  //Create the container.
	  wcscpy(szRelPath,L"cn=");

	  // Check if there is enough buffer.
	  if ( IS_BUFFER_ENOUGH(MAX_PATH, szRelPath, szContainer) > 0 )
	  {
	     wcscat(szRelPath,szContainer);
	  }
	  else
	  {
		  pObject->Release();
		  pDomain->Release();
		  wprintf(L"Buffer is to small, operation is aborting...");
		  return;
	  }


	  hr = pDomain->Create(L"container", //ldapDisplayName of the class of the object to create.
			                 szRelPath, //relative path in RDN=value format
							 &pDisp); //return an IDispatch pointer to the new object.
	  if (SUCCEEDED(hr))
	  {
        //QI for an IADs interface.
	    hr = pDisp->QueryInterface(IID_IADs, (void **)&pIADsObject);
		//Commit the new object to the directory.
		hr = pIADsObject->SetInfo();
		//QI for an IADsContainer interface.
		hr = pDisp->QueryInterface(IID_IADsContainer, (void **)&pNewContainer);
		if (SUCCEEDED(hr))
		{
		  //Create the new container object in the container.
		  wcscpy(szRelPath,L"cn=");

		  // Check for potential buffer overrun
		  if (!SAFE_APPEND(MAX_PATH, szRelPath, szNewObject) )
		  {
				  pObject->Release();
				  pDomain->Release();
				  pDisp->Release();
				  VariantClear(&var);
				  wprintf(L"Buffer is too small to hold the string");
				  return;
		  }
	      
    	  hr = pNewContainer->Create(L"container", //ldapDisplayName of the class of the object to create.
	                 szRelPath, //relative path in RDN=value format
					 &pDispNewObject); //return an IDispatch pointer to the new object.
		  if (SUCCEEDED(hr))
		  {
			//Get the DN of the new container object
			hr = pIADsObject->Get(L"distinguishedName", &var);
			if (SUCCEEDED(hr))
			{
			  if (!SAFE_APPEND(MAX_PATH, szNewContainerDN, var.bstrVal) )
			  {
				  pObject->Release();
				  pDomain->Release();
				  pDisp->Release();
				  pIADsObject->Release();
				  VariantClear(&var);
				  wprintf(L"Buffer is too small to hold the string");
				  return;
			  }
			  wcscpy(szNewContainerDN, var.bstrVal);
			  VariantClear(&var);
			  wprintf(L"Created new container with DN: %s\n",szNewContainerDN);
			  hr = pDispNewObject->QueryInterface(IID_IADs, (void **)&pNewObject);
		      if (SUCCEEDED(hr))
			  {
		        //Commit the new object to the directory.
		        hr = pNewObject->SetInfo();
			    //Get the DN for the new object
			    hr = pNewObject->Get(L"distinguishedName", &var);
			    if (SUCCEEDED(hr))
				{
	  			  wprintf(L"Created new child object with DN: %s\n",var.bstrVal);
				  //FOR BETA 3 only. Need to use LDAP API to set the otherWellKnownObjects property.
				  wprintf(L"Call AddValueToOtherWKOProperty with:\n");
				  wprintf(L"szContainer DN: %s\n",szNewContainerDN);
				  GUIDtoBindableString (&MyWKOTestObjectGUID, &szGUIDString);
				  wprintf(L"pWKOGUID (bindable string format): %s\n",szGUIDString);
				  wprintf(L"szWKOObjectDN: %s\n",var.bstrVal);
                  hr = AddValueToOtherWKOProperty(szNewContainerDN, //DN for container whose otherWellKnownObjects property to modify
								   &MyWKOTestObjectGUID, //WKO GUID for the well-known object.
								   var.bstrVal //DN of the well-known object.
								   );
				  wprintf(L"AddValueToOtherWKOProperty returned: %x\n",hr);
				  if (SUCCEEDED(hr))
				  {
					  //Now bind using WKGUID binding
					  //Build the ADsPath to the well-known object
					  
	                  wcscpy(szPath,L"LDAP://<WKGUID=");
					  SAFE_APPEND(MAX_PATH, szPath,szGUIDString);
					  SAFE_APPEND(MAX_PATH, szPath,L",");
					  SAFE_APPEND(MAX_PATH, szPath,szNewContainerDN);
					  SAFE_APPEND(MAX_PATH, szPath,L">");
  					  
				      wprintf(L"Bind with the following WKGUID binding string: %s\n",szPath);
					  hr = ADsOpenObject(szPath,
						 NULL,
						 NULL,
						 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
						 IID_IADs,
						 (void**)&pTestWKO1);
					  if (SUCCEEDED(hr))
					  {
						  hr = pTestWKO1->Get(L"distinguishedName",&vartest);
	  					  if (SUCCEEDED(hr))
						  {
	  				        wprintf(L"Successfully bound to object. DN: %s\n",vartest.bstrVal);
				  			VariantClear(&vartest);
						  }
					  }
					  else
  				        wprintf(L"Binding failed with hr: %x\n",hr);
					  
					  if (pTestWKO1)
						  pTestWKO1->Release();
					  //Bind again using the DN to get a regular ADsPath.
	                  wcscpy(szPath,L"LDAP://");
					  SAFE_APPEND(MAX_PATH, szPath,var.bstrVal);
					  
					  hr = ADsOpenObject(szPath,
						 NULL,
						 NULL,
						 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
						 IID_IADs,
						 (void**)&pTestWKO1);
					  hr = pTestWKO1->get_ADsPath(&bstr);
					  //Rename the WKO object
					  hr = pNewContainer->MoveHere(bstr,szNewObjectRenameRDN,NULL);
					  FreeADsStr(bstr);
					  if (pTestWKO1)
						  pTestWKO1->Release();
					  //Now AGAIN bind using WKGUID binding
					  //Build the ADsPath to the well-known object
	                  wcscpy(szPath,L"LDAP://<WKGUID=");
					  SAFE_APPEND(MAX_PATH, szPath,szGUIDString);
					  SAFE_APPEND(MAX_PATH, szPath,L",");
					  SAFE_APPEND(MAX_PATH, szPath,szNewContainerDN);
					  SAFE_APPEND(MAX_PATH, szPath,L">");
  					  
					  wprintf(L"Bind AGAIN with the following WKGUID binding string: %s\n",szPath);
					  hr = ADsOpenObject(szPath,
						 NULL,
						 NULL,
						 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
						 IID_IADs,
						 (void**)&pTestWKO2);
					  if (SUCCEEDED(hr))
					  {
						  hr = pTestWKO2->Get(L"distinguishedName",&vartest);
	  					  if (SUCCEEDED(hr))
						  {
	  				        wprintf(L"Successfully bound to object (Note the DN reflects the rename). DN: %s\n",vartest.bstrVal);
				  			VariantClear(&vartest);
						  }
					  }
					  else
  				        wprintf(L"Binding failed with hr: %x\n",hr);
				  }
				  CoTaskMemFree(szGUIDString);
				}
			  }
		      if (pNewObject)
			    pNewObject->Release();
			}
			VariantClear(&var);
		  }
	      if (pIADsObject)
		    pIADsObject->Release();
	      if (pDispNewObject)
	        pDispNewObject->Release();
		}

		//Ask user if they want us to delete the test containers.
		wprintf(L"Do you want to delete the test container and object (Y/N):");
		fgetws(pszBuffer,allocBuffer,stdin);
	
		if (0==wcsnicmp(L"Y", pszBuffer,1))
		{
			//Delete the object
			//Delete the container
			hr = pNewContainer->Delete(L"container",szNewObjectRenameRDN);
            if (SUCCEEDED(hr))
			{
			  wprintf(L"Successfully deleted test object.\n");
			  wcscpy(szRelPath,L"cn=");
			  SAFE_APPEND(MAX_PATH, szRelPath,szContainer);
  			
			  //Delete the container
			  hr = pDomain->Delete(L"container",szRelPath);
			  if (SUCCEEDED(hr))
			    wprintf(L"Successfully deleted test container and its contents.\n");
			  else
			    wprintf(L"Failed to delete test container and its contents. hr: %x\n",hr);
			}
			else
			  wprintf(L"Failed to delete test container and its contents. hr: %x\n",hr);
		}

	    if (pNewContainer)
	      pNewContainer->Release();
	  }
	  if (pDisp)
		  pDisp->Release();
	}
    if (pDomain)
    pDomain->Release();
}
if (pObject)
   pObject->Release();

//Uninitalize COM
CoUninitialize();

	return;
}

HRESULT AddValueToOtherWKOProperty(LPOLESTR szContainerDN, //DN for container whose otherWellKnownObjects property to modify
								   LPGUID pWKOGUID, //WKO GUID for the well-known object.
								   LPOLESTR szWKOObjectDN //DN of the well-known object.
								   )
{
HRESULT hr = E_FAIL;
LPOLESTR szGUIDString = new OLECHAR[MAX_PATH];
int      maxAlloc = MAX_PATH*2;
LPOLESTR szDNwithOctetString = new OLECHAR[MAX_PATH*2];
DWORD dwReturn;
//Connection handle
LDAP *hConnect = NULL;
//Specify NULL to bind to a DC in the current computer's domain.
//LDAP_PORT is the default port, 389
hConnect  = ldap_open(NULL,  LDAP_PORT);
//Bind using the preferred authentication method on Windows 2000
//and the logged on user's security context.
dwReturn = ldap_bind_s( hConnect, NULL, NULL, LDAP_AUTH_NEGOTIATE );
if (dwReturn==LDAP_SUCCESS)
{

  //Create the WKO value to add.
  GUIDtoBindableString (pWKOGUID, &szGUIDString);
  DWORD dwGUIDSize = (wcslen(szGUIDString));
  OLECHAR szLen[64];
  //Build the DNwithoctetstring
 
  
  wcscpy(szDNwithOctetString, L"B:");
  swprintf(szLen,L"%d", dwGUIDSize);
  SAFE_APPEND(maxAlloc, szDNwithOctetString,szLen);
  SAFE_APPEND(maxAlloc, szDNwithOctetString,L":");
  SAFE_APPEND(maxAlloc, szDNwithOctetString,szGUIDString);
  SAFE_APPEND(maxAlloc, szDNwithOctetString,L":");
  SAFE_APPEND(maxAlloc, szDNwithOctetString,szWKOObjectDN);

  //swprintf(szDNwithOctetString, L"B:%d:%s:%s", dwGUIDSize, szGUIDString,szWKOObjectDN); 
//  ULONG ulBerSize = (wcslen(szDNwithOctetString));
  //Build the BerVal
//  PCHAR pByteVal = (PCHAR)szDNwithOctetString;
//  berval berWKO;
//  berWKO.bv_len = ulBerSize;
//  berWKO.bv_val = pByteVal;
  //Build the mod structure to add the value.
  LDAPMod ldWKO;
  //mod_values takes a NULL terminated array of WCHARs.
  //We're adding a single value.
  WCHAR *StrValues[] = {szDNwithOctetString , NULL };
  //Operation
  ldWKO.mod_op = LDAP_MOD_ADD;
  //Attribute
  ldWKO.mod_type = L"otherWellKnownObjects";
  //Value to set.
  ldWKO.mod_vals.modv_strvals = StrValues;
  //mods is a NULL terminated array of LDAPMod structures.
  //We're adding a single value.
  LDAPMod *pMod[] = {&ldWKO,NULL};
	
  //Modify the object specified by szContainerDN.
  dwReturn = ldap_modify_s(  hConnect,
	                         szContainerDN,
							 pMod);
  CoTaskMemFree(szGUIDString);

  if (dwReturn==LDAP_SUCCESS)
	  hr = S_OK;
}
return hr;
}





HRESULT GUIDtoBindableString (LPGUID pGUID, LPOLESTR *ppGUIDString)
{
HRESULT hr = E_FAIL;
if (!pGUID)
  return E_INVALIDARG;
//Build bindable GUID string
LPOLESTR szDSGUID = new WCHAR [128];
DWORD dwLen =  sizeof(*pGUID);
LPBYTE lpByte = (LPBYTE) pGUID;
//Copy a blank string to make it a zero length string.
wcscpy( szDSGUID, L"" );
//Loop through to add each byte to the string.
for( DWORD dwItem = 0L; dwItem < dwLen ; dwItem++ )
{
  //Append to szDSGUID, double-byte, byte at dwItem index.
  swprintf(szDSGUID + wcslen(szDSGUID), L"%02x", lpByte[dwItem]);
  if( wcslen( szDSGUID ) > 128 )
    break;
}
//Allocate memory for string
*ppGUIDString = (OLECHAR *)CoTaskMemAlloc (sizeof(OLECHAR)*(wcslen(szDSGUID)+1));
if (*ppGUIDString)
  wcscpy(*ppGUIDString, szDSGUID);
else
  hr=E_FAIL;
//Caller must free ppGUIDString using CoTaskMemFree.
return hr;
}


// This function gets the specified well-known object for the current user's domain.

HRESULT GetWKOObject(LPOLESTR szBindableWKGUID, //IN. Bindable string GUID of well-known object.
						  IADs **ppObject //OUT. Return a pointer to the specified well-known object.
						  )
{
HRESULT hr = E_FAIL;
//Get rootDSE and the domain container's DN.
IADs *pObject = NULL;
LPOLESTR szPath = new OLECHAR[MAX_PATH];
VARIANT var;
hr = ADsOpenObject(L"LDAP://rootDSE",
				 NULL,
				 NULL,
				 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
				 IID_IADs,
				 (void**)&pObject);

//Get current domain DN.
if (SUCCEEDED(hr))
{
	hr = pObject->Get(L"defaultNamingContext",&var);
	if (SUCCEEDED(hr))
	{
		//Build the WKGUID binding string.
		wcscpy(szPath,L"LDAP://");
		SAFE_APPEND(MAX_PATH, szPath,L"<WKGUID=");
		SAFE_APPEND(MAX_PATH, szPath,szBindableWKGUID);
		SAFE_APPEND(MAX_PATH, szPath,L",");
		SAFE_APPEND(MAX_PATH, szPath,var.bstrVal);
		SAFE_APPEND(MAX_PATH, szPath,L">");

		//Print the binding string.
		//wprintf(L"WKGUID binding string: %s\n",szPath);
		VariantClear(&var);
		//Bind to the well-known object.
		hr = ADsOpenObject(szPath,
						 NULL,
						 NULL,
						 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
						 IID_IADs,
						 (void**)ppObject);
		if (FAILED(hr))
		{
			if (*ppObject)
			{
			  (*ppObject)->Release();
			  (*ppObject) = NULL;
			}
		}
	}
}
if (pObject)
  pObject->Release();

return hr;
}




int IS_BUFFER_ENOUGH(UINT maxAlloc, LPWSTR pszTarget, LPCWSTR pszSource, int toCopy)
{
	     
         if (toCopy == -1)

          {
               toCopy = wcslen(pszSource);
          }

		  return maxAlloc - (wcslen(pszTarget) + toCopy + 1); 
}



bool SAFE_APPEND(int targetSize, LPWSTR szTarget, LPCWSTR szSource) 
{
	if ( IS_BUFFER_ENOUGH( targetSize, szTarget, szSource) > 0 )
	{
	  wcscpy(szTarget, szSource);
	  return true;
	}

	return false;
}
 

