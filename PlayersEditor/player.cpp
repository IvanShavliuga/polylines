//---------------------------------------------------------------------------


#pragma hdrstop

#include "player.h"
TPlayers::TPlayers()
{
        Count=0;
        Select=-1;
        Players=NULL;
        CaptionGame[0]=0;
        A=17;
        C=5;
        M=256;
        X0=0;
        randomize();
}
TPlayers::~TPlayers()
{
        delete [] Players;
}
//---------------------------------------------------------------------------
void TPlayers::SaveAsIV2(char Name[256])
{
        FILE *file=fopen(Name,"wb");
        unsigned char string[256];
        long s;
        unsigned char mod2;
        fprintf(file,"IV2PLAYERS");
        NewKeys();
        fputc(X0,file);
        fputc(A,file);
        fputc(C,file);
        s=A+C+X0;
        fputc(s/256,file);
        fputc(s%256,file);
        for(int i=strlen(CaptionGame); i<256; i++)
          CaptionGame[i]=0;
        fwrite(Kodir(CaptionGame,256),1,256,file);
        for(int i=0; i<256; i++)
          s+=CaptionGame[i];
        sprintf(string,"%05d\0",Count);
        fwrite(Kodir(string,5),1,5,file);
        for(int i=0; i<5; i++)
          s+=string[i];
        fputc(s/256,file);
        fputc(s%256,file);
        for(int i=0; i<Count; i++)
        {
          s=0;
          for(int j=0; j<256; j++)
          {
            if(j>=strlen(Players[i].Name))
               Players[i].Name[j]=0;
            s+=Players[i].Name[j];
          }
          fwrite(Kodir(Players[i].Name,256),1,256,file);
          fputc(s/256,file);
          fputc(s%256,file);
          for(int j=0; j<256; j++)
          {
            if(j>=strlen(Players[i].Password))
               Players[i].Password[j]=0;
            s+=Players[i].Password[j];
          }
          fwrite(Kodir(Players[i].Password,256),1,256,file);
          fputc(s/256,file);
          fputc(s%256,file);
          for(int j=0; j<256; j++)
          {
            if(j>=strlen(Players[i].email))
               Players[i].email[j]=0;
            s+=Players[i].email[j];
          }
          fwrite(Kodir(Players[i].email,256),1,256,file);
          fputc(s/256,file);
          fputc(s%256,file);
          strnset(string,0,256);
          sprintf(string,"%010ld",Players[i].Score);
          fwrite(Kodir(string,10),1,10,file);
          for(int j=0; j<10; j++)
            s+=string[j];
          fputc(s/256,file);
          fputc(s%256,file);
          strnset(string,0,256);
          sprintf(string,"%010ld",Players[i].Energy);
          fwrite(Kodir(string,10),1,10,file);
          for(int j=0; j<10; j++)
            s+=string[j];
          fputc(s/256,file);
          fputc(s%256,file);
          s+=Players[i].Games+Players[i].Wins;
          fputc(Players[i].Games,file);
          fputc(Players[i].Wins,file);
          fputc(s/256,file);
          fputc(s%256,file);
          
        }
        fclose(file);
}
bool TPlayers::LoadAsIV2(char Name[256])
{
        FILE *file=fopen(Name,"rb");
        Error=0;
        if(!file)
        {
          Error=1;
          return false;
        }
        delete [] Players;
        Count=0;
        Select=-1;
        long s,etalon;
        int x0=X0,a=A,c=C;
        unsigned char string[256],buffer[256];
        fread(string,1,10,file);
        string[10]=0;
        if(strcmp(string,"IV2PLAYERS"))
        {
           Error=2;
           fclose(file);
           X0=x0;
           A=a;
           C=c;
           return false;
        }
        X0=fgetc(file);
        A=fgetc(file);
        C=fgetc(file);
        etalon=fgetc(file)*256+fgetc(file);
        s=X0+A+C;
        if(s!=etalon){
          fclose(file);
          A=a;
          C=c;
          X0=x0;
          Error=3;
          return false;
        }
        fread(string,1,256,file);
        for(int i=0; i<256; i++)
          CaptionGame[i]=0;
        sprintf(CaptionGame,"%s",DeKodir(string,256));
        for(int i=0; i<256; i++)
          s+=CaptionGame[i];
        fread(string,1,5,file);
        sprintf(buffer,"%s",DeKodir(string,5));
        for(int i=0; i<5; i++)
          s+=buffer[i];
        etalon=fgetc(file)*256+fgetc(file);
        if(s!=etalon)
        {
          Error=4;
          fclose(file);
          X0=x0;
          A=a;
          C=c;
          return false;
        }
        Count=atoi(buffer);
        Players = new TPlayer[Count];
        for(int i=0; i<Count; i++)
        {
          s=0;
          fread(string,1,256,file);
          sprintf(Players[i].Name,"%s",Kodir(string,256));
          for(int j=0; j<256; j++)
            s+=Players[i].Name[j];
          etalon=fgetc(file)*256+fgetc(file);
          if(s!=etalon){
             Error=5;
             fclose(file);
             delete [] Players;
             Count=0;
             CaptionGame[0]=0;
             return false;
          }
          fread(string,1,256,file);
          sprintf(Players[i].Password,"%s",Kodir(string,256));
          for(int j=0; j<256; j++)
            s+=Players[i].Password[j];
          etalon=fgetc(file)*256+fgetc(file);
          if(s!=etalon){
             Error=6;
             fclose(file);
             delete [] Players;
             Count=0;
             CaptionGame[0]=0;
             return false;
          }
          fread(string,1,256,file);
          sprintf(Players[i].email,"%s",Kodir(string,256));
          for(int j=0; j<256; j++)
            s+=Players[i].email[j];
          etalon=fgetc(file)*256+fgetc(file);
          if(s!=etalon){
             Error=7;
             fclose(file);
             delete [] Players;
             Count=0;
             CaptionGame[0]=0;
             return false;
          }
          fread(string,1,10,file);
          sprintf(buffer,"%s",Kodir(string,10));
          for(int j=0; j<10; j++)
            s+=buffer[j];
          Players[i].Score=atol(buffer);
          etalon=fgetc(file)*256+fgetc(file);
          if(s!=etalon){
             Error=8;
             fclose(file);
             delete [] Players;
             Count=0;
             CaptionGame[0]=0;
             return false;
          }
          strnset(buffer,0,256);
          fread(string,1,10,file);
          sprintf(buffer,"%s",Kodir(string,10));
          for(int j=0; j<10; j++)
            s+=buffer[j];
          Players[i].Energy=atol(buffer);
          etalon=fgetc(file)*256+fgetc(file);
          if(s!=etalon){
             Error=9;
             fclose(file);
             delete [] Players;
             Count=0;
             CaptionGame[0]=0;
             return false;
          }
          Players[i].Games=fgetc(file);
          Players[i].Wins=fgetc(file);
          s+=Players[i].Games+Players[i].Wins;
          etalon=fgetc(file)*256+fgetc(file);
          if(s!=etalon){
             Error=10;
             fclose(file);
             delete [] Players;
             Count=0;
             CaptionGame[0]=0;
             return false;
          }
          if(Players[i].Games) Players[i].Reyting=((double)Players[i].Wins)/Players[i].Games;
          else                 Players[i].Reyting=0.0;
        }
        fclose(file);
        return true;
}
void TPlayers::AddPlayer(TPlayer player)
{
        Players=(TPlayer *)realloc(Players,(Count+1)*sizeof(TPlayer));
        Players[Count]=player;
        Count++;
}
void TPlayers::DeletePlayer(int index)
{
        if(!Count) return;
        TPlayer *pl=(TPlayer *)calloc(Count-1,sizeof(TPlayer));
        for(int i=0; i<index; i++)
          pl[i]=Players[i];
        for(int i=index; i<Count-1; i++)
          pl[i]=Players[i+1];
        Count--;
        Select=index;
        delete [] Players;
        Players=pl;
        
}
char * TPlayers::GetName(int index)
{
        return Players[index].Name;
}
bool TPlayers::Password(char password[256],int index)
{
        if(!strcmp(Players[index].Password,password))
          return true;
        else
          return false;
}
int TPlayers::FindPlayer(char Name[256])
{
        int i=0;
        while(i<Count)
        {
          if(!strcmp(Name,Players[i].Name))
            return i;
          i++;
        }
        return -1;
}
bool TPlayers::AddPlayer(char name[256],char password[256],char email[256])
{
        TPlayer player;
        if(FindPlayer(name)!=-1)
          return false;
        strcpy(player.Name,name);
        strcpy(player.Password,password);
        strcpy(player.email,email);
        player.Energy=1000;
        player.Score=0;
        player.Wins=0;
        player.Games=0;
        player.Reyting=0.0;
        AddPlayer(player);
        return true;
}
bool TPlayers::DeletePlayer(char name[256],char password[256])
{
        int i=FindPlayer(name);
        if(i==-1)
          return false;
        if(!Password(password,i))
          return false;
        DeletePlayer(i);
        return true;
}
bool TPlayers::SelectPlayer(char name[256],char password[256],char email[256],
           long *score,long *energy,unsigned int *Wins,unsigned int *games,double *reyting)
{
        int i=FindPlayer(name);
        if(i==-1)
          return false;
        if(!Password(password,i))
          return false;
        strcpy(name,Players[i].Name);
        strcpy(password,Players[i].Password);
        strcpy(email,Players[i].email);
        *score=Players[i].Score;
        *energy=Players[i].Energy;
        *Wins=Players[i].Wins;
        *games=Players[i].Games;
        *reyting=Players[i].Reyting;
        Select=i;
        return true;
}
bool TPlayers::ChangePlayer(char Name[256],char password[256],char email[256],
           long score,long energy,unsigned int Wins,unsigned int games)
{
        int i=FindPlayer(Name);
        if(i==-1)
          return false;
        if(!Password(password,i))
          return false;
        strcpy(Players[i].email,email);
        Players[i].Score=score;
        Players[i].Energy=energy;
        Players[i].Wins=Wins;
        Players[i].Games=games;
        if(games) Players[i].Reyting=((double)Wins)/games;
        else      Players[i].Reyting=0.0;
        Select=i;
        return true;
}
void TPlayers::NewKeys(void)
{
        X0=random(256);
}
void TPlayers::NewKeys(int a, int c, int m, int x0)
{
        X0=x0;
        A=a;
        C=c;
        M=m;
}
char * TPlayers::Kodir(const char *string, int length)
{
        int X1=X0, X2=X0;
        char *result= new char[length];
        for(int i=0; i<length; i++)
        {
          result[i]=X2^string[i];
          X1=X2;
          X2=(A*X1+C)%M;
        }
        return result;
}
char * TPlayers::DeKodir(const char *string, int length)
{
        int X1=X0, X2=X0;
        char *result= new char[length];
        for(int i=0; i<length; i++)
        {
          result[i]=X2^string[i];
          X1=X2;
          X2=(A*X1+C)%M;
        }
        return result;
}

#pragma package(smart_init)

