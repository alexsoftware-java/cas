//---------------------------------------------------------------------------
#ifndef fReportSelectionH
#define fReportSelectionH
//---------------------------------------------------------------------------
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TfReportSelection : public TForm
{
__published:
        TGroupBox *GroupBox1;
        TMonthCalendar *MonthCalendar1;
        TDateTimePicker *DateTimePicker1;
        TRadioGroup *rgReportMode;
        TRadioGroup *rgReportType;
        TButton *Button1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall rgReportModeClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:
public:
             __fastcall TfReportSelection(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfReportSelection *fReportSelection;
//---------------------------------------------------------------------------
#endif