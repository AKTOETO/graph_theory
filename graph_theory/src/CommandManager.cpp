#include "CommandManager.h"

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

	// тестовая печать
	m_graph.PrintAdjacencyMatrix();

	/*INFO("Есть ли дуга от 0 к 4 = " + (m_graph.is_edge(0, 4) ? "да" : "нет"));
	INFO("Есть ли дуга от 1 к 2 = " + (m_graph.is_edge(1, 2) ? "да" : "нет"));
	INFO("Есть ли дуга от 1 к 1 = " + (m_graph.is_edge(1, 1) ? "да" : "нет"));
	INFO("Вес дуги от 1 к 2 = " + std::to_string(m_graph.weight(1,2)));
	INFO("Вес дуги от 1 к 1 = " + std::to_string(m_graph.weight(1,1)));
	INFO("Список смежных вершин с 4:");

	VertexArr vr = m_graph.adjacency_list(4);
	for (auto& el : vr)
	{
		std::cout << el << " ";
	}
	std::cout << "\n";*/

	// степень входа
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

void CommandManager::PrintParams() const
{
	std::string out;
	std::for_each(m_param.begin(), m_param.end(), [&out](std::string str)
		{
			out += "\'" + str + "\' ";
		}
	);

	INFO("ключи с параметрами: " + out);
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
	else if (!CheckEML()) ERROR("Неверное количество ключей -e -m -l");
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

bool CommandManager::CheckEML()
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
}

void CommandManager::ReadAdjacencyMatrix(std::string _context)
{
	// вызов функции считывания графа 
	m_graph.ReadGraphFromFile(_context, INPUT_FILE_TYPE::ADJACENCY_MATRIX);
}

void CommandManager::ReadAdjacencyList(std::string _context)
{
	// вызов функции считывания графа 
	m_graph.ReadGraphFromFile(_context, INPUT_FILE_TYPE::ADJACENCY_LIST);
}

void CommandManager::SetOutputFilepath(std::string _filepath)
{
	// просто перенаправлять cout в файловый поток
	m_fout.open(RESULT_FILE_PATH + _filepath);
	INFO("Вывод в файл: " + RESULT_FILE_PATH + _filepath);
	// TODO разграничить поток, чтобы не использовать cout
	
	// перенаправление буфера вывода
	std::cout.rdbuf(m_fout.rdbuf());
}

void CommandManager::GetDeveloperData(std::string _data)
{
	std::cout << DEVELOPER_DATA;
}
