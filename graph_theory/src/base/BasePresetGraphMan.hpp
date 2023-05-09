#pragma once
//#include "../Graph.h"
#include "../Algorithms.hpp"

class BaseGraphManager
{
protected:

	// Сам граф
	S_PTR(Graph) m_graph;

	// просчитана ли характеристика
	// 1 - просчитана
	// 0 - не просчитана
	S_PTR(std::vector<bool>) m_state_of_spec;

	// установить состояние характеристики
	// 1 - просчитана
	// 0 - не просчитана
	void SetStateOfSpec(SPEC _spec, bool _state)
	{
		(*m_state_of_spec)[int(_spec)] = _state;
	};
   
public:
	BaseGraphManager(const S_PTR(Graph)& _graph, const S_PTR(std::vector<bool>) _states)
		// инициализация полей
		:m_state_of_spec(_states),
		m_graph(_graph)
	{};

	virtual ~BaseGraphManager()
	{
		// очистка памяти
		m_graph.reset();
		m_state_of_spec.reset();
	};
};

#define IF_ST_CALC(_spec) if((*m_state_of_spec)[int(_spec)])
#define IF_ST_NOT_CALC(_spec) if(!(*m_state_of_spec)[int(_spec)])
#define IF_ST_SHOULD_BE_CALC(_spec, _calc_func) IF_ST_NOT_CALC(_spec) SetStateOfSpec(_spec,_calc_func);