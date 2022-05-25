//---------------------------------------------------------------------------

#ifndef playerH
#define playerH
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct TPlayer
{
  unsigned char Name[256];
  unsigned char Password[256];
  unsigned char email[256];
  long Score;
  long Energy;
  unsigned int Wins;
  unsigned int Games;
  double Reyting;
  TPlayer()
  {
    for(int i=0; i<256; i++)
    {
      Name[i]=0;
      Password[i]=0;
      email[i]=0;
    }
    Score=0;
    Energy=0;
    Wins=0;
    Games=0;
  }
} TPlayer;
//---------------------------------------------------------------------------
class TPlayers
{
 public:
  TPlayers();
  ~TPlayers();
  int Count;
  int Select;
  int Error;
  char CaptionGame[256];
  void SaveAsIV2(char name[256]);
  bool LoadAsIV2(char name[256]);
  bool AddPlayer(char name[256],char password[256],char email[256]);
  bool DeletePlayer(char name[256],char password[256]);
  bool SelectPlayer(char name[256],char password[256],char email[256],
           long *score,long *energy,unsigned int *Wins,unsigned int *games,double *reyting);
  bool ChangePlayer(char Name[256],char password[256],char email[256],
           long score,long energy,unsigned int Wins,unsigned int games);
  char * GetName(int index);
  void NewKeys(int a, int c, int m, int x0);
 private:
  int A,C,X0,M;
  TPlayer *Players;
  void AddPlayer(TPlayer player);
  void DeletePlayer(int index);
  int FindPlayer(char Name[256]);
  bool Password(char pass[256],int index);
  char * Kodir(const char *string, int length);
  char * DeKodir(const char *string, int length);
  void NewKeys(void);
};
#endif
 