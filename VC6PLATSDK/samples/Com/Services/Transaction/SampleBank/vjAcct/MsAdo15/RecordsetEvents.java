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

// Dispatch-only interface RecordsetEvents
/** @com.interface(iid=00000266-0000-0010-8000-00AA006D2EA4, thread=AUTO, type=DISPATCH) */
public interface RecordsetEvents extends IUnknown
{
  /** @com.method(dispid=9, type=METHOD, name="WillChangeField")
      @com.parameters([in,type=I4] cFields, [in,type=VARIANT] Fields, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pRecordset) */
  public void WillChangeField(int cFields, Variant Fields, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(dispid=10, type=METHOD, name="FieldChangeComplete")
      @com.parameters([in,type=I4] cFields, [in,type=VARIANT] Fields, [in,type=DISPATCH] pError, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pRecordset) */
  public void FieldChangeComplete(int cFields, Variant Fields, msado15.Error pError, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(dispid=11, type=METHOD, name="WillChangeRecord")
      @com.parameters([in,type=I4] adReason, [in,type=I4] cRecords, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pRecordset) */
  public void WillChangeRecord(int adReason, int cRecords, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(dispid=12, type=METHOD, name="RecordChangeComplete")
      @com.parameters([in,type=I4] adReason, [in,type=I4] cRecords, [in,type=DISPATCH] pError, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pRecordset) */
  public void RecordChangeComplete(int adReason, int cRecords, msado15.Error pError, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(dispid=13, type=METHOD, name="WillChangeRecordset")
      @com.parameters([in,type=I4] adReason, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pRecordset) */
  public void WillChangeRecordset(int adReason, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(dispid=14, type=METHOD, name="RecordsetChangeComplete")
      @com.parameters([in,type=I4] adReason, [in,type=DISPATCH] pError, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pRecordset) */
  public void RecordsetChangeComplete(int adReason, msado15.Error pError, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(dispid=15, type=METHOD, name="WillMove")
      @com.parameters([in,type=I4] adReason, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pRecordset) */
  public void WillMove(int adReason, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(dispid=16, type=METHOD, name="MoveComplete")
      @com.parameters([in,type=I4] adReason, [in,type=DISPATCH] pError, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pRecordset) */
  public void MoveComplete(int adReason, msado15.Error pError, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(dispid=17, type=METHOD, name="EndOfRecordset")
      @com.parameters([in,out,elementType=BOOLEAN,type=ARRAY] fMoreData, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pRecordset) */
  public void EndOfRecordset(boolean[] fMoreData, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(dispid=18, type=METHOD, name="FetchProgress")
      @com.parameters([in,type=I4] Progress, [in,type=I4] MaxProgress, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pRecordset) */
  public void FetchProgress(int Progress, int MaxProgress, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(dispid=19, type=METHOD, name="FetchComplete")
      @com.parameters([in,type=DISPATCH] pError, [in,out,elementType=I4,type=PTR] adStatus, [in,type=DISPATCH] pRecordset) */
  public void FetchComplete(msado15.Error pError, int[] adStatus, msado15._Recordset pRecordset);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x266, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
