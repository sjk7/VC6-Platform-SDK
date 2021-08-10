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

import com.ms.wfc.app.*;
import com.ms.wfc.core.*;
import com.ms.wfc.ui.*;

public class About extends Form
{
	private void okButton_click(Object sender, Event e)
	{
		this.setDialogResult(DialogResult.OK);
	}

	public About()
	{
		super();

		initForm();		
	}

	public void dispose()
	{
		super.dispose();
		components.dispose();
	}

	Container components = new Container();
	Button okButton = new Button();
	Label titleLabel = new Label();
	Label versionLabel = new Label();
	Label nameLabel = new Label();

	private void initForm()
	{
		okButton.setLocation(new Point(224, 16));
		okButton.setSize(new Point(84, 23));
		okButton.setTabIndex(0);
		okButton.setText("OK");
		okButton.addOnClick(new EventHandler(this.okButton_click));

		this.setText("About Microsoft Character Animation Previewer");
		this.setAcceptButton(okButton);
		this.setAutoScaleBaseSize(new Point(5, 13));
		this.setBorderStyle(FormBorderStyle.FIXED_TOOLWINDOW);
		this.setCancelButton(okButton);
		this.setClientSize(new Point(324, 85));
		this.setMaximizeBox(false);
		this.setMinimizeBox(false);
		this.setStartPosition(FormStartPosition.CENTER_SCREEN);

		titleLabel.setLocation(new Point(10, 10));
		titleLabel.setSize(new Point(192, 16));
		titleLabel.setTabIndex(1);
		titleLabel.setTabStop(false);
		titleLabel.setText("Microsoft Character Animation Previewer");

		versionLabel.setLocation(new Point(8, 56));
		versionLabel.setSize(new Point(64, 16));
		versionLabel.setTabIndex(2);
		versionLabel.setTabStop(false);
		versionLabel.setText("Version 1.00");

		nameLabel.setLocation(new Point(8, 32));
		nameLabel.setSize(new Point(192, 16));
		nameLabel.setTabIndex(3);
		nameLabel.setTabStop(false);
		nameLabel.setText("Copyright (C) 1998 Microsoft Corporation");

		this.setNewControls(new Control[] {
							nameLabel, 
							versionLabel, 
							titleLabel, 
							okButton});
	}

	public static void main(String args[])
	{
		Application.run(new About());
	}
}
