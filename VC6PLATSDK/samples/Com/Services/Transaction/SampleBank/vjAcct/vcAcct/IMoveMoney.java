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

// Dual interface IMoveMoney
/** @com.interface(iid=04CF0B77-1989-11D0-B917-0080C7394688, thread=AUTO, type=DUAL) */
public interface IMoveMoney extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1610743808, type=METHOD, name="Perform", addFlagsVtable=4)
      @com.parameters([in,type=I4] lPrimeAccount, [in,type=I4] lSecondAccount, [in,type=I4] lAmount, [in,type=I4] lTranType, [type=STRING] return) */
  public String Perform(int lPrimeAccount, int lSecondAccount, int lAmount, int lTranType);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x4cf0b77, (short)0x1989, (short)0x11d0, (byte)0xb9, (byte)0x17, (byte)0x0, (byte)0x80, (byte)0xc7, (byte)0x39, (byte)0x46, (byte)0x88);
}
