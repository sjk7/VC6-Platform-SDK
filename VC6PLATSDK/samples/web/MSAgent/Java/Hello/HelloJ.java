//==========================================================================
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1997-1998 Microsoft Corporation.  All Rights Reserved.
//
//--------------------------------------------------------------------------
//
// This sample demonstrates the simplest use of Microsoft Agent from a 
// Java Applet.
//
//==========================================================================

// Standard java imports

import java.applet.*;
import java.awt.*;

// COM and Microsoft Agent imports

import com.ms.com.Variant;
import agentsvr.AgentServer;
import agentsvr.IAgentEx;
import agentsvr.IAgentCharacter;
import agentsvr.IAgentCharacterEx;

// The HelloAgentJava class (Single threaded)

public class HelloJ extends Applet
{
	// Private members necessary for Agent instantiation

	private IAgentEx			m_AgentEx = null;
	private IAgentCharacterEx	m_Character[] = {null};
	private int					m_CharacterID[] = {-1};
	private int					m_RequestID[] = {0};
	private final String		m_CharacterPathOld = "\\program files\\microsoft agent\\characters\\merlin.acs";

	private final int			FALSE = 0;
	private final int			TRUE = 1;


	public HelloJ()
	{
		// Constructor left intentionally blank
	}

	public String getAppletInfo()
	{
		return "Name: HelloJ\r\n" +
		       "Author: anonymous\r\n" +
		       "Created with Microsoft Visual J++ Version 1.1";
	}

	public void init()
	{
    	resize(0, 0);
	}

	public void destroy()
	{
	}

	public void paint(Graphics g)
	{
	}

	public void start()
	{
		// Start the Microsoft Agent Server

		m_AgentEx = (IAgentEx) new AgentServer();

		try
		{
			// First try to load a default character
			
			m_AgentEx.Load(new Variant(), m_CharacterID, m_RequestID);
			
		}
		catch(com.ms.com.ComException e)
		{
			// No default character. Try to load Merlin from the directory
			// most commonly used in version 1.5 applications.
			
			Variant characterPath = new Variant();
			characterPath.putString(m_CharacterPathOld);

			try {
				
				m_AgentEx.Load(characterPath, m_CharacterID, m_RequestID);
			
			}
			catch(com.ms.com.ComException e2)
			{
				// Hmmm.  We couldn't load the character so what else
				// can we do?

				stop();
				return;
			}
		}

		try {

			// Get the IAgentCharacter interface. 
			// NOTE NOTE NOTE!!! If you are using Visual J++ or
			// other Java environments that can correctly handle
			// derived COM types (e.g. IAgentCharacterEx) then you
			// can retrieve the character interface with a single
			// call to GetCharacterEx.
			//
			//		m_AgentEx.GetCharacterEx(m_CharacterID[0], m_Character);
			//
			// Some environments (e.g. Visual J++ 1.1) do not correctly
			// handle derived COM types. So retrieving the IAgentCharacterEx
			// interface is a 2 step process. First get the IAgentCharacter
			// interface.
			
			IAgentCharacter char15[] = {null};			
			m_AgentEx.GetCharacter(m_CharacterID[0], char15);
			
			// Then get the IAgentCharacterEx interface and release
			// the IAgentCharacter interface.
			
			m_Character[0] = (IAgentCharacterEx)char15[0];
			char15 = null;
			
			// Set the character's language
			
			m_Character[0].SetLanguageID(0x0409);
			
			// Show the character

			m_Character[0].Show(FALSE, m_RequestID);

			// And speak hello

			m_Character[0].Speak("Hello World!", null, m_RequestID);

		}
		catch(com.ms.com.ComException e)
		{
			stop();
		}
	}
	
	public void stop()
	{
		if (m_CharacterID[0] > 0)
		{
			m_Character[0] = null;
			m_AgentEx.Unload(m_CharacterID[0]);
			m_CharacterID[0] = -1;
		}

		m_AgentEx = null;
	}
}
