#ifndef MAJORSCRIPTMANPRESET_H
#define MAJORSCRIPTMANPRESET_H

#include "../GraphManager.h"

#include "../../task1/PresetScriptManT1.h"
#include "../../task2/PresetScriptManT2.h"

class MajorScriptManPreset:
	public PresetScriptManrT1,
	public PresetScriptManrT2
{
protected:
	// сценарий расчета и вывода характеристик
	S_PTR(Script) m_script;

	// список возможных характеристик графа
	// с указателями на функции печати этих характеристик
	std::unordered_map<SPEC, void(MajorScriptManPreset::*)()const> m_specs;

public:
	MajorScriptManPreset(
		const S_PTR(GraphManager)& _graph_man, const S_PTR(Script)& _script
	);
	~MajorScriptManPreset() override;

	// главный метод
	void Run();
};
#endif // MAJORSCRIPTMANPRESET_H
