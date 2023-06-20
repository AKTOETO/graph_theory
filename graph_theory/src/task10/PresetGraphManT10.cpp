#include "../pch.h"
#include "PresetGraphManT10.h"


PresetGraphManT10::PresetGraphManT10(
	const S_PTR(SystemSetting)& _settings,
	const S_PTR(Graph)& _graph,
	const S_PTR(StateVector) _states
)
	:// инициализация всех полей
	BaseGraphPresetManager(_settings, _graph, _states),
	m_bandwidth(nullptr),
	m_max_flow_length(0),
	m_source(-1),
	m_sink(-1)
{
	m_lst.clear();
}

PresetGraphManT10::~PresetGraphManT10()
{
}

bool PresetGraphManT10::CalculateMaxFlow()
{
	// ищем источник и ток
	ALGO::FindSourceAndSink(m_graph, m_source, m_sink);

	m_max_flow_length =
		ALGO::FordFulkerson(m_graph, m_bandwidth, m_source, m_sink);

	// конвертация матрицы остаточных путей в список ребер
	// с указанием величины потока
	for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
	{
		for (int j = 0; j < m_graph->adjacency_matrix().size(); j++)
		{
			if (m_graph->adjacency_matrix()[i][j])
			{
				m_lst.push_back(
					EdgeBandwidth(i, j,
						m_graph->adjacency_matrix()[i][j] - (*m_bandwidth)[i][j],
						m_graph->adjacency_matrix()[i][j])
				);
			}
		}
	}

	return true;
}

bool PresetGraphManT10::CalculateFlowLength()
{
	IF_ST_SHOULD_BE_CALC(SPEC::T10_FORD_FULKERSON, CalculateMaxFlow());
	IF_ST_CALC(SPEC::T10_FORD_FULKERSON)return true;
	return false;
}

const EdgeBandwidthList& PresetGraphManT10::GetBandwidth() const
{
	return m_lst;
}

const Weight& PresetGraphManT10::GetFlowLength() const
{
	return m_max_flow_length;
}

const Vertex& PresetGraphManT10::GetSource() const
{
	return m_source;
}

const Vertex& PresetGraphManT10::GetSink() const
{
	return m_sink;
}

