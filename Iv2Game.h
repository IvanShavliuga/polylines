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
  //�����������
  Iv2Game();
  //������ ����
  bool Launch();
  //����� ������������
  bool NewUser(char name[256],char password[256]);
  //������� ������������
  bool SelectUser(char name[256],char password[256]);
  //���������� ����
  void Exit();
  //������ ��� ������
  char * GetUserNameA(void);
  //������ ���������� ���������� �������
  unsigned int  GetUserWins(void);
  //������ ���������� ��������� ����� �����
  long GetUserScoreAll(void);
  //������ ���� �� �������
  long GetUserScoreLevel(void);
  //������ ������� ������
  double GetUserReyting(void);
  //���������� �������
  bool SetupLevel(int number,int mode);
  //������ ����
  bool PlayGame(void);
  //�������� ������ �������������
  void GetUsers(char *names[256],int *count);
  //����� �� �����
  void Paint(bool res, bool level);
  //������ ���������� ���������� ������� ��� ������� ������
  unsigned int UserNumberLevels[3];
  //����� �������� ������
  unsigned int UserMode;
  //���������� ����
  void SaveGame(char name[256]);
  //�������� ����
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
  int SelectColomn;   //����� ��������� �������
  int SelectBall;     //����� ���������� ����
private:
  //���� ����� ������?
  bool Play;
  //��� ������������
  char UserName[256];
  //����� ������
  unsigned int UserLevel;
  //��������� ����� �� ��� ���������� ������
  long UserScore;
  //���� �� ������� �������
  long UserScoreLevel;
  //����� ���������� ���������� �������
  unsigned int UserWins;
  //������� �� ������ ������� ������
  double UserReyting;
  //������ ������������
  char UserPassword[256];
  PLLevel  Level;   //���. �������
  TPlayers Users;   //������ �������������
  TResults Results; //������� ��������
  //�����, � ������� ��������� ������������ ������
  char SaveFiles[3][256];
  int X0,A,C,M;     //�����
  //����������� ���������
  char * Kodir(char *str, int len);
  //��������� ������
  void SetupKeys(void);
  //���� ������ (��� ���������� ������)
  //����
  long ScoresMode[3];
};
#endif
