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

// Dual interface Property
/** @com.interface(iid=00000503-0000-0010-8000-00AA006D2EA4, thread=AUTO, type=DUAL) */
public interface Property extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=0, type=PROPGET, name="Value", name2="getValue", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getValue();

  /** @com.method(vtoffset=5, dispid=0, type=PROPPUT, name="Value", name2="putValue", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] pval) */
  public void setValue(Variant pval);

  /** @com.method(vtoffset=6, dispid=1610743810, type=PROPGET, name="Name", name2="getName", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getName();

  /** @com.method(vtoffset=7, dispid=1610743811, type=PROPGET, name="Type", name2="getType", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getType();

  /** @com.method(vtoffset=8, dispid=1610743812, type=PROPGET, name="Attributes", name2="getAttributes", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getAttributes();

  /** @com.method(vtoffset=9, dispid=1610743812, type=PROPPUT, name="Attributes", name2="putAttributes", addFlagsVtable=4)
      @com.parameters([in,type=I4] plAttributes) */
  public void setAttributes(int plAttributes);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x503, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
