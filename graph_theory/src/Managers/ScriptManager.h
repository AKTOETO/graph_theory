#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "GraphManager.h"
#include "PresetsManangers/MajorScriptManPreset.h"

class ScriptManager
{
protected:
	// настроки системы
	S_PTR(SystemSetting) m_sys_settings;

	// управляющий графом
	S_PTR(GraphManager) m_graph_manager;

	// упарвляющий поведением программы
	U_PTR(MajorScriptManPreset) m_script_mananger;

public:
	ScriptManager(const SystemSetting& _settings);
	~ScriptManager();

	void Run();
};


#endif // !SCRIPTMANAGER_H
