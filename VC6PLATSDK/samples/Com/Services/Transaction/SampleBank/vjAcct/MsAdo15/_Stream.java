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

// Dual interface _Stream
/** @com.interface(iid=00000565-0000-0010-8000-00AA006D2EA4, thread=AUTO, type=DUAL) */
public interface _Stream extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1, type=PROPGET, name="Size", name2="getSize", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getSize();

  /** @com.method(vtoffset=5, dispid=2, type=PROPGET, name="EOS", name2="getEOS", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public boolean getEOS();

  /** @com.method(vtoffset=6, dispid=3, type=PROPGET, name="Position", name2="getPosition", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getPosition();

  /** @com.method(vtoffset=7, dispid=3, type=PROPPUT, name="Position", name2="putPosition", addFlagsVtable=4)
      @com.parameters([in,type=I4] pPos) */
  public void setPosition(int pPos);

  /** @com.method(vtoffset=8, dispid=4, type=PROPGET, name="Type", name2="getType", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getType();

  /** @com.method(vtoffset=9, dispid=4, type=PROPPUT, name="Type", name2="putType", addFlagsVtable=4)
      @com.parameters([in,type=I4] ptype) */
  public void setType(int ptype);

  /** @com.method(vtoffset=10, dispid=5, type=PROPGET, name="LineSeparator", name2="getLineSeparator", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getLineSeparator();

  /** @com.method(vtoffset=11, dispid=5, type=PROPPUT, name="LineSeparator", name2="putLineSeparator", addFlagsVtable=4)
      @com.parameters([in,type=I4] pLS) */
  public void setLineSeparator(int pLS);

  /** @com.method(vtoffset=12, dispid=6, type=PROPGET, name="State", name2="getState", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getState();

  /** @com.method(vtoffset=13, dispid=7, type=PROPGET, name="Mode", name2="getMode", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getMode();

  /** @com.method(vtoffset=14, dispid=7, type=PROPPUT, name="Mode", name2="putMode", addFlagsVtable=4)
      @com.parameters([in,type=I4] pMode) */
  public void setMode(int pMode);

  /** @com.method(vtoffset=15, dispid=8, type=PROPGET, name="Charset", name2="getCharset", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getCharset();

  /** @com.method(vtoffset=16, dispid=8, type=PROPPUT, name="Charset", name2="putCharset", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pbstrCharset) */
  public void setCharset(String pbstrCharset);

  /** @com.method(vtoffset=17, dispid=9, type=METHOD, name="Read", addFlagsVtable=4)
      @com.parameters([in,type=I4] NumBytes, [type=VARIANT] return) */
  public Variant Read(int NumBytes);

  /** @com.method(vtoffset=18, dispid=10, type=METHOD, name="Open", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Source, [in,type=I4] Mode, [in,type=I4] Options, [in,type=STRING] UserName, [in,type=STRING] Password) */
  public void Open(Variant Source, int Mode, int Options, String UserName, String Password);

  /** @com.method(vtoffset=19, dispid=11, type=METHOD, name="Close", addFlagsVtable=4)
      @com.parameters() */
  public void Close();

  /** @com.method(vtoffset=20, dispid=12, type=METHOD, name="SkipLine", addFlagsVtable=4)
      @com.parameters() */
  public void SkipLine();

  /** @com.method(vtoffset=21, dispid=13, type=METHOD, name="Write", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Buffer) */
  public void Write(Variant Buffer);

  /** @com.method(vtoffset=22, dispid=14, type=METHOD, name="SetEOS", addFlagsVtable=4)
      @com.parameters() */
  public void SetEOS();

  /** @com.method(vtoffset=23, dispid=15, type=METHOD, name="CopyTo", addFlagsVtable=4)
      @com.parameters([in,iid=00000565-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] DestStream, [in,type=I4] CharNumber) */
  public void CopyTo(msado15._Stream DestStream, int CharNumber);

  /** @com.method(vtoffset=24, dispid=16, type=METHOD, name="Flush", addFlagsVtable=4)
      @com.parameters() */
  public void Flush();

  /** @com.method(vtoffset=25, dispid=17, type=METHOD, name="SaveToFile", addFlagsVtable=4)
      @com.parameters([in,type=STRING] FileName, [in,type=I4] Options) */
  public void SaveToFile(String FileName, int Options);

  /** @com.method(vtoffset=26, dispid=18, type=METHOD, name="LoadFromFile", addFlagsVtable=4)
      @com.parameters([in,type=STRING] FileName) */
  public void LoadFromFile(String FileName);

  /** @com.method(vtoffset=27, dispid=19, type=METHOD, name="ReadText", addFlagsVtable=4)
      @com.parameters([in,type=I4] NumChars, [type=STRING] return) */
  public String ReadText(int NumChars);

  /** @com.method(vtoffset=28, dispid=20, type=METHOD, name="WriteText", addFlagsVtable=4)
      @com.parameters([in,type=STRING] Data, [in,type=I4] Options) */
  public void WriteText(String Data, int Options);

  /** @com.method(vtoffset=29, dispid=21, type=METHOD, name="Cancel", addFlagsVtable=4)
      @com.parameters() */
  public void Cancel();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x565, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
