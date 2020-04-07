//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("C:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /javatlb /c2j /creg /xh /wfc  /w /xi /X:rkc /l "C:\DOCUME~1\a-sunilc\LOCALS~1\Temp\jvc7A.tmp" /nologo /d "D:\ComPlusSamples\Source\QCSample1" "D:\ComPlusSamples\Source\QCSample1\QCOrder.tlb")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package qcorder;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;
import com.ms.wfc.data.*;
import java.util.Vector;

/** @com.register(clsid=CB34A1A2-28C2-11D2-B5B6-00C04FC340EE, typelib=6DD1E6C2-28C1-11D2-B5B6-00C04FC340EE, version="1.0", description="Order Class")*/
public class Order implements IUnknown,com.ms.com.NoAutoScripting,qcorder.IOrderDefault
{
	private int		customerID		=	0;
	private int		orderID			=	0;
	private Vector	itemVect		=	null;
	private Vector	quantityVect	=	null;
	
	public Order()
	{
		itemVect		=	new Vector();
		quantityVect	=	new Vector();
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
		if((itemVect != null) && (quantityVect != null))
		{
			itemVect.addElement(new Integer(itemID));
			quantityVect.addElement(new Integer(quantity));
		}
	}

	/**
     * Adds order to Order Entry table and sends order to shipping department.
     *
     * @param       lFlags        option flags
     * @return      ---
     *
     **/
	public void Process(int lFlags)
	{
		boolean dataInsertFlag	=	false;
		boolean shipInvokeFlag	=	false;
		
		dataInsertFlag	=	WriteOrderDB();
		com.ms.win32.User32.MessageBox(0,"Order is added and queuing message is added for shipment process","Order Status",0);
		System.out.println(dataInsertFlag);
		if(dataInsertFlag) // if order is successfully added to order table 
		{
			shipInvokeFlag	=	InvokeShip();
		}
		
		com.ms.mtx.IObjectContext ctxObj = com.ms.mtx.Context.getObjectContext();
		if(ctxObj != null)
		 {
			if(shipInvokeFlag)
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
     * Writes the order into the Order Entry table.
     *
     * @param       ---
     * @return      boolean			True if successful else return false
     * @see			com.ms.wfc.data.Connection
     **/
	private boolean WriteOrderDB()
	{
		int			result		=	0;
		Connection	con			=	null;
		String		conDetail	=	null;
		boolean		returnValue	=	false;
		try
		{
			conDetail	=	"Data Source=" + helper.DatabaseSettings.DSN + ";" + "User Id=" + helper.DatabaseSettings.User + ";" + "Password=" + helper.DatabaseSettings.Pass + ";";
			con			=	new Connection();
			con.open(conDetail);
			for(int index = 0;index < itemVect.size(); index++)
			{
				String value =  String.valueOf(orderID) + "," + String.valueOf(customerID) + "," + String.valueOf(index) + "," + ((Integer)itemVect.elementAt(index)).toString() + "," +((Integer)quantityVect.elementAt(index)).toString()  ;
				result	=	con.executeUpdate("Insert into QCSampleOrder (order_id,cust_id,line_no,item_id,quantity) values(" + value + ")");
				System.out.println(result);
				if(result > 0)
				{
					returnValue = true;		// Database operation is successful
				}
				else
				{
					returnValue = false;	
					break;
				}
			}
		}
		catch(Exception exp)
		{
			System.out.println("Exception in database handling " + exp); 
		}
		finally
		{
			if(con != null)   
			{
				con.close();  // Close the database connection
			}
		}
		return returnValue;
	}
	
	/**
     * Creates a Ship object to send to the shipping department
     *
     * @param       ---
     * @return      boolean			True if successful else return false
     * @see			com.ms.win32.ole32.CoGetObject
     **/
	private boolean InvokeShip()
	{
		boolean returnValue		=	false;	
		qcship.IShip ship_obj	=	null;
		try
		{
			// Using Queue moniker to create queued component
			ship_obj =	(qcship.IShip)com.ms.win32.Ole32.CoGetObject("queue:/new:QCShipLib.Ship",null,qcship.IShip.iid);
			if(ship_obj != null)
			{
				ship_obj.setCustomerId(customerID);
				ship_obj.setOrderId(orderID);
				for(int index = 0;index < itemVect.size(); index++)
				{
					ship_obj.LineItem(((Integer)(itemVect.elementAt(index))).intValue(),((Integer)(quantityVect.elementAt(index))).intValue());
				}
				ship_obj.Process(0);
				returnValue	=	true;
			}                          
		}
		catch(com.ms.com.ComFailException exp)
		{
			System.out.println("Exception calling Ship :  " + exp);
		}
		
		return returnValue;
	}

}
