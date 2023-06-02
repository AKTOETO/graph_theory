#include "../pch.h"
#include "PresetGraphManT5.h"

PresetGraphManT5::PresetGraphManT5(
	const S_PTR(SystemSetting)& _settings,
	const S_PTR(Graph)& _graph,
	const S_PTR(StateVector) _states
) :// инициализация всех полей
	BaseGraphPresetManager(_settings, _graph, _states),
	m_dist_manh(INF)
{}

PresetGraphManT5::~PresetGraphManT5()
{
	//m_parent.reset();
}

bool PresetGraphManT5::CalculateShortPathDijkstra()
{
	INFO("Расчет кратчайшего расстояния между вершинами, Дейкста");

	// если вершины не больше их количества
	if (
		m_sys_settings->m_from < m_graph->adjacency_matrix().size() &&
		m_sys_settings->m_to < m_graph->adjacency_matrix().size()
		)
	{
		// кратчайшие расстояния не нужны в этой программе
		// как и вектор предков,
		// поэтому _dist определен не в поле класса, а здесь
		U_PTR(VertexArr) dist;
		U_PTR(VertexArr) parent;
		m_dist_manh = ALGO::Dijkstra(m_graph, m_sys_settings->m_from, m_sys_settings->m_to, dist, parent);

		// если есть путь
		if (m_dist_manh != INF)
			// конвертация вектора предков в список ребер
			m_short_dist_edge_list =
			ALGO::ConvDijksrtasVectToEdgeList(m_graph, parent, m_sys_settings->m_from, m_sys_settings->m_to);

		return true;
	}
	ERROR("Индекс начальной или конечной вершины больше количества вершин. n="
		+ std::to_string(m_sys_settings->m_from) + " d=" + std::to_string(m_sys_settings->m_to) +
		" количество вершин=" + std::to_string(m_graph->adjacency_matrix().size())
	);
	return false;
}

bool PresetGraphManT5::CalculateThereIsShortestPath()
{
	// если мы попытались расчитать кратчайшее расстояние, 
	// то есть смысл определять есть ли оно или нет

	IF_ST_SHOULD_BE_CALC(SPEC::T5_DIJKSTRA_PATH, CalculateShortPathDijkstra());

	IF_ST_CALC(SPEC::T5_DIJKSTRA_PATH)
	{
		INFO("Расчет: нет ли пути");

		return m_dist_manh != INF;
	}
	return false;
}

bool PresetGraphManT5::CalculateThereIsNotShortestPath()
{
	// если мы попытались расчитать кратчайшее расстояние, 
	// то есть смысл определять есть ли оно или нет

	IF_ST_SHOULD_BE_CALC(SPEC::T5_DIJKSTRA_PATH, CalculateShortPathDijkstra());

	IF_ST_CALC(SPEC::T5_DIJKSTRA_PATH)
	{
		INFO("Расчет: есть ли путь");

		return m_dist_manh == INF;
	}
	return false;
}

const Weight& PresetGraphManT5::GetShortestDistToVert() const
{
	return m_dist_manh;
}

const EdgeList& PresetGraphManT5::GetShortestDistEdgeList() const
{
	return m_short_dist_edge_list;
}
