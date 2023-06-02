#include "pch.h"
#include "CommandManager.h"

CommandManager::CommandManager(int argc, char* _keys[])
	:m_script_mananger(nullptr),
	m_is_h(0)
{
	// задание возможных ключей и функций их обработки
	m_commands =
	{
		{"-e", &CommandManager::ReadEdgesList},
		{"-m", &CommandManager::ReadAdjacencyMatrix},
		{"-l", &CommandManager::ReadAdjacencyList},
		{"-o", &CommandManager::SetOutputFilepath},
		{"-h", &CommandManager::GetDeveloperData},

		// Task4
		{"-k", &CommandManager::SetCruscalSpec},
		{"-p", &CommandManager::SetPrimSpec},
		{"-b", &CommandManager::SetBoruvkaSpec},
		{"-s", &CommandManager::SetCruscalPrimBoruvkaSpec},

		// Task5
		{"-d", &CommandManager::SetToVertex},
		{"-n", &CommandManager::SetFromVertex},

		// Task6
		{"-di", &CommandManager::SetDijkstraSpec},
		{"-be", &CommandManager::SetBellmanFordMurSpec},
		{"-t",  &CommandManager::SetLevitSpec},

		// Task8
		{"-m", &CommandManager::SetMapFilepath},
		{"-nn", &CommandManager::SetSourceCell},
		{"-dd", &CommandManager::SetDestinationCell},
	};

	// использование сценария программы по умолчанию
	m_sys_settings.m_script = TASK_SCRIPT;

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
		(this->*m_commands[m_param[0]])(Params(m_param.begin() + 1, it_end));

		// удаление первого ключа с его параметрами
		m_param.erase(m_param.begin(), it_end);
	}

	if (!m_is_h)
	{
		// выделение памяти под script manager и передача ему объекта  
		// SystemSettings для дальнейшей обработки его содержимого объектом 
		// MajorScriptManPreset
		m_script_mananger =
			std::make_unique<ScriptManager>(
				m_sys_settings
			);

		// запуск главного метода обработчика сценариев
		m_script_mananger->Run();
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
		m_is_h = 1;
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

#if !defined(T8)
		// проверка на введение одновременно ключей e m l
		if (!IsCorrectNumberOfEML()) ERROR("Неверное количество ключей -e -m -l");

#elif defined(T4)
		// Task 4
		// проверка на наличие доп ключей: -k -p -b -s
		// если нет ни одного ключа - выводим сообщение об отсутствии ключей
		if (!IsCorrectNumberOfKPBS()) ERROR("Неверное количество ключей: -k -p -b -s");

#elif defined(T5)
		// Task 5
		// проверка на наличие доп ключей: -d -n
		// должны быть оба ключа сразу
		if (!IsCorrectNumberOfND()) ERROR("Неверное количество ключей: -d -n. Должны быть оба!");
#elif defined(T6)
		// Task 6
		// проверка на наличиче ключа -n
		if (!IsCorrectNumberOfN()) ERROR("Неверное количество ключей: -n.");
		// проверка на наличиче ключа -d -b -t
		if (!IsCorrectNumberOfDIBET()) ERROR("Неверное количество ключей: -di -be -t. Должен быть какой-то один из них!");

#elif defined(T8)
		// Task 8
		// проверка на наличие ключей -m -nn -dd
		if (!IsCorrectNumberOfMNNDD()) ERROR("Неверное количество ключей: -m -nn -dd. Должны быть все!");

#endif

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

bool CommandManager::IsCorrectNumberOfKPBS()
{
	// если есть любой ключ из -k -p -b -s,
	// то все нормально
	return std::find_if(
		begin(m_param), end(m_param), [](const std::string& _str)
		{
			return _str == "-k" || _str == "-p" || _str == "-b" || _str == "-s";
		}) != end(m_param);
}

bool CommandManager::IsCorrectNumberOfND()
{
	// если есть оба ключа -d и -n
	return (
		std::find_if(
			begin(m_param), end(m_param), [](const std::string& _str)
			{
				return _str == "-d";
			}) != end(m_param)
			) && (
		std::find_if(
			begin(m_param), end(m_param), [](const std::string& _str)
			{
				return _str == "-n";
			}) != end(m_param)
			);
}

bool CommandManager::IsCorrectNumberOfN()
{
	return std::find_if(
		begin(m_param), end(m_param), [](const std::string& _str)
		{
			return _str == "-n";
		}) != end(m_param);
}

bool CommandManager::IsCorrectNumberOfDIBET()
{
	// map для подсчета количества ключей eml
	std::unordered_map<std::string, int> _eml =
	{
		{"-di", 0},
		{"-be", 0},
		{"-t", 0},
	};

	// подсчет количества dnt в m_param
	std::for_each(m_param.begin(), m_param.end(), [&_eml](std::string& el)
		{
			if (_eml.find(el) != _eml.end())
				_eml.at(el)++;
		}
	);

	// если количество eml таково:
	// di be t
	// 1  0  0
	// 0  1  0
	// 0  0  1
	// то все корректно
	if (
		_eml.at("-di") == 1 && _eml.at("-be") == 0 && _eml.at("-t") == 0 ||
		_eml.at("-di") == 0 && _eml.at("-be") == 1 && _eml.at("-t") == 0 ||
		_eml.at("-di") == 0 && _eml.at("-be") == 0 && _eml.at("-t") == 1
		) return true;
	return false;
}

bool CommandManager::IsCorrectNumberOfMNNDD()
{
	// если есть 3 ключа -m и -dd и -nn
	return (
		std::find_if(
			begin(m_param), end(m_param), [](const std::string& _str)
			{
				return _str == "-m";
			}) != end(m_param)
			) && (
		std::find_if(
			begin(m_param), end(m_param), [](const std::string& _str)
			{
				return _str == "-dd";
			}) != end(m_param)
			) && (
		std::find_if(
			begin(m_param), end(m_param), [](const std::string& _str)
			{
				return _str == "-nn";
			}) != end(m_param)
			);
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

////////////////////////////////////////////
// функции, выполняющие введенные команды
////////////////////////////////////////////

void CommandManager::ReadEdgesList(Params _context)
{
	// вставляем в начало программы спецификатор считывания списка ребер
	m_sys_settings.m_in_type = INPUT_FILE_TYPE::EDGES_LIST;
	// сохраняем путь до файла
	m_sys_settings.m_filepath = _context[0];
}

void CommandManager::ReadAdjacencyMatrix(Params _context)
{
	// вставляем в начало программы спецификатор считывания матрицы смежности
	m_sys_settings.m_in_type = INPUT_FILE_TYPE::ADJACENCY_MATRIX;
	// сохраняем путь до файла
	m_sys_settings.m_filepath = _context[0];
}

void CommandManager::ReadAdjacencyList(Params _context)
{
	// вставляем в начало программы спецификатор считывания списка смежности
	m_sys_settings.m_in_type = INPUT_FILE_TYPE::ADJACENCY_LIST;
	// сохраняем путь до файла
	m_sys_settings.m_filepath = _context[0];
}

void CommandManager::SetOutputFilepath(Params _filepath)
{
	// открытие файла
	m_fout.open(RESULT_FILE_PATH + _filepath[0]);

	INFO("Вывод в файл: " + RESULT_FILE_PATH + _filepath[0]);

	// перенаправление буфера вывода
	std::cout.rdbuf(m_fout.rdbuf());
}

void CommandManager::GetDeveloperData(Params _data)
{
	std::cout << DEVELOPER_DATA;
}

// TASK 4
// Обработка ключей

void CommandManager::SetCruscalSpec(Params _data)
{
	INFO("установка алгоритма Крусскала");

	// добавление в настроки системы алгоритма крускала
	m_sys_settings.m_script.push_back(SPEC::T4_KRUSKAL);
}

void CommandManager::SetPrimSpec(Params _data)
{
	INFO("установка алгоритма Прима");

	// добавление в настроки системы алгоритма прима
	m_sys_settings.m_script.push_back(SPEC::T4_PRIM);
}

void CommandManager::SetBoruvkaSpec(Params _data)
{
	INFO("установка алгоритма Борувки");

	// добавление в настроки системы алгоритма борувки
	m_sys_settings.m_script.push_back(SPEC::T4_BORUVKA);
}

void CommandManager::SetCruscalPrimBoruvkaSpec(Params _data)
{
	INFO("установка алгоритма Крускала Прима Борувки");

	// добавление в настроки системы алгоритма крускала, прима, борувки
	m_sys_settings.m_script.push_back(SPEC::T4_KRUSKAL_PRIM_BORUVKA);
}

void CommandManager::SetFromVertex(Params _data)
{
	// есть ли в строке _data неотрицательное число
	if (!IsThereANotNegativeNumberInVector(_data))
		ERROR(
			"Нет начальной вершины. После -n было введено: [" + 
			GetStringFromVector(_data.begin(), _data.end()) +
			"]");

	// иначе конвертируем строку в число и передаем в настройки системы эти числа
	m_sys_settings.m_from = std::stoi(_data[0]) - 1;

	INFO("Начальная вершина: " + std::to_string(m_sys_settings.m_from));
}

void CommandManager::SetToVertex(Params _data)
{
	// есть ли в строке _data неотрицательное число
	if (!IsThereANotNegativeNumberInVector(_data))
		ERROR(
			"Нет конечной вершины. После -d было введено: [" +
			GetStringFromVector(_data.begin(), _data.end()) +
			"]");

	// иначе конвертируем строку в число и передаем в настройки системы эти числа
	m_sys_settings.m_to = std::stoi(_data[0]) - 1;

	INFO("Конечная вершина: " + std::to_string(m_sys_settings.m_to));
}

void CommandManager::SetDijkstraSpec(Params _data)
{
	INFO("Установка алгоритма Дейкстры");
	// добавление в настроки системы алгоритма дейкстры
	m_sys_settings.m_script.push_back(SPEC::T6_USE_DIJKSTRA);
}

void CommandManager::SetBellmanFordMurSpec(Params _data)
{
	INFO("Установка алгоритма Беллмана Форда");
	// добавление в настроки системы алгоритма Беллмана-Форда-Мура
	m_sys_settings.m_script.push_back(SPEC::T6_USE_BELLMAN_FORD_MUR);
}

void CommandManager::SetLevitSpec(Params _data)
{
	INFO("Установка алгоритма Левита");
	// добавление в настроки системы алгоритма Левита
	m_sys_settings.m_script.push_back(SPEC::T6_USE_LEVIT);
}

void CommandManager::SetMapFilepath(Params _data)
{
	m_sys_settings.m_filepath = _data[0];
	INFO("Введенная часть пути файла с картой: " + GetStringFromVector(_data));
}

void CommandManager::SetSourceCell(Params _data)
{
	// есть ли в строке _data неотрицательное число
	if (!IsThereANotNegativeNumberInVector(_data) || _data.size() < 2)
		ERROR("Нет начальной вершины. После -nn было введено: [" +
			GetStringFromVector(_data) +
			"]");

	// установка начальных координат клетки
	m_sys_settings.m_begin.SetX(stoi(_data[0]));
	m_sys_settings.m_begin.SetY(stoi(_data[1]));

	INFO(
		"Начальные координаты клетки: [" +
		std::to_string(m_sys_settings.m_begin.GetX()) +
		"] [" +
		std::to_string(m_sys_settings.m_begin.GetY()) +
		"]"
	);
}

void CommandManager::SetDestinationCell(Params _data)
{
	// есть ли в строке _data неотрицательное число
	if (!IsThereANotNegativeNumberInVector(_data) || _data.size() < 2)
		ERROR("Нет конечной вершины. После -dd было введено: [" +
			GetStringFromVector(_data) +
			"]");

	// установка начальных координат клетки
	m_sys_settings.m_end.SetX(stoi(_data[0]));
	m_sys_settings.m_end.SetY(stoi(_data[1]));

	INFO(
		"Конечные координаты клетки: [" +
		std::to_string(m_sys_settings.m_end.GetX()) +
		"] [" +
		std::to_string(m_sys_settings.m_end.GetY()) +
		"]"
	);
}

