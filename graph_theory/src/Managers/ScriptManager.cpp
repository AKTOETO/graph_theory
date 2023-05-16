#include "../pch.h"
#include "ScriptManager.h"

ScriptManager::ScriptManager(
	const SystemSetting& _settings
) :	m_sys_settings(std::make_shared<SystemSetting>(_settings))
{
	// создание графа
	m_graph_manager = std::make_shared<GraphManager>(
		m_sys_settings
	);

	// создание управляющего программы
	m_script_mananger = std::make_unique<MajorScriptManPreset>(m_graph_manager, m_sys_settings);
}

ScriptManager::~ScriptManager()
{
	m_sys_settings.reset();
	m_graph_manager.reset();
	m_script_mananger.reset();
}

void ScriptManager::Run()
{
	m_script_mananger->Run();
}
