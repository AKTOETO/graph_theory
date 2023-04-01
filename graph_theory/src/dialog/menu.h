#pragma once
/****************************************************************
*							   M E N U					        *
****************************************************************/
#include "../logger/Logger.hpp"
#include "command.h"
#include <fstream>
#include <Windows.h>

class Menu
{
	/* массив с командами
	*	возможные коды управления СУБД
	* 0 -e
	* 1 -m
	* 2 -l
	* 3 -h
	* ...
	* ...
	**/	
	Command* m_command;
	
	// Список музыкальных товаров
	//DataBaseManager m_db_manager;

	// Для быстрого доступа к полям структуры
#define CMD_NAME(num) m_command[num].GetAttribute(0)
#define CMD_SH_DECR(num) m_command[num].GetAttribute(1)
#define CMD_FL_DESCR(num) m_command[num].GetAttribute(2)
#define CMD_CHK_FUNC(in_name, in_arg) (this->*m_command[GetNumberOfCommand(in_name)].GetCheckFunction())(in_arg)
	// Выход из функции, если пуст лист
#define RETURN_IF_LIST_IS_EMPTY \
	if (m_db_manager.GetDefaultList().is_empty())\
	{\
		FUNC_INFO("база данных пуста");\
		return;\
	}

	// Если дополнительный список пуст,
	// вызываем функцию выборки элементов из БД
	// иначе печатаем список
#define IF_SELECT_LIST_IS_EMPTY_FILL_IT_ELSE_PRINT \
	if(m_db_manager.GetSelectedList().is_empty())\
		CheckCMDSelectFromDB("");\
	else\
		m_db_manager.PrintSelectedDBToConsole();


public:
	// конструктор и деструктор
	Menu();
	~Menu();

	// функция меню
	void ProgramMenu();

	// Проверяет, является ли введенная строка командой СУБД
	bool IsCommandCorrect(const string& _command);

	// Получение номера команды в массиве
	int GetNumberOfCommand(const string& _command);

	// печать нумерованного массива параметров
	void PrintNumberedArray(const string[], int);

	// ввод номера параметра из нумерованного
	// масива параметров
	int ReadIndexInNumberedArray(const string _msg, int _min, int _max);

	//****************************//
	//		ФУНКЦИИ ПРОВЕРОК	  //
	//****************************//

	// проверка команды ПОМОЩЬ
	void CheckCMDHelp(string _str);


	//****************************************//
	//		ФУНКЦИИ ДЛЯ ФУНКЦИЙ ПРОВЕРОК	  //
	//****************************************//


};
