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
// This sample demonstrates loading and showing 2 Microsoft Agent characters
// and synchronizing their actions.  It also demonstrates the use of the 
// RequestComplete notification and an Agent notify sink.
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

// The Hello3J class (Single threaded)

public class Hello3J extends Applet
{
	// Private members necessary for Agent instantiation.  Change the
	// location of the characters to where they are stored on your system.

	private IAgentEx			m_AgentEx = null;
	private int					m_WaitID[] = {-1};
	private int					m_RequestID[] = {0};
	private IAgentCharacterEx	m_Merlin[] = {null};
	private int					m_MerlinID[] = {-1};
	private IAgentCharacterEx	m_Genie[] = {null};
	private int					m_GenieID[] = {-1};
	private final String		m_MerlinFilename = "merlin.acs";
	private final String		m_GenieFilename = "genie.acs";
	private final String		m_OldPath = "\\program files\\microsoft agent\\characters\\";

	// Declare an Agent Notify Sink so that we can get
	// notification callbacks from the Agent server.

	private Notify			m_Sink = null;
	private int				m_SinkID[] = {-1};

	private final int		FALSE = 0;
	private final int		TRUE = 1;


	public Hello3J()
	{
		// Constructor left intentionally blank
	}

	public String getAppletInfo()
	{
		return "Name: Hello3J\r\n" +
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

	private boolean LoadCharacter(String filename, 
								  int[] characterID, 
								  IAgentCharacterEx[] character)
	{
		try
		{
			// First, try to load using just the filename. This is
			// a new feature for Agent 2.0. Agent will look in the
			// %windows%\msagent\chars directory.
			
			m_AgentEx.Load(new Variant(filename), characterID, m_RequestID); 

		}
		catch(com.ms.com.ComException e)
		{
			// Couldn't load it. Construct a path using the directory
			// most common to Agent 1.5 applications and try to load
			// from there.
						
			try
			{
				
				m_AgentEx.Load(new Variant(m_OldPath + filename), characterID, m_RequestID);
			
			}
			catch(com.ms.com.ComException e2)
			{
				return false;
			}
		}
		
		try
		{
			// Get the IAgentCharacter interface. 
			// NOTE NOTE NOTE!!! If you are using Visual J++ or
			// other Java environments that can correctly handle
			// derived COM types (e.g. IAgentCharacterEx) then you
			// can retrieve the character interface with a single
			// call to GetCharacterEx.
			//
			//		m_AgentEx.GetCharacterEx(characterID[0], character);
			//
			// Some environments (e.g. Visual J++ 1.1) do not correctly
			// handle derived COM types. So retrieving the IAgentCharacterEx
			// interface is a 2 step process. First get the IAgentCharacter
			// interface.
			
			IAgentCharacter char15[] = {null};			
			m_AgentEx.GetCharacter(characterID[0], char15);
			
			// Then get the IAgentCharacterEx interface and release
			// the IAgentCharacter interface.
			
			character[0] = (IAgentCharacterEx)char15[0];
			char15 = null;
			
		}
		catch(com.ms.com.ComException e3)
		{
			return false;
		}
		
		return true;
	}		
			
	public void start()
	{
		// Start the Microsoft Agent Server

		m_AgentEx = (IAgentEx) new AgentServer();

		// Create and register a notify sink

		m_Sink = new Notify(this);

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
		
		// Load the characters
		
		if (!LoadCharacter(m_MerlinFilename, m_MerlinID, m_Merlin) ||
			!LoadCharacter(m_GenieFilename, m_GenieID, m_Genie))
		{
			stop();
			return;
		}
		
		try {

			// Set their language
			
			m_Genie[0].SetLanguageID(0x0409);
			m_Merlin[0].SetLanguageID(0x0409);
			
			// Position the characters

			m_Genie[0].MoveTo((short)0, (short)100, 0, m_RequestID);
			m_Merlin[0].MoveTo((short)200, (short)100, 0, m_RequestID);

			// Show them

			m_Genie[0].Show(FALSE, m_RequestID);
			m_Merlin[0].Show(FALSE, m_RequestID);

			// Have Genie gesture towards Merlin

			m_Genie[0].GestureAt((short)150, (short)100, m_RequestID);

			// And have Genie say hello to Merlin

			m_Genie[0].Speak("Hi there Merlin.", null, m_WaitID);

			// Make Merlin wait for Genie to finish speaking

			m_Merlin[0].Wait(m_WaitID[0], m_RequestID);

			// Have Merlin gesture towards Genie

			m_Merlin[0].GestureAt((short)0, (short)100, m_RequestID);

			// And then speak back to Genie.  Use a request id owned by the
			// sink object.  When we get a request complete notification, the
			// sink will call back into the applet.

			m_Merlin[0].Speak("Hi Genie.  See you later", null, m_Sink.m_DoneID);

		}
		catch(com.ms.com.ComException e)
		{
			stop();
		}
	}
	
	public void stop()
	{
		// Unload the characters

		if (m_MerlinID[0] > 0)
		{
			m_Merlin[0] = null;
			m_AgentEx.Unload(m_MerlinID[0]);
			m_MerlinID[0] = -1;
		}

		if (m_GenieID[0] > 0)
		{
			m_Genie[0] = null;
			m_AgentEx.Unload(m_GenieID[0]);
			m_GenieID[0] = -1;
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

	public void HideCharacters()
	{
		// This method is called by the notification sink when the
		// last Agent request has completed.  We'll just hide the
		// characters.

		m_Merlin[0].Hide(FALSE, m_RequestID);
		m_Genie[0].Hide(FALSE, m_RequestID);
	}
}
