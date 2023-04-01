#pragma once
#include "../pch.h"
#include "../logger/Logger.hpp"
#include <iostream>
#include <fstream>

using namespace std;

// объявление струкутры меню
class Menu;

// структура, содержащая описание каждой команды
class Command
{
	string m_path_to_cmd_descr_folder;	// путь до папки c описанием команд
	int m_number_of_descriptions;	// количество команд

	string m_name;				// имя команды
	string m_short_description;	// краткое описание
	string m_full_description;	// полное описание

	string** m_cmd_attributes;	// массив с указателями на поля структуры

	// указатель на функцию обработки
	typedef void (Menu::* CheckFunc)(string);
	CheckFunc m_check_func;

public:
	// конструкторы
	Command(string _file_name);
	Command();

	// деструктор
	~Command();

	// установить функцию обработки команды
	void SetCheckFunction(CheckFunc);

	// вернуть функцию обработки команды
	// нужно для вызова функции обработки извне
	CheckFunc GetCheckFunction() const;

	// получение атрибутов команды 
	// (имя, короткое описание, полное описание)
	string GetAttribute(int _index) const;

	// заполнение команды данными из файла
	void FillCommandData(string _file_name);

	// оператор вывода
	friend ostream& operator<<(ostream& _out_stream, const Command& _cmd);
};
