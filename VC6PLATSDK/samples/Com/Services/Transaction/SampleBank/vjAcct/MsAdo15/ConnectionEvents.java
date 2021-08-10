//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("D:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /wfc  /w /xi /X:rkc /l "D:\DOCUME~1\erica\LOCALS~1\Temp\jvc22.tmp" /nologo /d "D:\mssdk\samples\Com\Services\Transaction\SampleBank\vjacct" "D:\Program Files\Common Files\System\ado\msado15.dll")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package msado15;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// Dispatch-only interface ConnectionEvents
/** @com.interface(iid=00000400-0000-0010-8000-00AA006D2EA4, thread=AUTO, type=DISPATCH) */
public interface ConnectionEvents extends IUnknown
{
  /** @com.method(dispid=0, type=METHOD, name="InfoMessage")
      @com.parameters([in,type=DISPATCH] pError, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pConnection) */
  public void InfoMessage(msado15.Error pError, int[] adStatus, msado15._Connection pConnection);

  /** @com.method(dispid=1, type=METHOD, name="BeginTransComplete")
      @com.parameters([in,type=I4] TransactionLevel, [in,type=DISPATCH] pError, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pConnection) */
  public void BeginTransComplete(int TransactionLevel, msado15.Error pError, int[] adStatus, msado15._Connection pConnection);

  /** @com.method(dispid=3, type=METHOD, name="CommitTransComplete")
      @com.parameters([in,type=DISPATCH] pError, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pConnection) */
  public void CommitTransComplete(msado15.Error pError, int[] adStatus, msado15._Connection pConnection);

  /** @com.method(dispid=2, type=METHOD, name="RollbackTransComplete")
      @com.parameters([in,type=DISPATCH] pError, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pConnection) */
  public void RollbackTransComplete(msado15.Error pError, int[] adStatus, msado15._Connection pConnection);

  /** @com.method(dispid=4, type=METHOD, name="WillExecute")
      @com.parameters([in,out,elementType=STRING,type=ARRAY] Source, [in,out,elementType=I4,type=PTR] CursorType, [in,out,elementType=I4,type=PTR] LockType, [in,out,elementType=I4,type=ARRAY] Options, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pCommand, [in,type=DISPATCH] pRecordset, [in,type=DISPATCH] pConnection) */
  public void WillExecute(String[] Source, int[] CursorType, int[] LockType, int[] Options, int[] adStatus, msado15._Command pCommand, msado15._Recordset pRecordset, msado15._Connection pConnection);

  /** @com.method(dispid=5, type=METHOD, name="ExecuteComplete")
      @com.parameters([in,type=I4] RecordsAffected, [in,type=DISPATCH] pError, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pCommand, [in,type=DISPATCH] pRecordset, [in,type=DISPATCH] pConnection) */
  public void ExecuteComplete(int RecordsAffected, msado15.Error pError, int[] adStatus, msado15._Command pCommand, msado15._Recordset pRecordset, msado15._Connection pConnection);

  /** @com.method(dispid=6, type=METHOD, name="WillConnect")
      @com.parameters([in,out,elementType=STRING,type=ARRAY] ConnectionString, [in,out,elementType=STRING,type=ARRAY] UserID, [in,out,elementType=STRING,type=ARRAY] Password, [in,out,elementType=I4,type=ARRAY] Options, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pConnection) */
  public void WillConnect(String[] ConnectionString, String[] UserID, String[] Password, int[] Options, int[] adStatus, msado15._Connection pConnection);

  /** @com.method(dispid=7, type=METHOD, name="ConnectComplete")
      @com.parameters([in,type=DISPATCH] pError, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pConnection) */
  public void ConnectComplete(msado15.Error pError, int[] adStatus, msado15._Connection pConnection);

  /** @com.method(dispid=8, type=METHOD, name="Disconnect")
      @com.parameters([in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pConnection) */
  public void Disconnect(int[] adStatus, msado15._Connection pConnection);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x400, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
