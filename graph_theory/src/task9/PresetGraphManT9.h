#ifndef PRESETGRAPHMANT9_h
#define PRESETGRAPHMANT9_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT9 :
	virtual public BaseGraphPresetManager
{
protected:

	// минимальный гамильтонов цикл
	U_PTR(EdgeList) m_max_flow;

	// длина цикла
	Weight m_max_flow_length;

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

	// получение: Кратчайший цикл
	const U_PTR(EdgeList)& GetMinHamiltonCycle() const;

	// получение: Длина кратчайшего пути
	const Weight& GetHamiltonCyclesLength() const;
};

#endif // !PRESETGRAPHMANT9_h
