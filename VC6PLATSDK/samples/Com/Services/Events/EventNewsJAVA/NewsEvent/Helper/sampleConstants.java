package helper;
public interface sampleConstants
{
	public static final boolean PARALLEL_FLAG		=	true;
	public static final boolean UNINSTALL_FLAG		=	false;
	public static final boolean INSTALL_FLAG		=	true;
	public static final boolean SUBSCRIBE_FLAG		=	true;
	public static final boolean UNSUBSCRIBE_FLAG		=	false;
	
	public static final String	EVENT_CLSID			=	"{997FF9C0-0F01-11D3-9257-0080C7C30D72}";
	public static final String  CASCADE_EVENT_CLSID 	=	"{8CE4A9E0-0FC1-11D3-925A-0080C7C30D72}";
	
	public static final String  EVENT_NAME			=	"NEWSEVENTCLASSLib.NewsEvent";
	public static final String  CASCADE_EVENT_NAME	=	"CASCADEECLib.CascadeEC";		
	public static final String  PERSIS_EVENT_NAME	=	"PERSISTATLLib.NewsEvent";
	
	public static final String  SUBSCRIBER_NAME		=	"NewsSubscriber";
	public static final String  CASCADE_NAME		=	"CascadeSubscription" ;
	public static final String	PUBLISHER_NAME		=	"NewsPublisher";
	public static final String	PERSIS_NAME			=	"PersistentNewsSubscription";
	public static final String	TRANSIENT_NAME		=	"TransientSubscription";
	
	public static final String  PERSIST_EVENT_DLL	=	"D:\\mssdk\\Samples\\COM\\Services\\Events\\EventNewsJAVA\\PersistSubs\\PersistSubs.dll";
	public static final String  CASCADE_EVENT_DLL	=	"D:\\mssdk\\Samples\\COM\\Services\\Events\\EventNewsJAVA\\CascadeEvent\\CascadeEvent.dll";
	public static final String  NEW_EVENT_DLL		=	"D:\\mssdk\\Samples\\COM\\Services\\Events\\EventNewsJAVA\\NewsEvent\\NewsEvent.dll";
	
}
