#ifndef _Structures
#define _Structures

//--------------------------------------------------------------------------//

#define programVersion        "1.9.15"
//#define programName           "СКД - Предприятие для ОАО \"Красный пролетарий\"  v" programVersion
#define programName           "СКД - Школа  v" programVersion
#define programDBVersion      197
#define userRightsLength      18
#define cfgServiceManPassword "20scarlett00"
//#define cfgServiceManPassword    "qqq"

//--------------------------------------------------------------------------//

enum EventTypes
{ 
 evNotRegisteredExit            = -13,
 evExitWithExpiredCardAttempt   = -12,
 evExitWithDisabledCardAttempt  = -11,
 evManualExitDeviceOpening      = -3,
 evManualExit                   = -2,
 evExit                         = -1,
 evFirstUse                     =  0,
 evEntry                        =  1,
 evManualEntry                  =  2,
 evManualEntryDeviceOpening     =  3,
 evEntryWithDisabledCardAttempt =  11,
 evEntryWithExpiredCardAttempt  =  12,
 evNotRegisteredEntry           =  13,
 evUnsuccessfullyLoginAttempt   =  21,
 evLogon                        =  22,
 evPCShutdown                   =  23,
 evKPPStart                     =  24,
 evKPPStop                      =  25,
 evGuestCardIssue               =  30,
 evExitWithGuestCardUsingWrongKPPAttempt = 31,
 evSMSSent                      =  40,
 evSMSSendingError              =  41,
 evMealDiscount                          = 50,
 evMealDiscountAttempt                   = 51,
 evMealDiscountWithDisabledCardAttempt   = 52,
 evMealDiscountWithExpiredCardAttempt    = 53
};

//--------------------------------------------------------------------------//

enum UserTypes
{ 
 utRoot,
 utServiceMan,
 utUser
};

//--------------------------------------------------------------------------//

#pragma warn -inl
struct User
{
        int Type;
        int NN;
        int Card;
 AnsiString Rights;
 AnsiString Password;

 User(int Type_,   int NN_, int Card_,   AnsiString Rights_, AnsiString Password_) :
      Type(Type_), NN(NN_), Card(Card_), Rights(Rights_),    Password(Password_)  {}
};
#pragma warn .inl

//--------------------------------------------------------------------------//

struct TTreeViewDataItem
{
 int NN;
 int OType;
 TTreeViewDataItem(int NN_, int OType_)    :
                   NN(NN_), OType(OType_) {}
};

//--------------------------------------------------------------------------//
#endif