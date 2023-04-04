#include "Graph.h"

Graph::Graph()
{
	INFO("создание графа");
}

Graph::~Graph()
{
	INFO("уничтожение графа");
}

void Graph::ReadGraphFromFile(std::string _filepath, INPUT_FILE_TYPE _in_f_type)
{
	std::ifstream fin(GRAPH_FILE_PATH + _filepath, std::ifstream::binary);

	// Если файл не был открыт
	if (!fin)
	{
		ERROR("файл " + GRAPH_FILE_PATH + _filepath + " не был открыт!");
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
	// количество строк
	int numb_of_rows = 0;

	// получение количества строк
	while (_ifstream.peek() != EOF)
	{
		_ifstream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		numb_of_rows++;
	}

	// перемещение курсора в начало файла
	_ifstream.clear();
	_ifstream.seekg(0, std::ios::beg);

	// установка нужного размера матрицы
	m_adjacency_matrix.resize(numb_of_rows);
	for (auto& vec : m_adjacency_matrix)
		vec.resize(numb_of_rows);

	// строка файла
	std::string str;

	// токен строки
	std::string token;

	// номер строки и столбца
	int row_num = 0;

	// считывание данных
	while (_ifstream.peek() != EOF)
	{
		getline(_ifstream, str);

		// поиск и удаление символа переноса каретки в начало
		FindAndDeleteChar(str);

		// пока строка не пустая, выписываем из нее числа
		while (str.size() != 0)
		{
			// получение токена, отделенного пробелом
			token = GetToken(str, ' ');

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
				m_adjacency_matrix[row_num][stoi(token)] = 1;
			}
		}

		// переход на следующую строку
		row_num++;
	}
}

void Graph::ReadAdjacencyMatrixFromFile(std::ifstream& _ifstream)
{
	// строка файла
	VertexArr row;
	std::string token;

	// пока не конец файла
	do
	{
		// считывание всей строки из файла
		std::string str;
		getline(_ifstream, str);

		// поиск и удаление символа переноса каретки в начало
		FindAndDeleteChar(str);

		if (str.length() != 0)
		{
			// пока строка не пустая, выписываем из нее числа
			while (str.size() != 0)
			{
				// получение токена, отделенного пробелом
				token = GetToken(str, ' ');

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
	// размер матрицы
	int size = 0;

	// временные переменные
	std::string str;
	std::string token1, token2, token3;

	// узнаем размер матрицы смежности 
	while (_ifstream.peek() != EOF)
	{
		getline(_ifstream, str);

		// проверка на число
		token1 = GetToken(str, ' ');
		token2 = GetToken(str, ' ');
		if (!IsItANumber(token1) || !IsItANumber(token2))
		{
			ERROR("Найдены не числа");
		}

		size = std::max(size, std::max(stoi(token1), stoi(token2)));
	}

	// перемещение курсора в начало файла
	_ifstream.clear();
	_ifstream.seekg(0, std::ios::beg);

	// установка нужного размера матрицы
	m_adjacency_matrix.resize(size + 1);
	for (auto& vec : m_adjacency_matrix)
		vec.resize(size + 1);

	// считывание самих ребер
	while (_ifstream.peek() != EOF)
	{
		getline(_ifstream, str);

		// проверка на число
		token1 = GetToken(str, ' ');
		token2 = GetToken(str, ' ');
		token3 = GetToken(str, '\r');
		if (
			!IsItANumber(token1) ||
			!IsItANumber(token2) ||
			!IsItANumber(token3)
			)
		{
			ERROR("Найдены не числа: (" + token1 + ") (" + token2 + ") (" + token3 + ")");
		}

		// если считанные значения - числа
		m_adjacency_matrix[stoi(token1)][stoi(token2)] = stoi(token3);
	}
}

int Graph::weight(Vertex _vi, Vertex _vj) const
{
	if (
		!(_vi >= 0 && _vi < m_adjacency_matrix.size() &&
			_vj >= 0 && _vj < m_adjacency_matrix.size())
		)
	{
		ERROR("Номера вершин " + std::to_string(_vi) + " " + std::to_string(_vj) +
			" неверны. Размер матрицы смежности: " +
			std::to_string(m_adjacency_matrix.size()) +
			"x" + std::to_string(m_adjacency_matrix.size()));
	}
	return m_adjacency_matrix[_vi][_vj];
}

bool Graph::is_edge(Vertex _vi, Vertex _vj) const
{
	return weight(_vi, _vj) != 0;
}

const VertexMatrix& Graph::adjacency_matrix() const
{
	return m_adjacency_matrix;
}

VertexArr Graph::adjacency_list(Vertex _v) const
{
	// выходной список смежных вершин
	// смежными считаются досягаемые из _v вершины
	VertexArr out;

	// проходимся по всем верщинам
	for (int i = 0; i < m_adjacency_matrix.size(); i++)
	{
		if (i != _v && m_adjacency_matrix[_v][i] != 0)
		{
			out.push_back(i);
		}
	}

	return out;
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
