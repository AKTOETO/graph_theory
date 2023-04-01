#include "command.h"

Command::Command(string _file_name)
	:m_path_to_cmd_descr_folder(MSG_DECR_FOLDER),
	m_number_of_descriptions(3),
	m_cmd_attributes(new string* [m_number_of_descriptions]),
	m_check_func(nullptr)
{
	m_cmd_attributes[0] = &m_name;
	m_cmd_attributes[1] = &m_short_description;
	m_cmd_attributes[2] = &m_full_description;

	FillCommandData(_file_name);
}

Command::Command()
	:m_path_to_cmd_descr_folder(MSG_DECR_FOLDER),
	m_number_of_descriptions(3),
	m_cmd_attributes(new string* [m_number_of_descriptions]),
	m_check_func(nullptr)
{
	m_cmd_attributes[0] = &m_name;
	m_cmd_attributes[1] = &m_short_description;
	m_cmd_attributes[2] = &m_full_description;
}

Command::~Command()
{
	if (m_cmd_attributes)
		delete[] m_cmd_attributes;
}

void Command::SetCheckFunction(CheckFunc _check_func)
{
	m_check_func = _check_func;
}

Command::CheckFunc Command::GetCheckFunction() const
{
	return m_check_func;
}

string Command::GetAttribute(int _index) const
{
	if (0 <= _index && _index <= m_number_of_descriptions)
	{
		return *m_cmd_attributes[_index];
	}
	return "";
}

void Command::FillCommandData(string _file_name)
{
	string file_path = m_path_to_cmd_descr_folder + _file_name;

	ifstream fin(file_path);
	if (!fin)
	{
		cout << "\tFillCommandData: файл " << file_path << " не открылся\n";
		return;
	}

	string temp;
	int ind = 0; // индекс текущего заполняемого поля

	// считывание данных из файла
	while (fin.peek() != EOF && ind < m_number_of_descriptions)
	{
		// считывание строки
		getline(fin, temp);

		// если последний символ - ;
		if (temp[temp.size() - 1] == ';')
		{
			// удаляем этот символ
			temp = temp.substr(0, temp.size() - 1);

			// сохраняем полученную строку
			*m_cmd_attributes[ind] += temp;

			// переходим к следующей команде
			ind++;
		}
		// если это не конец всей фразы
		else
		{
			*m_cmd_attributes[ind] += temp + '\n';
		}
	}
}

ostream& operator<<(ostream& _out_stream, const Command& _cmd)
{
	_out_stream << _cmd.m_name << endl
		<< _cmd.m_short_description << endl
		<< _cmd.m_full_description << endl;
	return _out_stream;
}
