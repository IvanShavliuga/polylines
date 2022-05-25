//---------------------------------------------------------------------------

#ifndef PolyLinesLevelH
#define PolyLinesLevelH
#include "level.h"
#include <stdlib.h>

#define Adventure 0
#define Quest     1
#define Timer     2
//---------------------------------------------------------------------------
typedef enum  LevelStatus{
   lsGameOver,
   lsPlayGame,
   lsWinner
} LevelStatus;
class PLLevel: public TLevel
{
     public:
        PLLevel();
        PLLevel(char caption[100],unsigned int mode,unsigned int number,
                long scoremin,long scoremax);
        void SelectBall(int number);
        void SelectColomn(int number);
        bool AddBalls(void);
        void Paint(void);
        bool LoadPL(int mode,int number);
        bool LoadPL(char name[100]);
        void SavePL(void);
        void SavePL(char name[100]){
          Save(name);
        }
        long GetScoreMin(void)  {
          return ScoreMin;
        }
        long GetScoreMax(void) {
          return ScoreMax;
        }
        int CountData(void);
        void Analisator(void){
          Analise();
          Paint();
        }
        LevelStatus IsWinner(void);
        void NextTime(void){
          Time--;
        }
     private:
        char CountBonus;
        char CountColor;
        char Colomns[5];
        int Time;
        void NewMatrix(void);
        void NewBuffer(void);
        bool Analise(void);
        long Execute(void);
        void Obval(int x, int y);
        
};
#endif
