// otherwko.cpp : Defines the entry point for the console application.
//
#include <wchar.h>
#include <objbase.h>
#include <activeds.h>

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



HRESULT GUIDtoBindableString (LPGUID pGUID, LPOLESTR *ppGUIDString);

HRESULT AddValueToOtherWKOProperty(LPOLESTR szContainerDN, //DN for container whose otherWellKnownObjects property to modify
								   LPGUID pWKOGUID, //WKO GUID for the well-known object.
								   LPOLESTR szWKOObjectDN //DN of the well-known object.
								   );




void wmain( int argc, wchar_t *argv[ ])
{

//Handle the command line arguments.
LPOLESTR pszBuffer = new OLECHAR[MAX_PATH*2];
	wprintf(L"This program does the following:\n");
	wprintf(L"1. Creates a container (MyWKOTestContainer) in the current Window 2000 domain.\n");
	wprintf(L"2. Creates a container object (MyWKOTestObject) within the container.\n");
	wprintf(L"3. Adds a value for the container object on the otherWellKnownObject property of the container.\n");
	wprintf(L"4. Binds to the container object using WKGUID binding string.\n");
	wprintf(L"5. Renames the container object using WKGUID binding string.\n");
	wprintf(L"6. Binds to the container object using WKGUID binding string.\n");
	wprintf(L"7. Optionally, cleans up by removing the container and leaf object.\n\n");
	
	
//Intialize COM
CoInitialize(NULL);

HRESULT hr = S_OK;
IADs *pObject = NULL;
IADsContainer *pDomain = NULL;
IDispatch *pDisp = NULL;
IDispatch *pDispNewContainerObject = NULL;
IADsContainer *pNewContainer = NULL;
IADs *pIADsObject = NULL;
IADs *pNewContainerObject = NULL;

LPOLESTR szNewContainerDN = new OLECHAR[MAX_PATH];
LPOLESTR szPath = new OLECHAR[MAX_PATH];
LPOLESTR szRelPath = new OLECHAR[MAX_PATH];

//Names of the container and child object.
LPOLESTR szContainer = L"MyWKOTestContainer";
LPOLESTR szNewContainerObject = L"MyWKOTestObject";

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
	wcscat(szPath,var.bstrVal);
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
	  wcscat(szRelPath,szContainer);
	  hr = pDomain->Create(L"container", //ldapDisplayName of the class of the object to create.
			                 szRelPath, //relative path in RDN=value format
							 &pDisp); //return an IDispatch pointer to the new object.
	  if (SUCCEEDED(hr))
	  {
		//QI for an IADsContainer interface.
		hr = pDisp->QueryInterface(IID_IADsContainer, (void **)&pNewContainer);
		if (SUCCEEDED(hr))
		{
		  //Create the leaf object in the container.
		  wcscpy(szRelPath,L"cn=");
	      wcscat(szRelPath,szNewContainerObject);
    	  hr = pNewContainer->Create(L"leaf", //ldapDisplayName of the class of the object to create.
	                 szRelPath, //relative path in RDN=value format
					 &pDispNewContainerObject); //return an IDispatch pointer to the new object.
          //QI for an IADs interface.
  		  hr = pNewContainer->QueryInterface(IID_IADs, (void **)&pIADsObject);
		  if (SUCCEEDED(hr))
		  {
			//Get the DN of the new container object
			hr = pIADsObject->Get(L"distinguishedName", &var);
			if (SUCCEEDED(hr))
			{
			  wcscpy(szNewContainerDN, var.bstrVal);
			  VariantClear(&var);
			  hr = NewContainerObject->QueryInterface(IID_IADs, (void **)&pNewContainerObject);
		      if (SUCCEEDED(hr))
			  {
			    //Get the DN for the leaf object
			    hr = pNewContainerObject->Get(L"distinguishedName", &var);
			    if (SUCCEEDED(hr))
				{
				  //FOR BETA 3 only. Need to use LDAP API to set the otherWellKnownObjects property.
                  hr = AddValueToOtherWKOProperty(szNewContainerDN, //DN for container whose otherWellKnownObjects property to modify
								   &MyWKOTestObjectGUID, //WKO GUID for the well-known object.
								   var.bstrVal //DN of the well-known object.
								   );
				}
			  }
		      if (pNewContainerObject)
			    pNewContainerObject->Release();
			}
			VariantClear(&var);
		  }
	      if (pIADsObject)
		    pIADsObject->Release();
	      if (pDispNewContainerObject)
	        pDispNewContainerObject->Release();
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
  DWORD dwGUIDSize = sizeof(OLECHAR)*(wcslen(szGUIDString));
  //Build the DNwithoctetstring
  swprintf(szDNwithOctetString, L"B:%d:%s:%s", dwGUIDSize, szGUIDString,szWKOObjectDN); 
  ULONG ulBerSize = sizeof(OLECHAR)*(wcslen(szDNwithOctetString));
  //Build the BerVal
  PCHAR pByteVal = (PCHAR)szDNwithOctetString;
  berval berWKO;
  berWKO.bv_len = ulBerSize;
  berWKO.bv_val = pByteVal;

  //Build the mod structure to add the value.
  LDAPMod ldWKO;
  //mod_values takes a NULL terminated array of WCHARs.
  //We're adding a single value.
  OLECHAR *berValues[] = { szDNwithOctetString, NULL };
  //Operation
  ldWKO.mod_op = LDAP_MOD_ADD|LDAP_MOD_BVALUES;
  //Attribute
  ldWKO.mod_type = L"otherWellKnownValues";
  //Value to set.
  ldWKO.mod_values = berValues;
  //mods is a NULL terminated array of LDAPMod structures.
  //We're adding a single value.
  LDAPMod *pMod[] = {&ldWKO,NULL};
	
  //Modify the object specified by szContainerDN.
  dwReturn = ldap_modify_s(  hConnect,
	                         szContainerDN,
							 pMod);
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
		wcscat(szPath,L"<WKGUID=");
		wcscat(szPath,szBindableWKGUID);
		wcscat(szPath,L",");
		wcscat(szPath,var.bstrVal);
		wcscat(szPath,L">");
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
	
 

