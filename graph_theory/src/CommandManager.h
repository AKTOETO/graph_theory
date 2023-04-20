#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#include "Graph.h"

// обработчик введенных ключей
class CommandManager
{
private:
	// список возможных команд с указателями на функции,
	// выполняющие эти команды
	std::unordered_map<std::string, void(CommandManager::*)(std::string)> m_commands;

	// Граф
	Graph m_graph;

	// Введенные параметры при запуске
	std::vector<std::string> m_param;

	std::ofstream m_fout;

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


};

#endif // COMMANDMANAGER_H
