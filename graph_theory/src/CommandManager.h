#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#include "Managers/ScriptManager.h"


// обработчик введенных ключей
class CommandManager
{
private:
	// список возможных команд с указателями на функции,
	// выполняющие эти команды
	std::unordered_map<std::string, void(CommandManager::*)(std::string)> m_commands;

	// Управляющий сценарием выполнения программы
	U_PTR(ScriptManager) m_script_mananger;

	// Введенные параметры при запуске
	std::vector<std::string> m_param;

	// поток вывода данных
	std::ofstream m_fout;

	// настройки системы
	SystemSetting m_sys_settings;

public:
	CommandManager() = delete;
	CommandManager(int argc, char* _keys[]);
	~CommandManager();

	// главная функция программы, в ней происходит
	// обработка всех команд
	void Run();

	// печать ключей с параметрами
	void PrintParams()const;

	// Конвертировать введенные параметры в вектор строк
	void ConverCharArrayToStrVec(int argc, char* _keys[]);

	////////////////////////////////////////////
	// функции проверок введенных команд
	////////////////////////////////////////////

	// обработка ключей
	void CheckKeys();

	// проверка на наличие ключа
	bool IsThereAExistsKey();

	// проверка на одновременное указание ключей -e -m -l
	bool IsCorrectNumberOfEML();

	// проверка на наличие определенного ключа 
	bool IsThereAKey(const std::string& _key);

	// Task4 проверка на наличие доп ключей: -k -p -b -s
	bool IsCorrectNumberOfKPBS();

	// Task5 проверка на наличие доп ключей: -n -d
	bool IsCorrectNumberOfND();

	// Task6 проверка на наличие доп ключей: -n
	bool IsCorrectNumberOfN();

	// Task6 проверка на наличие доп ключей: -di -be -t
	bool IsCorrectNumberOfDIBET();

	////////////////////////////////////////////
	// функции, выполняющие введенные команды
	////////////////////////////////////////////

	/// <summary>
	/// Считывание списка ребер из файла
	/// </summary>
	/// <param name="_data"> - путь к файлу со списком ребер</param>
	void ReadEdgesList(std::string _data);

	/// <summary>
	/// Считывание матрицы смежности
	/// </summary>
	/// <param name="_data"> - путь к файлу с матрицой смежности</param>
	void ReadAdjacencyMatrix(std::string _data);

	/// <summary>
	/// Считывание списка смежности
	/// </summary>
	/// <param name="_data"> - путь к файлу со списком смежности</param>
	void ReadAdjacencyList(std::string _data);

	/// <summary>
	/// Задание файлового пути вывода информации
	/// </summary>
	/// <param name="_data"></param>
	void SetOutputFilepath(std::string _data);

	/// <summary>
	/// Печать информации об авторе работы, группе, списке клбючей с кратким описанием
	/// </summary>
	/// <param name="_data"></param>
	void GetDeveloperData(std::string _data);

	// TASK 4
	// Обработка ключей
	// -k - алгоритм Крускала
	void SetCruscalSpec(std::string _data);

	// Обработка ключей
	// -p - алгоритм Прима
	void SetPrimSpec(std::string _data);

	// Обработка ключей
	// -b - алгоритм Борувки
	void SetBoruvkaSpec(std::string _data);

	// Обработка ключей
	// -s - все 3 предыдущих алгоритма вместе
	void SetCruscalPrimBoruvkaSpec(std::string _data);

	// TASK 5
	// Обработка ключей
	// установка начальной точки
	void SetFromVertex(std::string _data);

	// установка конечной точки
	void SetToVertex(std::string _data);

	// TASK 6
	// Обработка ключей
	// -di - алгоритм Дейкстры
	void SetDijkstraSpec(std::string _data);

	// Обработка ключей
	// -be - алгоритм Беллмана-Форда-Мура
	void SetBellmanFordMurSpec(std::string _data);

	// Обработка ключей
	// -t - алгоритм Левита
	void SetLevitSpec(std::string _data);

};

#endif // COMMANDMANAGER_H
