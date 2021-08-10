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

// Dual interface Recordset21
/** @com.interface(iid=00000555-0000-0010-8000-00AA006D2EA4, thread=AUTO, type=DUAL) */
public interface Recordset21 extends msado15.Recordset20
{
  /** @com.method(vtoffset=4, dispid=500, type=PROPGET, name="Properties", name2="getProperties", addFlagsVtable=4)
      @com.parameters([iid=00000504-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15.Properties getProperties();

  /** @com.method(vtoffset=5, dispid=1000, type=PROPGET, name="AbsolutePosition", name2="getAbsolutePosition", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getAbsolutePosition();

  /** @com.method(vtoffset=6, dispid=1000, type=PROPPUT, name="AbsolutePosition", name2="putAbsolutePosition", addFlagsVtable=4)
      @com.parameters([in,type=I4] pl) */
  public void setAbsolutePosition(int pl);

  /** @com.method(vtoffset=7, dispid=1001, type=PROPPUTREF, name="ActiveConnection", name2="putActiveConnection", addFlagsVtable=4)
      @com.parameters([in,iid=00020400-0000-0000-C000-000000000046,thread=AUTO,type=DISPATCH] pvar) */
  public void setActiveConnection(Object pvar);

  /** @com.method(vtoffset=8, dispid=1001, type=PROPPUT, name="ActiveConnection", name2="putActiveConnection", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] pvar) */
  public void setActiveConnection(Variant pvar);

  /** @com.method(vtoffset=9, dispid=1001, type=PROPGET, name="ActiveConnection", name2="getActiveConnection", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getActiveConnection();

  /** @com.method(vtoffset=10, dispid=1002, type=PROPGET, name="BOF", name2="getBOF", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public boolean getBOF();

  /** @com.method(vtoffset=11, dispid=1003, type=PROPGET, name="Bookmark", name2="getBookmark", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getBookmark();

  /** @com.method(vtoffset=12, dispid=1003, type=PROPPUT, name="Bookmark", name2="putBookmark", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] pvBookmark) */
  public void setBookmark(Variant pvBookmark);

  /** @com.method(vtoffset=13, dispid=1004, type=PROPGET, name="CacheSize", name2="getCacheSize", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getCacheSize();

  /** @com.method(vtoffset=14, dispid=1004, type=PROPPUT, name="CacheSize", name2="putCacheSize", addFlagsVtable=4)
      @com.parameters([in,type=I4] pl) */
  public void setCacheSize(int pl);

  /** @com.method(vtoffset=15, dispid=1005, type=PROPGET, name="CursorType", name2="getCursorType", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getCursorType();

  /** @com.method(vtoffset=16, dispid=1005, type=PROPPUT, name="CursorType", name2="putCursorType", addFlagsVtable=4)
      @com.parameters([in,type=I4] plCursorType) */
  public void setCursorType(int plCursorType);

  /** @com.method(vtoffset=17, dispid=1006, type=PROPGET, name="EOF", name2="getEOF", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public boolean getEOF();

  /** @com.method(vtoffset=18, dispid=0, type=PROPGET, name="Fields", name2="getFields", addFlagsVtable=4)
      @com.parameters([iid=00000564-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15.Fields getFields();

  /** @com.method(vtoffset=19, dispid=1008, type=PROPGET, name="LockType", name2="getLockType", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getLockType();

  /** @com.method(vtoffset=20, dispid=1008, type=PROPPUT, name="LockType", name2="putLockType", addFlagsVtable=4)
      @com.parameters([in,type=I4] plLockType) */
  public void setLockType(int plLockType);

  /** @com.method(vtoffset=21, dispid=1009, type=PROPGET, name="MaxRecords", name2="getMaxRecords", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getMaxRecords();

  /** @com.method(vtoffset=22, dispid=1009, type=PROPPUT, name="MaxRecords", name2="putMaxRecords", addFlagsVtable=4)
      @com.parameters([in,type=I4] plMaxRecords) */
  public void setMaxRecords(int plMaxRecords);

  /** @com.method(vtoffset=23, dispid=1010, type=PROPGET, name="RecordCount", name2="getRecordCount", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getRecordCount();

  /** @com.method(vtoffset=24, dispid=1011, type=PROPPUTREF, name="Source", name2="putSource", addFlagsVtable=4)
      @com.parameters([in,iid=00020400-0000-0000-C000-000000000046,thread=AUTO,type=DISPATCH] pvSource) */
  public void setSource(Object pvSource);

  /** @com.method(vtoffset=25, dispid=1011, type=PROPPUT, name="Source", name2="putSource", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pvSource) */
  public void setSource(String pvSource);

  /** @com.method(vtoffset=26, dispid=1011, type=PROPGET, name="Source", name2="getSource", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getSource();

  /** @com.method(vtoffset=27, dispid=1012, type=METHOD, name="AddNew", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] FieldList, [in,type=VARIANT] Values) */
  public void AddNew(Variant FieldList, Variant Values);

  /** @com.method(vtoffset=28, dispid=1013, type=METHOD, name="CancelUpdate", addFlagsVtable=4)
      @com.parameters() */
  public void CancelUpdate();

  /** @com.method(vtoffset=29, dispid=1014, type=METHOD, name="Close", addFlagsVtable=4)
      @com.parameters() */
  public void Close();

  /** @com.method(vtoffset=30, dispid=1015, type=METHOD, name="Delete", addFlagsVtable=4)
      @com.parameters([in,type=I4] AffectRecords) */
  public void Delete(int AffectRecords);

  /** @com.method(vtoffset=31, dispid=1016, type=METHOD, name="GetRows", addFlagsVtable=4)
      @com.parameters([in,type=I4] Rows, [in,type=VARIANT] Start, [in,type=VARIANT] Fields, [type=VARIANT] return) */
  public Variant GetRows(int Rows, Variant Start, Variant Fields);

  /** @com.method(vtoffset=32, dispid=1017, type=METHOD, name="Move", addFlagsVtable=4)
      @com.parameters([in,type=I4] NumRecords, [in,type=VARIANT] Start) */
  public void Move(int NumRecords, Variant Start);

  /** @com.method(vtoffset=33, dispid=1018, type=METHOD, name="MoveNext", addFlagsVtable=4)
      @com.parameters() */
  public void MoveNext();

  /** @com.method(vtoffset=34, dispid=1019, type=METHOD, name="MovePrevious", addFlagsVtable=4)
      @com.parameters() */
  public void MovePrevious();

  /** @com.method(vtoffset=35, dispid=1020, type=METHOD, name="MoveFirst", addFlagsVtable=4)
      @com.parameters() */
  public void MoveFirst();

  /** @com.method(vtoffset=36, dispid=1021, type=METHOD, name="MoveLast", addFlagsVtable=4)
      @com.parameters() */
  public void MoveLast();

  /** @com.method(vtoffset=37, dispid=1022, type=METHOD, name="Open", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Source, [in,type=VARIANT] ActiveConnection, [in,type=I4] CursorType, [in,type=I4] LockType, [in,type=I4] Options) */
  public void Open(Variant Source, Variant ActiveConnection, int CursorType, int LockType, int Options);

  /** @com.method(vtoffset=38, dispid=1023, type=METHOD, name="Requery", addFlagsVtable=4)
      @com.parameters([in,type=I4] Options) */
  public void Requery(int Options);

  /** @com.method(vtoffset=39, dispid=1610809378, type=METHOD, name="_xResync", addFlagsVtable=4)
      @com.parameters([in,type=I4] AffectRecords)
      @hidden */
  public void _xResync(int AffectRecords);

  /** @com.method(vtoffset=40, dispid=1025, type=METHOD, name="Update", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Fields, [in,type=VARIANT] Values) */
  public void Update(Variant Fields, Variant Values);

  /** @com.method(vtoffset=41, dispid=1047, type=PROPGET, name="AbsolutePage", name2="getAbsolutePage", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getAbsolutePage();

  /** @com.method(vtoffset=42, dispid=1047, type=PROPPUT, name="AbsolutePage", name2="putAbsolutePage", addFlagsVtable=4)
      @com.parameters([in,type=I4] pl) */
  public void setAbsolutePage(int pl);

  /** @com.method(vtoffset=43, dispid=1026, type=PROPGET, name="EditMode", name2="getEditMode", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getEditMode();

  /** @com.method(vtoffset=44, dispid=1030, type=PROPGET, name="Filter", name2="getFilter", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getFilter();

  /** @com.method(vtoffset=45, dispid=1030, type=PROPPUT, name="Filter", name2="putFilter", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Criteria) */
  public void setFilter(Variant Criteria);

  /** @com.method(vtoffset=46, dispid=1050, type=PROPGET, name="PageCount", name2="getPageCount", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getPageCount();

  /** @com.method(vtoffset=47, dispid=1048, type=PROPGET, name="PageSize", name2="getPageSize", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getPageSize();

  /** @com.method(vtoffset=48, dispid=1048, type=PROPPUT, name="PageSize", name2="putPageSize", addFlagsVtable=4)
      @com.parameters([in,type=I4] pl) */
  public void setPageSize(int pl);

  /** @com.method(vtoffset=49, dispid=1031, type=PROPGET, name="Sort", name2="getSort", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getSort();

  /** @com.method(vtoffset=50, dispid=1031, type=PROPPUT, name="Sort", name2="putSort", addFlagsVtable=4)
      @com.parameters([in,type=STRING] Criteria) */
  public void setSort(String Criteria);

  /** @com.method(vtoffset=51, dispid=1029, type=PROPGET, name="Status", name2="getStatus", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getStatus();

  /** @com.method(vtoffset=52, dispid=1054, type=PROPGET, name="State", name2="getState", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getState();

  /** @com.method(vtoffset=53, dispid=1610809392, type=METHOD, name="_xClone", addFlagsVtable=4)
      @com.parameters([iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return)
      @hidden */
  public msado15._Recordset _xClone();

  /** @com.method(vtoffset=54, dispid=1035, type=METHOD, name="UpdateBatch", addFlagsVtable=4)
      @com.parameters([in,type=I4] AffectRecords) */
  public void UpdateBatch(int AffectRecords);

  /** @com.method(vtoffset=55, dispid=1049, type=METHOD, name="CancelBatch", addFlagsVtable=4)
      @com.parameters([in,type=I4] AffectRecords) */
  public void CancelBatch(int AffectRecords);

  /** @com.method(vtoffset=56, dispid=1051, type=PROPGET, name="CursorLocation", name2="getCursorLocation", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getCursorLocation();

  /** @com.method(vtoffset=57, dispid=1051, type=PROPPUT, name="CursorLocation", name2="putCursorLocation", addFlagsVtable=4)
      @com.parameters([in,type=I4] plCursorLoc) */
  public void setCursorLocation(int plCursorLoc);

  /** @com.method(vtoffset=58, dispid=1052, type=METHOD, name="NextRecordset", addFlagsVtable=4)
      @com.parameters([out,elementType=VARIANT,type=PTR] RecordsAffected, [iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15._Recordset NextRecordset(Variant RecordsAffected);

  /** @com.method(vtoffset=59, dispid=1036, type=METHOD, name="Supports", addFlagsVtable=4)
      @com.parameters([in,type=I4] CursorOptions, [type=BOOLEAN] return) */
  public boolean Supports(int CursorOptions);

  /** @com.method(vtoffset=60, dispid=4294967288, type=PROPGET, name="Collect", name2="getCollect", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Index, [type=VARIANT] return)
      @hidden */
  public Variant getCollect(Variant Index);

  /** @com.method(vtoffset=61, dispid=4294967288, type=PROPPUT, name="Collect", name2="putCollect", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Index, [in,type=VARIANT] pvar)
      @hidden */
  public void setCollect(Variant Index, Variant pvar);

  /** @com.method(vtoffset=62, dispid=1053, type=PROPGET, name="MarshalOptions", name2="getMarshalOptions", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getMarshalOptions();

  /** @com.method(vtoffset=63, dispid=1053, type=PROPPUT, name="MarshalOptions", name2="putMarshalOptions", addFlagsVtable=4)
      @com.parameters([in,type=I4] peMarshal) */
  public void setMarshalOptions(int peMarshal);

  /** @com.method(vtoffset=64, dispid=1058, type=METHOD, name="Find", addFlagsVtable=4)
      @com.parameters([in,type=STRING] Criteria, [in,type=I4] SkipRecords, [in,type=I4] SearchDirection, [in,type=VARIANT] Start) */
  public void Find(String Criteria, int SkipRecords, int SearchDirection, Variant Start);

  /** @com.method(vtoffset=65, dispid=1055, type=METHOD, name="Cancel", addFlagsVtable=4)
      @com.parameters() */
  public void Cancel();

  /** @com.method(vtoffset=66, dispid=1056, type=PROPGET, name="DataSource", name2="getDataSource", addFlagsVtable=4)
      @com.parameters([iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] return) */
  public IUnknown getDataSource();

  /** @com.method(vtoffset=67, dispid=1056, type=PROPPUTREF, name="DataSource", name2="putDataSource", addFlagsVtable=4)
      @com.parameters([in,iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] ppunkDataSource) */
  public void setDataSource(IUnknown ppunkDataSource);

  /** @com.method(vtoffset=68, dispid=1610874883, type=METHOD, name="_xSave", addFlagsVtable=4)
      @com.parameters([in,type=STRING] FileName, [in,type=I4] PersistFormat)
      @hidden */
  public void _xSave(String FileName, int PersistFormat);

  /** @com.method(vtoffset=69, dispid=1061, type=PROPGET, name="ActiveCommand", name2="getActiveCommand", addFlagsVtable=4)
      @com.parameters([iid=00020400-0000-0000-C000-000000000046,thread=AUTO,type=DISPATCH] return) */
  public Object getActiveCommand();

  /** @com.method(vtoffset=70, dispid=1063, type=PROPPUT, name="StayInSync", name2="putStayInSync", addFlagsVtable=4)
      @com.parameters([in,type=BOOLEAN] pbStayInSync) */
  public void setStayInSync(boolean pbStayInSync);

  /** @com.method(vtoffset=71, dispid=1063, type=PROPGET, name="StayInSync", name2="getStayInSync", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public boolean getStayInSync();

  /** @com.method(vtoffset=72, dispid=1062, type=METHOD, name="GetString", addFlagsVtable=4)
      @com.parameters([in,type=I4] StringFormat, [in,type=I4] NumRows, [in,type=STRING] ColumnDelimeter, [in,type=STRING] RowDelimeter, [in,type=STRING] NullExpr, [type=STRING] return) */
  public String GetString(int StringFormat, int NumRows, String ColumnDelimeter, String RowDelimeter, String NullExpr);

  /** @com.method(vtoffset=73, dispid=1064, type=PROPGET, name="DataMember", name2="getDataMember", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getDataMember();

  /** @com.method(vtoffset=74, dispid=1064, type=PROPPUT, name="DataMember", name2="putDataMember", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pbstrDataMember) */
  public void setDataMember(String pbstrDataMember);

  /** @com.method(vtoffset=75, dispid=1065, type=METHOD, name="CompareBookmarks", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Bookmark1, [in,type=VARIANT] Bookmark2, [type=I4] return) */
  public int CompareBookmarks(Variant Bookmark1, Variant Bookmark2);

  /** @com.method(vtoffset=76, dispid=1034, type=METHOD, name="Clone", addFlagsVtable=4)
      @com.parameters([in,type=I4] LockType, [iid=00000556-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15._Recordset Clone(int LockType);

  /** @com.method(vtoffset=77, dispid=1024, type=METHOD, name="Resync", addFlagsVtable=4)
      @com.parameters([in,type=I4] AffectRecords, [in,type=I4] ResyncValues) */
  public void Resync(int AffectRecords, int ResyncValues);

  /** @com.method(vtoffset=78, dispid=1066, type=METHOD, name="Seek", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] KeyValues, [in,type=I4] SeekOption) */
  public void Seek(Variant KeyValues, int SeekOption);

  /** @com.method(vtoffset=79, dispid=1067, type=PROPPUT, name="Index", name2="putIndex", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pbstrIndex) */
  public void setIndex(String pbstrIndex);

  /** @com.method(vtoffset=80, dispid=1067, type=PROPGET, name="Index", name2="getIndex", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getIndex();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x555, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
