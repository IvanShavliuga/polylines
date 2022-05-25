//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        strcpy(Players.CaptionGame,"PolyLines 1.0\0");
        LabeledEdit6->Enabled=false;
        LabeledEdit4->Enabled=false;
        LabeledEdit5->Enabled=false;       
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
        if(SaveDialog1->Execute())
          Players.SaveAsIV2(SaveDialog1->FileName.c_str());
        LabeledEdit6->Enabled=false;
        LabeledEdit4->Enabled=false;
        LabeledEdit5->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
        if(Players.AddPlayer(LabeledEdit1->Text.c_str(),
                          LabeledEdit2->Text.c_str(),
                          LabeledEdit3->Text.c_str()))
          ComboBox1->Items->Add(LabeledEdit1->Text);
        LabeledEdit6->Enabled=true;
        LabeledEdit4->Enabled=true;
        LabeledEdit5->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
        AnsiString str;
        ComboBox1->Items->Clear();
        ComboBox1->Text="";
        if(OpenDialog1->Execute())
        {
          if(!Players.LoadAsIV2(OpenDialog1->FileName.c_str()))
          {
            char buf[80];
            sprintf(buf,"файл не найден или взломан (Error=%d)",Players.Error);
            MessageBox(0,buf,"PlayersEditor 1.0",MB_ICONSTOP);
          }
          else
          {
            for(int i=0; i<Players.Count; i++)
            {
              str=AnsiString(Players.GetName(i));
              ComboBox1->Items->Add(str);
            }
          }
        }
        LabeledEdit6->Enabled=false;
        LabeledEdit4->Enabled=false;
        LabeledEdit5->Enabled=false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N7Click(TObject *Sender)
{
        if(Players.DeletePlayer(LabeledEdit1->Text.c_str(),LabeledEdit2->Text.c_str()))
          ComboBox1->Items->Delete(Players.Select);
        else
          MessageBox(0,"Пароль неверен или не введен","PlayersEditor 1.0",MB_ICONSTOP);
        LabeledEdit6->Enabled=false;
        LabeledEdit4->Enabled=false;
        LabeledEdit5->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
        LabeledEdit1->Text=ComboBox1->Text;
        LabeledEdit6->Enabled=false;
        LabeledEdit4->Enabled=false;
        LabeledEdit5->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
        if(Players.SelectPlayer(LabeledEdit1->Text.c_str(),LabeledEdit2->Text.c_str(),
           email,&score,&energy,&wins,&games,&reyting))
        {
          LabeledEdit3->Text=AnsiString(email);
          LabeledEdit6->Text=AnsiString(score);
          LabeledEdit4->Text=AnsiString(wins);
          LabeledEdit5->Text=AnsiString(games);
          LabeledEdit6->Enabled=true;
          LabeledEdit4->Enabled=true;
          LabeledEdit5->Enabled=true;
        }
        else
          MessageBox(0,"Пароль неверен или невведен","PlayersEditor 1.0",MB_ICONERROR);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        if(LabeledEdit4->Enabled)
          wins=LabeledEdit4->Text.ToInt();
        Players.ChangePlayer(LabeledEdit1->Text.c_str(),LabeledEdit2->Text.c_str(),
          email,score,energy,wins,games);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
        if(LabeledEdit6->Enabled)
          score=LabeledEdit6->Text.ToInt();
        Players.ChangePlayer(LabeledEdit1->Text.c_str(),LabeledEdit2->Text.c_str(),
          email,score,energy,wins,games);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
        if(LabeledEdit5->Enabled)
          games=LabeledEdit5->Text.ToInt();
        Players.ChangePlayer(LabeledEdit1->Text.c_str(),LabeledEdit2->Text.c_str(),
          email,score,energy,wins,games);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        if(LabeledEdit3->Enabled)
          strcpy(email,LabeledEdit3->Text.c_str());
        Players.ChangePlayer(LabeledEdit1->Text.c_str(),LabeledEdit2->Text.c_str(),
          email,score,energy,wins,games);
}
//---------------------------------------------------------------------------

