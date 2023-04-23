#include "CommandManager.h"

void CommandManager::PrintGraphInfo()
{
	if (m_graph.is_directed())
	{
		auto vr = m_graph.GetVertexDegrees(VERTEXES_DEGREESES::IN);
		std::cout << "deg+ = [";
		PrintVector(vr, ", ");
		std::cout << "]\n";

		// степень выхода
		vr = m_graph.GetVertexDegrees(VERTEXES_DEGREESES::OUT);
		std::cout << "deg- = [";
		PrintVector(vr, ", ");
		std::cout << "]\n";
	}
	else
	{
		auto vr = m_graph.GetVertexDegrees(VERTEXES_DEGREESES::IN_OUT);
		std::cout << "deg = [";
		PrintVector(vr, ", ");
		std::cout << "]\n";
	}

	// печать матрицы кратч. расст.
	INFO("печать матрицы кратчайших расстояний");

	std::cout << "Distancies:\n";
	auto mat = m_graph.GetShortestDistMatr();
	int print_width = CountDigitInMatrix(mat);
	INFO(std::to_string(print_width));
	for (auto& el : mat)
	{
		std::cout << "[";
		PrintVector(el, " ", print_width);
		std::cout << "]\n";
	}

	if (!IsThereElementInMatrix(mat, INF))
	{
		// Печать массива эксцентриситетов
		INFO("Печать массива эксцентриситетов");
		auto ecc = m_graph.GetEccentricity();
		std::cout << "Eccentricity: [";
		PrintVector(ecc, ", ");
		std::cout << "]\n";

		if (!m_graph.is_directed())
		{
			// диаметр
			std::cout << "D = " << m_graph.GetDiameter() << std::endl;

			// радиус
			std::cout << "R = " << m_graph.GetRadius() << std::endl;

			// центральные вершины
			std::cout << "Z = [";
			PrintVector(m_graph.GetCentralVertices(), ", ");
			std::cout << "]\n";

			// периферийные вершины
			std::cout << "P = [";
			PrintVector(m_graph.GetPeripheralVertices(), ", ");
			std::cout << "]\n";
		}
	}
}

CommandManager::CommandManager(int argc, char* _keys[])
{
	// задание возможных ключей и функций их обработки
	m_commands =
	{
		{"-e", &CommandManager::ReadEdgesList},
		{"-m", &CommandManager::ReadAdjacencyMatrix},
		{"-l", &CommandManager::ReadAdjacencyList},
		{"-o", &CommandManager::SetOutputFilepath},
		{"-h", &CommandManager::GetDeveloperData},
	};

	// конвертация char* _keys[] в vector<string>
	ConverCharArrayToStrVec(argc, _keys);

	// печать ключей с параметрами
	PrintParams();

	// обработка ключей
	CheckKeys();
}

CommandManager::~CommandManager()
{
	m_fout.close();
}

void CommandManager::Run()
{
	// пока введенные ключи с параметрами еще есть
	while (m_param.size() != 0)
	{
		// итератор на конец команды (ключ + параметры)
		auto it_end = std::find_if(m_param.begin() + 1, m_param.end(), [](std::string el)
			{
				return el[0] == '-';
			}
		);

		// вызов функции
		(this->*m_commands[m_param[0]])(GetStringFromVector(m_param.begin() + 1, it_end));

		// удаление первого ключа с его параметрами		
		m_param.erase(m_param.begin(), it_end);
	}
}

void CommandManager::PrintParams() const
{
	INFO("ключи с параметрами: " +
		GetStringFromVector(m_param.begin(), m_param.end(), "\"", " ")
	);
}

void CommandManager::CheckKeys()
{
	// проверка на отсутвтвие ключей
	if (m_param.size() == 0) ERROR("Отсутствие ключей");

	// проверка на наличие известных ключей
	if (!IsThereAExistsKey()) ERROR("Неизвестные ключи");

	// проверка на наличие ключа h
	if (IsThereAKey("-h"))
	{
		m_param.resize(1);
		m_param[0] = "-h";
	}
	else
	{
		// проверка на наличие ключа o
		if (IsThereAKey("-o"))
		{
			// вставка в начало команды этого ключа
			auto it_beg = std::find(m_param.begin(), m_param.end(), "-o");

			// итератор на конец команды (ключ + параметры)
			auto it_end = std::find_if(it_beg + 1, m_param.end(), [](std::string el)
				{
					return el[0] == '-';
				}
			);

			// вырезаем параметры и вставляем в начало
			m_param.insert(m_param.begin(), it_beg, it_end);
		}


		// проверка на введение одновременно ключей e m l
		if (!IsCorrectNumberOfEML()) ERROR("Неверное количество ключей -e -m -l");
	}
}

bool CommandManager::IsThereAExistsKey()
{
	for (const std::string& el : m_param)
	{
		for (const auto& cmd : m_commands)
		{
			if (el == cmd.first)
				return true;
		}
	}
	return false;
}

bool CommandManager::IsCorrectNumberOfEML()
{
	// map для подсчета количества ключей eml
	std::unordered_map<std::string, int> _eml =
	{
		{"-e", 0},
		{"-m", 0},
		{"-l", 0},
	};

	// подсчет количества eml в m_param
	std::for_each(m_param.begin(), m_param.end(), [&_eml](std::string& el)
		{
			if (_eml.find(el) != _eml.end())
				_eml.at(el)++;
		}
	);

	// если количество eml таково:
	// e m l
	// 1 0 0
	// 0 1 0
	// 0 0 1
	// то все корректно
	if (
		_eml.at("-e") == 1 && _eml.at("-m") == 0 && _eml.at("-l") == 0 ||
		_eml.at("-e") == 0 && _eml.at("-m") == 1 && _eml.at("-l") == 0 ||
		_eml.at("-e") == 0 && _eml.at("-m") == 0 && _eml.at("-l") == 1
		) return true;
	return false;
}

bool CommandManager::IsThereAKey(const std::string& _key)
{
	for (std::string& el : m_param)
	{
		if (el == _key) return true;
	}
	return false;
}

void CommandManager::ConverCharArrayToStrVec(int argc, char* _keys[])
{
	// задание размера вектора
	m_param.resize(size_t(argc) - 1);

	// копирование всех ключей вектор
	for (int i = 0; i < argc - 1; i++)
	{
		m_param[i] = std::string(_keys[i + 1]);
	}
}

void CommandManager::ReadEdgesList(std::string _context)
{
	// вызов функции считывания графа 
	m_graph.ReadGraphFromFile(_context, INPUT_FILE_TYPE::EDGES_LIST);

	// печать информации
	PrintGraphInfo();
}

void CommandManager::ReadAdjacencyMatrix(std::string _context)
{
	// вызов функции считывания графа 
	m_graph.ReadGraphFromFile(_context, INPUT_FILE_TYPE::ADJACENCY_MATRIX);

	// печать информации
	PrintGraphInfo();
}

void CommandManager::ReadAdjacencyList(std::string _context)
{
	// вызов функции считывания графа 
	m_graph.ReadGraphFromFile(_context, INPUT_FILE_TYPE::ADJACENCY_LIST);

	// печать информации
	PrintGraphInfo();
}

void CommandManager::SetOutputFilepath(std::string _filepath)
{
	// открытие файла
	m_fout.open(RESULT_FILE_PATH + _filepath);

	INFO("Вывод в файл: " + RESULT_FILE_PATH + _filepath);

	// перенаправление буфера вывода
	std::cout.rdbuf(m_fout.rdbuf());
}

void CommandManager::GetDeveloperData(std::string _data)
{
	std::cout << DEVELOPER_DATA;
}
