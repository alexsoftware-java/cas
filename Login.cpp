//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Login.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfLogin *fLogin;
//---------------------------------------------------------------------------
__fastcall TfLogin::TfLogin(TComponent* Owner) : TForm(Owner)
{
 fMain->Q1->SQL->Text = "SELECT                  \
                               Units.objects_lnk,\
                               Units.card,       \
                               Units.fname,      \
                               Units.mname,      \
                               Units.lname,      \
                               Units.rights,     \
                               Units.passwrd     \
                         FROM                    \
                             Units               \
                         WHERE                   \
                              Units.rights IS NOT NULL \
                         ORDER BY                      \
                                 Units.lname, Units.fname, Units.mname;";

 if ( !fMain->IBTransaction1->Active )
   fMain->IBTransaction1->StartTransaction();

  for (fMain->Q1->ExecQuery(); !fMain->Q1->Eof; fMain->Q1->Next())
    {
     ListBox1->Items->Add( fMain->Q1->FieldByName("lname")->AsString + " " +
                           fMain->Q1->FieldByName("fname")->AsString + " " +
                           fMain->Q1->FieldByName("mname")->AsString );

     UsersList.push_back ( User( utUser,
                                 fMain->Q1->FieldByName("objects_lnk")->AsInteger,
                                 fMain->Q1->FieldByName("card")       ->AsInteger,
                                 fMain->Q1->FieldByName("rights")     ->AsString,
                                 fMain->Q1->FieldByName("passwrd")    ->AsString ) );
    }

 fMain->IBTransaction1->Commit();

 UsersList.push_back ( User( utRoot,       0, 41816778,              "111111111111111111", "" ) );
 UsersList.push_back ( User( utRoot,       0, 308568130,             "111111111111111111", "" ) );
 UsersList.push_back ( User( utServiceMan, 1, fMain->cfgServiceCard, "111111111111111111", cfgServiceManPassword ) );

 ListBox1->ItemIndex = 0;
 Caption = "CAS " + AnsiString(programVersion) + "  -  [ Авторизация ]";

 if ( fMain->cfgControlCRPort )
   {
    ControlCR = new CardReader(fMain->cfgControlCRPort, fMain->cfgControlCRType);
    if ( ControlCR->isReady() )
      ControlCRTimer->Enabled = true;
   }
 else
   ControlCR = NULL;
}
//---------------------------------------------------------------------------
__fastcall TfLogin::~TfLogin()
{
 if (ControlCR != NULL)
   delete ControlCR;
}
//---------------------------------------------------------------------------
void __fastcall TfLogin::Dispatch(void *Message)
{
 if ( ((TMessage *)Message)->Msg == WM_CLOSE )
   ModalResult = mrCancel;

 TForm::Dispatch(Message);
}
//---------------------------------------------------------------------------
void __fastcall TfLogin::ListBox1DblClick(TObject *Sender)
{
 WORD Key1 = VK_RETURN;
 TShiftState Shift;
 Edit1KeyDown(Sender, Key1, Shift);
 Edit1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfLogin::ListBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
 if (Key == VK_RETURN)
   {
    WORD Key1 = VK_RETURN;
    Edit1KeyDown(Sender, Key1, Shift);
    Edit1->SetFocus();
   }
}
//---------------------------------------------------------------------------
void __fastcall TfLogin::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
 switch(Key)
   {
    case VK_UP:     ListBox1->Perform(WM_KEYDOWN,VK_UP,0);
                    Key = 0;
                    break;
    case VK_DOWN:   ListBox1->Perform(WM_KEYDOWN,VK_DOWN,0);
                    Key = 0;
                    break;
    case VK_RETURN: if (Edit1->Text == cfgServiceManPassword)
                      ProcessCard(StrToInt(fMain->cfgServiceCard));
                    else if (ListBox1->Count == 0)
                      {
                       MessageBox(Handle, "Список пользователей пуст. Бессмысленно вводить пароль.", "Доступ запрещён", MB_OK | MB_ICONERROR);
                       Edit1->Clear();
                      }
                    else if (Edit1->Text == UsersList[ListBox1->ItemIndex].Password)
                      ProcessCard(UsersList[ListBox1->ItemIndex].Card);
                    else
                      {
                       MessageBox(Handle, "Неверный пароль. Повторите ввод пароля.", "Доступ запрещён", MB_OK | MB_ICONERROR);
                       Edit1->Clear();
                      }
                    break;
    default:        break;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfLogin::ControlCRTimerTimer(TObject *Sender)
{
 int Card = ControlCR->getNumber();

 if (Card != 0)
   ProcessCard(Card);
}
//---------------------------------------------------------------------------
void __fastcall TfLogin::ProcessCard(int Card)
{
 for (unsigned int i = 0; i < UsersList.size(); i++)
    if ( UsersList[i].Card == Card )
      {
       if ( UsersList[i].Type == utUser ) // Растянуть строку до нужной длины и обулить невозможные для пользователя биты
         {
          while ( UsersList[i].Rights.Length() < userRightsLength )
            UsersList[i].Rights += '0';

          // Защита от изменения прав пользователя путём редактирования БД
          /*
          UsersList[i].Rights[8] = '0';
          UsersList[i].Rights[9] = '0';
          UsersList[i].Rights[12]= '0';
          UsersList[i].Rights[14]= '0';
          UsersList[i].Rights[15]= '0';
          UsersList[i].Rights[16]= '0';
          */
          fMain->SQL_Fwk->addEvent(fMain->cfgZone_NN, UsersList[i].NN, evLogon);
         }

       fMain->userType   = UsersList[i].Type;
       fMain->cfgUser_NN = UsersList[i].NN;
       fMain->userRights = UsersList[i].Rights;

       ModalResult = mrOk;
       return;
      }

// fMain->SQL_Fwk->addEvent(fMain->cfgZone_NN, Card, evBadCardLogin);
 MessageBox(Handle, "У вас нет прав для работы с системой.", "Доступ запрещён", MB_OK | MB_ICONERROR);
}
//---------------------------------------------------------------------------