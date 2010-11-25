//---------------------------------------------------------------------------
#ifndef fCafeteriaH
#define fCafeteriaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <IBDatabase.hpp>
#include <IBSQL.hpp>
#include <StdCtrls.hpp>
#include "_CardReader.h"
//---------------------------------------------------------------------------
class TfCafeteria : public TForm
{
__published:
        TIBTransaction *IBTransaction1;
        TIBSQL *IBSQL1;
        TImage *imgPhoto;
        TLabel *lbStructure;
        TLabel *lbLName;
        TLabel *lbFName;
        TLabel *lbMName;
        TLabel *lbPassText1;
        TLabel *lbPassText2;
        TShape *shpCircle;
        TTimer *Timer1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Timer1Timer(TObject *Sender);
private:
        CardReader *CR;
public:
             __fastcall TfCafeteria(TComponent* Owner, int CRport, int CRtype);
};
//---------------------------------------------------------------------------
extern PACKAGE TfCafeteria *fCafeteria;
//---------------------------------------------------------------------------
#endif