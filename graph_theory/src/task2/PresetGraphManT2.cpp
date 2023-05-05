#include "../pch.h"
#include "PresetGraphManT2.h"

PresetGraphManT2::PresetGraphManT2(const S_PTR(Graph)& _graph, const S_PTR(std::vector<bool>) _states)
// инициализация всех полей
	:BaseGraphManager(_graph, _states),
	m_numb_of_conn_compon(1)
{};
PresetGraphManT2::~PresetGraphManT2()
{
	// очистка памяти

};

//==================================//
//         CALCULATE МЕТОДЫ         //
//==================================//

//#define IF_ST_CALC(_spec) if((*m_state_of_spec)[int(_spec)])
//#define IF_ST_NOT_CALC(_spec) if(!(*m_state_of_spec)[int(_spec)])

bool PresetGraphManT2::CalculateIsConnected()
{

	return false;
}

bool PresetGraphManT2::CalculateIsNotConnected()
{
	return false;
}

bool PresetGraphManT2::CalculateConnectedComponents()
{
	IF_ST_NOT_CALC(SPEC::CONNECTED_COMPONENTS)
	{
		// если грав неориентированный
		if (!m_graph->is_directed())
		{
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

			return true;
		}
	}

	return false;
}

bool PresetGraphManT2::CalculateIsDigraphConnected()
{
	return false;
}

bool PresetGraphManT2::CalculateIsDigraphNotConnected()
{
	return false;
}

bool PresetGraphManT2::CalculateIsDigraphWeaklyConnected()
{
	return false;
}

bool PresetGraphManT2::CalculateIsDigraphStronglyConnected()
{
	return false;
}

bool PresetGraphManT2::CalculateStronglyConnectedComponents()
{
	return false;
}

//==================================//
//            GET МЕТОДЫ            //
//==================================//

const int& PresetGraphManT2::GetNumbOfConnComp() const
{
	return m_numb_of_conn_compon;
}

