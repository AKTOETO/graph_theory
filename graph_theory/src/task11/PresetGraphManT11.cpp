#include "../pch.h"
#include "PresetGraphManT11.h"


PresetGraphManT11::PresetGraphManT11(
	const S_PTR(SystemSetting)& _settings,
	const S_PTR(Graph)& _graph,
	const S_PTR(StateVector) _states
)
	:// инициализация всех полей
	BaseGraphPresetManager(_settings, _graph, _states),
	m_is_bipartite(1),
	m_bandwidth(nullptr),
	m_used(nullptr),
	m_edges(0)
{
	m_lst.clear();

#if defined(T11)
	// соотносим граф, если он ориентированный
	if (m_graph->is_directed())
		m_correl_graph = std::make_shared<Graph>(ALGO::CorrelatedGraph(m_graph));
	else
		m_correl_graph = m_graph;

#endif

}

PresetGraphManT11::~PresetGraphManT11()
{
}

bool PresetGraphManT11::CalculateIsBipartite()
{
	// количество вершин
	size_t len = m_graph->adjacency_matrix().size();

	// маркированные вершины
	m_used = std::make_unique<VertexArr>(len, 0);

	// проверка на двудольный граф
	for (int i = 0; i < len; i++)
	{
		// если вершина не посещена
		if ((*m_used)[i] == 0)
		{
			// если нет ребра, соединяющего i-ую вершину из одной доли
			// с какой либо вершиной из другой доли, то граф не двудольный
			if (!ALGO::DFSBipartite(m_correl_graph, m_used, i, 1))
			{
				m_is_bipartite = false;
				return false;
			}
		}
	}

	return true;
}

bool PresetGraphManT11::CalculateIsNotBipartite()
{
	IF_ST_SHOULD_BE_CALC(SPEC::T11_BIPARTITE, CalculateIsBipartite());
	IF_ST_NOT_CALC(SPEC::T11_BIPARTITE) return true;
	return false;
}

bool PresetGraphManT11::CalculateMaxMatching()
{
	IF_ST_SHOULD_BE_CALC(SPEC::T11_BIPARTITE, CalculateIsBipartite());
	IF_ST_CALC(SPEC::T11_BIPARTITE)
	{
		m_edges = ALGO::MaximumMatching(m_graph, m_used, m_bandwidth);

		// конвертация матрицы пропускной способности в список ребер
		for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
		{
			if ((*m_used)[i] == 1)
			{
				for (int j = 0; j < m_graph->adjacency_matrix().size(); j++)
				{
					if ((m_graph->adjacency_matrix()[i][j] - (*m_bandwidth)[i][j]) > 0)
						m_lst.push_back({ i + 1, j + 1 });
				}
			}
		}
		if (m_lst.empty())
			ERROR("Не было найдено подходщих ребер");

		return true;
	}
	return false;
}

bool PresetGraphManT11::GetIsBipartite() const
{
	return m_is_bipartite;
}

const EdgeList& PresetGraphManT11::GetMatching() const
{
	return m_lst;
}

const int& PresetGraphManT11::GetEdgeNumber() const
{
	return m_edges;
}
