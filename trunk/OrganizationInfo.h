//---------------------------------------------------------------------------
#ifndef fOrganizationInfoH
#define fOrganizationInfoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <IBDatabase.hpp>
#include <IBSQL.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TfOrganizationInfo : public TForm
{
__published:
        TIBTransaction *IBTransaction1;
        TIBSQL *IBSQL1;
        TToolBar *ToolBar1;
        TToolButton *tbSave;
        TToolButton *tbUndo;
        TLabeledEdit *LabeledEdit1;
        TLabeledEdit *LabeledEdit2;
        TLabeledEdit *LabeledEdit3;
        TLabeledEdit *LabeledEdit5;
        TButton *Button1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall tbSaveClick(TObject *Sender);
        void __fastcall tbUndoClick(TObject *Sender);
        void __fastcall Change(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:
        AnsiString Organization,
                   Director,
                   Phone,
                   ServiceCard;
        void __fastcall PrepareData(bool ButtonsEnabled);
public:
             __fastcall TfOrganizationInfo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfOrganizationInfo *fOrganizationInfo;
//---------------------------------------------------------------------------
#endif