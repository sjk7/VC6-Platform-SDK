//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("D:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /wfc  /w /xi /X:rkc /l "D:\DOCUME~1\erica\LOCALS~1\Temp\jvc19.tmp" /nologo /d "D:\mssdk\samples\Com\Services\Transaction\SampleBank\vjacct" "D:\mssdk\samples\com\Services\Transaction\SampleBank\vcacct\release\vcacct.dll")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package vcacct;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// Dual interface IUpdateReceipt
/** @com.interface(iid=A81260B7-DDC8-11D0-B5A0-00C04FB957D8, thread=AUTO, type=DUAL) */
public interface IUpdateReceipt extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1610743808, type=METHOD, name="Update", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int Update();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xa81260b7, (short)0xddc8, (short)0x11d0, (byte)0xb5, (byte)0xa0, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0xb9, (byte)0x57, (byte)0xd8);
}
