//---------------------------------------------------------------------------


#pragma hdrstop

#include "PolyLinesLevel.h"
PLLevel::PLLevel():TLevel()
{
        Width=15;
        Height=15;
        CountBonus=CountColor=Time=0;
}
PLLevel::PLLevel(char caption[100],unsigned int mode,unsigned int number,
                long scoremin,long scoremax):
                TLevel("PolyLines 1.0",caption,scoremin,scoremax,number,
                mode,15,15)
{
        CountBonus=number/3;
        CountColor=number/12+5;
        Time=600-(number/3)*10;
        NewMatrix();
        NewBuffer();
        for(unsigned char i=0; i<5; i++)
          Colomns[i]=-1;
}
//---------------------------------------------------------------------------
void PLLevel::NewMatrix(void)
{
        for(unsigned char i=0; i<Height; i++)
        {
           for(unsigned char j=0; j<Width; j++)
           {
              Matrix[i][j].Color=0;
              Matrix[i][j].Bonus=0;
              Matrix[i][j].Select=false;
           }
        }
}
void PLLevel::NewBuffer(void)
{
        randomize();
        for(unsigned char i=0; i<5; i++)
        {
          if(CountColor)
          {
            do{
              Buffer[i].Color=random(CountColor);
            }while(!Buffer[i].Color);
          }
          Buffer[i].Select=false;
          Buffer[i].Bonus=0;
        }
        unsigned char c=random(5);
        Buffer[c].Bonus=random(CountBonus+1);
        if(Buffer[c].Bonus==2)
        {
          unsigned char a;
          unsigned char b;
          do{
            a=random(CountColor-1)+1;
            b=random(CountColor-1)+1;
          }while(a==b);
          Buffer[c].Color=a*10+b;
        }
}
void PLLevel::SelectBall(int number)
{
        Buffer[number].Select=true;
}
void PLLevel::SelectColomn(int number)
{
        bool f=true;
        if(number>=15) number=14;
        for(unsigned char i=0; i<5; i++)
          Colomns[i]=-1;
        for(unsigned char i=0; i<5; i++)
        {
          if(Buffer[i].Select)
            Colomns[i]=number;
          else
          {
            do{
              f=false;
              Colomns[i]=random(Width);
              for(unsigned char j=0; j<i; j++)
              {
                if(Colomns[j]==Colomns[i])
                {
                   f=true;
                   break;
                } //if
              }//for
            }while(f);
          }//else
        }//for
        
}
bool PLLevel::AddBalls(void)
{
        for(unsigned char i=0; i<5; i++)
        {
          char c=0;
          for(char y=Height-1; y>=0; y--)
          {
            if(Matrix[y][Colomns[i]].Color>0)
              c++;
          }
          if(c==Height)
            return false;
        }
        bool padenie=true;
        char CoordY[5];
        for(unsigned char i=0; i<5; i++)
        {
          Matrix[0][Colomns[i]]=Buffer[i];
          Matrix[0][Colomns[i]].Select=true;
          CoordY[i]=0;
        }
        do{
          for(unsigned char i=0; i<5; i++)
          {
            if(!Matrix[CoordY[i]+1][Colomns[i]].Color&&CoordY[i]<Height-1)
            {
              TMatrixElement b=Matrix[CoordY[i]+1][Colomns[i]];
              Matrix[CoordY[i]+1][Colomns[i]]=Matrix[CoordY[i]][Colomns[i]];
              Matrix[CoordY[i]][Colomns[i]]=b;
              CoordY[i]++;
            }
            else
            {
              Matrix[CoordY[i]][Colomns[i]].Select=false;

            }
          }
          padenie=false;
          for(unsigned char i=0; i<5; i++)
          {
            if(Matrix[CoordY[i]][Colomns[i]].Select)
              padenie=true;
          }
          
        }while(padenie);
        return true;
}
bool PLLevel::Analise(void)
{
        bool Pos=false;
        //Вертикаль
        for(unsigned char j=0; j<Width; j++)
        {
          for(unsigned char i=0; i<Height; i++)
          {
            int y=0;
            while(Matrix[i+y][j].Color)
            {
              if(Matrix[i][j].Bonus==5&&Matrix[i+1][j].Color)
                {y++; Matrix[i][j].Color=Matrix[i+1][j].Color;}
              else if(Matrix[i+y][j].Bonus==5)
                {y++; continue;}
              else if(Matrix[i+y][j].Color==Matrix[i][j].Color)
                {y++; continue;}
              else if(Matrix[i][j].Bonus==2&&Matrix[i][j].Color/10==Matrix[i+1][j].Color)
                {y++; continue;}
              else if(Matrix[i][j].Bonus==2&&Matrix[i][j].Color%10==Matrix[i+1][j].Color)
                {y++; continue;}
              else if(Matrix[i+y][j].Bonus==2&&Matrix[i+y][j].Color/10==Matrix[i][j].Color)
                {y++; continue;}
              else if(Matrix[i+y][j].Bonus==2&&Matrix[i+y][j].Color%10==Matrix[i][j].Color)
                {y++; continue;}
              else
                break;
            }
            if(y>=3)
            {
              Pos=true;
              for(int t=0; t<y; t++)
                Matrix[i+t][j].Select=true;
            }
          }
        }
        //Горизонталь
        for(unsigned char j=0; j<Width; j++)
        {
          for(unsigned char i=0; i<Height; i++)
          {
            int y=0;
            while(Matrix[i][j+y].Color)
            {
              if(Matrix[i][j].Bonus==5&&Matrix[i][j+1].Color)
                {y++; Matrix[i][j].Color=Matrix[i][j+1].Color;}
              else if(Matrix[i][j+y].Bonus==5)
                {y++; continue;}
              else if(Matrix[i][j+y].Color==Matrix[i][j].Color)
                {y++; continue;}
              else if(Matrix[i][j].Bonus==2&&Matrix[i][j].Color/10==Matrix[i][j+1].Color)
                {y++; continue;}
              else if(Matrix[i][j].Bonus==2&&Matrix[i][j].Color%10==Matrix[i][j+1].Color)
                {y++; continue;}
              else if(Matrix[i][j+y].Bonus==2&&Matrix[i][j+y].Color/10==Matrix[i][j].Color)
                {y++; continue;}
              else if(Matrix[i][j+y].Bonus==2&&Matrix[i][j+y].Color%10==Matrix[i][j].Color)
                {y++; continue;}
              else
                break;
            }
            if(y>=3)
            {
              Pos=true;
              for(int t=0; t<y; t++)
                Matrix[i][j+t].Select=true;
            }
          }
        }
        //Главная диагональ
        for(unsigned char j=0; j<Width; j++)
        {
          for(unsigned char i=0; i<Height; i++)
          {
            int y=0;
            while(Matrix[i+y][j+y].Color)
            {
              if(Matrix[i][j].Bonus==5&&Matrix[i+1][j+1].Color)
                {y++; Matrix[i][j].Color=Matrix[i+1][j+1].Color;}
              else if(Matrix[i+y][j+y].Bonus==5)
                {y++; continue;}
              else if(Matrix[i+y][j+y].Color==Matrix[i][j].Color)
                {y++; continue;}
              else if(Matrix[i][j].Bonus==2&&Matrix[i][j].Color/10==Matrix[i+1][j+1].Color)
                {y++; continue;}
              else if(Matrix[i][j].Bonus==2&&Matrix[i][j].Color%10==Matrix[i+1][j+1].Color)
                {y++; continue;}
              else if(Matrix[i+y][j+y].Bonus==2&&Matrix[i+y][j+y].Color/10==Matrix[i][j].Color)
                {y++; continue;}
              else if(Matrix[i+y][j+y].Bonus==2&&Matrix[i+y][j+y].Color%10==Matrix[i][j].Color)
                {y++; continue;}
              else
                break;
            }
            if(y>=3)
            {
              Pos=true;
              for(int t=0; t<y; t++)
                Matrix[i+t][j+t].Select=true;
            }
          }
        }
        //Побочная диагональ
        for(unsigned char j=0; j<Width; j++)
        {
          for(unsigned char i=0; i<Height; i++)
          {
            int y=0;
            while(Matrix[i+y][j-y].Color)
            {
              if(Matrix[i][j].Bonus==5&&Matrix[i+1][j-1].Color)
                {y++; Matrix[i][j].Color=Matrix[i+1][j-1].Color;}
              else if(Matrix[i+y][j-y].Bonus==5)
                {y++; continue;}
              else if(Matrix[i+y][j-y].Color==Matrix[i][j].Color)
                {y++; continue;}
              else if(Matrix[i][j].Bonus==2&&Matrix[i][j].Color/10==Matrix[i+1][j-1].Color)
                {y++; continue;}
              else if(Matrix[i][j].Bonus==2&&Matrix[i][j].Color%10==Matrix[i+1][j-1].Color)
                {y++; continue;}
              else if(Matrix[i+y][j-y].Bonus==2&&Matrix[i+y][j-y].Color/10==Matrix[i][j].Color)
                {y++; continue;}
              else if(Matrix[i+y][j-y].Bonus==2&&Matrix[i+y][j-y].Color%10==Matrix[i][j].Color)
                {y++; continue;}
              else
                break;
            }
            if(y>=3)
            {
              Pos=true;
              for(int t=0; t<y; t++)
                Matrix[i+t][j-t].Select=true;
            }
          }
        }
        return Pos;
}
long PLLevel::Execute(void)
{
        int score=0;
        for(unsigned char i=0; i<Height; i++)
        {
          for(unsigned char j=0; j<Width; j++)
          {
            if(Matrix[i][j].Select)
            {
              switch(Matrix[i][j].Bonus)
              {
                case 6: //Лазер горизонтальный
                  for(int t=0; t<Width; t++)
                    Matrix[i][t].Select=true;
                  break;
                case 7: //Лазер вертикальный
                  for(int t=0; t<Height; t++)
                    Matrix[t][j].Select=true;
                  break;
                case 8: //Лазер побочно-диагональный
                  for(int t=i,p=j;t<Height&&p>=0;t++,p--)
                    Matrix[t][p].Select=true;
                  for(int t=i,p=j;t>=0&&p<Width;t--,p++)
                    Matrix[t][p].Select=true;
                  break;
                case 9: //Лазер главно-диагональный
                  for(int t=i,p=j;t<Height&&p<Width;t++,p++)
                    Matrix[t][p].Select=true;
                  for(int t=i,p=j;t>=0&&p>=0;t--,p--)
                    Matrix[t][p].Select=true;
                  break;


              }
            }
          }
        }
        for(unsigned char i=0; i<Height; i++)
        {
          for(unsigned char j=0; j<Width; j++)
          {
             if(Matrix[i][j].Select)
             {
              //Выполненине бонусов
              switch(Matrix[i][j].Bonus)
              {
               case 1:
                 score+=2;
                 Obval(j,i);
                 break;
               case 3:
                 score+=3;
                 Obval(j,i);
                 break;
               case 4:
                 if(i>0)                  Obval(j  ,i-1); 
                 if(i<Height-1)           Obval(j  ,i+1); 
                 if(j>0)                  Obval(j-1,i); 
                 if(j<Width-1)            Obval(j+1,i); 
                 if(i>0&&j>0)             Obval(j-1,i-1); 
                 if(i<Width-1,j>0)        Obval(j-1,i+1); 
                 if(i>0&&j<Height-1)      Obval(j+1,i-1); 
                 if(i<Width-1,j<Height-1) Obval(j+1,i+1);
                 score++;
                 break;
               case 10:
                 for(int y=0; y<Height; y++)
                 {
                   for(int x=0; x<Width; x++)
                   {
                     if(Matrix[y][x].Color==Matrix[i][j].Color)
                       Obval(x,y);
                       score++;
                   }
                 }
                 break;
               default:
                 Obval(j,i);
                 score++;
                 break;
              }
             }
          }
        }
        Score=score;
        return score;
}
void PLLevel::Obval(int x, int y)
{
        for(unsigned char t=y; t>0; t--)
          Matrix[t][x]=Matrix[t-1][x];
        Matrix[0][x].Color=0;
        Matrix[0][x].Bonus=0;
        Matrix[0][x].Select=false;
}
bool PLLevel::LoadPL(int mode,int number)
{
        char name[100];
        sprintf(name,"levels\\%d_%d.level",mode,number);
        if(Load(name))
        {
          CountBonus=Number/3;
          CountColor=Number/12+5;
          Time=600-(Number/3)*10;
          NewBuffer();
          return true;
        }
        return false;
}
bool PLLevel::LoadPL(char name[100])
{
        if(Load(name))
        {
          CountBonus=Number/3;
          CountColor=Number/12+5;
          Time=360-(Number/3)*10;
          return true;
        }
        return false;
}
void PLLevel::SavePL(void)
{
        char string[100];
        sprintf(string,"levels\\%d_%d.level",ModeGame,Number);
        Save(string);
}
int PLLevel::CountData(void)
{
        int count=0;
        for(unsigned char i=0; i<Height; i++)
        {
          for(unsigned char j=0; j<Width; j++)
          {
            if(Matrix[i][j].Data)
              count++;
          }
        }
        return count;
}
LevelStatus PLLevel::IsWinner()
{
        for(int i=0; i<Width; i++)
          if(Matrix[Height][i].Color)
            return lsGameOver;
        switch(ModeGame)
        {
          case Adventure:
            if(Score>=ScoreMax)
              return lsWinner;
            return lsPlayGame;
          case Quest:
            if(!CountData())
              return lsWinner;
            return lsPlayGame;
          case Timer:
            if(Score>=ScoreMax)
              return lsWinner;
            if(!Time)
              return lsGameOver;
            return lsPlayGame;
        }
}
#pragma package(smart_init)
