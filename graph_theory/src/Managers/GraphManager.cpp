#include "../pch.h"
#include "GraphManager.h"

GraphManager::GraphManager(const S_PTR(SystemSetting)& _settings)
	: m_sys_settings(_settings)
{
	// создание графа и массива состояний
	m_graph = std::make_shared<Graph>(m_sys_settings->m_filepath, m_sys_settings->m_in_type);
	m_states = std::make_shared<State>(NUMBER_OF_SPECIFIERS, 0);

	// создание главного пресета программы
	m_major_preset = std::make_unique<MajorGraphManPreset>(m_sys_settings,m_graph, m_states);
}

GraphManager::~GraphManager()
{
	m_graph.reset();
	m_states.reset();
	m_major_preset.reset();
}

const U_PTR(MajorGraphManPreset)& GraphManager::GetMajorPreset() const
{
	return m_major_preset;
}

const S_PTR(SystemSetting)& GraphManager::GetSystemSettings() const
{
	return m_sys_settings;
}


