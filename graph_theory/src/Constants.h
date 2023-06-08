#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pch.h"

//=========================//
// КАКОЕ ЗАДАНИЕ ЗАПУСКАТЬ //
//=========================//
// T1, T2, T3, T4, T5, T6, T7, T8, T9 - не сделал, T10
#define T10

//===================//
// К О Н С Т А Н Т Ы //
//===================//

// массив параметров
using Params = std::vector<std::string>;

// путь до папки с файлами для графа
const std::string GRAPH_FILE_PATH = "assets/graphs/";

// путь до папки с файлами вывода программы
const std::string RESULT_FILE_PATH = "assets/results/";

// бесконечность
#define INF 9999999

// ноль для нулевых ребер
#define NULLW -INF

// ширина при выводе символа бесконечности 
#define INF_PRINT_WIDTH 2

// Количество характеристик
#define NUMBER_OF_SPECIFIERS 45

//===========================//
// С П Е Ц И Ф И К А Т О Р Ы //
//===========================//

// возможные характеристики, которые есть у графа
// и которые можно просчитать
enum class SPEC
{	//==================//
	//      TASK 1      //
	//==================//
	T1_SHORTEST_DIST_MATR,
	T1_ECCENTR,
	T1_CENTRAL_VERT,
	T1_PERIPHERAL_VERT,
	T1_RADIUS,
	T1_DIAMETER,
	T1_DEGREES_IN,
	T1_DEGREES_OUT,
	T1_DEGREES_IN_OUT,

	//==================//
	//      TASK 2      //
	//==================//
	// неориентированный граф
	T2_IS_CONNECTED,
	T2_IS_NOT_CONNECTED,
	T2_CONNECTED_COMPONENTS,

	// ориентированный граф
	T2_IS_DIGRAPH_CONNECTED,
	T2_IS_DIGRAPH_NOT_CONNECTED,
	T2_DIGRAPH_WEAKLY_CONNECTED_COMPONENTS,
	T2_DIGRAPH_STRONGLY_CONNECTED_COMPONENTS,
	T2_IS_DIGRAPH_WEAKLY_CONNECTED,
	T2_IS_DIGRAPH_STRONGLY_CONNECTED,

	//==================//
	//      TASK 3      //
	//==================//
	// неориентированный граф
	T3_BRIDGES,
	T3_PIVOT,

	// ориентированный граф
	T3_DIGRAPH_BRIDGES,
	T3_DIGRAPH_PIVOT,

	//==================//
	//      TASK 4      //
	//==================//
	T4_KRUSKAL,
	T4_PRIM,
	T4_BORUVKA,
	T4_KRUSKAL_PRIM_BORUVKA,

	//==================//
	//      TASK 5      //
	//==================//
	T5_THERE_IS_SHORTEST_PATH,
	T5_THERE_IS_NOT_SHORTEST_PATH,
	T5_DIJKSTRA_PATH,

	//==================//
	//      TASK 6      //
	//==================//
	T6_USE_DIJKSTRA,
	T6_USE_BELLMAN_FORD_MUR,
	T6_USE_LEVIT,

	T6_NO_NEGATIVE_EDGES,
	T6_NEGATIVE_EDGES,

	T6_NEGATIVE_CYCLE,

	//==================//
	//      TASK 7      //
	//==================//
	T7_USE_JHONSON,

	T7_NO_NEGATIVE_EDGES,
	T7_NEGATIVE_EDGES,
	 
	T7_NEGATIVE_CYCLE,

	//==================//
	//      TASK 8      //
	//==================//
	T8_PATH,
	T8_PATH_LENGTH,

	//==================//
	//      TASK 9      //
	//==================//
	T9_ANT_COLONY,
	T9_BRANCH_AND_BOUND,

	//==================//
	//      TASK 10     //
	//==================//
	T10_FORD_FULKERSON,
	T10_MAXIMUM_FLOW,

};

// тип данных сценария выполнения программы
using Script = std::list<SPEC>;

// тип данных массива состояний
using StateVector = std::vector<bool>;

//===============================//
// ТИПЫ ВХОДНЫХ ФАЙЛОВ С ГРАФАМИ //
//===============================//
enum class INPUT_FILE_TYPE
{
	//  список ребер - это двумерная матрица, в которой
	//  (в11) (в12) (вес)
	//  .................
	//  (вn1) (вn2) (вес), где:
	//  
	//  в(индекс)1 - вершина, из которой выходит ребро
	//  в(индекс)2 - вершина, в которую входит ребро 
	//  вес - вес ребра
	//  
	EDGES_LIST,

	//  матрица смежности представляет из себя:
	//      к у д а
	//  от  a11 a12 ... a1n
	//  ку  a21 a22 ... a2n
	//  да  ...............
	//      an1 an2 ... ann
	//  где откуда - вершины, из которых выходит ребро
	//  куда - вершины, куда входит ребро
	//  коэффициенты aii - вес ребра: 
	//  0 - если ребра нет
	//  N - любое натуральное число, если ребро есть
	//  и оно имеет вес N
	//  
	ADJACENCY_MATRIX,

	//  список смежности представляет из себя:
	//  1) a1 ... an
	//  .) .........
	//  d) c1 ... cm
	//  где номера строк - вершины, из которых исходят ребра,
	//  а числа a1,...,an,...,c1,...,cm - вершины, в которые
	//  входят ребра
	//  
	ADJACENCY_LIST
};

//===================//
//  С Ц Е Н А Р И Й  //
//===================//

// В TASK_SCRIPT находятся те спецификаторы,
// которые должны выполняться по умолчанию ВСЕГДА
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
	SPEC::T2_IS_CONNECTED,
	SPEC::T2_IS_NOT_CONNECTED,
	SPEC::T2_IS_DIGRAPH_CONNECTED,
	SPEC::T2_IS_DIGRAPH_NOT_CONNECTED,

	SPEC::T2_CONNECTED_COMPONENTS,
	SPEC::T2_DIGRAPH_WEAKLY_CONNECTED_COMPONENTS,

	SPEC::T2_IS_DIGRAPH_STRONGLY_CONNECTED,
	SPEC::T2_IS_DIGRAPH_WEAKLY_CONNECTED,

	SPEC::T2_DIGRAPH_STRONGLY_CONNECTED_COMPONENTS,
};

#elif defined(T3)
// сценарий для третьего задания
static const Script TASK_SCRIPT = Script
{
	SPEC::T3_BRIDGES,
	SPEC::T3_PIVOT,

	SPEC::T3_DIGRAPH_BRIDGES,
	SPEC::T3_DIGRAPH_PIVOT,
};
#elif defined(T4)
// сценарий для четвертого задания
static const Script TASK_SCRIPT = Script
{
	// пусто, так как нужные параметры для расчета
	// выбираются путем ввода ключей
};
#elif defined(T5)
static const Script TASK_SCRIPT = Script
{
	SPEC::T5_THERE_IS_SHORTEST_PATH,
	SPEC::T5_THERE_IS_NOT_SHORTEST_PATH,
	SPEC::T5_DIJKSTRA_PATH
};
#elif defined(T6)
static const Script TASK_SCRIPT = Script
{
	SPEC::T6_NO_NEGATIVE_EDGES,
	SPEC::T6_NEGATIVE_EDGES,
	SPEC::T6_NEGATIVE_CYCLE,
};


#elif defined(T7)
static const Script TASK_SCRIPT = Script
{
	SPEC::T7_NO_NEGATIVE_EDGES,
	SPEC::T7_NEGATIVE_EDGES,
	SPEC::T7_NEGATIVE_CYCLE,
	SPEC::T7_USE_JHONSON,
};
#elif defined(T8)
static const Script TASK_SCRIPT = Script
{
	SPEC::T8_PATH_LENGTH,
	SPEC::T8_PATH,
};
#elif defined(T9)
static const Script TASK_SCRIPT = Script
{
};
#elif defined(T10)
static const Script TASK_SCRIPT = Script
{
	SPEC::T10_MAXIMUM_FLOW,
	SPEC::T10_FORD_FULKERSON,
};
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

// указатель на вектор указательей на VertexArr
// (матрица)
using PointerMatrix = std::vector<U_PTR(VertexArr)>;

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

// массив весов
using WeightVector = std::vector<Weight>;

// матрица весов
using WeightMatrix = std::vector<WeightVector>;

// пара, хранящая путь до вершины и саму вершину
using iPair = std::pair<Weight, Vertex>;

// ребро
struct Edge
{
	Vertex m_from;	// вершина, откуда исходир ребро
	Vertex m_to;	// вершина, куда идет ребро
	Weight m_weight;// вес ребра

};

// ребро с пропускной способностью
struct EdgeBandwidth:
	public Edge
{
	Weight m_bandwidth;	// пропускная способность
	EdgeBandwidth(Vertex _f, Vertex _t, Weight _w, Weight _b)
		:m_bandwidth(_b)
	{
		m_weight = _w;
		m_from = _f;
		m_to = _t;
	}
};

// список ребер с пропускной способностью
using EdgeBandwidthList = std::list<EdgeBandwidth>;

// список ребер
using EdgeList = std::list<Edge>;

// массив ребер
using EdgeArr = std::vector<Edge>;

// оператор сравнения ребер по весу
struct EdgeGreater
{
	bool operator()(const Edge& _ed1, const Edge& _ed2)
	{
		//std::cout << _ed1.m_weight << " " << _ed2.m_weight << std::endl;
		return _ed1.m_weight > _ed2.m_weight;
	}
};

//=================================//
// СТРУКТУРА НАСТРОЕК ВСЕЙ СИСТЕМЫ //
//=================================//
struct SystemSetting
{
	// список спецификаторов, которые ОБЯЗАТЕЛЬНО выполняются
	// (обязательные спецификаторы копируются из TASK_SCRIPT)
	// + спецификаторы, которые добавляются ключами программы
	// через CommandManager
	Script m_script;

	// путь до файла с данными
	// (для 8 задачи - путь к файлу с картой)
	std::string m_filepath;

	// тип файла ввода данных
	INPUT_FILE_TYPE m_in_type;

	// начальная и конечная точка геодезической цепи
	Vertex m_from, m_to;

	// Task 8 
	// начальная и конечная клетка 
	Cell m_begin;
	Cell m_end;

	// конструктор по умолчанию
	SystemSetting() :
		m_script(TASK_SCRIPT),
		m_filepath(""),
		m_in_type(INPUT_FILE_TYPE::ADJACENCY_MATRIX),
		m_from(0),
		m_to(0)
	{}
};

//==================//
//	ОСТОВНОЕ ДЕРЕВО	//
//==================//

struct SpanningTree
{
	// список ребер дерева
	EdgeList m_edge_list;

	// его вес
	int m_weight;

	SpanningTree()
		:m_weight(0)
	{}

	SpanningTree(const SpanningTree& _span)
	{
		m_weight = _span.m_weight;
		m_edge_list = _span.m_edge_list;
	}
};

//===============//
//   В Р Е М Я   //
//===============//

// время
using Time = int;

// массив времен
using TimeArr = std::vector<Time>;

// время из библиотеки chrono
using ChronoDurationMcs = std::chrono::duration<long long, std::micro>;

using ms = std::chrono::milliseconds;
using mcs = std::chrono::microseconds;


//==============//
//	К А Р Т А	//
//==============//

// вектор клеток
using CellVector = std::vector<Cell>;

// матрица ячеек
using CellMatrix = std::vector<CellVector>;

// ячейка с весом
using WeightedCell = std::pair<Weight, Cell>;

// посещенные клетки
using VisitedCell = std::vector<VisitedVert>;

// вектор взвешенных ячеек
using WeightedCellVector = std::vector<WeightedCell>;

// список соседей
using NeighborsList = std::list<WeightedCell>;

// оператор сравнения взвешенных вершин
struct WeightedCellGreater
{
	bool operator()(const WeightedCell& _wc1, const WeightedCell& _wc2)
	{
		return _wc1.first > _wc2.first;
	}
};

// тип эфристической функции
using HeuristicFunc = Weight(*)(const Cell&, const Cell&);

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
\n\
Задание 5:\n\
-n начальная вершина\n\
-d конечная вершина\n\
\n\
Задание 6:\n\
-di алгоритм Дейкстры\n\
-be алгоритм Беллмана-Форда\n\
-t алгоритм Левита\n\
-n начальная вершина\n\
\n\
Задание 7:\n\
\n\
Задание 8:\n\
-di алгоритм Дейкстры\n\
-be алгоритм Беллмана-Форда\n\
-t алгоритм Левита\n\
-n начальная вершина\n\
\n\
";

#endif // CONSTANTS_H
