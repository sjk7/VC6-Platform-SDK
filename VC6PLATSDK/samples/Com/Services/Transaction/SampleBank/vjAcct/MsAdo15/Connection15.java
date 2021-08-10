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

// Dual interface Connection15
/** @com.interface(iid=00000515-0000-0010-8000-00AA006D2EA4, thread=AUTO, type=DUAL) */
public interface Connection15 extends msado15._ADO
{
  /** @com.method(vtoffset=4, dispid=500, type=PROPGET, name="Properties", name2="getProperties", addFlagsVtable=4)
      @com.parameters([iid=00000504-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15.Properties getProperties();

  /** @com.method(vtoffset=5, dispid=0, type=PROPGET, name="ConnectionString", name2="getConnectionString", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getConnectionString();

  /** @com.method(vtoffset=6, dispid=0, type=PROPPUT, name="ConnectionString", name2="putConnectionString", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pbstr) */
  public void setConnectionString(String pbstr);

  /** @com.method(vtoffset=7, dispid=2, type=PROPGET, name="CommandTimeout", name2="getCommandTimeout", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getCommandTimeout();

  /** @com.method(vtoffset=8, dispid=2, type=PROPPUT, name="CommandTimeout", name2="putCommandTimeout", addFlagsVtable=4)
      @com.parameters([in,type=I4] plTimeout) */
  public void setCommandTimeout(int plTimeout);

  /** @com.method(vtoffset=9, dispid=3, type=PROPGET, name="ConnectionTimeout", name2="getConnectionTimeout", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getConnectionTimeout();

  /** @com.method(vtoffset=10, dispid=3, type=PROPPUT, name="ConnectionTimeout", name2="putConnectionTimeout", addFlagsVtable=4)
      @com.parameters([in,type=I4] plTimeout) */
  public void setConnectionTimeout(int plTimeout);

  /** @com.method(vtoffset=11, dispid=4, type=PROPGET, name="Version", name2="getVersion", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getVersion();

  /** @com.method(vtoffset=12, dispid=5, type=METHOD, name="Close", addFlagsVtable=4)
      @com.parameters() */
  public void Close();

  /** @com.method(vtoffset=13, dispid=6, type=METHOD, name="Execute", addFlagsVtable=4)
      @com.parameters([in,type=STRING] CommandText, [out,elementType=VARIANT,type=PTR] RecordsAffected, [in,type=I4] Options, [iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15._Recordset Execute(String CommandText, Variant RecordsAffected, int Options);

  /** @com.method(vtoffset=14, dispid=7, type=METHOD, name="BeginTrans", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int BeginTrans();

  /** @com.method(vtoffset=15, dispid=8, type=METHOD, name="CommitTrans", addFlagsVtable=4)
      @com.parameters() */
  public void CommitTrans();

  /** @com.method(vtoffset=16, dispid=9, type=METHOD, name="RollbackTrans", addFlagsVtable=4)
      @com.parameters() */
  public void RollbackTrans();

  /** @com.method(vtoffset=17, dispid=10, type=METHOD, name="Open", addFlagsVtable=4)
      @com.parameters([in,type=STRING] ConnectionString, [in,type=STRING] UserID, [in,type=STRING] Password, [in,type=I4] Options) */
  public void Open(String ConnectionString, String UserID, String Password, int Options);

  /** @com.method(vtoffset=18, dispid=11, type=PROPGET, name="Errors", name2="getErrors", addFlagsVtable=4)
      @com.parameters([iid=00000501-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15.Errors getErrors();

  /** @com.method(vtoffset=19, dispid=12, type=PROPGET, name="DefaultDatabase", name2="getDefaultDatabase", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getDefaultDatabase();

  /** @com.method(vtoffset=20, dispid=12, type=PROPPUT, name="DefaultDatabase", name2="putDefaultDatabase", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pbstr) */
  public void setDefaultDatabase(String pbstr);

  /** @com.method(vtoffset=21, dispid=13, type=PROPGET, name="IsolationLevel", name2="getIsolationLevel", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getIsolationLevel();

  /** @com.method(vtoffset=22, dispid=13, type=PROPPUT, name="IsolationLevel", name2="putIsolationLevel", addFlagsVtable=4)
      @com.parameters([in,type=I4] Level) */
  public void setIsolationLevel(int Level);

  /** @com.method(vtoffset=23, dispid=14, type=PROPGET, name="Attributes", name2="getAttributes", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getAttributes();

  /** @com.method(vtoffset=24, dispid=14, type=PROPPUT, name="Attributes", name2="putAttributes", addFlagsVtable=4)
      @com.parameters([in,type=I4] plAttr) */
  public void setAttributes(int plAttr);

  /** @com.method(vtoffset=25, dispid=15, type=PROPGET, name="CursorLocation", name2="getCursorLocation", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getCursorLocation();

  /** @com.method(vtoffset=26, dispid=15, type=PROPPUT, name="CursorLocation", name2="putCursorLocation", addFlagsVtable=4)
      @com.parameters([in,type=I4] plCursorLoc) */
  public void setCursorLocation(int plCursorLoc);

  /** @com.method(vtoffset=27, dispid=16, type=PROPGET, name="Mode", name2="getMode", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getMode();

  /** @com.method(vtoffset=28, dispid=16, type=PROPPUT, name="Mode", name2="putMode", addFlagsVtable=4)
      @com.parameters([in,type=I4] plMode) */
  public void setMode(int plMode);

  /** @com.method(vtoffset=29, dispid=17, type=PROPGET, name="Provider", name2="getProvider", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getProvider();

  /** @com.method(vtoffset=30, dispid=17, type=PROPPUT, name="Provider", name2="putProvider", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pbstr) */
  public void setProvider(String pbstr);

  /** @com.method(vtoffset=31, dispid=18, type=PROPGET, name="State", name2="getState", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getState();

  /** @com.method(vtoffset=32, dispid=19, type=METHOD, name="OpenSchema", addFlagsVtable=4)
      @com.parameters([in,type=I4] Schema, [in,type=VARIANT] Restrictions, [in,type=VARIANT] SchemaID, [iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15._Recordset OpenSchema(int Schema, Variant Restrictions, Variant SchemaID);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x515, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
