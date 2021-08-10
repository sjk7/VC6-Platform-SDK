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

// Dual interface _Record
/** @com.interface(iid=00000562-0000-0010-8000-00AA006D2EA4, thread=AUTO, type=DUAL) */
public interface _Record extends msado15._ADO
{
  /** @com.method(vtoffset=4, dispid=500, type=PROPGET, name="Properties", name2="getProperties", addFlagsVtable=4)
      @com.parameters([iid=00000504-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15.Properties getProperties();

  /** @com.method(vtoffset=5, dispid=1, type=PROPGET, name="ActiveConnection", name2="getActiveConnection", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getActiveConnection();

  /** @com.method(vtoffset=6, dispid=1, type=PROPPUT, name="ActiveConnection", name2="putActiveConnection", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pvar) */
  public void setActiveConnection(String pvar);

  /** @com.method(vtoffset=7, dispid=1, type=PROPPUTREF, name="ActiveConnection", name2="putActiveConnection", addFlagsVtable=4)
      @com.parameters([in,iid=00000550-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] pvar) */
  public void setActiveConnection(msado15._Connection pvar);

  /** @com.method(vtoffset=8, dispid=2, type=PROPGET, name="State", name2="getState", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getState();

  /** @com.method(vtoffset=9, dispid=3, type=PROPGET, name="Source", name2="getSource", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getSource();

  /** @com.method(vtoffset=10, dispid=3, type=PROPPUT, name="Source", name2="putSource", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pvar) */
  public void setSource(String pvar);

  /** @com.method(vtoffset=11, dispid=3, type=PROPPUTREF, name="Source", name2="putSource", addFlagsVtable=4)
      @com.parameters([in,iid=00020400-0000-0000-C000-000000000046,thread=AUTO,type=DISPATCH] pvar) */
  public void setSource(Object pvar);

  /** @com.method(vtoffset=12, dispid=4, type=PROPGET, name="Mode", name2="getMode", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getMode();

  /** @com.method(vtoffset=13, dispid=4, type=PROPPUT, name="Mode", name2="putMode", addFlagsVtable=4)
      @com.parameters([in,type=I4] pMode) */
  public void setMode(int pMode);

  /** @com.method(vtoffset=14, dispid=5, type=PROPGET, name="ParentURL", name2="getParentURL", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getParentURL();

  /** @com.method(vtoffset=15, dispid=6, type=METHOD, name="MoveRecord", addFlagsVtable=4)
      @com.parameters([in,type=STRING] Source, [in,type=STRING] Destination, [in,type=STRING] UserName, [in,type=STRING] Password, [in,type=I4] Options, [in,type=BOOLEAN] Async, [type=STRING] return) */
  public String MoveRecord(String Source, String Destination, String UserName, String Password, int Options, boolean Async);

  /** @com.method(vtoffset=16, dispid=7, type=METHOD, name="CopyRecord", addFlagsVtable=4)
      @com.parameters([in,type=STRING] Source, [in,type=STRING] Destination, [in,type=STRING] UserName, [in,type=STRING] Password, [in,type=I4] Options, [in,type=BOOLEAN] Async, [type=STRING] return) */
  public String CopyRecord(String Source, String Destination, String UserName, String Password, int Options, boolean Async);

  /** @com.method(vtoffset=17, dispid=8, type=METHOD, name="DeleteRecord", addFlagsVtable=4)
      @com.parameters([in,type=STRING] Source, [in,type=BOOLEAN] Async) */
  public void DeleteRecord(String Source, boolean Async);

  /** @com.method(vtoffset=18, dispid=9, type=METHOD, name="Open", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Source, [in,type=VARIANT] ActiveConnection, [in,type=I4] Mode, [in,type=I4] CreateOptions, [in,type=I4] Options, [in,type=STRING] UserName, [in,type=STRING] Password) */
  public void Open(Variant Source, Variant ActiveConnection, int Mode, int CreateOptions, int Options, String UserName, String Password);

  /** @com.method(vtoffset=19, dispid=10, type=METHOD, name="Close", addFlagsVtable=4)
      @com.parameters() */
  public void Close();

  /** @com.method(vtoffset=20, dispid=0, type=PROPGET, name="Fields", name2="getFields", addFlagsVtable=4)
      @com.parameters([iid=00000564-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15.Fields getFields();

  /** @com.method(vtoffset=21, dispid=11, type=PROPGET, name="RecordType", name2="getRecordType", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getRecordType();

  /** @com.method(vtoffset=22, dispid=12, type=METHOD, name="GetChildren", addFlagsVtable=4)
      @com.parameters([iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15._Recordset GetChildren();

  /** @com.method(vtoffset=23, dispid=13, type=METHOD, name="Cancel", addFlagsVtable=4)
      @com.parameters() */
  public void Cancel();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x562, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
