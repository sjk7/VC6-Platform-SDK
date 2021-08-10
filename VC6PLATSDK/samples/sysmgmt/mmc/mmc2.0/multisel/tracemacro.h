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
//  TraceMacro.h : Defines custom tracing helpers.
//


#ifndef _TRACE_MACRO_HEADER_
#define _TRACE_MACRO_HEADER_

//---------------------------------------------------------------------------
//  Function prototypes
//
VOID Trace_Start( LPCTSTR pszClass, LPCTSTR pszFunction );
VOID Trace_HR( LPCTSTR pszClass, LPCTSTR pszFunction, HRESULT hr );
VOID Trace_Value( LPCTSTR pszClass, LPCTSTR pszFunction, LPCTSTR pszValueName, LONG nValue ); 
VOID Trace_Pointer( LPCTSTR pszClass, LPCTSTR pszFunction, LPCTSTR pszObject, ULONG ulValue ); 
VOID Trace_Event( LPCTSTR pszClass, LPCTSTR pszFunction, LONG nEvent );
VOID MapEvent( LONG Event, LPTSTR szEventStr );


// Alternate version provides complete path to the file
// #define TRACE_HRESULT(str,hr)  Trace_HR( _T(__FILE__), (str), (hr) )

#ifdef _DEBUG                                                                                               

#undef  TRACE_HRESULT                                             
#define TRACE_HRESULT(s1,hr) Trace_HR( (MODULESTRING),(s1),(hr) )         

#undef  TRACE_VAL                                                        
#define TRACE_VAL(s1,s2,val) Trace_Value( (MODULESTRING),(s1),(s2),(val) )   

#undef  TRACE_PTR                                                        
#define TRACE_PTR(s1,s2,val) Trace_Pointer( (MODULESTRING),(s1),(s2),(val) )   

#undef  TRACE_EVENT                                                      
#define TRACE_EVENT(s1,val)  Trace_Event( (MODULESTRING),(s1),(val) )  

#undef  TRACE_START
#define TRACE_START( s1 )    Trace_Start( (MODULESTRING),(s1) )


#else 
                                                         
#undef  TRACE_HRESULT                                          
#define TRACE_HRESULT                                          

#undef  TRACE_VAL                                          
#define TRACE_VAL                                          

#undef  TRACE_PTR                                         
#define TRACE_PTR                                          

#undef  TRACE_EVENT
#define TRACE_EVENT

#undef  TRACE_START
#define TRACE_START

#endif //_DEBUG                                                          


#endif //_TRACE_MACRO_HEADER_
