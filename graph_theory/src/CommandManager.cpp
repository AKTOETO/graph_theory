#include "pch.h"
#include "CommandManager.h"

CommandManager::CommandManager(int argc, char* _keys[])
	:m_script_mananger(nullptr)
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
		{"-n", &CommandManager::SetFromVertex}
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
		(this->*m_commands[m_param[0]])(GetStringFromVector(m_param.begin() + 1, it_end));

		// удаление первого ключа с его параметрами		
		m_param.erase(m_param.begin(), it_end);
	}

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


		// Task 4
#if defined(T4)
		// проверка на наличие доп ключей: -k -p -b -s
		// если нет ни одного ключа - выводим сообщение об отсутствии ключей
		if (!IsCorrectNumberOfKPBS()) ERROR("Неверное количество ключей -k -p -b -s");

		// Task 5
#elif defined(T5)
		// проверка на наличие доп ключей: -d -n
		// должны быть оба ключа сразу
		if (!IsCorrectNumberOfND()) ERROR("Неверное количество ключей -d -n. Должны быть оба!");
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

void CommandManager::ReadEdgesList(std::string _context)
{
	// вставляем в начало программы спецификатор считывания списка ребер
	m_sys_settings.m_in_type = INPUT_FILE_TYPE::EDGES_LIST;
	// сохраняем путь до файла
	m_sys_settings.m_filepath = _context;
}

void CommandManager::ReadAdjacencyMatrix(std::string _context)
{
	// вставляем в начало программы спецификатор считывания матрицы смежности
	m_sys_settings.m_in_type = INPUT_FILE_TYPE::ADJACENCY_MATRIX;
	// сохраняем путь до файла
	m_sys_settings.m_filepath = _context;
}

void CommandManager::ReadAdjacencyList(std::string _context)
{
	// вставляем в начало программы спецификатор считывания списка смежности
	m_sys_settings.m_in_type = INPUT_FILE_TYPE::ADJACENCY_LIST;
	// сохраняем путь до файла
	m_sys_settings.m_filepath = _context;
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

// TASK 4
// Обработка ключей

void CommandManager::SetCruscalSpec(std::string _data)
{
	INFO("установка алгоритма Крусскала");

	// добавление в настроки системы алгоритма крускала
	m_sys_settings.m_script.push_back(SPEC::KRUSKAL);
}

void CommandManager::SetPrimSpec(std::string _data)
{
	INFO("установка алгоритма Прима");

	// добавление в настроки системы алгоритма прима
	m_sys_settings.m_script.push_back(SPEC::PRIM);
}

void CommandManager::SetBoruvkaSpec(std::string _data)
{
	INFO("установка алгоритма Борувки");

	// добавление в настроки системы алгоритма борувки
	m_sys_settings.m_script.push_back(SPEC::BORUVKA);
}

void CommandManager::SetCruscalPrimBoruvkaSpec(std::string _data)
{
	INFO("установка алгоритма Крускала Прима Борувки");

	// добавление в настроки системы алгоритма крускала, прима, борувки
	m_sys_settings.m_script.push_back(SPEC::KRUSKAL_PRIM_BORUVKA);
}

void CommandManager::SetFromVertex(std::string _data)
{
	// есть ли в строке _data неотрицательное число
	if (!IsThereANotNegativeNumber(_data)) 
		ERROR("Нет начальной вершины. После -n было введено: [" + _data + "]");

	// иначе конвертируем строку в число и передаем в настройки системы эти числа
	m_sys_settings.m_from = std::stoi(_data);
}

void CommandManager::SetToVertex(std::string _data)
{
	// есть ли в строке _data неотрицательное число
	if (!IsThereANotNegativeNumber(_data))
		ERROR("Нет конечной вершины. После -d было введено: [" + _data + "]");

	// иначе конвертируем строку в число и передаем в настройки системы эти числа
	m_sys_settings.m_to = std::stoi(_data);
}

