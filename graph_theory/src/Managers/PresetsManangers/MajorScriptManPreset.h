#ifndef MAJORSCRIPTMANPRESET_H
#define MAJORSCRIPTMANPRESET_H

#include "../GraphManager.h"

#include "../../task1/PresetScriptManT1.h"
#include "../../task2/PresetScriptManT2.h"
#include "../../task3/PresetScriptManT3.h"
#include "../../task4/PresetScriptManT4.h"
#include "../../task5/PresetScriptManT5.h"
#include "../../task6/PresetScriptManT6.h"
#include "../../task7/PresetScriptManT7.h"
#include "../../task8/PresetScriptManT8.h"
#include "../../task9/PresetScriptManT9.h"

class MajorScriptManPreset:
	public PresetScriptManT1,
	public PresetScriptManT2,
	public PresetScriptManT3,
	public PresetScriptManT4,
	public PresetScriptManT5,
	public PresetScriptManT6,
	public PresetScriptManT7,
	public PresetScriptManT9
{
protected:
	// настройки системы
	S_PTR(SystemSetting) m_sys_settings;

	// список возможных характеристик графа
	// с указателями на функции печати этих характеристик
	std::unordered_map<SPEC, void(MajorScriptManPreset::*)()const> m_specs;

public:
	MajorScriptManPreset(
		const S_PTR(GraphManager)& _graph_man,	// управляющий графом
		const S_PTR(SystemSetting)& _setts		// сценарий работы 
	);
	~MajorScriptManPreset() override;

	// главный метод
	void Run();
};
#endif // MAJORSCRIPTMANPRESET_H
