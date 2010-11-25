//---------------------------------------------------------------------------
#ifndef fLoginH
#define fLoginH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "_CardReader.h"
#include "Main.h"
//---------------------------------------------------------------------------
class TfLogin : public TForm
{
__published:
        TTimer *ControlCRTimer;
        TLabel *Label1;
        TListBox *ListBox1;
        TLabel *Label2;
        TEdit *Edit1;
        void __fastcall ListBox1DblClick(TObject *Sender);
        void __fastcall ListBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall ControlCRTimerTimer(TObject *Sender);
private:
        std::vector<User> UsersList;
        CardReader        *ControlCR;

        virtual void __fastcall Dispatch(void *Message);
        void __fastcall ProcessCard(int Card);
public:
             __fastcall TfLogin(TComponent* Owner);
             __fastcall ~TfLogin();
};
//---------------------------------------------------------------------------
extern PACKAGE TfLogin *fLogin;
//---------------------------------------------------------------------------
#endif