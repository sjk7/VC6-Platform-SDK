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

// VTable-only interface ConnectionEventsVt
/** @com.interface(iid=00000402-0000-0010-8000-00AA006D2EA4, thread=AUTO) */
public interface ConnectionEventsVt extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,iid=00000500-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pError, [in,out,type=PTR] adStatus, [in,iid=00000550-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pConnection) */
  public void InfoMessage(msado15.Error pError, int[] adStatus, msado15._Connection pConnection);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=I4] TransactionLevel, [in,iid=00000500-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pError, [in,out,type=PTR] adStatus, [in,iid=00000550-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pConnection) */
  public void BeginTransComplete(int TransactionLevel, msado15.Error pError, int[] adStatus, msado15._Connection pConnection);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,iid=00000500-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pError, [in,out,type=PTR] adStatus, [in,iid=00000550-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pConnection) */
  public void CommitTransComplete(msado15.Error pError, int[] adStatus, msado15._Connection pConnection);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([in,iid=00000500-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pError, [in,out,type=PTR] adStatus, [in,iid=00000550-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pConnection) */
  public void RollbackTransComplete(msado15.Error pError, int[] adStatus, msado15._Connection pConnection);

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters([in,out,size=1,type=ARRAY] Source, [in,out,type=PTR] CursorType, [in,out,type=PTR] LockType, [in,out,size=1,type=ARRAY] Options, [in,out,type=PTR] adStatus, [in,iid=0000054E-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pCommand, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset, [in,iid=00000550-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pConnection) */
  public void WillExecute(String[] Source, int[] CursorType, int[] LockType, int[] Options, int[] adStatus, msado15._Command pCommand, msado15._Recordset pRecordset, msado15._Connection pConnection);

  /** @com.method(vtoffset=5, addFlagsVtable=4)
      @com.parameters([in,type=I4] RecordsAffected, [in,iid=00000500-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pError, [in,out,type=PTR] adStatus, [in,iid=0000054E-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pCommand, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset, [in,iid=00000550-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pConnection) */
  public void ExecuteComplete(int RecordsAffected, msado15.Error pError, int[] adStatus, msado15._Command pCommand, msado15._Recordset pRecordset, msado15._Connection pConnection);

  /** @com.method(vtoffset=6, addFlagsVtable=4)
      @com.parameters([in,out,size=1,type=ARRAY] ConnectionString, [in,out,size=1,type=ARRAY] UserID, [in,out,size=1,type=ARRAY] Password, [in,out,size=1,type=ARRAY] Options, [in,out,type=PTR] adStatus, [in,iid=00000550-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pConnection) */
  public void WillConnect(String[] ConnectionString, String[] UserID, String[] Password, int[] Options, int[] adStatus, msado15._Connection pConnection);

  /** @com.method(vtoffset=7, addFlagsVtable=4)
      @com.parameters([in,iid=00000500-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pError, [in,out,type=PTR] adStatus, [in,iid=00000550-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pConnection) */
  public void ConnectComplete(msado15.Error pError, int[] adStatus, msado15._Connection pConnection);

  /** @com.method(vtoffset=8, addFlagsVtable=4)
      @com.parameters([in,out,type=PTR] adStatus, [in,iid=00000550-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pConnection) */
  public void Disconnect(int[] adStatus, msado15._Connection pConnection);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x402, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
