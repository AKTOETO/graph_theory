#ifndef LOGGER_H
#define LOGGER_H

#include "../Constants.h"
#include "../Support.h"


	// возможные цвета текста в консоли
	namespace CCS // console color settings
	{
		static std::string Reset = "\033[0m";

		static std::string Black = "\033[0;30m";
		static std::string Green = "\033[0;32m";
		static std::string Red = "\033[0;31m";
		static std::string White = "\033[0;37m";
	}

	// типы работы логгера
	enum class LoggingMode
	{
		CONSOLE,
		FILE
	};

	/// <summary>
	/// печать сообщения без подсветки 
	/// </summary>
	/// <param name="_color"> - цвет из CCS</param>
	/// <param name="_msg"> - печатаемое сообщение</param>
	/// <param name="_width"> - ширина печати</param>
	static void NotHighlightedConsolePrint(
		std::string _msg,
		int _width = 0
	)
	{
		// substr здесь нужна только для вычленения из пути до файла сам файл
		std::cout
			<< std::setfill(' ') << std::setw(_width)
			<< _msg.substr(_msg.find_last_of("\\") + 1);
	};
	
	/// <summary>
	/// печать сообщения с посветкой 
	/// </summary>
	/// <param name="_color"> - цвет из CCS</param>
	/// <param name="_msg"> - печатаемое сообщение</param>
	/// <param name="_width"> - ширина печати</param>
	static void HighlightedConsolePrint(
		std::string _msg,
		std::string _color = CCS::White,
		int _width = 0
	)
	{
		// substr здесь нужна только для вычленения из пути до файла сам файл
		std::cout << _color;
		NotHighlightedConsolePrint(_msg, _width);
		std::cout << CCS::Reset;
	};

	/// <summary>
	/// выбор печати (с подсветкой или без)
	/// </summary>
	/// <param name="_color"> - цвет из CCS</param>
	/// <param name="_msg"> - печатаемое сообщение</param>
	/// <param name="_width"> - ширина печати</param>
	static void ConsolePrint(
		std::string _msg,
		std::string _color = CCS::White,
		int _width = 0
	)
	{
		HighlightedConsolePrint(_msg, _color, _width);
	};

	// печать доп. информации
	static void PrintFuncData(std::string _fdata)
	{
		// вывод текущего времени 
		std::cout << "[";
		ConsolePrint(SupportFunctions::GetCurrentTime(), CCS::Green);
		std::cout << "] ";

		// файл
		std::cout << "[file: ";
		ConsolePrint(SupportFunctions::GetToken(_fdata), CCS::Green, 0);
		std::cout << "] ";

		// функция
		std::cout << "[func: ";
		ConsolePrint(SupportFunctions::GetToken(_fdata), CCS::Green, 0);
		std::cout << "] ";

		// строка
		std::cout << "[line: ";
		ConsolePrint(SupportFunctions::GetToken(_fdata), CCS::Green, 0);
		std::cout << "] ";

		// сообщение
		std::cout << "[msg: ";
		ConsolePrint(SupportFunctions::GetToken(_fdata), CCS::Green, 0);
		std::cout << "]\n";
	};		

	// вывод сообщения определенного типа
	static void Info(std::string _fdata)
	{
		// вывод типа сообщения
		std::cout << "[";
		ConsolePrint("INFO", CCS::Green);
		std::cout << "] ";

		PrintFuncData(_fdata);
	};

	static void Error(std::string _fdata)
	{
		// вывод типа сообщения
		std::cout << "[";
		ConsolePrint("ERROR", CCS::Red);
		std::cout << "] ";

		PrintFuncData(_fdata);

		exit(1);
	};	

	// информация о функции
#define DEL std::string(";")
#define TOSTR(arg) std::to_string(arg)
#define FDATA(msg) __FILE__+DEL+__FUNCTION__+DEL+TOSTR(__LINE__)+DEL+msg
		

// сокращения
#define INFO(msg) Info(FDATA(msg))
#define ERROR(msg) Error(FDATA(msg))


#endif
