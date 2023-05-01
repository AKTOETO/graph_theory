#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pch.h"

// путь до папки с файлами для графа
const std::string GRAPH_FILE_PATH = "assets/graphs/";

// путь до папки с файлами вывода программы
const std::string RESULT_FILE_PATH = "assets/results/";

// для алгоритма ФЛОЙДА-УОРШЕЛЛА
#define INF 9999999

// ширина при выводе символа бесконечности 
#define INF_PRINT_WIDTH 2

// Количество характеристик
#define NUMBER_OF_SPECIFIERS 9

// возможные характеристики, которые есть у графа
// и которые можно просчитать
enum class SPEC
{
	SHORTEST_DIST_MATR,
	ECCENTR,
	CENTRAL_VERT,
	PERIPHERAL_VERT,
	RADIUS,
	DIAMETER,
	DEGREES_IN,
	DEGREES_OUT,
	DEGREES_IN_OUT,
};

// тип данных сценария выполнения программы
using Script = std::list<SPEC>;

//===================//
//  С Ц Е Н А Р И Й  //
//===================//
static const Script TASK_SCRIPT = Script
{
	SPEC::DEGREES_IN_OUT,
	SPEC::DEGREES_IN,
	SPEC::DEGREES_OUT,
	SPEC::SHORTEST_DIST_MATR,
	SPEC::ECCENTR,
	SPEC::DIAMETER,
	SPEC::RADIUS,
	SPEC::CENTRAL_VERT,
	SPEC::PERIPHERAL_VERT
};

//===================//
// У К А З А Т Е Л И //
//===================//

#define U_PTR(type) std::unique_ptr<type>
#define S_PTR(type) std::shared_ptr<type>

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
