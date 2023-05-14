#include "pch.h"
#include "Graph.h"

Graph::Graph(std::string _filepath, INPUT_FILE_TYPE _in_f_type)
{
	INFO("конструктор по умолчанию");
	ReadGraphFromFile(_filepath, _in_f_type);
}

Graph::Graph(const Graph& _graph)
{
	INFO("конструктор копирования");
	this->m_adjacency_matrix = _graph.adjacency_matrix();
}

Graph::Graph(const VertexMatrix& _v_matr)
{
	INFO("конструктор от матрицы смежности");
	this->m_adjacency_matrix = _v_matr;
}

Graph::Graph(const EdgeList& _e_list)
{
	INFO("конструктор от списка ребер");
	// количество вершин в графе
	int n = 0;
	std::for_each(_e_list.begin(), _e_list.end(), [&](const Edge& _ed)
		{
			n = std::max({ _ed.m_from, _ed.m_to, n });
		}
	);

	// изменение размера матрицы
	this->m_adjacency_matrix.resize(n + 1, VertexArr(n + 1, 0));

	// запись матрицы смежности
	for (auto it = _e_list.begin(); it != _e_list.end(); it++)
	{
		m_adjacency_matrix[it->m_from][it->m_to] = it->m_weight;
	}
	INFO("конец конструктора от списка ребер");
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
				m_adjacency_matrix[row_num][stoi(token) - 1] = 1;
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
	m_adjacency_matrix.resize(size);
	for (auto& vec : m_adjacency_matrix)
		vec.resize(size);

	// считывание самих ребер
	while (_ifstream.peek() != EOF)
	{
		getline(_ifstream, str);

		// TODO исправить кучу GetToken (это костыль)
		// проверка на число
		token1 = GetToken(str, ' ');
		token2 = GetToken(str, ' ');
		token3 = GetToken(str, '\r');
		token3 = GetToken(token3, ' ');
		token3 = token3 == "" ? "1" : token3;
		if (
			!IsItANumber(token1) ||
			!IsItANumber(token2) ||
			!IsItANumber(token3)
			)
		{
			ERROR("Найдены не числа: (" + token1 + ") (" + token2 + ") (" + token3 + ")");
		}

		// если считанные значения - числа
		m_adjacency_matrix[stoi(token1) - 1][stoi(token2) - 1] = stoi(token3);
	}
}

int Graph::weight(Vertex _vi, Vertex _vj) const
{
	if (
		!(_vi >= 0 && _vi < m_adjacency_matrix.size() &&
			_vj >= 0 && _vj < m_adjacency_matrix.size())
		)
	{
		// TODO
		// Лучше добавить Warning, так как здесь нужно, чтобы сообщение было видно и в релизе
		// но не нужно, чтобы программа крашилась, как при Error'e
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

VertexList Graph::adjacency_list(Vertex _v) const
{
	// если такой вершины не существует
	if (_v >= m_adjacency_matrix.size())
		ERROR("Вершины под номером " + std::to_string(_v) + " НЕ существует");

	// выходной список смежных вершин
	// смежными считаются досягаемые из _v вершины
	VertexList out;

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

EdgeList Graph::list_of_edges() const
{
	EdgeList out;

	for (int i = 0; i < m_adjacency_matrix.size(); i++)
	{
		for (int j = 0; j < m_adjacency_matrix.size(); j++)
		{
			if (is_edge(i, j))
			{
				out.push_back({ i,j,weight(i,j) });
			}
		}
	}

	return out;
}

EdgeList Graph::list_of_edges(Vertex _v) const
{
	EdgeList out;

	for (int i = 0; i < m_adjacency_matrix.size(); i++)
	{
		if (is_edge(_v, i))
		{
			out.push_back({ _v,i,weight(_v,i) });
		}
	}

	return out;
}

// ориентирован ли граф
bool Graph::is_directed() const
{
	// проходимся по всем элементам и сравниваем их с 
	// элементами симметричными им относительно главной диагонали
	for (int i = 0; i < m_adjacency_matrix.size(); i++)
	{
		for (int j = 0; j <= i; j++)
		{
			// если m_adj_mtr[i][j] != m_adj_mtr[j][i]
			// значит граф ориентированный
			//INFO(std::to_string(m_adjacency_matrix[i][j]) + " " + std::to_string(m_adjacency_matrix[j][i]));
			if (m_adjacency_matrix[i][j] != m_adjacency_matrix[j][i])return true;
		}
	}
	return false;
}
