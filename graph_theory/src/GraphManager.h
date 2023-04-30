#ifndef GRAPH_MANAGER_H
#define GRAPH_MANAGER_H

#include "Graph.h"

class GraphManager
{
private:
	//  указатель на объект графа
	std::unique_ptr<Graph> m_graph;

public:
	GraphManager();
	~GraphManager();

	/// <summary>
	/// Считывание списка смежносит из файла
	/// </summary>
	/// <param name="_ifstream"> - входной файл</param>
	void ReadAdjacencyListFromFile(std::ifstream& _ifstream);

	/// <summary>
	/// Считывание матрицы смежности из файла
	/// </summary>
	/// <param name="_ifstream"></param>
	void ReadAdjacencyMatrixFromFile(std::ifstream& _ifstream);

	/// <summary>
	/// Считывание списка ребер из файла
	/// </summary>
	/// <param name="_ifstream"></param>
	void ReadEdgesListFromFile(std::ifstream& _ifstream);

	/// <summary>
	/// Расчет матрицы кратчайших расстояний
	/// </summary>
	void CalculateShortDistMatr();

	/// <summary>
	/// Расчет эксцентриситета
	/// </summary>
	void CalculateEccentricity();

	/// <summary>
	/// Расчет радиуса
	/// </summary>
	void CalculateRadius();

	/// <summary>
	/// Расчет диаметра
	/// </summary>
	void CalculateDiameter();

	/// <summary>
	/// Расчет центральных вершин
	/// </summary>
	void CalculateCentralVertices();

	/// <summary>
	/// Расчет периферийных вершин
	/// </summary>
	void CalculatePeripheralVertices();

};

#endif // !GRAPH_MANAGER_H
