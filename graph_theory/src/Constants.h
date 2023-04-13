#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pch.h"

// путь до папки с файлами для графа
const std::string GRAPH_FILE_PATH = "assets/graphs/";

// путь до папки с файлами вывода программы
const std::string RESULT_FILE_PATH = "assets/results/";

// для алгоритма ФЛОЙДА-УОРШЕЛЛА
#define INF 9999999

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

//==================//
//	С П Р А В К А	//
//==================//

const std::string DEVELOPER_DATA = 
"\
Автор: Плоцкий Богдан\n\
Группа: М3О-211Б-21\n\
Описание комманд:\n\
-m считывание матрицы смежности\n\
-e считывание списка ребер\n\
-l считывание списка смежности\n\
-o если указан ключ, то результат программы выведется в файл, стоящий после этого ключа\n\
-h вывод справки о программе\n\
";

#endif // CONSTANTS_H
