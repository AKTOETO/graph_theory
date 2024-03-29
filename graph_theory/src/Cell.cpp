﻿#include "pch.h"
#include "Cell.h"


Cell::Cell(int _x, int _y)
	:m_x(_x), m_y(_y)
{}

Cell::Cell()
	:m_x(-1), m_y(-1)
{}

Cell::~Cell()
{
}

Cell& Cell::operator=(const Cell& _cell)
{
	m_x = _cell.GetX();
	m_y = _cell.GetY();
	return *this;
}

bool Cell::operator==(const Cell& _cell)
{
	return m_x == _cell.GetX() && m_y == _cell.GetY();
}

bool Cell::operator!=(const Cell& _cell)
{
	return m_x != _cell.GetX() || m_y != _cell.GetY();
}

void Cell::SetX(int _x)
{
	m_x = _x;
}

void Cell::SetY(int _y)
{
	m_y = _y;
}

const int& Cell::GetX() const
{
	return m_x;
}

const int& Cell::GetY() const
{
	return m_y;
}

std::ostream& operator<<(std::ostream& _ostream, const Cell& _c)
{
	_ostream << "(" << _c.GetX() << ", " << _c.GetY() << ")";
	return _ostream;
}
