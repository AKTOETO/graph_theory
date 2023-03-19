#include "Graph.h"

Graph::Graph(std::string _filepath, INPUT_FILE_TYPE _in_f_type)
{
	INFO("создание графа");

	std::ifstream fin(FILE_PATH + _filepath);

	// Если файл не был открыт
	if (!fin)
	{
		ERROR("файл " + FILE_PATH + _filepath + " не был открыт!");
	}

	// игнорирование пробелов
	fin >> std::ws;

	// если же файл был открыт, 
	// определяем тип функции чтения из файла
	switch (_in_f_type)
	{
	case INPUT_FILE_TYPE::EDGES_LIST:
		ReadEdgesListFromFile(fin);
		break;

	case INPUT_FILE_TYPE::ADJACENCY_MATRIX:
		ReadAdjacencyMatrixFromFile(fin);
		break;

	case INPUT_FILE_TYPE::ADJACENCY_LIST:
		ReadAdjacencyListFromFile(fin);
		break;

	default:
		ERROR("неизвестный тип файла");
		break;
	}
}

Graph::~Graph()
{
	INFO("уничтожение графа");
}

void Graph::PrintAdjacencyMatrix() const
{
	INFO("Печать матрицы смежности графа");

	for (int i = 0; i < m_adjacency_matrix.size(); i++)
	{
		for (int j = 0; j < m_adjacency_matrix[i].size(); j++)
		{
			std::cout << m_adjacency_matrix[i][j] << " ";
		}
		std::cout << '\n';
	}
}

void Graph::ReadAdjacencyListFromFile(std::ifstream& _ifstream)
{
	// хехе >_<
}

void Graph::ReadAdjacencyMatrixFromFile(std::ifstream& _ifstream)
{
	// строка файла
	VertexArr row;

	// пока не конец файла
	do
	{
		// считывание всей строки из файла
		std::string str;
		getline(_ifstream, str);
		if (str.length() != 0)
		{
			// пока строка не пустая, выписываем из нее числа
			while (str.size() != 0)
			{
				// получение токена, отделенного пробелом
				std::string token = SupportFunctions::GetToken(str, ' ');

				// если есть что-то помимо цифр
				if (token.find_first_not_of("0123456789") != std::string::npos)
				{
					ERROR("в исходном файле на "
						+ std::to_string(m_adjacency_matrix.size() + 1)
						+ " строке найдено (" + token + ")");
				}
				// иначе сохраняем число
				else if (token != "")
				{
					row.push_back(std::stoi(token));
				}
			}

			// запись строки в матрицу
			m_adjacency_matrix.push_back(row);
			row.clear();

			// проверка на одну длину строк матрицы
			if (m_adjacency_matrix.size() > 1
				&& m_adjacency_matrix[m_adjacency_matrix.size() - 1].size() !=
				m_adjacency_matrix[m_adjacency_matrix.size() - 2].size())
			{
				ERROR("в исходном файле длина "
					+ std::to_string(m_adjacency_matrix.size())
					+ " строки = "
					+ std::to_string(m_adjacency_matrix[m_adjacency_matrix.size() - 1].size())
					+ " отличается от длин других строк"
				);
			}
		}
	} while (!_ifstream.eof());

	// проверка на квадратность матрицы
	if (m_adjacency_matrix.size() !=
		m_adjacency_matrix[m_adjacency_matrix.size() - 1].size())
	{
		ERROR("Количество столбцов не совпадает с количеством строк");
	}

	INFO("Матрица смежности успешно считана!");
}

void Graph::ReadEdgesListFromFile(std::ifstream& _ifstream)
{

}

int Graph::weight(Vertex _vi, Vertex _vj) const
{
	return 0;
}

bool Graph::is_edge(Vertex _vi, Vertex _vj) const
{
	return false;
}

const VertexMatrix& Graph::adjacency_matrix() const
{
	return m_adjacency_matrix;
}

VertexArr Graph::adjacency_list(Vertex _v) const
{
	return VertexArr();
}

EdgeArr Graph::list_of_edges() const
{
	return EdgeArr();
}

EdgeArr Graph::list_of_edges(Vertex _v) const
{
	return EdgeArr();
}

bool Graph::is_directed() const
{
	return false;
}
