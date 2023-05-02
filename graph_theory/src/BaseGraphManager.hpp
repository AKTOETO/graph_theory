#pragma once
#include "Graph.h"

template<class GraphMan>
class BaseGraphManager
{
protected:

	// Сам граф
	U_PTR(Graph) m_graph;

	// просчитана ли характеристика
	// 1 - просчитана
	// 0 - не просчитана
	U_PTR(std::vector<bool>) m_state_of_spec;

	// установить состояние характеристики
	// 1 - просчитана
	// 0 - не просчитана
	void SetStateOfSpec(SPEC _spec, bool _state);

	// список возможных характеристик графа
	// с указателями на функции вычисления этих характеристик
	std::unordered_map<SPEC, bool(GraphMan::*)()> m_specs;

public:
	BaseGraphManager(std::string _filepath, INPUT_FILE_TYPE _in_f_type);
	virtual ~BaseGraphManager();

	/// <summary>
	/// Расчет определенной характеристики
	/// </summary>
	/// <param name="_spec"> - характеристика, которую надо расчитать</param>
	/// <returns></returns>
	void CalculateSpecifier(SPEC _spec);

	/// <summary>
	/// получение состояния всех характеристик
	/// </summary>
	/// <returns>указатель на вектор</returns>
	const U_PTR(std::vector<bool>)& GetStatesOfSpecs() const;
};

template<class GraphMan>
void BaseGraphManager<GraphMan>::SetStateOfSpec(SPEC _spec, bool _state)
{
	(*m_state_of_spec)[int(_spec)] = _state;
}

template<class GraphMan>
BaseGraphManager<GraphMan>::BaseGraphManager(std::string _filepath, INPUT_FILE_TYPE _in_f_type)
// инициализация полей
	:m_state_of_spec(std::make_unique<std::vector<bool>>(NUMBER_OF_SPECIFIERS, 0)),
	m_graph(std::make_unique<Graph>(_filepath, _in_f_type))
{}

template<class GraphMan>
BaseGraphManager<GraphMan>::~BaseGraphManager()
{
	// очистка памяти
	m_graph.reset();
	m_state_of_spec.reset();
}

template<class GraphMan>
void BaseGraphManager<GraphMan>::CalculateSpecifier(SPEC _spec)
{
	// если раньше не рассчитывали параметр _spec
	if (!(*m_state_of_spec)[int(_spec)])
	{
		// расчитываем его
		SetStateOfSpec(_spec, (dynamic_cast<GraphMan*>(this)->*m_specs[_spec])());
	}
}

template<class GraphMan>
const U_PTR(std::vector<bool>)& BaseGraphManager<GraphMan>::GetStatesOfSpecs() const
{
	return m_state_of_spec;
}
