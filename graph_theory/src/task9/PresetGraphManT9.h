#ifndef PRESETGRAPHMANT9_h
#define PRESETGRAPHMANT9_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT9 :
	virtual public BaseGraphPresetManager
{
protected:

	// муравьиный алгоритм
	// минимальный гамильтонов цикл
	U_PTR(EdgeList) m_min_hamilton_cycle_ant;

	// длина цикла
	Weight m_hamilton_cycles_length_ant;

	// ветви и границы
	// минимальный гамильтонов цикл
	U_PTR(EdgeList) m_min_hamilton_cycle_bnb;

	// длина цикла
	Weight m_hamilton_cycles_length_bnb;

public:
	// конструктор и деструктор
	PresetGraphManT9(
		const S_PTR(SystemSetting)& _settings,
		const S_PTR(Graph)& _graph,
		const S_PTR(StateVector) _states
	);
	~PresetGraphManT9() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//

	// расчет: Подходит ли граф
	bool CalculateCanCalculateCycle();

	// расчет: Кратчайший цикл. Ветви и границы
	bool CalculateBranchAndBounds();

	// расчет: Кратчайший цикл. Муравьиная колония
	bool CalculateAntColony();

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	// муравьиный алгоритм
	// получение: Кратчайший цикл
	const U_PTR(EdgeList)& GetMinHamiltonCycleAnt() const;

	// получение: Длина кратчайшего пути
	const Weight& GetHamiltonCyclesLengthAnt() const;

	// ветви и границы
	// получение: Кратчайший цикл
	const U_PTR(EdgeList)& GetMinHamiltonCycleBnb() const;

	// получение: Длина кратчайшего пути
	const Weight& GetHamiltonCyclesLengthBnb() const;
};

#endif // !PRESETGRAPHMANT9_h
