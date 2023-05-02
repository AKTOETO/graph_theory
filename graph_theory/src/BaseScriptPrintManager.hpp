#pragma once
#include "BaseGraphManager.hpp"

template <class ScriptMan, class GraphMan>
class BaseScriptPrintManager
{
protected:
	// сценарий расчета и вывода характеристик
	U_PTR(Script) m_script;

	// Управляющий графом
	U_PTR(GraphMan) m_graph_manager;

	// список возможных характеристик графа
	// с указателями на функции печати этих характеристик
	std::unordered_map<SPEC, void(ScriptMan::*)()const> m_specs;

public:
	BaseScriptPrintManager(std::string _filepath, INPUT_FILE_TYPE _in_f_type, Script _script);
	virtual ~BaseScriptPrintManager();

	// главный метод
	void Run();
};

template <class ScriptMan, class GraphMan>
BaseScriptPrintManager<ScriptMan, GraphMan>::BaseScriptPrintManager(
	std::string _filepath, INPUT_FILE_TYPE _in_f_type, Script _script
)
	:m_graph_manager(std::make_unique<GraphMan>(_filepath, _in_f_type)),
	m_script(std::make_unique<Script>(_script))
{}

template <class ScriptMan, class GraphMan>
BaseScriptPrintManager<ScriptMan, GraphMan>::~BaseScriptPrintManager()
{
	m_graph_manager.reset();
	m_script.reset();
}

template<class ScriptMan, class GraphMan>
void BaseScriptPrintManager<ScriptMan, GraphMan>::Run()
{
	std::for_each(m_script->begin(), m_script->end(), [&](const SPEC& spec)
		{
			m_graph_manager->CalculateSpecifier(spec);
		}
	);

	// TODO надо еще выводить величины
	// для вывода спрашивать у граф менеджера: 
	// расчитана ли эта велечина?
	// для всего сценария вызываем соответствующие функции печати
	std::for_each(m_script->begin(), m_script->end(), [&](const SPEC& el)
		{
			(dynamic_cast<ScriptMan*>(this)->*m_specs[el])();
		}
	);
}
