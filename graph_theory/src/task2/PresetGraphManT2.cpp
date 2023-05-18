#include "../pch.h"
#include "PresetGraphManT2.h"

PresetGraphManT2::PresetGraphManT2(
	const S_PTR(SystemSetting)& _settings,
	const S_PTR(Graph)& _graph,
	const S_PTR(StateVector) _states
)
// инициализация всех полей
	:BaseGraphPresetManager(_settings, _graph, _states),
	m_numb_of_conn_compon(1),
	m_numb_of_strng_con_comp(1),
	m_is_connected(0),
	m_is_strongly_connected(0)
{};
PresetGraphManT2::~PresetGraphManT2()
{
	// очистка памяти
	m_marked_vertices.reset();
	m_digraph_marked_vertices.reset();
};

//==================================//
//         CALCULATE МЕТОДЫ         //
//==================================//

bool PresetGraphManT2::CalculateIsConnected()
{
	// если раньше не считали связность графа
	// то считаем ее
	IF_ST_NOT_CALC(SPEC::T2_IS_CONNECTED)
	{
		// если не считали компненты связности, считаем их
		IF_ST_SHOULD_BE_CALC(SPEC::T2_CONNECTED_COMPONENTS, CalculateConnectedComponents());
		//IF_ST_NOT_CALC(SPEC::T2_CONNECTED_COMPONENTS)
		//	SetStateOfSpec(SPEC::T2_CONNECTED_COMPONENTS, CalculateConnectedComponents());

		// если посчитать компоненты связности удалось, вычисляем связность
		IF_ST_CALC(SPEC::T2_CONNECTED_COMPONENTS)
		{
			// если всего одна компонента связности, то граф связный
			if (m_numb_of_conn_compon == 1)
			{
				INFO("расчет: граф связен");

				m_is_connected = 1;
				return true;
			}
		}
	}

	return false;
}

bool PresetGraphManT2::CalculateIsNotConnected()
{
	// если не была выполнена функция вычисления связности
	// пытаемся выполнить ее
	IF_ST_SHOULD_BE_CALC(SPEC::T2_IS_CONNECTED, CalculateIsConnected());

	// если она Не выполнилась
	IF_ST_NOT_CALC(SPEC::T2_IS_CONNECTED)
	{
		// если несколько компонент связности, то граф не связный
		if (m_numb_of_conn_compon != 1)
		{
			INFO("расчет: граф не связен");

			m_is_connected = 0;
			return true;
		}
	}

	return false;
}

bool PresetGraphManT2::CalculateConnectedComponents()
{
	IF_ST_NOT_CALC(SPEC::T2_CONNECTED_COMPONENTS)
	{
		// если граф неориентированный
		if (!m_graph->is_directed())
		{
			INFO("расчет: компоненты связности");

			m_numb_of_conn_compon = 1;

			// создаем вектор с посещенными вершинами, 
			// заполняем его нулями
			m_marked_vertices =
				std::make_unique<VertexArr>(m_graph->adjacency_matrix().size(), 0);

			// цикл по всем вершинам
			for (int vert = 0; vert < m_graph->adjacency_matrix().size(); vert++)
			{
				// если вершина не была посещена
				if (!(*m_marked_vertices)[vert])
				{
					ALGO::BFS(m_graph, m_marked_vertices, vert, m_numb_of_conn_compon);
					m_numb_of_conn_compon++;
				}
			}
			if (m_numb_of_conn_compon != 1)--m_numb_of_conn_compon;

			return true;
		}
		INFO("граф ориентированный");
	}

	return false;
}

bool PresetGraphManT2::CalculateIsDigraphConnected()
{
	// если не посчитаны компоненты слабой связности, надо посчитать
	IF_ST_SHOULD_BE_CALC(SPEC::T2_DIGRAPH_WEAKLY_CONNECTED_COMPONENTS, CalculateDWeaklyConnectedComponents());

	// если посчитаны компоненты слабой связности
	IF_ST_CALC(SPEC::T2_DIGRAPH_WEAKLY_CONNECTED_COMPONENTS)
	{
		// если количество компонент слабой связности равно одной,
		// то диграф связен
		if (m_numb_of_conn_compon == 1)
		{
			INFO("расчет: диграф связен");

			m_is_connected = 1;
			return true;
		}
	}

	return false;
}

bool PresetGraphManT2::CalculateIsDigraphNotConnected()
{
	// если не посчитаны компоненты слабой связности, надо посчитать
	IF_ST_SHOULD_BE_CALC(SPEC::T2_DIGRAPH_WEAKLY_CONNECTED_COMPONENTS, CalculateDWeaklyConnectedComponents());

	// если посчитаны компоненты слабой связности
	IF_ST_CALC(SPEC::T2_DIGRAPH_WEAKLY_CONNECTED_COMPONENTS)
	{
		// если количество компонент слабой связности больше одной,
		// то диграф не связен
		if (m_numb_of_conn_compon > 1)
		{
			INFO("расчет: диграф не связен");

			m_is_connected = 0;
			return true;
		}
	}

	return false;
}

bool PresetGraphManT2::CalculateIsDigraphWeaklyConnected()
{
	// посчитать компоненты сильной связности, если они еще не посчитаны
	IF_ST_SHOULD_BE_CALC(SPEC::T2_DIGRAPH_STRONGLY_CONNECTED_COMPONENTS, CalculateDStronglyConnectedComponents());

	// если удалось посчитать компоненты сильной связности
	IF_ST_CALC(SPEC::T2_DIGRAPH_STRONGLY_CONNECTED_COMPONENTS)
	{
		// если компонент сильной связности больше одной,
		// значит диграф слабо связен
		if (m_numb_of_strng_con_comp > 1)
		{
			INFO("расчет: диграф слабо связен");

			m_is_strongly_connected = 0;
			return true;
		}
	}

	return false;
}

bool PresetGraphManT2::CalculateIsDigraphStronglyConnected()
{
	// посчитать компоненты сильной связности, если они еще не посчитаны
	IF_ST_SHOULD_BE_CALC(SPEC::T2_DIGRAPH_STRONGLY_CONNECTED_COMPONENTS, CalculateDStronglyConnectedComponents());

	// если удалось посчитать компоненты сильной связности
	IF_ST_CALC(SPEC::T2_DIGRAPH_STRONGLY_CONNECTED_COMPONENTS)
	{
		// если компонент сильной связности больше одной,
		// значит диграф слабо связен
		if (m_numb_of_strng_con_comp == 1)
		{
			INFO("расчет: диграф сильно связен");

			m_is_strongly_connected = 1;
			return true;
		}
	}

	return false;
}

bool PresetGraphManT2::CalculateDStronglyConnectedComponents()
{
	// если еще не считали компоненты сильной связности орграфа,
	// то считаем их
	IF_ST_NOT_CALC(SPEC::T2_DIGRAPH_STRONGLY_CONNECTED_COMPONENTS)
	{
		// если граф ориентированный
		if (m_graph->is_directed())
		{
			INFO("расчет: компоненты сильной связности");

			// если граф ориентированный, инвертируем его,
			// обнуляем массив посещенный вершин, производим топологическую соритровку
			// выполняем DFS для всех вершин обычного графа 
			// в порядке топологической сортировки инвертированного графа

			// инвертируем граф
			EdgeList edge_list = m_graph->list_of_edges();
			std::for_each(edge_list.begin(), edge_list.end(), [](Edge& _edge)
				{
					std::swap(_edge.m_from, _edge.m_to);
				}
			);

			// обнуляем массив посещенных вершин
			m_digraph_marked_vertices = std::make_unique<VertexArr>(
				m_graph->adjacency_matrix().size(), 0
			);

			// инвертированный граф
			Graph inverted_graph(edge_list);

			// топологическая сортировка инвертированного графа
			// (сортировка вершин по времени выхода)
			VertexList order = ALGO::TopologicalSort(std::make_shared<Graph>(inverted_graph));

			m_numb_of_strng_con_comp = 1;

			// цикл DFS по непосещенным вершинам обычного графа в порядке order
			for (auto& el : order)
			{
				if (!(*m_digraph_marked_vertices)[el])
				{
					ALGO::DFS(m_graph, m_digraph_marked_vertices, el, m_numb_of_strng_con_comp);
					m_numb_of_strng_con_comp++;
				}
			}
			if (m_numb_of_strng_con_comp != 1)--m_numb_of_strng_con_comp;
			return true;
		}
	}
	return false;
}

bool PresetGraphManT2::CalculateDWeaklyConnectedComponents()
{
	// если еще не считали компоненты слабой связности орграфа,
	// то считаем их
	IF_ST_NOT_CALC(SPEC::T2_DIGRAPH_WEAKLY_CONNECTED_COMPONENTS)
	{
		INFO("расчет: компоненты слабой связности");

		// если граф ориентированный, ищем соотнесенный граф
		// проводим BFS по всем его вершинам
		if (m_graph->is_directed())
		{
			m_numb_of_conn_compon = 1;

			// выделение памяти под массив маркированных вершин
			m_marked_vertices =
				std::make_unique<VertexArr>(m_graph->adjacency_matrix().size(), 0);

			// создание соотнесенного графа
			m_correl_graph = std::make_shared<Graph>(ALGO::CorrelatedGraph(m_graph));

			// цикл по всем вершинам
			for (int vert = 0; vert < m_graph->adjacency_matrix().size(); vert++)
			{
				// если вершина не была посещена
				if (!(*m_marked_vertices)[vert])
				{
					ALGO::BFS(m_correl_graph, m_marked_vertices, vert, m_numb_of_conn_compon);
					m_numb_of_conn_compon++;
				}
			}
			if (m_numb_of_conn_compon != 1)--m_numb_of_conn_compon;
			return true;
		}
		INFO("граф неориентированный");
	}
	return false;
}

//==================================//
//            GET МЕТОДЫ            //
//==================================//

const int& PresetGraphManT2::GetNumberOfConnectedComponents() const
{
	return m_numb_of_conn_compon;
}

const U_PTR(VertexArr)& PresetGraphManT2::GetConnectedComponents() const
{
	return m_marked_vertices;
}

const bool& PresetGraphManT2::GetIsGraphConnected() const
{
	return m_is_connected;
}

const U_PTR(VertexArr)& PresetGraphManT2::GetStronglyConnectedComponents() const
{
	return m_digraph_marked_vertices;
}

const int& PresetGraphManT2::GetNumberOfStronglyConnectedComponents() const
{
	return m_numb_of_strng_con_comp;
}

const bool& PresetGraphManT2::GetIsDigraphStronglyConnected()
{
	return m_is_strongly_connected;
}

