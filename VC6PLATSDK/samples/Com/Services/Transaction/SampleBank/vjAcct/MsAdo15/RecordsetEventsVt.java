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

// VTable-only interface RecordsetEventsVt
/** @com.interface(iid=00000403-0000-0010-8000-00AA006D2EA4, thread=AUTO) */
public interface RecordsetEventsVt extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=I4] cFields, [in,type=VARIANT] Fields, [in,out,type=PTR] adStatus, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset) */
  public void WillChangeField(int cFields, Variant Fields, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=I4] cFields, [in,type=VARIANT] Fields, [in,iid=00000500-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pError, [in,out,type=PTR] adStatus, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset) */
  public void FieldChangeComplete(int cFields, Variant Fields, msado15.Error pError, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=I4] adReason, [in,type=I4] cRecords, [in,out,type=PTR] adStatus, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset) */
  public void WillChangeRecord(int adReason, int cRecords, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([in,type=I4] adReason, [in,type=I4] cRecords, [in,iid=00000500-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pError, [in,out,type=PTR] adStatus, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset) */
  public void RecordChangeComplete(int adReason, int cRecords, msado15.Error pError, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters([in,type=I4] adReason, [in,out,type=PTR] adStatus, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset) */
  public void WillChangeRecordset(int adReason, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(vtoffset=5, addFlagsVtable=4)
      @com.parameters([in,type=I4] adReason, [in,iid=00000500-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pError, [in,out,type=PTR] adStatus, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset) */
  public void RecordsetChangeComplete(int adReason, msado15.Error pError, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(vtoffset=6, addFlagsVtable=4)
      @com.parameters([in,type=I4] adReason, [in,out,type=PTR] adStatus, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset) */
  public void WillMove(int adReason, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(vtoffset=7, addFlagsVtable=4)
      @com.parameters([in,type=I4] adReason, [in,iid=00000500-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pError, [in,out,type=PTR] adStatus, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset) */
  public void MoveComplete(int adReason, msado15.Error pError, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(vtoffset=8, addFlagsVtable=4)
      @com.parameters([in,out,size=1,type=ARRAY] fMoreData, [in,out,type=PTR] adStatus, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset) */
  public void EndOfRecordset(boolean[] fMoreData, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(vtoffset=9, addFlagsVtable=4)
      @com.parameters([in,type=I4] Progress, [in,type=I4] MaxProgress, [in,out,type=PTR] adStatus, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset) */
  public void FetchProgress(int Progress, int MaxProgress, int[] adStatus, msado15._Recordset pRecordset);

  /** @com.method(vtoffset=10, addFlagsVtable=4)
      @com.parameters([in,iid=00000500-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pError, [in,out,type=PTR] adStatus, [in,iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pRecordset) */
  public void FetchComplete(msado15.Error pError, int[] adStatus, msado15._Recordset pRecordset);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x403, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
