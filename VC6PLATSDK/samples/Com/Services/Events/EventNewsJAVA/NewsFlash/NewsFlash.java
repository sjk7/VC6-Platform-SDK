import com.ms.wfc.app.*;
import com.ms.wfc.core.*;
import com.ms.wfc.ui.*;
import com.ms.wfc.html.*;
import com.ms.com.Variant;

/**
 * This class can take a variable number of parameters on the command
 * line. Program execution begins with the main() method. The class
 * constructor is not invoked unless an object of type 'Form1' is
 * created in the main() method.
 */
public class NewsFlash extends Form
{
	comadmin.ICOMAdminCatalog	admin	=	null;
	
	public NewsFlash()
	{
		// Required for Visual J++ Form Designer support
		initForm();		
		ecDllNameFT.setText(helper.sampleConstants.NEW_EVENT_DLL);
		initAdminCatlog();
	}

	/**
	 * NewsFlash overrides dispose so it can clean up the
	 * component list.
	 */
	public void dispose()
	{
		super.dispose();
		components.dispose();
	}
	/**
     * Publish the event.
     *
     * @param       ---
     * @return      ---
     * @see			Queuing, Monikers, com.ms.win32.Ole32.CoGetObject
     **/
	private void publishButton_click(Object source, Event e)
	{
		String							monikerString	=	null;
		newseventclass.INewsEvent		traderObj		=	null;
				  
		monikerString	=	"new:" + helper.sampleConstants.EVENT_CLSID;
		if(queuedCB.getChecked())
		{
			monikerString = "queue:/" + monikerString;	// if Queuing is used
		}
		traderObj	=	(newseventclass.INewsEvent)(com.ms.win32.Ole32.CoGetObject(monikerString,null,newseventclass.INewsEvent.iid));
		traderObj.NewsFlash((double)(System.currentTimeMillis()),symbolTF.getText(),headlineTF.getText(),urlTF.getText()); // Fire a event
	}

	/**
     * Install event class.
     *
     * @param       ---
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog
     **/
	private void installEventButton_click(Object source, Event e)
	{
		if((installEventButton.getText()).equals("Install"))
		{
			String ecName = ecDllNameFT.getText();
			//Install Event Class.
			admin.InstallEventClass(helper.sampleConstants.PUBLISHER_NAME,ecDllNameFT.getText(),"" , "");
			if(parallelCB.getChecked())
			{
				updateCollections(helper.sampleConstants.PARALLEL_FLAG); 
			}
			installEventButton.setText("Uninstall");
			
		}
		else //Uninstall the event class.
		{
			updateCollections(helper.sampleConstants.UNINSTALL_FLAG);
			installEventButton.setText("Install");
		}
	}
	/**
     * Update the different Collections in Admin catalog.
     *
     * @param       processFlag		The flag specify whether the object in the collection is required to be added or removed.
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog
     **/
	private void updateCollections(boolean processFlag)
	{
		comadmin.ICatalogCollection		appCollec	=	null;
		
		appCollec	=(comadmin.ICatalogCollection)(admin.GetCollection("Application")); //Get the application collection
		appCollec.Populate(); // 
		checkForApplication(appCollec,processFlag);
		
	}
	/**
     * Check for whether the given application name is present or not.
     *
     * @param       appCollec		Collection of Applications
     * @param		processFlag		The flag specify whether the object in the collection is required to be added or removed.
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog , ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	private void checkForApplication(comadmin.ICatalogCollection appCollec,boolean processFlag)
	{
		int								index		=	0;
		comadmin.ICatalogCollection		compCollec	=	null;
		
		for(index = 0; index < appCollec.getCount(); index++)
		{
			 // Checking for Publisher Application in the collection
			if(((((comadmin.ICatalogCollection)(appCollec.getItem(index))).getName()).toString()).equals(helper.sampleConstants.PUBLISHER_NAME))
			{
				// If the application is present get the collection of components in the application.
				compCollec	=(comadmin.ICatalogCollection)(appCollec.GetCollection("Components",((comadmin.ICatalogObject)(appCollec.getItem(index))).getKey())); 
				compCollec.Populate();
				checkForComponent(compCollec , processFlag);
				break;
			}
		}
	}
	
	/**
     * Check for whether the given component name is present or not in application.
     *
     * @param       compCollec		Collection of Components in Application
     * @param		processFlag		The flag specify whether the object in the collection is required to be added or removed.
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog, ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	private void checkForComponent(comadmin.ICatalogCollection compCollec, boolean processFlag)
	{
		int								index		=	0;
		comadmin.ICatalogObject			catalogObj	=	null;
		
		for(index = 0 ;index < compCollec.getCount(); index++)
		{
			 //Checking for Event component in the collection
			if(((((comadmin.ICatalogObject)(compCollec.getItem(index))).getName()).toString()).equals(helper.sampleConstants.EVENT_NAME))
			{
				//Checking if event is required to be fired in parallel
				if(processFlag == helper.sampleConstants.PARALLEL_FLAG)
				{
					catalogObj = (comadmin.ICatalogObject)(compCollec.getItem(index));
					catalogObj.setValue("FireInParallel",new Variant(true));
					compCollec.SaveChanges();
					installEventButton.setText("Uninstall");
				}
				else 
				{
					compCollec.Remove(index);
					compCollec.SaveChanges();
					installEventButton.setText("Install");
				}
				break;
			}
		}
	}
								   
	/**
     * Initialize the admin catalog
     *
     * @param       ---
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog, ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	private void initAdminCatlog()
	{
		comadmin.ICatalogCollection appCollec	=	null;
		comadmin.ICatalogObject		catalogObj	=	null;
			
		try
		{
			admin		=	(comadmin.ICOMAdminCatalog)new comadmin.COMAdminCatalog();
			appCollec	=	(comadmin.ICatalogCollection)(admin.GetCollection("Applications"));
			// Checking if application already present.
			checkForAppAlreadyInstalled(appCollec);
			//Setting the catalog properties
			catalogObj	=	(comadmin.ICatalogObject)(appCollec.Add());
			catalogObj.setValue("Name" , new Variant(helper.sampleConstants.PUBLISHER_NAME));
			catalogObj.setValue("Activation" , new Variant(1));
			//catalogObj.setValue("QueuingEnabled" ,new  Variant(1));
			//catalogObj.setValue("QueueListenerEnabled",new Variant(1));
			catalogObj.setValue("Authentication", new Variant(1));
			appCollec.SaveChanges();
		}
		catch(com.ms.com.ComException exp)
		{
			int hr = exp.getHResult();
			System.out.println(exp);
		}
								   
		
	}
	/**
     * Check if application is already present.
     *
     * @param       appCollec		Collection of  Applications.
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog, ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	private void checkForAppAlreadyInstalled(comadmin.ICatalogCollection appCollec)
	{
		
		int			index		=	0;
		
		appCollec.Populate();
		for(index = 0; index < appCollec.getCount(); index++)
		{
			Variant v = (((comadmin.ICatalogObject)(appCollec.getItem(index))).getName());
			if((v.toString()).equals(helper.sampleConstants.PUBLISHER_NAME))
			{
				// If application already present then remove the application from the catalog.
				appCollec.Remove(index);
				appCollec.SaveChanges();
				break;
			}
		}
		
	}

	/**
	 * NOTE: The following code is required by the Visual J++ form
	 * designer.  It can be modified using the form editor.  Do not
	 * modify it using the code editor.
	 */
	Container components = new Container();
	GroupBox PublishEventBorder = new GroupBox();
	GroupBox InstallEventBorder = new GroupBox();
	Button publishButton = new Button();
	Button installEventButton = new Button();
	Label symbolLabel = new Label();
	Label urlLabel = new Label();
	Label headlineLabel = new Label();
	Edit symbolTF = new Edit();
	Edit headlineTF = new Edit();
	CheckBox queuedCB = new CheckBox();
	Edit urlTF = new Edit();
	CheckBox parallelCB = new CheckBox();
	Label ecDllNameLabel = new Label();
	Edit ecDllNameFT = new Edit();

	private void initForm()
	{
		this.setText("NewsFlash");
		this.setAutoScaleBaseSize(new Point(5, 13));
		this.setClientSize(new Point(555, 430));

		PublishEventBorder.setLocation(new Point(24, 24));
		PublishEventBorder.setSize(new Point(408, 184));
		PublishEventBorder.setTabIndex(0);
		PublishEventBorder.setTabStop(false);
		PublishEventBorder.setText("Publish News Event");

		InstallEventBorder.setLocation(new Point(24, 224));
		InstallEventBorder.setSize(new Point(408, 176));
		InstallEventBorder.setTabIndex(1);
		InstallEventBorder.setTabStop(false);
		InstallEventBorder.setText("Instal Event");

		publishButton.setLocation(new Point(24, 32));
		publishButton.setSize(new Point(112, 32));
		publishButton.setTabIndex(0);
		publishButton.setText("Publish");
		publishButton.addOnClick(new EventHandler(this.publishButton_click));

		installEventButton.setLocation(new Point(24, 32));
		installEventButton.setSize(new Point(112, 32));
		installEventButton.setTabIndex(0);
		installEventButton.setText("Install");
		installEventButton.addOnClick(new EventHandler(this.installEventButton_click));

		symbolLabel.setLocation(new Point(152, 32));
		symbolLabel.setSize(new Point(80, 20));
		symbolLabel.setTabIndex(1);
		symbolLabel.setTabStop(false);
		symbolLabel.setText("Symbol");

		urlLabel.setLocation(new Point(152, 136));
		urlLabel.setSize(new Point(80, 20));
		urlLabel.setTabIndex(3);
		urlLabel.setTabStop(false);
		urlLabel.setText("URL");

		headlineLabel.setLocation(new Point(152, 88));
		headlineLabel.setSize(new Point(80, 20));
		headlineLabel.setTabIndex(2);
		headlineLabel.setTabStop(false);
		headlineLabel.setText("Headline");

		symbolTF.setLocation(new Point(256, 32));
		symbolTF.setSize(new Point(144, 20));
		symbolTF.setTabIndex(4);
		symbolTF.setText("");

		headlineTF.setLocation(new Point(256, 88));
		headlineTF.setSize(new Point(144, 20));
		headlineTF.setTabIndex(5);
		headlineTF.setText("");

		queuedCB.setLocation(new Point(24, 136));
		queuedCB.setSize(new Point(104, 16));
		queuedCB.setTabIndex(6);
		queuedCB.setText("Queued");

		urlTF.setLocation(new Point(256, 136));
		urlTF.setSize(new Point(144, 20));
		urlTF.setTabIndex(7);
		urlTF.setText("");

		parallelCB.setLocation(new Point(24, 120));
		parallelCB.setSize(new Point(120, 24));
		parallelCB.setTabIndex(1);
		parallelCB.setText("Parallel");

		ecDllNameLabel.setLocation(new Point(152, 40));
		ecDllNameLabel.setSize(new Point(96, 24));
		ecDllNameLabel.setTabIndex(2);
		ecDllNameLabel.setTabStop(false);
		ecDllNameLabel.setText("EC DLL Path");

		ecDllNameFT.setLocation(new Point(256, 40));
		ecDllNameFT.setSize(new Point(144, 20));
		ecDllNameFT.setTabIndex(3);
		ecDllNameFT.setText("");

		this.setNewControls(new Control[] {
							InstallEventBorder, 
							PublishEventBorder});
		PublishEventBorder.setNewControls(new Control[] {
										  urlTF, 
										  queuedCB, 
										  headlineTF, 
										  symbolTF, 
										  urlLabel, 
										  headlineLabel, 
										  symbolLabel, 
										  publishButton});
		InstallEventBorder.setNewControls(new Control[] {
										  ecDllNameFT, 
										  ecDllNameLabel, 
										  parallelCB, 
										  installEventButton});
	}

	/**
	 * The main entry point for the application. 
	 *
	 * @param args Array of parameters passed to the application
	 * via the command line.
	 */
	public static void main(String args[])
	{
		Application.run(new NewsFlash());
	}
}
