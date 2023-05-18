#include "../pch.h"
#include "PresetGraphManT7.h"

PresetGraphManT7::PresetGraphManT7(
	const S_PTR(SystemSetting)& _settings,
	const S_PTR(Graph)& _graph,
	const S_PTR(StateVector) _states
) :// инициализация всех полей
	BaseGraphPresetManager(_settings, _graph, _states),
	m_is_there_negative_cycle(0),
	m_is_there_negative_edges(0),
	m_dist(nullptr)
{}

PresetGraphManT7::~PresetGraphManT7()
{
}

//bool PresetGraphManT7::CalculateBellmanFordMurShortPath()
//{
//	// Запуск алгоритма Дейкстры с модификацией Форда
//	// и проверка на наличие отрицательного цикла
//	// Запуск производится только если еще
//	// не было найдено отрицательного цикла
//	if (!m_is_there_negative_cycle)
//	{
//		m_dist.reset();
//		U_PTR(VertexArr) parent;
//		ALGO::BellmanFord(
//			m_graph, m_sys_settings->m_from, 0, m_dist, m_is_there_negative_cycle
//		);
//		// если есть отрицательный цикл, то отмечаем кратчайший путь не найденным
//		if (m_is_there_negative_cycle)
//			return false;
//		return true;
//	}
//	return false;
//}

bool PresetGraphManT7::CalculateJhonsonShortPath()
{
	if (!m_is_there_negative_cycle)
	{
		m_dist.reset();
		m_is_there_negative_cycle = ALGO::Jhonson(
			m_graph, m_dist
		);
		// если есть отрицательный цикл, то отмечаем кратчайший путь не найденным
		if (m_is_there_negative_cycle)
			return false;
		return true;
	}
	return false;
}

bool PresetGraphManT7::CalculateIsThereNegativeEdges()
{
	// для вычисления существования ребер с отрицательными весами
	// надо убедиться, что нет отрицательного цикла
	IF_ST_SHOULD_BE_CALC(SPEC::T7_USE_JHONSON, CalculateJhonsonShortPath());

	// если отрицательного цикла нет, смотрим, есть ли отрицательные ребра
	if (!m_is_there_negative_cycle)
	{
		auto lst = m_graph->list_of_edges();
		// если было найдено ребро с отрицательным весом
		if (
			std::find_if(lst.begin(), lst.end(), [](const Edge& ed)
				{ return ed.m_weight < 0; }
			) != lst.end()
			)
		{
			// запоминаем, что есть отрицательные ребра
			m_is_there_negative_edges = 1;
			return true;
		}
	}
	return false;
}

bool PresetGraphManT7::CalculateIsThereNoNegativeEdges()
{
	IF_ST_SHOULD_BE_CALC(SPEC::T7_NEGATIVE_EDGES, CalculateIsThereNegativeEdges());
	IF_ST_NOT_CALC(SPEC::T7_NEGATIVE_EDGES)
	{

		// если отрицательного цикла нет, смотрим, есть ли отрицательные ребра
		if (!m_is_there_negative_cycle)
		{
			m_is_there_negative_edges = 0;
			return true;
		}
	}
	return false;
}

bool PresetGraphManT7::CalculaetNegativeCycle()
{
	IF_ST_SHOULD_BE_CALC(SPEC::T7_USE_JHONSON, CalculateJhonsonShortPath());
	return m_is_there_negative_cycle;
}




const bool& PresetGraphManT7::GetIsThereNegativeEdges() const
{
	return m_is_there_negative_edges;
}

const bool& PresetGraphManT7::GetIsThereNegativeCycle() const
{
	return m_is_there_negative_cycle;
}

const VertexMatrix& PresetGraphManT7::GetJhonsonDistancies() const
{
	return *m_dist;
}
