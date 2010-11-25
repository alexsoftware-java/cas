//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Report.h"
#include "ReportChart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfReportChart *fReportChart;
//---------------------------------------------------------------------------
__fastcall TfReportChart::TfReportChart(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void __fastcall TfReportChart::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfReportChart::Chart1ClickSeries(TCustomChart *Sender, TChartSeries *Series, int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (ValueIndex == 0) // "Общее число"
   return;

 TfReport *fReport = new TfReport(Application, dt);
 fReport->PrepareData(401, 0, 0, Series->XLabel[ValueIndex]);
}
//---------------------------------------------------------------------------