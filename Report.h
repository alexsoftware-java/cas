//---------------------------------------------------------------------------
#ifndef fReportH
#define fReportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBDatabase.hpp>
#include <IBQuery.hpp>
#include "pr_Classes.hpp"
#include "pr_Common.hpp"
//---------------------------------------------------------------------------
class TfReport : public TForm
{
__published:
        TIBTransaction *IBTransaction1;
        TIBQuery *IBQuery1;
        TIBQuery *IBQuery2;
        TprReport *prReport1;
        TAnimate *Animate1;
        void __fastcall prReport1DestroyPreview(TObject *Sender);
private:
        TDateTime BeginDate,
                  EndDate;
        AnsiString BeginTimeInWords,
                   EndTimeInWords;
public:
             __fastcall TfReport(TComponent* Owner, TDateTime BeginDate_, AnsiString BeginTimeInWords_ = "", TDateTime EndDate_ = Date(), AnsiString EndTimeInWords_ = "");
        void __fastcall PrepareData(int ReportType, int ReportMode, int ParentObject = 0, AnsiString dopInfo = "");
};
//---------------------------------------------------------------------------
extern PACKAGE TfReport *fReport;
//---------------------------------------------------------------------------
#endif