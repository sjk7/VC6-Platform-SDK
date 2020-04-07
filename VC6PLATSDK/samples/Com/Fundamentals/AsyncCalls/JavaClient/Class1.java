/*+==========================================================================
  File:      Class1.java
  Summary:	 Simple demo of non-blocking method calls in Java
-----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995-1998 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/
import fullsvr.*;//VS6 imported COM wrapper
import java.io.IOException;

public class Class1
{
	
	public static void main (String[] args)
	{
		int i;
		
		//Create the server
		FullServ pFullServ = new FullServ();
		
		//QueryInterface for ICallFactory
		ICallFactory pICallFactory = (ICallFactory)pFullServ;
		
		//Create the call object
		AsyncIFullServ arrayAsyncIFullServ[] = new AsyncIFullServ[1];
		pICallFactory.CreateCall(AsyncIFullServ.iid,null,AsyncIFullServ.iid,arrayAsyncIFullServ);
		AsyncIFullServ pAsyncIFullServ = arrayAsyncIFullServ[0];
		
		//QueryInterface for ISynchronize
		ISynchronize pISynchronize = (ISynchronize) pAsyncIFullServ;
		
		//Begin non-blocking call
		pAsyncIFullServ.Begin_Sum(2,3);
		
		System.out.println("Waiting for call completion.");
		//Wait for call completion
		try{
			pISynchronize.Wait(0,-1);// -1 = INFINITE
		}catch(com.ms.com.ComFailException cfe){
			System.err.println("Error during Wait");
			return;
		}
		//Finish the call
		i = pAsyncIFullServ.Finish_Sum();
		
		System.out.println("2 + 3 = " + i );	
		
		System.out.println("\n\nPress Enter to continue..\n \n");
		try{System.in.read();}
		catch(IOException e){}

	}
}
