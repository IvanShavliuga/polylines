//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
void TResults::OnPrint(int Left,int Top,int Width, int Height)
{
        Form1->ListBox1->Clear();
        AnsiString string=AnsiString(Caption);
        if(Caption[0])
        {
          Form1->Caption="";
          Form1->Caption="Results Editor 1.3 -- ["+string+"]";
        }
        for(int i=0; i<Count; i++)
        {
          string=AnsiString(Data[i].Name);
          string+="  ";
          string+=IntToStr(Data[i].Date.Hour);
          string+=":";
          string+=IntToStr(Data[i].Date.Minute);
          string+=":";
          string+=IntToStr(Data[i].Date.Second);
          string+="  ";
          string+=IntToStr(Data[i].Date.Day);
          string+="\\";
          string+=IntToStr(Data[i].Date.Month);
          string+="\\";
          string+=IntToStr(Data[i].Date.Year);
          string+="  ";
          string+=IntToStr(Data[i].Score);

          Form1->ListBox1->Items->Add(string);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender)
{
        Recordes.Create(20);
        Recordes.PrintData();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender)
{
        if(OpenDialog1->Execute())
        {
           AnsiString buf=OpenDialog1->FileName;
           if(!Recordes.Load(buf.c_str()))
           {
             char str[256],str1[256];
             Recordes.GetErrorCode(str);
             MessageBox(0,str,"ошибка",MB_ICONERROR);
           }
        }
        Recordes.PrintData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
       if(SaveDialog1->Execute())
       {
           AnsiString buf=SaveDialog1->FileName;
           Recordes.Save(buf.c_str());
       }
       Recordes.PrintData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        Panel1->Visible=false;
        Recordes.AddData(Edit1->Text.c_str(),Edit2->Text.ToInt());
        Recordes.PrintData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject *Sender)
{
        Panel1->Visible=true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N9Click(TObject *Sender)
{
        AnsiString str=InputBox("Очистка","Введите маску","");
        Recordes.ClearData(str.c_str());
        Recordes.PrintData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N13Click(TObject *Sender)
{
        AnsiString str=InputBox("Измение названия","Новое название","");
        sprintf(Recordes.Caption,str.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N8Click(TObject *Sender)
{
        AnsiString str=InputBox("Удаление результата","Введите номер:","");
        Recordes.DeleteData(str.ToInt());
        Recordes.PrintData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N11Click(TObject *Sender)
{
        char string[256];
        sprintf(string,"Results Editor 1.3\nИванов И. С. г. Новополоцк 2008г.\n"
                       "Размер памяти под класс: %ld",sizeof(TResults));
        MessageBox(0,string,"О программе",MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

