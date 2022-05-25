//---------------------------------------------------------------------------


#pragma hdrstop

#include "Level.h"
TLevel::TLevel()
{
        randomize();
        Width=Height=ScoreMin=ScoreMax=0;
        X0=A=C=0;
        M=256;
        ModeGame=-1;
        Number=-1;
        ScoreMin=0;
        ScoreMax=0;
        Width=50;
        Height=50;
        Score=0;
        for(unsigned char i=0; i<100; i++)
          Game[i]=Caption[i]=0;
}
TLevel::TLevel(char game[100],char caption[100],long ScoreMin,long ScoreMax,
          unsigned int number,unsigned int modegame,unsigned char width,unsigned char height)
{
        for(unsigned char i=0; i<100; i++)
          Game[i]=Caption[i]=0;
        strcpy(Game,game);
        strcpy(Caption,caption);
        TLevel::ScoreMin=ScoreMin;
        TLevel::ScoreMax=ScoreMax;
        Number=number;
        ModeGame=modegame;
        Width=width;
        Height=height;
        Score=0;
}
//---------------------------------------------------------------------------
bool TLevel::Load(char Name[100])
{
  FILE *file=fopen(Name,"rb");      //Открыть файл
  ErrorCode=0;                      //Код ошибки
  if(!file){                        //Файл не найден
    ErrorCode=1;
    return false;
  }
  char string[100];                 //буфер
  fread(string,1,8,file);
  string[8]=0;
  if(strcmp(string,"IV2LEVEL"))
  {
     ErrorCode=2;
     return false;
  }
  int x0=X0,a=A,c=C;
  X0=fgetc(file);
  A=fgetc(file);
  C=fgetc(file);
  int s=0;
  int mod2=X0+A+C;
  fread(string,1,100,file);
  strcpy(Game,Kodir(string,100));
  for(unsigned char i=0; i<100; i++)
  {
     if(i>=strlen(Game))
       Game[i]=0;
     s+=Game[i];
  }
  mod2+=s;
  s=0;
  fread(string,1,100,file);
  strcpy(Caption,Kodir(string,100));
  for(unsigned char i=0; i<100; i++)
  {
     if(i>=strlen(Caption))
       Caption[i]=0;
     s+=Caption[i];
  }
  mod2+=s;
  s=0;
  fread(string,1,20,file);
  char buffer[20];
  strcpy(buffer,Kodir(string,20));
  for(unsigned char i=0; i<10; i++)
  {
     s+=buffer[i];
  }
  mod2+=s;
  s=0;
  for(unsigned char i=0; i<10; i++)
  {
     s+=buffer[i+10];
  }
  mod2+=s;
  for(unsigned char i=0; i<20; i++)
    string[i]=0;
  for(unsigned char i=0; i<10; i++)
    string[i]=buffer[i];
  ScoreMin=atol(string);
  for(unsigned char i=0; i<20; i++)
    string[i]=0;
  for(unsigned char i=0; i<10; i++)
    string[i]=buffer[i+10];
  ScoreMax=atol(string);
  ModeGame=fgetc(file);
  Number=fgetc(file);
  mod2+=ModeGame+Number;
  Width=fgetc(file);
  mod2+=Width;
  Height=fgetc(file);
  mod2+=Height;
  int etalon=fgetc(file)*256+fgetc(file);
  ErrorCode=mod2^etalon;
  if(ErrorCode)
  {
    Caption[0]=0;
    Game[0]=0;
    ScoreMax=ScoreMin=0;
    Width=Height=0;
    X0=x0;
    A=a;
    C=c;
    return false;
  }
  for(unsigned char i=0; i<Height; i++)
  {
    for(unsigned char  j=0; j<Width; j++)
    {
      char a1=fgetc(file);
      char b=fgetc(file);
      char c1=fgetc(file);
      char d=fgetc(file);
      if((a1^b)!=d)
      {
        A=a;
        X0=x0;
        C=c;
        Caption[0]=0;
        Number=-1;
        ErrorCode=i<<8+j;
        return false;
      }
      Matrix[i][j].Color=a1;
      Matrix[i][j].Bonus=b;
      Matrix[i][j].Data=c1;
    }
  }
  for(unsigned char  j=0; j<10; j++)
    {
    char a1=fgetc(file);
    char b=fgetc(file);
    char c1=fgetc(file);
    char d=fgetc(file);
    if((a1^b)!=d)
    {
      A=a;
      X0=x0;
      C=c;
      Caption[0]=0;
      Number=-1;
      ErrorCode=1<<13+j;
      return false;
    }
    Buffer[j].Color=a1;
    Buffer[j].Bonus=b;
    Buffer[j].Data=c1;
  }
  Score=0;
  fclose(file);                     //Закрыть файл
  return true;
}
//Сохранеие уровня в файл
void TLevel::Save(char Name[100])
{
  SetupKeys(random(256),17,5);             //Сгенерировать ключи
  FILE *file=fopen(Name,"wb");   //Открыть файл
  fprintf(file,"IV2LEVEL");      //Распознователь моего формата
  int mod2,s=0;                //Флаги четности, сумма
  char string[100];  //буфер
  fputc(X0,file);                //Пишем ключи
  fputc(A,file);
  fputc(C,file);                                        //2 1 0
  mod2=X0+A+C;   //Флаги четности в байте C A X0
  for(unsigned char i=0; i<100; i++)       //Суммируем символы в Game
  {
    if(i>=strlen(Game))          //Обнуляем ненужные
      Game[i]=0;
    s+=Game[i];
  }
  mod2+=s;                //Флаг четности 3-й бит
  fwrite(Kodir(Game,100),1,100,file);  //Шифровка и запись
  s=0;                           //Суммируем символы в Caption
  for( unsigned char i=0; i<100; i++)
  {
    if(i>=strlen(Caption))
      Caption[i]=0;
    s+=Caption[i];
  }
  mod2+=s;                //Флаг четности 4-й бит
  fwrite(Kodir(Caption,100),1,100,file);
  //Тоже самое и для ScoreMin и ScoreMax
  sprintf(string,"%010ld%010ld\0\0",ScoreMin,ScoreMax);
  s=0;
  for( unsigned char i=0; i<10; i++) s+=string[i];
  mod2+=s;
  s=0;
  for( unsigned char i=0; i<10; i++) s+=string[i+10];
  mod2+=s;
  fwrite(Kodir(string,20),1,20,file);
  fputc(ModeGame,file);
  fputc(Number,file);
  mod2+=ModeGame+Number;
  fputc(Width,file);                 //Ширина
  mod2+=Width;
  fputc(Height,file);                //Высота
  mod2+=Height;
  fputc(mod2/256,file);                  //Флаги
  fputc(mod2%256,file);                  //Флаги
  for(unsigned char i=0; i<Height; i++)        //Запись матрицы
  {
    for(unsigned char j=0; j<Width; j++)
    {
       fputc(Matrix[i][j].Color,file);  //Цвет
       fputc(Matrix[i][j].Bonus,file);  //Бонус
       fputc(Matrix[i][j].Data,file);   //Выделение
       fputc(Matrix[i][j].Color^Matrix[i][j].Bonus,file);
    }

  }
  for(unsigned char i=0; i<10; i++)
  {
    fputc(Buffer[i].Color,file);  //Цвет
    fputc(Buffer[i].Bonus,file);  //Бонус
    fputc(Buffer[i].Data,file);   //Выделение
    fputc(Buffer[i].Color^Buffer[i].Bonus,file);
  }
  fclose(file);
}

int TLevel::GetErrorCode(void)
{
   return ErrorCode;
}
unsigned char * TLevel::Kodir(unsigned char *str, int len)
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
unsigned char * TLevel::DeKodir(unsigned  char *string, int length)
{
        unsigned char *result= new char[length];
        unsigned char *keys= new char[length];
        keys[0]=X0;
        for(int i=1; i<length; i++)
          keys[i]=(A*keys[i-1]+C)%M;
        for(int i=0; i<length; i++)
          result[i]=keys[i]^string[i];
        return result;
}
void TLevel::SetupKeys(short x0,short a, short c)
{
        X0=x0;
        A=a;
        C=c;
        M=256;
}
void TLevel::SetupElement(char x, char y, char color, char bonus, char select,char data)
{
        if(color>=0) Matrix[y][x].Color=color;
        if(bonus>=0) Matrix[y][x].Bonus=bonus;
        if(select>=0)Matrix[y][x].Select=select;
        if(data>=0)  Matrix[y][x].Data=data;
}
long TLevel::Run(void)
{
        long s=0;
        while(Analise()) {
          s+=Execute();
        }
        NewBuffer();
        return s;
}
#pragma package(smart_init)
