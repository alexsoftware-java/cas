//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "InputLine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfInputLine *fInputLine;
//---------------------------------------------------------------------------
__fastcall TfInputLine::TfInputLine(TComponent* Owner, AnsiString caption, AnsiString initialValue) : TForm(Owner)
{
 Caption      = caption;
 InitialValue = initialValue;
 LabeledEdit1->Text = InitialValue;
}
//---------------------------------------------------------------------------
void __fastcall TfInputLine::LabeledEdit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
 if (Key == VK_RETURN && Button1->Enabled)
   Button1->Click();
}
//---------------------------------------------------------------------------
void __fastcall TfInputLine::LabeledEdit1Change(TObject *Sender)
{
 Button1->Enabled = (LabeledEdit1->Text != InitialValue && !LabeledEdit1->Text.IsEmpty());
}
//---------------------------------------------------------------------------