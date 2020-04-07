//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("C:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /javatlb /c2j /creg /xh /wfc  /w /xi /X:rkc /l "C:\DOCUME~1\a-sunilc\LOCALS~1\Temp\jvc2.tmp" /nologo /d "D:\ComPlusSamples\Source\LCE\PersistSubs" "D:\ComPlusSamples\Source\LCE\PersistSubs\PersistATL.tlb")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package persistatl;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// Dual interface INewsEventDefault
/** @com.interface(iid=00020400-0000-0000-C000-000000000046, thread=AUTO, type=DUAL) */
public interface INewsEventDefault extends persistatl.INewsEvent
{
  /** @com.method(vtoffset=4, dispid=1, type=METHOD, name="NewsFlash", addFlagsVtable=4)
      @com.parameters([in,type=DATE] dtTimeStamp, [in,type=STRING] Symbol, [in,type=STRING] Headline, [in,type=STRING] URL) */
  public void NewsFlash(double dtTimeStamp, String Symbol, String Headline, String URL);

  /** @com.method(vtoffset=5, dispid=2, type=METHOD, name="ShortQuote", addFlagsVtable=4)
      @com.parameters([in,type=STRING] Symbol, [in,type=R8] BidPrice, [in,type=R8] AskPrice, [in,type=DATE] LastTradeTime, [in,type=R8] LastTradePrice, [in,type=R8] NetChange, [in,type=R8] DailyHigh, [in,type=R8] DailyLow) */
  public void ShortQuote(String Symbol, double BidPrice, double AskPrice, double LastTradeTime, double LastTradePrice, double NetChange, double DailyHigh, double DailyLow);

  /** @com.method(vtoffset=6, dispid=3, type=METHOD, name="LongQuote", addFlagsVtable=4)
      @com.parameters([in,type=STRING] Symbol, [in,type=R8] BidPrice, [in,type=R8] AskPrice, [in,type=STRING] LastTradeTime, [in,type=R8] LastTradePrice, [in,type=R8] NetChange, [in,type=R8] DailyHigh, [in,type=R8] DailyLow, [in,type=I4] AskSize, [in,type=I4] BidSize, [in,type=R8] OpenPrice, [in,type=R8] ClosePrice, [in,type=STRING] CloseDate) */
  public void LongQuote(String Symbol, double BidPrice, double AskPrice, String LastTradeTime, double LastTradePrice, double NetChange, double DailyHigh, double DailyLow, int AskSize, int BidSize, double OpenPrice, double ClosePrice, String CloseDate);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x20400, (short)0x0, (short)0x0, (byte)0xc0, (byte)0x0, (byte)0x0, (byte)0x0, (byte)0x0, (byte)0x0, (byte)0x0, (byte)0x46);
}
