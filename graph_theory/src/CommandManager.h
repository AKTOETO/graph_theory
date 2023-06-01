#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#include "Managers/ScriptManager.h"


// обработчик введенных ключей
class CommandManager
{
private:
	// список возможных команд с указателями на функции,
	// выполняющие эти команды
	std::unordered_map<std::string, void(CommandManager::*)(Params)> m_commands;

	// Управляющий сценарием выполнения программы
	U_PTR(ScriptManager) m_script_mananger;

	// Введенные параметры при запуске
	Params m_param;

	// поток вывода данных
	std::ofstream m_fout;

	// настройки системы
	SystemSetting m_sys_settings;
	bool m_is_h;

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

	// Task8 проверка наличия ключей -m -nn -dd
	bool IsCorrectNumberOfMNNDD();

	////////////////////////////////////////////
	// функции, выполняющие введенные команды
	////////////////////////////////////////////

	/// <summary>
	/// Считывание списка ребер из файла
	/// </summary>
	/// <param name="_data"> - путь к файлу со списком ребер</param>
	void ReadEdgesList(Params _data);

	/// <summary>
	/// Считывание матрицы смежности
	/// </summary>
	/// <param name="_data"> - путь к файлу с матрицой смежности</param>
	void ReadAdjacencyMatrix(Params _data);

	/// <summary>
	/// Считывание списка смежности
	/// </summary>
	/// <param name="_data"> - путь к файлу со списком смежности</param>
	void ReadAdjacencyList(Params _data);

	/// <summary>
	/// Задание файлового пути вывода информации
	/// </summary>
	/// <param name="_data"></param>
	void SetOutputFilepath(Params _data);

	/// <summary>
	/// Печать информации об авторе работы, группе, списке клбючей с кратким описанием
	/// </summary>
	/// <param name="_data"></param>
	void GetDeveloperData(Params _data);

	// TASK 4
	// Обработка ключей
	// -k - алгоритм Крускала
	void SetCruscalSpec(Params _data);

	// Обработка ключей
	// -p - алгоритм Прима
	void SetPrimSpec(Params _data);

	// Обработка ключей
	// -b - алгоритм Борувки
	void SetBoruvkaSpec(Params _data);

	// Обработка ключей
	// -s - все 3 предыдущих алгоритма вместе
	void SetCruscalPrimBoruvkaSpec(Params _data);

	// TASK 5
	// Обработка ключей
	// установка начальной точки
	void SetFromVertex(Params _data);

	// установка конечной точки
	void SetToVertex(Params _data);

	// TASK 6
	// Обработка ключей
	// -di - алгоритм Дейкстры
	void SetDijkstraSpec(Params _data);

	// Обработка ключей
	// -be - алгоритм Беллмана-Форда-Мура
	void SetBellmanFordMurSpec(Params _data);

	// Обработка ключей
	// -t - алгоритм Левита
	void SetLevitSpec(Params _data);

	// TASK 8
	// Обработка ключей
	// -m путь к файлу карты
	void SetMapFilepath(Params _data);

	// -nn начальная верщина x y
	void SetSourceCell(Params _data);

	// -dd конечная вершина x y
	void SetDestinationCell(Params _data);

};

#endif // COMMANDMANAGER_H
