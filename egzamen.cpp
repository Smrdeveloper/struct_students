/*Смирнов Вячеслав,БСБО-14-18.
Программа по созданию структуры студентов.
Здесь парочка ньюансов:
1 - Нужно в начале программы указать сколько студентов Вы хотите ввести,если ввести 1 , то в будущем 
нельзя будет ввести еще одного студента, по сути можно, но будет утечка данных , и не будет выводится список.
2 - Данные в файле нужно чистить самому.
*/
// 1 - пользователь вводит данные в массивы
// 2 - полученные данные можно вывести
// 3 - данные можно записать в файл
// 4 - данные можно считать из файла
// 5 - пользователь может сортировать данные 1.по возрастанию или 2.по убыванию.
// 6 - чистка массивов
// 7 - выход из цикла do....while(), конец программы.
#include "pch.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <clocale>
#include <cstring>
#include <Windows.h>

using namespace std;


struct students
{
	char *FIO;
	char *codestud;
	char *codenap;

};

void vvod(students *a, int length);

char *inputString();

void vivod(students *a, int length);

void del(students *a, int length);

void Zapisat_v_fail(students *a, int  length);

void chtenie_iz_Faila(students *a, int length);

void sort(students *a, int lenght, char*c);

void menu();

int main()
{

	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	int N;
	cout << "Введите количество студентов: ";
	cin >> N;
	students *stud = new students[N];

	cout << "Сначала нужно ввести стундент(а/ов)"<< endl;
	cout << "Иначе программа не будет работать!"<< endl;
	cout << "И всегда перед тем как выйти из программы, очищайте массивы!" << endl;
	cout << "Иначе будет утечка памяти!" << endl;

	char c;

	do
	{
		menu();
		cin >> c;

		switch (c)
		{
		case '1':
			system("cls");
			vvod(stud, N);
			break;
		case '2':
			system("cls");
			vivod(stud, N);
			break;
		case '3':
			system("cls");
			Zapisat_v_fail(stud, N);
			break;
		case '4':
			system("cls");
			chtenie_iz_Faila(stud, N);
			break;
		case '5':
			system("cls");
			char c;
			cout << "Как сортировать?" <<
			endl << "1.По возрастнанию." << 
			endl << "2.По убыванию." << endl;
			cin >> c;
			sort(stud,N,&c);
			cout << "Для того, чтобы посмотреть результат сортировки , нажмите 2."<< endl;
			break;
		case '6':
			system("cls");
			del(stud, N);
			break;
		case '7':
			cout << "Вы вышли из программы !"<< endl;
			cout << "Нажмите enter!";
			break;
		default:
			cout << "Нет такого пункта меню!";
			break;



		}
	} while (c != '7');


	
	delete[] stud;

	_getch();
	return 0;

}
void vvod(students *a, int length)// ввод данных пользователем
{
	for (int i(0); i < length; i++)
	{
		cout << i + 1 << ":\n";
		cout << "Введите ФИО студента(Например Смирнов Вячеслав): ";
		a[i].FIO = inputString();
		cout << endl;
		cout << "Введите код студента(Например 18В703): ";
		a[i].codestud = inputString();
		cout << endl;
		cout << "Введите код направления(Например 09.03.02): ";
		a[i].codenap = inputString();
		cout << endl;
	}
}
char* inputString()//каждый раз при вызове функции создается массив.
{
	char* resultStr = new char[1];
	resultStr[0] = '\0';
	char string = NULL;
	bool flag = true;

	while (flag)
	{
		string = _getch();
		if (string != 0)
		{
			if (string == 32 && strlen(resultStr) == 0)// по таблице ascii 32 = пробел
				                                       // следовательно, когда пользователь вводит пробел
				                                       // выходит сообщение об ошибке
			{
				cout<< "Пожалуйста, введите строку корректно"<< endl;
			}
			else if (string == 13)// по той же таблице 13 = enter , то бишь это выход из цикла.
			{
				flag = false;
			}
			else if (string != 8)
			{
				cout << string;
				int len = strlen(resultStr);
				char* tmp = new char[len + 2];
				strcpy_s(tmp, len + 2, resultStr);
				tmp[len] = string;
				tmp[len + 1] = '\0';

				delete[] resultStr;
				resultStr = tmp;

			}
			else if (strlen(resultStr) > 0)//это условие выполняет удаление символов в getch();
			{                              //например пользователь ввел не 09. , а случайно 09ю
				cout << "\b \b";           //так \b \b "заменяет" на "пустоту". Надеюсь понятно объяснил.
				int len = strlen(resultStr);
				char* tmp = new char[len];
				strncpy_s(tmp, len, resultStr, len - 1);
				tmp[len - 1] = '\0';
				delete[] resultStr;
				resultStr = tmp;
			}
		}
	}
	return resultStr;
}
void vivod(students *a, int length)//функция вывода массивов
{
	for (int i = 0; i < length; i++)
	{
		cout << i + 1 << " Студент:\n";
		cout << "ФИО студента: " << a[i].FIO << endl;
		cout << "Код студента: " << a[i].codestud << endl;
		cout << "Код направления: " << a[i].codenap << endl;
		cout << "----------------------------------";
		cout << endl;
	}
}

void del(students *a, int length) // удаление данных из массивов
{
	for (int i(0); i < length; i++)
	{
		delete[] a[i].FIO;
		delete[] a[i].codestud;
		delete[] a[i].codenap;
	}
}

void Zapisat_v_fail(students *a, int  length) // запись данных в файл 
{

	ofstream Fount;
	Fount.open("myText.txt");
	/*---------------------------------------*/
	if (!Fount.is_open())
	{
		cout << "Error , file is not find! ";
	}
	else
	{

		for (int i(0); i < length; i++)
		{
			Fount << i + 1 << " Студент:\n";
			Fount << "ФИО студента: " << a[i].FIO << endl;
			Fount << "Код студента: " << a[i].codestud << endl;
			Fount << "Код направления: " << a[i].codenap << endl;
			Fount << "----------------------------------";
			Fount << endl;
		}
	}

	Fount.close();
}

void chtenie_iz_Faila(students *a, int length)// чтение из файла
{
	ifstream Fint;
	Fint.open("myText.txt");
	/*----------------------------*/
	if (!Fint.is_open())
	{
		cout << "File is not find!";
	}
	else
	{
		cout << "File open!" << endl;
		char c;
		while (Fint.get(c))
		{
			cout << c;
		}
	}

}
void sort(students *a, int lenght, char*c)// Сортировка по фамилии.
{
	if (*c == '1')//по возрастанию
	{
		char *s;
		char *t;
		char* m;
		for (int i = 1; i <= lenght - 1; i++)
		{
			for (int j = 0; j < lenght - i; j++)
			{
				if (strcmp(a[j].FIO, a[j + 1].FIO) > 0)
				{
					s = a[j + 1].FIO;
					a[j + 1].FIO = a[j].FIO;
					a[j].FIO = s;
					t = a[j + 1].codestud;
					a[j + 1].codestud = a[j].codestud;
					a[j].codestud = t;
					m = a[j + 1].codenap;
					a[j + 1].codenap = a[j].codenap;
					a[j].codenap = m;
				}
			}

		}
	}
	else if (*c == '2')// по убыванию
	{
		char *s;
		for (int i = 1; i <= lenght - 1; i++)
		{
			for (int j = 0; j < lenght - i; j++)
			{
				if (strcmp(a[j].FIO, a[j + 1].FIO) < 0)
				{
					s = a[j + 1].FIO;
					a[j + 1].FIO = a[j].FIO;
					a[j].FIO = s;

				}
			}

		}
	}

}

void menu()// функция при вызове выводит меню.
{
	cout << "\t\t\t\t\t ---------------------------------------- " << endl;
	cout << "\t\t\t\t\t|                 Меню:                  |" << endl;
	cout << "\t\t\t\t\t| 1.Записать студент(а/ов).              |" << endl;
	cout << "\t\t\t\t\t| 2.Вывести список.                      |" << endl;
	cout << "\t\t\t\t\t| 3.Записать в файл.                     |" << endl;
	cout << "\t\t\t\t\t| 4.Чтение из файла.                     |" << endl;
	cout << "\t\t\t\t\t| 5.Сортировка.                          |" << endl;
	cout << "\t\t\t\t\t| 6.Очистка массивов.                    |" << endl;
	cout << "\t\t\t\t\t| 7.Выход из программы.                  |" << endl;
	cout << "\t\t\t\t\t ---------------------------------------- " << endl;
}

