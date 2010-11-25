//----------------------------------------------------------------------------
#ifndef fAboutH
#define fAboutH
//----------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//----------------------------------------------------------------------------
class TfAbout : public TForm
{
__published:
        TMemo *AboutMemo;
        TButton *OKButton;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall OKButtonClick(TObject *Sender);
private:
public:
             __fastcall TfAbout(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern TfAbout *fAbout;
//----------------------------------------------------------------------------
#endif