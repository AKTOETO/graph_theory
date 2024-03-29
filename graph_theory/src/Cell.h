﻿#ifndef CELL_H
#define CELL_H
// класс ячейки
class Cell
{
private:
	int m_x;
	int m_y;
public:
	Cell(int _x, int _y);
	Cell();
	~Cell();

	Cell& operator=(const Cell& _cell);
	bool operator==(const Cell& _c1);
	bool operator!=(const Cell& _cell);
	friend std::ostream& operator<<(std::ostream& _ostream, const Cell&);

	// set методы
	void SetX(int _x);
	void SetY(int _y);

	// Get методы
	const int& GetX() const;
	const int& GetY() const;
};
#endif CELL_H
