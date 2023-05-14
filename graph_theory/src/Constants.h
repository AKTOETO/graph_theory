﻿#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pch.h"

//=========================//
// КАКОЕ ЗАДАНИЕ ЗАПУСКАТЬ //
//=========================//
// T1, T2, T3, T4, MULTITASK
#define T4

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
#define NUMBER_OF_SPECIFIERS 30

//===========================//
// С П Е Ц И Ф И К А Т О Р Ы //
//===========================//

// возможные характеристики, которые есть у графа
// и которые можно просчитать
enum class SPEC
{	//===================//
	// TASK 1
	SHORTEST_DIST_MATR,
	ECCENTR,
	CENTRAL_VERT,
	PERIPHERAL_VERT,
	RADIUS,
	DIAMETER,
	DEGREES_IN,
	DEGREES_OUT,
	DEGREES_IN_OUT,

	//===================//
	// TASK 2
	// неориентированный граф
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

	//===================//
	// TASK 3
	// неориентированный граф
	BRIDGES,
	PIVOT,

	// ориентированный граф
	DIGRAPH_BRIDGES,
	DIGRAPH_PIVOT,

	//===================//
	// TASK 4
	// неориентированный граф
	CRUSCAL,
	PRIM,
	BORUVKA,
	CRUSCAL_PRIM_BORUVKA,

	// ориентированный граф
	DIGRAPH_CRUSCAL,
	DIGRAPH_PRIM,
	DIGRAPH_BORUVKA,
	DIGRAPH_CRUSCAL_PRIM_BORUVKA,

};

// тип данных сценария выполнения программы
using Script = std::list<SPEC>;

// тип данных массива состояний
using State = std::vector<bool>;

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
// сценарий для четвертого задания
static const Script TASK_SCRIPT = Script
{
	// пусто, так как нужные параметры для расчета
	// выбираются путем ввода ключей
};
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
	std::string m_filepath;

	// тип файла ввода данных
	INPUT_FILE_TYPE m_in_type;

	// конструктор по умолчанию
	SystemSetting() :
		m_script(TASK_SCRIPT),
		m_filepath(""),
		m_in_type(INPUT_FILE_TYPE::ADJACENCY_MATRIX)
	{}
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

// оператор сравнения ребер по весу
struct EdgeGreater
{
	bool operator()(const Edge& _ed1, const Edge& _ed2)
	{
		return _ed1.m_weight > _ed2.m_weight;
	}
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
