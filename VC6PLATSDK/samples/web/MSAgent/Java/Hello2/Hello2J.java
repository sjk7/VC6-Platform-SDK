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
// This sample demonstrates the use of Microsoft Agent from a Java Applet
// and the use of a notification sink to receive callbacks from the Agent
// server. It also demonstrates adding a command.
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
import agentsvr.IAgentCommands;

// The HelloAgentJava class (Single threaded)

public class Hello2J extends Applet
{
	// Private members necessary for Agent instantiation

	private IAgentEx			m_AgentEx = null;
	private IAgentCharacterEx	m_Character[] = {null};
	private int					m_CharacterID[] = {-1};
	private IAgentCommands		m_Commands = null;
	private int					m_CommandID[] = {-1};
	private int					m_RequestID[] = {0};
	private final String		m_CharacterPathOld = "\\program files\\microsoft agent\\characters\\merlin.acs";

	private boolean				m_bUsingDefaultCharacter;
	
	// Declare an Agent Notify Sink so that we can get
	// notification callbacks from the Agent server.

	private Notify				m_Sink = null;
	private int					m_SinkID[] = {-1};

	private final int			FALSE = 0;
	private final int			TRUE = 1;


	public Hello2J()
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

		// Create a notify sink object

		m_Sink = new Notify();

		try
		{
			// And register it with Microsoft Agent so that we
			// can receive notifications.
			
			m_AgentEx.Register(m_Sink, m_SinkID);
			
		}
		catch(com.ms.com.ComException eSink)
		{
			stop();
			return;
		}
		
		// Load a character
		
		try
		{
			// First try to load a default character
			
			m_AgentEx.Load(new Variant(), m_CharacterID, m_RequestID);
	
			m_bUsingDefaultCharacter = true;
			
		}
		catch(com.ms.com.ComException e)
		{
			// No default character. Try to load Merlin from the directory
			// most commonly used in version 1.5 applications.
			
			Variant characterPath = new Variant();
			characterPath.putString(m_CharacterPathOld);

			try {
				
				m_AgentEx.Load(characterPath, m_CharacterID, m_RequestID);
			
				m_bUsingDefaultCharacter = false;
				
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
			
			// If we successfully loaded the default character,
			// add a command so that the user can switch characters.
			
			if (m_bUsingDefaultCharacter)
			{			
				m_Commands = (IAgentCommands)m_Character[0];
				m_Commands.Add("&Choose Character...", "", TRUE, TRUE, m_CommandID);
				m_Commands = null;
			}
			
			// Give our notify sink access to the necessary data

			m_Sink.Initialize(m_AgentEx, m_Character[0], m_CommandID[0]);

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

		// Unregister the notify sink, we're done with the
		// Agent server.

		if (m_SinkID[0] > 0)
		{
			m_AgentEx.Unregister(m_SinkID[0]);
			m_SinkID[0] = -1;
		}

		m_Sink = null;
		m_AgentEx = null;
	}
}
