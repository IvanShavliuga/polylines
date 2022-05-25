//---------------------------------------------------------------------------

#ifndef Iv2GameH
#define Iv2GameH
#include <mmsystem.hpp>
#include "Res\Result.h"
#include "PlayersEditor\player.h"
#include "LevelsEditor\polylineslevel.h"
//---------------------------------------------------------------------------
class Iv2Game
{
public:
  //Конструктор
  Iv2Game();
  //Запуск игры
  bool Launch();
  //Новый пользователь
  bool NewUser(char name[256],char password[256]);
  //Выбрать пользователя
  bool SelectUser(char name[256],char password[256]);
  //Завершение игры
  void Exit();
  //Узнать имя игрока
  char * GetUserNameA(void);
  //Узнать количество пройденных уровней
  unsigned int  GetUserWins(void);
  //Узнать количество набранных ранее очков
  long GetUserScoreAll(void);
  //Узнать очки за уровень
  long GetUserScoreLevel(void);
  //Узнать рейтинг игрока
  double GetUserReyting(void);
  //Установить уровень
  bool SetupLevel(int number,int mode);
  //Играть игру
  bool PlayGame(void);
  //Получить список пользователей
  void GetUsers(char *names[256],int *count);
  //Вывод на экран
  void Paint(bool res, bool level);
  //Номера посмледних пройденных уровней для каждого режима
  unsigned int UserNumberLevels[3];
  //Номер игрового режима
  unsigned int UserMode;
  //Сохранение игры
  void SaveGame(char name[256]);
  //Загрузка игры
  bool LoadGame(char name[256]);
  void NextTime() {Level.NextTime();}
  void BreakGame(void){
    char string[256];
    sprintf(string,"games//%s.game",UserName);
    UserNumberLevels[UserMode]=UserLevel;
    long Energy=UserNumberLevels[0];
    Energy+=UserNumberLevels[1]*1000;
    Energy+=UserNumberLevels[2]*100000;
    Users.ChangePlayer(UserName,UserPassword,string,UserScore,Energy,UserWins,90);
    Users.SaveAsIV2("polylines.users");
    SaveGame(string);
  }
  int SelectColomn;   //Номер выбранной колонки
  int SelectBall;     //Номер выбранного шара
private:
  //Флаг можно играть?
  bool Play;
  //имя пользователя
  char UserName[256];
  //Номер уровня
  unsigned int UserLevel;
  //Набранные оочки за все пройденные уровни
  long UserScore;
  //Очки за текущий уровень
  long UserScoreLevel;
  //Общее количество пройденных уровней
  unsigned int UserWins;
  //Рейтинг на момент запуска уровня
  double UserReyting;
  //Пароль пользователя
  char UserPassword[256];
  PLLevel  Level;   //тек. уровень
  TPlayers Users;   //список пользователей
  TResults Results; //таблица рекордов
  //Файлы, в которые сохранены непройденные уровни
  char SaveFiles[3][256];
  int X0,A,C,M;     //Ключи
  //Кодирование сообщения
  char * Kodir(char *str, int len);
  //Установка ключей
  void SetupKeys(void);
  //Файл отчета (для устронения ошиюок)
  //Очки
  long ScoresMode[3];
};
#endif
