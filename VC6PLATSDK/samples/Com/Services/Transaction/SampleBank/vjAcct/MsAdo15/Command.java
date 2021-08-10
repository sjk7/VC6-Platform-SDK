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

/** @com.class(classid=00000507-0000-0010-8000-00AA006D2EA4,DynamicCasts) 
    @com.interface(iid=0000054E-0000-0010-8000-00AA006D2EA4, thread=AUTO, type=DUAL) */
public class Command implements IUnknown,com.ms.com.NoAutoScripting,msado15._Command
{
  /** @com.method(vtoffset=4, dispid=500, type=PROPGET, name="Properties", name2="getProperties", addFlagsVtable=4)
      @com.parameters([iid=00000504-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public native msado15.Properties getProperties();

  /** @com.method(vtoffset=5, dispid=1610809344, type=PROPGET, name="ActiveConnection", name2="getActiveConnection", addFlagsVtable=4)
      @com.parameters([iid=00000550-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public native msado15._Connection getActiveConnection();

  /** @com.method(vtoffset=6, dispid=1610809344, type=PROPPUTREF, name="ActiveConnection", name2="putActiveConnection", addFlagsVtable=4)
      @com.parameters([in,iid=00000550-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] ppvObject) */
  public native void setActiveConnection(msado15._Connection ppvObject);

  /** @com.method(vtoffset=7, dispid=1610809344, type=PROPPUT, name="ActiveConnection", name2="putActiveConnection", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] ppvObject) */
  public native void setActiveConnection(Variant ppvObject);

  /** @com.method(vtoffset=8, dispid=1610809347, type=PROPGET, name="CommandText", name2="getCommandText", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public native String getCommandText();

  /** @com.method(vtoffset=9, dispid=1610809347, type=PROPPUT, name="CommandText", name2="putCommandText", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pbstr) */
  public native void setCommandText(String pbstr);

  /** @com.method(vtoffset=10, dispid=1610809349, type=PROPGET, name="CommandTimeout", name2="getCommandTimeout", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int getCommandTimeout();

  /** @com.method(vtoffset=11, dispid=1610809349, type=PROPPUT, name="CommandTimeout", name2="putCommandTimeout", addFlagsVtable=4)
      @com.parameters([in,type=I4] pl) */
  public native void setCommandTimeout(int pl);

  /** @com.method(vtoffset=12, dispid=1610809351, type=PROPGET, name="Prepared", name2="getPrepared", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public native boolean getPrepared();

  /** @com.method(vtoffset=13, dispid=1610809351, type=PROPPUT, name="Prepared", name2="putPrepared", addFlagsVtable=4)
      @com.parameters([in,type=BOOLEAN] pfPrepared) */
  public native void setPrepared(boolean pfPrepared);

  /** @com.method(vtoffset=14, dispid=1610809353, type=METHOD, name="Execute", addFlagsVtable=4)
      @com.parameters([out,elementType=VARIANT,type=PTR] RecordsAffected, [in,elementType=VARIANT,type=PTR] Parameters, [in,type=I4] Options, [iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public native msado15._Recordset Execute(Variant RecordsAffected, Variant Parameters, int Options);

  /** @com.method(vtoffset=15, dispid=1610809354, type=METHOD, name="CreateParameter", addFlagsVtable=4)
      @com.parameters([in,type=STRING] Name, [in,type=I4] Type, [in,type=I4] Direction, [in,type=I4] Size, [in,type=VARIANT] Value, [iid=0000050C-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public native msado15._Parameter CreateParameter(String Name, int Type, int Direction, int Size, Variant Value);

  /** @com.method(vtoffset=16, dispid=0, type=PROPGET, name="Parameters", name2="getParameters", addFlagsVtable=4)
      @com.parameters([iid=0000050D-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public native msado15.Parameters getParameters();

  /** @com.method(vtoffset=17, dispid=1610809356, type=PROPPUT, name="CommandType", name2="putCommandType", addFlagsVtable=4)
      @com.parameters([in,type=I4] plCmdType) */
  public native void setCommandType(int plCmdType);

  /** @com.method(vtoffset=18, dispid=1610809356, type=PROPGET, name="CommandType", name2="getCommandType", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int getCommandType();

  /** @com.method(vtoffset=19, dispid=1610809358, type=PROPGET, name="Name", name2="getName", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public native String getName();

  /** @com.method(vtoffset=20, dispid=1610809358, type=PROPPUT, name="Name", name2="putName", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pbstrName) */
  public native void setName(String pbstrName);

  /** @com.method(vtoffset=21, dispid=1610874880, type=PROPGET, name="State", name2="getState", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int getState();

  /** @com.method(vtoffset=22, dispid=1610874881, type=METHOD, name="Cancel", addFlagsVtable=4)
      @com.parameters() */
  public native void Cancel();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x54e, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);

  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0x507, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
