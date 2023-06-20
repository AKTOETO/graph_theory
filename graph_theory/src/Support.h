#ifndef SUPPORT_H
#define SUPPORT_H

#include "Constants.h"

//==========================//
//	ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ	//
//==========================//

// подсчет количество цифр в числе
inline int CountDigit(const int& number) {
	return int(log10(number) + 1);
}

// подсчет максимального числа цифр в числе в векторе
inline int CountDigitInVector(const VertexArr& _vec)
{
	int num = 0;
	std::for_each(_vec.begin(), _vec.end(), [&num](const int& el)
		{
			if (el != INF)
				num = std::max(CountDigit(el), num);
		}
	);
	return num;
}

// подсчет максимального числа цифр в числе в матрице
inline int CountDigitInMatrix(const VertexMatrix& _vec)
{
	int num = 0;
	std::for_each(_vec.begin(), _vec.end(), [&num](const VertexArr& el)
		{
			num = std::max(CountDigitInVector(el), num);
		}
	);
	return num;
}

// печать символа бесконечности
inline void PrintInfinity(
	int _setwidth = 0
)
{
	// смена локали на стандартную для С
	std::locale::global(std::locale::classic());

	// смена кодовой панели консоли на 65001
	system("chcp 65001 > nul");

	// вывод символа бесконечности
	std::cout << std::fixed
		<< std::setw(static_cast<std::streamsize>(_setwidth)
			+ INF_PRINT_WIDTH)
		<< std::setfill(' ') << u8"∞";

	// смена локали на русскую
	std::locale::global(std::locale("ru"));

	// смена кодовой панели консоли на 866
	system("chcp 866 > nul");
}

// печать вектора через определенный элемент
template<typename T>
inline void PrintVector(
	const std::vector<T>& _vec,
	std::string _delim = " ",
	int _setwidth = 0
)
{
	// нужен ли автоматический подбор ширины вывода числа
	bool auto_width = (_setwidth == 0 ? 1 : 0);

	for (int i = 0; i < _vec.size(); i++)
	{
		// если нужен автоматическое вычисление ширины вывода
		if (auto_width)_setwidth = CountDigit((_vec[i] != INF) ? _vec[i] : 1);

		// вывод элементов
		// вывод символа бесконечности
		if (_vec[i] >= INF)
		{
			PrintInfinity(_setwidth);
		}
		// иначе просто выводим текущий символ
		else
		{
			// если это первый символ в сторке, выводим на 1 меньшую ширину			
			std::cout << std::fixed <<
				std::setw(_setwidth)
				<< std::setfill(' ');

			std::cout << _vec[i];
		}
		if (i + 1 != _vec.size())std::cout << _delim;
	}
}

// печать компонент связности, используя маркированные вершины графа
inline void PrintConnectedComponentsInConsole(
	const VertexArr& _marked_vertices,	// маркированные вершины
	std::string _delim = ", ",	// разделитель элементов при печати
	int _setwidth = 0			// ширина печати одного элемента
)
{
	// ищем максимальный номер компоннеты
	int max_comp = *std::max_element(_marked_vertices.begin(), _marked_vertices.end());

	// массив вершин в текущей компоненте
	VertexArr vert_in_comp;

	// перечисляем в цикле все номера компонент, параллельно собрая
	// массив вершин в текущей компоненте
	for (int comp_number = max_comp - 1; comp_number >= 0; comp_number--)
	{
		std::cout << "[";

		// узнаем количество вершин в iой компоненте связности
		auto numb_of_vert = std::count_if(
			_marked_vertices.begin(), _marked_vertices.end(), [&comp_number](const Vertex& _v)
			{
				return _v - 1 == comp_number;
			}
		);
		// изменяем размер массива вершин в текущей компоненте
		vert_in_comp.resize(numb_of_vert);

		// итератор на начало массива вершин в текущей компоненте
		// для заполнения вершин
		auto it = vert_in_comp.begin();

		// ищем подходящие вершины
		for (int vertex_number = 0; vertex_number < _marked_vertices.size() && it != vert_in_comp.end(); vertex_number++)
		{
			if (_marked_vertices[vertex_number] - 1 == comp_number)
			{
				*it = vertex_number + 1;
				it++;
			}
		}

		// печатаем массив вершин
		PrintVector(vert_in_comp, _delim, _setwidth);

		std::cout << "]";

		// печатаем разедлитель
		if (comp_number)std::cout << _delim;
	}
}

// печать массива ребер
inline void PrintEdgeList(
	const EdgeList& _edge_l,	// список ребер
	std::string _delim = ", ",	// разделитель элементов при печати
	bool _is_need_weight = 0,	// нужно ли печатать вес ребра
	bool _is_need_greater = 0	// нужно ли отображать вершины по возростанию
)
{
	auto it = _edge_l.begin();
	for (; it != _edge_l.end(); it++)
	{
		if (_is_need_greater)
			std::cout << "("
			<< std::min(it->m_from, it->m_to) + 1
			<< _delim
			<< std::max(it->m_from, it->m_to) + 1;
		else
			std::cout << "("
			<< it->m_from + 1
			<< _delim
			<< it->m_to + 1;

		if (_is_need_weight)
			std::cout << _delim
			<< it->m_weight;

		std::cout << ")";
		//печать разделителя
		if (std::distance(it, _edge_l.end()) > 1)
			std::cout << _delim;
	}
}

// печать списка ребер вертикально
inline void PrintEdgeListVertically(
	const EdgeList& _edge_l,	// список ребер
	std::string _delim = ", ",	// разделитель элементов при печати
	bool _is_need_weight = 0,	// нужно ли печатать вес ребра
	std::string _weight_delim = ":"	// разделитель веса
)
{
	auto it = _edge_l.begin();
	for (; it != _edge_l.end(); it++)
	{
		std::cout
			<< it->m_from + 1
			<< _delim
			<< it->m_to + 1;

		if (_is_need_weight)
			std::cout << _weight_delim
			<< it->m_weight
			<<"\n";

		////печать разделителя
		//if (std::distance(it, _edge_l.end()) > 1)
		//	std::cout << _delim;
	}
}

// Печать всей муравьиной колонии
inline void PrintFullAntColony(
	const AntColony& _colony
)
{
	for (auto& ant : _colony)
	{
		std::cout << "len: " << ant.length;
		std::cout << "\npath: ";

		for (auto& el : ant.tour)
			std::cout << el + 1 << " ";

		//for (auto& el : CalcPath(ant, _edges))
		//{
		//	cout << el.start << " - " << el.end << " : (" << el.weight << ")\n";
		//}
		std::cout << "\n";
		std::cout << "\n";
	}
}

// печать массива шарниров
inline void PrintPivotsInConsole(
	const PivotArr& _vec,
	std::string _delim = ", ",
	int _setwidth = 0
)
{
	// массив шарниров
	VertexArr p_arr(
		std::count_if(_vec.begin(), _vec.end(), [](const Pivot& p)
			{
				return p == 1;
			}), 0
	);

	// преобразование массива шарниров
	// текущий элемент в конечном массиве шарниров
	int ind = 0;
	for (int i = 0; i < _vec.size(); i++)
	{
		if (_vec[i] == 1)
			p_arr[ind++] = i + 1;
	}

	// печать преобразованного массива
	PrintVector(p_arr, _delim, _setwidth);
}

// печать путей от конкретной вершины до всех остальных с весами
inline void PrintShortestPathFromVToAllOtherV(
	const VertexArr& _dists,
	const Vertex& _start_v,
	const bool& _need_inf = 1
)
{
	// проходимся по мвссиву расстояний и выводим кратчайшие пути
	for (int i = 0; i < _dists.size(); i++)
	{
		if (i != _start_v)
		{
			// бесконечная длина
			if (_dists[i] == INF && _need_inf)
			{
				std::cout << _start_v + 1 << " - " << i + 1 << ": ";
				PrintInfinity();
				std::cout << "\n";
			}
			else if (_dists[i] != INF)
			{
				std::cout << _start_v + 1 << " - " << i + 1 << ": "
					<< _dists[i] << "\n";
			}
		}
	}
}

// печать путей от всех вершин ко всем
inline void PrintAllShortestPath(
	const VertexMatrix& _dists,
	const bool& _need_inf = 1
)
{
	// выбираем вершину и выводим ребра для нее
	for (int i = 0; i < _dists.size(); i++)
	{
		PrintShortestPathFromVToAllOtherV(_dists[i], i, _need_inf);
	}
}

// печать вектора клеток
inline void PrintCellVector(
	const CellVector& _dist,
	std::string _sep = ", ",
	std::string _delim = ", "
)
{
	for (auto it = _dist.begin(); it != _dist.end(); it++)
	{
		std::cout
			<< "(" << it->GetX()
			<< _sep << it->GetY()
			<< ")";
		if (std::distance(it, _dist.end()) > 1)
			std::cout << ", ";
	}
}


// проверка на наличие определенного элемента в матрице
template<typename ScriptMan>
inline bool IsThereElementInMatrix(
	const std::vector<std::vector<ScriptMan>>& _mat,
	const ScriptMan& _el
)
{
	// проходимся по всем строкам и смотрим, есть ли там элемент _el
	for (const std::vector<ScriptMan>& row : _mat)
	{
		if (std::find(row.begin(), row.end(), _el) != row.end())
		{
			return true;
		}
	}
	return false;
}

// получение текущего времени
inline std::string GetCurrentTime()
{
	time_t now = time(0);
	tm* tstruct = new tm;
	char buf[9];
	localtime_s(tstruct, &now);
	strftime(buf, sizeof(buf), "%H:%M:%S", tstruct);

	return std::string(buf);
}

// получение текущей даты
inline std::string GetCurrentDate()
{
	time_t now = time(0);
	tm* tstruct = new tm;
	char buf[120];
	localtime_s(tstruct, &now);
	strftime(buf, sizeof(buf), "%d-%m-%Y(%H-%M-%S)", tstruct);

	return std::string(buf);
}

// получение подстроки отделенной с помощью delim
// и удаление этой подстроки из изначальной строки
inline std::string GetToken(std::string& _str, char _delim = ';')
{
	// позиция делителя
	size_t delim_pos = _str.find(_delim);

	// если делитель не был найден, переносим всю строку
	if (delim_pos == -1)
	{
		delim_pos = _str.size();
	}

	// строка с нужной подстрокой
	// копирование нужной строки
	std::string new_str = _str.substr(0, delim_pos);

	// сдвиг всех символов в начало
	_str.erase(0, delim_pos + 1);

	return new_str;
}

// поиск и удаление определенного символа в строке
inline void FindAndDeleteChar(std::string& _str, char _to_del = '\r')
{
	_str.erase(
		std::remove_if(_str.begin(), _str.end(), [_to_del](char& ch)
			{
				return ch == _to_del;
			}),
		_str.end());
}

// получение строки из вектора путем объединения 
// конкретных элементов этого вектора
inline std::string GetStringFromVector(
	std::vector<std::string>::const_iterator _begin,
	std::vector<std::string>::const_iterator  _end,
	const std::string _wrapper = "",
	const std::string _delim = " "
)
{
	std::string out;

	std::for_each(_begin, _end, [&](std::string str)
		{
			out += _wrapper + str + _wrapper + _delim;
		}
	);

	return out;
}
// получение строки из вектора
inline std::string GetStringFromVector(
	const Params& _par,
	const std::string _wrapper = "",
	const std::string _delim = " "
)
{
	return GetStringFromVector(
		_par.begin(), _par.end(), _wrapper, _delim
	);
}
// Булевая функция по умолчанию
inline bool DefaultTrueFunc(std::string)
{
	return true;
}

// Проверка на число
inline bool IsItANumber(std::string _str)
{
	// итератор на начало строки
	std::string::const_iterator it = _str.begin();

	// идем до символа, который окажется не цифрой
	while (
		it != _str.end() && (std::isdigit(*it) ||
		((it - _str.begin() == 0) && (*it == '-')))
		) it++;

	// если строка не пустая и мы дошли до конца
	// значит это число
	return (_str.end() == it);
}

// Проверка на наличие числа в строке
inline bool IsThereANumber(std::string _str)
{
	// итератор на начало строки
	std::string::const_iterator it = _str.begin();

	// идем до символа, который окажется не цифрой
	while (it != _str.end() && std::isdigit(*it)) it++;

	// если строка не пустая и мы дошли до конца
	// значит это число
	return !_str.empty() && (_str.begin() - it != 0);
}

// проверка на не отрицательное число
inline bool IsThereANotNegativeNumber(std::string _str)
{
	// если это число и оно не отрицательно
	if (IsThereANumber(_str) && atoi(_str.c_str()) >= 0)
		return true;
	return false;
}

// проверка на не отрицательное число в векторе строк
inline bool IsThereANotNegativeNumberInVector(Params _vec)
{
	for (auto& el : _vec)
		if (!IsThereANotNegativeNumber(el))
			return false;
	return true;
}

// ввод и проверка значений
template<class FUNC = bool(std::string)>
inline std::string CheckableRead(
	const std::string _welcome_str,		// строка с запросом ввода
	const FUNC& _comp				// функция сравнения 
	= DefaultTrueFunc,
	const std::string _err_str			// строка с ошибкой
	= "Было введено некорректное значение"
)
{
	// считываемый символ
	std::string str;

	// вывод сообщения
	std::cout << _welcome_str;
	// считывание из консоли
	getline(std::cin, str);

	// если было введено не то, что нужно было
	if (!_comp(str))
	{
		std::cout << "\t" + std::string(__FUNCTION__) + ": " + str + "\n";
		// рекурсивный запрос значения
		str = CheckableRead<FUNC>(_welcome_str, _comp, _err_str);
	}
	return str;
}

// является ли символ кириллическим
inline bool IsCyrillic(char _symb)
{
	return 'А' <= _symb && _symb <= 'я'
		|| _symb == 'ё' || _symb == 'Ё';
}


// проверка на корректность данных
inline std::string IsStringNotEmpty(const std::string& _str)
{
	// если строка не пустая, тогда возвращаем ее
	// иначе вернем ошибочное сообщение
	return (_str.length() ? _str : "-");
}

/// <summary>
/// Подготовка строки для получения из нее слов
/// </summary>
/// <param name="_str"> строка, которую надо подготовить </param>
/// <param name="_delim"> символ, который делит строку на слова</param>
inline void RemoveUnnecessarySpaces(std::string& _str)
{
	// добавление _delim в конец
	// нужно для корректной работы алгоритма удаления
	_str += ' ';

	// уничтожение ненужных символов _delim
	size_t begin_del_pos = -1;
	size_t end_del_pos = 0;
	do
	{
		// поиск первого разделяющего символа
		begin_del_pos = _str.find(' ', begin_del_pos + 1);
		// поиск конца последовательности из разделяющих символов
		end_del_pos = _str.substr(begin_del_pos).find_first_not_of(' ');

		// удаление этих пробелов
		_str.erase(begin_del_pos, end_del_pos - 1);

	} while (
		end_del_pos != std::string::npos &&
		begin_del_pos != std::string::npos
		);

	// если первый символ - пробел
	if (_str[0] == ' ')
	{
		_str.erase(0, 1);
	}
}

/// <summary>
/// Перевод строки в нижний регистр
/// </summary>
/// <param name="_str"> Строка, которую нужно перевести в нижний регистр</param>
/// <returns>Вернет строку в нижнем регистре</returns>
inline std::string ToLowerCase(const std::string _str)
{
	std::string out;
	for (int i = 0; i < _str.length(); i++)
	{
		if (IsCyrillic(_str[i]) && _str[i] < 'а')
		{
			out += (char(_str[i] + 32));
		}
		else
		{
			out += tolower(_str[i]);
		}
	}
	return out;
}

/// <summary>
/// Перевод строки в верхний регистр
/// </summary>
/// <param name="_str"> Строка, которую нужно перевести в верхний регистр</param>
/// <returns>Вернет строку в верхнем регистре</returns>
inline std::string ToUpperCase(const std::string _str)
{
	std::string out;
	for (int i = 0; i < _str.length(); i++)
	{
		if (IsCyrillic(_str[i]) && _str[i] >= 'а')
		{
			out += (char(_str[i] - 32));
		}
		else
		{
			out += toupper(_str[i]);
		}
	}
	return out;
}

//**********************************//
//		ФУНКЦИИ СРАВНЕНИЯ СТРОК		//
//**********************************//
namespace COMPARE
{
	inline bool IsLower(std::string s1, std::string s2)
	{
		if (IsItANumber(s1) && IsItANumber(s2))
			return atoi(s1.c_str()) < atoi(s2.c_str());

		return s1 < s2 && s1.length() <= s2.length();
	}

	inline bool IsGreater(std::string s1, std::string s2)
	{
		if (IsItANumber(s1) && IsItANumber(s2))
			return atoi(s1.c_str()) > atoi(s2.c_str());

		return s1 > s2 && s1.length() >= s2.length();
	}

	inline bool IsEqual(std::string s1, std::string s2)
	{
		if (IsItANumber(s1) && IsItANumber(s2))
			return atoi(s1.c_str()) == atoi(s2.c_str());

		return s1 == s2;
	}

	inline bool IsLowerEqual(std::string s1, std::string s2)
	{
		return IsLower(s1, s2) || IsEqual(s1, s2);
	}

	inline bool IsGreaterEqual(std::string s1, std::string s2)
	{
		return IsGreater(s1, s2) || IsEqual(s1, s2);
	}

	// Массив функций сравнения
	static bool (*COMPARISONS[])(std::string, std::string) =
	{
		IsGreater,
		IsLower,
		IsEqual,
		IsLowerEqual,
		IsGreaterEqual
	};
}

#endif
