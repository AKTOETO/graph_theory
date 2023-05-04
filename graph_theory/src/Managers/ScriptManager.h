#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "GraphManager.h"
#include "PresetsManangers/MajorScriptManPreset.h"

class ScriptManager
{
protected:
	// сценарий работы программы
	S_PTR(Script) m_script;

	// управляющий графом
	S_PTR(GraphManager) m_graph_manager;

	// упарвляющий поведением программы
	U_PTR(MajorScriptManPreset) m_script_manager;

public:
	ScriptManager(const std::string& _filepath, const INPUT_FILE_TYPE& _in_f_type, const Script& _script);
	~ScriptManager();

	void Run();
};


#endif // !SCRIPTMANAGER_H
