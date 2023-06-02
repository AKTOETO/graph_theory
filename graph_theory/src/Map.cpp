#include "pch.h"
#include "Map.h"

Map::Map(std::string _filepath)
{
	// пример пути к файлу:
	// _filepath = task8/map_001.txt
	// открытие файла карты
	std::ifstream _ifstream(GRAPH_FILE_PATH + _filepath, std::ifstream::binary);
	// Если файл не был открыт
	if (!_ifstream)
		ERROR("файл " + GRAPH_FILE_PATH + _filepath + " не был открыт!");

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
	m_map.resize(numb_of_rows);
	for (auto& vec : m_map)
		vec.resize(numb_of_rows);

	// считывание весов карты
	for (auto& cvec : m_map)
	{
		for (auto& c : cvec)
		{
			_ifstream >> c;
		}
	}
}

Map::~Map()
{
}

const size_t Map::GetSize() const
{
	return m_map.size();
}

const Weight& Map::GetCellHeight(const Cell& _cell) const
{
	// проверка на верные координаты
	if (
		!(_cell.GetX() >= 0 && _cell.GetX() < m_map.size() &&
			_cell.GetY() >= 0 && _cell.GetY() < m_map.size())
		)
		ERROR("Неверные координаты клетки: " +
			std::to_string(_cell.GetX()) + " " + std::to_string(_cell.GetY()) +
			" размер карты: " + std::to_string(m_map.size())
		);

	// получение веса
	return m_map[_cell.GetX()][_cell.GetY()];
}

NeighborsList Map::neighbors(const Cell& _cell)
{
	NeighborsList nlst;

	// массив смещений
	std::list<std::pair<int, int>> difs =
	{
		{0, 1},  // верхняя
		{1, 0},  // правая
		{0, -1}, // нижняя
		{-1, 0}  // левая
	};

	for (auto& el : difs)
	{
		int x = _cell.GetX() + el.first;
		int y = _cell.GetY() + el.second;

		// если x y находятся в границах карты
		if (x >= 0 && x < m_map.size() && y >= 0 && y < m_map.size())
			// добавляем клетку в список соседей
			nlst.push_back(
				std::make_pair(m_map[x][y], Cell(x, y))
			);
	}

	return nlst;
}
