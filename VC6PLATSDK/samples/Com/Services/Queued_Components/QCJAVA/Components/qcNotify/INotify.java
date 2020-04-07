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

// Dual interface INotify
/** @com.interface(iid=6DD1E6EF-28C1-11D2-B5B6-00C04FC340EE, thread=AUTO, type=DUAL) */
public interface INotify extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1, type=PROPPUT, name="CustomerId", name2="putCustomerId", addFlagsVtable=4)
      @com.parameters([in,type=I4] _jcomparam_0) */
  public void setCustomerId(int _jcomparam_0);

  /** @com.method(vtoffset=5, dispid=2, type=PROPPUT, name="OrderId", name2="putOrderId", addFlagsVtable=4)
      @com.parameters([in,type=I4] _jcomparam_0) */
  public void setOrderId(int _jcomparam_0);

  /** @com.method(vtoffset=6, dispid=3, type=METHOD, name="LineItem", addFlagsVtable=4)
      @com.parameters([in,type=I4] lItemId, [in,type=I4] lQuantity, [in,type=I4] ShipStatus) */
  public void LineItem(int lItemId, int lQuantity, int ShipStatus);

  /** @com.method(vtoffset=7, dispid=4, type=METHOD, name="Process", addFlagsVtable=4)
      @com.parameters([in,type=I4] lFlags) */
  public void Process(int lFlags);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x6dd1e6ef, (short)0x28c1, (short)0x11d2, (byte)0xb5, (byte)0xb6, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0xc3, (byte)0x40, (byte)0xee);
}
