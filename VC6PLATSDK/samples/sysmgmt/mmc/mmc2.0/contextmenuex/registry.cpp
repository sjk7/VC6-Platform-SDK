/////////////////////////////////////////////////////////////////////////////
//
//  This source code is only intended as a supplement to existing
//  Microsoft documentation. 
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1999 - 2001 Microsoft Corporation.  All Rights Reserved.
//


#include <ObjBase.h>
#include "Registry.h"
#include "Globals.h"


#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("Registry")


/////////////////////////////////////////////////////////////////////////////
// Internal helper functions prototypes


// Set the given key and its value.
HRESULT SetKeyAndValue( const TCHAR* pszPath, const TCHAR* szSubkey, const TCHAR* szValue);

// Set the given key and its value in the MMC Snapin location
HRESULT SetSnapInKeyAndValue( const TCHAR* szKey, const TCHAR* szSubkey, const TCHAR* szName, const TCHAR* szValue );

// Set the given valuename under the key to value
HRESULT SetValue( const TCHAR* szKey, const TCHAR* szValueName, const TCHAR* szValue); 

// Delete szKeyChild and all of its descendents.
HRESULT RecursiveDeleteKey( HKEY hKeyParent, const TCHAR* szKeyChild );

// Set the nodetype key and subkeys for this extension
HRESULT SetExtensionKey( const TCHAR* szNodeType );

/////////////////////////////////////////////////////////////////////////////
// Public function implementation


//---------------------------------------------------------------------------
//  Register the component in the registry.  This is the minimalist way
//  to register a component, you may want to add keys for ProgID.
//
HRESULT RegisterServer
(
  HMODULE        hModule,          //[in] DLL module handle
  const CLSID&   clsid,            //[in] Class ID
  const TCHAR*   szFriendlyName    //[in] Name string
)
{
  // Get server location.
  TCHAR    szModule[512] ;
  TCHAR*   pszCLSID = NULL;    
  LPOLESTR wszCLSID = NULL ;
  HRESULT  hResult  = S_FALSE;

  DWORD dwResult = ::GetModuleFileName( hModule, 
                                        szModule,
                                        sizeof(szModule)/sizeof(TCHAR)
                                      );
  if( 0 == dwResult ) return HRESULT_FROM_WIN32( dwResult );

  do                         // Fail unless we complete everything
  {
    // Get CLSID string in wide char
    hResult = StringFromCLSID( clsid, &wszCLSID ) ;
    if( S_OK != hResult )
    {
      CoTaskMemFree( wszCLSID );
      BREAK_ON_ERROR( hResult );
    }  

    W2T( &pszCLSID, wszCLSID );          // W2T is defined in Globals.h  
    CoTaskMemFree( wszCLSID );           // Through with wide version

    TCHAR szKey[64];                     // Build the CLSID key string CLSID\\{...}
    _tcscpy( szKey, _T("CLSID\\") );
    _tcscat( szKey, pszCLSID );
    
    // Add the CLSID to the registry.
    hResult = SetKeyAndValue( szKey, NULL, szFriendlyName );
    BREAK_ON_ERROR( hResult );    
    
    // Add the server filename subkey under the CLSID key.
    hResult = SetKeyAndValue( szKey, _T("InprocServer32"), szModule );
    BREAK_ON_ERROR( hResult );

    // Set the threading model
    _tcscat( szKey, _T("\\InprocServer32") );
    hResult = SetValue( szKey, _T("ThreadingModel"), _T("Apartment") );
    BREAK_ON_ERROR( hResult );

  }while( 0 );

  CoTaskMemFree( pszCLSID );           // Through with TCHAR version
    
  return hResult;
}


//---------------------------------------------------------------------------
// Remove the component from the registry.
//
LONG UnregisterServer
( 
  const CLSID& clsid         //[in] Class ID of component to remove 
)
{
  HRESULT hResult = S_OK;

  // Allocate the CLSID string
  LPOLESTR wszCLSID = NULL ;
  hResult = StringFromCLSID( clsid, &wszCLSID );
  if( S_OK != hResult )
  {
    CoTaskMemFree( wszCLSID );
    return hResult;
  }
     
  // Build the key CLSID\\{...}
  TCHAR szKey[64];
  _tcscpy( szKey, _T("CLSID\\") );

  TCHAR* pszCLSID = NULL;    
  W2T( &pszCLSID, wszCLSID );          // W2T is defined in Globals.h  
  CoTaskMemFree( wszCLSID );           // Through with wide version

  _tcscat( szKey, pszCLSID );
  CoTaskMemFree( pszCLSID );           // Through with TCHAR version
    
  // Delete the CLSID Key - CLSID\{...}
  LONG lResult = RecursiveDeleteKey( HKEY_CLASSES_ROOT, szKey );
  if( ERROR_SUCCESS != lResult )
    hResult = HRESULT_FROM_WIN32( lResult );

  return hResult;
}

//---------------------------------------------------------------------------
// Register the snap-in in the registry.
//
HRESULT RegisterSnapin
(
  const  CLSID&  clsid,              //[in] Class ID
  const  TCHAR*  szNameString,       //[in] NameString
  const  CLSID&  clsidAbout,		     //[in] Class Id for About Class
  const  BOOL    bSupportExtensions  //[in] TRUE if we support extensions
)
{
  HRESULT hResult = S_FALSE; 
  TCHAR*  pszSnapCLSID = NULL;         // Needed for TCHAR version of the ClassID   

  // If any part of this process fails, jump out of the loop and return
  // the error code 
  do
  {
    // Allocate the CLSID string
    LPOLESTR wszSnapCLSID  = NULL ;
    hResult = StringFromCLSID( clsid, &wszSnapCLSID ) ;
    if( S_OK != hResult )
    {
       CoTaskMemFree( wszSnapCLSID );
       continue;
    }  

    W2T( &pszSnapCLSID, wszSnapCLSID );  // W2T is defined in Globals.h  
    CoTaskMemFree( wszSnapCLSID );       // Through with wide version

    // Add the Snap-in's CLSID to the registry
    hResult = SetSnapInKeyAndValue( pszSnapCLSID, NULL, _T("NameString"), szNameString );
    BREAK_ON_ERROR( hResult );
    
    // Extensions don't support ISnapinAbout, so this is not handled
    //
    if( TRUE == bSupportExtensions )     // Build the NodeTypesKey
    {
    }

  }while( 0 );

  hResult = SetExtensionKey( gtszDEVICE_GUID );  

  CoTaskMemFree( pszSnapCLSID);
  return hResult;
}


//---------------------------------------------------------------------------
// Unregister the snap-in in the registry.
//
HRESULT UnregisterSnapin
(
  const CLSID& clsid         //[in] Class ID of object to unregister
)
{
  HRESULT hResult = S_OK;

  TCHAR    szKeyBuf[1024];
  LPOLESTR wszCLSID = NULL;
  TCHAR*   pszCLSID = NULL;        // Needed for TCHAR version of the ClassID   
    
  // Get CLSID as a wide string
  hResult = StringFromCLSID( clsid, &wszCLSID );
  if( S_OK != hResult )
  {
    CoTaskMemFree( wszCLSID );
    return hResult;
  }   

  W2T( &pszCLSID, wszCLSID );          // W2T is defined in Globals.h  
  CoTaskMemFree( wszCLSID );           // Through with wide version

  // Load the buffer with the Snap-In Location
  _tcscpy( szKeyBuf, _T("SOFTWARE\\Microsoft\\MMC\\SnapIns") );
    
  _tcscat( szKeyBuf, _T("\\") );       // Copy keyname into buffer.
  _tcscat( szKeyBuf, pszCLSID );
    
  // Delete the CLSID Key - CLSID\{...}
  LONG lResult = RecursiveDeleteKey( HKEY_LOCAL_MACHINE, szKeyBuf );
  if( ERROR_SUCCESS != lResult ) 
    hResult = HRESULT_FROM_WIN32( lResult );    

  CoTaskMemFree( pszCLSID );
  return hResult;
}

//---------------------------------------------------------------------------
// Delete a key and all of its descendents.
//
HRESULT RecursiveDeleteKey
(
  HKEY          hKeyParent,    //[in] Parent of key to delete
  const TCHAR*  lpszKeyChild   //[in] Key to delete
)
{
  // Open the child.
  HKEY hKeyChild = NULL;
  LONG lResult   = ERROR_SUCCESS;

  do                     // We go to all this trouble to prevent any 
  {                      // possibility of exiting while leaving a key open

    lResult = RegOpenKeyEx( hKeyParent,
                            lpszKeyChild,
                            0,
                            KEY_ALL_ACCESS,
                            &hKeyChild
                          );
    if( ERROR_SUCCESS != lResult )
      continue;
    
    // Enumerate all of the decendents of this child.
    FILETIME time;
    _TCHAR szBuffer[256];
    DWORD dwSize = 256;
    while( S_OK == RegEnumKeyEx(hKeyChild,0,szBuffer,&dwSize,NULL,NULL,NULL,&time) )
    {
      // Delete the decendents of this child.
      lResult = RecursiveDeleteKey( hKeyChild, szBuffer );
      if( ERROR_SUCCESS != lResult )
      {
        continue;
      }
      dwSize = 256;
    }
  }while( 0 );

  RegCloseKey( hKeyChild );            // Always try to close the child
                                       // then delete this child.
  return RegDeleteKey( hKeyParent, lpszKeyChild );
}

//---------------------------------------------------------------------------
// Create a Registry Key and set its value.
//   - This helper function was borrowed and modifed from
//     Kraig Brockschmidt's book Inside OLE.
//
HRESULT SetKeyAndValue
(
  const TCHAR*  szKey,       //[in] Parent key
  const TCHAR*  szSubkey,    //[in] Child key
  const TCHAR*  szValue      //[in] Value to set
)
{
  HKEY hKey = NULL;
  HRESULT hResult = S_FALSE;
  TCHAR szKeyBuf[1024];
    
  // Copy keyname into buffer.
  _tcscpy( szKeyBuf, szKey );
    
  // Add subkey name to buffer.
  if( NULL != szSubkey )
  {
    _tcscat( szKeyBuf, _T("\\") );
    _tcscat( szKeyBuf, szSubkey );
  }

  do                     // We go to all this trouble to prevent any 
  {                      // possibility of exiting while leaving a key open
    
    // Create and open key and subkey.
    long lResult = RegCreateKeyEx( HKEY_CLASSES_ROOT,
                                   szKeyBuf, 
                                   0,
                                   NULL,
                                   REG_OPTION_NON_VOLATILE,
                                   KEY_ALL_ACCESS,
                                   NULL, 
                                   &hKey,
                                   NULL
                                 );
    if( ERROR_SUCCESS != lResult )
    {
      hResult = HRESULT_FROM_WIN32( lResult );
      continue;
    } 
   
    if( NULL != szValue )    // Now set the value
    {
      hResult = RegSetValueEx( hKey,
                               NULL,
                               0,
                               REG_SZ, 
                               (BYTE*)szValue, 
                               BYTE_SIZE( szValue )    // BYTE_SIZE is in Globals.h
                             );
      BREAK_ON_ERROR( hResult );
    }
  }while( 0 );    

  RegCloseKey( hKey );       // Always try to close the key
  return hResult;
}


//---------------------------------------------------------------------------
// Open a key value and set it
//
HRESULT SetValue
(
  const TCHAR*  szKey,         //[in] Parent key
  const TCHAR*  szValueName,   //[in] Name of value
  const TCHAR*  szValue        //[in] Value in string format
)
{
  HKEY    hKey = NULL;
  HRESULT hResult = S_FALSE;
  TCHAR szKeyBuf[1024];
    
  // Copy keyname into buffer.
  _tcscpy( szKeyBuf, szKey );
    
  do                     // We go to all this trouble to prevent any 
  {                      // possibility of exiting while leaving a key open

    // Create and open key and subkey.
    long lResult = RegCreateKeyEx( HKEY_CLASSES_ROOT ,
                                   szKeyBuf, 
                                   0,
                                   NULL,
                                   REG_OPTION_NON_VOLATILE,
                                   KEY_ALL_ACCESS,
                                   NULL, 
                                   &hKey,
                                   NULL
                                 );
    if( ERROR_SUCCESS != lResult )
    {
      hResult = HRESULT_FROM_WIN32( lResult );
      continue;
    }
    
    if( NULL != szValue )    // Now set the value 
    {
      hResult = RegSetValueEx( hKey,
                               szValueName,
                               0,
                               REG_SZ, 
                               (BYTE*)szValue, 
                               BYTE_SIZE( szValue )  
                             );
      BREAK_ON_ERROR( hResult );
    }
  }while( 0 );    
  
  RegCloseKey( hKey );       //Always attempt to close the key
  return hResult;
}


//---------------------------------------------------------------------------
// Create a key and set its value.
//   - This helper function was borrowed and modifed from
//     Kraig Brockschmidt's book Inside OLE.
//
HRESULT SetSnapInKeyAndValue
(
  const TCHAR*  szKey,       //[in] Parent key 
  const TCHAR*  szSubkey,    //[in] Child key
  const TCHAR*  szName,      //[in] Value name
  const TCHAR*  szValue      //[in] Value in string format
)
{
  HKEY    hKey = NULL;
  HRESULT hResult = S_FALSE;
  TCHAR   szKeyBuf[1024];
    
  // Load the buffer with the Snap-In Location
  _tcscpy( szKeyBuf, _T("SOFTWARE\\Microsoft\\MMC\\SnapIns") );
    
  _tcscat( szKeyBuf, _T("\\") );       // Copy keyname into buffer.
  _tcscat( szKeyBuf, szKey );
    
  if( NULL != szSubkey )               // Add subkey name to buffer.
  {
    _tcscat( szKeyBuf, _T("\\") );
    _tcscat( szKeyBuf, szSubkey );
  }

  do                     // We go to all this trouble to prevent any 
  {                      // possibility of exiting while leaving a key open
    
    // Create and open key and subkey.
    long lResult = RegCreateKeyEx( HKEY_LOCAL_MACHINE,
                                   szKeyBuf, 
                                   0,
                                   NULL,
                                   REG_OPTION_NON_VOLATILE,
                                   KEY_ALL_ACCESS,
                                   NULL, 
                                   &hKey,
                                   NULL
                                 );
    if( ERROR_SUCCESS != lResult )     // Will return S_FALSE
      continue;
    
    // Set the Value.
    if( szValue != NULL )
    {
      hResult = RegSetValueEx( hKey,
                               szName,
                               0,
                               REG_SZ, 
                               (BYTE*)szValue, 
                               BYTE_SIZE(szValue)
                             );
      BREAK_ON_ERROR( hResult );
    }
    else                   
    {                        // Got this far so everything is OK. 
      hResult = S_OK;
    }
  }while( 0 );    
  
  RegCloseKey( hKey );       //Always attempt to close the key
  return hResult;
}

//---------------------------------------------------------------------------
// Adds the keys under the MMC/NodeTypes key to register our
// Snapin as an extension.
//
HRESULT SetExtensionKey
(
  const TCHAR*  szNodeType
)
{
  HKEY    hNodeKey = NULL;
  HRESULT hResult  = S_FALSE;
  TCHAR   szKeyBuf[1024];
    
  // Load the buffer with the NodeTypes Location
  _tcscpy( szKeyBuf, _T("SOFTWARE\\Microsoft\\MMC\\NodeTypes") );
    
  _tcscat( szKeyBuf, _T("\\") );       // Copy NodeType GUID into buffer.
  _tcscat( szKeyBuf, szNodeType );

  _tcscat( szKeyBuf, _T("\\") );       // Copy Subkeys into buffer
  _tcscat( szKeyBuf, _T("Extensions\\ContextMenu") );

  long lResult = RegCreateKeyEx( HKEY_LOCAL_MACHINE,
                                 szKeyBuf, 
                                 0,
                                 NULL,
                                 REG_OPTION_NON_VOLATILE,
                                 KEY_ALL_ACCESS,
                                 NULL, 
                                 &hNodeKey,
                                 NULL
                               );
  
  if( ERROR_SUCCESS != lResult )     // Will return S_FALSE
  {
    RegCloseKey( hNodeKey );
    return S_FALSE;
  }
  
  hResult = RegSetValueEx( hNodeKey,
                           gtszCTXMENUX_GUID,
                           0,
                           REG_SZ, 
                           (BYTE*)gtszOBJECT_NAME, 
                           BYTE_SIZE(gtszOBJECT_NAME)
                         );

  return hResult;
}
