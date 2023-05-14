#ifndef MAJORGRAPHMANPRESET_H
#define MAJORGRAPHMANPRESET_H

#include "../../task1/PresetGraphManT1.h"
#include "../../task2/PresetGraphManT2.h"
#include "../../task3/PresetGraphManT3.h"
#include "../../task4/PresetGraphManT4.h"

class MajorGraphManPreset : 
	public PresetGraphManT1,
	public PresetGraphManT2,
	public PresetGraphManT3,
	public PresetGraphManT4

{
protected:

	// список возможных характеристик графа
	// с указателями на функции вычисления этих характеристик
	std::unordered_map<SPEC, bool(MajorGraphManPreset::*)()> m_specs;

public:
	MajorGraphManPreset(
		const S_PTR(Graph)& _graph, const S_PTR(State) _states);
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
	const S_PTR(State)& GetStatesOfSpecs() const;
};
#endif // !MAJORGRAPHMANPRESET_H

