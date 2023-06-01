#include "pch.h"
#include "DSU.h"

// конструктор, принимающий количество 
// элементов в системе множеств
DSU::DSU(size_t _size)
{
	m_subsets = new Subset[_size];

	for (int i = 0; i < _size; i++)
	{
		MakeSet(i);
	}
}

// деструктор
DSU::~DSU()
{
	delete[] m_subsets;
}

// добавдение элемента m_x,
// помещая его в новое множество
void DSU::MakeSet(int m_x)
{
	m_subsets[m_x].m_parent = m_x;
	m_subsets[m_x].m_rank = 0;
}

// поиск множества,в котором содержится 
// переданный в функцию элемент
int DSU::FindSet(int i)
{
	if (m_subsets[i].m_parent == i)
	{
		return i;
	}
	return m_subsets[i].m_parent = FindSet(m_subsets[i].m_parent);
}

// объединение множеств по рангу
void DSU::UnionSet(int m_x, int m_y)
{
	m_x = FindSet(m_x);
	m_y = FindSet(m_y);

	// если m_x и m_y - это разнве множества
	if (m_x != m_y)
	{
		// прикрепляем дерево с меньши рангом
		// к дереву с большим рангом
		if (m_subsets[m_x].m_rank < m_subsets[m_y].m_rank)
		{
			std::swap(m_x, m_y);
		}
		m_subsets[m_y].m_parent = m_x;

		// если ранги одинаковые, увеличиваем ранг на 1
		if (m_subsets[m_x].m_rank == m_subsets[m_y].m_rank)
		{
			m_subsets[m_x].m_rank++;
		}
	}
}
