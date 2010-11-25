//---------------------------------------------------------------------------
#ifndef fKPPH
#define fKPPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include "_CardProcessingThread.h"
//---------------------------------------------------------------------------
class TfKPP : public TForm
{
__published:
        TImage *imgPhoto;
        TLabel *lbStructure;
        TLabel *lbLName;
        TLabel *lbFName;
        TLabel *lbMName;
        TLabel *lbPassText1;
        TLabel *lbPassText2;
        TShape *shpCircle;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
        CardProcessingThread *CPT;
public:
             __fastcall TfKPP(TComponent* Owner, int CRport, int CRtype, int DeviceId, int KPPType, AnsiString ZoneName, int KPPNumber);
             __fastcall ~TfKPP();
};
//---------------------------------------------------------------------------
extern PACKAGE TfKPP *fKPP;
//---------------------------------------------------------------------------
#endif