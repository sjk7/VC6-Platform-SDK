//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("C:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /javatlb /c2j /creg /xh /wfc  /w /xi /X:rkc /l "C:\DOCUME~1\a-sunilc\LOCALS~1\Temp\jvc24F.tmp" /nologo /d "D:\ComPlusSamples\Source\QCSample1" "D:\ComPlusSamples\Source\QCSample1\QCNotify.tlb")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package qcnotify;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;
import com.ms.wfc.data.*;
import java.util.*;

/** @com.register(clsid=6DD1E6F0-28C1-11D2-B5B6-00C04FC340EE, typelib=6DD1E6DC-28C1-11D2-B5B6-00C04FC340EE, version="1.0", description="Notify Class")*/
public class Notify implements IUnknown,com.ms.com.NoAutoScripting,qcnotify.INotifyDefault
{
	private int		customerID		=	0;
	private int		orderID			=	0;
	private Vector	itemVect		=	null;
	private Vector	quantityVect	=	null;
	private Vector  shipStatusVect	=	null;
	
	public Notify()
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
		this.orderID = orderID;
	}
	
	/**
     * Adds a single item to an order
     *
     * @param       itemID        An item identifier 
     * @param		quantity	  Quantity of the item ordered
     * @param		shipStatus	  Shipping status value.
     * @return      ---
     *
     **/
	public void LineItem(int itemID, int quantity, int shipStatus)
	{
		if((itemVect != null) && (quantityVect != null) &&(shipStatusVect != null))
		{
			itemVect.addElement(new Integer(itemID));
			quantityVect.addElement(new Integer(quantity));
			shipStatusVect.addElement(new Integer(shipStatus));
		}	
	}
	
	/**
     * Updates order entry database with shipping status strings.
     *
     * @param       lFlags        option flags
     * @return      ---
     *
     **/
	public void Process(int lFlags)
	{
		boolean dataInsertFlag		=	false;
		
		dataInsertFlag	=	WriteDB();
		com.ms.mtx.IObjectContext ctxObj = com.ms.mtx.Context.getObjectContext();
		if(ctxObj != null)
		 {
			if(dataInsertFlag)
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
     * Updates order entry database with shipping status strings.
     *
     * @param       ---
     * @return      boolean			True if successful else return false
     * @see			com.ms.wfc.data.Connection
     **/
	private boolean WriteDB()
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
			StringBuffer sql = new StringBuffer("");
			sql.append("Update QCSampleOrder set ship_status = '");
			sql.append(getShipStatusString((Integer)shipStatusVect.elementAt(index)));
			sql.append("' ");
			sql.append("Where (cust_id = ");
			sql.append(String.valueOf(customerID) + ") And");
			sql.append("( order_id = ");
			sql.append(String.valueOf(orderID) + ") And");
			sql.append("( line_no = ");
			sql.append(String.valueOf(index) + ") And");
			sql.append("( item_id = ");
			sql.append(((Integer)(itemVect.elementAt(index))).toString() + ") And");
			sql.append("( quantity = ");
			sql.append(((Integer)(quantityVect.elementAt(index))).toString() + ")");
			result	=	con.executeUpdate(sql.toString());
			if(result > 0)
			{
				returnValue = true;
			}
			else
			{
				returnValue = false;
				break;
			}
			System.out.println(result);
		}
		con.close();
		return returnValue;
		
	}
	
	/**
     * Determines shipping status string based on shipping status value
     *
     * @param       ---
     * @return      String			Shipping status string
     **/
	private String getShipStatusString(Integer statusVal)
	{
		String	result	=	null;
		int		value	=	statusVal.intValue();
		
		switch(value)
		{
			case _ShipStatus.ssShipped : 
			{
				result = "ssShipped";
				break;
			}
			case _ShipStatus.ssBackOrdered :
			{
				result = "ssBackOrdered";
				break;
			}
			case _ShipStatus.ssNotStocked : 
			{
				result = "ssNotStocked";
				break;
			}
			default :
			{
				result = "ssUnrecognizedItem";
			}
		}
		return result;
	}

}
