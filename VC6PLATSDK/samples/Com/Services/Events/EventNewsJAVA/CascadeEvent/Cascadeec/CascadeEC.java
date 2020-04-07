//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("C:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /javatlb /c2j /creg /xh /wfc  /w /xi /X:rkc /l "C:\DOCUME~1\a-sunilc\LOCALS~1\Temp\jvc11E.tmp" /nologo /d "D:\ComPlusSamples\Source\LCE\CascadeEvent" "D:\ComPlusSamples\Source\LCE\CascadeEvent\CascadeEC.tlb")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package cascadeec;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

/** @com.register(clsid=8CE4A9E0-0FC1-11D3-925A-0080C7C30D72, typelib=7508F170-0FC1-11D3-925A-0080C7C30D72, version="1.0", description="Cascade Class")*/
public class CascadeEC implements IUnknown,com.ms.com.NoAutoScripting,cascadeec.INewsEventDefault
{
  public void NewsFlash(double dtTimeStamp, String Symbol, String Headline, String URL) 
  {
  }

  public void ShortQuote(String Symbol, double BidPrice, double AskPrice, double LastTradeTime, double LastTradePrice, double NetChange, double DailyHigh, double DailyLow) 
  {
  }

  public void LongQuote(String Symbol, double BidPrice, double AskPrice, String LastTradeTime, double LastTradePrice, double NetChange, double DailyHigh, double DailyLow, int AskSize, int BidSize, double OpenPrice, double ClosePrice, String CloseDate) 
  {
  }

}
