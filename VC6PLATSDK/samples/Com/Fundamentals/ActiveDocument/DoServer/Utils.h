// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------

/**************************************************************************

  File:          Utils.h
  
	Description:   Utility definitions.
	
**************************************************************************/

/**************************************************************************
function prototypes
**************************************************************************/

STDAPI_(void) ParseCommandLine(LPSTR, LPBOOL, LPTSTR);
static LPTSTR GetWord(LPTSTR, LPTSTR);
STDAPI GetOleObjectDataHere(LPPERSISTSTORAGE, LPFORMATETC, LPSTGMEDIUM);

/**************************************************************************
global variables
**************************************************************************/

#define EMBEDDINGFLAG TEXT("Embedding")

