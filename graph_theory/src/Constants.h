#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pch.h"

//=========================//
// КАКОЕ ЗАДАНИЕ ЗАПУСКАТЬ //
//=========================//
// T1, T2, T3, MULTITASK
#define T3

//===================//
// К О Н С Т А Н Т Ы //
//===================//

// путь до папки с файлами для графа
const std::string GRAPH_FILE_PATH = "assets/graphs/";

// путь до папки с файлами вывода программы
const std::string RESULT_FILE_PATH = "assets/results/";

// для алгоритма ФЛОЙДА-УОРШЕЛЛА
#define INF 9999999

// ширина при выводе символа бесконечности 
#define INF_PRINT_WIDTH 2

// Количество характеристик
#define NUMBER_OF_SPECIFIERS 22

//===========================//
// С П Е Ц И Ф И К А Т О Р Ы //
//===========================//

// возможные характеристики, которые есть у графа
// и которые можно просчитать
enum class SPEC
{
	// task1
	SHORTEST_DIST_MATR,
	ECCENTR,
	CENTRAL_VERT,
	PERIPHERAL_VERT,
	RADIUS,
	DIAMETER,
	DEGREES_IN,
	DEGREES_OUT,
	DEGREES_IN_OUT,

	// task2
	// не ориентированный граф
	IS_CONNECTED,
	IS_NOT_CONNECTED,
	CONNECTED_COMPONENTS,

	// ориентированный граф
	IS_DIGRAPH_CONNECTED,
	IS_DIGRAPH_NOT_CONNECTED,
	DIGRAPH_WEAKLY_CONNECTED_COMPONENTS,
	DIGRAPH_STRONGLY_CONNECTED_COMPONENTS,
	IS_DIGRAPH_WEAKLY_CONNECTED,
	IS_DIGRAPH_STRONGLY_CONNECTED, 

	// task3
	// не ориентированный граф
	BRIDGES,
	PIVOT,

	// ориентированный граф
	DIGRAPH_BRIDGES,
	DIGRAPH_PIVOT
};

// тип данных сценария выполнения программы
using Script = std::list<SPEC>;

// тип данных массива состояний
using State = std::vector<bool>;

//===================//
//  С Ц Е Н А Р И Й  //
//===================//

#if defined(T1)
// сценарий для первого задания
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

#elif defined(T2)
// сценарий для второго задания
static const Script TASK_SCRIPT = Script
{
	SPEC::IS_CONNECTED,
	SPEC::IS_NOT_CONNECTED,
	SPEC::IS_DIGRAPH_CONNECTED,
	SPEC::IS_DIGRAPH_NOT_CONNECTED,

	SPEC::CONNECTED_COMPONENTS,
	SPEC::DIGRAPH_WEAKLY_CONNECTED_COMPONENTS,

	SPEC::IS_DIGRAPH_STRONGLY_CONNECTED,
	SPEC::IS_DIGRAPH_WEAKLY_CONNECTED,

	SPEC::DIGRAPH_STRONGLY_CONNECTED_COMPONENTS,
};

#elif defined(T3)
// сценарий для третьего задания
static const Script TASK_SCRIPT = Script
{
	SPEC::BRIDGES,
	SPEC::PIVOT,

	SPEC::DIGRAPH_BRIDGES,
	SPEC::DIGRAPH_PIVOT,
};
#elif defined(T4)

#elif defined(T5)

#elif defined(T6)

#elif defined(T7)

#elif defined(T8)

#elif defined(T9)

#elif defined(T10)

#elif defined(T11)

#elif defined(MULTITASK)
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
	SPEC::PERIPHERAL_VERT,
	SPEC::IS_CONNECTED,
	SPEC::IS_NOT_CONNECTED,
	SPEC::IS_DIGRAPH_CONNECTED,
	SPEC::IS_DIGRAPH_NOT_CONNECTED,

	SPEC::CONNECTED_COMPONENTS,
	SPEC::DIGRAPH_WEAKLY_CONNECTED_COMPONENTS,

	SPEC::IS_DIGRAPH_STRONGLY_CONNECTED,
	SPEC::IS_DIGRAPH_WEAKLY_CONNECTED,

	SPEC::DIGRAPH_STRONGLY_CONNECTED_COMPONENTS,
};

#endif 



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

// массив вершин
using VertexArr = std::vector<Vertex>;

// список вершин
using VertexList = std::list<Vertex>;

// очередь вершин
using VertexQueue = std::queue<Vertex>;

// матрица
using VertexMatrix = std::vector<VertexArr>;

// список вершин в компонентах связности
using ConnectCompList = std::list<VertexArr>;

// список посещенных вершин
using VisitedVert = std::vector<bool>;

//=============//
// Ш А Р Н И Р //
//=============//

// шарнир
using Pivot = Vertex;

// список массив шарниров
using PivotArr = std::vector<bool>;

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
using EdgeList = std::list<Edge>;

//===============//
//   В Р Е М Я   //
//===============//

// время
using Time = int;

// массив времен
using TimeArr = std::vector<Time>;

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
\n\
Задание 4:\n\
-k алгоритм Крускала\n\
-p алгоритм Прима\n\
-b алгоритм Борувки\n\
-s расчет производится тремя алгоритмами поочередно\n\
";

#endif // CONSTANTS_H
