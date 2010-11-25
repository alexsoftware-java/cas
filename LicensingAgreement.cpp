//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "LicensingAgreement.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfLicensingAgreement *fLicensingAgreement;
//---------------------------------------------------------------------------
__fastcall TfLicensingAgreement::TfLicensingAgreement(TComponent* Owner) : TForm(Owner) { }
//---------------------------------------------------------------------------
void __fastcall TfLicensingAgreement::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------