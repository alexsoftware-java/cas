//---------------------------------------------------------------------------
#include "_frmupd.h"
#include <stdio.h>
//---------------------------------------------------------------------------
int _cdecl is_digit(char c)
{
if (c<'0') return 0;
if (c>'9') return 0;
return 1;
}
//---------------------------------------------------------------------------
int _cdecl IsFloat(char *c)
{
char *d=c,point=true;
if (!*d) return false;
if (*d=='+' || *d=='-') d++;
while (*d) 
 {
 if ((*d=='.' || *d==',') && point)
  {
  point=false;
  }
 else
  {
  if (!is_digit(*d)) return false;
  }
 d++;
 }
return true;
}
//---------------------------------------------------------------------------
int _cdecl IsInteger(char *c)
{
char *d=c;
if (!*d) return false;
if (*d=='+' || *d=='-') d++;
while (*d) 
 {
 if (!is_digit(*d)) return false;
 d++;
 }
return true;
}
//---------------------------------------------------------------------------
void QUpdateFromAnsiString(TIBQuery *Q1,AnsiString Text,char *field)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,strlen(field)+16+Text.Length());
if (Text.IsEmpty()) sprintf(buf,",%s=NULL",field);
else sprintf(buf,",%s='%s'",field,Text.c_str());
Q1->SQL->Add(buf);
HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void QUpdateDoubleFromAnsiString(TIBQuery *Q1,AnsiString Text,char *field)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,strlen(field)+16+Text.Length());
if (Text.IsEmpty() || !IsFloat(Text.c_str())) sprintf(buf,",%s=NULL",field);
else sprintf(buf,",%s=%f",field,Text.ToDouble());
Q1->SQL->Add(buf);
HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void QUpdateFromInt(TIBQuery *Q1,int value,char *field)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,strlen(field)+16);
sprintf(buf,",%s=%lu",field,value);
Q1->SQL->Add(buf);
HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void QUpdateFromIntNM(TIBQuery *Q1,int value,char *field)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,strlen(field)+16);
if (value==-1)
 {
 sprintf(buf,",%s=NULL",field);
 Q1->SQL->Add(buf);
 }
else QUpdateFromInt(Q1,value,field);
HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void QUpdateFromCombo(TIBQuery *Q1,TComboBox *Box1,TComboBox *Box2,char *field)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,strlen(field)+16);

if (Box1->ItemIndex==-1) sprintf(buf,",%s=NULL",field);
else sprintf(buf,",%s=%lu",field,Box2->Items->Strings[Box1->ItemIndex].ToInt());
Q1->SQL->Add(buf);
HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void FormCombosFromTable(TIBQuery *Q1,TComboBox *Box1,TComboBox *Box2,char *table,int value)
{
FormCombosFromTable_Ex(Q1,Box1,Box2,table,"NAME",NULL,"NAME",value);
}
//---------------------------------------------------------------------------
void FormCombosFromTable_Ex(TIBQuery *Q1,TComboBox *Box1,TComboBox *Box2,char *table,char *field,char *cond,char *order_by,int value)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,strlen(table)+strlen(field)+12);
TField *f;

Q1->SQL->Clear();
sprintf(buf,"SELECT NN,%s",field);
Q1->SQL->Add(buf);
sprintf(buf,"FROM %s",table);
Q1->SQL->Add(buf);
if (cond!=NULL && *cond) Q1->SQL->Add(cond);
if (order_by!=NULL && *order_by)
 {
 sprintf(buf,"ORDER BY %s",order_by);
 Q1->SQL->Add(buf);
 }
//ShowMessage(Q1->SQL->Text.c_str());
Q1->Prepare();
Q1->Open();
Box1->Items->Clear();
Box2->Items->Clear();
while(!Q1->Eof)
 {
 f=Q1->FindField(field);
 Box1->Items->Add(f->Text);
 f=Q1->FindField("NN");
 Box2->Items->Add(f->Text);
 if (!f->Text.IsEmpty() && f->AsInteger==value) Box1->ItemIndex=Box1->Items->Count-1;
 Q1->Next();
 }
Q1->Close();
Q1->UnPrepare();
HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void FormCombosFromPersons(TIBQuery *Q1,TComboBox *Box1,TComboBox *Box2,int value)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,512);
TField *f,*f1,*f2;

Q1->SQL->Clear();
Q1->SQL->Add("SELECT NN,MNAME,LNAME,FNAME");
Q1->SQL->Add("FROM PERSONS");
Q1->SQL->Add("ORDER BY MNAME,LNAME,FNAME");
Q1->Prepare();
Q1->Open();
Box1->Items->Clear();
Box2->Items->Clear();
while(!Q1->Eof)
 {
 f=Q1->FindField("LNAME");
 f1=Q1->FindField("FNAME");
 f2=Q1->FindField("MNAME");
 sprintf(buf,"%s %s %s",f->Text.c_str(),f1->Text.c_str(),f2->Text.c_str());
 Box1->Items->Add(buf);
 f=Q1->FindField("NN");
 Box2->Items->Add(f->Text);
 if (!f->Text.IsEmpty() && f->AsInteger==value) Box1->ItemIndex=Box1->Items->Count-1;
 Q1->Next();
 }
Q1->Close();
Q1->UnPrepare();
HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void QInsertInt(int i,char *fff,char *vvv,char *field)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,16+strlen(field));
sprintf(buf,",%s",field);
strcat(fff,buf);
sprintf(buf,",%lu",i);
strcat(vvv,buf);
HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void QInsertIntNM(int i,char *fff,char *vvv,char *field)
{
if (i!=-1) QInsertInt(i,fff,vvv,field);
}
//---------------------------------------------------------------------------
void QInsertIntFromText(AnsiString Text,char *fff,char *vvv,char *field)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,Text.Length()+4+strlen(field));

if (!Text.IsEmpty() && IsInteger(Text.c_str()))
 {
 sprintf(buf,",%s",field);
 strcat(fff,buf);
 sprintf(buf,",%lu",Text.ToInt());
 strcat(vvv,buf);
 }

HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void QInsertDoubleZFromText(AnsiString Text,char *fff,char *vvv,char *field)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,Text.Length()+4+strlen(field));
if (!Text.IsEmpty() && IsFloat(Text.c_str()))
 {
 sprintf(buf,",%s",field);
 strcat(fff,buf);
 sprintf(buf,",%f",Text.ToDouble());
 strcat(vvv,buf);
 }
else
 {
 sprintf(buf,",%s",field);
 strcat(fff,buf);
 strcat(vvv,",0");
 }
HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void QInsertDoubleFromText(AnsiString Text,char *fff,char *vvv,char *field)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,Text.Length()+4+strlen(field));

if (!Text.IsEmpty() && IsFloat(Text.c_str()))
 {
 sprintf(buf,",%s",field);
 strcat(fff,buf);
 sprintf(buf,",%f",Text.ToDouble());
 strcat(vvv,buf);
 }

HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void QInsertText(AnsiString Text,char *fff,char *vvv,char *field)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,Text.Length()+4+strlen(field));

if (!Text.IsEmpty())
 {
 sprintf(buf,",%s",field);
 strcat(fff,buf);
 sprintf(buf,",'%s'",Text.c_str());
 strcat(vvv,buf);
 }

HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void QInsertIntFromCombo(TComboBox *Box1,TComboBox *Box2,char *fff,char *vvv,char *field)
{
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,Box2->Items->Text.Length()+4+strlen(field));

if (Box1->ItemIndex!=-1)
 {
 sprintf(buf,",%s",field);
 strcat(fff,buf);
 sprintf(buf,",%lu",Box2->Items->Strings[Box1->ItemIndex].ToInt());
 strcat(vvv,buf);
 }

HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
int QCheckExist(TIBQuery *Q1,char *table,char *where)
{
TField *f;
int i;
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,20+strlen(table));
Q1->SQL->Clear();
sprintf(buf,"SELECT NN FROM %s",table);
Q1->SQL->Add(buf);
if (where!=NULL && *where) Q1->SQL->Add(where);
Q1->Prepare();
Q1->Open();
f=Q1->FindField("NN");
if (f->Text.IsEmpty()) i=0;
else i=f->AsInteger;
Q1->Close();
Q1->UnPrepare();
HeapFree(GetProcessHeap(),0,buf);
return i;
}
//---------------------------------------------------------------------------
int QGetStatus(TIBQuery *Q1,char *table,char *where)
{
TField *f;
int i;
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,20+strlen(table));
Q1->SQL->Clear();
sprintf(buf,"SELECT STATUS FROM %s",table);
Q1->SQL->Add(buf);
Q1->SQL->Add(where);
Q1->Prepare();
Q1->Open();
f=Q1->FindField("STATUS");
if (f->Text.IsEmpty()) i=-1;
else i=f->AsInteger;
Q1->Close();
Q1->UnPrepare();
HeapFree(GetProcessHeap(),0,buf);
return i;
}
//---------------------------------------------------------------------------
void QLookupNNFromVal(TIBQuery *Q1,char *table,char *field,char *val,int *nn)
{
TField *f;
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,50+strlen(table)+strlen(field)+strlen(val));
Q1->SQL->Clear();
sprintf(buf,"SELECT NN FROM %s WHERE %s='%s'",table,field,val);
Q1->SQL->Add(buf);
Q1->Prepare();
Q1->Open();
f=Q1->FindField("NN");
if (f->Text.IsEmpty()) *nn=-1;
else *nn=f->AsInteger;
Q1->Close();
Q1->UnPrepare();
HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
void QLookupValFromNN(TIBQuery *Q1,char *table,char *field,char *val,int nn)
{
TField *f;
char *buf=(char *)HeapAlloc(GetProcessHeap(),0,50+strlen(table)+strlen(field));
Q1->SQL->Clear();
sprintf(buf,"SELECT %s FROM %s WHERE NN=%lu",field,table,nn);
Q1->SQL->Add(buf);
Q1->Prepare();
Q1->Open();
f=Q1->FindField(field);
if (f->Text.IsEmpty()) *val=0;
else strcpy(val,f->Text.c_str());
Q1->Close();
Q1->UnPrepare();
HeapFree(GetProcessHeap(),0,buf);
}
//---------------------------------------------------------------------------
int QSeek(TIBQuery *Q1,char *field_name,int NN)
// Перемещает Позицию в запросе к NN, запрос должен быть отсортирован по NN
{
TField *f;
f=Q1->FindField(field_name);
while(1)
 {
 if (f->AsInteger==NN) return true;
 if (f->AsInteger<NN)
  {
  if (Q1->Eof) return false;
  else Q1->Next();
  if (f->AsInteger>NN) return false;
  }
 else
  {
  if (Q1->Bof) return false;
  else Q1->Prior();
  if (f->AsInteger<NN) return false;
  }
 }
}
//---------------------------------------------------------------------------