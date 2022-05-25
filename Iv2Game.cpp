//---------------------------------------------------------------------------


#pragma hdrstop

#include "Iv2Game.h"
Iv2Game::Iv2Game()
{
        UserName[0]=UserPassword[0]=0;
        for(int i=0; i<3; i++)
        {
          SaveFiles[i][0]=0;
          UserNumberLevels[i]=0;
          ScoresMode[i]=0;
        }
        UserScore=UserScoreLevel=0;
        UserMode=UserLevel=UserWins=0;
        UserReyting=0.0;
        Play=false;
        SelectBall=SelectColomn=-1;
}
//---------------------------------------------------------------------------
bool Iv2Game::Launch(void) //Загрузка игры
{
        if(!Results.Load("polylines.score"))
        {
          Results.Create(10);
          Results.Save("polylines.score");
        }
        else
        {
          TData data1 = Results.GetData(0);
          TData data2;
          for(int i=1; i<10; i++)
          {
            data2 = Results.GetData(i);
            if(data2.Score>data1.Score)
            {
              Results.DeleteData(i);
              Results.AddData("Аноним\0",0);
            }
            data1=data2;
          }
        }
        if(!Users.LoadAsIV2("polylines.users"))
        {
            strcpy(Users.CaptionGame,"PolyLines 1.0");
            Users.SaveAsIV2("polylines.users");
        }
        Play=true;
        return true;
}
bool Iv2Game::NewUser(char name[256],char password[256])
{
        char email[256];
        if(UserName[0])
        {
          sprintf(email,"games\\%s.game",UserName);
          SaveGame(email);
        }
        sprintf(email,"games\\%s.game",name);
        if(!Users.AddPlayer(name,password,email))
          return false;
        else
        {
          UserScore=0;
          UserNumberLevels[0]=UserNumberLevels[1]=UserNumberLevels[2]=0;
          UserLevel=0;
          UserMode=0;
          UserWins=0;
          UserReyting=0.0;
          UserScoreLevel=0;
          Users.ChangePlayer(name,password,email,0,0,0,90);
          strcpy(UserName,name);
          strcpy(UserPassword,password);
          Users.SaveAsIV2("polylines.users");
          for(int j=0; j<3; j++)
            for(int i=0; i<256; i++)
              SaveFiles[j][i]=0;
          return true;
        }
}
bool Iv2Game::SelectUser(char name[256],char password[256])
{
        long Energy=0;
        unsigned int Games;
        Energy=UserNumberLevels[0];
        Energy+=UserNumberLevels[1]*1000;
        Energy+=UserNumberLevels[2]*100000;
        char email[256];
        if(UserName[0]) {
          sprintf(email,"games\\%s.game",UserName);
          SaveGame(email);
          Users.ChangePlayer(UserName,UserPassword,email,UserScore,Energy,UserWins,90);
          Users.SaveAsIV2("polylines.users");
        }
        if(Users.SelectPlayer(name,password,email,&UserScore,&Energy,&UserWins,&Games,&UserReyting))
        {
          if(Games!=90) Games=90;
          UserNumberLevels[2]=Energy/100000;
          Energy=Energy-UserNumberLevels[2]*100000;
          UserNumberLevels[1]=Energy/1000;
          Energy=Energy-UserNumberLevels[1]*1000;
          UserNumberLevels[0]=Energy;
          if(UserWins>Games||UserWins!=UserNumberLevels[0]+UserNumberLevels[1]+UserNumberLevels[2]) {
            UserWins=UserNumberLevels[0]+UserNumberLevels[1]+UserNumberLevels[2];
            UserReyting=((double)UserWins)/Games;
          }
          strcpy(UserName,name);
          strcpy(UserPassword,password);
          if(!LoadGame(email)){
            UserLevel=UserNumberLevels[0];
            UserMode=0;
            UserScoreLevel=0;
            SetupLevel(UserLevel,UserMode);
          }
          return true;
        }
        else {
          sprintf(email,"games\\%s.game",UserName);
          Users.SelectPlayer(UserName,UserPassword,email,&UserScore,&Energy,&UserWins,&Games,&UserReyting);
          return false;
        }
}
void Iv2Game::Exit()
{
        long Energy=UserNumberLevels[0];
        Energy+=UserNumberLevels[1]*1000;
        Energy+=UserNumberLevels[2]*100000;
        char email[256];
        if(UserName[0]){
          sprintf(email,"games\\%s.game",UserName);
          SaveGame(email);
        }
        Users.ChangePlayer(UserName,UserPassword,email,UserScore,Energy,UserWins,90);
        Users.SaveAsIV2("polylines.users");
        Results.Save("polylines.score");
}
void Iv2Game::SaveGame(char name[256])
{
        FILE *file=fopen(name,"wb");
        char string[256];
        fprintf(file,"IV2GAME");
        SetupKeys();
        fputc(X0,file);
        fputc(A,file);
        fputc(C,file);
        int mod2=X0+A+C;
        fputc(mod2/256,file);
        fputc(mod2%256,file);
        fwrite(Kodir(UserName,256),1,256,file);
        int s=0;
        for(int i=0; i<256; i++)
        {
          if(i>strlen(UserName))
            UserName[i]=0;
          s+=UserName[i];
        }
        fputc(s/256,file);
        fputc(s%256,file);
        mod2=0;
        ScoresMode[UserMode]=UserScoreLevel;
        for(int i=0; i<3; i++)
        {
          sprintf(string,"%010ld",ScoresMode[i]);
          fwrite(Kodir(string,10),1,10,file);
          mod2+=ScoresMode[i];
        }
        fputc(mod2/256,file);
        fputc(mod2%256,file);
        sprintf(SaveFiles[UserMode],"games\\%d%s.sav",UserMode,UserName);
        Level.SavePL(SaveFiles[UserMode]);
        fclose(file);
}

bool Iv2Game::LoadGame(char name[256])
{
        FILE *file=fopen(name,"rb");
        char string[256];
        int x0, a, c,mod2,s;
        if(!file){
          return false;
        }
        fread(string,1,7,file);
        string[7]=0;
        if(strcmp(string,"IV2GAME"))
        {
          fclose(file);
          return false;
        }
        x0=fgetc(file);
        a=fgetc(file);
        c=fgetc(file);
        int et=fgetc(file)*256+fgetc(file);
        mod2=x0+a+c;
        if(mod2!=et)
        {
           fclose(file);
           return false;
        }
        X0=x0;
        A=a;
        C=c;
        fread(string,1,256,file);
        strcpy(string,Kodir(string,256));
        s=0;
        for(int i=0; i<256; i++)  {
          if(i>strlen(string))
            string[i]=0;
          s+=string[i];
        }
        et=fgetc(file)*256+fgetc(file);
        mod2=0;
        for(int i=0; i<3; i++)
        {
           fread(string,1,10,file);
           strcpy(string,Kodir(string,10));
           ScoresMode[i]=atol(string);
           mod2+=ScoresMode[i];
        }
        UserMode=0;
        UserScoreLevel=ScoresMode[0];
        et=fgetc(file)*256+fgetc(file);
        if(et!=mod2)
        {
           fclose(file);
           return false;
        }
        sprintf(SaveFiles[UserMode],"games\%d%s.sav",UserMode,UserName);
        Level.LoadPL(SaveFiles[UserMode]);
        Play=true;
        fclose(file);
        return true;
}
char * Iv2Game::GetUserNameA(void)
{
        char * string = new char[256];
        strcpy(string,UserName);
        return string;
}
unsigned int Iv2Game::GetUserWins(void)
{
        return UserWins;
}
long Iv2Game::GetUserScoreAll(void)
{
        return UserScore;
}
long Iv2Game::GetUserScoreLevel(void)
{
        return UserScoreLevel;
}
double Iv2Game::GetUserReyting(void)
{
        return UserReyting; 
}
bool Iv2Game::SetupLevel(int number,int mode)
{
        PLLevel old=Level;
        if(!Level.LoadPL(mode,number))
        {
          Level=old;
          return false;
        }
        if(UserScore<Level.GetScoreMin())
        {
          Level=old;
          return false;
        }
        UserMode=mode;
        UserLevel=number;
        return true;
}
void Iv2Game::GetUsers(char *names[256],int *count)
{
        for(int i=0; i<Users.Count; i++)
        {
          names[i] =  new char[256];
          strcpy(names[i],Users.GetName(i));
        }
        *count=Users.Count;
}
bool Iv2Game::PlayGame(void)
{
        Results.PrintData();
        if(Play){
          Level.SelectBall(SelectBall);
          Level.SelectColomn(SelectColomn);
          if(!Level.AddBalls()&&UserScoreLevel<Level.GetScoreMax())
          {
            UserScoreLevel=0;
            if(UserScore)
              Results.AddData(UserName,UserScore);
            SetupLevel(UserLevel,UserMode);
            return true;
          }
          UserScoreLevel+=Level.Run();
          if(Level.IsWinner()==lsWinner||UserScoreLevel>=Level.GetScoreMax())
          {
            UserScore+=UserScoreLevel;
            if(UserScore<Level.GetScoreMax())
              UserScore+=Level.GetScoreMax();
            if(UserLevel<29)
              UserLevel++;
            else
            {
              Play=false;
              Results.AddData(UserName,UserScore);
              return false;
            }
            UserWins++;
            if(UserScore)
              Results.AddData(UserName,UserScore);
            SetupLevel(UserLevel,UserMode);
          }
          Level.Paint();
          if(Results.Count>10){
            Results.Count=10;
            Results.Save("polylines.score");
          }
          return true;
        }
        
        return false;
       
}
void Iv2Game::Paint(bool res, bool level)
{
        if(level) Level.Paint();
        if(res)   Results.PrintData();
}
void Iv2Game::SetupKeys(void)
{
        A=17;
        C=5;
        M=256;
        randomize();
        X0=random(256);
}
char * Iv2Game::Kodir(char *str,int len)
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
#pragma package(smart_init)
