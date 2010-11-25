//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "PrintCards.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfPrintCards *fPrintCards;
//---------------------------------------------------------------------------
__fastcall TfPrintCards::TfPrintCards(TComponent* Owner) : TForm(Owner)
{
 for (int i = 0; i < CardsOnPage; i++)
    bmpCards[i] = NULL;

 OpenPictureDialog1->InitialDir = fMain->ExePath + "Templates\\";

 IBDataSet1->Prepare();
 IBDataSet1->Open();

 rbPhotoPrinterClick(this);
}
//---------------------------------------------------------------------------
__fastcall TfPrintCards::~TfPrintCards()
{
 for (int i = 0; i < CardsOnPage; i++)
    if ( bmpCards[i] != NULL )
      delete bmpCards[i];
}
//---------------------------------------------------------------------------
void __fastcall TfPrintCards::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfPrintCards::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
 this->VertScrollBar->Position -= WheelDelta;
 Handled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfPrintCards::rbPhotoPrinterClick(TObject *Sender)
{
 lbePageTemplateFile->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfPrintCards::rbCardPrinterClick(TObject *Sender)
{
 lbePageTemplateFile->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfPrintCards::PaintBoxPaint(TObject *Sender)
{
 TPaintBox *PaintBox = (TPaintBox *) Sender;

 if ( bmpCards[PaintBox->Tag] != NULL )
   PaintBox->Canvas->StretchDraw(PaintBox->ClientRect, bmpCards[PaintBox->Tag]);
}
//---------------------------------------------------------------------------
void __fastcall TfPrintCards::PaintBoxClick(TObject *Sender)
{
 TPaintBox *PaintBox = (TPaintBox *) Sender;

 if (bmpCards[PaintBox->Tag] != NULL) // Если карточка уже была заполнена
   {
    delete bmpCards[PaintBox->Tag];
    bmpCards[PaintBox->Tag] = NULL;
    PaintBox->Repaint();
   }
 else
   {
    if (bmpCards[PaintBox->Tag] == NULL)
      bmpCards[PaintBox->Tag] = new Graphics::TBitmap();

    fillCard(bmpCards[PaintBox->Tag], IBDataSet1->FieldByName("template")->AsString, IBDataSet1, PaintBox);
    IBDataSet1->Next();
   }
}
//---------------------------------------------------------------------------
void __fastcall TfPrintCards::btSelectPictureClick(TObject *Sender)
{
 if (!OpenPictureDialog1->Execute())
   return;

 if (bmpCards[0] == NULL)
   bmpCards[0] = new Graphics::TBitmap();

 bmpCards[0]->LoadFromFile(OpenPictureDialog1->FileName);

 for (int i = 1; i < CardsOnPage; i++)
    {
     if (bmpCards[i] == NULL)
       bmpCards[i] = new Graphics::TBitmap();
     bmpCards[i]->Assign(bmpCards[0]);
    }

 TPaintBox *PaintBoxes[] = { PaintBox1, PaintBox2, PaintBox3, PaintBox4, PaintBox5, PaintBox6, PaintBox7, PaintBox8, PaintBox9, PaintBox10, NULL };
 for (int i = 0; PaintBoxes[i] != NULL; i++)
    PaintBoxes[i]->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfPrintCards::PrintClick(TObject *Sender)
{
 if ( !PrintDialog1->Execute() )
   return;

 TPaintBox *PaintBoxes[] = { PaintBox1, PaintBox2, PaintBox3, PaintBox4, PaintBox5, PaintBox6, PaintBox7, PaintBox8, PaintBox9, PaintBox10, NULL };

 Printer()->BeginDoc();

 if ( rbPrintPage->Checked )
   {
    Printer()->Title = "Готовая картинка";
    for (int i = 1, last = StrToInt(lbePagesNumber->Text); i <= last; i++)
       {
        if ( i > 1 )
          Printer()->NewPage();

        printPage();
       }
   }
 else // rbPrintFromDB->Checked
   {
    Printer()->Title = "Карточки";
    for (int i = 1, last = StrToInt(lbePagesNumber->Text); i <= last && !IBDataSet1->Eof; i++)
       {
        for (int j = 0; j < CardsOnPage; j++, IBDataSet1->Next())
           {
            if ( !IBDataSet1->Eof )
              {
               if (bmpCards[j] == NULL)
                 bmpCards[j] = new Graphics::TBitmap();

               fillCard(bmpCards[j], IBDataSet1->FieldByName("template")->AsString, IBDataSet1, PaintBoxes[j]);
              }
            else
              if ( j < CardsOnPage && bmpCards[j] != NULL)
                {
                 delete bmpCards[j];
                 bmpCards[j] = NULL;
                 PaintBoxes[j]->Repaint();
                }
           }
        if ( i > 1 )
          Printer()->NewPage();

        printPage();
       }
   }

 if ( cbClearAfterPrinting->Checked )
   {
    for (int i = 0; i < CardsOnPage; i++)
       if (bmpCards[i] != NULL)
         {
          delete bmpCards[i];
          bmpCards[i] = NULL;
          PaintBoxes[i]->Repaint();
         }
   }

 Printer()->EndDoc();
}
//---------------------------------------------------------------------------
void TfPrintCards::fillCard(Graphics::TBitmap *bmpCard, AnsiString TemplateFile, TIBDataSet *IBDataSet, TPaintBox *PaintBox)
{
 TStringList *Template = new TStringList;
 Template->LoadFromFile(fMain->ExePath + "Templates\\" + TemplateFile);

 bmpCard->LoadFromFile(fMain->ExePath + "Templates\\" + Template->Values["Background"]);

 // Количество точек на сантиметр
 const double dpi_x = GetDeviceCaps(bmpCard->Canvas->Handle, LOGPIXELSX) / 2.54,
              dpi_y = GetDeviceCaps(bmpCard->Canvas->Handle, LOGPIXELSY) / 2.54;

 // При печати текста, цвет фона не меняется
 bmpCard->Canvas->Brush->Style = bsClear;

 if ( Template->Values["Photo_X"] != "" )
   {
    TJPEGImage *jpgPhoto = new TJPEGImage();

    if ( fMain->cfgPhotosPath == "::db" )
      {
       if ( !IBDataSet->FieldByName("photo")->IsNull )
         {
          TStream *bsPhoto = IBDataSet->CreateBlobStream(IBDataSet->FieldByName("photo"), bmRead);
          jpgPhoto->LoadFromStream(bsPhoto);
          delete bsPhoto;
         }
      }
    else
      {
       try {
            TFileStream *fsPhoto = new TFileStream(fMain->cfgPhotosPath + IBDataSet->FieldByName("card")->AsString + ".jpg", fmOpenRead || fmShareCompat);
            jpgPhoto->LoadFromStream(fsPhoto);
            delete fsPhoto;
           }
       catch (const EFOpenError &Exception) { }
      }

    if (jpgPhoto->Width != 0) // Фото всё-таки удалось загрузить
      {
       double sWidth  = 0,
              sHeight = 0,
              xCentered = 0,
              yCentered = 0;

       if ( Template->Values["Photo_Width"] != "" ) // Рисуем фото без сохранения пропорций, растягивая до заданных размеров
         {
          sWidth  = StrToFloat(Template->Values["Photo_Width"]);
          sHeight = StrToFloat(Template->Values["Photo_Height"]);
         }
       else // Рисуем фото с сохранением пропорций
         {
          sWidth  = jpgPhoto->Width;
          sHeight = jpgPhoto->Height;

          const double xyAspect        = sWidth / sHeight,
                       Photo_MaxWidth  = StrToFloat(Template->Values["Photo_MaxWidth"]),
                       Photo_MaxHeight = StrToFloat(Template->Values["Photo_MaxHeight"]);

          if (sWidth > sHeight)
            {
             sWidth  = Photo_MaxWidth;
             sHeight = Photo_MaxWidth / xyAspect;
         
             if (sHeight > Photo_MaxHeight)
               {
                sWidth = Photo_MaxHeight * xyAspect;
                sHeight = Photo_MaxHeight;
               }
            }
          else
            {
             sWidth  = Photo_MaxHeight * xyAspect;
             sHeight = Photo_MaxHeight;
    
             if (sWidth > Photo_MaxWidth)
               {
                sWidth  = Photo_MaxWidth;
                sHeight = Photo_MaxWidth / xyAspect;
               }
            }
          xCentered = ( Photo_MaxWidth - sWidth  ) / 2;
          yCentered = ( Photo_MaxHeight - sHeight ) / 2;
         }

       bmpCard->Canvas->StretchDraw( Rect(
                                          ( StrToFloat( Template->Values["Photo_X"]) + xCentered )           * dpi_x,
                                          ( StrToFloat( Template->Values["Photo_Y"]) + yCentered )           * dpi_y,
                                          ( StrToFloat( Template->Values["Photo_X"]) + xCentered + sWidth  ) * dpi_x,
                                          ( StrToFloat( Template->Values["Photo_Y"]) + yCentered + sHeight ) * dpi_y
                                         ),
                                     jpgPhoto );
      }
    delete jpgPhoto;
   }

 AnsiString VariableName = "Text1_",
            Text;
 int i = 1;
 do
   {
    bmpCard->Canvas->Font->Color = (TColor) StrToInt(Template->Values[VariableName + "Color"]);
    bmpCard->Canvas->Font->Name  = Template->Values[VariableName + "FontName"];
    bmpCard->Canvas->Font->Size  = StrToInt(Template->Values[VariableName + "FontSize"]);
    //bmpCard->Canvas->Font->Style = TFontStyles() << fsBold << fsUnderline;

    if (Template->Values[VariableName + "Field"] == "")
      Text = Template->Values[VariableName + "Text"];
    else
      Text = IBDataSet->FieldByName(Template->Values[VariableName + "Field"])->AsString;

    bmpCard->Canvas->TextOut( StrToFloat(Template->Values[VariableName + "X"]) * dpi_x,
                              StrToFloat(Template->Values[VariableName + "Y"]) * dpi_y,
                              Text );

    i++;
    VariableName = "Text" + IntToStr(i) + "_";
   }
 while (Template->Values[VariableName + "X"] != "");

 delete Template;

 PaintBox->Repaint();
}
//---------------------------------------------------------------------------
void TfPrintCards::printPage()
{
 TPrinter *Prn = Printer();

 // Количество точек на сантиметр
 const double prn_dpi_x = GetDeviceCaps(Prn->Canvas->Handle, LOGPIXELSX) / 2.54,
              prn_dpi_y = GetDeviceCaps(Prn->Canvas->Handle, LOGPIXELSY) / 2.54;

 // Печать на карточном  принтере
 if ( rbCardPrinter->Checked )
   {
    // Расположение карточек на листе
    const double CardWidth  = 8.6,
                 CardHeight = 5.5,
                 Left1 = 0,
                 Top1 = 0;

    TRect CardRect = Rect (Left1 * prn_dpi_x, Top1 * prn_dpi_y, (Left1 + CardWidth) * prn_dpi_x, (Top1 + CardHeight) * prn_dpi_y);

    for (int i = 0; i < CardsOnPage; i++)
       {
        if (bmpCards[i] != NULL)
          {
           Prn->Canvas->StretchDraw(CardRect, bmpCards[i]);
           if ( i + 1 < CardsOnPage && bmpCards[i+1] != NULL )
             Prn->NewPage();
          }
       }

    return;
   }

 TStringList *Template = new TStringList;
 Template->LoadFromFile(fMain->ExePath + "Templates\\" + lbePageTemplateFile->Text);

 // Расположение карточек на листе
 const double CardWidth  = StrToFloat(Template->Values["Card_Width"]),
              CardHeight = StrToFloat(Template->Values["Card_Height"]),
              Left1 = StrToFloat(Template->Values["Card_Left1"]),
              Left2 = StrToFloat(Template->Values["Card_Left2"]),
              Top1 = StrToFloat(Template->Values["Card1_Top"]),
              Top2 = StrToFloat(Template->Values["Card2_Top"]),
              Top3 = StrToFloat(Template->Values["Card3_Top"]),
              Top4 = StrToFloat(Template->Values["Card4_Top"]),
              Top5 = StrToFloat(Template->Values["Card5_Top"]);

 TRect CardRect[10];
 CardRect[0] = Rect (Left1 * prn_dpi_x, Top1 * prn_dpi_y, (Left1 + CardWidth) * prn_dpi_x, (Top1 + CardHeight) * prn_dpi_y);
 CardRect[1] = Rect (Left2 * prn_dpi_x, Top1 * prn_dpi_y, (Left2 + CardWidth) * prn_dpi_x, (Top1 + CardHeight) * prn_dpi_y);
 CardRect[2] = Rect (Left1 * prn_dpi_x, Top2 * prn_dpi_y, (Left1 + CardWidth) * prn_dpi_x, (Top2 + CardHeight) * prn_dpi_y);
 CardRect[3] = Rect (Left2 * prn_dpi_x, Top2 * prn_dpi_y, (Left2 + CardWidth) * prn_dpi_x, (Top2 + CardHeight) * prn_dpi_y);
 CardRect[4] = Rect (Left1 * prn_dpi_x, Top3 * prn_dpi_y, (Left1 + CardWidth) * prn_dpi_x, (Top3 + CardHeight) * prn_dpi_y);
 CardRect[5] = Rect (Left2 * prn_dpi_x, Top3 * prn_dpi_y, (Left2 + CardWidth) * prn_dpi_x, (Top3 + CardHeight) * prn_dpi_y);
 CardRect[6] = Rect (Left1 * prn_dpi_x, Top4 * prn_dpi_y, (Left1 + CardWidth) * prn_dpi_x, (Top4 + CardHeight) * prn_dpi_y);
 CardRect[7] = Rect (Left2 * prn_dpi_x, Top4 * prn_dpi_y, (Left2 + CardWidth) * prn_dpi_x, (Top4 + CardHeight) * prn_dpi_y);
 CardRect[8] = Rect (Left1 * prn_dpi_x, Top5 * prn_dpi_y, (Left1 + CardWidth) * prn_dpi_x, (Top5 + CardHeight) * prn_dpi_y);
 CardRect[9] = Rect (Left2 * prn_dpi_x, Top5 * prn_dpi_y, (Left2 + CardWidth) * prn_dpi_x, (Top5 + CardHeight) * prn_dpi_y);

 for (int i = 0; i < CardsOnPage; i++)
    {
     if (bmpCards[i] != NULL)
       Prn->Canvas->StretchDraw(CardRect[i], bmpCards[i]);
    }

 // Мишень для пробивки № 1
 const double T1_Width  = StrToFloat(Template->Values["Target1_Width"]),
              T1_Height = StrToFloat(Template->Values["Target1_Height"]),
              T1_Left1 = StrToFloat(Template->Values["Target1_Left1"]),
              T1_Left3 = StrToFloat(Template->Values["Target1_Left3"]),
              T1_Top1 = StrToFloat(Template->Values["Target1_Top1"]),
              T1_Top2 = StrToFloat(Template->Values["Target1_Top2"]),
              T1_Top3 = StrToFloat(Template->Values["Target1_Top3"]),
              T1_Top4 = StrToFloat(Template->Values["Target1_Top4"]),
              T1_Top5 = StrToFloat(Template->Values["Target1_Top5"]);

 TRect T1_Rect1[5], T1_Rect2[5], T1_Rect3[5], T1_Rect4[5], T1_Rect5[5];
 T1_Rect1[0] = Rect ( T1_Left1 * prn_dpi_x, T1_Top1 * prn_dpi_y, (T1_Left1 + T1_Width) * prn_dpi_x, (T1_Top1 + T1_Height) * prn_dpi_y);
 T1_Rect2[0] = Rect ( (T1_Left1 + T1_Width + CardWidth + 0.1) * prn_dpi_x, T1_Top1 * prn_dpi_y, (T1_Left1 + CardWidth + T1_Width + T1_Width + 0.1) * prn_dpi_x, (T1_Top1 + T1_Height) * prn_dpi_y);
 T1_Rect3[0] = Rect ( T1_Left3 * prn_dpi_x, T1_Top1 * prn_dpi_y, (T1_Left3 + T1_Width) * prn_dpi_x, (T1_Top1 + T1_Height) * prn_dpi_y);
 T1_Rect4[0] = Rect ( (T1_Left3 + T1_Width + CardWidth + 0.1) * prn_dpi_x, T1_Top1 * prn_dpi_y, (T1_Left3 + CardWidth + T1_Width + T1_Width + 0.1) * prn_dpi_x, (T1_Top1 + T1_Height) * prn_dpi_y);
 T1_Rect1[1] = Rect ( T1_Left1 * prn_dpi_x, T1_Top2 * prn_dpi_y, (T1_Left1 + T1_Width) * prn_dpi_x, (T1_Top2 + T1_Height) * prn_dpi_y);
 T1_Rect2[1] = Rect ( (T1_Left1 + T1_Width + CardWidth + 0.1) * prn_dpi_x, T1_Top2 * prn_dpi_y, (T1_Left1 + CardWidth + T1_Width + T1_Width + 0.1) * prn_dpi_x, (T1_Top2 + T1_Height) * prn_dpi_y);
 T1_Rect3[1] = Rect ( T1_Left3 * prn_dpi_x, T1_Top2 * prn_dpi_y, (T1_Left3 + T1_Width) * prn_dpi_x, (T1_Top2 + T1_Height) * prn_dpi_y);
 T1_Rect4[1] = Rect ( (T1_Left3 + T1_Width + CardWidth + 0.1) * prn_dpi_x, T1_Top2 * prn_dpi_y, (T1_Left3 + CardWidth + T1_Width + T1_Width + 0.1) * prn_dpi_x, (T1_Top2 + T1_Height) * prn_dpi_y);
 T1_Rect1[2] = Rect ( T1_Left1 * prn_dpi_x, T1_Top3 * prn_dpi_y, (T1_Left1 + T1_Width) * prn_dpi_x, (T1_Top3 + T1_Height) * prn_dpi_y);
 T1_Rect2[2] = Rect ( (T1_Left1 + T1_Width + CardWidth + 0.1) * prn_dpi_x, T1_Top3 * prn_dpi_y, (T1_Left1 + CardWidth + T1_Width + T1_Width + 0.1) * prn_dpi_x, (T1_Top3 + T1_Height) * prn_dpi_y);
 T1_Rect3[2] = Rect ( T1_Left3 * prn_dpi_x, T1_Top3 * prn_dpi_y, (T1_Left3 + T1_Width) * prn_dpi_x, (T1_Top3 + T1_Height) * prn_dpi_y);
 T1_Rect4[2] = Rect ( (T1_Left3 + T1_Width + CardWidth + 0.1) * prn_dpi_x, T1_Top3 * prn_dpi_y, (T1_Left3 + CardWidth + T1_Width + T1_Width + 0.1) * prn_dpi_x, (T1_Top3 + T1_Height) * prn_dpi_y);
 T1_Rect1[3] = Rect ( T1_Left1 * prn_dpi_x, T1_Top4 * prn_dpi_y, (T1_Left1 + T1_Width) * prn_dpi_x, (T1_Top4 + T1_Height) * prn_dpi_y);
 T1_Rect2[3] = Rect ( (T1_Left1 + T1_Width + CardWidth + 0.1) * prn_dpi_x, T1_Top4 * prn_dpi_y, (T1_Left1 + CardWidth + T1_Width + T1_Width + 0.1) * prn_dpi_x, (T1_Top4 + T1_Height) * prn_dpi_y);
 T1_Rect3[3] = Rect ( T1_Left3 * prn_dpi_x, T1_Top4 * prn_dpi_y, (T1_Left3 + T1_Width) * prn_dpi_x, (T1_Top4 + T1_Height) * prn_dpi_y);
 T1_Rect4[3] = Rect ( (T1_Left3 + T1_Width + CardWidth + 0.1) * prn_dpi_x, T1_Top4 * prn_dpi_y, (T1_Left3 + CardWidth + T1_Width + T1_Width + 0.1) * prn_dpi_x, (T1_Top4 + T1_Height) * prn_dpi_y);
 T1_Rect1[4] = Rect ( T1_Left1 * prn_dpi_x, T1_Top5 * prn_dpi_y, (T1_Left1 + T1_Width) * prn_dpi_x, (T1_Top5 + T1_Height) * prn_dpi_y);
 T1_Rect2[4] = Rect ( (T1_Left1 + T1_Width + CardWidth + 0.1) * prn_dpi_x, T1_Top5 * prn_dpi_y, (T1_Left1 + CardWidth + T1_Width + T1_Width + 0.1) * prn_dpi_x, (T1_Top5 + T1_Height) * prn_dpi_y);
 T1_Rect3[4] = Rect ( T1_Left3 * prn_dpi_x, T1_Top5 * prn_dpi_y, (T1_Left3 + T1_Width) * prn_dpi_x, (T1_Top5 + T1_Height) * prn_dpi_y);
 T1_Rect4[4] = Rect ( (T1_Left3 + T1_Width + CardWidth + 0.1) * prn_dpi_x, T1_Top5 * prn_dpi_y, (T1_Left3 + CardWidth + T1_Width + T1_Width + 0.1) * prn_dpi_x, (T1_Top5 + T1_Height) * prn_dpi_y);

 Graphics::TBitmap *bmpT1 = new Graphics::TBitmap();
 bmpT1->LoadFromFile(fMain->ExePath + "Templates\\" + Template->Values["Target1_File"]);
 for (int i = 0; i < 5; i++)
    {
     Prn->Canvas->StretchDraw(T1_Rect1[i], bmpT1);
     Prn->Canvas->StretchDraw(T1_Rect2[i], bmpT1);
     Prn->Canvas->StretchDraw(T1_Rect3[i], bmpT1);
     Prn->Canvas->StretchDraw(T1_Rect4[i], bmpT1);
    }

 delete bmpT1;

 // Точка для пробивки № 2
 const double T2_Width  = StrToFloat(Template->Values["Target2_Width"]),
              T2_Height = StrToFloat(Template->Values["Target2_Height"]),
              T2_Left = StrToFloat(Template->Values["Target2_Left"]),
              T2_Top1 = StrToFloat(Template->Values["Target2_Top1"]),
              T2_Top2 = StrToFloat(Template->Values["Target2_Top2"]);
 TRect T2_Rect1 = Rect ( T2_Left * prn_dpi_x, T2_Top1 * prn_dpi_y, (T2_Left + T2_Width) * prn_dpi_x, (T2_Top1 + T2_Height) * prn_dpi_y);
 TRect T2_Rect2 = Rect ( T2_Left * prn_dpi_x, T2_Top2 * prn_dpi_y, (T2_Left + T2_Width) * prn_dpi_x, (T2_Top2 + T2_Height) * prn_dpi_y);

 Graphics::TBitmap *bmpT2 = new Graphics::TBitmap();
 bmpT2->LoadFromFile(fMain->ExePath + "Templates\\" + Template->Values["Target2_File"]);

 Prn->Canvas->StretchDraw(T2_Rect1, bmpT2);
 Prn->Canvas->StretchDraw(T2_Rect2, bmpT2);

 delete bmpT2;
}
//---------------------------------------------------------------------------