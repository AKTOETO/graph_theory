#include "../pch.h"
#include "PresetGraphManT4.h"

PresetGraphManT4::PresetGraphManT4(const S_PTR(Graph)& _graph, const S_PTR(std::vector<bool>) _states)
	:// инициализация всех полей
	BaseGraphPresetManager(_graph, _states),
	m_cruscal_spanning_tree(nullptr),
	m_prim_spanning_tree(nullptr),
	m_boruvka_spanning_tree(nullptr)
{
	// TODO в m_cur_graph класть либо сам граф или 
	// соотнесенный граф, что позволит убрать лишние 
	// спецификаторы для орграфа. В функциях, которые
	// описаны ниже, использовать m_cur_graph
	// 

	
}

PresetGraphManT4::~PresetGraphManT4()
{
	m_boruvka_spanning_tree.reset();
	m_prim_spanning_tree.reset();
	m_cruscal_spanning_tree.reset();
}

//==================================//
//         CALCULATE МЕТОДЫ         //
//==================================//

// неориентированный граф
bool PresetGraphManT4::CalculateCruscal()
{
	if(!m_graph->is_directed())
	{
		INFO("Расчет Краскал");

		// перевыделение памяти под список ребер мин. остовного дерева
		// и запись остовного дерева
		m_cruscal_spanning_tree.reset();
		m_cruscal_spanning_tree = std::make_unique<SpanningTree>(ALGO::Cruscal(m_graph));

		return true;
	}
	return false;
}

bool PresetGraphManT4::CalculatePrim()
{
	if (!m_graph->is_directed())
	{
		INFO("Расчет Прим");

		// перевыделение памяти под список ребер мин. остовного дерева
		// и запись остовного дерева
		m_prim_spanning_tree.reset();
		m_prim_spanning_tree = std::make_unique<SpanningTree>(ALGO::Prim(m_graph));

		return true;
	}
	return false;
}

bool PresetGraphManT4::CalculateBoruvka()
{
	if (!m_graph->is_directed())
	{
		INFO("Расчет Борувка");

		// перевыделение памяти под список ребер мин. остовного дерева
		// и запись остовного дерева
		m_boruvka_spanning_tree.reset();
		m_boruvka_spanning_tree = std::make_unique<SpanningTree>(ALGO::Boruvka(m_graph));

		return true;
	}
	return false;
}

bool PresetGraphManT4::CalculateCruscalPrimBoruvka()
{
	return false;
}
// ориентированный граф

bool PresetGraphManT4::CalculateDigraphCruscal()
{
	return false;
}

bool PresetGraphManT4::CalculateDigraphPrim()
{
	return false;
}

bool PresetGraphManT4::CalculateDigraphBoruvka()
{
	return false;
}

bool PresetGraphManT4::CalculateDigraphCruscalPrimBoruvka()
{
	return false;
}


//==================================//
//            GET МЕТОДЫ            //
//==================================//

const U_PTR(SpanningTree)& PresetGraphManT4::GetCruscalSpanTree() const
{
	return m_cruscal_spanning_tree;
}

const U_PTR(SpanningTree)& PresetGraphManT4::GetPrimSpanTree() const
{
	return m_prim_spanning_tree;
}

const U_PTR(SpanningTree)& PresetGraphManT4::GetBoruvkaSpanTree() const
{
	return m_boruvka_spanning_tree;
}
