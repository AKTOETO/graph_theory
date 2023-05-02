#include "../pch.h"
#include "GraphManagerT1.h"

GraphManagerT1::GraphManagerT1(std::string _filepath, INPUT_FILE_TYPE _in_f_type)
// инициализация всех полей
	:BaseGraphManager(_filepath, _in_f_type),
	m_shortest_distance_matr(nullptr),
	m_eccentricity(nullptr),
	m_central_vertices(nullptr),
	m_peripheral_vertices(nullptr),
	m_radius(nullptr),
	m_diameter(nullptr),
	m_degrees_in(nullptr),
	m_degrees_out(nullptr),
	m_degrees_in_out(nullptr)
{
	m_specs =
	{
		{SPEC::SHORTEST_DIST_MATR,	&GraphManagerT1::CalculateShortestDistMatr},
		{SPEC::ECCENTR,				&GraphManagerT1::CalculateEccentricity},
		{SPEC::CENTRAL_VERT,		&GraphManagerT1::CalculateCentralVertices},
		{SPEC::PERIPHERAL_VERT,		&GraphManagerT1::CalculatePeripheralVertices},
		{SPEC::RADIUS,				&GraphManagerT1::CalculateRadius},
		{SPEC::DIAMETER,			&GraphManagerT1::CalculateDiameter},
		{SPEC::DEGREES_IN,			&GraphManagerT1::CalculateVertexDegreesIn},
		{SPEC::DEGREES_OUT,			&GraphManagerT1::CalculateVertexDegreesOut},
		{SPEC::DEGREES_IN_OUT,		&GraphManagerT1::CalculateVertexDegreesInOut},
	};
};
GraphManagerT1::~GraphManagerT1()
{
	// очистка памяти
	m_shortest_distance_matr.reset();
	m_eccentricity.reset();
	m_central_vertices.reset();
	m_peripheral_vertices.reset();
	m_radius.reset();
	m_diameter.reset();
	m_degrees_in.reset();
	m_degrees_out.reset();
	m_degrees_in_out.reset();
};

//==================================//
//         CALCULATE МЕТОДЫ         //
//==================================//

#define IF_CALC(_spec) if((*m_state_of_spec)[int(_spec)])
#define IF_NOT_CALC(_spec) if(!(*m_state_of_spec)[int(_spec)])

bool GraphManagerT1::CalculateVertexDegreesIn()
{
	// если граф направленный, расчитываем степень входа
	if (m_graph->is_directed())
	{
		INFO("расчет степеней входа");

		// выделение памяти под массив степеней вершин входа
		m_degrees_in = std::make_unique<VertexArr>(m_graph->adjacency_matrix().size(), 0);

		// расчет степеней вершин входа
		for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
		{
			for (int j = 0; j < m_graph->adjacency_matrix().size(); j++)
			{
				if (m_graph->is_edge(j, i)) (*m_degrees_in)[i]++;
			}
		}
		return true;
	}
	return false;
}

bool GraphManagerT1::CalculateVertexDegreesOut()
{
	// если граф направленный, расчитываем степень выхода
	if (m_graph->is_directed())
	{
		INFO("расчет степеней выхода");

		// выделение памяти под массив степеней вершин входа
		m_degrees_out = std::make_unique<VertexArr>(m_graph->adjacency_matrix().size(), 0);

		// расчет степеней вершин входа
		for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
		{
			for (int j = 0; j < m_graph->adjacency_matrix().size(); j++)
			{
				if (m_graph->is_edge(i, j)) (*m_degrees_out)[i]++;
			}
		}
		return true;
	}
	return false;
}

bool GraphManagerT1::CalculateVertexDegreesInOut()
{
	// если граф не направленный, расчитываем степень входа и выхода
	if (!m_graph->is_directed())
	{
		INFO("расчет степеней входа и выхода");

		// выделение памяти под массив степеней вершин входа
		m_degrees_in_out = std::make_unique<VertexArr>(m_graph->adjacency_matrix().size(), 0);

		// расчет степеней вершин входа
		for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
		{
			for (int j = 0; j < m_graph->adjacency_matrix().size(); j++)
			{
				if (m_graph->is_edge(i, j) || m_graph->is_edge(j, i)) (*m_degrees_in_out)[i]++;
			}
		}
		return true;
	}
	return false;
}

/// <summary>
/// Расчет матрицы кратчайших расстояний
/// </summary>
/// <returns>матрица кратчайших расстояний</returns>
bool GraphManagerT1::CalculateShortestDistMatr()
{
	INFO("расчет кратчайших расстояний");
	// выделение памяти под матрицу кратчайших расстояний 
	// и установка размера матрицы
	m_shortest_distance_matr =
		std::make_unique<VertexMatrix>(m_graph->adjacency_matrix().size());

	for (auto& el : *m_shortest_distance_matr)
		el.resize(m_graph->adjacency_matrix().size());

	// копирование значений матрицы смежности в матрицу расстояний
	for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
	{
		for (int j = 0; j < m_graph->adjacency_matrix().size(); j++)
		{
			// если это не элемент главной диагонали
			if (i != j)
			{
				// если ребра нет, пишем на его месте бесконечность ,
				// иначе саму длину ребра
				(*m_shortest_distance_matr)[i][j] =
					m_graph->adjacency_matrix()[i][j] != 0 ? m_graph->adjacency_matrix()[i][j] : INF;
			}
			else
			{
				// пишем 0 на главной диагонали
				(*m_shortest_distance_matr)[i][j] = 0;
			}
		}
	}

	// алгоритм Флойда-Уоршелла получения матрицы кратчайших расстояний
	for (int k = 0; k < m_shortest_distance_matr->size(); ++k)
	{
		for (int i = 0; i < m_shortest_distance_matr->size(); ++i)
		{
			for (int j = 0; j < m_shortest_distance_matr->size(); ++j)
			{
				// если дистанция ikj короче, чем ij, то запоминаем эту дистанцию
				if (
					(*m_shortest_distance_matr)[i][j] >
					(*m_shortest_distance_matr)[i][k] + (*m_shortest_distance_matr)[k][j]
					)
					(*m_shortest_distance_matr)[i][j] = (*m_shortest_distance_matr)[i][k] + (*m_shortest_distance_matr)[k][j];
			}
		}
	}

	return true;
};

/// <summary>
/// Расчет эксцентриcитета графа
/// </summary>
/// <returns>массив с эксцентриситетом для каждой вершины</returns>
bool GraphManagerT1::CalculateEccentricity()
{
	// если не расчитана матрица кратч. расст., расчитываем ее
	IF_NOT_CALC(SPEC::SHORTEST_DIST_MATR) CalculateShortestDistMatr();

	// если в матрице критчайших расстояний нет бесконечностей, 
	// расчитываем эксцентриситеты
	if (!IsThereElementInMatrix(*m_shortest_distance_matr, INF))
	{
		INFO("расчет эксцентриситета");

		// выделение памяти под массив эксцентриситетов
		m_eccentricity = std::make_unique<VertexArr>(0);

		// вычисление эксцентриситета
		for (auto& el : *m_shortest_distance_matr)
		{
			m_eccentricity->push_back(*std::max_element(el.begin(), el.end()));
		}
		return true;
	}
	return false;
};

/// <summary>
/// Расчет диаметра графа
/// </summary>
/// <returns>диаметр графа</returns>
bool GraphManagerT1::CalculateDiameter()
{
	IF_NOT_CALC(SPEC::ECCENTR) CalculateEccentricity();

	// если эксцентриситеты были расчитаны и граф неориентированный,
	// считаем диаметр
	IF_CALC(SPEC::ECCENTR)
		if (!m_graph->is_directed())
		{
			INFO("расчет диаметра");

			// выделение памяти и запись максимального эксцентриситета
			m_diameter = std::make_unique<int>(
				*std::max_element(m_eccentricity->begin(), m_eccentricity->end())
			);
			return true;
		}

	return false;
};

/// <summary>
/// Расчет радиуса гарфа
/// </summary>
/// <returns>радиус гарфа</returns>
bool GraphManagerT1::CalculateRadius()
{
	IF_NOT_CALC(SPEC::ECCENTR) CalculateEccentricity();

	// если эксцентриситеты были расчитаны и граф неориентированный,
	// считаем радиус
	IF_CALC(SPEC::ECCENTR)
		if (!m_graph->is_directed())
		{
			INFO("расчет радиуса");
			// выделение памяти и запись максимального эксцентриситета
			m_radius = std::make_unique<int>(
				*std::min_element(m_eccentricity->begin(), m_eccentricity->end())
			);
			return true;
		}
	return false;
};

/// <summary>
/// Расчет центральных вершин
/// </summary>
/// <returns>центральные вершины</returns>
bool GraphManagerT1::CalculateCentralVertices()
{
	IF_NOT_CALC(SPEC::ECCENTR) CalculateEccentricity();
	IF_NOT_CALC(SPEC::RADIUS) CalculateRadius();

	// если посчитан эксцентриситет и радиус и граф неориентированный,
	// тогда считаем центральные вершины
	IF_CALC(SPEC::ECCENTR)
		IF_CALC(SPEC::RADIUS)
		if (!m_graph->is_directed())
		{
			INFO("расчет центральных вершин");
			m_central_vertices = std::make_unique<VertexArr>();

			// если эксцентриситет вершины минимален (равен радиусу графа),
			// то она центральная
			for (int i = 0; i < m_eccentricity->size(); i++)
			{
				if ((*m_eccentricity)[i] == *m_radius)
				{
					m_central_vertices->push_back(i + 1);
				}
			}
			return true;
		}
	return false;
};

/// <summary>
/// Расчет периферийных вершин
/// </summary>
/// <returns>периферийные вершины</returns>
bool GraphManagerT1::CalculatePeripheralVertices()
{
	IF_NOT_CALC(SPEC::ECCENTR) CalculateEccentricity();
	IF_NOT_CALC(SPEC::DIAMETER) CalculateRadius();
	// если посчитан эксцентриситет и диаметр и граф неориентированный,
	// тогда считаем периферийные вершины
	IF_CALC(SPEC::ECCENTR)
		IF_CALC(SPEC::DIAMETER)
		if (!m_graph->is_directed())
		{
			INFO("расчет периферийных вершин");
			m_peripheral_vertices = std::make_unique<VertexArr>();

			// если эксцентриситет вершины максимален (равен диаметру графа),
			// то она периферийная
			for (int i = 0; i < m_eccentricity->size(); i++)
			{
				if ((*m_eccentricity)[i] == *m_diameter)
				{
					m_peripheral_vertices->push_back(i + 1);
				}
			}
			return true;
		}

	return false;
}

//==================================//
//            GET МЕТОДЫ            //
//==================================//

const U_PTR(VertexArr)& GraphManagerT1::GetVertexDegreesIn() const
{
	return m_degrees_in;
}
const U_PTR(VertexArr)& GraphManagerT1::GetVertexDegreesOut() const
{
	return m_degrees_out;
}
const U_PTR(VertexArr)& GraphManagerT1::GetVertexDegreesInOut() const
{
	return m_degrees_in_out;
}

/// <summary>
/// Получение матрицы кратчайших расстояний
/// </summary>
/// <returns>матрица кратчайших расстояний</returns>
const U_PTR(VertexMatrix)& GraphManagerT1::GetShortestDistMatr() const
{
	return m_shortest_distance_matr;
};

/// <summary>
/// получение эксцентриcитета графа
/// </summary>
/// <returns>массив с эксцентриситетом для каждой вершины</returns>
const U_PTR(VertexArr)& GraphManagerT1::GetEccentricity() const
{
	return m_eccentricity;
};

/// <summary>
/// Получение диаметра графа
/// </summary>
/// <returns>диаметр графа</returns>
const U_PTR(int)& GraphManagerT1::GetDiameter() const
{
	return m_diameter;
};

/// <summary>
/// Получение радиуса гарфа
/// </summary>
/// <returns>радиус гарфа</returns>
const U_PTR(int)& GraphManagerT1::GetRadius() const
{
	return m_radius;
};

/// <summary>
/// Получение центральных вершин
/// </summary>
/// <returns>центральные вершины</returns>
const U_PTR(VertexArr)& GraphManagerT1::GetCentralVertices() const
{
	return m_central_vertices;
};

/// <summary>
/// Получение периферийных вершин
/// </summary>
/// <returns>периферийные вершины</returns>
const U_PTR(VertexArr)& GraphManagerT1::GetPeripheralVertices() const
{
	return m_peripheral_vertices;
}
 

#undef IF_CALC
#undef IF_NOT_CALC
