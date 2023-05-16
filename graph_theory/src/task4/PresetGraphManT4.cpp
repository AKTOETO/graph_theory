#include "../pch.h"
#include "PresetGraphManT4.h"

PresetGraphManT4::PresetGraphManT4(
	const S_PTR(SystemSetting)& _settings,
	const S_PTR(Graph)& _graph,
	const S_PTR(State) _states
)
	:// инициализация всех полей
	BaseGraphPresetManager(_settings, _graph, _states),
	m_kruskal_spanning_tree(nullptr),
	m_prim_spanning_tree(nullptr),
	m_boruvka_spanning_tree(nullptr)
{
	// если исходный граф ориентированный
	// делаем из него соотнесенный
	if (m_graph->is_directed())
		m_cur_graph = std::make_shared<Graph>(ALGO::CorrelatedGraph(m_graph));
}

PresetGraphManT4::~PresetGraphManT4()
{
	m_boruvka_spanning_tree.reset();
	m_prim_spanning_tree.reset();
	m_kruskal_spanning_tree.reset();
}

//==================================//
//         CALCULATE МЕТОДЫ         //
//==================================//

bool PresetGraphManT4::CalculateKruskal()
{
	INFO("Расчет Краскал");

	// перевыделение памяти под список ребер мин. остовного дерева
	// и запись остовного дерева
	m_kruskal_spanning_tree.reset();

	auto start = std::chrono::high_resolution_clock::now();
	m_kruskal_spanning_tree = std::make_unique<SpanningTree>(ALGO::Kruskal(m_cur_graph));
	auto end = std::chrono::high_resolution_clock::now();

	m_kruskal_time = std::chrono::duration_cast<mcs>(end - start);

	return true;
}

bool PresetGraphManT4::CalculatePrim()
{
	INFO("Расчет Прим");

	// перевыделение памяти под список ребер мин. остовного дерева
	// и запись остовного дерева
	m_prim_spanning_tree.reset();

	auto start = std::chrono::high_resolution_clock::now();
	m_prim_spanning_tree = std::make_unique<SpanningTree>(ALGO::Prim(m_cur_graph));
	auto end = std::chrono::high_resolution_clock::now();

	m_prim_time = std::chrono::duration_cast<mcs>(end - start);

	return true;
}

bool PresetGraphManT4::CalculateBoruvka()
{
	INFO("Расчет Борувка");

	// перевыделение памяти под список ребер мин. остовного дерева
	// и запись остовного дерева
	m_boruvka_spanning_tree.reset();

	auto start = std::chrono::high_resolution_clock::now();
	m_boruvka_spanning_tree = std::make_unique<SpanningTree>(ALGO::Boruvka(m_cur_graph));
	auto end = std::chrono::high_resolution_clock::now();

	m_boruvka_time = std::chrono::duration_cast<mcs>(end - start);

	return true;
}

bool PresetGraphManT4::CalculateKruskalPrimBoruvka()
{
	// все алгоритмы должны быть расчитаны
	IF_ST_SHOULD_BE_CALC(SPEC::KRUSKAL, CalculateKruskal());
	IF_ST_SHOULD_BE_CALC(SPEC::BORUVKA, CalculateBoruvka());
	IF_ST_SHOULD_BE_CALC(SPEC::PRIM, CalculatePrim());

	IF_ST_CALC(SPEC::KRUSKAL) IF_ST_CALC(SPEC::BORUVKA) IF_ST_CALC(SPEC::PRIM)
		return true;

	return false;
}

//==================================//
//            GET МЕТОДЫ            //
//==================================//

const U_PTR(SpanningTree)& PresetGraphManT4::GetKruskalSpanTree() const
{
	return m_kruskal_spanning_tree;
}

const U_PTR(SpanningTree)& PresetGraphManT4::GetPrimSpanTree() const
{
	return m_prim_spanning_tree;
}

const U_PTR(SpanningTree)& PresetGraphManT4::GetBoruvkaSpanTree() const
{
	return m_boruvka_spanning_tree;
}

const ChronoDurationMcs& PresetGraphManT4::GetKruskalTime() const
{
	return m_kruskal_time;
}

const ChronoDurationMcs& PresetGraphManT4::GetPrimTime() const
{
	return m_prim_time;
}

const ChronoDurationMcs& PresetGraphManT4::GetBoruvkaTime() const
{
	return m_boruvka_time;
}
