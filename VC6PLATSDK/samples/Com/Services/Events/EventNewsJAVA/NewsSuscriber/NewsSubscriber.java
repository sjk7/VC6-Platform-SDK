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
public class NewsSubscriber extends Form
{
	comadmin.ICOMAdminCatalog	admin			=	null;
	String						cascadeAppName	=	null;
	
	public NewsSubscriber()
	{
		// Required for Visual J++ Form Designer support
		initForm();
		dllPathTF.setText(helper.sampleConstants.CASCADE_EVENT_DLL);
		initAdminCatlog();
	}

	/**
	 * Form1 overrides dispose so it can clean up the
	 * component list.
	 */
	public void dispose()
	{
		super.dispose();
		uninstallCascadeEvent();
		components.dispose();
		
	}
	
	/**
     * Handle transient subscription processing
     *
     * @param		---
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog, ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	 
	private void subscribeTransButton_click(Object source, Event e)
	{
		comadmin.ICatalogCollection		subCollec	=	null;
		String							eventCLSID	=	null;
		
		subCollec	=	(comadmin.ICatalogCollection)(admin.GetCollection("TransientSubscriptions"));
		// If cascade radio button is checked then register the transient subscription fot cascade event class
		if(cascadeTransRB.getChecked())
		{
			eventCLSID	=	helper.sampleConstants.CASCADE_EVENT_CLSID;	
			directTransRB.setEnabled(false);
		}
		// If direct radio button is checked then register the transient subscription fot news event class
		else if(directTransRB.getChecked())
		{
			eventCLSID	=	helper.sampleConstants.EVENT_CLSID;
			cascadeTransRB.setEnabled(false);
		}
		if((subscribeTransButton.getText()).equals("Subscribe"))
		{
			//Register the subscription.
			updateSubscription(subCollec,helper.sampleConstants.TRANSIENT_NAME,eventCLSID,helper.sampleConstants.SUBSCRIBE_FLAG);	
			subscribeTransButton.setText("Unsubscribe");
		}
		else
		{
			//Unsubscribe the subscription.
			updateSubscription(subCollec,helper.sampleConstants.TRANSIENT_NAME,eventCLSID,helper.sampleConstants.UNSUBSCRIBE_FLAG);	
			subscribeTransButton.setText("Subscribe");
			if(!((installCascadeButton.getText()).equals("Install")))
			{
				cascadeTransRB.setEnabled(true);
			}
			directTransRB.setEnabled(true);
		}
	}

	private void clearButton_click(Object source, Event e)
	{
		eventList.removeAll();
	}

	/**
     * Handle persistent subscription processing
     *
     * @param		---
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog, ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	private void subscribePersisButton_click(Object source, Event e)
	{
		comadmin.ICatalogCollection		appCollec	=	null;
		String							eventCLSID	=	null;
		
		
		appCollec	=	(comadmin.ICatalogCollection)(admin.GetCollection("Applications"));
		// If cascade radio button is checked then register the persistent subscription fot cascade event class
		if(cascadePersisRB.getChecked())
		{
			eventCLSID	=	helper.sampleConstants.CASCADE_EVENT_CLSID;	
			directPersisRB.setEnabled(false);
		}
		// If direct radio button is checked then register the persistent subscription fot news event class
		else if(directPersisRB.getChecked())
		{
			eventCLSID	=	helper.sampleConstants.EVENT_CLSID;
			cascadePersisRB.setEnabled(false);
		}
		if((subscribePersisButton.getText()).equals("Subscribe"))
		{
			// Register the subscription.
			checkForApplication(appCollec, helper.sampleConstants.INSTALL_FLAG,helper.sampleConstants.SUBSCRIBER_NAME , helper.sampleConstants.PERSIS_EVENT_NAME ,helper.sampleConstants.PERSIS_NAME, eventCLSID , helper.sampleConstants.SUBSCRIBE_FLAG );
			subscribePersisButton.setText("Unsubscribe");
			if(queuedPersisCB.getChecked())
			{
				queuedPersisCB.setEnabled(false);
			}
		}
		else // Unsubscribe Persistent subscription.
		{
			checkForApplication(appCollec, helper.sampleConstants.INSTALL_FLAG,helper.sampleConstants.SUBSCRIBER_NAME , helper.sampleConstants.PERSIS_EVENT_NAME ,helper.sampleConstants.PERSIS_NAME, eventCLSID , helper.sampleConstants.UNSUBSCRIBE_FLAG );
			subscribePersisButton.setText("Subscribe");
			queuedPersisCB.setEnabled(true);
			if(!((installCascadeButton.getText()).equals("Install")))
			{
				cascadePersisRB.setEnabled(true);
			}
			directPersisRB.setEnabled(true);
			
		}

			
		
	}

	/**
     * Install Cascade event class on the local machine and also makes it persistent
     * subscriber for news event.
     *
     * @param		---
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog, ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	
	private void installCascadeButton_click(Object source, Event e)
	{
		comadmin.ICatalogCollection		appCollec	=	null;
		//Get the application collection
		appCollec	=	(comadmin.ICatalogCollection)(admin.GetCollection("Applications"));
		if((installCascadeButton.getText()).equals("Install"))
		{
			// Check if the application is already present.
			checkForAppAlreadyInstalled(appCollec ,appNameTF.getText());
			//Create new application for the cascade event class.
			addCatalog(appCollec,appNameTF.getText());
			//Install cascade event class.
			cascadeAppName = appNameTF.getText();
			admin.InstallEventClass(appNameTF.getText(),dllPathTF.getText(),"" , "");
			//Create persistent subscription to news event class.
			checkForApplication(appCollec, helper.sampleConstants.INSTALL_FLAG,appNameTF.getText() , helper.sampleConstants.CASCADE_EVENT_NAME ,helper.sampleConstants.CASCADE_NAME, helper.sampleConstants.EVENT_CLSID,helper.sampleConstants.SUBSCRIBE_FLAG );
			cascadePersisRB.setEnabled(true);
			cascadeTransRB.setEnabled(true);
			installCascadeButton.setText("Uninstall");
		}
		else
		{
			uninstallCascadeEvent();
		}
	}
	
	/**
     * Uninstall Cascade Event.
     *
     * @param		---
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog, ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	private void uninstallCascadeEvent()
	{
		comadmin.ICatalogCollection		appCollec	=	null;
		if(cascadeAppName != null)
		{
			//Get the application collection
			appCollec	=	(comadmin.ICatalogCollection)(admin.GetCollection("Applications"));
		
			// Uninstall the cascade event class.
			checkForApplication(appCollec, helper.sampleConstants.UNINSTALL_FLAG ,cascadeAppName,"", "","" ,helper.sampleConstants.SUBSCRIBE_FLAG);
			cascadePersisRB.setEnabled(false);
			cascadeTransRB.setEnabled(false);
			installCascadeButton.setText("Install");
		}
	}
	
	/**
     * Check for whether the given application name is present or not.
     *
     * @param       appCollec		Collection of Applications
     * @param		processFlag		The flag specify whether the object in the collection is required to be added or removed.
     * @param		appName			Name of the application to look for in the collection.
     * @param		compName		Name of the component to look for if application is present in the collection.
     * @param		subName			The name of subscription 
     * @param		eventCLSID		Event class id for subscription processing. 
     * @param		subProcessFlag	Whether to subscribe to the event or to remove the subscription.
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog , ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	private void checkForApplication(comadmin.ICatalogCollection appCollec,boolean appProcessFlag, String appName , String compName, String subName, String eventCLSID , boolean subProcessFlag)
	{
		int								index		=	0;
		comadmin.ICatalogCollection		compCollec	=	null;
		
		appCollec.Populate();
		for(index = 0; index < appCollec.getCount(); index++)
		{
			String str = (((comadmin.ICatalogObject)(appCollec.getItem(index))).getName()).toString();
			//Checking if application is present in the collection.
			if(((((comadmin.ICatalogObject)(appCollec.getItem(index))).getName()).toString()).equals(appName))
			{
				if(appProcessFlag == helper.sampleConstants.INSTALL_FLAG)
				{
					// Get Components collection.
					compCollec	=(comadmin.ICatalogCollection)(appCollec.GetCollection("Components",((comadmin.ICatalogObject)(appCollec.getItem(index))).getKey()));
					compCollec.Populate();
					checkForComponent(compCollec , compName , subName , eventCLSID, subProcessFlag);
					
				}
				else // Uninstall the application.
				{
					appCollec.Remove(index);
					appCollec.SaveChanges();
				}
				break;
			}
		}
	}
	
	/**
     * Check for whether the given component name is present or not in application.
     *
     * @param       compCollec		Collection of Components in Application
     * @param		compName		Name of the component to look for.
     * @param		subName			The name of subscription 
     * @param		eventCLSID		Event class id for subscription processing. 
     * @param		subProcessFlag	Whether to subscribe to the event or to remove the subscription.
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog, ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	private void checkForComponent(comadmin.ICatalogCollection compCollec,  String compName, String subName, String eventCLSID, boolean subProcessFlag)
	{
		int								index		=	0;
		comadmin.ICatalogCollection		subCollec	=	null;
		
		for(index = 0 ;index < compCollec.getCount(); index++)
		{
			//Checking if given component is present in the collection.
			if(((((comadmin.ICatalogObject)(compCollec.getItem(index))).getName()).toString()).equals(compName))
			{
				// Get the subscriptions associated with the component.
				subCollec	=(comadmin.ICatalogCollection)(compCollec.GetCollection("SubscriptionsForComponent",((comadmin.ICatalogObject)(compCollec.getItem(index))).getKey()));
				subCollec.Populate();
				updateSubscription(subCollec , subName , eventCLSID, subProcessFlag);
				break;
				
			}
		}
	}
	/**
     * Handle Subscriptions processing
     *
     * @param       subCollec		Collection of Subscriptions.
     * @param		subName			The name of subscription 
     * @param		eventCLSID		Event class id. 
     * @param		subProcessFlag	Whether to subscribe to the event or to remove the subscription.
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog, ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	private comadmin.ICatalogCollection updateSubscription(comadmin.ICatalogCollection  subCollec , String subName , String eventCLSID, boolean subProcessFlag)
	{
		comadmin.ICatalogObject	subCatalogObj	=	null;
		if(subProcessFlag) 
		{
			// Add a subscription.
			subCatalogObj	=	(comadmin.ICatalogObject)(subCollec.Add());
			subCatalogObj.setValue("EventCLSID",new Variant(eventCLSID));
			subCatalogObj.setValue("Name" , new Variant(subName));
			if(subName.equals(helper.sampleConstants.PERSIS_NAME))
			{
				if(queuedPersisCB.getChecked())
				{
					subCatalogObj.setValue("Queued" , new Variant(true));
				}
			}
			else if (subName.equals(helper.sampleConstants.TRANSIENT_NAME))
			{
				subCatalogObj.setValue("SubscriberInterface" , new Variant(this));
			}
			subCollec.SaveChanges();
		}
		else
		{
			removeSubscription(subCollec , subName);
		}
		return subCollec;
	}
	/**
     * Removing Subscription from the collection
     *
     * @param       subCollec		Collection of Subscriptions.
     * @param		subName			The name of subscription to be removed.
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog, ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	private void removeSubscription(comadmin.ICatalogCollection subCollec , String subName)
	{
		int		index	=	0;
		
		for(index = 0 ; index < subCollec.getCount() ; index++)
		{
			// Checking if given subscription is present in the collection.
			if(((((comadmin.ICatalogObject)(subCollec.getItem(index))).getName()).toString()).equals(subName))
			{
				subCollec.Remove(index);
				subCollec.SaveChanges();
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
		
		try
		{
			admin		=	(comadmin.ICOMAdminCatalog)new comadmin.COMAdminCatalog();
			appCollec	=	(comadmin.ICatalogCollection)(admin.GetCollection("Applications"));
			checkForAppAlreadyInstalled(appCollec , helper.sampleConstants.SUBSCRIBER_NAME);
			addCatalog(appCollec, helper.sampleConstants.SUBSCRIBER_NAME);
			//Install persistent subscriber component.
			admin.InstallComponent(helper.sampleConstants.SUBSCRIBER_NAME,helper.sampleConstants.PERSIST_EVENT_DLL,"","");	
								   
			
		}
		catch(Exception exp)
		{
			System.out.println(exp);
		}
								   
		
	}
	
	/**
     * Setting application properties
     *
     * @param       appCollec		Collection of  Applications.
     * @param		appName			Application Name to be checked for.
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog, ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	private void addCatalog(comadmin.ICatalogCollection appCollec , String appName)
	{
		comadmin.ICatalogObject		catalogObj	=	null;
		
		catalogObj	=	(comadmin.ICatalogObject)(appCollec.Add());
			
		catalogObj.setValue("Name" , new Variant(appName));
		catalogObj.setValue("Activation" , new Variant(1));
		//catalogObj.setValue("QueuingEnabled" ,new  Variant(true));
		//catalogObj.setValue("QueueListenerEnabled",new Variant(true));
		appCollec.SaveChanges();
	}
	
	/**
     * Check if application is already present.
     *
     * @param       appCollec		Collection of  Applications.
     * @param		appName			Application Name to be checked for.
     * @return      ---
     * @see			ComAdmin.IComAdminCatalog, ComAdmin.ICatalogCollection, ComAdmin.ICatalogObject
     **/
	private void checkForAppAlreadyInstalled(comadmin.ICatalogCollection appCollec , String appName)
	{
		
		int			index		=	0;
		
		appCollec.Populate();
		for(index = 0; index < appCollec.getCount(); index++)
		{
			if(((((comadmin.ICatalogObject)(appCollec.getItem(index))).getName()).toString()).equals(appName))
			{
				// If application already present then remove the application from the catalog.
				appCollec.Remove(index);		
				appCollec.SaveChanges();
			}
		}
		
	}
	
	/************* Event Handlers **********/
	public void LongQuote(String Symbol, double BidPrice, double AskPrice, String LastTradeTime, double LastTradePrice, double NetChange, double DailyHigh, double DailyLow, int AskSize, int BidSize, double OpenPrice, double ClosePrice, String CloseDate)
	{
	}
	public void ShortQuote(String Symbol, double BidPrice, double AskPrice, double LastTradeTime, double LastTradePrice, double NetChange, double DailyHigh, double DailyLow)
	{
	}
	public void NewsFlash(double dtTimeStamp, String Symbol, String Headline, String URL)
	{
		eventList.addItem( Symbol +" : " + Headline);
	}

	
	/**
	 * NOTE: The following code is required by the Visual J++ form
	 * designer.  It can be modified using the form editor.  Do not
	 * modify it using the code editor.
	 */
	Container components = new Container();
	GroupBox transientHeading = new GroupBox();
	GroupBox persistentHeading = new GroupBox();
	GroupBox cascadeHeading = new GroupBox();
	Button subscribeTransButton = new Button();
	ListBox eventList = new ListBox();
	RadioButton directTransRB = new RadioButton();
	RadioButton cascadeTransRB = new RadioButton();
	Button clearButton = new Button();
	Button subscribePersisButton = new Button();
	RadioButton directPersisRB = new RadioButton();
	RadioButton cascadePersisRB = new RadioButton();
	CheckBox queuedPersisCB = new CheckBox();
	Button installCascadeButton = new Button();
	Label appNameLB = new Label();
	Label dllPathLB = new Label();
	CheckBox queuedCascadeCB = new CheckBox();
	Edit appNameTF = new Edit();
	Edit dllPathTF = new Edit();

	private void initForm()
	{
		this.setText("News Subscriber");
		this.setAutoScaleBaseSize(new Point(5, 13));
		this.setClientSize(new Point(515, 455));
		
		transientHeading.setLocation(new Point(16, 8));
		transientHeading.setSize(new Point(480, 256));
		transientHeading.setTabIndex(0);
		transientHeading.setTabStop(false);
		transientHeading.setText("Transient Subscriber");

		persistentHeading.setLocation(new Point(16, 272));
		persistentHeading.setSize(new Point(480, 64));
		persistentHeading.setTabIndex(1);
		persistentHeading.setTabStop(false);
		persistentHeading.setText("Persistent Subscriber");

		cascadeHeading.setLocation(new Point(16, 344));
		cascadeHeading.setSize(new Point(480, 104));
		cascadeHeading.setTabIndex(2);
		cascadeHeading.setTabStop(false);
		cascadeHeading.setText("Cascade Event Class");

		subscribeTransButton.setLocation(new Point(24, 24));
		subscribeTransButton.setSize(new Point(104, 32));
		subscribeTransButton.setTabIndex(0);
		subscribeTransButton.setText("Subscribe");
		subscribeTransButton.addOnClick(new EventHandler(this.subscribeTransButton_click));

		eventList.setLocation(new Point(24, 64));
		eventList.setSize(new Point(432, 147));
		eventList.setTabIndex(1);
		eventList.setText("listBox1");
		eventList.setUseTabStops(true);

		directTransRB.setLocation(new Point(200, 32));
		directTransRB.setSize(new Point(96, 16));
		directTransRB.setTabIndex(2);
		directTransRB.setTabStop(true);
		directTransRB.setText("Direct");
		directTransRB.setChecked(true);

		cascadeTransRB.setEnabled(false);
		cascadeTransRB.setLocation(new Point(352, 32));
		cascadeTransRB.setSize(new Point(96, 16));
		cascadeTransRB.setTabIndex(3);
		cascadeTransRB.setText("Cascade");

		clearButton.setLocation(new Point(344, 224));
		clearButton.setSize(new Point(112, 24));
		clearButton.setTabIndex(4);
		clearButton.setText("Clear");
		clearButton.addOnClick(new EventHandler(this.clearButton_click));

		subscribePersisButton.setLocation(new Point(24, 24));
		subscribePersisButton.setSize(new Point(96, 24));
		subscribePersisButton.setTabIndex(0);
		subscribePersisButton.setText("Subscribe");
		subscribePersisButton.addOnClick(new EventHandler(this.subscribePersisButton_click));

		directPersisRB.setLocation(new Point(152, 24));
		directPersisRB.setSize(new Point(88, 24));
		directPersisRB.setTabIndex(1);
		directPersisRB.setTabStop(true);
		directPersisRB.setText("Direct");
		directPersisRB.setChecked(true);

		cascadePersisRB.setEnabled(false);
		cascadePersisRB.setLocation(new Point(256, 24));
		cascadePersisRB.setSize(new Point(88, 24));
		cascadePersisRB.setTabIndex(2);
		cascadePersisRB.setText("Cascade");

		queuedPersisCB.setLocation(new Point(376, 24));
		queuedPersisCB.setSize(new Point(96, 24));
		queuedPersisCB.setTabIndex(3);
		queuedPersisCB.setText("Queued");

		installCascadeButton.setLocation(new Point(24, 24));
		installCascadeButton.setSize(new Point(96, 24));
		installCascadeButton.setTabIndex(0);
		installCascadeButton.setText("Install");
		installCascadeButton.addOnClick(new EventHandler(this.installCascadeButton_click));

		appNameLB.setLocation(new Point(168, 24));
		appNameLB.setSize(new Point(96, 16));
		appNameLB.setTabIndex(1);
		appNameLB.setTabStop(false);
		appNameLB.setText("App Name");

		dllPathLB.setLocation(new Point(168, 56));
		dllPathLB.setSize(new Point(96, 16));
		dllPathLB.setTabIndex(2);
		dllPathLB.setTabStop(false);
		dllPathLB.setText("DLL Path");

		queuedCascadeCB.setLocation(new Point(168, 80));
		queuedCascadeCB.setSize(new Point(96, 16));
		queuedCascadeCB.setTabIndex(3);
		queuedCascadeCB.setText("Queued");

		appNameTF.setLocation(new Point(272, 24));
		appNameTF.setSize(new Point(200, 20));
		appNameTF.setTabIndex(4);
		appNameTF.setText("");

		dllPathTF.setLocation(new Point(272, 56));
		dllPathTF.setSize(new Point(200, 20));
		dllPathTF.setTabIndex(5);
		dllPathTF.setText("");

		this.setNewControls(new Control[] {
							cascadeHeading, 
							persistentHeading, 
							transientHeading});
		transientHeading.setNewControls(new Control[] {
										clearButton, 
										cascadeTransRB, 
										directTransRB, 
										eventList, 
										subscribeTransButton});
		persistentHeading.setNewControls(new Control[] {
										 queuedPersisCB, 
										 cascadePersisRB, 
										 directPersisRB, 
										 subscribePersisButton});
		cascadeHeading.setNewControls(new Control[] {
									  dllPathTF, 
									  appNameTF, 
									  queuedCascadeCB, 
									  dllPathLB, 
									  appNameLB, 
									  installCascadeButton});
	}

	/**
	 * The main entry point for the application. 
	 *
	 * @param args Array of parameters passed to the application
	 * via the command line.
	 */
	public static void main(String args[])
	{
		Application.run(new NewsSubscriber());
	}
}
