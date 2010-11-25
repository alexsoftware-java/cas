//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TfAbout *fAbout;
//---------------------------------------------------------------------------
__fastcall TfAbout::TfAbout(TComponent* AOwner) : TForm(AOwner) {}
//---------------------------------------------------------------------------
void __fastcall TfAbout::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfAbout::OKButtonClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------