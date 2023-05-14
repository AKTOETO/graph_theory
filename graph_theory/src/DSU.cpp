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

// добавдение элемента x,
// помещая его в новое множество
void DSU::MakeSet(int x)
{
	m_subsets[x].m_parent = x;
	m_subsets[x].m_rank = 0;
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
void DSU::UnionSet(int x, int y)
{
	x = FindSet(x);
	y = FindSet(y);

	// если x и y - это разнве множества
	if (x != y)
	{
		// прикрепляем дерево с меньши рангом
		// к дереву с большим рангом
		if (m_subsets[x].m_rank < m_subsets[y].m_rank)
		{
			std::swap(x, y);
		}
		m_subsets[y].m_parent = x;

		// если ранги одинаковые, увеличиваем ранг на 1
		if (m_subsets[x].m_rank == m_subsets[y].m_rank)
		{
			m_subsets[x].m_rank++;
		}
	}
}
