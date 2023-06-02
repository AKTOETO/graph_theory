#include "../pch.h"
#include "PresetGraphManT8.h"

//PresetGraphManT7::PresetGraphManT7(
//	const S_PTR(SystemSetting)& _settings,
//	const S_PTR(Graph)& _graph,
//	const S_PTR(StateVector) _states
//) :// инициализация всех полей
//	BaseGraphPresetManager(_settings, _graph, _states),
//	m_is_there_negative_cycle(0),
//	m_is_there_negative_edges(0),
//	m_dist(nullptr)
//{}

//PresetGraphManT7::~PresetGraphManT7()
//{
//}
//
//bool PresetGraphManT7::CalculateJhonsonShortPath()
//{
//	if (!m_is_there_negative_cycle)
//	{
//		m_dist.reset();
//		m_is_there_negative_cycle = ALGO::Jhonson(
//			m_graph, m_dist
//		);
//		// если есть отрицательный цикл, то отмечаем кратчайший путь не найденным
//		if (m_is_there_negative_cycle)
//			return false;
//		return true;
//	}
//	return false;
//}
//
//bool PresetGraphManT7::CalculateIsThereNegativeEdges()
//{
//	// для вычисления существования ребер с отрицательными весами
//	// надо убедиться, что нет отрицательного цикла
//	IF_ST_SHOULD_BE_CALC(SPEC::T7_USE_JHONSON, CalculateJhonsonShortPath());
//
//	// если отрицательного цикла нет, смотрим, есть ли отрицательные ребра
//	if (!m_is_there_negative_cycle)
//	{
//		auto lst = m_graph->list_of_edges();
//		// если было найдено ребро с отрицательным весом
//		if (
//			std::find_if(lst.begin(), lst.end(), [](const Edge& ed)
//				{ return ed.m_weight < 0; }
//			) != lst.end()
//			)
//		{
//			// запоминаем, что есть отрицательные ребра
//			m_is_there_negative_edges = 1;
//			return true;
//		}
//	}
//	return false;
//}
//
//bool PresetGraphManT7::CalculateIsThereNoNegativeEdges()
//{
//	IF_ST_SHOULD_BE_CALC(SPEC::T7_NEGATIVE_EDGES, CalculateIsThereNegativeEdges());
//	IF_ST_NOT_CALC(SPEC::T7_NEGATIVE_EDGES)
//	{
//
//		// если отрицательного цикла нет, смотрим, есть ли отрицательные ребра
//		if (!m_is_there_negative_cycle)
//		{
//			m_is_there_negative_edges = 0;
//			return true;
//		}
//	}
//	return false;
//}
//
//bool PresetGraphManT7::CalculaetNegativeCycle()
//{
//	IF_ST_SHOULD_BE_CALC(SPEC::T7_USE_JHONSON, CalculateJhonsonShortPath());
//	return m_is_there_negative_cycle;
//}
//
//
//
//
//const bool& PresetGraphManT7::GetIsThereNegativeEdges() const
//{
//	return m_is_there_negative_edges;
//}
//
//const bool& PresetGraphManT7::GetIsThereNegativeCycle() const
//{
//	return m_is_there_negative_cycle;
//}
//
//const VertexMatrix& PresetGraphManT7::GetJhonsonDistancies() const
//{
//	return *m_dist;
//}

PresetGraphManT8::PresetGraphManT8(
	const S_PTR(SystemSetting)& _settings,
	const S_PTR(Graph)& _graph,
	const S_PTR(StateVector) _states
) :// инициализация всех полей
	BaseGraphPresetManager(_settings, _graph, _states),
	m_dist(nullptr),
	m_dist_length(nullptr),
	m_map(std::make_unique<Map>(m_sys_settings->m_filepath))
{
}

PresetGraphManT8::~PresetGraphManT8()
{
}

bool PresetGraphManT8::CalculateAStarShortestPath()
{
	bool found;

	Weight w = ALGO::AStar(
		m_map, m_dist, m_used_cell,
		m_sys_settings->m_begin, m_sys_settings->m_end,
		ALGO::Chebyshev, found);

	for (auto& el : *m_dist)
	{
		std::cout << "(" << el.GetX() << ", " << el.GetY() << "), ";
	}

	return false;
}

bool PresetGraphManT8::CalculateAStarShortestPathLength()
{
	return false;
}

const U_PTR(CellVector)& PresetGraphManT8::GetAStarShortestPath() const
{
	return m_dist;
}

const U_PTR(int)& PresetGraphManT8::GetAStarShortestPathLength() const
{
	return m_dist_length;
}
