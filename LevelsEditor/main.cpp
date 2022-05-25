//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "level.h"
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

void __fastcall TForm1::N5Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        int x=X/15;
        int y=Y/15;
        if(Button==mbRight)
        {
          if(TabSet1->TabIndex==0) color--;
          if(TabSet1->TabIndex==2) select=false;
          if(TabSet1->TabIndex==1) bonus--;
        }
        else if(Button==mbLeft)
        {
          if(TabSet1->TabIndex==0) color++;
          if(TabSet1->TabIndex==2) select=true;
          if(TabSet1->TabIndex==1) bonus++;
        }
        else
        {
          /*if(TabSet1->TabIndex==0) color=0;
          select=false;
          if(TabSet1->TabIndex==1) bonus=0;*/
        }

        if(TabSet1->TabIndex==0){
          if(color)
            Level.SetupElement(x,y,color,-1,-1,1);
          else
            Level.SetupElement(x,y,color,-1,-1,0);
        }
        else if(TabSet1->TabIndex==1)
          Level.SetupElement(x,y,-1,bonus,-1,-1);
        else
          Level.SetupElement(x,y,-1,-1,-1,select);
        Level.Paint();
}
//---------------------------------------------------------------------------
void PLLevel::Paint(void)
{
        Form1->Image1->Canvas->Font->Size=8;
        Form1->Image1->Canvas->Pen->Color=clWhite;
        Form1->Image1->Canvas->Rectangle(0,0,400,400);
        Form1->Image2->Canvas->Pen->Color=clWhite;
        Form1->Image2->Canvas->Rectangle(0,0,400,400);
        for(int i=0; i<Height; i++)
        {
          for(int j=0; j<Width; j++)
          {
            switch(Matrix[j][i].Color)
            {
              case 0:
                Form1->Image1->Canvas->Font->Color=clWhite;
                break;
              case 1:
                Form1->Image1->Canvas->Font->Color=clNavy;
                break;
              case 2:
                Form1->Image1->Canvas->Font->Color=clRed;
                break;
              case 3:
                Form1->Image1->Canvas->Font->Color=clFuchsia;
                break;
              case 4:
                Form1->Image1->Canvas->Font->Color=clYellow;
                break;
              case 5:
                Form1->Image1->Canvas->Font->Color=clLime;
                break;
              case 6:
                Form1->Image1->Canvas->Font->Color=clAqua;
                break;
              case 7:
                Form1->Image1->Canvas->Font->Color=clGray;
                break;
             default:
                Form1->Image1->Canvas->Font->Color=clBlack;
                break;
            }
            switch(Form1->TabSet1->TabIndex)
            {
              case 0:
                Form1->Image1->Canvas->TextOutA(i*15,j*15,AnsiString(Matrix[j][i].Color+0));
                break;
              case 1:
                Form1->Image1->Canvas->TextOutA(i*15,j*15,AnsiString(Matrix[j][i].Bonus+0));
                break;
              case 2:
                Form1->Image1->Canvas->TextOutA(i*15,j*15,AnsiString(Matrix[j][i].Data+0));
                break;

            }
          }
        }
        for(int i=0; i<5; i++)
        {
          switch(Form1->TabSet1->TabIndex)
          {
            case 0:
              Form1->Image2->Canvas->TextOutA(i*15,0,AnsiString(Buffer[i].Color+0));
              break;
            case 1:
              Form1->Image2->Canvas->TextOutA(i*15,0,AnsiString(Buffer[i].Bonus+0));
              break;
            case 2:
              Form1->Image2->Canvas->TextOutA(i*15,0,AnsiString(Buffer[i].Data+0));
              break;
          }
        }
        Form1->CaptionLevel->Text=AnsiString(Caption);
        Form1->GameName->Text=AnsiString(Game);
        Form1->NumberLevel->Text=Number;
        Form1->ModeGame->ItemIndex=ModeGame;
        Form1->MaxScore->Text=AnsiString(ScoreMax);
        Form1->MinScore->Text=AnsiString(ScoreMin);
}

void __fastcall TForm1::TabSet1Click(TObject *Sender)
{
         Level.Paint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        Level.SelectBall(0);
        Level.SelectColomn(0);
        if(Level.AddBalls())
          MinScore->Text=AnsiString(Level.Run());

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
        AnsiString str=InputBox("Открыть","Введите номер уровня:","0");
        AnsiString buf=InputBox("Открыть","Введите номер режима:","0");
        int num=str.ToInt(),mode=buf.ToInt();
        if(!Level.LoadPL(mode,num))
        {
          char str[100];
          sprintf(str,"Ошибка %d",Level.GetErrorCode());
          MessageBox(0,"Файл не найден",str,MB_ICONSTOP);
        }
        Level.Paint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        Level=PLLevel(CaptionLevel->Text.c_str(),ModeGame->ItemIndex,
          NumberLevel->Text.ToInt(),MinScore->Text.ToInt(),MaxScore->Text.ToInt());
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
        Level.SavePL();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        Level=PLLevel("Тест",0,0,0,300);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        Level.Analisator();        
}
//---------------------------------------------------------------------------

