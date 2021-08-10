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

// Dual interface Field15
/** @com.interface(iid=00000505-0000-0010-8000-00AA006D2EA4, thread=AUTO, type=DUAL) */
public interface Field15 extends msado15._ADO
{
  /** @com.method(vtoffset=4, dispid=500, type=PROPGET, name="Properties", name2="getProperties", addFlagsVtable=4)
      @com.parameters([iid=00000504-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15.Properties getProperties();

  /** @com.method(vtoffset=5, dispid=1109, type=PROPGET, name="ActualSize", name2="getActualSize", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getActualSize();

  /** @com.method(vtoffset=6, dispid=1036, type=PROPGET, name="Attributes", name2="getAttributes", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getAttributes();

  /** @com.method(vtoffset=7, dispid=1103, type=PROPGET, name="DefinedSize", name2="getDefinedSize", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getDefinedSize();

  /** @com.method(vtoffset=8, dispid=1100, type=PROPGET, name="Name", name2="getName", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getName();

  /** @com.method(vtoffset=9, dispid=1102, type=PROPGET, name="Type", name2="getType", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getType();

  /** @com.method(vtoffset=10, dispid=0, type=PROPGET, name="Value", name2="getValue", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getValue();

  /** @com.method(vtoffset=11, dispid=0, type=PROPPUT, name="Value", name2="putValue", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] pvar) */
  public void setValue(Variant pvar);

  /** @com.method(vtoffset=12, dispid=1610809351, type=PROPGET, name="Precision", name2="getPrecision", addFlagsVtable=4)
      @com.parameters([type=U1] return) */
  public byte getPrecision();

  /** @com.method(vtoffset=13, dispid=1610809352, type=PROPGET, name="NumericScale", name2="getNumericScale", addFlagsVtable=4)
      @com.parameters([type=U1] return) */
  public byte getNumericScale();

  /** @com.method(vtoffset=14, dispid=1107, type=METHOD, name="AppendChunk", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Data) */
  public void AppendChunk(Variant Data);

  /** @com.method(vtoffset=15, dispid=1108, type=METHOD, name="GetChunk", addFlagsVtable=4)
      @com.parameters([in,type=I4] Length, [type=VARIANT] return) */
  public Variant GetChunk(int Length);

  /** @com.method(vtoffset=16, dispid=1104, type=PROPGET, name="OriginalValue", name2="getOriginalValue", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getOriginalValue();

  /** @com.method(vtoffset=17, dispid=1105, type=PROPGET, name="UnderlyingValue", name2="getUnderlyingValue", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getUnderlyingValue();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x505, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
