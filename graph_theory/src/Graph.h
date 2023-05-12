#ifndef GRAPH_H
#define GRAPH_H

#include "Logger.hpp"


// класс, содержащий граф
class Graph
{
private:

	//==========================
	//   П Е Р Е М Е Н Н Ы Е
	//==========================
	
	// матрица смежности
	VertexMatrix m_adjacency_matrix;

	//==========================
	//      Ф У Н К Ц И И
	//==========================

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

public:

	// конструктор с путем до файла и типом файла
	Graph(std::string _filepath, INPUT_FILE_TYPE);
	
	// конструктор копирования графа
	Graph(const Graph& _graph);

	// конструктор графа от матрицы смежности
	Graph(const VertexMatrix& _v_matr);

	// конструктор графа от списка ребер
	Graph(const EdgeList& _e_list);

	// деструктор класса
	~Graph();

	/// <summary>
	/// считывание графа из файла
	/// </summary>
	/// <param name="_filepath"> - путь к файлу, содержащий название файла с его расширением</param>
	void ReadGraphFromFile(std::string _filepath, INPUT_FILE_TYPE);

	// вывод матрицы смежности
	void PrintAdjacencyMatrix() const;
	
	/// <summary>
	/// Возвращает вес ребра, связывающего вершины _vi и _vj
	/// </summary>
	/// <param name="_vi"> - откуда исходит ребро</param>
	/// <param name="_vj"> - куда входит ребро</param>
	/// <returns>вес ребра</returns>
	int weight(Vertex _vi, Vertex _vj) const;
	
	/// <summary>
	/// Возвращает true, если есть ребро между _vi и _vj,
	/// иначе - false
	/// </summary>
	/// <param name="_vi"> - откуда исходит ребро</param>
	/// <param name="_vj"> - куда входит ребро</param>
	/// <returns>true/false</returns>
	bool is_edge(Vertex _vi, Vertex _vj) const;

	/// <summary>
	/// Возврат матрицы смежности
	/// </summary>
	/// <returns>матрицы смежности</returns>
	const VertexMatrix& adjacency_matrix() const;

	/// <summary>
	/// Получение списка вершин, смежных с вершиной _v
	/// </summary>
	/// <param name="_v"> - исходная вершина</param>
	/// <returns>список вершин</returns>
	VertexList adjacency_list(Vertex _v) const;

	/// <summary>
	/// Возврат списка ребер
	/// </summary>
	/// <returns> - список ребер</returns>
	EdgeList list_of_edges() const;

	/// <summary>
	/// Ребра графа, инцидентные вершине _v
	/// </summary>
	/// <param name="_v"> - исходная вершина</param>
	/// <returns> - список ребер</returns>
	EdgeList list_of_edges(Vertex _v) const;

	/// <summary>
	/// Возврат true, если граф ориентированный,
	/// иначе - false
	/// </summary>
	/// <returns></returns>
	bool is_directed() const;
};

#endif // GRAPH_H
