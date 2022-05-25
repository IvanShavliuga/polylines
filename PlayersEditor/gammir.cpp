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
void __fastcall TForm1::Memo1Change(TObject *Sender)
{
        AnsiString str;
        if(Memo1->Lines->Text.Length()>0&&Memo4->Lines->Text.Length()>0)
          N3->Enabled=true;
        else
          N3->Enabled=false;
        str=Memo1->Lines->Text;
        if(str.Length()>MaxLength-10)
        {
          str.SetLength(MaxLength-10);
          Memo1->Clear();
          Memo1->Lines->Add(str);
        }
        ToolButton13->Enabled=N3->Enabled;
        Memo2->Clear();
        Memo3->Clear();
        Memo2->Lines->Add(Dvoid(Memo1->Lines->Text));
        Memo3->Lines->Add(Dec(Memo1->Lines->Text));
        
}
//---------------------------------------------------------------------------
AnsiString TForm1::Dvoid(AnsiString string)
{
        unsigned long i,j;
        char chars[MaxLength],b[30],code;
        AnsiString res,buf;
        if(string.Length()>MaxLength)
          string.SetLength(MaxLength);
        if(string.Length()==0) return "";
        string=string.UpperCase();
        sprintf(chars,"%s",string.c_str());
        res="";

        for(i=0; i<string.Length(); i++)
        {
           switch(alfavit)
           {
             case 1:      // Англ
               code=chars[i]-'A';
               break;
             case 0:      // Русский
               code=chars[i]-'А';
               break;
             default:
               code=chars[i]-'А';
               break;
           }
           if(code<0||code>=32)
             continue;

           itoa(code,b,2);
           buf.sprintf("%s",b);
           res+=buf+" ";
           
        }
        return res;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        M=32;
        A=5;
        C=3;
        X0=13;
        alfavit=0;
}
//---------------------------------------------------------------------------
AnsiString TForm1::Dec(AnsiString string)
{
        unsigned long i;
        char chars[MaxLength],b[17],code;
        AnsiString res,buf;
        if(string.Length()>MaxLength)
          string.SetLength(MaxLength);
        if(string.Length()==0) return "";
        string=string.UpperCase();
        sprintf(chars,"%s",string.c_str());
        res="";
        for(i=0; i<string.Length(); i++)
        {
           switch(alfavit)
           {
             case 1:
               code=chars[i]-'A';
               break;
             case 0:
               code=chars[i]-'А';
               break;
             default:
               code=chars[i]-'А';
               break;
           }
           if(code>=0&&code<32)
           {
             buf.sprintf("%03d",code);
             res+=buf+" ";
           }
        }
        return res;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Memo5Change(TObject *Sender)
{
        AnsiString str;
        if(Memo5->Lines->Text.Length()>0&&Memo4->Lines->Text.Length()>0)
          N4->Enabled=true;
        else
          N4->Enabled=false;
        str=Memo1->Lines->Text;
        if(str.Length()>MaxLength-10)
        {
          str.SetLength(MaxLength-10);
          Memo1->Clear();
          Memo1->Lines->Add(str);
        }
        ToolButton14->Enabled=N4->Enabled;
        Memo6->Clear();
        Memo7->Clear();
        Memo6->Lines->Add(Dvoid(Memo5->Lines->Text));
        Memo7->Lines->Add(Dec(Memo5->Lines->Text));

}
//---------------------------------------------------------------------------
AnsiString TForm1::GetGamma(int len)
{
        unsigned long i;
        char code;
        char chars[MaxLength];
        AnsiString res;
        for(i=0; i<MaxLength; i++)
          chars[i]='\0';
        chars[0]=X0;
        if(len==0 ||len>MaxLength) len=MaxLength;
        for(i=1; i<len; i++)
        {
          chars[i]=(A*chars[i-1]+C)%M;
        }
        for(i=0; i<len; i++)
        {
           switch(alfavit)
           {
             
             case 1:
               chars[i]+='A';
               break;
             case 0:
               chars[i]+='А';
               break;
             default:
               chars[i]+='А';
               break;
           }


        }
        chars[len]='\0';
        dlina=len;
        res.sprintf("%s",chars);
        return res.UpperCase();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Memo4Change(TObject *Sender)
{
        Memo9->Clear();
        Memo8->Clear();
        Memo9->Lines->Add(Dvoid(Memo4->Lines->Text));
        Memo8->Lines->Add(Dec(Memo4->Lines->Text));

}
//---------------------------------------------------------------------------
void __fastcall TForm1::New1Click(TObject *Sender)
{
        Memo1->Clear();
        Memo4->Clear();
        Memo5->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Exit1Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
        unsigned long i,len;
        int res;
        res=Form2->ShowModal();
        if(res==mrOk)
        {
          if(Memo1->Lines->Text.Length()>0)
            N3->Enabled=true;
          if(Memo5->Lines->Text.Length()>0)
            N4->Enabled=true;
          ToolButton13->Enabled=N3->Enabled;
          ToolButton14->Enabled=N4->Enabled;

          A=Form2->CSpinEdit1->Value;
          C=Form2->CSpinEdit2->Value;
          X0=Form2->CSpinEdit3->Value;
          M=Form2->CSpinEdit4->Value;
          alfavit=Form2->ComboBox1->ItemIndex;
          len=MaxLength;
          if(Memo1->Lines->Text.Length()>0&&
              Memo1->Lines->Text.Length()>Memo5->Lines->Text.Length())
          len=Memo1->Lines->Text.Length();
          else len=Memo5->Lines->Text.Length();
          gamma=GetGamma(len);
          Memo4->Clear();
          Memo4->Lines->Add(gamma);
          Memo1Change(Sender);
          Memo5Change(Sender);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Open1Click(TObject *Sender)
{
       if(OpenDialog1->Execute())
        {
          if(!FileExists(OpenDialog1->FileName))
          {
            MessageBox(0,"Файл не существует.","Гаммирование",MB_OK|MB_ICONINFORMATION);
            return;
          }
          if(OpenDialog1->FilterIndex==1)
            Memo1->Lines->LoadFromFile(OpenDialog1->FileName);
          if(OpenDialog1->FilterIndex==2)
            Memo5->Lines->LoadFromFile(OpenDialog1->FileName);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
        char string1[MaxLength],string2[MaxLength];
        char string3[MaxLength],k;
        AnsiString res;
        unsigned long i;
        sprintf(string1,"%s",Memo1->Lines->Text.c_str());
        sprintf(string2,"%s",gamma.c_str());
        switch(alfavit)
           {
             case 1:
               k='A';
               break;
             case 0:
               k='А';
               break;
             default:
               k='А';
               break;
           }

        for(i=0; i<Memo1->Lines->Text.Length();i++)
        {
          if(string1[i]<k||string2[i]<k||
             string1[i]=='\n'||string2[i]=='\n'||
             string1[i]=='\r'||string2[i]=='\r')
          {
            string3[i]=string1[i];
            continue;
          }


         
          string1[i]-=k;
          string2[i]-=k;
          string3[i]=string1[i]^string2[i];
          string3[i]+=k;

        }
        string3[Memo1->Lines->Text.Length()]='\0';
        res.sprintf("%s",string3);
        if(dlina<Memo5->Lines->Text.Length()) res.SetLength(dlina);
        Memo5->Clear();
        Memo5->Lines->Add(res);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Save1Click(TObject *Sender)
{
        if(SaveDialog1->Execute())
        {
          if(SaveDialog1->FilterIndex==1)
            Memo1->Lines->SaveToFile(SaveDialog1->FileName);
          else
            Memo5->Lines->SaveToFile(SaveDialog1->FileName);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
        char string1[MaxLength],string2[MaxLength];
        char string3[MaxLength],k;
        AnsiString res;
        unsigned long i;
        sprintf(string1,"%s",Memo5->Lines->Text.c_str());
        sprintf(string2,"%s",gamma.c_str());
        switch(alfavit)
           {
             case 1:
               k='A';
               break;
             case 0:
               k='А';
               break;
             default:
               k='А';
               break;
           }
        for(i=0; i<Memo5->Lines->Text.Length();i++)
        {
          if(string1[i]<k||string2[i]<k||
             string1[i]=='\n'||string2[i]=='\n'||
             string1[i]=='\r'||string2[i]=='\r')
          {
            string3[i]=string1[i];
            continue;
          }
          string1[i]-=k;
          string2[i]-=k;
          string3[i]=string1[i]^string2[i];
          string3[i]+=k;

        }
        string3[Memo5->Lines->Text.Length()]='\0';
        res.sprintf("%s",string3);
        if(dlina<Memo5->Lines->Text.Length()) res.SetLength(dlina);
        Memo1->Clear();
        Memo1->Lines->Add(res);

}               
//---------------------------------------------------------------------------


void __fastcall TForm1::N10Click(TObject *Sender)
{
        AboutBox->ShowModal();        
}
//---------------------------------------------------------------------------

