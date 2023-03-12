#ifndef SUPPORT_H
#define SUPPORT_H

#include "pch.h"

//==========================//
//	ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ	//
//==========================//
namespace SupportFunctions
{
	// получение текущего времени
	inline std::string GetCurrentTime()
	{
		time_t now = time(0);
		tm* tstruct = new tm;
		char buf[9];
		localtime_s(tstruct ,&now);
		strftime(buf, sizeof(buf), "%H:%M:%S", tstruct);

		return std::string(buf);
	}

	// получение текущей даты
	inline std::string GetCurrentDate()
	{
		time_t now = time(0);
		tm* tstruct = new tm;
		char buf[120];
		localtime_s(tstruct, &now);
		strftime(buf, sizeof(buf), "%d-%m-%Y(%H-%M-%S)", tstruct);

		return std::string(buf);
	}

	// получение подстроки отделенной с помощью delim
	// и удаление этой подстроки из изначальной строки
	inline std::string GetToken(std::string& _str, char _delim = ';')
	{
		// позиция делителя
		size_t delim_pos = _str.find(_delim);

		// если делитель не был найден, переносим всю строку
		if (delim_pos == -1)
		{
			delim_pos = _str.size();
		}

		// строка с нужной подстрокой
		// копирование нужной строки
		std::string new_str = _str.substr(0, delim_pos);

		// сдвиг всех символов в начало
		_str.erase(0, delim_pos + 1);

		return new_str;
	}
}

#endif
