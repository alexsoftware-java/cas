//---------------------------------------------------------------------------
#ifndef fReportChartH
#define fReportChartH
//---------------------------------------------------------------------------
#include <Chart.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
class TfReportChart : public TForm
{
__published:
        TChart *Chart1;
        THorizBarSeries *Series1;
        THorizBarSeries *Series2;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Chart1ClickSeries(TCustomChart *Sender, TChartSeries *Series, int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y);
private:
public:
        TDateTime dt;
        friend class TfReport;
             __fastcall TfReportChart(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfReportChart *fReportChart;
//---------------------------------------------------------------------------
#endif