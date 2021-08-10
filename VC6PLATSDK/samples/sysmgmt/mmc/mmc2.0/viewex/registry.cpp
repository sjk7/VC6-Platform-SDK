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

// VIEWEX:  New methods to register extensions
//
// Set key for nodes which we want to extend us
HRESULT SetExtensionKey( TCHAR* szNode2Extend, TCHAR* szExtensionNode, TCHAR* szExtensionType, TCHAR* szDescription );

HRESULT SetNodeTypesKey( const TCHAR* szNodeGuid );

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
    
    hResult = SetSnapInKeyAndValue( pszSnapCLSID, _T("StandAlone"), NULL, NULL );
    BREAK_ON_ERROR( hResult );

    // Add registry information for ISnapinAbout if we support it
    LPOLESTR wszAboutCLSID = NULL;
    TCHAR*   pszAboutCLSID = NULL;
    if( IID_NULL != clsidAbout ) 
    {
      hResult = StringFromCLSID( clsidAbout, &wszAboutCLSID );
      if( S_OK != hResult )
      {
        CoTaskMemFree( wszAboutCLSID ); // Free this memory before exiting 
        continue;
      }

      W2T( &pszAboutCLSID, wszAboutCLSID );
      hResult = SetSnapInKeyAndValue( pszSnapCLSID, NULL, _T("About"), pszAboutCLSID );
      CoTaskMemFree( wszAboutCLSID );
      CoTaskMemFree( pszAboutCLSID );
      BREAK_ON_ERROR( hResult );
    }

    if( TRUE == bSupportExtensions )     // Build the NodeTypesKey
    {
      hResult = SetSnapInKeyAndValue( pszSnapCLSID, _T("NodeTypes"), NULL, NULL );
      BREAK_ON_ERROR( hResult );
      TCHAR szKey[64];
      _tcscpy( szKey, pszSnapCLSID );
      _tcscat(szKey, _T("\\NodeTypes"));
      hResult = SetSnapInKeyAndValue( szKey, pszSnapCLSID, NULL, NULL );
      BREAK_ON_ERROR( hResult );

      // VIEWEX:  First set the values for the node which will be extended.
      hResult = SetSnapInKeyAndValue( szKey, gtszCLSID_FOLDERNODE, NULL, NULL );
      BREAK_ON_ERROR( hResult );

      // Add the GUID for the node which will be extended under MMC/NodeTypes
      hResult = SetNodeTypesKey( gtszCLSID_FOLDERNODE );
      BREAK_ON_ERROR( hResult );

      // VIEWEX:  Set MMC's View Extension to extend us
      hResult = SetExtensionKey( gtszCLSID_FOLDERNODE,
                                 gtszCLSID_MMCVIEWEX,
                                 _T("View"),
                                 _T("MMCViewExt 1.0 Object")
                               );
      BREAK_ON_ERROR( hResult );
    }
  }while( 0 );

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
//  VIEWEX:  Adds the keys under the MMC/NodeTypes key to register the 
//           GUID passed in as an extension.
//
HRESULT SetExtensionKey
(
  TCHAR*  szNode2Extend,     //[in] GUID of node we are extending
  TCHAR*  szExtensionNode,   //[in] GUID of extension node
  TCHAR*  szExtensionType,   //[in] Type of extension
  TCHAR*  szDescription      //[in] Description string
)
{
  HKEY    hNodeKey = NULL;
  HRESULT hResult  = S_FALSE;
  TCHAR   szKeyBuf[1024];
    
  // Load the buffer with the NodeTypes Location
  _tcscpy( szKeyBuf, _T("SOFTWARE\\Microsoft\\MMC\\NodeTypes") );
    
  _tcscat( szKeyBuf, _T("\\") );       // Copy NodeType GUID into buffer.
  _tcscat( szKeyBuf, szNode2Extend );

                                       // Copy Subkeys into buffer
  _tcscat( szKeyBuf, _T("\\Extensions\\") );
  _tcscat( szKeyBuf, szExtensionType );
  
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
                           szExtensionNode,
                           0,
                           REG_SZ, 
                           (BYTE*)szDescription, 
                           BYTE_SIZE(szDescription)
                         );

  return hResult;
}

//---------------------------------------------------------------------------
//  VIEWEX:  New method which adds a key for a nodetype guid.  Need to
//           do this for every nodetype which can be extended.
//
HRESULT SetNodeTypesKey
(
  const TCHAR*  szNodeGuid       //[in] Parent key 
)
{
  HKEY    hKey = NULL;
  TCHAR   szKeyBuf[1024];

  // Load the buffer with the Snap-In Location
  _tcscpy( szKeyBuf, _T("SOFTWARE\\Microsoft\\MMC\\NodeTypes") );
  _tcscat( szKeyBuf, _T("\\") );       // Copy keyname into buffer.
  _tcscat( szKeyBuf, szNodeGuid );

  // Create and open key.
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
  
  RegCloseKey( hKey );       //Always close the key
  return (ERROR_SUCCESS == lResult) ? S_OK : S_FALSE;

}

