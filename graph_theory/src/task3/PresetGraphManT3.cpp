#include "../pch.h"
#include "PresetGraphManT3.h"

PresetGraphManT3::PresetGraphManT3(
	const S_PTR(SystemSetting)& _settings,
	const S_PTR(Graph)& _graph,
	const S_PTR(State) _states
)
	:// инициализация всех полей
	BaseGraphPresetManager(_settings, _graph, _states),
	m_marked_vertices(nullptr),
	m_tin(nullptr),
	m_tout(nullptr),
	m_bridges(nullptr),
	m_pivots(nullptr)
{
}

PresetGraphManT3::~PresetGraphManT3()
{
	// очистка памяти
	m_marked_vertices.reset();
	m_tin.reset();
	m_tout.reset();
	m_bridges.reset();
	m_pivots.reset();
}

bool PresetGraphManT3::CalculateBridges()
{
	// если граф неориентированный
	if (!m_graph->is_directed())
	{
		INFO("расчет мостов в графе");

		// если мы считали шарниры, тогда надо обнулить 
		// масив времени входа, выхода, маркированных вершин
		IF_ST_CALC(SPEC::PIVOT)
		{
			// обнуление значний
			for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
			{
				m_marked_vertices->assign(m_graph->adjacency_matrix().size(), 0);
				m_tin->assign(m_graph->adjacency_matrix().size(), 0);
				m_tout->assign(m_graph->adjacency_matrix().size(), 0);
			}
		}
		// иначе выделяем память под эти массивы
		else
		{
			// выделение памяти под массив времени входа, выхода
			m_marked_vertices = std::make_unique<VisitedVert>(m_graph->adjacency_matrix().size(), 0);
			m_tin = std::make_unique<TimeArr>(m_graph->adjacency_matrix().size(), 0);
			m_tout = std::make_unique<TimeArr>(m_graph->adjacency_matrix().size(), 0);
		}
		
		// основной алгоритм
		{
			// выделение памяти под список мостов
			m_bridges = std::make_unique<EdgeList>(0);

			// текущее время
			Time time = 0;

			// поиск мостов поиском в глубину
			for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
			{
				INFO(std::to_string(i));
				// если вершина не посещена
				if (!(*m_marked_vertices)[i])
				{
					ALGO::BridgeDFS(m_graph, m_marked_vertices, i, time, m_tin, m_tout, m_bridges);
				}
			}
		}
		return true;
	}
    return false;
}

bool PresetGraphManT3::CalculatePivots()
{
	// если граф неориентированный
	if (!m_graph->is_directed())
	{
		INFO("расчет шарниров в графе");

		// если мы считали мосты, тогда надо обнулить 
		// масив времени входа, выхода, маркированных вершин
		IF_ST_CALC(SPEC::BRIDGES)
		{
			// обнуление значний
			for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
			{
				m_marked_vertices->assign(m_graph->adjacency_matrix().size(), 0);
				m_tin->assign(m_graph->adjacency_matrix().size(), 0);
				m_tout->assign(m_graph->adjacency_matrix().size(), 0);
			}
		}
		// иначе выделяем память под эти массивы
		else
		{
			// выделение памяти под массив времени входа, выхода
			m_marked_vertices = std::make_unique<VisitedVert>(m_graph->adjacency_matrix().size(), 0);
			m_tin = std::make_unique<TimeArr>(m_graph->adjacency_matrix().size(), 0);
			m_tout = std::make_unique<TimeArr>(m_graph->adjacency_matrix().size(), 0);
		}

		// основной агоритм
		{
			// выделение памяти под массив шарниров
			m_pivots = std::make_unique<PivotArr>(m_graph->adjacency_matrix().size(), 0);

			// текущее время
			Time time = 0;

			// поиск шарниров поиском в глубину
			for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
			{
				// если вершина не посещена
				if (!(*m_marked_vertices)[i])
				{
					ALGO::PivotDFS(m_graph, m_marked_vertices, i, time, m_tin, m_tout, m_pivots);
				}
			}
		}
		return true;
	}
    return false;
}

bool PresetGraphManT3::CalculateDigraphBridges()
{
	// если граф ориентированный
	if (m_graph->is_directed())
	{
		INFO("расчет мостов в орграфе");

		// если мы считали шарниры в орграфе, тогда надо обнулить 
		// масив времени входа, выхода, маркированных вершин
		IF_ST_CALC(SPEC::DIGRAPH_PIVOT)
		{
			// обнуление значний
			for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
			{
				m_marked_vertices->assign(m_graph->adjacency_matrix().size(), 0);
				m_tin->assign(m_graph->adjacency_matrix().size(), 0);
				m_tout->assign(m_graph->adjacency_matrix().size(), 0);
			}
		}
		// иначе выделяем память под эти массивы
		else
		{
			// выделение памяти под массив времени входа, выхода
			m_marked_vertices = std::make_unique<VisitedVert>(m_graph->adjacency_matrix().size(), 0);
			m_tin = std::make_unique<TimeArr>(m_graph->adjacency_matrix().size(), 0);
			m_tout = std::make_unique<TimeArr>(m_graph->adjacency_matrix().size(), 0);
			// выделение памяти и инфнициализация соотнесенного графа
			m_correl_graph = std::make_shared<Graph>(ALGO::CorrelatedGraph(m_graph));
		}

		// основной алгоритм
		{
			// выделение памяти под список мостов
			m_bridges = std::make_unique<EdgeList>(0);

			// текущее время
			Time time = 0;

			// поиск мостов поиском в глубину
			for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
			{
				// если вершина не посещена
				if (!(*m_marked_vertices)[i])
				{
					ALGO::BridgeDFS(m_correl_graph, m_marked_vertices, i, time, m_tin, m_tout, m_bridges);
				}
			}
		}
		return true;
	}
	return false;
}

bool PresetGraphManT3::CalculateDigraphPivots()
{
	// если граф неориентированный
	if (m_graph->is_directed())
	{
		INFO("расчет шарниров в орграфе");

		// если мы считали мосты, тогда надо обнулить 
		// масив времени входа, выхода, маркированных вершин
		IF_ST_CALC(SPEC::DIGRAPH_BRIDGES)
		{
			// обнуление значний
			for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
			{
				m_marked_vertices->assign(m_graph->adjacency_matrix().size(), 0);
				m_tin->assign(m_graph->adjacency_matrix().size(), 0);
				m_tout->assign(m_graph->adjacency_matrix().size(), 0);
			}
		}
		// иначе выделяем память под эти массивы
		else
		{
			// выделение памяти под массив времени входа, выхода
			m_marked_vertices = std::make_unique<VisitedVert>(m_graph->adjacency_matrix().size(), 0);
			m_tin = std::make_unique<TimeArr>(m_graph->adjacency_matrix().size(), 0);
			m_tout = std::make_unique<TimeArr>(m_graph->adjacency_matrix().size(), 0);
			// выделение памяти и инфнициализация соотнесенного графа
			m_correl_graph = std::make_shared<Graph>(ALGO::CorrelatedGraph(m_graph));
		}

		// основной агоритм
		{
			// выделение памяти под массив шарниров
			m_pivots = std::make_unique<PivotArr>(m_graph->adjacency_matrix().size(), 0);

			// текущее время
			Time time = 0;

			// поиск шарниров поиском в глубину
			for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
			{
				// если вершина не посещена
				if (!(*m_marked_vertices)[i])
				{
					ALGO::PivotDFS(m_correl_graph, m_marked_vertices, i, time, m_tin, m_tout, m_pivots);
				}
			}
		}
		return true;
	}
	return false;
}

const U_PTR(EdgeList)& PresetGraphManT3::GetBridges() const
{
	return m_bridges;
}

const U_PTR(PivotArr)& PresetGraphManT3::GetPivots() const
{
	return m_pivots;
}
