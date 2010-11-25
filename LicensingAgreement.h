//---------------------------------------------------------------------------
#ifndef LicensingAgreementH
#define LicensingAgreementH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TfLicensingAgreement : public TForm
{
__published:
        TRichEdit *RichEdit1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
public:
        __fastcall TfLicensingAgreement(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfLicensingAgreement *fLicensingAgreement;
//---------------------------------------------------------------------------
#endif