#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pch.h"


//==================//
//	В Е Р Ш И Н А	//
//==================//

// тип данных вершины
using Vertex = int;

// список вершин
using VertexArr = std::vector<Vertex>;

// матрица
using VertexMatrix = std::vector<VertexArr>;

//==============//
//	Р Е Б Р О	//
//==============//

// вес ребра
using Weight = int;

// ребро
struct Edge
{
	Vertex m_from;	// вершина, откуда исходир ребро
	Vertex m_to;	// вершина, куда идет ребро
	Weight m_weight;// вес ребра
};

// список ребер
using EdgeArr = std::vector<Edge>;


#endif // CONSTANTS_H
