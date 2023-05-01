#pragma once
#include "GraphManager.h"


class ScriptPrintManager
{
private:
	// сценарий расчета и вывода характеристик
	U_PTR(Script) m_script;

	// Управляющий графом
	U_PTR(GraphManager) m_graph_manager;

	// список возможных характеристик графа
	// с указателями на функции печати этих характеристик
	std::unordered_map<SPEC, void(ScriptPrintManager::*)()const> m_specs;

public:
	ScriptPrintManager(std::string _filepath, INPUT_FILE_TYPE, Script);
	~ScriptPrintManager();

	// Главный метод, который нужно запустить для работы всего
	void Run();

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать матрицы кратчайших расстояний
	void PrintShortestDistMatrix() const;

	// печать списка эксцентриситетов
	void PrintEccentricity() const;

	// печать центральных вершин
	void PrintCentralVertices() const;

	// печать периферийных вершин
	void PrintPeripheralVertices() const;

	// печать радиуса
	void PrintRadius() const;

	// печать диаметра
	void PrintDiameter() const;

	// печать степени входа вершины
	void PrintVertexDegreesIn() const;

	// печать степени выхода вершины
	void PrintVertexDegreesOut() const;

	// печать степени входа и выхода вершины
	void PrintVertexDegreesInOut() const;
};

