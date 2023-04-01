#include "menu.h"

Menu::Menu()
{
	// выделение памяти под массив с описанием функций
	m_command = new Command[NUMBER_OF_COMMANDS];

	// чтение команд из файлов
	for (int i = 0; i < NUMBER_OF_COMMANDS; i++)
	{
		m_command[i].FillCommandData(COMMAND_DESCRIPTION_FILES[i]);
	}

	// заполнение массива функций обработки команд
	m_command[0].SetCheckFunction(&Menu::CheckCMDHelp);
}

Menu::~Menu()
{
	delete[] m_command;
}

void Menu::ProgramMenu()
{
	// строка с введенными командами
	string input_all_command;
	// строка с введенными командами
	string input_first_command;
	// строка с введенными аттрибутами команды
	string input_attributes;

	// цикл выполнения программы
	do
	{
		// вывод сообщения запроса команды
		cout << DBMS_CONSOLE_REQUEST_COMMAND;

		// считывание команды
		getline(cin, input_all_command);

		// если строка не пустая,
		// тогда можно проверять ее на корректность
		if (input_all_command.length() != 0)
		{
			// подготовка строки для получения слов из нее
			RemoveUnnecessarySpaces(input_all_command);

			// перевод строки в нижний регистр
			input_all_command = ToLowerCase(input_all_command);

			// получение только команды (без атрибутов)
			input_first_command = GetToken(input_all_command, ' ');

			// если введенное слово является командой
			// и не был введен выход 

			if (
				IsCommandCorrect(input_first_command) &&
				input_first_command != CMD_NAME(0)
				)
			{
				//вызов необходимой функции для команды
				CMD_CHK_FUNC(input_first_command, input_all_command);
			}
			// если была введена не команда
			else if (input_first_command != CMD_NAME(0))
			{
				INFO("\"" + input_first_command + "\"" + NOT_CORRECT_COMMAND);
			}
		}

	} while (input_first_command != CMD_NAME(0));
}

bool Menu::IsCommandCorrect(const string& _command)
{
	// проходимся по массиву команд
	for (int i = 0; i < NUMBER_OF_COMMANDS; i++)
	{
		// если нашли совпадающую команду
		// выводим 1
		if (CMD_NAME(i) == _command)
		{
			return true;
		}
	}

	// иначе выводим 0
	return false;
}

int Menu::GetNumberOfCommand(const string& _command)
{
	// проходимся по массиву команд
	for (int i = 0; i < NUMBER_OF_COMMANDS; i++)
	{
		// если нашли совпадающую команду
		// выводим i
		if (CMD_NAME(i) == _command)
		{
			return i;
		}
	}

	// иначе -1
	return -1;
}

void Menu::PrintNumberedArray(const string _arr[], int _size)
{
	for (int i = 0; i < _size; i++)
	{
		cout << "\t" << i + 1 << ") " << _arr[i] << "\n";
	}
}

int Menu::ReadIndexInNumberedArray(const string _str, int _min, int _max)
{
	return atoi(
		CheckableRead(
			"\t[" + _str + "]> ",
			[_min, _max](string num)
			{
				return	IsThereANumber(num) &&
				_min <= atoi(num.c_str()) &&
			atoi(num.c_str()) <= _max;
			}
	).c_str()) - 1;
}


// проверка команды ПОМОЩЬ
void Menu::CheckCMDHelp(string _str)
{
	// если аргументы не были переданы
	// тогда выводим все команды и информацию по ним
	if (!_str.length())
	{
		for (int i = 0; i < NUMBER_OF_COMMANDS; i++)
		{
			cout << ToUpperCase(CMD_NAME(i))
				<< "\t\t" << CMD_SH_DECR(i)
				<< endl;
		}
	}
	// если есть какие-то аргументы
	else
	{
		// если этот аргумент - команда
		// выводим подробную инфу по ней
		if (IsCommandCorrect(_str))
		{
			cout << CMD_FL_DESCR(GetNumberOfCommand(_str)) << endl;
		}
		// если такого аргумента не существует
		else
		{
			cout << "\t\"" << _str << "\"" << NOT_CORRECT_COMMAND;
		}
	}
}
