#ifndef MAP_H
#define MAP_H
#include "Logger.hpp"

// класс карты
class Map
{
private:
	// карта весов каждой ячейки
	WeightMatrix m_map;

public:
	Map(std::string _filepath);
	~Map();	
	
	// размер матрицы
	const size_t GetSize() const;

	// высота в ячейке
	const Weight& GetCellHeight(const Cell& _cell) const;

	// получение списка соседей для клетки
	NeighborsList neighbors(const Cell& _cell);
};

#endif MAP_H
