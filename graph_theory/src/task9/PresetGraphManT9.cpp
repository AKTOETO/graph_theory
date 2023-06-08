﻿#include "../pch.h"
#include "PresetGraphManT9.h"

PresetGraphManT9::PresetGraphManT9(
	const S_PTR(SystemSetting)& _settings,
	const S_PTR(Graph)& _graph,
	const S_PTR(StateVector) _states
) :// инициализация всех полей
	BaseGraphPresetManager(_settings, _graph, _states),
	m_min_hamilton_cycle(nullptr),
	m_hamilton_cycles_length(-1)
{
}

PresetGraphManT9::~PresetGraphManT9()
{
}

bool PresetGraphManT9::CalculateCanCalculateCycle()
{
	// в связном графе на n >= 3 вершинах для
	// каждой вершины должно выполняться условие:
	// deg(v) >= n/2, тогда в графе есть 
	// гамильтонов цикл
	
	// расчет степеней вершин
	// если граф не направленный, расчитываем степень входа и выхода

	// выделение памяти под массив степеней вершин входа
	VertexArr m_degrees (m_graph->adjacency_matrix().size(), 0);

	// расчет степеней вершин входа
	for (int i = 0; i < m_graph->adjacency_matrix().size(); i++)
	{
		for (int j = 0; j < m_graph->adjacency_matrix().size(); j++)
		{
			if (m_graph->is_edge(i, j) || m_graph->is_edge(j, i)) (m_degrees)[i]++;
		}
	}

	// проверка условия deg(v) >= n/2
	for (auto& el : m_degrees)
	{
		if (el < m_graph->adjacency_matrix().size())
		{
			ERROR("Условие гамильтонова цикла deg(v) >= n/2 не выполняется!");
			return false;
		}
	}
	return true;
}

bool PresetGraphManT9::CalculateBranchAndBounds()
{
	// если граф подходит
	if (CalculateCanCalculateCycle())
	{

	}
	return false;
}

bool PresetGraphManT9::CalculateAntColony()
{
	// если граф подходит
	if (CalculateCanCalculateCycle())
	{

	}
	return false;
}


const U_PTR(EdgeList)& PresetGraphManT9::GetMinHamiltonCycle() const
{
	// TODO: вставьте здесь оператор return
}

const Weight& PresetGraphManT9::GetHamiltonCyclesLength() const
{
	// TODO: вставьте здесь оператор return
}