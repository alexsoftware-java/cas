//---------------------------------------------------------------------------
#ifndef fPrintCardsH
#define fPrintCardsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <Grids.hpp>
#include <IBCustomDataSet.hpp>
#include <IBDatabase.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TfPrintCards : public TForm
{
__published:
        TIBTransaction *IBTransaction1;
        TIBDataSet *IBDataSet1;
        TDataSource *DataSource1;
        TPrintDialog *PrintDialog1;
        TOpenPictureDialog *OpenPictureDialog1;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TRadioButton *rbPhotoPrinter;
        TLabeledEdit *lbePageTemplateFile;
        TRadioButton *rbCardPrinter;
        TGroupBox *GroupBox3;
        TRadioButton *rbPrintFromDB;
        TRadioButton *rbPrintPage;
        TCheckBox *cbClearAfterPrinting;
        TButton *btSelectPicture;
        TGroupBox *GroupBox4;
        TLabeledEdit *lbePagesNumber;
        TUpDown *UpDown1;
        TButton *btPrint;
        TDBGrid *DBGrid1;
        TPanel *Panel1;
        TPaintBox *PaintBox1;
        TPanel *Panel2;
        TPaintBox *PaintBox2;
        TPanel *Panel3;
        TPaintBox *PaintBox3;
        TPanel *Panel4;
        TPaintBox *PaintBox4;
        TPanel *Panel5;
        TPaintBox *PaintBox5;
        TPanel *Panel6;
        TPaintBox *PaintBox6;
        TPanel *Panel7;
        TPaintBox *PaintBox7;
        TPanel *Panel8;
        TPaintBox *PaintBox8;
        TPanel *Panel9;
        TPaintBox *PaintBox9;
        TPanel *Panel10;
        TPaintBox *PaintBox10;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
        void __fastcall rbPhotoPrinterClick(TObject *Sender);
        void __fastcall rbCardPrinterClick(TObject *Sender);
        void __fastcall btSelectPictureClick(TObject *Sender);
        void __fastcall PrintClick(TObject *Sender);
        void __fastcall PaintBoxPaint(TObject *Sender);
        void __fastcall PaintBoxClick(TObject *Sender);
private:
        #define CardsOnPage 10
        Graphics::TBitmap *bmpCards[CardsOnPage];
        void printPage();
public:
             __fastcall TfPrintCards(TComponent* Owner);
             __fastcall ~TfPrintCards();
        void fillCard(Graphics::TBitmap *bmpCard, AnsiString TemplateFile, TIBDataSet *IBDataSet, TPaintBox *PaintBox);
};
//---------------------------------------------------------------------------
extern PACKAGE TfPrintCards *fPrintCards;
//---------------------------------------------------------------------------
#endif