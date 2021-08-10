//==========================================================================
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1997-1998 Microsoft Corporation.  All Rights Reserved.
//
//==========================================================================

// Standard java imports

import java.applet.*;
import java.awt.*;

// COM and Microsoft Agent imports

import com.ms.com.Variant;
import agentsvr.IAgentEx;
import agentsvr.IAgentNotifySinkEx;
import agentsvr.IAgentCharacterEx;

// This class is an implementation of an IAgentNotifySinkEx.
// All methods are stubs except Click.

public class Notify implements IAgentNotifySinkEx
{
	IAgentEx			m_AgentEx = null;
	IAgentCharacterEx	m_Character = null;
	int					m_RequestID[] = {-1};
	int					m_CommandID = -1;
										 
	private final int	TRUE = 1;
	private final int	MK_LBUTTON = 0x0001;
	
	public Notify()
	{
		// Constructor left intentionally blank
	}

	public void Initialize(IAgentEx agent, 
						   IAgentCharacterEx character,
						   int commandID)
	{
		m_AgentEx = agent;
		m_Character = character;
		m_CommandID = commandID;
	}

	public void Click(int characterID, short keys, int x, int y)
	{
		if ((m_Character != null) && ((keys & MK_LBUTTON) == MK_LBUTTON))
		{
			m_Character.Speak("You clicked on me with the left mouse button.", "", m_RequestID);
		}
	}

	public void DblClick(int characterID, short keys, int x, int y)
	{
	}

	public void Restart()
	{
	}

	public void BookMark(int bookmarkID)
	{
	}

	public void Shutdown()
	{
	}

	public void DragStart(int characterID, short keys, int x, int y)
	{
	}

	public void DragComplete(int characterID, short keys, int x, int y)
	{
	}

	public void ActivateInputState(int characterID, int activated)
	{
	}

	public void Command(int commandID, com.ms.com.IUnknown userInput)
	{
		if (commandID == m_CommandID)
		{
			m_AgentEx.ShowDefaultCharacterProperties((short)-1, (short)-1, TRUE);
		}
	}

	public void RequestStart(int requestID)
	{
	}

	public void RequestComplete(int requestID, int status)
	{
	}

	public void VisibleState(int characterID, int visible, int cause)
	{
	}

	public void Idle(int characterID, int start)
	{
	}

	public void Move(int characterID, int x, int y, int cause)
	{
	}

	public void Size(int characterID, int width, int height)
	{
	}

	public void BalloonVisibleState(int characterID, int visible)
	{
	}
	
	public void HelpComplete(int characterID, int commandID, int cause)
	{
	}
	
	public void ListeningState(int characterID, int state, int cause)
	{
	}
	
	public void DefaultCharacterChange(String guid)
	{
		if (m_Character != null)
		{
			m_Character.Speak("The character changed.", "", m_RequestID);
		}
	}
	
	public void AgentPropertyChange()
	{
	}
	
	public void ActiveClientChange(int characterID, int status)
	{
	}
}
