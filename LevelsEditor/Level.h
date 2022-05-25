//---------------------------------------------------------------------------

#ifndef LevelH
#define LevelH
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//---------------------------------------------------------------------------
typedef struct TMatrixElement
{
  char Color;
  char Bonus;
  char Data;
  bool Select;
  TMatrixElement() {Color=Bonus=0; Select=false;Data=0;}
  TMatrixElement(char C, char B, bool S,char data)
  {
    Color=C; Bonus=B; Select=S; Data=data;
  }
} TMatrixElement;
class TLevel
{
 public:
   TLevel();
   TLevel(char game[100],char caption[100],long ScoreMin,long ScoreMax,
          unsigned int number,unsigned int modegame,unsigned char width,unsigned char height);
   char Caption[100];
   int Number;
   int GetErrorCode(void);
   long GetScore(void);
   long Run(void);
   void SetupElement(char x, char y, char color, char bonus, char select,char data);
 protected:
   char Game[100];
   long ScoreMin;
   long ScoreMax;
   long Score;
   int ModeGame;
   unsigned char Width;
   unsigned char Height;
   TMatrixElement  Matrix[50][50];
   TMatrixElement  Buffer[10];
   bool Load(char name[100]);
   void Save(char name[100]);
   virtual void NewMatrix(void)=0;
   virtual void NewBuffer(void)=0;
   virtual bool Analise(void)=0;
   virtual long  Execute(void)=0;
   virtual void Paint(void)=0;
   void SetupKeys(short x0, short a, short c);
 private:
   int ErrorCode;
   short X0,A,C,M;
   unsigned char * Kodir(unsigned char *str, int len);
   unsigned char * DeKodir(unsigned char *string, int length);
};
#endif
 