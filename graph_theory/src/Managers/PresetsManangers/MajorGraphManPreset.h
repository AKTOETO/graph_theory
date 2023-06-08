#ifndef MAJORGRAPHMANPRESET_H
#define MAJORGRAPHMANPRESET_H

#include "../../task1/PresetGraphManT1.h"
#include "../../task2/PresetGraphManT2.h"
#include "../../task3/PresetGraphManT3.h"
#include "../../task4/PresetGraphManT4.h"
#include "../../task5/PresetGraphManT5.h"
#include "../../task6/PresetGraphManT6.h"
#include "../../task7/PresetGraphManT7.h"
#include "../../task8/PresetGraphManT8.h"
#include "../../task9/PresetGraphManT9.h"
#include "../../task10/PresetGraphManT10.h"

class MajorGraphManPreset : 
	public PresetGraphManT1,
	public PresetGraphManT2,
	public PresetGraphManT3,
	public PresetGraphManT4,
	public PresetGraphManT5,
	public PresetGraphManT6,
	public PresetGraphManT7,
	public PresetGraphManT8,
	public PresetGraphManT9,
	public PresetGraphManT10

{
protected:

	// список возможных характеристик графа
	// с указателями на функции вычисления этих характеристик
	std::unordered_map<SPEC, bool(MajorGraphManPreset::*)()> m_specs;

	// настройки системы
	//S_PTR(SystemSetting) m_sys_settings;

public:
	MajorGraphManPreset(
		const S_PTR(SystemSetting)& _settings,
		const S_PTR(Graph)& _graph,
		const S_PTR(StateVector) _states
	);
	virtual ~MajorGraphManPreset();

	/// <summary>
	/// Расчет определенной характеристики
	/// </summary>
	/// <param name="_spec"> - характеристика, которую надо расчитать</param>
	/// <returns></returns>
	void CalculateSpecifier(SPEC _spec);

	/// <summary>
	/// получение состояния всех характеристик
	/// </summary>
	/// <returns>указатель на вектор</returns>
	const S_PTR(StateVector)& GetStatesOfSpecs() const;
};
#endif // !MAJORGRAPHMANPRESET_H

