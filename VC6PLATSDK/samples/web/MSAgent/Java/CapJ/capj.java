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
// CapJ is the WFC Java version of the Character Animation Previewer sample.
// It demonstrates loading characters, playing animations, speaking, moving,
// etc.
//
//==========================================================================

import com.ms.wfc.app.*;
import com.ms.wfc.core.*;
import com.ms.wfc.ui.*;
import com.ms.wfc.io.*;
import com.ms.fx.*;

// We want access to 2 native APIs so we'll add the
// import directive here so that we don't have to do
// it for each API. Note the use of the auto parameter.
// This tells J/Direct to use the UNICODE APIs on NT and
// ANSI everywhere else.

/** @dll.import("USER32", auto) */
public class CapJ extends Form
{
	// Native APIs
	
	private static native int GetForegroundWindow();
	private static native int GetWindowText(int hWnd, StringBuffer text, int nMaxCount);
	
	// Class globals
	
	private agentctl.IAgentCtlCharacterEx m_pCharacter = null;
	
	// Constants
	
	private final String kpszRecentFilesSubkey = "Software\\Microsoft\\Microsoft Agent\\Tools\\Character Previewer\\Recent Files";
	private final String kpszRecentFilesItem = "File";
	
	private final String kpszCharacterWindowTitle = "Microsoft Agent";
	private final String kpszOptionsWindowTitle = "Advanced Character Options";
	
	private final int MAX_RECENT_FILES = 4;
	private final int MAX_RECENT_FILENAME = 32;
	
	// Constants from AgtSvr.h
	
	private final int UserHid = 0;
	private final int UserHidViaCharacterMenu = 7;
	
	// Constructor
	
	public CapJ()
	{
		super();

		initForm();	
		
		// Ensure that we're connected to Microsoft Agent
		
		agent1.setConnected(true);
		
		// Update the recent file list in the File menu
		
		UpdateRecentFiles(null);		
	}

	public void dispose()
	{
		super.dispose();
		components.dispose();
	}

	private void LoadCharacter(String path) 
	{			
		com.ms.com.IEnumVariant enum = null;
		com.ms.com.Variant vName[] = {null};
		int iRetrieved[] = {-1};
		int iBalloonStyle;
		boolean bHasAnims;
		
		com.ms.com.Variant vPath = new com.ms.com.Variant();
		com.ms.com.Variant vFast = new com.ms.com.Variant();

		// Was a path specified
		
		if (path == "") 
		{
			// Nope. Create a file dialog object.
			
			OpenFileDialog fOpenDlg = new OpenFileDialog();
			
			fOpenDlg.setFilter("Agent Character Files (*.acs)|*.acs|Agent Character Files (*.acf)|*.acf|All files (*.*)|*.*");
			fOpenDlg.setCheckFileExists(true);
			fOpenDlg.setCheckPathExists(true);
			
			// Show it
			
			if (fOpenDlg.showDialog() == DialogResult.OK)
				vPath.putString(fOpenDlg.getFileName());
			else
				return;
		}
		else
		{
			vPath.putString(path);
		}
		
		// If we already have a character loaded, unload it and
		// clear the animation name list box.
		
		if (m_pCharacter != null) 
		{
			agent1.getCharacters().Unload("characterID");
			m_pCharacter = null;
			this.AnimationsListBox.removeAll();
		}
						
		// Load the character
		
		try 
		{					
			agent1.getCharacters().Load("characterID",vPath);			
		}
		catch (com.ms.com.ComFailException e)
		{
			return;
		}
		
		// Save the character interface/object
		
		m_pCharacter = agent1.getCharacters().Character("characterID");

		// Move the character to the right of the window
		
		Rectangle rcWindow = new Rectangle(this.getLocation().x,
										   this.getLocation().y,
										   this.getSize().x,
										   this.getSize().y);			

		// Make sure we'll fit to the right (NOTE: a production
		// quality app would handle multi-monitor!!!)
		
		int charLeft;
		
		charLeft = rcWindow.getRight();
		
		if ((charLeft + m_pCharacter.getWidth()) > FxToolkit.getSystemMetric(FxToolkit.SCREEN_WIDTH))
			charLeft = rcWindow.x - m_pCharacter.getWidth();

		// Position the character
		
		m_pCharacter.MoveTo((short)charLeft, (short)rcWindow.y, new com.ms.com.Variant(0));
		
		// And show it
		
		m_pCharacter.Show(vFast);
		
		// Enumerate the character's animation names
		
		enum = (com.ms.com.IEnumVariant)m_pCharacter.getAnimationNames().getEnum();

		while (true) {
			enum.Next(1, vName, iRetrieved);
			if (iRetrieved[0] != 1)
				break;
			this.AnimationsListBox.addItem(vName[0].getString());
		}
		
		// Initialize the animation list box label with the character's
		// name.
		
		AnimationsLabel.setText("Animations for " + m_pCharacter.getName());
		
		// Initialize controls
		
		UseSfx.setChecked(m_pCharacter.getSoundEffectsOn());
		
		bHasAnims = AnimationsListBox.getItemCount() > 0;
	
		if (bHasAnims)
			AnimationsListBox.setSelectedIndex(0);
		
		AnimationsLabel.setEnabled(bHasAnims);
		AnimationsListBox.setEnabled(bHasAnims);
		UseSfx.setEnabled(bHasAnims && agent1.getAudioOutput().getSoundEffects());
		StopBeforePlay.setEnabled(bHasAnims);
		PlayButton.setEnabled(bHasAnims);
		StopButton.setEnabled(bHasAnims);
		SpeechOutputLabel.setEnabled(bHasAnims);
		SpeakText.setEnabled(bHasAnims);
		SpeakButton.setEnabled(bHasAnims);
		
		PositionLabel.setEnabled(bHasAnims);
		XLabel.setEnabled(bHasAnims);
		X.setEnabled(bHasAnims);
		YLabel.setEnabled(bHasAnims);
		Y.setEnabled(bHasAnims);
		Move.setEnabled(bHasAnims);
		
		iBalloonStyle = m_pCharacter.getBalloon().getStyle();
		
		UseBalloon.setChecked((iBalloonStyle & 1) == 1);
		SizeToText.setChecked((iBalloonStyle & 2) == 2);
		AutoHide.setChecked((iBalloonStyle & 4) == 4);
		AutoPace.setChecked((iBalloonStyle & 8) == 8);
		
		UseBalloon.setEnabled(bHasAnims);
		AutoHide.setEnabled(bHasAnims && UseBalloon.getChecked());
		AutoPace.setEnabled(bHasAnims && UseBalloon.getChecked());
		SizeToText.setEnabled(bHasAnims && UseBalloon.getChecked());
		
		// Add commands
				
		m_pCharacter.getCommands().Add("PropSheet",
									   new com.ms.com.Variant("&Advanced Character Properties"),
									   new com.ms.com.Variant(),
									   new com.ms.com.Variant(),
									   new com.ms.com.Variant());

		// Add the loaded character to the recent file list

		UpdateRecentFiles(vPath.getString());
	}		

	private String MakeEllipsisPath(String pszPath, int iMaxLength) 
	{
		// This function takes a full path and truncates to a fixed
		// specified size using ellipses as necessary.

		int iPathPartLen;
		int iEndDir;
		int i;
		String pszFilename;
		
		// If the specified path fits, then just copy it and return

		if (pszPath.length() <= iMaxLength)
			return new String(pszPath);
	
		// See if the filename alone is too big

		i = pszPath.lastIndexOf("\\");
		
		if (i >= 0)
			pszFilename = pszPath.substring(i+1, pszPath.length());
		else
			pszFilename = new String(pszPath);
		
		if (pszFilename.length() >= iMaxLength)
			return pszFilename.substring(0, iMaxLength-3) + "...";

		// Make a copy
		
		String pszPathCopy = new String(pszPath);
		
		if (pszPathCopy.startsWith("\\\\"))
			iEndDir = 3;
		else
			iEndDir = pszPathCopy.indexOf('\\') + 1;
		
		iEndDir = pszPathCopy.indexOf('\\', iEndDir);
		
		// If we couldn't find the first directory component, give up
		// and just return the filename only.

		if (iEndDir < 0)
			return pszFilename;
		else
			iEndDir++;
				
		if (iEndDir < (iMaxLength - pszFilename.length() - 4))
			iPathPartLen = iEndDir;
		else
			iPathPartLen = iMaxLength - pszFilename.length() - 4;
		
		return new String(pszPathCopy.substring(0, iPathPartLen) + "...\\" + pszFilename);
	}
	
	private void UpdateRecentFiles(String pszFilename) 
	{	
		Registry reg;
		RegistryKey rk;
		
		int iNumExisting = 0;
		int iFind = -1;
		int iCount;
		String pszEllipsis;
		String[] rgpszRecentFiles = new String[MAX_RECENT_FILES];
		
		// Create/Open the recent files registry subkey
		
		reg = new Registry();
		
		rk = reg.CURRENT_USER.createSubKey(kpszRecentFilesSubkey);

		for (int i=1; i <= MAX_RECENT_FILES; i++) 
		{			
			// Get the registry value of the form "File<#>"
			
			Integer i2 = new Integer(i);
			
			rgpszRecentFiles[i-1] = (String)rk.getValue(kpszRecentFilesItem + i2.toString());
			
			// Did we find a value
			
			if (rgpszRecentFiles[i-1] != null) 
			{				
				// If a filename was specified, see if it matches this one

				if (pszFilename != null) 
				{
					if (pszFilename.equals(rgpszRecentFiles[iNumExisting])) 
					{
						// If the specified file is the first file we find,
						// then we're done.

						if (iNumExisting == 0) 
						{
							rk.close();
							return;
						}

						iFind = iNumExisting;
					}
				}
				
				++iNumExisting;
			}
		}
		
		// If no filename was specified, and we don't have any
		// existing files, we're done.

		if ((pszFilename == null) && (iNumExisting == 0))
		{
			recentSeparator.setVisible(false);
			return;
		}

		// If a file was specified, we have to update the registry

		if (pszFilename != null) 
		{
			// Write the new filename to the registry

			rk.setValue(kpszRecentFilesItem + "1", pszFilename);

			// If we previously had the maximum number of files, and
			// the new one is not one of them, we disregard the last
			// one.

			if ((iNumExisting == MAX_RECENT_FILES) && (iFind < 0))
				--iNumExisting;

			// Now, write the remaining items

			iCount = 1;

			for (int i=0; i < iNumExisting; i++) 
			{
				if (i != iFind) 
				{
					Integer i2 = new Integer(++iCount);
					rk.setValue(kpszRecentFilesItem + i2.toString(), rgpszRecentFiles[i]);
				}
			}
		}		

		// Set the recent file menu items to be non-visible

		recent1.setVisible(false);
		recent2.setVisible(false);
		recent3.setVisible(false);
		recent4.setVisible(false);
		
		// Create an ellipsis path from the specified filename and
		// insert it into the menu.

		if (pszFilename != null) 
		{
			pszEllipsis = MakeEllipsisPath(pszFilename, MAX_RECENT_FILENAME);
			String pszMenuItemText = new String("&1 " + pszEllipsis);
			recent1.setText(pszMenuItemText);
			recent1.setVisible(true);
			iCount = 1;
		}
		else 
		{
			iCount = 0;
		}
		
		// Then do the same for the remaining items

		for (int i=0; i < iNumExisting; i++) 
		{
			if (i != iFind) 
			{
				Integer i2 = new Integer(iCount+1);

				pszEllipsis = MakeEllipsisPath(rgpszRecentFiles[i], MAX_RECENT_FILENAME);

				String pszMenuItemText = new String("&" + i2.toString() + " " + pszEllipsis);

				if (iCount == 0) 
				{
					recent1.setText(pszMenuItemText);
					recent1.setVisible(true);
				}
				else if (iCount == 1) 
				{
					recent2.setText(pszMenuItemText);
					recent2.setVisible(true);
				}
				else if (iCount == 2) 
				{
					recent3.setText(pszMenuItemText);
					recent3.setVisible(true);
				}
				else if (iCount == 3) 
				{
					recent4.setText(pszMenuItemText);
					recent4.setVisible(true);
				}
						 
				++iCount;
			}
		}
		
		// Show/Hide the separator as appropriate

		if ((iNumExisting == 0) && (pszFilename == null))
			recentSeparator.setVisible(false);
		else
			recentSeparator.setVisible(true);

		rk.close();
	}
	
	private void OnRecentFile(int iFile) 
	{	
		Registry reg = new Registry();
		RegistryKey rk;
		Integer i = new Integer(iFile);
	
		// Open the registry subkey
		
		rk = reg.CURRENT_USER.createSubKey(kpszRecentFilesSubkey);
		
		// Try to find a value name of "File<iFile>"
		
		String pszFilename = (String)rk.getValue(kpszRecentFilesItem + i.toString());
		
		// Did we find it?
		
		if (pszFilename == null)
			return;
		
		// Load the character
		
		LoadCharacter(pszFilename);
	}
	
	public void exitMenu_click(Object sender, Event e)
	{
		// Unload the character (if necessary)
		
		if (m_pCharacter != null) {
			m_pCharacter = null;
			agent1.getCharacters().Unload("characterID");
		}

		Application.exit();
	}

	private void aboutMenu_click(Object sender, Event e)
	{
		About myAbout = new About();				
		myAbout.showDialog();
	}

	private void openMenu_click(Object source, Event e)
	{
		LoadCharacter("");
	}

	private void recent1_click(Object source, Event e)
	{
		OnRecentFile(1);
	}

	private void recent2_click(Object source, Event e)
	{
		OnRecentFile(2);
	}

	private void recent3_click(Object source, Event e)
	{
		OnRecentFile(3);
	}

	private void recent4_click(Object source, Event e)
	{
		OnRecentFile(4);
	}

	private void OnListDblClick(Object sender, Event e) 
	{	
		PlayButton_click(sender, e);
	}
		
	private void PlayButton_click(Object sender, Event e)
	{
		String curAnim = new String("");
		
		if (m_pCharacter == null)
			return;
		
		curAnim = (String)this.AnimationsListBox.getSelectedItem();
		
		if (curAnim != "") 
		{			
			if (this.StopBeforePlay.getChecked())
				m_pCharacter.StopAll(new com.ms.com.Variant());
			
			m_pCharacter.Play(curAnim);
		}
	}

	private void StopButton_click(Object source, Event e)
	{
		if (m_pCharacter != null)
			m_pCharacter.StopAll(new com.ms.com.Variant());		
	}

	private void SpeakButton_click(Object source, Event e)
	{
		int iStyle;
		
		if (m_pCharacter == null)
			return;

		iStyle = 0;
		
		if (UseBalloon.getChecked())
			iStyle |= 1;
		
		if (SizeToText.getChecked())
			iStyle |= 2;
		
		if (AutoHide.getChecked())
			iStyle |= 4;
		
		if (AutoPace.getChecked())
			iStyle |= 8;

		m_pCharacter.getBalloon().setStyle(iStyle);
		
		if (SpeakText.getText().length() != 0)
			m_pCharacter.Speak(new com.ms.com.Variant(SpeakText.getText()), new com.ms.com.Variant());
	}

	private void Move_click(Object source, Event e)
	{
		Short x;
		Short y;
		
		if (m_pCharacter == null)
			return;
		
		if ((X.getText().length() == 0) || (Y.getText().length() == 0))
			return;

		try 
		{
			x = new Short(X.getText());
		}
		catch (NumberFormatException exc) 
		{
			X.setSelectionStart(0);
			X.setSelectionEnd(-1);
			return;
		}
		
		try 
		{
			y = new Short(Y.getText());
		}
		catch (NumberFormatException exc) 
		{
			Y.selectAll();
			return;
		}
				
		if (this.StopBeforePlay.getChecked())
			m_pCharacter.StopAll(new com.ms.com.Variant());
			
		m_pCharacter.MoveTo(x.shortValue(), y.shortValue(), new com.ms.com.Variant());
	}

	private void UseSfx_click(Object source, Event e)
	{
		if (m_pCharacter == null)
			return;
		
		m_pCharacter.setSoundEffectsOn(UseSfx.getChecked());
	}

	private void UseBalloon_click(Object source, Event e)
	{
		boolean bUseBalloon;
		
		bUseBalloon = UseBalloon.getChecked();
		
		AutoHide.setEnabled(bUseBalloon);
		AutoPace.setEnabled(bUseBalloon);
		SizeToText.setEnabled(bUseBalloon);
	}

	private void agent1_command(Object sender, agentctl.Agent.CommandEvent e)
	{
		// The user selected a command from the popup menu.
		
		agentctl.IAgentCtlUserInput ui = (agentctl.IAgentCtlUserInput)(e.UserInput);
		
		if (ui.getName().equals("PropSheet")) 
		{			
			agentctl.IAgentCtlPropertySheet ps = agent1.getPropertySheet();
			short sX = (short)(ps.getLeft() + ps.getWidth()/2);
			short sY = (short)(ps.getTop() + ps.getHeight()/2);
		
			// Stop the character
			
			m_pCharacter.StopAll(new com.ms.com.Variant());			
			
			// Gesture at the center of the property sheet
			
			m_pCharacter.GestureAt(sX, sY);
			
			// And show the property sheet
			
			ps.setVisible(true);
		}
	}

	private void agent1_move(Object sender, agentctl.Agent.MoveEvent e)
	{
		// The character moved. Resync our window to the
		// new position.
		
		Short sX = new Short(e.x);
		Short sY = new Short(e.y);		
		X.setText(sX.toString());
		Y.setText(sY.toString());
	}

	private void agent1_agentPropertyChange(Object sender, Event e)
	{
		// When an Agent property changes (via the Advanced Character
		// Options property sheet), we need to resync our window with
		// the current state of Agent's properties.
		
		UseSfx.setEnabled(agent1.getAudioOutput().getSoundEffects() &&
						  AnimationsListBox.getItemCount() > 0);
		
		boolean bEnable = m_pCharacter.getBalloon().getEnabled();
		
		UseBalloon.setEnabled(bEnable);
		
		bEnable = bEnable && UseBalloon.getChecked();
		
		SizeToText.setEnabled(bEnable);
		AutoHide.setEnabled(bEnable);
		AutoPace.setEnabled(bEnable);
	}


	private void CapJ_closing(Object source, CancelEvent e)
	{
		// Unload the character (if necessary)
		
		if (m_pCharacter != null) {
			m_pCharacter = null;
			agent1.getCharacters().Unload("characterID");
		}
	}

	private void AnimationsListBox_doubleClick(Object source, Event e)
	{
		PlayButton_click(source, e);
	}

	private void CapJ_activate(Object source, Event e)
	{	
		// Is a character currently loaded?
		
		if (m_pCharacter != null)
		{
			// We never want to show the character if the window
			// is minimized (i.e. state == 1).

			if (getWindowState() != 1)
			{
				// We want to show the character on activation but there's
				// a special case. If the user hid the character we could get
				// an activate message after the character window hides.
				// In that case, we sure don't want to show the character. So
				// check the visibility cause of the character. If the user hid
				// it, we won't show it.

				if ((m_pCharacter.getVisibilityCause() == UserHid) ||
					(m_pCharacter.getVisibilityCause() == UserHidViaCharacterMenu))
					return;

				m_pCharacter.Show(new com.ms.com.Variant(true));
			}
		}
	}

	private void CapJ_deactivate(Object source, Event e)
	{
		// When the window is deactivated, we'll hide the character
		// (non-animated). This code also demonstrates the use of
		// J/Direct.
		
		// Is a character currently loaded?
		
		if (m_pCharacter != null)
		{
			// Use J/Direct to get the foreground window
			
			int hWnd = GetForegroundWindow();
			
			// Create a StringBuffer to get the window title
			// of the foreground window.
			
			StringBuffer title = new StringBuffer(256);
			
			// Get the title of the foreground window using
			// J/Direct.
			
			if (GetWindowText(hWnd, title, 256) > 0)
			{				
				// We don't want to hide the character if it is the
				// foreground window.
				
				if (title.toString().equalsIgnoreCase(kpszCharacterWindowTitle))
					return;

				// Check to see if it's the Agent Character Property
				// Sheet. NOTE: this currently only works on English
				// systems. A more robust way to do this would be to
				// use the process id of the window that is getting
				// focus, and make sure that it's not AgentSvr.exe.

				if (title.toString().equalsIgnoreCase(kpszOptionsWindowTitle))
					return;
			}
			
			// Hide the character (no animation)
			
			m_pCharacter.Hide(new com.ms.com.Variant(true));
		}
	}

	Container components = new Container();
	MainMenu mainMenu1 = new MainMenu();
	MenuItem openMenu = new MenuItem();
	GroupBox AnimationsLabel = new GroupBox();
	MenuItem recentSeparator = new MenuItem();
	ListBox AnimationsListBox = new ListBox();
	MenuItem aboutMenu = new MenuItem();
	MenuItem fileMenu = new MenuItem();
	CheckBox AutoHide = new CheckBox();
	Button PlayButton = new Button();
	Button StopButton = new Button();
	CheckBox UseSfx = new CheckBox();
	CheckBox StopBeforePlay = new CheckBox();
	GroupBox SpeechOutputLabel = new GroupBox();
	Edit SpeakText = new Edit();
	CheckBox UseBalloon = new CheckBox();
	MenuItem exitMenu = new MenuItem();
	MenuItem helpMenu = new MenuItem();
	agentctl.Agent.Agent agent1 = new agentctl.Agent.Agent();
	CheckBox AutoPace = new CheckBox();
	CheckBox SizeToText = new CheckBox();
	Button SpeakButton = new Button();
	GroupBox PositionLabel = new GroupBox();
	Label XLabel = new Label();
	Edit X = new Edit();
	Label YLabel = new Label();
	Edit Y = new Edit();
	Button Move = new Button();
	MenuItem menuItem1 = new MenuItem();
	MenuItem recent2 = new MenuItem();
	MenuItem recent3 = new MenuItem();
	MenuItem recent4 = new MenuItem();
	MenuItem recent1 = new MenuItem();

	private void initForm()
	{
		// NOTE:  This form is storing resource information in an
		// external file.  Do not modify the string parameter to any
		// resources.getObject() function call. For example, do not
		// modify "foo1_location" in the following line of code
		// even if the name of the Foo object changes: 
		//   foo1.setLocation((Point)resources.getObject("foo1_location"));

		IResourceManager resources = new ResourceManager(this, "CapJ");
		components.add(openMenu, "openMenu");
		openMenu.setShortcut(Shortcut.CTRL_O);
		openMenu.setText("&Open...");
		openMenu.addOnClick(new EventHandler(this.openMenu_click));

		components.add(AnimationsLabel, "AnimationsLabel");
		AnimationsLabel.setEnabled(false);
		AnimationsLabel.setLocation(new Point(8, 8));
		AnimationsLabel.setSize(new Point(280, 168));
		AnimationsLabel.setTabIndex(2);
		AnimationsLabel.setTabStop(false);
		AnimationsLabel.setText("&Animations");

		components.add(recentSeparator, "recentSeparator");
		recentSeparator.setText("-");

		components.add(AnimationsListBox, "AnimationsListBox");
		AnimationsListBox.setEnabled(false);
		AnimationsListBox.setLocation(new Point(16, 24));
		AnimationsListBox.setSize(new Point(264, 108));
		AnimationsListBox.setTabIndex(1);
		AnimationsListBox.setText("listBox1");
		AnimationsListBox.setSorted(true);
		AnimationsListBox.setUseTabStops(true);
		AnimationsListBox.addOnDoubleClick(new EventHandler(this.AnimationsListBox_doubleClick));

		components.add(aboutMenu, "aboutMenu");
		aboutMenu.setText("&About Microsoft Character Animation Previewer");
		aboutMenu.addOnClick(new EventHandler(this.aboutMenu_click));

		components.add(AutoHide, "AutoHide");
		AutoHide.setEnabled(false);
		AutoHide.setLocation(new Point(32, 112));
		AutoHide.setSize(new Point(64, 16));
		AutoHide.setTabIndex(2);
		AutoHide.setText("Auto hi&de");

		components.add(PlayButton, "PlayButton");
		PlayButton.setEnabled(false);
		PlayButton.setLocation(new Point(304, 24));
		PlayButton.setSize(new Point(96, 24));
		PlayButton.setTabIndex(3);
		PlayButton.setText("&Play");
		PlayButton.addOnClick(new EventHandler(this.PlayButton_click));

		components.add(StopButton, "StopButton");
		StopButton.setEnabled(false);
		StopButton.setLocation(new Point(304, 64));
		StopButton.setSize(new Point(96, 24));
		StopButton.setTabIndex(4);
		StopButton.setText("S&top");
		StopButton.addOnClick(new EventHandler(this.StopButton_click));

		components.add(UseSfx, "UseSfx");
		UseSfx.setEnabled(false);
		UseSfx.setLocation(new Point(8, 136));
		UseSfx.setSize(new Point(112, 16));
		UseSfx.setTabIndex(0);
		UseSfx.setText("Play sound &effects");
		UseSfx.addOnClick(new EventHandler(this.UseSfx_click));

		components.add(StopBeforePlay, "StopBeforePlay");
		StopBeforePlay.setEnabled(false);
		StopBeforePlay.setLocation(new Point(136, 136));
		StopBeforePlay.setSize(new Point(128, 16));
		StopBeforePlay.setTabIndex(1);
		StopBeforePlay.setText("Stop &before next action");

		components.add(SpeechOutputLabel, "SpeechOutputLabel");
		SpeechOutputLabel.setEnabled(false);
		SpeechOutputLabel.setLocation(new Point(8, 184));
		SpeechOutputLabel.setSize(new Point(280, 144));
		SpeechOutputLabel.setTabIndex(5);
		SpeechOutputLabel.setTabStop(false);
		SpeechOutputLabel.setText("Speech &Output");

		components.add(SpeakText, "SpeakText");
		SpeakText.setEnabled(false);
		SpeakText.setLocation(new Point(8, 16));
		SpeakText.setSize(new Point(264, 64));
		SpeakText.setTabIndex(0);
		SpeakText.setText("");
		SpeakText.setMultiline(true);
		SpeakText.setScrollBars(ScrollBars.VERTICAL);

		components.add(UseBalloon, "UseBalloon");
		UseBalloon.setEnabled(false);
		UseBalloon.setLocation(new Point(8, 88));
		UseBalloon.setSize(new Point(120, 16));
		UseBalloon.setTabIndex(1);
		UseBalloon.setText("Display &word balloon");
		UseBalloon.addOnClick(new EventHandler(this.UseBalloon_click));

		components.add(exitMenu, "exitMenu");
		exitMenu.setText("E&xit");
		exitMenu.addOnClick(new EventHandler(this.exitMenu_click));

		components.add(helpMenu, "helpMenu");
		helpMenu.setMenuItems(new MenuItem[] {
							  aboutMenu});
		helpMenu.setText("&Help");

		components.add(agent1, "agent1");
		agent1.setLocation(new Point(368, 96));
		agent1.setSize(new Point(32, 32));
		agent1.setTabIndex(0);
		agent1.setOcxState((AxHost.State)resources.getObject("agent1_ocxState"));
		agent1.addOnCommand(new agentctl.Agent.CommandHandler(this.agent1_command));
		agent1.addOnMove(new agentctl.Agent.MoveHandler(this.agent1_move));
		agent1.addOnAgentPropertyChange(new EventHandler(this.agent1_agentPropertyChange));

		components.add(AutoPace, "AutoPace");
		AutoPace.setEnabled(false);
		AutoPace.setLocation(new Point(112, 112));
		AutoPace.setSize(new Point(72, 16));
		AutoPace.setTabIndex(3);
		AutoPace.setText("Auto pa&ce");

		components.add(SizeToText, "SizeToText");
		SizeToText.setEnabled(false);
		SizeToText.setLocation(new Point(192, 112));
		SizeToText.setSize(new Point(72, 16));
		SizeToText.setTabIndex(4);
		SizeToText.setText("Si&ze to text");

		components.add(SpeakButton, "SpeakButton");
		SpeakButton.setEnabled(false);
		SpeakButton.setLocation(new Point(304, 200));
		SpeakButton.setSize(new Point(96, 24));
		SpeakButton.setTabIndex(6);
		SpeakButton.setText("&Speak");
		SpeakButton.addOnClick(new EventHandler(this.SpeakButton_click));

		components.add(PositionLabel, "PositionLabel");
		PositionLabel.setEnabled(false);
		PositionLabel.setLocation(new Point(8, 336));
		PositionLabel.setSize(new Point(280, 56));
		PositionLabel.setTabIndex(7);
		PositionLabel.setTabStop(false);
		PositionLabel.setText("Position");

		components.add(XLabel, "XLabel");
		XLabel.setEnabled(false);
		XLabel.setLocation(new Point(16, 24));
		XLabel.setSize(new Point(16, 16));
		XLabel.setTabIndex(0);
		XLabel.setTabStop(false);
		XLabel.setText("&X:");

		components.add(X, "X");
		X.setEnabled(false);
		X.setLocation(new Point(32, 24));
		X.setSize(new Point(40, 20));
		X.setTabIndex(1);
		X.setText("");

		components.add(YLabel, "YLabel");
		YLabel.setEnabled(false);
		YLabel.setLocation(new Point(112, 24));
		YLabel.setSize(new Point(16, 16));
		YLabel.setTabIndex(2);
		YLabel.setTabStop(false);
		YLabel.setText("&Y:");

		components.add(Y, "Y");
		Y.setEnabled(false);
		Y.setLocation(new Point(136, 24));
		Y.setSize(new Point(40, 20));
		Y.setTabIndex(3);
		Y.setText("");

		components.add(Move, "Move");
		Move.setEnabled(false);
		Move.setLocation(new Point(304, 360));
		Move.setSize(new Point(96, 24));
		Move.setTabIndex(9);
		Move.setText("&Move");
		Move.addOnClick(new EventHandler(this.Move_click));

		components.add(menuItem1, "menuItem1");
		menuItem1.setText("-");

		components.add(recent2, "recent2");
		recent2.setText("");
		recent2.setVisible(false);
		recent2.addOnClick(new EventHandler(this.recent2_click));

		components.add(recent3, "recent3");
		recent3.setText("");
		recent3.setVisible(false);
		recent3.addOnClick(new EventHandler(this.recent3_click));

		components.add(recent4, "recent4");
		recent4.setText("");
		recent4.setVisible(false);
		recent4.addOnClick(new EventHandler(this.recent4_click));

		components.add(recent1, "recent1");
		recent1.setText("");
		recent1.setVisible(false);
		recent1.addOnClick(new EventHandler(this.recent1_click));

		components.add(fileMenu, "fileMenu");
		fileMenu.setMenuItems(new MenuItem[] {
							  openMenu, 
							  recentSeparator, 
							  recent1, 
							  recent2, 
							  recent3, 
							  recent4, 
							  menuItem1, 
							  exitMenu});
		fileMenu.setText("&File");

		components.add(mainMenu1, "mainMenu1");
		mainMenu1.setMenuItems(new MenuItem[] {
							   fileMenu, 
							   helpMenu});
		/* @designTimeOnly mainMenu1.setLocation(new Point(320, 136)); */

		this.setAllowDrop(true);
		this.setAnchor(ControlAnchor.ALL);
		this.setLocation(new Point(298, 88));
		this.setText("Microsoft Character Animation Previewer");
		this.setAutoScaleBaseSize(new Point(5, 13));
		this.setClientSize(new Point(414, 403));
		this.setIcon((Icon)resources.getObject("this_icon"));
		this.setMaximizeBox(false);
		this.setMenu(mainMenu1);
		this.setStartPosition(FormStartPosition.CENTER_SCREEN);
		this.addOnActivate(new EventHandler(this.CapJ_activate));
		this.addOnDeactivate(new EventHandler(this.CapJ_deactivate));
		this.addOnClosing(new CancelEventHandler(this.CapJ_closing));

		this.setNewControls(new Control[] {
							Move, 
							PositionLabel, 
							SpeakButton, 
							SpeechOutputLabel, 
							StopButton, 
							PlayButton, 
							AnimationsListBox, 
							agent1, 
							AnimationsLabel});
		AnimationsLabel.setNewControls(new Control[] {
									   StopBeforePlay, 
									   UseSfx});
		SpeechOutputLabel.setNewControls(new Control[] {
										 SizeToText, 
										 AutoPace, 
										 AutoHide, 
										 UseBalloon, 
										 SpeakText});
		PositionLabel.setNewControls(new Control[] {
									 Y, 
									 YLabel, 
									 X, 
									 XLabel});

		agent1.begin();
	}

	public static void main(String args[])
	{
		Application.run(new CapJ());
	}
}
