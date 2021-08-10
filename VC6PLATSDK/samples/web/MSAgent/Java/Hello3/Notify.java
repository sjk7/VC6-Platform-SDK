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
import agentsvr.IAgentNotifySinkEx;

// This class is an implementation of an IAgentNotifySinkEx.
// All methods are stubs except RequestComplete.

public class Notify implements IAgentNotifySinkEx
{
	public  int				m_DoneID[] = {-1};
	private Hello3J			m_Applet;

	public Notify(Hello3J applet)
	{
		m_Applet = applet;
	}

	public void Click(int characterID, short keys, int x, int y)
	{
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
	}

	public void RequestStart(int requestID)
	{
	}

	public void RequestComplete(int requestID, int status)
	{
		if (requestID == m_DoneID[0])
		{
			m_Applet.HideCharacters();
		}
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
	}
	
	public void AgentPropertyChange()
	{
	}
	
	public void ActiveClientChange(int characterID, int status)
	{
	}
}
