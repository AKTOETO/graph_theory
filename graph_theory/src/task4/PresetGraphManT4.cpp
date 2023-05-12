#include "../pch.h"
#include "PresetGraphManT4.h"

PresetGraphManT4::PresetGraphManT4(const S_PTR(Graph)& _graph, const S_PTR(std::vector<bool>) _states)
	:// инициализация всех полей
	BaseGraphPresetManager(_graph, _states),
	m_cruscal_spanning_tree(nullptr),
	m_prim_spanning_tree(nullptr),
	m_boruvka_spanning_tree(nullptr)
{
}

PresetGraphManT4::~PresetGraphManT4()
{
}

//==================================//
//         CALCULATE МЕТОДЫ         //
//==================================//

// TODO добавить в базовый клсс указатель на текущий граф,
// который будет равен либо исходному графу, либо соотнесенному,
// который будет создаваться из исходного

//==================================//
//            GET МЕТОДЫ            //
//==================================//

