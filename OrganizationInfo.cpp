//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "OrganizationInfo.h"
#include "_CardReader.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfOrganizationInfo *fOrganizationInfo;
//---------------------------------------------------------------------------
__fastcall TfOrganizationInfo::TfOrganizationInfo(TComponent* Owner) : TForm(Owner)
{
 LabeledEdit5->Visible = ( fMain->userType == utRoot );
 Button1     ->Visible = ( fMain->userType == utRoot );
 PrepareData(false);
}
//---------------------------------------------------------------------------
void __fastcall TfOrganizationInfo::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfOrganizationInfo::FormCloseQuery(TObject *Sender, bool &CanClose)
{
 AnsiString mbCaption = Caption + " -- Предупреждение";

 if (tbSave->Enabled == true)
   switch(MessageBox(Handle, "Вы изменяли информацию в базе данных.\nСохранить изменения?", mbCaption.c_str(), MB_YESNOCANCEL | MB_ICONWARNING))
     {
      case IDCANCEL: CanClose = false;
                     break;
      case IDYES   : tbSaveClick(Sender);
                     break;
      default      : break;
     }
}
//---------------------------------------------------------------------------
void __fastcall TfOrganizationInfo::tbSaveClick(TObject *Sender)
{
 int CCode = 0;
 if ( LabeledEdit5->Text != "" && LabeledEdit5->Text != "0")
   CCode = StrToInt(LabeledEdit5->Text[3]) + StrToInt(LabeledEdit5->Text[7]) * StrToInt(LabeledEdit5->Text[1]);

 fMain->SQL_Fwk->sqlUpdate(IBTransaction1, "Organization_Info",
                           "nn", "1",
                           "organization",LabeledEdit1->Text.c_str(),
                           "director",    LabeledEdit2->Text.c_str(),
                           "phone",       LabeledEdit3->Text.c_str(),
                           "ServiceCard", LabeledEdit5->Text == "0" ? "" : LabeledEdit5->Text.c_str(),
                           "CCode",       CCode == 0                ? "" : AnsiString(CCode).c_str(),
                           NULL);

 IBTransaction1->Commit();

 PrepareData(false);
}
//---------------------------------------------------------------------------
void __fastcall TfOrganizationInfo::tbUndoClick(TObject *Sender)
{
 LabeledEdit1->Text = Organization;
 LabeledEdit2->Text = Director;
 LabeledEdit3->Text = Phone;
 LabeledEdit5->Text = ServiceCard;
}
//---------------------------------------------------------------------------
void __fastcall TfOrganizationInfo::Change(TObject *Sender)
{
 if (Organization != LabeledEdit1->Text)  { tbSave->Enabled = true;  tbUndo->Enabled = true; return; }
                                   else   { tbSave->Enabled = false; tbUndo->Enabled = false; }
 if (Director     != LabeledEdit2->Text)  { tbSave->Enabled = true;  tbUndo->Enabled = true; return; }
                                   else   { tbSave->Enabled = false; tbUndo->Enabled = false; }
 if (Phone        != LabeledEdit3->Text)  { tbSave->Enabled = true;  tbUndo->Enabled = true; return; }
                                   else   { tbSave->Enabled = false; tbUndo->Enabled = false; }
 if (ServiceCard  != LabeledEdit5->Text)  { tbSave->Enabled = true;  tbUndo->Enabled = true; return; }
                                   else   { tbSave->Enabled = false; tbUndo->Enabled = false; }
}
//---------------------------------------------------------------------------
void __fastcall TfOrganizationInfo::Button1Click(TObject *Sender)
{
 if ( !fMain->cfgControlCRPort )
   return;

 CardReader *ControlCR = new CardReader(fMain->cfgControlCRPort, fMain->cfgControlCRType);

 if ( ControlCR->isReady() )
   LabeledEdit5->Text = ControlCR->getNumber();

 delete ControlCR;
}
//---------------------------------------------------------------------------
void __fastcall TfOrganizationInfo::PrepareData(bool ButtonsEnabled)
{
 IBSQL1->Close();
 IBSQL1->SQL->Text = "SELECT * FROM Organization_Info WHERE nn=1;";
 if ( !IBTransaction1->Active )
   IBTransaction1->StartTransaction();
 IBSQL1->ExecQuery();

 Organization = IBSQL1->FieldByName("organization")->AsString;
 Director     = IBSQL1->FieldByName("director")    ->AsString;
 Phone        = IBSQL1->FieldByName("phone")       ->AsString;
 ServiceCard  = IBSQL1->FieldByName("ServiceCard") ->AsString;

 tbUndoClick(this);

 tbSave->Enabled = ButtonsEnabled;
 tbUndo->Enabled = ButtonsEnabled;
}
//---------------------------------------------------------------------------