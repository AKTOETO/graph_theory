#ifndef GRAPH_H
#define GRAPH_H

#include "logger/Logger.h"

// класс, содержащий граф
class Graph
{
private:

	// путь до файла с графом
	std::string m_filepath;

	// матрица смежности
	VertexMatrix m_adjacency_matrix;


	/// <summary>
	/// Чтение графа из файла с определенной структурой:
	/// (в11) (в12) (вес)
	/// .................
	/// (вn1) (вn2) (вес), где:
	/// 
	/// в(индекс)1 - вершина, из которой выходит ребро 
	/// в(индекс)2 - вершина, в которую входит ребро 
	/// вес - вес ребра
	/// 
	/// </summary>
	void ReadGraphFromFile(std::ifstream& _ifstream);

public:
	/// <summary>
	/// Конструктор класса Graph
	/// </summary>
	/// <param name="_filepath"> - путь к файлу, содержащий название файла с его расширением</param>
	Graph(std::string _filepath);
	
	// деструктор класса
	~Graph();

	
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
	VertexArr adjacency_list(Vertex _v) const;

	/// <summary>
	/// Возврат списка ребер
	/// </summary>
	/// <returns></returns>
	EdgeArr list_of_edges() const;

	/// <summary>
	/// Ребра графа, инцидентные вершине _v
	/// </summary>
	/// <param name="_v"> - исходная вершина</param>
	/// <returns>список ребер</returns>
	EdgeArr list_of_edges(Vertex _v) const;

	/// <summary>
	/// Возврат true, если граф ориентированный,
	/// иначе - false
	/// </summary>
	/// <returns></returns>
	bool is_directed() const;
};

#endif // GRAPH_H
