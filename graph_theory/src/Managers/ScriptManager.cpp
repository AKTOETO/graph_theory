#include "../pch.h"
#include "ScriptManager.h"

ScriptManager::ScriptManager(
	const std::string& _filepath, const INPUT_FILE_TYPE& _in_f_type, const Script& _script
) :
	m_script(std::make_shared<Script>(_script))
{
	// создание графа
	m_graph_manager = std::make_shared<GraphManager>(_filepath, _in_f_type);

	// создание управляющего программы
	m_script_manager = std::make_unique<MajorScriptManPreset>(m_graph_manager, m_script);
}

ScriptManager::~ScriptManager()
{
	m_script.reset();
	m_graph_manager.reset();
	m_script_manager.reset();
}

void ScriptManager::Run()
{
	m_script_manager->Run();
}
