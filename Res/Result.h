//---------------------------------------------------------------------------

#ifndef ResultH
#define ResultH
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAXRESULTS 20
typedef struct DateAndTime
{
   unsigned char Second,Minute, Hour;
   unsigned char Day, Month;
   unsigned int Year;
}DateAndTime;
typedef struct TData
{
   char Name[256];
   long Score;
   DateAndTime Date;
}TData;
class TResults
{
    /*��������� ���������� � �������*/
  public:
    TResults();                 //�����������

    bool Load(char Name[256]);  //�������� ������ �� �����
    void Save(char Name[256]);  //���������� ������ � ����
    void Create(int count);     //�������� �������
    void ClearData(void);       //������� �����������
    void ClearData(char Mask[256]);
    void PrintData(void);       //������� ������ (��������� ����������������)
    TData GetData(int Index);   //�������� ������ (��������� ��� �����. �������)
    void DeleteData(int Index); //������� ������
    void AddData(char Name[256],long Score);
    void GetErrorCode(char Error[256]);//��������� ��� ������
    
    int Count;                  //���-�� �������
    int Select;                 //����� ���������� ������
    char Caption[256];          //��������� �������
    /*������������ ������� ���������� � ������� (������ ��������)*/
  private:
    void AddData(TData data);   //���������� ����������
    //���������������� ������� ������ �������
    void OnPrint(int Left,int Top,int Width, int Height);
    int A,C,X0;
    TData Data[MAXRESULTS];     //����������
    char ErrorCode;              //��� ������
    void SetupKeys(void);
    char * Kodir(char *str,int len);
};
//---------------------------------------------------------------------------
#endif
