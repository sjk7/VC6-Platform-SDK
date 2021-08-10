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

/** @com.class(classid=0000050B-0000-0010-8000-00AA006D2EA4,DynamicCasts) 
    @com.interface(iid=0000050C-0000-0010-8000-00AA006D2EA4, thread=AUTO, type=DUAL) */
public class Parameter implements IUnknown,com.ms.com.NoAutoScripting,msado15._Parameter
{
  /** @com.method(vtoffset=4, dispid=500, type=PROPGET, name="Properties", name2="getProperties", addFlagsVtable=4)
      @com.parameters([iid=00000504-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public native msado15.Properties getProperties();

  /** @com.method(vtoffset=5, dispid=1610809344, type=PROPGET, name="Name", name2="getName", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public native String getName();

  /** @com.method(vtoffset=6, dispid=1610809344, type=PROPPUT, name="Name", name2="putName", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pbstr) */
  public native void setName(String pbstr);

  /** @com.method(vtoffset=7, dispid=0, type=PROPGET, name="Value", name2="getValue", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public native Variant getValue();

  /** @com.method(vtoffset=8, dispid=0, type=PROPPUT, name="Value", name2="putValue", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] pvar) */
  public native void setValue(Variant pvar);

  /** @com.method(vtoffset=9, dispid=1610809348, type=PROPGET, name="Type", name2="getType", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int getType();

  /** @com.method(vtoffset=10, dispid=1610809348, type=PROPPUT, name="Type", name2="putType", addFlagsVtable=4)
      @com.parameters([in,type=I4] psDataType) */
  public native void setType(int psDataType);

  /** @com.method(vtoffset=11, dispid=1610809350, type=PROPPUT, name="Direction", name2="putDirection", addFlagsVtable=4)
      @com.parameters([in,type=I4] plParmDirection) */
  public native void setDirection(int plParmDirection);

  /** @com.method(vtoffset=12, dispid=1610809350, type=PROPGET, name="Direction", name2="getDirection", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int getDirection();

  /** @com.method(vtoffset=13, dispid=1610809352, type=PROPPUT, name="Precision", name2="putPrecision", addFlagsVtable=4)
      @com.parameters([in,type=U1] pbPrecision) */
  public native void setPrecision(byte pbPrecision);

  /** @com.method(vtoffset=14, dispid=1610809352, type=PROPGET, name="Precision", name2="getPrecision", addFlagsVtable=4)
      @com.parameters([type=U1] return) */
  public native byte getPrecision();

  /** @com.method(vtoffset=15, dispid=1610809354, type=PROPPUT, name="NumericScale", name2="putNumericScale", addFlagsVtable=4)
      @com.parameters([in,type=U1] pbScale) */
  public native void setNumericScale(byte pbScale);

  /** @com.method(vtoffset=16, dispid=1610809354, type=PROPGET, name="NumericScale", name2="getNumericScale", addFlagsVtable=4)
      @com.parameters([type=U1] return) */
  public native byte getNumericScale();

  /** @com.method(vtoffset=17, dispid=1610809356, type=PROPPUT, name="Size", name2="putSize", addFlagsVtable=4)
      @com.parameters([in,type=I4] pl) */
  public native void setSize(int pl);

  /** @com.method(vtoffset=18, dispid=1610809356, type=PROPGET, name="Size", name2="getSize", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int getSize();

  /** @com.method(vtoffset=19, dispid=1610809358, type=METHOD, name="AppendChunk", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Val) */
  public native void AppendChunk(Variant Val);

  /** @com.method(vtoffset=20, dispid=1610809359, type=PROPGET, name="Attributes", name2="getAttributes", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int getAttributes();

  /** @com.method(vtoffset=21, dispid=1610809359, type=PROPPUT, name="Attributes", name2="putAttributes", addFlagsVtable=4)
      @com.parameters([in,type=I4] plParmAttribs) */
  public native void setAttributes(int plParmAttribs);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x50c, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);

  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0x50b, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
