#include "../pch.h"
#include "GraphManager.h"

GraphManager::GraphManager(std::string _filepath, INPUT_FILE_TYPE _in_f_type)
{
	// создание графа и массива состояний
	m_graph = std::make_shared<Graph>(_filepath, _in_f_type);
	m_states = std::make_shared<State>(NUMBER_OF_SPECIFIERS, 0);

	// создание главного пресета программы
	m_major_preset = std::make_unique<MajorGraphManPreset>(m_graph, m_states);
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


