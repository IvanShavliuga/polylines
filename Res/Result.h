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
    /*Доступные переменные и функции*/
  public:
    TResults();                 //Конструктор

    bool Load(char Name[256]);  //Загрузка данных из файла
    void Save(char Name[256]);  //Сохранение данных в файл
    void Create(int count);     //Создание таблицы
    void ClearData(void);       //Очистка результатов
    void ClearData(char Mask[256]);
    void PrintData(void);       //Функция вывода (запускает пользовательскую)
    TData GetData(int Index);   //Получить запись (результат под опред. номером)
    void DeleteData(int Index); //Удалить запись
    void AddData(char Name[256],long Score);
    void GetErrorCode(char Error[256]);//Описывает код ошибки
    
    int Count;                  //Кол-во записей
    int Select;                 //Номер выделенной записи
    char Caption[256];          //Заголовок таблицы
    /*Неизменяемые вручную переменные и функции (Доступ запрещен)*/
  private:
    void AddData(TData data);   //Добавление результата
    //Пользовательская функция вывода таблицы
    void OnPrint(int Left,int Top,int Width, int Height);
    int A,C,X0;
    TData Data[MAXRESULTS];     //Результаты
    char ErrorCode;              //Код ошибки
    void SetupKeys(void);
    char * Kodir(char *str,int len);
};
//---------------------------------------------------------------------------
#endif
