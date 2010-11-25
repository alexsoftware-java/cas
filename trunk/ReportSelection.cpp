//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Report.h"
#include "ReportSelection.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfReportSelection *fReportSelection;
//---------------------------------------------------------------------------
__fastcall TfReportSelection::TfReportSelection(TComponent* Owner) : TForm(Owner)
{
 if (fMain->userType == utUser)
   {
    rgReportMode->Controls[1]->Enabled = ( fMain->userRights[11] == '1' );
    rgReportMode->Controls[2]->Enabled = ( fMain->userRights[12] == '1' );
   }

 rgReportModeClick(this);
 MonthCalendar1->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall TfReportSelection::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfReportSelection::rgReportModeClick(TObject *Sender)
{
 switch (rgReportMode->ItemIndex)
   {
    case 0: Button1->Caption = "Просмотр";
            break;
    case 1: Button1->Caption = "Печать";
            break;
    case 2: Button1->Caption = "Редактирование";
            break;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfReportSelection::Button1Click(TObject *Sender)
{
 if (rgReportType->ItemIndex > -1)
   {
    TfReport *fReport = new TfReport(Application, MonthCalendar1->Date, DateTimePicker1->Date.FormatString("hh:nn"));
    fReport->PrepareData(rgReportType->ItemIndex, rgReportMode->ItemIndex);
   }
}
//---------------------------------------------------------------------------