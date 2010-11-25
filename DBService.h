//---------------------------------------------------------------------------
#ifndef fDBServiceH
#define fDBServiceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <IBCustomDataSet.hpp>
#include <IBDatabase.hpp>
#include <IBSQL.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TfDBService : public TForm
{
__published:
        TIBDatabase *IBDatabase1;
        TIBTransaction *IBTransaction1;
        TIBSQL *IBSQL1;
        TIBDataSet *IBDataSet1;
        TOpenDialog *OpenDialog1;
        TOpenDialog *OpenDialog2;
        TSaveDialog *SaveDialog1;
        TSaveDialog *SaveDialog2;
        TSaveDialog *SaveDialog3;
        TLabeledEdit *LabeledEdit1;
        TLabeledEdit *LabeledEdit2;
        TLabeledEdit *LabeledEdit3;
        TLabeledEdit *LabeledEdit4;
        TRadioGroup *RadioGroup1;
        TEdit *Edit1;
        TCheckBox *chbExportLog;
        TCheckBox *chbExcelVisible;
        TButton *btDBCreate;
        TButton *btExcelExport;
        TButton *btExcelImport;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btDBCreateClick(TObject *Sender);
        void __fastcall btExcelExportClick(TObject *Sender);
        void __fastcall btExcelImportClick(TObject *Sender);
private:
        bool __fastcall openDB();
public:
        __fastcall TfDBService(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfDBService *fDBService;
//---------------------------------------------------------------------------
#endif