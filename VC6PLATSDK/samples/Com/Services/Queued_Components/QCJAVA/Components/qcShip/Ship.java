//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("C:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /javatlb /c2j /creg /xh /wfc  /w /xi /X:rkc /l "C:\DOCUME~1\a-sunilc\LOCALS~1\Temp\jvc1E6.tmp" /nologo /d "D:\ComPlusSamples\Source\QCSample1" "D:\ComPlusSamples\Source\QCSample1\QCShip.tlb")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package qcship;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;
import com.ms.wfc.data.*;
import java.util.Vector;


/** @com.register(clsid=CB34A1A5-28C2-11D2-B5B6-00C04FC340EE, typelib=6DD1E6CF-28C1-11D2-B5B6-00C04FC340EE, version="1.0", description="Ship Class")*/
public class Ship implements IUnknown,com.ms.com.NoAutoScripting,qcship.IShipDefault
{
	private int		customerID		=	0;
	private int		orderID			=	0;
	private Vector	itemVect		=	null;
	private Vector	quantityVect	=	null;
	private Vector  shipStatusVect	=	null;
	
	public Ship()
	{
		itemVect		=	new Vector();
		quantityVect	=	new Vector();
		shipStatusVect	=	new Vector();
	}
	
	/**
     * property put for CustomerId property
     *
     * @param       customerID        A customer identifier
     * @return      ---
     *
     **/
	public void setCustomerId(int customerID) 
	{
		this.customerID = customerID;	   
	}
	
	/**
     * property put for OrderId property
     *
     * @param       orderID        An order identifier
     * @return      ---
     *
     **/
	public void setOrderId(int orderID) 
	{
		this.orderID	=	orderID;
	}
	
	/**
     * Adds a single item to an order
     *
     * @param       itemID        An item identifier 
     * @param		quantity	  Quantity of the item ordered
     * @return      ---
     *
     **/
	public void LineItem(int itemID, int quantity) 
	{
		if((itemVect != null) && (quantityVect != null) &&(shipStatusVect != null))
		{
			itemVect.addElement(new Integer(itemID));
			quantityVect.addElement(new Integer(quantity));
			shipStatusVect.addElement(randomShipStatus());
		}
	}
	
	/**
     * Adds order to Shipping table and notify requestor of shipping status.
     *
     * @param       lFlags        option flags
     * @return      ---
     *
     **/
	public void Process(int lFlags)
	{
		boolean dataInsertFlag		=	false;
		boolean notifyInvokeFlag	=	false;
		
		dataInsertFlag	=	WriteShipDB();
		if(dataInsertFlag)
		{
			notifyInvokeFlag	=	InvokeNotify();
		}
		com.ms.mtx.IObjectContext ctxObj = com.ms.mtx.Context.getObjectContext();
		if(ctxObj != null)
		 {
			if(notifyInvokeFlag)
			{
				ctxObj.SetComplete();
			}
			else
			{
				ctxObj.SetAbort();
			}
		 }
	}
	
	/**
     * Writes the order into the Shipping table.
     *
     * @param       ---
     * @return      boolean			True if successful else return false
     * @see			com.ms.wfc.data.Connection
     **/
	private boolean WriteShipDB()
	{
		int			result		=	0;
		Connection	con			=	null;
		String		conDetail	=	null;
		boolean		returnValue	=	false;
		
		conDetail	=	"Data Source=" + helper.DatabaseSettings.DSN + ";" + "User Id=" + helper.DatabaseSettings.User + ";" + "Password=" + helper.DatabaseSettings.Pass + ";";
		con			=	new Connection();
		con.open(conDetail);
		for(int index = 0;index < itemVect.size(); index++)
		{
			String value =  String.valueOf(orderID) + "," + String.valueOf(customerID) + "," + String.valueOf(index) + "," + ((Integer)itemVect.elementAt(index)).toString() + "," +((Integer)quantityVect.elementAt(index)).toString() + ", '" + (String)(shipStatusVect.elementAt(index)) + "'" ;
			System.out.println(value);
			result	=	con.executeUpdate("Insert into QCSampleShip (order_id,cust_id,line_no,item_id,quantity,ship_status) values(" + value + ")");
			if(result > 0)
			{
				returnValue = true;
			}
			else
			{
				returnValue = false;
				break;
			}
		}
		con.close();
		return returnValue;
	}
	
	/**
     * Creates a Notify object to notify requestor of shipping status.
     *
     * @param       ---
     * @return      boolean			True if successful else return false
     * @see			com.ms.win32.ole32.CoGetObject
     **/
	private boolean InvokeNotify()
	{
		boolean				returnValue		=	false;	
		qcnotify.INotify	notify_obj		=	null;
		try
		{
			// Using Queue moniker to create queued component
			notify_obj =	(qcnotify.INotify)com.ms.win32.Ole32.CoGetObject("queue:/new:QCNotifyLib.Notify",null,qcnotify.INotify.iid);
			if(notify_obj != null)
			{
				notify_obj.setCustomerId(customerID);
				notify_obj.setOrderId(orderID);
				for(int index = 0;index < itemVect.size(); index++)
				{
					notify_obj.LineItem(((Integer)(itemVect.elementAt(index))).intValue(),((Integer)(quantityVect.elementAt(index))).intValue(),shipStatusValue((String)(shipStatusVect.elementAt(index))));
				}
				notify_obj.Process(0);
				returnValue	=	true;
			}                          
		}
		catch(com.ms.com.ComFailException exp)
		{
			System.out.println("Exception calling Notify :  " + exp);
		}
		
		return returnValue;
	}
	
	/**
     * Determines shipping status for a particular line item.
     *
     * @param       ---
     * @return      String			Shipping status string
     **/
	private String randomShipStatus()
	{   
		double randomStatusValue	=	0.0;
		String shipStatus			=	null;
		
		randomStatusValue	=	java.lang.Math.random() * 100;
		if(randomStatusValue < 80)
		{
			shipStatus	=	"ssShipped";
		}
		else if(randomStatusValue < 93)
		{
			shipStatus	=	"ssBackOrdered";
		}
		else if(randomStatusValue < 97)
		{
			shipStatus	=	"ssNotStocked";
		}
		else
		{
			shipStatus	=	"ssUnrecognizedItem";
		}
		return shipStatus; 
	}
	
	/**
     * Determines shipping status value based on shipping status string
     *
     * @param       ---
     * @return      int			Shipping status value
     **/
	private int shipStatusValue(String shipStatus)
	{
		int returnValue		=	0;
		if(shipStatus.equals("ssShipped"))
		{
			returnValue	=	qcnotify._ShipStatus.ssShipped;
		}
		else if(shipStatus.equals("ssBackOrdered"))
		{
			returnValue	=	qcnotify._ShipStatus.ssBackOrdered;
		}
		else if(shipStatus.equals("ssNotStocked"))
		{
			returnValue	=	qcnotify._ShipStatus.ssNotStocked;
		}
		else if(shipStatus.equals("ssUnrecognizedItem"))
		{
			returnValue	=	qcnotify._ShipStatus.ssUnrecognizedItem;
		}
		return returnValue;
		
	}
	

}
