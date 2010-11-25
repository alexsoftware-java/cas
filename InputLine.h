//---------------------------------------------------------------------------
#ifndef fInputLineH
#define fInputLineH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TfInputLine : public TForm
{
__published:
        TButton *Button1;
        TButton *Button2;
        TLabeledEdit *LabeledEdit1;
        void __fastcall LabeledEdit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall LabeledEdit1Change(TObject *Sender);
private:
public:
        AnsiString InitialValue;
        __fastcall TfInputLine(TComponent* Owner, AnsiString caption, AnsiString initialValue = "");
};
//---------------------------------------------------------------------------
extern PACKAGE TfInputLine *fInputLine;
//---------------------------------------------------------------------------
#endif