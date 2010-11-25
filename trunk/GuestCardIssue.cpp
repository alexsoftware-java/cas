//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "_frmupd.h"
#include "Main.h"
#include "GuestCardIssue.h"
#include "InputLine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfGuestCardIssue *fGuestCardIssue;
//---------------------------------------------------------------------------
__fastcall TfGuestCardIssue::TfGuestCardIssue(TComponent* Owner)
        : TForm(Owner)
{
strcpy(sortfield,"LNAME");
*filter=0;
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::FormDestroy(TObject *Sender)
{
fGuestCardIssue=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::FormClose(TObject *Sender, TCloseAction &Action)
{
Action=caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::ButtonOkClick(TObject *Sender)
{
TIBBlobStream *bs;
//unsigned short y1,m1,d1;

Guests->Append();
Guests->FindField("FNAME")->Text=EditFN->Text;
Guests->FindField("MNAME")->Text=EditMN->Text;
Guests->FindField("LNAME")->Text=EditLN->Text;
Guests->FindField("STRUCTURES_LNK")->Text=ComboBox1a->Items->Strings[ComboBox1->ItemIndex];
Guests->FindField("visit_from")->Text=EditFrom->Text;
Guests->FindField("visit_reason")->Text=ComboBoxReas->Text;
if (jpPhoto!=NULL)
 {
 bs=(TIBBlobStream *)Guests->CreateBlobStream(Guests->FindField("DOCUMENT_PHOTO"),bmWrite);
 jpPhoto->SaveToStream(bs);
 }
Guests->Post();
if (jpPhoto) bs->Free();
Guests->Close();

sprintf(buf,"SELECT * FROM UNITS WHERE NN=%s",ComboBox2a->Items->Strings[ComboBox2->ItemIndex]);
Units->SelectSQL->Clear();
Units->SelectSQL->Add(buf);
Units->Open();
Units->Edit();
if (jpPhoto!=NULL)
 {
 if ( fMain->cfgPhotosPath == "::db" )
  {
  bs=(TIBBlobStream *)Units->CreateBlobStream(Units->FindField("PHOTO"),bmWrite);
  jpPhoto->SaveToStream(bs);
  }
 else
  {
  sprintf(buf,"%s%s.jpg",fMain->cfgPhotosPath.c_str(),ComboBox2->Text.c_str());
  jpPhoto->SaveToFile(buf);
  }
 }
Units->FindField("CARD_TYPE")->Text="2";
Units->FindField("EXPIRE")->AsDateTime=DateTimePicker1->Date;
Units->Post();
Units->Close();

/*
DateTimePicker1->Date.DecodeDate(&y1,&m1,&d1);
sprintf(buf,"UPDATE UNITS SET CARD_TYPE=2,EXPIRE='%hu/%hu/%hu 23:59' WHERE NN=%s",m1,d1,y1,ComboBox2a->Items->Strings[ComboBox2->ItemIndex]);
Q1->SQL->Clear();
Q1->SQL->Add(buf);
Q1->ExecSQL();
*/

sprintf(buf,"INSERT INTO LOG (NN,UNITS_LNK,ZONES_LNK,EVENTTYPES_LNK) VALUES (GEN_ID(GEN_LOG,1),%s,%lu,30)",ComboBox2a->Items->Strings[ComboBox2->ItemIndex],fMain->cfgZone_NN);
Q1->SQL->Clear();
Q1->SQL->Add(buf);
Q1->ExecSQL();

if (From_Archive!=-1)
 {
 sprintf(buf,"UPDATE GUESTS_REQUEST SET FINISHED=1 WHERE NN=%lu",From_Archive);
 Q1->SQL->Clear();
 Q1->SQL->Add(buf);
 Q1->ExecSQL();
 }

GuestTransaction->Commit();
//Close();
if (unlink_fname!="-1") unlink(unlink_fname.c_str());
FormCreate(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::ButtonCancelClick(TObject *Sender)
{
Guests->Close();
GuestTransaction->Rollback();
Close();
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::FormCreate(TObject *Sender)
{
From_Archive=-1;
unlink_fname="-1";
jpPhoto=NULL;
GuestTransaction->StartTransaction();
FormCombosFromTable(Q1,ComboBox1,ComboBox1a,"OBJECTS",-1);
FormCombosFromTable_Ex(Q1,ComboBox2,ComboBox2a,"UNITS","CARD","WHERE CARD_TYPE=1 AND ENABLED=1","CARD",-1);
Guests->Open();
GuestsReq->Open();
}
//---------------------------------------------------------------------------


void __fastcall TfGuestCardIssue::ButtonArchClick(TObject *Sender)
{
TStream *bs;
TField *f;

if (Guests->FindField("NN")==NULL || Guests->FindField("NN")->IsNull) return;
EditFN->Text=Guests->FindField("FNAME")->Text;
EditMN->Text=Guests->FindField("MNAME")->Text;
EditLN->Text=Guests->FindField("LNAME")->Text;
f=Guests->FindField("STRUCTURES_LNK");
if (!f->Text.IsEmpty()) FormCombosFromTable(Q1,ComboBox1,ComboBox1a,"OBJECTS",f->AsInteger);
EditFrom->Text=Guests->FindField("visit_from")->Text;
ComboBoxReas->Text=Guests->FindField("visit_reason")->Text;
if (!Guests->FindField("DOCUMENT_PHOTO")->IsNull)
 {
 if (jpPhoto==NULL) jpPhoto = new TJPEGImage();
 bs=Guests->CreateBlobStream(Guests->FindField("DOCUMENT_PHOTO"),bmRead);
 jpPhoto->LoadFromStream(bs);
 ImageMain->Picture->Assign(jpPhoto);
 delete bs;
 }
EditLNChange(Sender);
From_Archive=-1;
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::DBGrid1CellClick(TColumn *Column)
{
TStream *bs;
if (Guests->FindField("NN")==NULL || Guests->FindField("NN")->IsNull) return;
TJPEGImage *jpPhoto2 = new TJPEGImage();

ImageArch->Picture->Assign(NULL);
if (!Guests->FindField("DOCUMENT_PHOTO")->IsNull)
 {
 bs=Guests->CreateBlobStream(Guests->FindField("DOCUMENT_PHOTO"),bmRead);
 jpPhoto2->LoadFromStream(bs);
 ImageArch->Picture->Assign(jpPhoto2);
 delete bs;
 }
delete jpPhoto2;
}
//---------------------------------------------------------------------------
void __fastcall TfGuestCardIssue::ButtonScanClick(TObject *Sender)
{
if (!OpenJPGDialog->Execute()) return;
if (jpPhoto==NULL) jpPhoto = new TJPEGImage();
jpPhoto->LoadFromFile(OpenJPGDialog->FileName);
unlink_fname=OpenJPGDialog->FileName;
ImageMain->Picture->Assign(jpPhoto);
}
//---------------------------------------------------------------------------


void __fastcall TfGuestCardIssue::ComboBox1Change(TObject *Sender)
{
EditFN->Text=EditFN->Text.Trim();
EditLN->Text=EditLN->Text.Trim();
EditMN->Text=EditMN->Text.Trim();
if (ComboBox1->ItemIndex!=-1 && ComboBox2->ItemIndex!=-1 && !EditFN->Text.IsEmpty() && !EditLN->Text.IsEmpty() && !EditMN->Text.IsEmpty() && !EditFrom->Text.IsEmpty() && !ComboBoxReas->Text.IsEmpty()) ButtonOk->Enabled=true;
else ButtonOk->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::EditLNChange(TObject *Sender)
{
QSeek();
ComboBox1Change(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::EditFNKeyPress(TObject *Sender,
      char &Key)
{
if (Key==' ') EditMN->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::EditLNKeyPress(TObject *Sender,
      char &Key)
{
if (Key==' ') EditFN->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::EditMNKeyPress(TObject *Sender,
      char &Key)
{
if (Key==' ') ComboBox1->SetFocus();
}
//---------------------------------------------------------------------------
int TfGuestCardIssue::QSeek(void)
// sеремещает sозицию в запросе к NN, запрос должен быть отсортирован по NN
{
TField *f;
f=Guests->FindField("LNAME");
while(1)
 {
 if (!EditLN->Text.AnsiCompareIC(f->Text)) return true;
 if (EditLN->Text.AnsiCompareIC(f->Text)>0)
  {
  if (Guests->Eof) return false;
  else Guests->Next();
  if (EditLN->Text.AnsiCompareIC(f->Text)<0) {Guests->Prior();return false;}
  }
 else
  {
  if (Guests->Bof) return false;
  else Guests->Prior();
  if (EditLN->Text.AnsiCompareIC(f->Text)>0) {Guests->Next();return false;}
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::ButtonQueryClick(TObject *Sender)
{
TStream *bs;
TField *f;

if (GuestsReq->FindField("NN")==NULL || GuestsReq->FindField("NN")->IsNull) return;

EditFN->Text=GuestsReq->FindField("FNAME")->Text;
EditMN->Text=GuestsReq->FindField("MNAME")->Text;
EditLN->Text=GuestsReq->FindField("LNAME")->Text;
DateTimePicker1->DateTime=GuestsReq->FindField("VISIT_DATE")->AsDateTime;
f=GuestsReq->FindField("STRUCTURES_LNK");
if (!f->Text.IsEmpty()) FormCombosFromTable(Q1,ComboBox1,ComboBox1a,"OBJECTS",f->AsInteger);
EditFrom->Text=GuestsReq->FindField("visit_from")->Text;
ComboBoxReas->Text=GuestsReq->FindField("visit_reason")->Text;
/*
if (!GuestsReq->FindField("DOCUMENT_PHOTO")->IsNull)
 {
 if (jpPhoto==NULL) jpPhoto = new TJPEGImage();
 bs=GuestsReq->CreateBlobStream(GuestsReq->FindField("DOCUMENT_PHOTO"),bmRead);
 jpPhoto->LoadFromStream(bs);
 ImageMain->Picture->Assign(jpPhoto);
 delete bs;
 }*/
EditLNChange(Sender);
From_Archive=GuestsReq->FindField("NN")->AsInteger;
}
//---------------------------------------------------------------------------


void __fastcall TfGuestCardIssue::FormResize(TObject *Sender)
{
int x=(this->ClientWidth - GroupBox3->Width -4)/2;
GroupBox1->Width=x;
GroupBox2->Width=x;
GroupBox3->Left=x+2;
DBGrid1->Height=GroupBox1->ClientHeight-ImageArch->Height-5;
DBGrid2->Height=DBGrid1->Height;
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::DBGrid1TitleClick(TColumn *Column)
{
strcpy(sortfield,Column->FieldName.c_str());
MakeSelectSQL();
}
//---------------------------------------------------------------------------

void TfGuestCardIssue::MakeSelectSQL(void)
{
Guests->Close();
Guests->SelectSQL->Clear();
Guests->SelectSQL->Add("SELECT * FROM GUESTS");

if (*filter) Guests->SelectSQL->Add(filter);

sprintf(buf,"ORDER BY %s",sortfield);
Guests->SelectSQL->Add(buf);

Guests->Open();
}
//---------------------------------------------------------------------------


void __fastcall TfGuestCardIssue::N1Click(TObject *Sender)
{
TfInputLine *fInputLine = new TfInputLine(this, "Фильтр");
if (fInputLine->ShowModal() == mrOk)
 {
 sprintf(filter,"where %s CONTAINING '%s'",DBGrid1->SelectedField->FieldName,fInputLine->LabeledEdit1->Text.c_str());
 MakeSelectSQL();
 }
delete fInputLine;
}
//---------------------------------------------------------------------------

void __fastcall TfGuestCardIssue::N2Click(TObject *Sender)
{
*filter=0;
MakeSelectSQL();
}
//---------------------------------------------------------------------------