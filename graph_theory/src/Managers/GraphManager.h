#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include "PresetsManangers/MajorGraphManPreset.h"

class GraphManager
{
protected:
	U_PTR(MajorGraphManPreset) m_major_preset;

	S_PTR(Graph) m_graph;
	S_PTR(StateVector) m_states;

	// настройки системы
	S_PTR(SystemSetting) m_sys_settings;

public:
	GraphManager(const S_PTR(SystemSetting)& _settings);
	~GraphManager();

	const U_PTR(MajorGraphManPreset)& GetMajorPreset() const;
	const S_PTR(SystemSetting)& GetSystemSettings() const;
};

#endif //GRAPHMANAGER_H
