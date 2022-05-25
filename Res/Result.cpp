//---------------------------------------------------------------------------


#pragma hdrstop

#include "Result.h"
TResults::TResults()
{
  Select=-1;
  Count=0;
  strcpy(Caption,"");
}
//---------------------------------------------------------------------------
void TResults::Save(char Name[256])
{
  FILE *file=fopen(Name,"wb");      //Открыть файл
  char Buffer[256];                     //Данные
  long s;
  ErrorCode=0;                      //Код ошибки
  SetupKeys();
  fprintf(file,"IV2RESULTS");
  fputc(X0,file);
  fputc(A,file);
  fputc(C,file);
  s=X0+A+C;
  fputc(s/256,file);
  fputc(s%256,file);
  for(int i=0; i<256; i++)
  {
    if(i>strlen(Caption))
      Caption[i]=0;
    s+=Caption[i];
  }
  s+=Count;
  fwrite(Kodir(Caption,256),1,256,file);
  fputc(Count,file);
  fputc(s/256,file);
  fputc(s%256,file);
  for(int i=0; i<Count;i++)
  {
    s=0;
    for(int j=0; j<256; j++)
    {
      if(j>strlen(Data[i].Name))
        Data[i].Name[j]=0;
      s+=Data[i].Name[j];
    }
    fwrite(Kodir(Data[i].Name,256),1,256,file);
    for(int j=0; j<256; j++)
      Buffer[j]=0;
    Buffer[0]=Data[i].Date.Hour;
    Buffer[1]=Data[i].Date.Minute;
    Buffer[2]=Data[i].Date.Second;
    Buffer[3]=Data[i].Date.Day;
    Buffer[4]=Data[i].Date.Month;
    Buffer[5]=Data[i].Date.Year/100;
    Buffer[6]=Data[i].Date.Year%100;
    for(int j=0; j<7; j++)
      s+=Buffer[j];
    fwrite(Kodir(Buffer,7),1,7,file);
    sprintf(Buffer,"%010ld",Data[i].Score);
    for(int j=0; j<10;j++)
      s+=Buffer[j];
    fwrite(Kodir(Buffer,10),1,10,file);
    fputc(s/256,file);
    fputc(s%256,file);
  }
  fflush(file);
  fclose(file);
}
//Загрузка

//Анализатор кода ошибки
void TResults::GetErrorCode(char Error[256])
{
  switch(ErrorCode)
  {
     case 0:  strcpy(Error,"Выполнено успешно\0");          break;
     case 1:  strcpy(Error,"Файл результатов не найден\0"); break;
     case 2:  strcpy(Error,"Неверный формат файла\0");      break;
     case 3:  strcpy(Error,"Неверна задана дата\0");        break;
     case 4:  strcpy(Error,"Не хватает памяти\0");          break;
     default: strcpy(Error,"Ошибка неопознана\0");          break;
  }
}

TData TResults::GetData(int Index)
{
  return Data[Index];
}
void TResults::ClearData(void)
{
  for(int i=0; i<Count; i++)
  {
     strnset(Data[i].Name,0,256);
     Data[i].Score      =0;
     Data[i].Date.Second=0;
     Data[i].Date.Minute=0;
     Data[i].Date.Hour  =0;
     Data[i].Date.Day   =0;
     Data[i].Date.Month =0;
     Data[i].Date.Year  =0;
  }

}
void TResults::AddData(TData data)
{
  int i=0;
  if(!Count)
  {
    Data[0]=data;
    Count++;
    return;
  }
  while(data.Score<Data[i].Score)
  {
    if(i==Count)  {
      return;
    }
    i++;
  }
  for(int j=Count; j>i; j--) Data[j]=Data[j-1];
  Data[i]=data;
  if(Count<MAXRESULTS)        Count++;

}
void TResults::PrintData(void)
{
  int maxlen=0;
  char string[512];
  for(int i=0; i<Count; i++)
  {
    sprintf(string,"%s %ld",Data[i].Name,Data[i].Score);
    int len=strlen(string)+2+1+2+1+2+1+2+1+2+1+4;
    if(len>maxlen)
      maxlen=len;
  }
  OnPrint(0,0,maxlen,Count);

}
void TResults::DeleteData(int Index)
{
  if(!Count||Index>=Count)
  {
    return;
  }
  for(int i=Index+1; i<Count; i++)
    Data[i-1]=Data[i];
  Count--;
}
bool TResults::Load(char Name[256])
{
  FILE *file=fopen(Name,"rb");      //Открыть файл
  ErrorCode=0;                      //Код ошибки
  long s=0, et=0;
  char Buffer[256];
  if(!file){
    ErrorCode=1;
    return false;
  }
  fread(Buffer,1,10,file);
  Buffer[10]=0;
  if(strcmp(Buffer,"IV2RESULTS"))
  {
    fclose(file);
    ErrorCode=2;
    return false;
  }
  int x0=fgetc(file);
  int  a=fgetc(file);
  int  c=fgetc(file);
  et=fgetc(file)*256+fgetc(file);
  s=x0+a+c;
  if(et!=s){
    ErrorCode=2;
    fclose(file);
    return false;
  }
  else{
    X0=x0;
    A=a;
    C=c;
  }
  fread(Buffer,1,256,file);
  strcpy(Caption,Kodir(Buffer,256));
  for(int i=0; i<256; i++)
    s+=Caption[i];
  Count=fgetc(file);
  s+=Count;
  et=fgetc(file)*256+fgetc(file);
  if(et!=s){
    Count=0;
    Caption[0]=0;
    fclose(file);
    ErrorCode=2;
    return false;
  }
  for(int i=0; i<Count; i++)
  {
    fread(Buffer,1,256,file);
    strcpy(Data[i].Name,Kodir(Buffer,256));
    s=0;
    for(int j=0; j<256; j++)
      s+=Data[i].Name[j];
    fread(Buffer,1,7,file);
    strcpy(Buffer,Kodir(Buffer,7));
    for(int j=0; j<7; j++)
      s+=Buffer[j];
    Data[i].Date.Hour=Buffer[0];
    Data[i].Date.Minute=Buffer[1];
    Data[i].Date.Second=Buffer[2];
    Data[i].Date.Day=Buffer[3];
    Data[i].Date.Month=Buffer[4];
    Data[i].Date.Year=Buffer[5]*100+Buffer[6];
    fread(Buffer,1,10,file);
    strcpy(Buffer,Kodir(Buffer,10));
    Data[i].Score=atol(Buffer);
    for(int j=0; j<10; j++)
      s+=Buffer[j];
    et=fgetc(file)*256+fgetc(file);
    if(et!=s){
       ErrorCode=2;
       Count=0;
       Caption[0]=0;
       fclose(file);
       return false;
    }
  }
  return true;
}


void TResults::ClearData(char Mask[256])
{
   ClearData();
   for(int i=0; i<Count; i++)
     strcpy(Data[i].Name,Mask);

}

void TResults::AddData(char Name[256],long Score)
{
    TData data;
    DateAndTime dt;
    char string[30],buf[30];
    long t;
    time(&t);
    sprintf(string,"%s",ctime(&t));
    strnset(buf,0,30);
    for(int i=0; i<3; i++)
      buf[i]=string[i+4];
    if(!stricmp(buf,"jan"))      dt.Month=1;
    else if(!stricmp(buf,"feb")) dt.Month=2;
    else if(!stricmp(buf,"mar")) dt.Month=3;
    else if(!stricmp(buf,"apr")) dt.Month=4;
    else if(!stricmp(buf,"may")) dt.Month=5;
    else if(!stricmp(buf,"jun")) dt.Month=6;
    else if(!stricmp(buf,"jul")) dt.Month=7;
    else if(!stricmp(buf,"aug")) dt.Month=8;
    else if(!stricmp(buf,"sep")) dt.Month=9;
    else if(!stricmp(buf,"oct")) dt.Month=10;
    else if(!stricmp(buf,"nov")) dt.Month=11;
    else if(!stricmp(buf,"dec")) dt.Month=12;
    else                         dt.Month=0;
    strnset(buf,0,30);
    for(int i=0; i<2; i++)
      buf[i]=string[i+8];
    dt.Day=atoi(buf);
    strnset(buf,0,30);
    for(int i=0; i<2; i++)
      buf[i]=string[i+11];
    dt.Hour=atoi(buf);
    strnset(buf,0,30);
    for(int i=0; i<2; i++)
      buf[i]=string[i+14];
    dt.Minute=atoi(buf);
    strnset(buf,0,30);
    for(int i=0; i<2; i++)
      buf[i]=string[i+17];
    dt.Second=atoi(buf);
    for(int i=0; i<4; i++)
      buf[i]=string[i+20];
    dt.Year=atoi(buf);
    strcpy(data.Name,Name);
    data.Date=dt;
    data.Score=Score;
    AddData(data);
}
void TResults::Create(int count)
{
    TData data;
    DateAndTime dt;
    char string[30],buf[30];
    long t;
    time(&t);
    Count=0;
    sprintf(string,"%s",ctime(&t));
    strnset(buf,0,30);
    for(int i=0; i<3; i++)
      buf[i]=string[i+4];
    if(!stricmp(buf,"jan"))      dt.Month=1;
    else if(!stricmp(buf,"feb")) dt.Month=2;
    else if(!stricmp(buf,"mar")) dt.Month=3;
    else if(!stricmp(buf,"apr")) dt.Month=4;
    else if(!stricmp(buf,"may")) dt.Month=5;
    else if(!stricmp(buf,"jun")) dt.Month=6;
    else if(!stricmp(buf,"jul")) dt.Month=7;
    else if(!stricmp(buf,"aug")) dt.Month=8;
    else if(!stricmp(buf,"sep")) dt.Month=9;
    else if(!stricmp(buf,"oct")) dt.Month=10;
    else if(!stricmp(buf,"nov")) dt.Month=11;
    else if(!stricmp(buf,"dec")) dt.Month=12;
    else                         dt.Month=0;
    strnset(buf,0,30);
    for(int i=0; i<2; i++)
      buf[i]=string[i+8];
    dt.Day=atoi(buf);
    strnset(buf,0,30);
    for(int i=0; i<2; i++)
      buf[i]=string[i+11];
    dt.Hour=atoi(buf);
    strnset(buf,0,30);
    for(int i=0; i<2; i++)
      buf[i]=string[i+14];
    dt.Minute=atoi(buf);
    strnset(buf,0,30);
    for(int i=0; i<2; i++)
      buf[i]=string[i+17];
    dt.Second=atoi(buf);
    for(int i=0; i<4; i++)
      buf[i]=string[i+20];
    dt.Year=atoi(buf);
    strcpy(data.Name,"Аноним");
    data.Score=0;
    data.Date=dt;
    for(int i=0; i<count; i++)
      AddData(data);
    strcpy(Caption,"Turnament Results\0");
  
}
char * TResults::Kodir(char *str,int len)
{
        char *res = new char[len];
        char x1=X0,x2=X0;
        for(int i=0; i<len; i++)
        {
          res[i]=str[i]^x2;
          x1=x2;
          x2=(A^x1+C)%256;
        }
        return res;
}
void TResults::SetupKeys(void)
{
        A=17;
        C=5;
        randomize();
        X0=random(256);
}
#pragma package(smart_init)

